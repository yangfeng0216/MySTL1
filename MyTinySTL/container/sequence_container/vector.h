#ifndef TINYSTL_VECTOR_H
#define TINYSTL_VECTOR_H

// vector 头文件

// 异常保证
// mystl::vecotr<T> 满足基本异常保证，部分函数无异常保证，并对以下函数做强异常安全保证：
//   * emplace
//   * emplace_back
//   * push_back
// 当 std::is_nothrow_move_assignable<T>::value == true 时，以下函数也满足强异常保证：
//   * reserve
//   * resize
//   * insert

#include <initializer_list>
#include "iterator.h"
#include "memory.h"
#include "util.h"
#include "exceptdef.h"
#include "algo.h"

namespace mystl {
#ifdef max
    #pragma message("#undefing marco max")
#undef max
#endif // max

#ifdef min
    #pragma message("#undefing marco min")
#undef min
#endif // min
}  // namespace mystl;

namespace mystl {
    // vector
    template <typename T>
    class vector {
        // vector<bool> 特殊性，并不是STL容器
        static_assert(!std::is_same<bool, T>::value, "vector<bool> is not support in mystl.");
    public:
        // 嵌套类型定义
        typedef mystl::allocator<T>                         allocator_type;
        typedef mystl::allocator<T>                         data_allocator;

        typedef typename allocator_type::value_type         value_type;
        typedef typename allocator_type::pointer            pointer;
        typedef typename allocator_type::const_pointer      const_pointer;
        typedef typename allocator_type::reference          reference;
        typedef typename allocator_type::const_reference    const_reference;
        typedef typename allocator_type::size_type          size_type;
        typedef typename allocator_type::difference_type    difference_type;

        // vecrtor的迭代器是普通指针，randomiterator
        typedef value_type*                                 iterator;
        typedef const value_type*                           const_iterator;
        typedef mystl::reverse_iterator<iterator>           reverse_iterator;
        typedef mystl::reverse_iterator<const_iterator>     const_reverse_iterator;

        allocator_type get_allocator() { return data_allocator(); }

    private:
        iterator begin_;    // 记录目前使用空间的头部
        iterator end_;      // 记录目前使用空间的尾部
        iterator cap_;      // 表示目前储存空间的尾部

    public:
        // 构造, 复制, 移动, 析构
        // 无参构造函数
        vector() noexcept { try_init(); }

        // 有参构造函数
        explicit vector(size_type n) { fill_init(n, value_type()); }  // 调用value_type的默认构造函数

        vector(size_type n, const value_type &value) { fill_init(n, value); }  // 使用value初始化分配的空间

        // 迭代器范围初始化
        //函数参数里的Iter类型，其值按说是与iterator是相同的，但是替换后并不能成功运行
        //这是因为iterator是T*，但是传参可能是const T*，所以使用另一个类型Iter，并让它自行推断参数类型
        template <typename Iter, typename std::enable_if<  // 如果是input_iterator_tag, int = 0
                mystl::is_input_iterator<Iter>::value, int>::type = 0>
        vector(Iter first, Iter last) {
            MYSTL_DEBUG(!(last < first));
            range_init(first, last);
        }

        // 拷贝构造函数
        vector(const vector &rhs) {
            range_init(rhs.begin_, rhs.end_);
        }

        // 移动构造函数, 因为肯定会改变传入对象，所以和拷贝构造函数不同，参数不能是const
        vector(vector &&rhs) noexcept
        :begin_(rhs.begin_), end_(rhs.end_), cap_(rhs.cap_) {
            rhs.begin_ = nullptr;
            rhs.end_ = nullptr;
            rhs.cap_ = nullptr;
        }

        // 列表初始化
        vector(std::initializer_list<value_type> ilist) {
            range_init(ilist.begin(), ilist.end());
        }

        // 常引用赋值
        vector &operator=(const vector &rhs);

        // 移动赋值
        vector &operator=(vector &&rhs) noexcept;

        // 初始化列表赋值
        vector &operator=(std::initializer_list<value_type> ilist) {
            vector tmp(ilist.begin(), ilist.end());
            swap(tmp);  // 交换后，tmp离开作用域时会销毁，调用析构函数，安全
            return *this;
        }

