#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include "deque.h"

void test_deque_01() {
    std::cout << "test deque_buf_size" << std::endl;
    std::cout << "value: " << mystl::deque_buf_size<int>::value << std::endl;

    std::cout << "test iterator" << std::endl;
    auto iter = mystl::deque_iterator<int, int&, int*>();
    std::cout << "type of cur: "    << typeid(iter.cur).name()   << std::endl;
    std::cout << "type of first: "  << typeid(iter.first).name() << std::endl;
    std::cout << "type of last: "   << typeid(iter.last).name()  << std::endl;
    std::cout << "type of node: "   << typeid(iter.node).name()  << std::endl;

    std::cout << "test deque" << std::endl;
    std::cout << "test deque constructor" << std::endl;
    mystl::deque<int> deq1;
    deq1.push_back(10);
    std::cout << "deq1.size(): " << deq1.size() << std::endl;
    mystl::deque<int> deq2(100);
    std::cout << "deq2.size(): " << deq2.size() << std::endl;
    mystl::deque<int> deq3(20, 10);
    std::cout << "deq3.size(): " << deq3.size() << std::endl;
    mystl::vector<int> vec1{1, 2, 3, 4, 5, 6, 7, 8, 9};
    mystl::deque<int> deq4(vec1.begin(), vec1.end());
    std::cout << "deq4.size(): " << deq4.size() << std::endl;
    mystl::deque<int> deq5{1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::cout << "deq5.size(): " << deq5.size() << std::endl;
    mystl::deque<int> deq6(deq5);
    std::cout << "deq6.size(): " << deq6.size() << std::endl;
    mystl::deque<int> deq7(std::move(deq5));
    auto printVal = [](const int &val) {
        std::cout << val << " ";
    };
    mystl::for_each(deq7.begin(),deq7.end(), printVal);
    std::cout << std::endl;
    std::cout << "deq7.size(): " << deq7.size() << std::endl;
    mystl::deque<int> deq8;
    deq8 = deq7;
    std::cout << "deq8.size(): " << deq8.size() << std::endl;
    mystl::deque<int> deq9;
    deq9 = std::move(deq6);
    std::cout << "deq9.size(): " << deq9.size() << std::endl;
    mystl::deque<int> deq10;
    deq10 = {2, 3, 4, 5, 6, 7, 8, 9};
    std::cout << "deq10.size(): " << deq10.size() << std::endl;
}

void test_deque_02() {
    std::cout << "iterator related work. " << std::endl;
    mystl::deque<int> deq1 = {1, 2 ,3 ,4 ,5, 6, 7, 8, 9, 0};
    std::cout << "begin_: " << *deq1.begin() << std::endl;
    std::cout << "end_: "   << *deq1.end()   << std::endl;
    std::cout << "is_empty:" << deq1.empty() << std::endl;
    std::cout << "size:"     << deq1.size()  << std::endl;
    std::cout << "max_size:" << deq1.max_size()  << std::endl;
    deq1.resize(5);
    std::cout << "after resize:" << deq1.size()  << std::endl;
    deq1.resize(10, 10);
    std::cout << "after resize:" << deq1.size()  << std::endl;
    deq1.shrink_to_fit();
    auto printVal = [](const int &val) {
        std::cout << val << " ";
    };
    mystl::for_each(deq1.begin(), deq1.end(), printVal);
    std::cout << std::endl;
    std::cout << "after shrink_to_fit:" << deq1.size()  << std::endl;
    std::cout << "operator[0]: " << deq1[0]  << std::endl;
    std::cout << "operator[9]: " << deq1[9]  << std::endl;
    std::cout << "at(0): " << deq1.at(0)  << std::endl;
    std::cout << "at(9): " << deq1.at(9)   << std::endl;
    std::cout << "front(): " << deq1.front()  << std::endl;
    std::cout << "back() : " << deq1.back()   << std::endl;
    mystl::vector<int> vec1{0, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    deq1.assign(vec1.begin(), vec1.end());
    mystl::for_each(deq1.begin(), deq1.end(), printVal);
    std::cout << std::endl;
    deq1.assign({3, 4, 5, 6, 7, 8, 9, 10});
    mystl::for_each(deq1.begin(), deq1.end(), printVal);
    std::cout << std::endl;

    deq1.emplace_front(10);
    deq1.emplace_back(-1);
    deq1.emplace(deq1.begin(), -1);
    deq1.push_front(2);
    deq1.push_back(12);
    mystl::for_each(deq1.begin(), deq1.end(), printVal);
    std::cout << std::endl;
    deq1.pop_front();
    deq1.pop_back();
    mystl::for_each(deq1.begin(), deq1.end(), printVal);
    std::cout << std::endl;

    deq1.insert(deq1.begin(), 100);
    deq1.insert(deq1.end() - 1, 100);
    deq1.insert(deq1.begin(), vec1.begin(), vec1.begin() + 3);
    mystl::for_each(deq1.begin(), deq1.end(), printVal);
    std::cout << std::endl;
    deq1.erase(deq1.begin());
    deq1.erase(deq1.begin(), deq1.begin() + 3);
    mystl::for_each(deq1.begin(), deq1.end(), printVal);
    std::cout << std::endl;
    deq1.clear();
}

void test_deque_03() {
    mystl::deque<int> deq1 = {1, 2, 3, 4, 5};
    mystl::deque<int> deq2 = {5, 4, 3, 2, 1};
    auto printVal = [](const int &val) {
        std::cout << val << " ";
    };
    mystl::for_each(deq1.begin(), deq1.end(), printVal);
    std::cout << std::endl;
    mystl::for_each(deq2.begin(), deq2.end(), printVal);
    std::cout << std::endl;
    swap(deq1, deq2);
    std::cout << "after swap" << std::endl;
    mystl::for_each(deq1.begin(), deq1.end(), printVal);
    std::cout << std::endl;
    mystl::for_each(deq2.begin(), deq2.end(), printVal);
    std::cout << std::endl;

    std::cout << "deq1 == deq2? " << (deq1 == deq2) << std::endl;
    std::cout << "deq1 <= deq2? " << (deq1 <= deq2) << std::endl;
    std::cout << "deq1 >= deq2? " << (deq1 >= deq2) << std::endl;
    std::cout << "deq1 != deq2? " << (deq1 != deq2) << std::endl;
    std::cout << "deq1 >  deq2? " << (deq1 <  deq2) << std::endl;
    std::cout << "deq1 <  deq2? " << (deq1 >  deq2) << std::endl;
}