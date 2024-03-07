#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include "functional.h"

void comp(int a,int b){
    std::cout << a << " " << b << std::endl;
}

template <typename T, typename BinaryOperator>
void testFun(const T &a, const T &b, BinaryOperator comp) {
    comp(a, b);
}

template <typename T>
class Compare {
public:
    void operator()(const T &a, const T &b) {
        std::cout << a << " " << b << std::endl;
    }
};

void test_functional_00() {
    std::cout << "测试Compare comp： " << std::endl;
    // TODO: 为什么可以传入函数！
    std::cout << "传入函数：" << std::endl;
    testFun(10, 20, comp);
    std::cout << "传入仿函数: " << std::endl;
    testFun(10, 20, Compare<int>());
}

void test_functional_01() {
    std::cout << "测试算术类函数对象： " << std::endl;
    auto resIntSum = mystl::plus<int>()(10, 20);
    std::cout << "sum: 10 + 20 = " << resIntSum << std::endl;
    std::cout << "type of resIntSum is: " << typeid(resIntSum).name()  << std::endl;

    auto resStrSum = mystl::plus<std::string>()("aaa", "bbb");
    std::cout << "sum: aaa + bbb = " << resStrSum << std::endl;
    std::cout << "type of resStrSum is: " << typeid(resStrSum).name()  << std::endl;

    auto resIntMinus = mystl::minus<int>()(10, 20);
    std::cout << "minus: 10 - 20 = " << resIntMinus << std::endl;
    std::cout << "type of res is: " << typeid(resIntMinus).name()  << std::endl;

    auto resIntMul = mystl::multiplies<int>()(10, 20);
    std::cout << "multiplies: 10 * 20 = " << resIntMul << std::endl;
    std::cout << "type of res is: " << typeid(resIntMul).name()  << std::endl;


    auto resIntDiv = mystl::divides<int>()(10, 20);
    std::cout << "div: 10 / 20 = " << resIntDiv << std::endl;
    std::cout << "type of res is: " << typeid(resIntDiv).name()  << std::endl;

    auto resIntMod = mystl::modulus<int>()(10, 20);
    std::cout << "Mod: 10 % 20 = " << resIntMod << std::endl;
    std::cout << "type of resIntSum is: " << typeid(resIntMod).name()  << std::endl;

    auto resIntNeg = mystl::negate<int>()(10);
    std::cout << "neg: 10 = " << resIntNeg << std::endl;
    std::cout << "type of res is: " << typeid(resIntNeg).name()  << std::endl;

    auto idenPlus = identity_element(mystl::plus<int>());
    std::cout << "加法证同元素： " << idenPlus << std::endl;

    auto idenMul = identity_element(mystl::multiplies<int>());
    std::cout << "乘法证同元素： " << idenMul << std::endl;
}

void test_functional_02() {
    std::cout << "测试关系类函数对象： " << std::endl;

    std::cout << "10 > 20: " << mystl::greater<int>()(10, 20) << std::endl;
    std::cout << "30 > 20: " << mystl::greater<int>()(30, 20) << std::endl;

    std::cout << "10 < 20: " << mystl::less<int>()(10, 20) << std::endl;
    std::cout << "30 < 20: " << mystl::less<int>()(30, 20) << std::endl;

    std::cout << "10 >= 20: " << mystl::greater_equal<int>()(10, 20) << std::endl;
    std::cout << "20 >= 20: " << mystl::greater_equal<int>()(20, 20) << std::endl;

    std::cout << "10 <= 20: " << mystl::less_equal<int>()(10, 20) << std::endl;
    std::cout << "20 <= 20: " << mystl::less_equal<int>()(20, 20) << std::endl;
}

void test_functional_03() {
    std::cout << "测试逻辑运算类函数对象： " << std::endl;

    std::cout << "true && true = " << mystl::logical_and<bool>()(true, true) << std::endl;
    std::cout << "true && false = " << mystl::logical_and<bool>()(true, false) << std::endl;
    std::cout << "false && false = " << mystl::logical_and<bool>()(false, false) << std::endl;

    std::cout << "true || true = " << mystl::logical_or<bool>()(true, true) << std::endl;
    std::cout << "true || false = " << mystl::logical_or<bool>()(true, false) << std::endl;
    std::cout << "false || false = " << mystl::logical_or<bool>()(false, false) << std::endl;

    std::cout << "! true = " << mystl::logical_not<bool>()(true) << std::endl;
    std::cout << "！false = " << mystl::logical_not<bool>()(false) << std::endl;
}

void test_functional_04() {
    std::cout << "测试正同、选择、投射 函数对象： " << std::endl;

    std::cout << "int 100 正同：" << mystl::identity<int>()(100) << std::endl;
    std::cout << "string test 正同：" << mystl::identity<std::string>()("test") << std::endl;

    auto pair1 = mystl::pair<int, std::string>(10, "test");
    std::cout << "pair<10, test> first: " << mystl::selectfirst<mystl::pair<int, std::string>>()(pair1) << std::endl;
    std::cout << "pair<10, test> second: " << mystl::selectsecond<mystl::pair<int, std::string>>()(pair1) << std::endl;

    std::cout << "10, test 第一参数: " << mystl::projectfirst<int, std::string>()(10, "test") << std::endl;
    std::cout << "10, test 第二参数: " << mystl::projectsecond<int, std::string>()(10, "test") << std::endl;
}

void test_functional_05() {
    std::cout << "测试hash_func： " << std::endl;

    int *p = new int(10);
    std::cout << "int指针: " << mystl::hash<int *>()(p) << std::endl;

    std::cout << "int 10: " << mystl::hash<int>()(10) << std::endl;
    std::cout << "bool false: " << mystl::hash<bool>()(false) << std::endl;

    std::cout << "float 10.01: " << mystl::hash<float>()(10.01) << std::endl;
    std::cout << "float 10.01 again: " << mystl::hash<float>()(10.01) << std::endl;
    std::cout << "double 10.0203: " << mystl::hash<double>()(10.0203) << std::endl;
    std::cout << "double 10.0203 again: " << mystl::hash<double>()(10.0203) << std::endl;
}