        ~vector() {
            destroy_and_recover(begin_, end_, cap_ - begin_);
            begin_ = end_ = cap_ = nullptr;
        }

    public:
        // 迭代器相关操作
        iterator        begin()       noexcept  { return begin_; }
        const_iterator  begin() const noexcept  { return begin_; }
        iterator        end()         noexcept  { return end_; }
        const_iterator  end()   const noexcept  { return end_; }  // 因为end_指向的空间不能使用，不用const

        reverse_iterator        rbegin()           noexcept  { return reverse_iterator(end()); }
        const_reverse_iterator  rbegin()     const noexcept  { return const_reverse_iterator(end()); }
        reverse_iterator        rend()             noexcept  { return reverse_iterator(begin()); }
        const_reverse_iterator  const_rend() const noexcept  { return const_reverse_iterator(begin()); }

        const_iterator         cbegin()  const noexcept { return begin(); }
        const_iterator         cend()    const noexcept { return end(); }
        const_reverse_iterator crbegin() const noexcept { return rbegin(); }
        const_reverse_iterator crend()   const noexcept { return rend(); }

        // 容量相关操作
        // 因为size_t是unsigned，所以将-1强制转换为unsigned会得到这个类型的最大数
        bool      empty()    const noexcept { return begin_ == end_; }
        size_type size()     const noexcept { return static_cast<size_type>(end_ - begin_); }
        size_type max_size() const noexcept { return static_cast<size_type>(-1) / sizeof(T); }
        size_type capacity() const noexcept { return static_cast<size_type>(cap_ - begin_); }

        void reserve(size_type n);
        void shrink_to_fit();

        // 在C++中，const成员函数与非const成员函数是可以重载的。
        // 访问元素相关操作
        reference operator[](size_type n) {
            MYSTL_DEBUG(n < size());
            return *(begin_ + n);
        }

        const_reference operator[](size_type n) const {
            MYSTL_DEBUG(n < size());
            return *(begin_ + n);
        }

        reference at(size_type n) {
            THROW_OUT_OF_RANGE_IF(n >= size(), "vector<T>::at() subscript out of range");
            return (*this)[n];
        }

        const_reference at(size_type n) const {
            THROW_OUT_OF_RANGE_IF(n >= size(), "vector<T>::at() subscript out of range");
            return (*this)[n];
        }

        reference front() {
            MYSTL_DEBUG(!empty());
            return *begin_;
        }

        const_reference front() const {
            MYSTL_DEBUG(!empty());
            return *begin_;
        };

        reference back() {
            MYSTL_DEBUG(!empty());
            return *(end_ - 1);
        }

        const_reference back() const {
            MYSTL_DEBUG(!empty());
            return *(end_ - 1);
        };

        pointer data() noexcept {
            return begin_;
        }

        const_pointer data() const noexcept {
            return begin_;
        }

        // 修改容器容量
        // assign
        void assign(size_type n, const value_type &value) {
            fill_assign(n, value);
        }

        template <typename Iter, typename std::enable_if<
                mystl::is_input_iterator<Iter>::value, int>::type = 0>
        void assign(Iter first, Iter last) {
            MYSTL_DEBUG(!(last < first));
            copy_assign(first, last, iterator_category(first));
        }

        void assign(std::initializer_list<value_type> il){
            copy_assign(il.begin(), il.end(), mystl::forward_iterator_tag());
        }

        // emplace、emplace_back
        template <typename ...Args>
        iterator emplace(const_iterator pos, Args&& ...args);

        template <typename ...Args>
        void emplace_back(Args&& ...args);

        // push_back / pop_back
        void push_back(const value_type &value);

        void push_back(value_type &&value) {
            emplace_back(mystl::move(value));  // 这里能不能用mystl::forward();
        }

        void pop_back();

        // insert
        iterator insert(const_iterator pos, const value_type &value);

        iterator insert(const_iterator pos, value_type &&value) {
            return emplace(pos, mystl::move(value));
        }

        iterator insert(const_iterator pos, size_type n, const value_type &value) {
            MYSTL_DEBUG(pos >= begin() && pos <= end());
            return fill_insert(const_cast<iterator>(pos), n, value);
        }

