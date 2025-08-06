#include <cassert>
#include <iostream>

#include "array.h"

inline void test_default_constructor() {
    std::cout << "Testing default constructor..." << std::endl;
    DynamicArray<int> arr;
    std::cout << "Default constructor test passed" << std::endl;
}

inline void test_size_constructor() {
    std::cout << "Testing size constructor..." << std::endl;
    DynamicArray<int> arr(5);
    for (int i = 0; i < 5; i++) {
        arr[i] = i * 10;
    }
    assert(arr[0] == 0);
    assert(arr[4] == 40);
    std::cout << "Size constructor test passed" << std::endl;
}

inline void test_copy_constructor() {
    std::cout << "Testing copy constructor..." << std::endl;
    DynamicArray<int> arr1(3);
    arr1[0] = 10;
    arr1[1] = 20;
    arr1[2] = 30;

    DynamicArray<int> arr2(arr1);
    assert(arr2[0] == 10);
    assert(arr2[1] == 20);
    assert(arr2[2] == 30);

    arr1[0] = 100;
    assert(arr2[0] == 10);
    std::cout << "Copy constructor test passed" << std::endl;
}

inline void test_move_constructor() {
    std::cout << "Testing move constructor..." << std::endl;
    DynamicArray<int> arr1(3);
    arr1[0] = 10;
    arr1[1] = 20;
    arr1[2] = 30;

    DynamicArray<int> arr2(std::move(arr1));
    assert(arr2[0] == 10);
    assert(arr2[1] == 20);
    assert(arr2[2] == 30);
    std::cout << "Move constructor test passed" << std::endl;
}

inline void test_resize() {
    std::cout << "Testing resize..." << std::endl;
    DynamicArray<int> arr(3);
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;

    arr.resize(5);
    assert(arr[0] == 1);
    assert(arr[1] == 2);
    assert(arr[2] == 3);
    assert(arr[3] == 0);
    assert(arr[4] == 0);

    arr.resize(2);
    assert(arr[0] == 1);
    assert(arr[1] == 2);
    std::cout << "Resize test passed" << std::endl;
}

inline void test_pushBack() {
    std::cout << "Testing pushBack..." << std::endl;
    DynamicArray<int> arr;

    int val1 = 10;
    arr.pushBack(std::move(val1));

    int val2 = 20;
    arr.pushBack(std::move(val2));

    assert(arr[0] == 10);
    assert(arr[1] == 20);
    std::cout << "PushBack test passed" << std::endl;
}

inline void test_operator_access() {
    std::cout << "Testing operator[]..." << std::endl;
    DynamicArray<int> arr(3);

    arr[0] = 100;
    arr[1] = 200;
    arr[2] = 300;

    assert(arr[0] == 100);
    assert(arr[1] == 200);
    assert(arr[2] == 300);

    const DynamicArray<int>& const_arr = arr;
    assert(const_arr[0] == 100);
    assert(const_arr[1] == 200);
    assert(const_arr[2] == 300);
    std::cout << "Operator[] test passed" << std::endl;
}

inline void test_out_of_bounds() {
    std::cout << "Testing out of bounds access..." << std::endl;
    DynamicArray<int> arr(3);

    bool exception_thrown = false;
    try {
        arr[3];
    } catch (const std::runtime_error& e) {
        exception_thrown = true;
        assert(std::string(e.what()) == "index >= size");
    }
    assert(exception_thrown);

    exception_thrown = false;
    try {
        const DynamicArray<int>& const_arr = arr;
        const_arr[5];
    } catch (const std::runtime_error& e) {
        exception_thrown = true;
        assert(std::string(e.what()) == "index >= size");
    }
    assert(exception_thrown);
    std::cout << "Out of bounds test passed" << std::endl;
}

inline void test_with_strings() {
    std::cout << "Testing with strings..." << std::endl;
    DynamicArray<std::string> arr(2);
    arr[0] = "Hello";
    arr[1] = "World";

    assert(arr[0] == "Hello");
    assert(arr[1] == "World");

    DynamicArray<std::string> arr2(arr);
    assert(arr2[0] == "Hello");
    assert(arr2[1] == "World");
    std::cout << "String test passed" << std::endl;
}

void test_negative_index() {
    std::cout << "Testing negative index..." << std::endl;
    DynamicArray<int> arr(3);

    bool exception_thrown = false;
    try {
        arr[-1];
    } catch (const std::runtime_error& e) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    std::cout << "Negative index test passed" << std::endl;
}