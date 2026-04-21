#pragma once
#include <cstddef>

template<typename T>
class ForwardList {
    struct Node {
        T _value;
        Node* _next;
        Node(const T& v, Node* n) : _value(v), _next(n) {}
    };
public:
    ForwardList() : _head(nullptr), _size(0) {}
    ~ForwardList() {
        while (_head) {
            Node* tmp = _head;
            _head = _head->_next;
            delete tmp;
        }
    }

    ForwardList(const ForwardList&) = delete;
    ForwardList& operator=(const ForwardList&) = delete;

    std::size_t size() const { return _size; }

    void push_front(const T& x) {
        _head = new Node(x, _head);
        _size++;
    }

    bool remove_first(const T& x) {
        if (!_head) return false;
        if (_head->_value == x) {
            Node* tmp = _head;
            _head = _head->_next;
            delete tmp;
            _size--;
            return true;
        }
        Node* curr = _head;
        while (curr->_next) {
            if (curr->_next->_value == x) {
                Node* tmp = curr->_next;
                curr->_next = curr->_next->_next;
                delete tmp;
                _size--;
                return true;
            }
            curr = curr->_next;
        }
        return false;
    }

    bool contains(const T& x) const {
        for (Node* c = _head; c; c = c->_next) if (c->_value == x) return true;
        return false;
    }

private:
    Node* _head;
    std::size_t _size;
};