        template <class Iter, typename std::enable_if<
                mystl::is_input_iterator<Iter>::value, int>::type = 0>
        void insert(const_iterator pos, Iter first, Iter last) {
            MYSTL_DEBUG(pos >= begin() && pos <= end() && !(last < first));
            copy_insert(const_cast<iterator>(pos), first, last);
        }

        // erase / clear
        iterator erase(const_iterator pos);

        iterator erase(const_iterator first, const_iterator last);

        void clear() { erase(begin(), end()); }

        // resize / reverse
        void resize(size_type new_size) { return resize(new_size, value_type()); }

        void resize(size_type new_size, const value_type &value);

        void reverse() { mystl::reverse(begin(), end()); }

        // swap
        void swap(vector &rhs) noexcept;

    private:
        // helper functions
        // initialize / destroy
        void try_init() noexcept;

        void init_space(size_type size, size_type cap);

        void fill_init(size_type n, const value_type& value);

        template <typename Iter>
        void range_init(Iter first, Iter last);

        void destroy_and_recover(iterator first, iterator last, size_type n);

        // calculate the growth size
        size_type get_new_cap(size_type add_size);

        // assign
        void fill_assign(size_type n, const value_type &value);

        template <typename IIter>
        void copy_assign(IIter first, IIter last, input_iterator_tag);

        template <typename FIter>
        void copy_assign(FIter first, FIter last, forward_iterator_tag);

        // reallocate
        template <typename ...Args>
        void reallocate_emplace(iterator pos, Args&& ...args);

        void reallocate_insert(iterator pos, const value_type& value);

        // insert
        iterator fill_insert(iterator pos, size_type n, const value_type &value);

        template <typename IIter>
        void copy_insert(iterator pos, IIter first, IIter last);

        // shrink_to_fit
        void reinsert(size_type size);
    };
    /*********************************
     *赋值操作符
     *********************************/
     // 复制赋值操作符
    template <typename T>
    vector<T> &vector<T>::operator=(const vector &rhs) {
        if (this != &rhs) {                             // 不处理自己给自己赋值
            const auto len = rhs.size();
            if (len > capacity()) {                     // 当前vector容量不够，需要扩容
                vector tmp(rhs.begin(), rhs.end());
            swap(tmp);                              // this 和 另一个vector互换
            }else if (size() >= len) {                 // 当前vector内容比rhs长，需要将当前vector多余的内容析构
                auto i = mystl::copy(rhs.begin(), rhs.end(), begin());
                data_allocator::destroy(i, end_);      // 析构范围内的元素，但并不会释放空间
                end_ = begin_ + len;
            }else {
                mystl::copy(rhs.begin(), rhs.begin() + size(), begin_);
                mystl::uninitialized_copy(rhs.begin() + size(), rhs.end(), end_);
                cap_ = end_ = begin_ + len;
            }
        }
        return *this;
    }

    // 移动赋值操作符
    template <typename T>
    vector<T> &vector<T>::operator=(vector &&rhs) noexcept {
        destroy_and_recover(begin_, end_, cap_ - begin_);
        begin_ = rhs.begin_;
        end_ = rhs.end_;
        cap_ = rhs.cap_;
        rhs.begin_ = nullptr;
        rhs.end_ = nullptr;
        rhs.cap_ = nullptr;

        return *this;
    }

    /*********************************
     *容量相关操作
     *********************************/
    // 预留空间大小，当原容量小于要求大小时，才会重新分配
    template<typename T>
    void vector<T>::reserve(size_type n) {
        if (capacity() < n) {
            THROW_LENGTH_ERROR_IF(n > max_size(),
                                  "n can not larger than max_size() in vector<T>::reserve(n)");
            const auto old_size = size();
            auto tmp = data_allocator::allocate(n);
            mystl::uninitialized_move(begin_, end_, tmp);
            data_allocator::deallocate(begin_, cap_ - begin_);
            begin_ = tmp;
            end_ = tmp + old_size;
            cap_ = begin_ + n;
        }
    }

    // 放弃多余的容量
    template <typename T>
    void vector<T>::shrink_to_fit() {
        if (end_ < cap_) {
            reinsert(size());
        }
    }

