#include <iostream>
#include <vector>
#include "hashtable.h"
#include "unordered_map.h"
#include "unordered_set.h"

void test_hashtable_01() {
    std::cout << "test hash table node: " << std::endl;
    mystl::hashtable_node<int> node1;
    mystl::hashtable_node<int> node2(10);
    mystl::hashtable_node<int> node3(node2);
    mystl::hashtable_node<int> node4(std::move(node3));

    std::cout << "test hash table value traits: " << std::endl;
    std::cout << "get_key："   << mystl::ht_value_traits_imp<int, false>::get_key(100)   << std::endl;
    std::cout << "get_value：" << mystl::ht_value_traits_imp<int, false>::get_value(100) << std::endl;

    mystl::pair<int, int> pair1(10, 100);
    std::cout << "get_key："   << mystl::ht_value_traits_imp<mystl::pair<int, int>, true>::get_key(pair1) << std::endl;
    std::cout << "get_value：" << mystl::ht_value_traits_imp<
            mystl::pair<int, int>, true>::get_value(pair1).second << std::endl;

    std::cout << "get_key："   << mystl::ht_value_traits<int>::get_key(100)   << std::endl;
    std::cout << "get_value：" << mystl::ht_value_traits<int>::get_value(100) << std::endl;
    std::cout << "get_key："   << mystl::ht_value_traits<mystl::pair<int, int>>::get_key(pair1)          << std::endl;
    std::cout << "get_value：" << mystl::ht_value_traits<mystl::pair<int, int>>::get_value(pair1).second << std::endl;
}

