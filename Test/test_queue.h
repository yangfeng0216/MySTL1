#include <iostream>
#include <vector>
#include <typeinfo>
#include "queue.h"

void test_queue_01() {
    std::cout << "test queue: " << std::endl;
    mystl::queue<int> que1;
    std::cout << "que1.size(): " << que1.size() << std::endl;
    mystl::queue<int> que2(10);
    std::cout << "que2.size(): " << que2.size() << std::endl;
    mystl::queue<int> que3(5, 1);
    std::cout << "que3.size(): " << que3.size() << std::endl;
    mystl::vector<int> vec1 {1, 2, 3, 4 ,5};
    mystl::queue<int> que4(vec1.begin(), vec1.end());
    std::cout << "que4.size(): " << que4.size() << std::endl;
    mystl::queue<int> que5(que4);
    std::cout << "que5.size(): " << que5.size() << std::endl;
    mystl::queue<int> que6(std::move(que5));
    std::cout << "que5.size(): " << que5.size() << std::endl;
    std::cout << "que6.size(): " << que6.size() << std::endl;

    que1 = que6;
    std::cout << "que1.size(): " << que1.size() << std::endl;
    std::cout << "que6.size(): " << que6.size() << std::endl;
    que6 = {3, 4, 5, 6, 7, 8, 9};
    std::cout << "que6.size(): " << que6.size() << std::endl;
    mystl::queue<int> que7;
    que7 =  mystl::move(que3);
    std::cout << "que7.size(): " << que7.size() << std::endl;
    std::cout << "que3.size(): " << que3.size() << std::endl;

    std::cout << "get elem: " << std::endl;
    std::cout << "que6.size(): "  << que6.size()  << std::endl;
    std::cout << "que6.front(): " << que6.front() << std::endl;
    std::cout << "que6.back() : " << que6.back()  << std::endl;
    std::cout << "que6.empty(): " << que6.empty() << std::endl;
    que6.pop();
    std::cout << "st6.top(): " << que6.front() << std::endl;
    que6.push(10);
    std::cout << "st6.top(): " << que6.front() << std::endl;
    que6.emplace(20);
    std::cout << "st6.top(): " << que6.front() << std::endl;

    std::cout << "override operator: " << std::endl;
    std::cout << "que6 == que7? " << (que6 == que7) << std::endl;
    std::cout << "que6 != que7? " << (que6 != que7) << std::endl;
    std::cout << "que6 <= que7? " << (que6 <= que7) << std::endl;
    std::cout << "que6 >= que7? " << (que6 >= que7) << std::endl;
    std::cout << "que6  < que7? " << (que6  < que7) << std::endl;
    std::cout << "que6  > que7? " << (que6  > que7) << std::endl;

    mystl::swap(que6, que7);
    std::cout << "after swap(que6, que7): " << std::endl;
    std::cout << "override operator: " << std::endl;
    std::cout << "que6 == que7? " << (que6 == que7) << std::endl;
    std::cout << "que6 != que7? " << (que6 != que7) << std::endl;
    std::cout << "que6 <= que7? " << (que6 <= que7) << std::endl;
    std::cout << "que6 >= que7? " << (que6 >= que7) << std::endl;
    std::cout << "que6  < que7? " << (que6  < que7) << std::endl;
    std::cout << "que6  > que7? " << (que6  > que7) << std::endl;
}

void test_pri_queue_01() {
    std::cout << "test priority_queue: " << std::endl;
    mystl::priority_queue<int> que1;
    std::cout << "que1.size(): " << que1.size() << std::endl;
    mystl::priority_queue<int> que2(10);
    std::cout << "que2.size(): " << que2.size() << std::endl;
    mystl::priority_queue<int> que3(5, 1);
    std::cout << "que3.size(): " << que3.size() << std::endl;
    mystl::vector<int> vec1 {1, 2, 3, 4 ,5};
    mystl::priority_queue<int> que4(vec1.begin(), vec1.end());
    std::cout << "que4.size(): " << que4.size() << std::endl;
    mystl::priority_queue<int> que5(que4);
    std::cout << "que5.size(): " << que5.size() << std::endl;
    mystl::priority_queue<int> que6(std::move(que5));
    std::cout << "que5.size(): " << que5.size() << std::endl;
    std::cout << "que6.size(): " << que6.size() << std::endl;

    que1 = que6;
    std::cout << "que1.size(): " << que1.size() << std::endl;
    std::cout << "que6.size(): " << que6.size() << std::endl;
    que6 = {3, 4, 5, 6, 7, 8, 9};
    std::cout << "st6.size(): " << que6.size() << std::endl;
    mystl::priority_queue<int> que7;
    que7 =  mystl::move(que3);
    std::cout << "que7.size(): " << que7.size() << std::endl;
    std::cout << "que3.size(): " << que3.size() << std::endl;

    mystl::vector<int> vec2 {1, 2, 3, 4 ,5};
    mystl::vector<int> vec3 {1, 2, 3, 4 ,5};
    std::cout << "vec2 == vec3? " << (vec2 == vec3) << std::endl;

    std::cout << "override operator: " << std::endl;
    std::cout << "que6 == que7? " << (que6 == que7) << std::endl;
    std::cout << "que6 != que7? " << (que6 != que7) << std::endl;

    mystl::swap(que6, que7);
    std::cout << "after swap(que6, que7): " << std::endl;
    std::cout << "override operator: " << std::endl;
    std::cout << "que6 == que7? " << (que6 == que7) << std::endl;
    std::cout << "que6 != que7? " << (que6 != que7) << std::endl;

}

void test_pri_queue_02() {
    std::cout << "test priority_queue order: " << std::endl;
    mystl::priority_queue<int> pri1{0, 8, 7, 5, 4, 2, 3, 4, 1};
    std::cout << "pri1.size(): "  << pri1.size()  << std::endl;
    std::cout << "pri1.empty(): " << pri1.empty() << std::endl;
    std::cout << "pri1.top(): "   << pri1.top()   << std::endl;
    int size = pri1.size();
    while (size--) {
        std::cout << pri1.top() << " ";
        pri1.pop();
    }
    std::cout << std::endl;

    for (int i = 0; i < 10; ++i) {
        pri1.push(i);
    }
    size = pri1.size();
    while (size--) {
        std::cout << pri1.top() << " ";
        pri1.pop();
    }
    std::cout << std::endl;
}
