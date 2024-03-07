#include <iostream>
#include <string>
#include <vector>
#include "allocator.h"

void test_alloc_01() {
    // 基本类型的创建
    std::cout << "基本类型的构建：" << std::endl;
    typedef mystl::allocator<int> allocInt;
    auto *locInt = allocInt::allocate();
    std::cout << "size: " << sizeof(locInt) << std::endl;
    allocInt::construct(locInt);
    std::cout << "int value: " << *locInt << std::endl;
    allocInt::destroy(locInt);
    allocInt::deallocate(locInt);
    locInt = nullptr;

    auto *locIntArray = allocInt::allocate(10);
    std::cout << "int array size: " << sizeof(locIntArray) << std::endl;
    auto *loc0 = locIntArray;
    for (int i = 0; i < 10; ++i) {
        allocInt::construct(loc0, i);
        std::cout << "int value: " << *loc0 << std::endl;
        ++loc0;
    }
    while (locIntArray != loc0) {
        allocInt::destroy(--loc0);
    }
    allocInt::deallocate(locIntArray, 10);

    typedef mystl::allocator<float> allocFloat;
    auto *locFloat = allocFloat::allocate();
    std::cout << "size: " << sizeof(locFloat) << std::endl;
    allocFloat::construct(locFloat);
    std::cout << "float value: " << *locFloat << std::endl;
    allocFloat::destroy(locFloat);
    allocFloat::deallocate(locFloat);
    locFloat = nullptr;

    auto *locFloatArray = allocFloat::allocate(10);
    std::cout << "Float array size: " << sizeof(locFloatArray) << std::endl;
    auto *loc1 = locFloatArray;
    for (int i = 0; i < 10; ++i) {
        allocFloat::construct(loc1, i + 0.1 );
        std::cout << "float value: " << *loc1 << std::endl;
        ++loc1;
    }
    while (locFloatArray != loc1) {
        allocFloat::destroy(--loc1);
    }
    allocFloat::deallocate(locFloatArray, 10);

    typedef mystl::allocator<std::string> allocString;
    auto *locStr = allocString::allocate();
    std::cout << "string size: " << sizeof(locStr) << std::endl;
    allocString::construct(locStr);
    std::cout << "string value: " << *locStr << std::endl;
    allocString::destroy(locStr);
    allocString::deallocate(locStr);
    locStr = nullptr;

    auto *locStrArray = allocString::allocate(10);
    std::cout << "string array size: " << sizeof(locIntArray) << std::endl;
    auto *loc2 = locStrArray;
    for (int i = 0; i < 10; ++i) {
        allocString::construct(loc2, "aaa");
        std::cout << "string value: " << *loc2 << std::endl;
        ++loc2;
    }
    while (locStrArray != loc2) {
        allocString::destroy(--loc2);
    }
    allocString::deallocate(locStrArray, 10);

    std::cout << "finish!" << std::endl;
}

class testAlloc {
private:
    int num;
public:
    testAlloc() {
        num = 1;
    }

    testAlloc(int n):num(n) {}

    testAlloc(int &&n):num(n) {}

    int getNum() {
        return num;
    }
};

void test_alloc_02() {
    // 基本类型的创建
    std::cout << "class类型的构建：" << std::endl;
    typedef mystl::allocator<testAlloc> allocTest;
    auto *test = allocTest::allocate();
    allocTest::construct(test);
    std::cout << "num: " << test->getNum() << std::endl;

    auto *testArray = allocTest::allocate(5);
    auto *loc = testArray;
    for (int i = 0; i < 5; ++i) {
        allocTest::construct(loc, i);
        std::cout << "num: " << loc->getNum() << std::endl;
        ++loc;
    }

    while (testArray != loc) {
        --loc;
        allocTest::destroy(loc);
    }
    allocTest::deallocate(testArray, 5);
    std::cout << "finish." << std::endl;
}