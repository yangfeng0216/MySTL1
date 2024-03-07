#ifndef TINYSTL_CONSTRUCT_H
#define TINYSTL_CONSTRUCT_H

// 这个头文件包含两个函数 construct， destroy
// construct: 负责构造对象
// destroy: 负责析构对象

#include <new>
#include "type_traits.h"
#include "util.h"
#include "iterator.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4100)  // unused parameter
#endif // _MSC_VER

namespace mystl {
    // construct: 全局函数，构造对象
    template <typename Ty>
    void construct(Ty *ptr) {  // ptr指向已经分配好的内存空间
        ::new ((void *)ptr) Ty();  // placement new，使用TY的默认构造函数
    }

    template <typename Ty1, typename Ty2>
    void construct(Ty1 *ptr, const Ty2 &value) {
        ::new ((void *)ptr) Ty1(value);  // placement new, 调用 Ty1::Ty1(value)
    }

    template <typename Ty, typename ... Args>  // 可变长参数列表
    void construct(Ty *ptr, Args&& ...args) {
        ::new ((void *)ptr) Ty(mystl::forward<Args>(args)...);  // 完美转发
    }

    // destroy
    template <typename Ty>
    void destroy_one(Ty *, std::true_type) {}  // 使用默认析构函数，无额外操作

    template <typename Ty>
    void destroy_one(Ty *pointer, std::false_type) {  // 调用自己设计的析构函数
        if (pointer != nullptr) {
            pointer->~Ty();
        }
    }

    template <typename ForwardIter>
    void destroy_cat(ForwardIter , ForwardIter , std::true_type) {}

    template <typename Ty>
    void destroy(Ty *pointer) {
        destroy_one(pointer, std::is_trivially_destructible<Ty>{});
    }

    template <typename ForwardIter>
    void destroy_cat(ForwardIter first, ForwardIter last, std::false_type) {
        for (; first != last; ++first) {
            destroy(& *first);  // 回调destroy(Ty *pointer)
        }
    }

    template <typename ForwardIter>
    void destroy(ForwardIter first, ForwardIter last) {
        destroy_cat(first, last, std::is_trivially_destructible<
            typename iterator_traits<ForwardIter>::value_type>{});
    }
}  // namespace mystl

#ifdef _MSC_VER
#pragma warning(pop)
#endif // _MSC_VER

#endif //TINYSTL_CONSTRUCT_H
