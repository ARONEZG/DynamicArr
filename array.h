#pragma once

#include <stdexcept>
#include <utility>

template <typename T>
class DynamicArray final {
public:
    DynamicArray() = default;

    ~DynamicArray() {
        if (_ptr != nullptr) {
            for (size_t i = 0; i < _size; ++i) {
                _ptr[i].~T();
            }
            ::operator delete(_ptr);
        }
        _ptr = nullptr;
        _size = 0;
        _capacity = 0;
    }

    DynamicArray(size_t size) {
        _capacity = size * 2;
        _ptr = static_cast<T *>(::operator new(_capacity * sizeof(T)));
        int constructed = 0;
        try {
            for (; constructed < size; constructed++) {
                new (_ptr + constructed) T();
            }

            _size = size;
        } catch (...) {
            destruct(constructed);
            throw;
        }
    }

    DynamicArray(const T *begin, int size) {
        _capacity = size * 2;
        _ptr = static_cast<T *>(::operator new(_capacity * sizeof(T)));
        int constructed = 0;

        try {
            for (; constructed < size; ++constructed) {
                new (_ptr + constructed) T(begin[constructed]);
            }

            _size = size;
        } catch (...) {
            destruct(constructed);
            throw;
        }
    }

    DynamicArray(const DynamicArray &ohter) {
        _size = ohter._size;
        _capacity = ohter._capacity;
        _ptr = static_cast<T *>(::operator new(_capacity * sizeof(T)));
        int constructed = 0;
        try {
            for (; constructed < _size; ++constructed) {
                new (_ptr + constructed) T(ohter._ptr[constructed]);
            }
        } catch (...) {
            destruct(constructed);
            throw;
        }
    }

    DynamicArray &operator=(DynamicArray other) {
        swap(other);
        return *this;
    }

    DynamicArray &operator=(DynamicArray &&other) {
        swap(other);
        return *this;
    }

    DynamicArray(DynamicArray &&other) {
        _size = other._size;
        _capacity = other._capacity;
        _ptr = other._ptr;
        other._ptr = nullptr;
        other._size = 0;
        other._capacity = 0;
    }

    void swap(DynamicArray &other) {
        std::swap(_ptr, other._ptr);
        std::swap(_size, other._size);
        std::swap(_capacity, other._capacity);
    }

    void resize(size_t size) {
        if (size < _size) {
            _size = size;
            return;
        }

        auto resized = static_cast<T *>(::operator new(size * 2 * sizeof(T)));

        int constructed = 0;

        try {
            for (; constructed < _size; ++constructed) {
                new (resized + constructed) T(std::move(*(_ptr + constructed)));
            }

            for (; constructed < size; ++constructed) {
                new (resized + constructed) T();
            }

            destruct(constructed);
            _capacity = size * 2;
            _size = size;
            _ptr = resized;

        } catch (...) {
            destruct(constructed);
            throw;
        }
    }

    void pushBack(T &&item) {
        if (_size < _capacity) {
            new (_ptr + _size) T(std::forward<T>(item));
            _size++;
            return;
        }

        auto resized =
            static_cast<T *>(::operator new((_size + 1) * 2 * sizeof(T)));

        int constructed = 0;
        try {
            for (; constructed < _size; ++constructed) {
                new (resized + constructed) T(std::move(*(_ptr + constructed)));
            }

            new (resized + _size) T(std::forward<T>(item));
            _size++;
            _capacity = _size * 2;

            ::operator delete(_ptr);
            _ptr = resized;
        } catch (...) {
            destruct(constructed);
            throw;
        }
    }

    T &operator[](int index) const {
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

    void destruct(int constructed) {
        for (int i = 0; i < constructed; ++i) {
            _ptr[i].~T();
        }

        ::operator delete(_ptr);
        _ptr = nullptr;
        _size = 0;
        _capacity = 0;
    }
};