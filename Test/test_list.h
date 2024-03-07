#include <iostream>
#include <string>
#include <typeinfo>
#include "iterator.h"
#include "list.h"
#include "vector.h"


void test_list_01() {
    std::cout << "测试node" << std::endl;
    std::cout << typeid(mystl::node_traits<int>::base_ptr).name() << std::endl;
    std::cout << typeid(mystl::node_traits<int>::node_ptr).name() << std::endl;

    std::cout << typeid(mystl::list_node_base<int>::base_ptr).name() << std::endl;
    std::cout << typeid(mystl::list_node_base<int>::node_ptr).name() << std::endl;
    mystl::list_node_base<int> baseNode;
    std::cout << "baseNode.prev == nullptr? " << (baseNode.prev == nullptr) << std::endl;
    std::cout << "baseNode.next == nullptr? " << (baseNode.next == nullptr) << std::endl;

    std::cout << typeid(mystl::list_node<int>::base_ptr).name() << std::endl;
    std::cout << typeid(mystl::list_node<int>::node_ptr).name() << std::endl;
    mystl::list_node<int> node(10);
    std::cout << "node.val is 10? " << node.value << std::endl;
    std::cout << "node.prev == nullptr? " << (node.prev == nullptr) << std::endl;
    std::cout << "node.next == nullptr? " << (node.next == nullptr) << std::endl;

    std::cout << "测试迭代器" << std::endl;
    mystl::list_iterator<int> iter(&node), iter1(&node);
    std::cout << "iter operator* " << *iter << std::endl;
    std::cout << "iter operator-> " << *(iter.operator->()) << std::endl;
    std::cout << "iter operator== " << (iter == iter1) << std::endl;
    std::cout << "iter operator!= " << (iter != iter1) << std::endl;

    std::cout << "测试list构造函数" << std::endl;
    mystl::list<int> list1;
    std::cout << "list1.size():" << list1.size() << std::endl;

    mystl::list<int> list2(50);
    std::cout << "list2.size():" << list2.size() << std::endl;

    mystl::list<std::string> list3(30, "aa");
    std::cout << "list3.size():" << list3.size() << std::endl;

    mystl::vector<int> vec1{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    mystl::list<int> list4(vec1.begin(), vec1.end());
    std::cout << "list4.size():" << list4.size() << std::endl;

    mystl::list<std::string> list5(list3);
    std::cout << "list5.size():" << list5.size() << std::endl;

    mystl::list<std::string> list6(mystl::move(list3));
    std::cout << "list3.size():" << list3.size() << std::endl;
    std::cout << "list6.size():" << list6.size() << std::endl;

    mystl::list<int> list7;
    list7 = list1;
    std::cout << "list7.size():" << list7.size() << std::endl;

    mystl::list<std::string> list8;
    list8 = mystl::move(list6);
    std::cout << "list8.size():" << list8.size() << std::endl;
    std::cout << "list6.size():" << list6.size() << std::endl;

    mystl::list<int> list9;
    list9 = {1, 2, 3, 5, 6, 7};
    std::cout << "list9.size():" << list9.size() << std::endl;

    std::cout << "iterator relate work" << std::endl;
    std::cout << "list9.begin():" << *list9.begin() << std::endl;
    std::cout << "--list9.end():" << *(--list9.end()) << std::endl;

    std::cout << "size relate work" << std::endl;
    std::cout << "list9.empty():" << list9.empty() << std::endl;
    std::cout << "list9.size():" << list9.size() << std::endl;
    std::cout << "list9.max_size():" << list9.max_size() << std::endl;

    std::cout << "Accessing Element Related Operations" << std::endl;
    std::cout << "list9.front():" << list9.front() << std::endl;
    std::cout << "list9.back():" << list9.back() << std::endl;

    std::cout << "Adjust container related operations" << std::endl;
    std::cout << "list9.assign():" << std::endl;
    list9.assign(10, 1);
    std::cout << "list9.size():" << list9.size() << std::endl;
    std::cout << "list9.front():" << list9.front() << std::endl;
    std::cout << "list9.back():" << list9.back() << std::endl;

    mystl::vector<int> vec2{1, 2, 3, 4 ,5 ,6 ,7 };
    list9.assign(vec2.begin(), vec2.end());
    std::cout << "list9.size():" << list9.size() << std::endl;
    std::cout << "list9.front():" << list9.front() << std::endl;
    std::cout << "list9.back():" << list9.back() << std::endl;

    list9.assign({0, 1, 2, 3, 4, 5, 6});
    std::cout << "list9.size():" << list9.size() << std::endl;
    std::cout << "list9.front():" << list9.front() << std::endl;
    std::cout << "list9.back():" << list9.back() << std::endl;

    std::cout << "emplace related work. " << std::endl;
    list9.emplace_front(100);
    std::cout << "list9.size():" << list9.size() << std::endl;
    std::cout << "list9.front():" << list9.front() << std::endl;

    list9.emplace_back(99);
    std::cout << "list9.size():" << list9.size() << std::endl;
    std::cout << "list9.back():" << list9.back() << std::endl;

    list9.emplace(list9.begin(), 100);
    std::cout << "list9.size():" << list9.size() << std::endl;
    std::cout << "list9.front():" << list9.front() << std::endl;

    std::cout << "insert related work. " << std::endl;
    list9.insert(list9.begin(), 88);
    std::cout << "list9.size():" << list9.size() << std::endl;
    std::cout << "list9.front():" << list9.front() << std::endl;

    int tmp = 77;
    list9.insert(list9.begin(), tmp);
    std::cout << "list9.size():" << list9.size() << std::endl;
    std::cout << "list9.front():" << list9.front() << std::endl;


    list9.insert(list9.begin(), 10, 34);
    std::cout << "list9.size():" << list9.size() << std::endl;
    std::cout << "list9.front():" << list9.front() << std::endl;

    list9.insert(list9.begin(), vec2.begin(), vec2.end());
    std::cout << "list9.size():" << list9.size() << std::endl;
    std::cout << "list9.front():" << list9.front() << std::endl;

    std::cout << "pop_front / pop_back related work. " << std::endl;
    std::cout << "list9.size():" << list9.size() << std::endl;
    list9.pop_front();
    std::cout << "list9.size():" << list9.size() << std::endl;
    list9.pop_back();
    std::cout << "list9.size():" << list9.size() << std::endl;
    list9.push_front(10);
    std::cout << "list9.size():" << list9.size() << std::endl;
    list9.push_front(tmp);
    std::cout << "list9.size():" << list9.size() << std::endl;

    std::cout << "erase、resize " << std::endl;
    list9.erase(list9.begin());
    std::cout << "list9.size():" << list9.size() << std::endl;
    std::cout << "list9.front():" << list9.front() << std::endl;

    list9.erase(list9.begin(), ++list9.begin());
    std::cout << "list9.size():" << list9.size() << std::endl;
    std::cout << "list9.front():" << list9.front() << std::endl;

    list9.clear();
    std::cout << "list9.size():" << list9.size() << std::endl;

    list9.resize(10);
    list9.resize(10, 23);
    std::cout << "list9.size():" << list9.size() << std::endl;
    std::cout << "list9.front():" << list9.front() << std::endl;

    std::cout << "splice related work. " << std::endl;
    list7= {1, 2, 3, 5, 6, 7};
    list9.splice(list9.begin(), list7);
    std::cout << "list9.size():" << list9.size() << std::endl;
    std::cout << "list9.front():" << list9.front() << std::endl;

    list7= {1, 2, 3, 5, 6, 7};
    list9.splice(list9.begin(), list7, --list7.end());
    std::cout << "list9.size():" << list9.size() << std::endl;
    std::cout << "list9.front():" << list9.front() << std::endl;

    list7= {1, 2, 3, 5, 6, 7};
    list9.splice(list9.begin(), list7, list7.begin(), list7.end());
    std::cout << "list9.size():" << list9.size() << std::endl;
    std::cout << "list9.front():" << list9.front() << std::endl;

    auto printVal = [](const int &val) {
        std::cout << val << " ";
    };
    mystl::for_each(list9.begin(), list9.end(), printVal);
    std::cout << std::endl;

    auto judge = [](const int &val) -> bool {
        if (val == 0) {
            return true;
        }
        return false;
    };
    list9.remove_if(judge);
    mystl::for_each(list9.begin(), list9.end(), printVal);
    std::cout << std::endl;

    list9.unique();
    mystl::for_each(list9.begin(), list9.end(), printVal);
    std::cout << std::endl;

    list7= {1, 2, 3, 5, 6, 7};
    list9.merge(list7);
    std::cout << "list9.size():" << list9.size() << std::endl;
    std::cout << "list7.size():" << list7.size() << std::endl;
    mystl::for_each(list9.begin(), list9.end(), printVal);
    std::cout << std::endl;

    list9.sort();
    mystl::for_each(list9.begin(), list9.end(), printVal);
    std::cout << std::endl;

    list9.unique();
    mystl::for_each(list9.begin(), list9.end(), printVal);
    std::cout << std::endl;

    list9.reverse();
    mystl::for_each(list9.begin(), list9.end(), printVal);
    std::cout << std::endl;

    list7= {1, 2, 3, 5, 6, 7};
    std::cout << "operator override" << std::endl;
    std::cout << "==: " << (list9 == list7) << std::endl;
    std::cout << "!=: " << (list9 != list7) << std::endl;
    std::cout << "< : " << (list9 <  list7) << std::endl;
    std::cout << "> : " << (list9  > list7) << std::endl;
    std::cout << "<=: " << (list9 <= list7) << std::endl;
    std::cout << ">=: " << (list9 >= list7) << std::endl;

    std::cout << "list9.size():" << list9.size() << std::endl;
    std::cout << "list7.size():" << list7.size() << std::endl;
    std::cout << "swap: " << std::endl;
    swap(list9, list7);
    std::cout << "list9.size():" << list9.size() << std::endl;
    std::cout << "list7.size():" << list7.size() << std::endl;
}