    /*********************************
     *emplace
     *********************************/
    // 在 pos 位置就地构造元素，避免额外的复制或移动开销
    // 将参数传递给T的构造函数，而不是包含参数的对象，emplace使用这些参数在内存空间中直接构造元素
    template <typename T>
    template <typename ...Args>
    typename vector<T>::iterator vector<T>::emplace(const_iterator pos, Args&& ...args) {
        MYSTL_DEBUG(pos >= begin() && pos <= end());
        auto xpos = const_cast<iterator>(pos);  // 去const
        const size_type n = xpos - begin_;
        if (end_ != cap_ && xpos == end_) {
            // address_of()就是取对象的地址，这里直接传end_也可以
            // construct函数是在指定位置，依据传入的参数构建对象
            // 调用的方法是::new ((void*)pos) T(args...)
            data_allocator::construct(mystl::address_of(*end_),  mystl::forward<Args>(args)...);
            ++end_;
        }else if (end_ != cap_) {  // 还有未使用空间
            auto new_end = end_;
            data_allocator::construct(mystl::address_of(*end_), *(end_ - 1));  // 先对end_执行构造
            ++new_end;
            mystl::copy_backward(xpos, end_ - 1, end_);
            *xpos = value_type(mystl::forward<Args>(args)...);  // 数据搬运操作
            end_ = new_end;
        }else {  // 如果空间不够则重新分配空间，并在 pos 处就地构造元素
            reallocate_emplace(xpos, mystl::forward<Args>(args)...);
        }

        return begin() + n;
    }

    // 在尾部就地构造元素，避免额外的复制或移动开销
    template <typename T>
    template <typename ...Args>
    void vector<T>::emplace_back(Args&& ...args) {
        if (end_ < cap_) {
            data_allocator::construct(mystl::address_of(*end_), mystl::forward<Args>(args)...);
            ++end_;
        }else {
            reallocate_emplace(end_, mystl::forward<Args>(args)...);
        }
    }

    /*********************************
     * push_back, pop_back
     *********************************/
    // 在尾部插入元素
    template <typename T>
    void vector<T>::push_back(const value_type &value) {
        if (end_ != cap_) {
            data_allocator::construct(mystl::address_of(*end_), value);
            ++end_;
        }else {
            reallocate_insert(end_, value);
        }
    }

    // 弹出尾部元素
    template <typename T>
    void vector<T>::pop_back() {
        MYSTL_DEBUG(!empty());
        data_allocator::destroy(end_ - 1);  // 调用析构函数,有可能什么也不做
        --end_;
    }

    /*********************************
     * insert
     * emplace和insert相比，只是因为传参而不是传对象，所以少了构建一次临时对象的步骤
     *********************************/
    // 在pos处插入元素
    template <typename T>
    typename vector<T>::iterator vector<T>::insert(const_iterator pos, const value_type &value) {
        MYSTL_DEBUG(pos >= begin() && pos <= end());
        auto xpos = const_cast<iterator> (pos);
        const size_type n = pos - begin_;
        if (end_ != cap_ && xpos == end_) {
            data_allocator::construct(mystl::address_of(*end_), value);
            ++end_;
        }else if (end_ != cap_) {
            auto new_end = end_;
            data_allocator::construct(mystl::address_of(*end_), *(end_ - 1));
            ++new_end;
            auto value_copy = value;  // 避免元素因以下复制操作而被改变
            mystl::copy_backward(xpos, end_ - 1, end_);
            *xpos = mystl::move(value_copy);
        }else {
            reallocate_insert(xpos, value);
        }
        return begin_ + n;
    }

    /*********************************
    * erase / clear
    *********************************/
    // 删除 pos 位置上的元素
    template <typename T>
    typename vector<T>::iterator vector<T>::erase(const_iterator pos) {
        MYSTL_DEBUG(pos >= begin() && pos < end());
        iterator xpos = begin_ + (pos - begin());  // 为什么不用强制转换了？
        mystl::move(xpos + 1, end_, xpos);  // 对应哪个重载函数
        data_allocator::destroy(end_ - 1);
        --end_;
        return xpos;
    }

