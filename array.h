#pragma once

#include <stdexcept>
#include <utility>

template <typename T>
class DynamicArray final {
public:
    DynamicArray() = default;

    ~DynamicArray() {}

    DynamicArray(size_t size) {
        _capacity = size * 2;
        _ptr = static_cast<T *>(::operator new(_capacity * sizeof(T)));
        new (_ptr) T[size];
        _size = size;
    }

    DynamicArray(const DynamicArray &ohter) {
        _size = ohter._size;
        _capacity = ohter._capacity;
        _ptr = static_cast<T *>(::operator new(_capacity * sizeof(T)));
        for (size_t i = 0; i < _size; ++i) {
            new (_ptr + i) T(ohter._ptr[i]);
        }
    }

    DynamicArray(DynamicArray &&ohter) {
        _size = ohter._size;
        _capacity = ohter._capacity;
        _ptr = ohter._ptr;
        ohter._ptr = nullptr;
        ohter._size = 0;
        ohter._capacity = 0;
    }

    void resize(size_t size) {
        if (size < _size) {
            _size = size;
            return;
        }

        auto resized = static_cast<T *>(::operator new(size * 2 * sizeof(T)));

        for (size_t i = 0; i < _size; ++i) {
            new (resized + i) T(std::move(*(_ptr + i)));
        }

        for (size_t i = _size; i < size; ++i) {
            new (resized + i) T();
        }

        _capacity = size * 2;
        _size = size;

        delete[] _ptr;
        _ptr = resized;
    }

    void pushBack(T &&item) {
        if (_capacity < _size + 1 && _size != 0 && _ptr != nullptr) {
            new (_ptr + _size) T(std::forward<T>(item));
            _size = _size + 1;
            return;
        }

        auto resized =
            static_cast<T *>(::operator new((_size + 1) * 2 * sizeof(T)));

        for (size_t i = 0; i < _size; ++i) {
            new (resized + i) T(std::move(*(_ptr + i)));
        }

        new (resized + _size) T(std::forward<T>(item));
        _size++;
        _capacity = _size * 2;

        delete[] _ptr;
        _ptr = resized;
    }

    T operator[](int index) const {
        if (index >= _size) {
            throw std::runtime_error("index >= size");
        }

        return *(_ptr + index);
    }

    T &operator[](int index) {
        if (index >= _size) {
            throw std::runtime_error("index >= size");
        }

        return *(_ptr + index);
    }

private:
    T *_ptr = nullptr;
    size_t _size = 0;
    size_t _capacity = 0;
};