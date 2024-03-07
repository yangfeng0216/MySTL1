#ifndef TINYSTL_ALLOCATOR_H
#define TINYSTL_ALLOCATOR_H

// allocator: 管理内存的分配、释放，对象的构造、析构
#include "construct.h"
#include "util.h"

namespace mystl {
    // allocator
    template <typename T>
    class allocator {
    public:
        typedef T            value_type;        // 数据类型
        typedef T*           pointer;           // 数据类型指针
        typedef const T*     const_pointer;     // const数据类型指针
        typedef T&           reference;         // 数据类型引用
        typedef const T&     const_reference;   // const数据类型引用
        typedef size_t       size_type;         // 数据类型大小
        typedef ptrdiff_t    difference_type;   // 数据类型指针距离

    public:
        // 全部都是静态函数

        static T *allocate();
        static T *allocate(size_type n);

        static void deallocate(T *ptr);
        static void deallocate(T *ptr, size_type n);

        static void construct(T *ptr);
        static void construct(T *ptr, const T &value);
        static void construct(T *ptr, T &&value);

        template <typename... Args>
        static void construct(T *ptr, Args&& ...args);

        static void destroy(T *ptr);
        static void destroy(T *first, T *last);
    };

    // 申请空间
    template <typename T>
    T *allocator<T>::allocate() {  // 调用operator new 分配内存,大小为sizeof(T)
        return static_cast<T*>(::operator new(sizeof(T)));
    }

    template <typename T>
    T *allocator<T>::allocate(size_type n) {  // 大小为n * sizeof(T)
        if (n == 0) { return nullptr; }
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }

    // 释放空间
    template <typename T>
    void allocator<T>::deallocate(T *ptr) {
        if (ptr == nullptr) { return; }
        ::operator delete(ptr);
    }

    template <typename T>
    void allocator<T>::deallocate(T *ptr, size_type) {
        if (ptr == nullptr) { return; }
        ::operator delete(ptr);
    }

    // 构造，调用全局构造、销毁函数
    template <typename T>
    void allocator<T>::construct(T *ptr) {
        mystl::construct(ptr);
    }

    template <typename T>
    void allocator<T>::construct(T *ptr, const T &value) {
        mystl::construct(ptr, value);
    }

    template <typename T>
    void allocator<T>::construct(T *ptr, T &&value) {  // 右值引用， 移动语义
        mystl::construct(ptr, mystl::move(value));
    }

    template <typename T>
    template <typename... Args>
    void allocator<T>::construct(T *ptr, Args&& ...args) {  // 完美转发
        mystl::construct(ptr, mystl::forward<Args>(args)...);
    }

    template <typename T>
    void allocator<T>::destroy(T *ptr) {
        mystl::destroy(ptr);
    }

    template <typename T>
    void allocator<T>::destroy(T *first, T *last) {
        mystl::destroy(first, last);
    }
} // namespace mystl
#endif //TINYSTL_ALLOCATOR_H
