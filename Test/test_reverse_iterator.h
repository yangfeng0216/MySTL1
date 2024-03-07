#include <iostream>
#include <vector>
#include <typeinfo>
#include "reverse_iterator.h"

void test_reverse_iterator_01() {
    std::cout << "test reverse iterator: " << std::endl;
    mystl::vector<int> vec1{1, 2, 3, 4 , 5};
    mystl::reverse_iterator<mystl::vector<int>::iterator> revIter1(vec1.begin());
    std::cout << "typeof revIter1: " << typeid(revIter1).name() << std::endl;
    auto vecIter1 = revIter1.base();
    std::cout << "vecIter1.value: " << *vecIter1 << std::endl;
    std::cout << "typeof vecIter1: " << typeid(vecIter1).name() << std::endl;

    std::cout << "test operator" << std::endl;
    // 下面的代码应该会出错，此时的反向迭代器会返回 begin() - 1, 越界
    std::cout << "revIter1.value: " << *revIter1 << std::endl;
    mystl::reverse_iterator<mystl::vector<int>::iterator> revIter2(vec1.end());
    // iter.end() - 1
    std::cout << "revIter2.value: " << *revIter2 << std::endl;
    // 遍历
    for (auto beg = revIter2; beg != revIter1; ++beg) {
        std::cout << *beg << " ";
    }
    std::cout << std::endl;

    std::cout << "test + : " << *(revIter2 +  2) << std::endl;
    std::cout << "test - : " << *(revIter1 -  1) << std::endl;
    std::cout << "test +=: " << *(revIter2 += 2) << std::endl;
    std::cout << "test -=: " << *(revIter1 -= 1) << std::endl;
    std::cout << "test []: " << revIter2[2]      << std::endl;
    std::cout << "revIter2 - revIter1: " << (revIter2 - revIter1) << std::endl;

    std::cout << "compare operator: " << std::endl;
    std::cout << "revIter1 == revIter2: " << (revIter1 == revIter2) << std::endl;
    std::cout << "revIter1 != revIter2: " << (revIter1 != revIter2) << std::endl;
    std::cout << "revIter1 <= revIter2: " << (revIter1 <= revIter2) << std::endl;
    std::cout << "revIter1 >= revIter2: " << (revIter1 >= revIter2) << std::endl;
    std::cout << "revIter1 <  revIter2: " << (revIter1 <  revIter2) << std::endl;
    std::cout << "revIter1 >  revIter2: " << (revIter1 >  revIter2) << std::endl;
}