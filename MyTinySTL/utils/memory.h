#ifndef TINYSTL_MEMORY_H
#define TINYSTL_MEMORY_H
// 这个头文件负责更高级的动态内存管理
// 包含一些基本函数、空间配置器、未初始化的储存空间管理，以及一个模板类 auto_ptr

#include <cstddef>
#include <cstdlib>
#include <climits>

#include "algobase.h"
#include "allocator.h"
#include "construct.h"
#include "uninitialized.h"

namespace mystl {
    // 获取对象地址
    template <typename Tp>
    constexpr Tp *address_of(Tp &value) noexcept {
        return &value;
    }

    // 获取/释放 临时缓冲区
    template <typename  T>
    pair<T*, ptrdiff_t> get_buffer_helper(ptrdiff_t len, T*) {
        if (len > static_cast<ptrdiff_t>(INT_MAX / sizeof(T))) {
            len = INT_MAX / sizeof(T);
        }
        while (len > 0) {
            T *tmp = static_cast<T *>(malloc(static_cast<size_t>(len) * sizeof(T)));
            if (tmp) {  // 判断是否申请成功
                return pair<T*, ptrdiff_t>(tmp, len);
            }
            len /= 2;  // 不断缩小申请空间
        }
        return pair<T*, ptrdiff_t>(nullptr, 0);
    }

    template <typename T>
    pair<T*, ptrdiff_t> get_temporary_buffer(ptrdiff_t len) {
        return get_buffer_helper(len, static_cast<T*>(0));
    }

    template <typename T>
    pair<T*, ptrdiff_t> get_temporary_buffer(ptrdiff_t len, T*) {
        return get_buffer_helper(len, static_cast<T*>(0));
    }

    template <class T>
    void release_temporary_buffer(T* ptr) {
        free(ptr);
        ptr = nullptr;
    }

    // 模板类 : temporary_buffer
    // 进行临时缓冲区的申请与释放
    template <typename ForwardIterator, typename T>
    class temporary_buffer {
    private:
        ptrdiff_t original_len;  // 缓冲区申请的大小
        ptrdiff_t len;  // 缓冲区实际的大小
        T *buffer;  // 指向缓冲区的指针

    public:
        // 构造、析构函数
        temporary_buffer(ForwardIterator first, ForwardIterator last);

        ~temporary_buffer() {
            mystl::destroy(buffer, buffer + len);
            free(buffer);
        }

        temporary_buffer(const temporary_buffer&) = delete;
        void operator=(const temporary_buffer&) = delete;

    public:
        ptrdiff_t   size()            const noexcept { return len; }
        ptrdiff_t   requested_size()  const noexcept { return original_len; }
        T           *begin()                noexcept { return buffer; }
        T           *end()                  noexcept { return buffer + len; }

    private:
        void allocate_buffer();
        void initialize_buffer(const T&, std::true_type) {}  // 构造函数什么也不做
        void initialize_buffer(const T &value, std::false_type) {
            mystl::uninitialized_fill_n(buffer, len, value);
        }
    };

    // 构造函数
    template <typename ForwardIterator, typename T>
    temporary_buffer<ForwardIterator, T>::
    temporary_buffer(ForwardIterator first, ForwardIterator last) {
        try {
            original_len = len;
            len = mystl::distance(first, last);  // 计算分配的空间大小
            allocate_buffer();  // 分配空间，不一定等于origin_len
            if (len > 0) {
                initialize_buffer(*first, std::is_trivially_default_constructible<T>());
            }
        }catch (...) {
            free(buffer);
            buffer = nullptr;
            len = 0;
        }
    }

    // allocate_buffer
    template <typename ForwardIterator, typename T>
    void temporary_buffer<ForwardIterator, T>::allocate_buffer() {
        if (len > static_cast<ptrdiff_t>(INT_MAX / sizeof(T))) {
            len = INT_MAX / sizeof(T);
        }
        while (len > 0) {
            buffer = static_cast<T*>(malloc(len * sizeof(T)));
            if (buffer) {
                break;
            }
            len /= 2;  // 不断缩小申请空间
        }
    }

    // 模板类：auto_ptr
    // 一个具有严格对象所有权的小型智能指针
    template <class T>
    class auto_ptr {
    public:
        typedef T elem_type;

    private:
        T *m_ptr;  // 实际指针

    public:
        // 构造、复制、析构函数
        explicit auto_ptr(T *p = nullptr) :m_ptr(p) {}
        auto_ptr(auto_ptr &rhs) :m_ptr(rhs.release()) {}
        template<typename U>
        auto_ptr(auto_ptr<U> &rhs) : m_ptr(rhs.release()) {}

        auto_ptr &operator=(auto_ptr &rhs) {
            if (this != &rhs) {
                delete m_ptr;
                m_ptr = rhs.release();
            }
            return *this;
        }

        template<typename U>
        auto_ptr& operator=(auto_ptr<U> &rhs) {
            if (this->get() != rhs.get()) {
                delete m_ptr;
                m_ptr = rhs.release();
            }
            return *this;
        }
        ~auto_ptr() {delete m_ptr;}

    public:
        // 重载 operator* 和 operator->
        T &operator*() const { return *m_ptr; }
        T *operator->() const { return m_ptr; }

        // 获得指针
        T *get() const { return m_ptr; }

        // 释放指针
        T *release() {
            T *tmp = m_ptr;
            m_ptr = nullptr;
            return tmp;
        }

        // 重置指针
        void reset(T *p = nullptr) {
            if (m_ptr != p) {
                delete m_ptr;
                m_ptr = p;
            }
        }
    };

}  // namespace mystl;
#endif //TINYSTL_MEMORY_H