    // 删除[first, last)上的元素
    template <typename T>
    typename vector<T>::iterator
    vector<T>::erase(const_iterator first, const_iterator last) {
        MYSTL_DEBUG(first >= begin() && last <= end() && !(last < first));
        const auto n = first - begin();
        iterator r = begin_ + (first - begin());
        data_allocator::destroy(mystl::move(r + (last - first), end_, r), end_);
        end_ = end_ - (last - first);
        return begin_ + n;
    }

    /*********************************
     * reverse / resize
     *********************************/
    template <typename T>
    void vector<T>::resize(size_type new_size, const value_type &value) {
        if (new_size < size()) {
            erase(begin() + new_size, end());
        }else {
            insert(end(), new_size - size(), value);
        }
    }

    /*********************************
     * swap
     *********************************/
    template <typename T>
    void vector<T>::swap(vector<T>& rhs) noexcept {
        if (this != &rhs) {
            mystl::swap(begin_, rhs.begin_);
            mystl::swap(end_, rhs.end_);
            mystl::swap(cap_, rhs.cap_);
        }
    }

    /*********************************
     * helper function
     *********************************/
    // try_init：若分配失败则忽略，不抛出异常, 令指针指向为空
    template <typename T>
    void vector<T>::try_init() noexcept {
        try {
            begin_ = data_allocator::allocate(16);
            end_ = begin_;
            cap_ = begin_ + 16;
        }catch (...) {
            begin_ = nullptr;
            end_ = nullptr;
            cap_ = nullptr;
        }
    }

    // init_space 函数, 会抛出异常，因为后面会初始化空间
    template<typename T>
    void vector<T>::init_space(size_type size, size_type cap) {
        try {
            begin_ = data_allocator::allocate(cap);
            end_ = begin_ + size;
            cap_ = begin_ + cap;
        }catch (...) {
            begin_ = nullptr;
            end_ = nullptr;
            cap_ = nullptr;
            throw;
        }
    }

    // fill_init
    template <typename T>
    void vector<T>::fill_init(size_type n, const value_type &value) {
        const size_type init_size = mystl::max(static_cast<size_type>(16), n);
        init_space(n, init_size);
        mystl::uninitialized_fill_n(begin_, n, value);
    }

    // range_init
    template<typename T>
    template<typename Iter>
    void vector<T>::range_init(Iter first, Iter last) {
        const size_type len = mystl::distance(first, last);
        const size_type init_size = mystl::max(len, static_cast<size_type>(16));
        init_space(len, init_size);
        mystl::uninitialized_copy(first, last, begin_);
    }

    // destroy_and_recover 函数
    template<typename T>
    void vector<T>::destroy_and_recover(iterator first, iterator last, size_type n) {
        data_allocator::destroy(first, last);
        data_allocator::deallocate(first, n);
    }

    // get_new_cap 函数
    // 获取能增加的容量
    template <typename T>
    typename vector<T>::size_type vector<T>::get_new_cap(size_type add_size) {
        // 现有容量大小
        const auto old_size = capacity();
        // 如果现有容量+要增加的容量 大于 最大容量 直接异常
        THROW_LENGTH_ERROR_IF(old_size > max_size() - add_size,
                              "vector<T>'s size too big");
        // 如果现有容量的1.5倍 大于 最大容量
        if (old_size > max_size() - old_size / 2) {
            // 如果 现有容量 + 要增加的容量 + 16 大于 最大容量
            // 则返回 现有容量 + 要增加的容量
            // 否则返回 现有容量 + 要增加的容量 + 16
            return old_size + add_size > max_size() - 16
                        ? old_size + add_size
                        : old_size + add_size + 16;
        }

        // 如果现有容量为0
        // 则返回 要增加的容量 和 16 比较大的
        // 否则返回 现有容量1.5倍 和 现有容量+要增加的容量 比较大的
        const size_type new_size = old_size == 0
                                   ? mystl::max(add_size, static_cast<size_type>(16))
                                   : mystl::max(old_size + old_size / 2, old_size + add_size);
        return new_size;
    }

