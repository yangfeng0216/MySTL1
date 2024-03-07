#ifndef TINYSTL_BASIC_STRING_H
#define TINYSTL_BASIC_STRING_H

// basic_string: 字符串

#include <iostream>
#include "iterator.h"
#include "memory.h"
#include "functional.h"
#include "exceptdef.h"

namespace mystl {
    // char_traits
    template <typename CharType>
    struct char_traits {
        typedef CharType char_type;

        static size_t length(const char_type *str) {
            size_t len = 0;
            for (; *str != char_type(0); ++str) {
                ++len;
            }
            return len;
        }

        static int compare(const char_type *s1, const char_type *s2, size_t n) {
            for (; n != 0; --n, ++s1, ++s2) {
                if (*s1 < *s2) {
                    return -1;
                }
                if (*s2 < *s1) {
                    return 1;
                }
            }
            return 0;
        }

        static char_type *copy(char_type *dst, const char_type *src, size_t n) {
            MYSTL_DEBUG(src + n <= dst || dst + n <= src);  // 防止覆盖
            char_type *r = dst;
            for (; n != 0; --n, ++dst, ++src) {
                *dst = *src;
            }
            return r;
        }

        static char_type *move(char_type *dst, const char_type *src, size_t n) {
            char_type *r = dst;
            // 考虑覆盖
            if (dst < src) {
                for (; n != 0; --n, ++dst, ++src) {
                    *dst = *src;
                }
            }else if (src < dst) {
                dst += n;
                src += n;
                for (; n != 0; --n) {
                    *--dst = *--src;
                }
            }
            return r;
        }

        static char_type *fill(char_type *dst, char_type ch, size_t count) {
            char_type* r = dst;
            for (; count > t; --count, ++dst) {
                *dst = ch;
            }
            return r;
        }
    };

    // Partialized. char_traits<char>
    template <>
    struct char_traits<char> {
        typedef char char_type;

        static size_t length(const char_type *str) noexcept {
            return std::strlen(str)
        }

        static int compare(const char_type *s1, const char_type *s2, size_t n) noexcept {
            return std::memcmp(s1, s2, n);
        }

        static char_type* copy(const char_type *dst, const char_type *src, size_t n) noexcept {
            MYSTL_DEBUG(src + n <= dst || dst + n <= src);
            return static_cast<char_type*>(std::memcpy(dst, src, n));
        }

        static char_type* move(const char_type *dst, const char_type *src, size_t n) noexcept {
            return static_cast<char_type*>(std::memmove(dst, src, n));
        }

        static char_type* fill(const char_type *dst, const char_type ch, size_t count) noexcept {
            return static_cast<char_type*>(std::memset(dst, ch, count));
        }
    };

    // Partialized. char_traits<wchar_t>
    template <>
    struct char_traits<wchar_t>
    {
        typedef wchar_t char_type;

        static size_t length(const char_type *str) noexcept {
            return std::wcslen(str)
        }

        static int compare(const char_type *s1, const char_type *s2, size_t n) noexcept {
            return std::wmemcmp(s1, s2, n);
        }

        static char_type* copy(const char_type *dst, const char_type *src, size_t n) noexcept {
            MYSTL_DEBUG(src + n <= dst || dst + n <= src);
            return static_cast<char_type*>(std::wmemcpy(dst, src, n));
        }

        static char_type* move(const char_type *dst, const char_type *src, size_t n) noexcept {
            return static_cast<char_type*>(std::wmemmove(dst, src, n));
        }

        static char_type* fill(const char_type *dst, const char_type ch, size_t count) noexcept {
            return static_cast<char_type*>(std::wmemset(dst, ch, count));
        }
    };

    // Partialized. char_traits<char16_t>
    template <>
    struct char_traits<char16_t> {
        typedef char16_t char_type;

        static size_t length(const char_type *str) noexcept
        {
            size_t len = 0;
            for (; *str != char_type(0); ++str) {
                ++len;
            }
            return len;
        }

        static int compare(const char_type *s1, const char_type *s2, size_t n) noexcept {
            for (; n != 0; --n, ++s1, ++s2)
            {
                if (*s1 < *s2) {
                    return -1;
                }
                if (*s2 < *s1) {
                    return 1;
                }
            }
            return 0;
        }

        static char_type* copy(char_type *dst, const char_type *src, size_t n) noexcept {
            MYSTL_DEBUG(src + n <= dst || dst + n <= src);
            char_type *r = dst;
            for (; n != 0; --n, ++dst, ++src) {
                *dst = *src;
            }
            return r;
        }

