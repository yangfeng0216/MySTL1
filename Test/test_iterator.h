#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include "iterator.h"

struct iterInput0 :public mystl::iterator<mystl::input_iterator_tag, int> {};
struct iterInput1 :public mystl::iterator<mystl::input_iterator_tag, std::string> {};

struct iterImpl0 :public mystl::iterator_traits<int> {};
struct iterImpl1 :public mystl::iterator_traits<std::string> {};
struct iterImpl2 :public mystl::iterator_traits<iterInput0> {};
struct iterImpl3 :public mystl::iterator_traits<int*> {};
struct iterImpl4 :public mystl::iterator_traits<std::string*> {};
struct iterImpl5 :public mystl::iterator_traits<const int*> {};
struct iterImpl6 :public mystl::iterator_traits<const std::string*> {};

struct iterForward0 :public mystl::iterator<mystl::forward_iterator_tag, int> {};
struct iterForward1 :public mystl::iterator<mystl::forward_iterator_tag, std::string> {};

struct iterRandom0 :public mystl::iterator<mystl::random_access_iterator_tag, int> {};
struct iterRandom1 :public mystl::iterator<mystl::random_access_iterator_tag, std::string> {};

void test_iterator_01() {
    std::cout << "测试iterator: " << std::endl;
    std::cout << "type id of iterator_category: "   << typeid(iterInput0::iterator_category).name()     << std::endl;
    std::cout << "type id of value_type: "          << typeid(iterInput0::value_type).name()            << std::endl;
    std::cout << "type id of pointer: "             << typeid(iterInput0::pointer).name()               << std::endl;
    std::cout << "type id of reference: "           << typeid(iterInput0::reference).name()             << std::endl;
    std::cout << "type id of difference_type: "     << typeid(iterInput0::difference_type).name()       << std::endl;

    std::cout << "type id of iterator_category: "   << typeid(iterInput1::iterator_category).name()     << std::endl;
    std::cout << "type id of value_type: "          << typeid(iterInput1::value_type).name()            << std::endl;
    std::cout << "type id of pointer: "             << typeid(iterInput1::pointer).name()               << std::endl;
    std::cout << "type id of reference: "           << typeid(iterInput1::reference).name()             << std::endl;
    std::cout << "type id of difference_type: "     << typeid(iterInput1::difference_type).name()       << std::endl;

    std::cout << "测试has_iterator_cat: " << std::endl;
    std::cout << "has_iterator_cat(int): "          << mystl::has_iterator_cat<int>::value          << std::endl;
    std::cout << "has_iterator_cat(iterInput0): "   << mystl::has_iterator_cat<iterInput0>::value   << std::endl;

    std::cout << "测试iterator_traits_impl、iterator_traits_helper、iterator_traits" << std::endl;

    // 编译器报错
    // std::cout << "type id of iterator_category: "   << typeid(iterImpl0::iterator_category).name()     << std::endl;
    // std::cout << "type id of value_type: "          << typeid(iterImpl0::value_type).name()            << std::endl;
    // std::cout << "type id of pointer: "             << typeid(iterImpl0::pointer).name()               << std::endl;
    // std::cout << "type id of reference: "           << typeid(iterImpl0::reference).name()             << std::endl;
    // std::cout << "type id of difference_type: "     << typeid(iterImpl0::difference_type).name()       << std::endl;
    //
    // std::cout << "type id of iterator_category: "   << typeid(iterImpl1::iterator_category).name()     << std::endl;
    // std::cout << "type id of value_type: "          << typeid(iterImpl1::value_type).name()            << std::endl;
    // std::cout << "type id of pointer: "             << typeid(iterImpl1::pointer).name()               << std::endl;
    // std::cout << "type id of reference: "           << typeid(iterImpl1::reference).name()             << std::endl;
    // std::cout << "type id of difference_type: "     << typeid(iterImpl1::difference_type).name()       << std::endl;

    std::cout << "type id of iterator_category: "   << typeid(iterImpl2::iterator_category).name()     << std::endl;
    std::cout << "type id of value_type: "          << typeid(iterImpl2::value_type).name()            << std::endl;
    std::cout << "type id of pointer: "             << typeid(iterImpl2::pointer).name()               << std::endl;
    std::cout << "type id of reference: "           << typeid(iterImpl2::reference).name()             << std::endl;
    std::cout << "type id of difference_type: "     << typeid(iterImpl2::difference_type).name()       << std::endl;

    std::cout << "type id of iterator_category: "   << typeid(iterImpl3::iterator_category).name()     << std::endl;
    std::cout << "type id of value_type: "          << typeid(iterImpl3::value_type).name()            << std::endl;
    std::cout << "type id of pointer: "             << typeid(iterImpl3::pointer).name()               << std::endl;
    std::cout << "type id of reference: "           << typeid(iterImpl3::reference).name()             << std::endl;
    std::cout << "type id of difference_type: "     << typeid(iterImpl3::difference_type).name()       << std::endl;

    std::cout << "type id of iterator_category: "   << typeid(iterImpl4::iterator_category).name()     << std::endl;
    std::cout << "type id of value_type: "          << typeid(iterImpl4::value_type).name()            << std::endl;
    std::cout << "type id of pointer: "             << typeid(iterImpl4::pointer).name()               << std::endl;
    std::cout << "type id of reference: "           << typeid(iterImpl4::reference).name()             << std::endl;
    std::cout << "type id of difference_type: "     << typeid(iterImpl4::difference_type).name()       << std::endl;

    std::cout << "type id of iterator_category: "   << typeid(iterImpl5::iterator_category).name()     << std::endl;
    std::cout << "type id of value_type: "          << typeid(iterImpl5::value_type).name()            << std::endl;
    std::cout << "type id of pointer: "             << typeid(iterImpl5::pointer).name()               << std::endl;
    std::cout << "type id of reference: "           << typeid(iterImpl5::reference).name()             << std::endl;
    std::cout << "type id of difference_type: "     << typeid(iterImpl5::difference_type).name()       << std::endl;

    std::cout << "type id of iterator_category: "   << typeid(iterImpl6::iterator_category).name()     << std::endl;
    std::cout << "type id of value_type: "          << typeid(iterImpl6::value_type).name()            << std::endl;
    std::cout << "type id of pointer: "             << typeid(iterImpl6::pointer).name()               << std::endl;
    std::cout << "type id of reference: "           << typeid(iterImpl6::reference).name()             << std::endl;
    std::cout << "type id of difference_type: "     << typeid(iterImpl6::difference_type).name()       << std::endl;
}

