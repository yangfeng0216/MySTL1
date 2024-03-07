#include <iostream>
#include <valarray>
#include "test_utils.h"
#include "test_allocator.h"
#include "test_functional.h"
#include "test_iterator.h"
#include "test_vector.h"
#include "test_algorithm.h"
#include "test_list.h"
#include "test_deque.h"
#include "test_stack.h"
#include "test_queue.h"
#include "test_reverse_iterator.h"
#include "test_hash.h"
#include "test_RBTree.h"

void test_alloc() {
    std::cout << "测试mystl::alloc" << std::endl;
    test_alloc_01();
    test_alloc_02();
}

void test_func() {
    std::cout << "测试mystl::alloc" << std::endl;
    test_functional_00();
    test_functional_01();
    test_functional_02();
    test_functional_03();
    test_functional_04();
    test_functional_05();
}

void test_iter() {
    test_iterator_01();
    test_iterator_02();
    test_iterator_03();
}

void test_vector() {
    test_vector_01();
    test_vector_02();
}

void test_utils() {
    test_util_01();
    test_util_02();
    test_util_03();
    test_util_04();
    test_util_05();
    test_util_06();
    test_util_07();
    test_util_08();
}

void test_algorithm() {
    test_algorithm_01();
    test_algorithm_02();
    test_algorithm_03();
    test_algorithm_04();
    test_algorithm_05();
    test_algorithm_06();
}

void test_list() {
    test_list_01();
}

void test_deque() {
    test_deque_01();
    test_deque_02();
    test_deque_03();
}

void test_stack() {
    test_stack_01();
}

void test_queue() {
    test_queue_01();
    test_pri_queue_01();
    test_pri_queue_02();
}

void test_reverse_iterator() {
    test_reverse_iterator_01();
}

void test_hashtable() {
    // test_hashtable_01();
    // test_hashtable_02();
    // test_hashtable_03();
    // test_hashtable_04();
    // test_hashtable_05();
    // test_hashtable_06();
    test_hashtable_07();
}

int main() {
    std::cout << "main: " << std::endl;
    test_hashtable();
    return 0;
}