        static char_type *move(char_type *dst, const char_type *src, size_t n) noexcept {
            char_type *r = dst;
            if (dst < src) {
                for (; n != 0; --n, ++dst, ++src)
                    *dst = *src;
            }else if (src < dst) {
                dst += n;
                src += n;
                for (; n != 0; --n) {
                    *--dst = *--src;
                }
            }
            return r;
        }

        static char_type* fill(char_type *dst, char_type ch, size_t count) noexcept {
            char_type *r = dst;
            for (; count > 0; --count, ++dst)
                *dst = ch;
            return r;
        }
    };

    // Partialized. char_traits<char32_t>
    template <>
    struct char_traits<char32_t> {
        typedef char16_t char_type;

        static size_t length(const char_type *str) noexcept {
            size_t len = 0;
            for (; *str != char_type(0); ++str) {
                ++len;
            }
            return len;
        }

        static int compare(const char_type *s1, const char_type *s2, size_t n) noexcept {
            for (; n != 0; --n, ++s1, ++s2)
            {
                if (*s1 < *s2) {
                    return -1;
                }
                if (*s2 < *s1) {
                    return 1;
                }
            }
            return 0;
        }

        static char_type* copy(char_type *dst, const char_type *src, size_t n) noexcept {
            MYSTL_DEBUG(src + n <= dst || dst + n <= src);
            char_type *r = dst;
            for (; n != 0; --n, ++dst, ++src) {
                *dst = *src;
            }
            return r;
        }

        static char_type *move(char_type *dst, const char_type *src, size_t n) noexcept {
            char_type *r = dst;
            if (dst < src) {
                for (; n != 0; --n, ++dst, ++src)
                    *dst = *src;
            }else if (src < dst) {
                dst += n;
                src += n;
                for (; n != 0; --n) {
                    *--dst = *--src;
                }
            }
            return r;
        }

        static char_type* fill(char_type *dst, char_type ch, size_t count) noexcept {
            char_type *r = dst;
            for (; count > 0; --count, ++dst)
                *dst = ch;
            return r;
        }
    };

    // 初始化 basic_string 尝试分配的最小 buffer 大小，可能被忽略
    #define STRING_INIT_SIZE 32

    // 模板类 basic_string
    // 参数一代表字符类型，参数二代表萃取字符类型的方式，缺省使用 mystl::char_traits
    template <class CharType, class CharTraits = mystl::char_traits<CharType>>
    class basic_string {
    public:
        typedef CharTraits                              traits_type;
        typedef CharTraits                              char_tratis;

        typedef mystl::allocator<CharType>              allocator_type;
        typedef mystl::allocator<CharType>              data_allocator;

        typedef typename allocator_type::value_type         value_type;
        typedef typename allocator_type::pointer            pointer;
        typedef typename allocator_type::const_pointer      const_pointer;
        typedef typename allocator_type::reference          reference;
        typedef typename allocator_type::const_reference    const_reference;
        typedef typename allocator_type::size_type          size_type;
        typedef typename allocator_type::difference_type    difference_type;

        // 迭代器就是普通指针，randomiterator
        typedef value_type*                                 iterator;
        typedef const value_type*                           const_iterator;
        typedef mystl::reverse_iterator<iterator>           reverse_iterator;
        typedef mystl::reverse_iterator<const_iterator>     const_reverse_iterator;

        allocator_type get_allocator() { return allocator_type(); }

        static_assert(std::is_pod<CharType>::value, "Character type of basic_string must be a POD");
        static_assert(std::is_same<CharType, typename traits_type::char_type>::value,
                      "CharType must be same as traits_type::char_type");

    public:
        // 末尾位置的值，例:
        // if (str.find('a') != string::npos) { /* do something */ }
        static constexpr size_type npos = static_cast<size_type>(-1);

    private:
        iterator buffer_;  // 储存字符串的起始位置
        size_type size_;  // 大小
        size_type cap_;  // 容量

    public:
        // 构造、复制、移动、析构函数
        basic_string() noexcept { try_init(); }

        basic_string(size_type n, value_type ch)
        :buffer_(nullptr), size_(0), cap_(0) {
            fill_init(n, ch);
        }