    // fill_assign 函数
    // fill_assign将vector赋值为n个value
    template <typename T>
    void vector<T>::fill_assign(size_type n, const value_type &value) {
        if (n > capacity()) {
            vector tmp(n, value);
            swap(tmp);
        }else if (n > size()) {
            mystl::fill(begin(), end(), value);
            end_ = mystl::uninitialized_fill_n(end_, n - size(), value);
        }else {
            //删除末尾多出来的内容
            erase(mystl::fill_n(begin_, n, value), end_);
        }
    }

    // copy_assign 函数
    template <typename T>
    template <typename IIter>
    void vector<T>::copy_assign(IIter first, IIter last, input_iterator_tag) {
        auto cur = begin_;
        for (; first != last && cur != end_; ++first, ++cur) {
            *cur = *first;
        }

        //如果size比迭代器范围大，说明后面还有内容，应该删掉
        if (first == last) {
            erase(cur, end_);
        } else {  //继续复制迭代器范围内的元素
            // 越界交给insert去处理
            insert(end_, first, last);
        }
    }

    template <typename T>
    template <typename FIter>
    void vector<T>::copy_assign(FIter first, FIter last, forward_iterator_tag) {
        const size_type len = mystl::distance(first, last);
        if (len > capacity()) {
            vector tmp(first, last);
            swap(tmp);
        }else if (size() >= len) {
            auto new_end = mystl::copy(first, last, begin_);
            data_allocator::destroy(new_end, end_);
            end_ = new_end;
        }else {
            auto mid = first;
            mystl::advance(mid, size());
            mystl::copy(first, mid, begin_);
            auto new_end = mystl::uninitialized_copy(mid, last, end_);
            end_ = new_end;
        }
    }

    // reallocate_emplace
    // 重新分配空间并在 pos 处就地构造元素
    template <typename T>
    template <typename ...Args>
    void vector<T>::reallocate_emplace(iterator pos, Args&& ...args) {
        const auto new_size = get_new_cap(1);
        auto new_begin = data_allocator::allocate(new_size);
        auto new_end = new_begin;
        try {
            new_end = mystl::uninitialized_move(begin_, pos, new_begin);
            data_allocator::construct(mystl::address_of(*new_end), mystl::forward<Args>(args)...);
            ++new_end;
            new_end = mystl::uninitialized_move(pos, end_, new_end);
        }catch (...) {
            data_allocator::deallocate(new_begin, new_size);
            throw;
        }
        destroy_and_recover(begin_, end_, cap_ - begin_);
        begin_ = new_begin;
        end_ = new_end;
        cap_ = new_begin + new_size;
    }

    // reallocate_insert
    // 重新分配空间并在 pos 处插入元素
    template <typename T>
    void vector<T>::reallocate_insert(iterator pos, const value_type &value) {
        const auto new_size = get_new_cap(1);
        auto new_begin = data_allocator::allocate(new_size);
        auto new_end = new_begin;
        const value_type& value_copy = value;
        try {
            new_end = mystl::uninitialized_move(begin_, pos, new_begin);
            data_allocator::construct(mystl::address_of(*new_end), value_copy);
            ++new_end;
            new_end = mystl::uninitialized_move(pos, end_, new_end);
        }catch (...) {
            data_allocator::deallocate(new_begin, new_size);
            throw;
        }
        destroy_and_recover(begin_, end_, cap_ - begin_);
        begin_ = new_begin;
        end_ = new_end;
        cap_ = new_begin + new_size;
    }