void test_iterator_02() {
    std::cout << "测试has_iterator_cat_of: " << std::endl;

    std::cout << "int is input_iterator_tag: "
            << mystl::has_iterator_cat_of<int, mystl::input_iterator_tag>::value << std::endl;
    std::cout << "iterInput0 is input_iterator_tag: "
              << mystl::has_iterator_cat_of<iterInput0, mystl::input_iterator_tag>::value << std::endl;
    std::cout << "iterInput1 is input_iterator_tag: "
              << mystl::has_iterator_cat_of<iterInput1, mystl::input_iterator_tag>::value << std::endl;

    std::cout << "int is input_iterator_tag: "
              << mystl::is_input_iterator<int>::value << std::endl;
    std::cout << "iterInput0 is input_iterator_tag: "
              << mystl::is_input_iterator<iterInput0>::value << std::endl;
    std::cout << "iterInput1 is input_iterator_tag: "
              << mystl::is_input_iterator<iterInput1>::value << std::endl;
    std::cout << "iterInput0 is forward_iterator_tag: "
              << mystl::is_forward_iterator<iterInput0>::value << std::endl;
    std::cout << "iterInput1 is bidirectional_iterator_tag: "
              << mystl::is_bidirectional_iterator<iterInput1>::value << std::endl;

    std::cout << "测试is_iterator、iterator_category、distance_type、value_type" << std::endl;
    std::cout << "int is_iterator? "        << mystl::is_iterator<int>::value           << std::endl;
    std::cout << "iterInput0 is_iterator? " << mystl::is_iterator<iterInput0>::value    << std::endl;
    std::cout << "iterInput1 is_iterator? " << mystl::is_iterator<iterInput1>::value    << std::endl;

    std::cout << "iterator_category of iterForward0: "
              << typeid(mystl::iterator_category(iterForward0())).name() << std::endl;
    std::cout << "iterator_category of iterForward1: "
              << typeid(mystl::iterator_category(iterForward1())).name() << std::endl;
    std::cout << "iterator_category of iterRandom0: "
              << typeid(mystl::iterator_category(iterRandom0())).name() << std::endl;
    std::cout << "iterator_category of iterRandom1: "
              << typeid(mystl::iterator_category(iterRandom1())).name() << std::endl;

    std::cout << "value_type of iterForward0: "
              << typeid(mystl::value_type(iterForward0())).name() << std::endl;
    std::cout << "value_type of iterForward1: "
              << typeid(mystl::value_type(iterForward1())).name() << std::endl;
    std::cout << "value_type of iterRandom0: "
              << typeid(mystl::value_type(iterRandom0())).name() << std::endl;
    std::cout << "value_type of iterRandom1: "
              << typeid(mystl::value_type(iterRandom1())).name() << std::endl;

    std::cout << "distance_type of iterForward0: "
              << typeid(mystl::distance_type(iterForward0())).name() << std::endl;
    std::cout << "distance_type of iterForward1: "
              << typeid(mystl::distance_type(iterForward1())).name() << std::endl;
    std::cout << "distance_type of iterRandom0: "
              << typeid(mystl::distance_type(iterRandom0())).name() << std::endl;
    std::cout << "distance_type of iterRandom1: "
              << typeid(mystl::distance_type(iterRandom1())).name() << std::endl;
}

void test_iterator_03() {
    std::cout << "尚未测试distance、advance函数，与容器一同测试" << std::endl;
}