        basic_string(const basic_string &other, size_type pos)
        :buffer_(nullptr), size_(0), cap_(0) {
            init_from(other.buffer_, pos, other.size_ - pos);
        }
        basic_string(const basic_string &other, size_type pos, size_type count)
        :buffer_(nullptr), size_(0), cap_(0) {
            init_from(other.buffer_, pos, count);
        }

        basic_string(const_pointer str)
        :buffer_(nullptr), size_(0), cap_(0) {
            init_from(str, 0, char_traits::length(str));
        }

        basic_string(const_pointer str, size_type count)
        :buffer_(nullptr), size_(0), cap_(0) {
            init_from(str, 0, count);
        }

        template <class Iter, typename std::enable_if<
                mystl::is_input_iterator<Iter>::value, int>::type = 0>
        basic_string(Iter first, Iter last) {
            copy_init(first, last, iterator_category(first));
        }

        basic_string(const basic_string& rhs)
        :buffer_(nullptr), size_(0), cap_(0) {
            init_from(rhs.buffer_, 0, rhs.size_);
        }

        basic_string(basic_string &&rhs) noexcept
        :buffer_(rhs.buffer_), size_(rhs.size_), cap_(rhs.cap_) {
            rhs.buffer_ = nullptr;
            rhs.size_ = 0;
            rhs.cap_ = 0;
        }

        basic_string &operator=(const basic_string &rhs);

        basic_string &operator=(basic_string &&rhs) noexcept;

        basic_string &operator=(const_pointer str);

        basic_string &operator=(value_type ch);

        ~basic_string() { destroy_buffer(); }

    public:
        // 迭代器相关操作
        // 正向迭代器
        iterator begin() noexcept { return buffer_; }

        const_iterator begin() const noexcept { return buffer_; }

        iterator end() noexcept { return buffer_ + size_; }

        const_iterator end() const noexcept { return buffer_ + size_; }

        // 反向迭代器
        reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }

        const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }

        reverse_iterator rend() noexcept { return reverse_iterator(begin()); }

        const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }

        // const 迭代器
        const_iterator cbegin() const noexcept { return begin(); }

        const_iterator cend() const noexcept { return end(); }

        const_reverse_iterator crbegin() const noexcept { return rbegin(); }

        const_reverse_iterator crend() const noexcept { return rend(); }

        // 容量相关操作
        bool empty() const noexcept { return size_ == 0; }

        size_type size() const noexcept { return size_; }

        size_type length() const noexcept { return size_; }

        size_type capacity() const noexcept { return cap_; }

        size_type max_size() const noexcept { return static_cast<size_type>(-1); }

        void reserve(size_type n);

        void shrink_to_fit();

        // 访问元素相关操作
        reference operator[](size_type n) {
            MYSTL_DEBUG(n <= size_);
            if (n == size_) {
                *(buffer_ + n) = value_type();
            }
            return *(buffer_ + n);
        }

        const_reference operator[](size_type n) const {
            MYSTL_DEBUG(n <= size_);
            if (n == size_) {
                *(buffer_ + n) = value_type();
            }
            return *(buffer_ + n);
        }

        reference at(size_type n) {
            THROW_OUT_OF_RANGE_IF(n >= size_,
                                  "basic_string<Char, Traits>::at() subscript out of range");
            return (*this)[n];
        }

        const_reference at(size_type n) const {
            THROW_OUT_OF_RANGE_IF(n >= size_,
                                  "basic_string<Char, Traits>::at() subscript out of range");
            return (*this)[n];
        }

        reference front() {
            MYSTL_DEBUG(!empty());
            return *begin();
        }

        const_reference front() const {
            MYSTL_DEBUG(!empty());
            return *begin();
        }

        reference back() {
            MYSTL_DEBUG(!empty());
            return *(end() - 1);
        }

        const_reference back() const {
            MYSTL_DEBUG(!empty());
            return *(end() - 1);
        }

        const_pointer data() const noexcept {
            return to_raw_point();
        }

        const_pointer c_str() const noexcept {
            return to_raw_pointer();
        }

        // 添加删除相关操作
        // insert
        iterator insert(const_iterator pos, value_type ch);

        iterator insert(const_iterator pos, size_type count, value_type ch);

        template <typename Iter>
        iterator insert(const_iterator pos, Iter first, Iter last);

        // push_back / pop_back
        void push_back(value_type ch) { append(1, ch); }

        void pop_back() {
            MYSTL_DEBUG(!empty());
            --size_;
        }

        // TODO: 未完成
    };
}

#endif //TINYSTL_BASIC_STRING_H
