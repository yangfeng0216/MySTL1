#include <iostream>
#include <string>
#include <typeinfo>
#include "iterator.h"
#include "vector.h"


void test_vector_01() {
    std::cout << "测试构造函数: " << std::endl;
    std::cout << "无参构造构造函数: " << std::endl;
    mystl::vector<int> vec1;
    std::cout << "vec1.size: "      << vec1.size()      << std::endl;
    std::cout << "vec1.capacity: "  << vec1.capacity()  << std::endl;

    std::cout << "获取vector萃取类型：" << std::endl;
    std::cout << "typeid of allocator_type: " << typeid(mystl::vector<int>::allocator_type).name() << std::endl;


    std::cout << "测试普通指针能否判断为input_iterator_tag" << std::endl;
    auto beg = vec1.begin();
    auto end = vec1.end();
    std::cout << "typeid of beg: " << typeid(beg).name() << std::endl;
    std::cout << "typeid of end: " << typeid(end).name() << std::endl;
    std::cout << "beg is input_iterator_tag: " << mystl::is_input_iterator<decltype(beg)>::value << std::endl;
    std::cout << "end is input_iterator_tag: " << mystl::is_input_iterator<decltype(end)>::value << std::endl;

    std::cout << "有参构造构造函数: " << std::endl;
    mystl::vector<int> vec2(20);
    std::cout << "vec2.size: "      << vec2.size()      << std::endl;
    std::cout << "vec2.capacity: "  << vec2.capacity()  << std::endl;

    std::cout << "有参构造构造函数: " << std::endl;
    mystl::vector<int> vec3(20, 10);
    std::cout << "vec3.size: "      << vec3.size()      << std::endl;
    std::cout << "vec3.capacity: "  << vec3.capacity()  << std::endl;

    std::cout << "迭代器范围构造函数: " << std::endl;
    mystl::vector<int> vec4(vec3.begin(), vec3.end());
    std::cout << "vec4.size: "      << vec4.size()      << std::endl;
    std::cout << "vec4.capacity: "  << vec4.capacity()  << std::endl;

    std::cout << "拷贝构造函数: " << std::endl;
    mystl::vector<int> vec5(vec4);
    std::cout << "vec5.size: "      << vec5.size()      << std::endl;
    std::cout << "vec5.capacity: "  << vec5.capacity()  << std::endl;

    std::cout << "移动构造函数: " << std::endl;
    mystl::vector<int> vec6(mystl::move(vec5));
    std::cout << "vec6.size: "      << vec6.size()      << std::endl;
    std::cout << "vec6.capacity: "  << vec6.capacity()  << std::endl;
    auto beg5 = vec5.begin();
    auto end5 = vec5.end();
    std::cout << "vec5.begin: "  << beg5 << std::endl;
    std::cout << "vec5.end: "    << end5 << std::endl;

    std::cout << "花括号列表初始化: " << std::endl;
    mystl::vector<int> vec7{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::cout << "vec7.size: "      << vec7.size()      << std::endl;
    std::cout << "vec7.capacity: "  << vec7.capacity()  << std::endl;

    std::cout << "拷贝赋值操作符: " << std::endl;
    mystl::vector<int> vec8;
    vec8 = vec7;
    std::cout << "vec8.size: "      << vec8.size()      << std::endl;
    std::cout << "vec8.capacity: "  << vec8.capacity()  << std::endl;
    std::cout << "vec8.begin address: " << vec8.begin() << std::endl;
    std::cout << "vec8.end address: "   << vec8.end()   << std::endl;

    std::cout << "赋值操作符: " << std::endl;
    mystl::vector<int> vec9;
    vec9 = std::move(vec8);
    std::cout << "vec9.size: "      << vec9.size()      << std::endl;
    std::cout << "vec9.capacity: "  << vec9.capacity()  << std::endl;
    std::cout << "vec9.begin address: " << vec9.begin() << std::endl;
    std::cout << "vec9.end address: "   << vec9.end()   << std::endl;
    std::cout << "vec8.beign: "     << vec8.begin()     << std::endl;
    std::cout << "vec8.end: "       << vec8.end()       << std::endl;

    std::cout << "花括号赋值操作符: " << std::endl;
    mystl::vector<int> vec10;
    vec10 = {1, 3, 5, 7, 9};
    std::cout << "vec10.size: "      << vec10.size()      << std::endl;
    std::cout << "vec10.capacity: "  << vec10.capacity()  << std::endl;

    std::cout << "迭代器相关操作：" << std::endl;
    std::cout << "vec10.begin address: "  << vec10.begin()  << std::endl;
    std::cout << "vec10.end address: "    << vec10.end()    << std::endl;
    // std::cout << "vec10.rbegin address: " << vec10.rbegin() << std::endl;
    // std::cout << "vec10.rend address: "   << vec10.rend()   << std::endl;
    std::cout << "vec10.cbegin address: " << vec10.cbegin() << std::endl;
    std::cout << "vec10.cend address: "   << vec10.cend()   << std::endl;

    std::cout << "容量相关操作：" << std::endl;
    std::cout << "vec10.empty(): "      << vec10.empty()   << std::endl;
    std::cout << "vec10.size(): "       << vec10.size()    << std::endl;
    std::cout << "vec10.max_size(): "   << vec10.max_size()   << std::endl;
    std::cout << "vec10.capacity(): "   << vec10.capacity()   << std::endl;

    std::cout << "after vec10.reserve" << std::endl;
    vec10.reserve(30);
    std::cout << "vec10.empty(): "      << vec10.empty()   << std::endl;
    std::cout << "vec10.size(): "       << vec10.size()    << std::endl;
    std::cout << "vec10.capacity(): "   << vec10.capacity()   << std::endl;

    std::cout << "after vec10.shrink_to_fit" << std::endl;
    vec10.shrink_to_fit();
    std::cout << "vec10.empty(): "      << vec10.empty()   << std::endl;
    std::cout << "vec10.size(): "       << vec10.size()    << std::endl;
    std::cout << "vec10.capacity(): "   << vec10.capacity()   << std::endl;

    std::cout << "访问元素相关：" << std::endl;
    std::cout << "vec10[i]: ";
    for (int i = 0; i < vec10.size(); ++i) {
        std::cout << "vec[" << i << "]: " << vec10[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "vec10.at(i): ";
    for (int i = 0; i < vec10.size(); ++i) {
        std::cout << "vec10.at(" << i << "): " << vec10.at(i) << " ";
    }
    std::cout << std::endl;

    std::cout << "vec10.front(): " << vec10.front() << std::endl;
    std::cout << "vec10.back(): "  << vec10.back()  << std::endl;
    std::cout << "vec10.data(): "  << *vec10.data()  << std::endl;
}

void test_vector_02() {
    mystl::vector<std::string> vec1{"aa", "bb", "cc", "dd"};
    std::cout << "vec1.size: "      << vec1.size()      << std::endl;
    std::cout << "vec1.capacity: "  << vec1.capacity()  << std::endl;

    std::cout << "after assign(10, \"ee\"): " << std::endl;
    vec1.assign(10, "ee");
    std::cout << "vec1.size: "      << vec1.size()      << std::endl;
    std::cout << "vec1.capacity: "  << vec1.capacity()  << std::endl;

    mystl::vector<std::string> vec2{"aa", "bb", "cc", "dd", "aa", "bb", "cc", "dd", "aa", "bb", "cc", "dd",
                                    "cc", "dd", "aa", "bb", "cc", "dd", "cc", "dd", "aa", "bb", "cc", "dd",
                                    "cc", "dd", "aa", "bb", "cc", "dd", "cc", "dd", "aa", "bb", "cc", "dd"};
    std::cout << "after assign(vec2.begin(), vec2.end()): " << std::endl;
    vec1.assign(vec2.begin(), vec2.end());
    std::cout << "vec1.size: "      << vec1.size()      << std::endl;
    std::cout << "vec1.capacity: "  << vec1.capacity()  << std::endl;

    std::initializer_list<std::string> il = {"aa", "bb", "cc", "dd"};
    std::cout << "after assign(il): " << std::endl;
    vec1.assign(il);
    std::cout << "vec1.size: "      << vec1.size()      << std::endl;
    std::cout << "vec1.capacity: "  << vec1.capacity()  << std::endl;

    std::cout << "emplace, push, insert" << std::endl;
    std::cout << "emplce: " << std::endl;
    vec1.emplace(vec1.begin(), "string");
    vec1.emplace_back("string");
    std::cout << "vec1.size: "      << vec1.size()      << std::endl;
    std::cout << "vec1.capacity: "  << vec1.capacity()  << std::endl;

    std::cout << "push: " << std::endl;
    std::string tmp = "str";
    vec1.push_back(tmp);
    vec1.push_back("string");
    std::cout << "vec1.size: "      << vec1.size()      << std::endl;
    std::cout << "vec1.capacity: "  << vec1.capacity()  << std::endl;

    std::cout << "insert: " << std::endl;
    tmp = "str2";
    vec1.insert(vec1.begin(), tmp);
    vec1.insert(vec1.begin(), "string");
    vec1.insert(vec1.begin(), 3, tmp);
    std::cout << "vec1.size: "      << vec1.size()      << std::endl;
    std::cout << "vec1.capacity: "  << vec1.capacity()  << std::endl;

    std::cout << "erase: " << std::endl;
    vec1.erase(vec1.begin());
    vec1.erase(vec1.end() - 1);
    vec1.erase(vec1.begin(), vec1.begin() + 2);
    std::cout << "vec1.size: "      << vec1.size()      << std::endl;
    std::cout << "vec1.capacity: "  << vec1.capacity()  << std::endl;

    std::cout << "resize: " << std::endl;
    vec1.resize(6, "str3");
    std::cout << "vec1.size: "      << vec1.size()      << std::endl;
    std::cout << "vec1.capacity: "  << vec1.capacity()  << std::endl;

    mystl::vector<std::string> vec3 = {"aa", "bb", "cc"};
    std::cout << "vec3.size: "      << vec3.size()      << std::endl;
    std::cout << "vec3.capacity: "  << vec3.capacity()  << std::endl;
    std::cout << "after swap: " << std::endl;
    vec1.swap(vec3);
    std::cout << "vec1.size: "      << vec1.size()      << std::endl;
    std::cout << "vec1.capacity: "  << vec1.capacity()  << std::endl;
    std::cout << "vec3.size: "      << vec3.size()      << std::endl;
    std::cout << "vec3.capacity: "  << vec3.capacity()  << std::endl;

    std::cout << "vec1 == vec3: " << bool(vec1 == vec3) << std::endl;
    std::cout << "vec1 != vec3: " << bool(vec1 != vec3) << std::endl;
    std::cout << "vec1 <= vec3: " << bool(vec1 <= vec3) << std::endl;
    std::cout << "vec1 >= vec3: " << bool(vec1 >= vec3) << std::endl;

    std::cout << "全局函数： swap" << std::endl;
    swap(vec1, vec3);
    std::cout << "vec1.size: "      << vec1.size()      << std::endl;
    std::cout << "vec1.capacity: "  << vec1.capacity()  << std::endl;
    std::cout << "vec3.size: "      << vec3.size()      << std::endl;
    std::cout << "vec3.capacity: "  << vec3.capacity()  << std::endl;
}

