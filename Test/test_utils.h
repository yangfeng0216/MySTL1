#include <iostream>
#include <string>
#include <windows.h>
#include <ctime>
#include <typeinfo>
#include "vector.h"
#include "util.h"
#include "memory.h"
#include "allocator.h"


int gettimeofday(struct timeval *tp) {
    time_t clock;
    struct tm tm1;
    SYSTEMTIME wtm;
    GetLocalTime(&wtm);
    tm1.tm_year = wtm.wYear - 1900;
    tm1.tm_mon = wtm.wMonth - 1;
    tm1.tm_mday = wtm.wDay;
    tm1.tm_hour = wtm.wHour;
    tm1.tm_min = wtm.wMinute;
    tm1.tm_sec = wtm.wSecond;
    tm1. tm_isdst = -1;
    clock = mktime(&tm1);
    tp->tv_sec = clock;
    tp->tv_usec = wtm.wMilliseconds * 1000;
    return (0);
}

void test_util_01() {
    std::cout << "test memory.h" << std::endl;
    std::cout << "test address_of" << std::endl;
    int num = 10;
    std::cout << "address_of a: " << mystl::address_of(num) << std::endl;
    int &numRef = num;
    std::cout << "address_of a'reference: " << mystl::address_of(numRef) << std::endl;
    mystl::vector<int> vec1(10, 0);
    std::cout << "address_of vec1: " << mystl::address_of(vec1) << std::endl;

    std::cout << "test get_temporary" << std::endl;
    auto tmp = mystl::get_temporary_buffer<int>(10);
    std::cout << "type of tmp: " << typeid(tmp).name() << std::endl;
    std::cout << "tmp: " << tmp.first << " " << tmp.second << std::endl;
    std::cout << "release tmp：" << std::endl;
    mystl::release_temporary_buffer(tmp.first);
    auto tmp1 = mystl::get_temporary_buffer(20, &num);
    std::cout << "type of tmp1: " << typeid(tmp1).name() << std::endl;
    std::cout << "tmp1: " << tmp1.first << " " << tmp1.second << std::endl;
    std::cout << "release tmp1：" << std::endl;
    mystl::release_temporary_buffer(tmp1.first);

    // 会产生警告，tmpBuf may be used uninitialized in this function
    // std::cout << "test temporary_buffer" << std::endl;
    // mystl::vector<int> vec2(50, 0);
    // mystl::temporary_buffer<mystl::vector<int>::iterator ,int> tmpBuf(vec2.begin(), vec2.end());
    //
    // std::cout << "size: " << tmpBuf.size() << std::endl;
    // std::cout << "equested_size: " << tmpBuf.requested_size() << std::endl;
    // std::cout << "address begin: " << tmpBuf.begin() << std::endl;
}

void test_util_02() {
    std::cout << "test memory.h" << std::endl;
    std::cout << "m_bool_constant<true>::value: "   << mystl::m_bool_constant<true>::value  << std::endl;
    std::cout << "m_bool_constant<false>::value: "  << mystl::m_bool_constant<false>::value << std::endl;
    std::cout << "test is_pair" << std::endl;
    std::cout << "int is_pair>? "           << mystl::is_pair<int>::value << std::endl;
    auto myPair = mystl::pair<std::string, int>();
    std::cout << "pair<std::string, int> is_pair? "   << mystl::is_pair<decltype(myPair)>::value << std::endl;
}

