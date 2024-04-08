#pragma once

#include <iostream>

template <typename T>
class LINKED_LIST {
private:
    typedef struct _NODE {
        T value;
        struct _NODE* lpNext;

        _NODE(const T& value) : value(value), lpNext(nullptr) {}
        _NODE(const T& value, _NODE* lpNext) : value(value), lpNext(lpNext) {}
    } NODE, * LPNODE;

    LPNODE head;
    size_t size;

public:
    typedef struct _ITERATOR {
    private:
        LPNODE lpNodeCurrent;
    public:
        _ITERATOR(LPNODE lpNode) : lpNodeCurrent(lpNode) {}

        _ITERATOR() : lpNodeCurrent(nullptr) {}

        T& operator*() const {
            return lpNodeCurrent->value;
        }

        LPNODE getNode() {
            return lpNodeCurrent;
        }

        _ITERATOR& operator++() {
            lpNodeCurrent = lpNodeCurrent->lpNext;
            return *this;
        }

        bool operator==(const _ITERATOR& iteratorOther) {
            return lpNodeCurrent == iteratorOther.lpNodeCurrent;
        }

        bool operator!=(const _ITERATOR& iteratorOther) {
            return !(*this == iteratorOther);
        }


    } ITERATOR, * LPITERATOR;

    LINKED_LIST() : head(nullptr), size(0) {}

    LINKED_LIST(std::initializer_list<T> initList) : head(nullptr), size(0) {
        for (const auto& value : initList) {
            push_bottom(value);
        }
    }

    ~LINKED_LIST() {
        clear();
    }

    ITERATOR begin() const {
        return ITERATOR(head);
    }

    ITERATOR end() const {
        return ITERATOR(nullptr);
    }

    bool isEmpty(
    ) const {
        return size == 0;
    }

    T& top() const {
        return head->value;
    }

    LINKED_LIST& push(const T& value) { // O(1)
        LPNODE newNode;

        newNode = new NODE(value, head);
        push(newNode);
        return *this;
    }

    LINKED_LIST& push(LPNODE newNode) {
        head = newNode;
        size++;
        return *this;
    }

    LINKED_LIST& push(LPNODE newNode, size_t size) {
        head = newNode;
        this->size += size;
        return *this;
    }

    LINKED_LIST& push_bottom(const T& value) { // O(N)
        LPNODE newNode;
        newNode = new NODE(value);

        push_bottom(newNode);
        return *this;
    }

    LINKED_LIST& push_bottom(const LPNODE newNode) { // O(N)
        ITERATOR iterator;
        LPNODE currentNode;

        currentNode = head;

        if (isEmpty()) {
            head = newNode;
        }
        else {
            for (iterator = begin(); ++iterator != end();) {
                currentNode = currentNode->lpNext;
            }
            currentNode->lpNext = newNode;
        }
        size++;
        return *this;
    }

    LINKED_LIST& push_bottom(LPNODE newNode, size_t size) { // O(N)
        LPNODE currentNode;
        ITERATOR iterator;

        currentNode = head;

        if (isEmpty()) {
            head = newNode;
        }
        else {
            for (iterator = begin(); ++iterator != end();) {
                currentNode = currentNode->lpNext;
            }
            currentNode->lpNext = newNode;
        }
        this->size += size;
        return *this;
    }

    void pop() { // O(1)
        LPNODE lpTempNode;

        if (!isEmpty()) {
            lpTempNode = head;
            head = head->lpNext;
            delete lpTempNode;
            size--;
        }
    }

    void pop_bottom() { //O(N)
        ITERATOR iterator;
        ITERATOR prevIterator;

        if (!isEmpty()) {
            if (length() == 1) {
                delete head;
                head = nullptr;
                size = 0;
            }
            else {
                iterator = begin();
                prevIterator = iterator;
                ++iterator;

                while (++iterator != end()) {
                    ++prevIterator;
                }

                delete prevIterator.getNode()->lpNext;
                prevIterator.getNode()->lpNext = nullptr;
                size--;
            }
        }
    }

    LPNODE getHead() {
        return head;
    }

    void clear() { // O(N)
        while (begin() != end()) {
            pop();
        }
    }

    void reverse()
    { // O(N)
        LPNODE newNode;
        size_t sizeTempLength;

        if (!isEmpty() && length() != 1) {
            sizeTempLength = length();
            newNode = new NODE(*begin());
            pop();

            while (begin() != end()) {
                newNode = new NODE(*begin(), newNode);
                pop();
            }

            head = newNode;
            size = sizeTempLength;
        }
    }

    T& operator[](size_t index) {
        ITERATOR iterator;

        index = (index + length()) % length();

        for (iterator = begin(); iterator != end() && index != 0; ++iterator) {
            index--;
        }

        return *iterator;
    }

    size_t length() const{
        return size;
    }

    LINKED_LIST<T>& operator+(const T& value) {
        push_bottom(value);
        return *this;
    }

    LINKED_LIST<T>& operator--() {
        pop_bottom();
        return *this;
    }

    LINKED_LIST<T>& operator+(LINKED_LIST<T>& list) {
        LPNODE newHead;
        LPNODE currentNode;
        ITERATOR iterator;

        if (list.isEmpty()) {
            return *this;
        }

        newHead = new NODE(*list.begin());
        currentNode = newHead;

        for (iterator = ++list.begin(); iterator != list.end(); ++iterator) {
            currentNode->lpNext = new NODE(*iterator);
            currentNode = currentNode->lpNext;
        }

        push_bottom(newHead, list.length());

        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os,const LINKED_LIST& list) {
        os << "{ ";
        for (auto item : list) {
            os << item << " ";
        }
        os << "}";
        return os;
    }
};