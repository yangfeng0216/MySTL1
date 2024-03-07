#include <iostream>
#include <vector>
#include <typeinfo>
#include "stack.h"

void test_stack_01() {
    std::cout << "test stack: " << std::endl;
    mystl::stack<int> st1;
    std::cout << "st1.size(): " << st1.size() << std::endl;
    mystl::stack<int> st2(10);
    std::cout << "st2.size(): " << st2.size() << std::endl;
    mystl::stack<int> st3(5, 1);
    std::cout << "st3.size(): " << st3.size() << std::endl;
    mystl::vector<int> vec1 {1, 2, 3, 4 ,5};
    mystl::stack<int> st4(vec1.begin(), vec1.end());
    std::cout << "st4.size(): " << st4.size() << std::endl;
    mystl::stack<int> st5(st4);
    std::cout << "st5.size(): " << st5.size() << std::endl;
    mystl::stack<int> st6(std::move(st5));
    std::cout << "st5.size(): " << st5.size() << std::endl;
    std::cout << "st6.size(): " << st6.size() << std::endl;

    st1 = st6;
    std::cout << "st1.size(): " << st1.size() << std::endl;
    std::cout << "st6.size(): " << st6.size() << std::endl;
    st6 = {3, 4, 5, 6, 7, 8, 9};
    std::cout << "st6.size(): " << st6.size() << std::endl;
    mystl::stack<int> st7;
    st7 =  mystl::move(st3);
    std::cout << "st7.size(): " << st7.size() << std::endl;
    std::cout << "st3.size(): " << st3.size() << std::endl;

    std::cout << "get elem: " << std::endl;
    std::cout << "st6.size(): " << st6.size() << std::endl;
    std::cout << "st6.top(): " << st6.top() << std::endl;
    std::cout << "st6.empty(): " << st6.empty() << std::endl;
    st6.pop();
    std::cout << "st6.top(): " << st6.top() << std::endl;
    st6.push(10);
    std::cout << "st6.top(): " << st6.top() << std::endl;
    st6.emplace(20);
    std::cout << "st6.top(): " << st6.top() << std::endl;

    std::cout << "override operator: " << std::endl;
    std::cout << "st6 == st7? " << (st6 == st7) << std::endl;
    std::cout << "st6 != st7? " << (st6 != st7) << std::endl;
    std::cout << "st6 <= st7? " << (st6 <= st7) << std::endl;
    std::cout << "st6 >= st7? " << (st6 >= st7) << std::endl;
    std::cout << "st6 <  st7? " << (st6 <  st7) << std::endl;
    std::cout << "st6 >  st7? " << (st6 >  st7) << std::endl;

    mystl::swap(st6, st7);
    std::cout << "after swap(st6, st7): " << std::endl;
    std::cout << "st6 == st7? " << (st6 == st7) << std::endl;
    std::cout << "st6 != st7? " << (st6 != st7) << std::endl;
    std::cout << "st6 <= st7? " << (st6 <= st7) << std::endl;
    std::cout << "st6 >= st7? " << (st6 >= st7) << std::endl;
    std::cout << "st6 <  st7? " << (st6 <  st7) << std::endl;
    std::cout << "st6 >  st7? " << (st6 >  st7) << std::endl;
}