void test_util_03() {
    std::cout << "test uninitialized.h" << std::endl;
    std::cout << "test uninitialized_copy" << std::endl;
    mystl::vector<int> vec1(100, 10);
    auto start = mystl::allocator<int>::allocate(100);
    std::cout << "申请空间返回的值类型：" << typeid(start).name() << std::endl;
    mystl::uninitialized_copy(vec1.begin(), vec1.end(), start);
    std::cout << "调用之后start处的值： " << *start << std::endl;
    int count = 0;
    for (int i = 0; i < 100; ++i) {
        ++count;
        std::cout << *(start + i) << " ";
    }
    std::cout << "count = " << count << std::endl;

    std::cout << "test uninitialized_copy_n" << std::endl;
    mystl::vector<int> vec2(50, 20);
    auto start2 = mystl::allocator<int>::allocate(50);
    std::cout << "申请空间返回的值类型：" << typeid(start2).name() << std::endl;
    int n = mystl::distance(vec2.begin(), vec2.end());
    mystl::uninitialized_copy_n(vec2.begin(), n, start2);
    std::cout << "调用之后start处的值： " << *start2 << std::endl;
    int count2 = 0;
    for (int i = 0; i < 50; ++i) {
        ++count2;
        std::cout << *(start2 + i) << " ";
    }
    std::cout << "count = " << count2 << std::endl;

    std::cout << "test uninitialized_fill" << std::endl;
    auto start3 = mystl::allocator<int>::allocate(70);
    std::cout << "申请空间返回的值类型：" << typeid(start3).name() << std::endl;
    mystl::uninitialized_fill(start3, start3 + 70, 70);
    std::cout << "调用之后start处的值： " << *start3 << std::endl;
    int count3 = 0;
    for (int i = 0; i < 70; ++i) {
        ++count3;
        std::cout << *(start3 + i) << " ";
    }
    std::cout << "count = " << count3 << std::endl;

    std::cout << "test uninitialized_fill_n" << std::endl;
    auto start4 = mystl::allocator<int>::allocate(60);
    std::cout << "申请空间返回的值类型：" << typeid(start4).name() << std::endl;
    auto res4 = mystl::uninitialized_fill_n(start4, 60, 70);
    std::cout << "调用之后start处的值： " << *start4 << std::endl;
    int count4 = 0;
    for (auto beg = start4; beg < res4; ++beg) {
        ++count4;
        std::cout << *beg << " ";
    }
    std::cout << "count = " << count4 << std::endl;

    std::cout << "test uninitialized_move" << std::endl;
    mystl::vector<int> vec5(30, 30);
    auto start5 = mystl::allocator<int>::allocate(30);
    std::cout << "申请空间返回的值类型：" << typeid(start4).name() << std::endl;
    mystl::uninitialized_move(vec5.begin(), vec5.end(), start5);
    std::cout << "调用之后start处的值： " << *start4 << std::endl;
    int count5 = 0;
    for (int i = 0; i < 30; ++i) {
        ++count5;
        std::cout << *(start5 + i) << " ";
    }
    std::cout << "count = " << count4 << std::endl;
    for (int i = 0; i < 30; ++i) {
        std::cout << vec5[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "test uninitialized_move_n" << std::endl;
    mystl::vector<int> vec6(45, 45);
    auto start6 = mystl::allocator<int>::allocate(45);
    std::cout << "申请空间返回的值类型：" << typeid(start6).name() << std::endl;
    auto res6 = mystl::uninitialized_move_n(vec6.begin(), (vec6.end() - vec6.begin()), start6);
    std::cout << "调用之后start处的值： " << *start6 << std::endl;
    int count6 = 0;
    for (auto beg = start6; beg < res6; ++beg) {
        ++count6;
        std::cout << *beg << " ";
    }
    std::cout << "count = " << count6 << std::endl;
}

void test_util_04() {
    std::cout << "test util.h" << std::endl;
    std::cout << "move 功能测试..." << std::endl;
    int num1 = 10, num2;
    std::cout << "直接将 num1 赋值给 num2:          " << std::endl;
    num2 = num1;
    std::cout << "num1: " << num1 << " num2: " << num2 << std::endl;

    int num3 = 10, num4;
    std::cout << "使用move将 num3 赋值给 num4:          " << std::endl;
    num4 = mystl::move(num3);
    std::cout << "num3: " << num3 << " num4: " << num4 << std::endl;

    mystl::vector<int> vec1{10, 10, 5, 5, 6, 6}, vec2;
    std::cout << "直接将 vec1 赋值给 vec2:          " << std::endl;
    vec2 = vec1;
    std::cout << "vec1.size(): " << vec1.size() << " vec2.size(): " << vec2.size() << std::endl;

    mystl::vector<int> vec3{10, 10, 5, 5, 6, 6}, vec4;
    std::cout << "使用move将 vec3 赋值给 vec4:          " << std::endl;
    vec4 = mystl::move(vec3);
    std::cout << "vec3.size(): " << vec3.size() << " vec4.size(): " << vec4.size() << std::endl;

    std::string st1 = "test1", st2;
    std::cout << "直接将 st1 赋值给 st2:          " << std::endl;
    st2 = st1;
    std::cout << "st1: " << st1 << " st2: " << st2 << std::endl;

    std::string st3 = "test3", st4;
    std::cout << "使用 std::move 将st3移动到st4:  " << std::endl;
    st4 = std::move(st3);
    std::cout << "st3: " << st3 << " st4: " << st4 << std::endl;

    std::string st5 = "test3", st6;
    std::cout << "使用 mystl::move 将st3移动到st4:" << std::endl;
    st6 = mystl::move(st5);
    std::cout << "st5: " << st5 << " st6: " << st6 << std::endl;
}

void test_util_05() {
    std::cout << "move 性能测试..." << std::endl;
    const int kRunTime = 1000 * 1000;     // 循环次数
    const int kStringLength = 100000;   // 字符串长度
    std::string str;
    std::string copy_str, std_move_str, mystl_move;

    for(int i = 0; i < kStringLength; ++i)
        str += 'a';

    timeval start, end;
    gettimeofday(&start);
    for (int i = 0; i < kRunTime; ++i) {
        copy_str = str;
//        str = copy_str;
    }
    gettimeofday(&end);
    std::cout << "copy string, time: " << (end.tv_sec - start.tv_sec) * 1000
        << (end.tv_usec-start.tv_usec) / 1000 << "ms" << std::endl;

    gettimeofday(&start);
    for (int i = 0; i < kRunTime; ++i) {
        std_move_str = std::move(str);
        str = std::move(std_move_str);
    }
    gettimeofday(&end);
    std::cout << "std move string, time: " << (end.tv_sec - start.tv_sec) * 1000
              << (end.tv_usec-start.tv_usec) / 1000 << "ms" << std::endl;

    gettimeofday(&start);
    for (int i = 0; i < kRunTime; ++i) {
        std_move_str = mystl::move(str);
        str = mystl::move(std_move_str);
    }
    gettimeofday(&end);
    std::cout << "std move string, time: " << (end.tv_sec - start.tv_sec) * 1000
              << (end.tv_usec-start.tv_usec) / 1000 << "ms" << std::endl;
}

// function with lvalue and rvalue reference overloads:
void overloaded(const int &x) {
    std::cout << "[lvalue]: " << x << std::endl;
}

void overloaded(int &&x) {
    std::cout << "[rvalue]: " << x << std::endl;
}

template <class T> void fn(T &&x) {
    overloaded (x);                   // always an lvalue
    overloaded (std::forward<T>(x));  // rvalue if argument is rvalue
}

template <class T> void fn1(T &&x) {
    overloaded (x);                         // always an lvalue
    overloaded (mystl::forward<T>(x));   // rvalue if argument is rvalue
}

void test_util_06() {
    std::cout << "forward 功能测试..." << std::endl;
    int a = 10;
    std::cout << "左值a" << std::endl;
    fn(a);
    fn1(a);
    std::cout << "右值0" << std::endl;
    fn(0);
    fn1(0);
}

void test_util_07() {
    std::cout << "swap 函数测试...  " << std::endl;
    int a = 10, b = 20;
    std::cout << "使用std::swap()之前，a: " << a << " b: " << b << std::endl;
    std::swap(a, b);
    std::cout << "使用std::swap()之后，a: " << a << " b: " << b << std::endl;

    std::cout << "使用mystl::swap()之前，a: " << a << " b: " << b << std::endl;
    mystl::swap(a, b);
    std::cout << "使用mystl::swap()之后，a: " << a << " b: " << b << std::endl;

    std::string st1 = "test1.", st2 = "test2";
    std::cout << "使用std::swap()之前，st1: " << st1 << " st2: " << st2 << std::endl;
    std::swap(st1, st2);
    std::cout << "使用std::swap()之后，st1: " << st1 << " st2: " << st2 << std::endl;

    std::cout << "使用mystl::swap()之前，st1: " << st1 << " st2: " << st2 << std::endl;
    mystl::swap(st1, st2);
    std::cout << "使用mystl::swap()之后，st1: " << st1 << " st2: " << st2 << std::endl;
}

void test_util_08() {
    // pair 初始化测试
    std::pair<int, int> p1;
    std::cout << "p1.first: " << p1.first << " p1.second: " << p1.second << std::endl;
    std::pair<int, int> p2(10, 20);
    std::cout << "p2.first: " << p2.first << " p2.second: " << p2.second << std::endl;
    std::pair<std::string, std::string> p3;
    std::cout << "p3.first: " << p3.first << " p3.second: " << p3.second << std::endl;
    std::pair<std::string, std::string> p4("abc", "def");
    std::cout << "p4.first: " << p4.first << " p4.second: " << p4.second << std::endl;
    std::pair<int, std::string> p5;
    std::cout << "p5.first: " << p5.first << " p5.second: " << p5.second << std::endl;
    std::pair<std::string, int> p6("xyz", 30);
    std::cout << "p6.first: " << p6.first << " p6.second: " << p6.second << std::endl;

    mystl::pair<int, int> my_p1;
    std::cout << "my_p1.first: " << my_p1.first << " my_p1.second: " << my_p1.second << std::endl;
    mystl::pair<int, int> my_p2(10, 20);
    std::cout << "my_p2.first: " << my_p2.first << " my_p2.second: " << my_p2.second << std::endl;
    mystl::pair<std::string, std::string> my_p3;
    std::cout << "my_p3.first: " << my_p3.first << " my_p3.second: " << my_p3.second << std::endl;
    mystl::pair<std::string, std::string> my_p4("abc", "def");
    std::cout << "my_p4.first: " << my_p4.first << " my_p4.second: " << my_p4.second << std::endl;
    mystl::pair<int, std::string> my_p5;
    std::cout << "my_p5.first: " << my_p5.first << " my_p5.second: " << my_p5.second << std::endl;
    mystl::pair<std::string, int> my_p6("xyz", 30);
    std::cout << "my_p6.first: " << my_p6.first << " my_p6.second: " << my_p6.second << std::endl;

    // test operator
    auto p7 = std::make_pair(50, 60);
    auto my_p7 = mystl::make_pair(50, 70);
    std::cout << "p1 == p7: " << (p1 == p7) << std::endl;
    std::cout << "my_p1 == my_p7: " << (my_p1 == my_p7) << std::endl;
    auto p8 = p2;
    auto my_p8 = my_p2;
    std::cout << "befor swap p7: " << p7.first << "p8: " << p8.first << std::endl;
    std::swap(p7, p8);
    std::cout << "after swap p7: " << p7.first << "p8: " << p8.first << std::endl;

    std::cout << "befor swap my_p7: " << my_p7.first << "my_p8: " << my_p8.first << std::endl;
    mystl::swap(my_p7, my_p8);
    std::cout << "after swap my_p7: " << my_p7.first << "my_p8: " << my_p8.first << std::endl;
}