    // fill_insert
    template <typename T>
    typename vector<T>::iterator vector<T>::fill_insert(iterator pos, size_type n, const value_type &value) {
        if (n == 0) {
            return pos;
        }
        const size_type xpos = pos - begin_;
        const value_type value_copy = value;  // 避免被覆盖
        if (static_cast<size_type>(cap_ - end_) >= n) {
            // 如果备用空间大于等于增加的空间
            const size_type after_elems = end_ - pos;
            auto old_end = end_;
            if (after_elems > n) {
                mystl::uninitialized_copy(end_ - n, end_, end_);
                end_ += n;
                mystl::move_backward(pos, old_end - n, old_end);  // 这里为什么用move
                mystl::uninitialized_fill_n(pos, n, value_copy);
            }else {
                end_ = mystl::uninitialized_fill_n(end_, n - after_elems, value_copy);
                end_ = mystl::uninitialized_move(pos, old_end, end_);
                mystl::uninitialized_fill_n(pos, after_elems, value_copy);
            }
        }else {
            // 如果备用空间不足
            const auto new_size = get_new_cap(n);
            auto new_begin = data_allocator::allocate(new_size);
            auto new_end = new_begin;
            try {
                new_end = mystl::uninitialized_move(begin_, pos, new_begin);
                new_end = mystl::uninitialized_fill_n(new_end, n, value);
                new_end = mystl::uninitialized_move(pos, end_, new_end);
            }catch (...) {
                destroy_and_recover(new_begin, new_end, new_size);
                throw;
            }
            data_allocator::deallocate(begin_, cap_ - begin_);
            begin_ = new_begin;
            end_ = new_end;
            cap_ = begin_ + new_size;
        }
        return begin_ + xpos;
    }

    // copy_insert 函数
    template <typename T>
    template <typename IIter>
    void vector<T>:: copy_insert(iterator pos, IIter first, IIter last) {
        if (first == last) {
            return;
        }
        const auto n = mystl::distance(first, last);
        // 如果备用空间大小足够
        if ((cap_ - end_) >= n) {
            const auto after_elems = end_ - pos;
            auto old_end = end_;
            if (after_elems > n) {
                end_ = mystl::uninitialized_copy(end_ - n, end_, end_);
                mystl::move_backward(pos, old_end - n, old_end);
                mystl::uninitialized_copy(first, last, pos);
            }else {
                auto mid = first;
                mystl::advance(mid, after_elems);
                end_ = mystl::uninitialized_copy(mid, last, end_);
                end_ = mystl::uninitialized_move(pos, old_end, end_);
                mystl::uninitialized_copy(first, mid, pos);
            }
        }else { // 备用空间不足
            const auto new_size = get_new_cap(n);
            auto new_begin = data_allocator::allocate(new_size);
            auto new_end = new_begin;
            try{
                new_end = mystl::uninitialized_move(begin_, pos, new_begin);
                new_end = mystl::uninitialized_copy(first, last, new_end);
                new_end = mystl::uninitialized_move(pos, end_, new_end);
            }catch (...) {
                destroy_and_recover(new_begin, new_end, new_size);
                throw;
            }
            data_allocator::deallocate(begin_, cap_ - begin_);
            begin_ = new_begin;
            end_ = new_end;
            cap_ = begin_ + new_size;
        }
    }

    // reinsert 函数
    template <typename T>
    void vector<T>::reinsert(size_type size) {
        auto new_begin = data_allocator::allocate(size);
        try {
            mystl::uninitialized_move(begin_, end_, new_begin);
        }catch (...) {
            data_allocator::deallocate(new_begin, size);
            throw;
        }
        // 前面用的是move，所以不能再调用析构函数
        data_allocator::deallocate(begin_, cap_ - begin_);
        begin_ = new_begin;
        end_ = begin_ + size;
        cap_ = begin_ + size;
    }

    /*********************************
    * 运算符重载
    *********************************/
    template <typename T>
    bool operator==(const vector<T> &lhs, const vector<T> &rhs) {
        return lhs.size() == rhs.size()
        && mystl::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template <typename T>
    bool operator<(const vector<T> &lhs, const vector<T> &rhs) {
        return mystl::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <typename T>
    bool operator!=(const vector<T> &lhs, const vector<T> &rhs) {
        return !(lhs == rhs);
    }

    template <typename T>
    bool operator>(const vector<T> &lhs, const vector<T> &rhs) {
        return rhs < lhs;
    }

    template <typename T>
    bool operator<=(const vector<T> &lhs, const vector<T> &rhs) {
        return !(rhs < lhs);
    }

    template <typename T>
    bool operator>=(const vector<T> &lhs, const vector<T> &rhs) {
        return !(lhs < rhs);
    }
    /*********************************
    * swap函数重载
    *********************************/
    template <typename T>
    void swap(vector<T> &lhs, vector<T> &rhs) {
        lhs.swap(rhs);
    }
}  // namespace
#endif //TINYSTL_VECTOR_H
