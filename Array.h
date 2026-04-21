#pragma once
#include <cstddef>
#include <stdexcept>
#include <string>

template<typename T>
class Array {
public:
    explicit Array(std::size_t capacity = 0)
        : _capacity(capacity), _size(0), _data(capacity ? new T[capacity] : nullptr) {}

    ~Array() { delete[] _data; }

    Array(const Array&) = delete;
    Array& operator=(const Array&) = delete;

    std::size_t size() const { return _size; }
    std::size_t capacity() const { return _capacity; }

    void push_back(const T& x) {
        if (_size == _capacity) _grow();
        _data[_size++] = x;
    }

    bool remove_first(const T& x) {
        for (std::size_t i = 0; i < _size; ++i) {
            if (_data[i] == x) {
                for (std::size_t j = i; j < _size - 1; ++j) _data[j] = _data[j + 1];
                _size--;
                return true;
            }
        }
        return false;
    }

    bool contains(const T& x) const {
        for (std::size_t i = 0; i < _size; ++i) {
            if (_data[i] == x) return true;
        }
        return false;
    }

private:
    std::size_t _capacity;
    std::size_t _size;
    T* _data;

    void _grow() {
        std::size_t new_cap = _capacity * 2 + 1;
        T* new_data = new T[new_cap];
        for (std::size_t i = 0; i < _size; ++i) new_data[i] = _data[i];
        delete[] _data;
        _data = new_data;
        _capacity = new_cap;
    }
};