void test_hashtable_02() {
    std::cout << "test unrdered_set node: " << std::endl;
    mystl::unordered_set<int> uset1();
    mystl::unordered_set<int> uset2(10);
    mystl::unordered_set<int> uset3(10, mystl::hash<int>(), mystl::equal_to<int>());
    mystl::vector<int> vec1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    mystl::unordered_set<int> uset4(vec1.begin(), vec1.end());
    mystl::unordered_set<int> uset5({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    mystl::unordered_set<int> uset6(uset4);
    mystl::unordered_set<int> uset7(mystl::move(uset6));

    mystl::unordered_set<int> uset8;
    uset8 = uset7;

    mystl::unordered_set<int> uset9;
    uset9 = std::move(uset7);

    mystl::unordered_set<int> uset10;
    uset10 = {1, 2, 3, 4};
}

void test_hashtable_03() {
    mystl::unordered_set<int> uset1{1, 2, 3, 4, 5, 6, 7, 10, 9, 8};
    std::cout << "test capacity: "    << std::endl;
    std::cout << "uset1.size(): "     << uset1.size()  << std::endl;
    std::cout << "uset1.empty(): "    << uset1.empty() << std::endl;
    std::cout << "uset1.max_size(): " << uset1.max_size() << std::endl;

    std::cout << "test iterator: "    << std::endl;
    std::cout << "beign(): "  << *uset1.begin()  << std::endl;
    std::cout << "cbeign(): " << *uset1.cbegin() << std::endl;
    auto printVal = [](const int &val) {
        std::cout << val << " ";
    };
    mystl::for_each(uset1.begin(), uset1.end(), printVal);
    std::cout << std::endl;

    std::cout << "test add / erase: "    << std::endl;
    uset1.emplace(100);
    std::cout << "uset1.size(): "     << uset1.size()  << std::endl;

    uset1.insert(50);
    std::cout << "uset1.size(): "     << uset1.size()  << std::endl;

    mystl::vector<int> vec1{23, 45, 56, 45};
    std::cout << "uset1.size(): "     << uset1.size()  << std::endl;

    uset1.insert(vec1.begin(), vec1.end());
    mystl::for_each(uset1.begin(), uset1.end(), printVal);
    std::cout << std::endl;

    uset1.erase(uset1.begin());
    uset1.erase(10);
    mystl::for_each(uset1.begin(), uset1.end(), printVal);
    std::cout << std::endl;

    std::cout << "test buckket begin" << std::endl;
    std::cout << "test find: " << std::endl;
    std::cout << "uset1.count(0): "     << uset1.count(1)   << std::endl;
    std::cout << "uset1.count(1): "     << uset1.count(2)   << std::endl;
    std::cout << "uset1.count(77): "    << uset1.count(77)  << std::endl;

    mystl::unordered_set<int> uset2{6, 7, 10, 9, 8, 10, 9, 8, 1, 2, 2};
    swap(uset1, uset2);
    std::cout << "after swapuset1 uset2" << std::endl;
    mystl::for_each(uset1.begin(), uset1.end(), printVal);
    std::cout << std::endl;
    std::cout << "uset1.count(2): "     << uset1.count(2)          << std::endl;

    std::cout << "uset1.begin(2): "     << *uset1.begin(2)          << std::endl;
    std::cout << "bucket_count: "       << uset1.bucket_count()        << std::endl;
    std::cout << "max_bucket_count: "   << uset1.max_bucket_count()    << std::endl;
    std::cout << "bucket_size: "        << uset1.bucket_size(1)     << std::endl;
    std::cout << "bucket: "             << uset1.bucket(2)         << std::endl;

    std::cout << "uset1.load_factor: "  << uset1.load_factor()          << std::endl;
    std::cout << "max_load_factor: "    << uset1.max_load_factor()      << std::endl;

    std::cout << "uset1 == uset2: "     << (uset1 == uset2)             << std::endl;
    std::cout << "uset1 != uset2: "     << (uset1 != uset2)             << std::endl;
}

void test_hashtable_04() {
    mystl::unordered_multiset<int> umultiset1{1, 2, 3, 4, 5, 6, 7, 10, 9, 8, 8, 9, 9};
    std::cout << "test capacity: " << std::endl;
    std::cout << "umultiset1.size(): "     << umultiset1.size()  << std::endl;
    std::cout << "umultiset1.empty(): "    << umultiset1.empty() << std::endl;
    std::cout << "umultiset1.max_size(): " << umultiset1.max_size() << std::endl;

    std::cout << "test iterator: " << std::endl;
    std::cout << "beign(): "  << *umultiset1.begin()  << std::endl;
    std::cout << "cbeign(): " << *umultiset1.cbegin() << std::endl;
    auto printVal = [](const int &val) {
        std::cout << val << " ";
    };
    mystl::for_each(umultiset1.begin(), umultiset1.end(), printVal);
    std::cout << std::endl;

    std::cout << "test add / erase: "  << std::endl;
    umultiset1.emplace(100);
    std::cout << "umultiset1.size(): " << umultiset1.size()  << std::endl;

    umultiset1.insert(100);
    std::cout << "umultiset1.size(): " << umultiset1.size()  << std::endl;

    mystl::vector<int> vec1{23, 45, 56, 45, 45, 56, 23};
    umultiset1.insert(vec1.begin(), vec1.end());
    std::cout << "umultiset1.size(): " << umultiset1.size()  << std::endl;
    mystl::for_each(umultiset1.begin(), umultiset1.end(), printVal);
    std::cout << std::endl;

    umultiset1.erase(umultiset1.begin());
    umultiset1.erase(10);
    mystl::for_each(umultiset1.begin(), umultiset1.end(), printVal);
    std::cout << std::endl;

    std::cout << "test buckket begin" << std::endl;
    std::cout << "test find: " << std::endl;
    std::cout << "umultiset1.count(0): "     << umultiset1.count(1)   << std::endl;
    std::cout << "umultiset1.count(1): "     << umultiset1.count(2)   << std::endl;
    std::cout << "umultiset1.count(77): "    << umultiset1.count(77)  << std::endl;

    mystl::unordered_multiset<int> umultiset2{6, 7, 10, 9, 8, 10, 9, 8, 1, 2, 2};
    swap(umultiset1, umultiset2);
    std::cout << "after swapumultiset1 umultiset2" << std::endl;
    mystl::for_each(umultiset1.begin(), umultiset1.end(), printVal);
    std::cout << std::endl;
    std::cout << "umultiset1.count(2): "    << umultiset1.count(2)         << std::endl;

    std::cout << "umultiset1.begin(2): "    << *umultiset1.begin(2)          << std::endl;
    std::cout << "bucket_count: "           << umultiset1.bucket_count()        << std::endl;
    std::cout << "max_bucket_count: "       << umultiset1.max_bucket_count()    << std::endl;
    std::cout << "bucket_size: "            << umultiset1.bucket_size(1)     << std::endl;
        std::cout << "bucket: "             << umultiset1.bucket(2)         << std::endl;

    std::cout << "umultiset1.load_factor: "  << umultiset1.load_factor()          << std::endl;
    std::cout << "max_load_factor: "         << umultiset1.max_load_factor()      << std::endl;

    std::cout << "umultiset1 == umultiset2: "     << (umultiset1 == umultiset2)   << std::endl;
    std::cout << "umultiset1 != umultiset2: "     << (umultiset1 != umultiset2)   << std::endl;

    umultiset1 = {1, 2, 3};
    umultiset2 = {1, 2, 3};

    std::cout << "umultiset1 == umultiset2: "     << (umultiset1 == umultiset2)   << std::endl;
    std::cout << "umultiset1 != umultiset2: "     << (umultiset1 != umultiset2)   << std::endl;

}

void test_hashtable_05() {
    std::cout << "test unrdered_map node: " << std::endl;
    mystl::unordered_map<int, int> umap1();
    mystl::unordered_map<int, int> umap2(10);
    mystl::unordered_map<int, int> umap3(10, mystl::hash<int>(), mystl::equal_to<int>());
    mystl::vector<mystl::pair<int, int>> vec1{{0, 0}, {1, 1}, {2, 2}};
    mystl::unordered_map<int, int> umap4(vec1.begin(), vec1.end());
    mystl::unordered_map<int, int> umap5({{0, 0}, {1, 1}, {2, 2}});
    mystl::unordered_map<int, int> umap6(umap4);
    mystl::unordered_map<int, int> umap7(mystl::move(umap6));

    mystl::unordered_map<int, int> umap8;
    umap8 = umap7;

    mystl::unordered_map<int, int> umap9;
    umap9 = std::move(umap7);

    mystl::unordered_map<int, int> umap10;
    umap10 = {{0, 0}, {1, 1}, {2, 2}};
}

void test_hashtable_06() {
    mystl::unordered_map<int, int> umap1{{0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
    std::cout << "test capacity: "    << std::endl;
    std::cout << "umap1.size(): "     << umap1.size()  << std::endl;
    std::cout << "umap1.empty(): "    << umap1.empty() << std::endl;
    std::cout << "umap1.max_size(): " << umap1.max_size() << std::endl;

    std::cout << "test iterator: "    << std::endl;
    auto beg = umap1.begin();
    std::cout << "first: " << beg->first << " second: " << beg->second << std::endl;

    auto printVal = [](const mystl::pair<int, int> &val) {
        std::cout << "(" << val.first << ", " << val.second << ")" << " ";
    };
    mystl::for_each(umap1.begin(), umap1.end(), printVal);
    std::cout << std::endl;

    std::cout << "test add / erase: " << std::endl;
    mystl::pair<int, int> pair1{100, 1000};
    umap1.emplace(pair1);
    std::cout << "umap1.size(): "     << umap1.size()  << std::endl;

    pair1 = {50, 50};
    umap1.insert(pair1);
    std::cout << "umap1.size(): "     << umap1.size()  << std::endl;

    mystl::vector<mystl::pair<int, int>> vec1{{0, 0}, {8, 8}, {9, 9}};
    umap1.insert(vec1.begin(), vec1.end());
    std::cout << "umap1.size(): "     << umap1.size()  << std::endl;
    mystl::for_each(umap1.begin(), umap1.end(), printVal);
    std::cout << std::endl;

    umap1.erase(umap1.begin());
    umap1.erase(0);
    mystl::for_each(umap1.begin(), umap1.end(), printVal);
    std::cout << std::endl;

    std::cout << "test buckket begin" << std::endl;
    std::cout << "test find: " << std::endl;
    std::cout << "umap1.count(0): "     << umap1.count(1)   << std::endl;
    std::cout << "umap1.count(1): "     << umap1.count(2)   << std::endl;
    std::cout << "umap1.count(77): "    << umap1.count(77)  << std::endl;

    mystl::unordered_map<int, int> umap2{{99, 99}, {88, 88}, {77, 77}};
    swap(umap1, umap2);
    std::cout << "after swapumap1 umap2" << std::endl;
    mystl::for_each(umap1.begin(), umap1.end(), printVal);
    std::cout << std::endl;
    std::cout << "umap1.count(2): "     << umap1.count(2)          << std::endl;


    std::cout << "bucket_count: "       << umap1.bucket_count()        << std::endl;
    std::cout << "max_bucket_count: "   << umap1.max_bucket_count()    << std::endl;
    std::cout << "bucket_size: "        << umap1.bucket_size(1)     << std::endl;
    std::cout << "bucket: "             << umap1.bucket(2)         << std::endl;

    std::cout << "umap1.load_factor: "  << umap1.load_factor()          << std::endl;
    std::cout << "max_load_factor: "    << umap1.max_load_factor()      << std::endl;

    std::cout << "umap1 == umap2: "     << (umap1 == umap2)             << std::endl;
    std::cout << "umap1 != umap2: "     << (umap1 != umap2)             << std::endl;
}

void test_hashtable_07(){
    mystl::unordered_multimap<int, int> umulmap1{{0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};;
    std::cout << "test capacity: " << std::endl;
    std::cout << "umultimap1.size(): "     << umulmap1.size()  << std::endl;
    std::cout << "umultimap1.empty(): "    << umulmap1.empty() << std::endl;
    std::cout << "umultimap1.max_size(): " << umulmap1.max_size() << std::endl;

    std::cout << "test iterator: " << std::endl;
    auto beg = umulmap1.begin();
    std::cout << "first: " << beg->first << " second: " << beg->second << std::endl;

    auto printVal = [](const mystl::pair<int, int> &val) {
        std::cout << "(" << val.first << ", " << val.second << ")" << " ";
    };
    mystl::for_each(umulmap1.begin(), umulmap1.end(), printVal);
    std::cout << std::endl;

    std::cout << "test add / erase: "  << std::endl;
    mystl::pair<int, int> pair1 = {0, 0};
    umulmap1.emplace(pair1);
    std::cout << "umultimap1.size(): " << umulmap1.size()  << std::endl;

    umulmap1.insert(pair1);
    std::cout << "umultimap1.size(): " << umulmap1.size()  << std::endl;

    mystl::vector<mystl::pair<int, int>> vec1{{0, 0}, {8, 8}, {9, 9}};
    umulmap1.insert(vec1.begin(), vec1.end());
    std::cout << "umultimap1.size(): " << umulmap1.size()  << std::endl;
    mystl::for_each(umulmap1.begin(), umulmap1.end(), printVal);
    std::cout << std::endl;

    umulmap1.erase(umulmap1.begin());
    umulmap1.erase(0);
    mystl::for_each(umulmap1.begin(), umulmap1.end(), printVal);
    std::cout << std::endl;

    std::cout << "test buckket begin" << std::endl;
    std::cout << "test find: " << std::endl;
    std::cout << "umultimap1.count(0): "     << umulmap1.count(0)   << std::endl;
    std::cout << "umultimap1.count(1): "     << umulmap1.count(2)   << std::endl;
    std::cout << "umultimap1.count(77): "    << umulmap1.count(77)  << std::endl;

    mystl::unordered_multimap<int, int> umulmap2{{0, 0}, {8, 8}, {9, 9}};
    swap(umulmap1, umulmap2);
    std::cout << "after swapumultimap1 umultimap2" << std::endl;
    mystl::for_each(umulmap1.begin(), umulmap1.end(), printVal);
    std::cout << std::endl;
    std::cout << "umulmap1.count(2): "    << umulmap1.count(2)         << std::endl;

    std::cout << "bucket_count: "           << umulmap1.bucket_count()        << std::endl;
    std::cout << "max_bucket_count: "       << umulmap1.max_bucket_count()    << std::endl;
    std::cout << "bucket_size: "            << umulmap1.bucket_size(1)     << std::endl;
    std::cout << "bucket: "             << umulmap1.bucket(2)         << std::endl;

    std::cout << "umulmap1.load_factor: "  << umulmap1.load_factor()          << std::endl;
    std::cout << "max_load_factor: "         << umulmap1.max_load_factor()      << std::endl;

    std::cout << "umulmap1 == umulmap2: "     << (umulmap1 == umulmap2)   << std::endl;
    std::cout << "umulmap1 != umulmap2: "     << (umulmap1 != umulmap2)   << std::endl;
}