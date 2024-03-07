#ifndef TINYSTL_TYPE_TRAITS_H
#define TINYSTL_TYPE_TRAITS_H

// 用于提取类型信息
#include <type_traits>


namespace mystl {
    // helper struct, 用类来激发模板参数
    template <typename T, T v>
    struct m_integral_constant {
        static constexpr T value = v;  // 静态常数值
    };

    template <bool b>
    using m_bool_constant = m_integral_constant<bool, b>;

    typedef m_bool_constant<true>  m_true_type;
    typedef m_bool_constant<false> m_false_type;

    template <typename T1, typename T2>
    struct pair;

    template <typename T>
    struct is_pair :public mystl::m_false_type {};

    template <typename T1, typename T2>
    struct is_pair<mystl::pair<T1, T2>> :public mystl::m_true_type {};
}  // namespace mystl
#endif //TINYSTL_TYPE_TRAITS_H
