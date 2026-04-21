#pragma once
#include "Array.h"
#include "ForwardList.h"

template<typename T, template<typename> class Storage = Array>
class Sequence;

template<typename T>
class Sequence<T, Array> {
    Array<T> _storage;
public:
    void append(const T& x) { _storage.push_back(x); }
    void remove(const T& x) { _storage.remove_first(x); }
    bool contains(const T& x) const { return _storage.contains(x); }
    std::size_t size() const { return _storage.size(); }
    bool empty() const { return _storage.size() == 0; }
    std::size_t capacity() const { return _storage.capacity(); }
};

template<typename T>
class Sequence<T, ForwardList> {
    ForwardList<T> _storage;
public:
    void append(const T& x) { _storage.push_front(x); }
    void remove(const T& x) { _storage.remove_first(x); }
    bool contains(const T& x) const { return _storage.contains(x); }
    std::size_t size() const { return _storage.size(); }
    bool empty() const { return _storage.size() == 0; }
    std::size_t capacity() const { return _storage.size(); } 
};