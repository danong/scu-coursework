#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <cassert>
#include <algorithm>

namespace DONG
{
template <class T>
class stack
{
public:
    // constants
    static const std::size_t INITIAL_CAPACITY = 100;


    // constructor

    // pre:
    // post: a new stack has been created with given capacity
    //       if not specified, INITIAL_CAPACITY is used
    stack(std::size_t init_capacity = INITIAL_CAPACITY);

    // const members

    // pre:
    // post: returns true iff there are no elements in this stack
    bool empty() const;

    // pre:
    // post: returns the number of elements in this stack
    std::size_t size() const;

    // pre:
    // post: returns a reference to top of this stack

    T & top();
    const T & top() const;

    // mutator members

    // pre: this stack is not empty
    // post: the top element has been removed from this stack
    void pop();


    // pre:
    // post: a copy of entry has been added to this stack
    void push(const T & entry);

private:

    T *data;
    std::size_t capacity, used;

    // invariants:
    // 1) capacity is the physical size of dynamic array data
    // 2) used is the actual number of elements in this array
    // 3) data[0], data[1], ..., data[used-1] hold the
    //    elements of this stack in increasing insertion time
    //    in particular, data[used-1] is the top element
    //    (last one inserted)
};


template<class T>
stack<T>::stack(std::size_t init_capacity)
{
    data = new T[init_capacity];
    capacity = init_capacity;
    used = 0;
}

template <class T>
bool stack<T>::empty() const
{
    return (used == 0);
}

template <class T>
std::size_t stack<T>::size() const
{
    return used;
}

template <class T>
T & stack<T>::top()
{
    assert(!empty());
    return data[used-1];
}

template <class T>
const T & stack<T>::top() const
{
    assert(!empty());
    return data[used-1];
}

template <class T>
void stack<T>::pop()
{
    assert(!empty());
    --used;
}

template <class T>
void stack<T>::push(const T & entry)
{
    if (used == capacity)
    {
        capacity *= 2;
        T *newdata = new T[capacity];
        std::copy(data, data+used, newdata);
        delete [] data;
        data = newdata;
    }
    data[used++] = entry;
}
}
#endif // STACK_H
