#ifndef QUEUE_H
#define QUEUE_H

#include <cassert>
#include <iostream>

namespace DONG
{
template <class T>
class queue
{
public:

    static const std::size_t CAPACITY = 100;
    // pre:
    // post: creates an empty queue
    queue();

    // constant members

    // pre:
    // post: returns true if there are no elements in this queue
    bool empty() const;

    // pre:
    // post: returns the number of elementes in this queue
    std::size_t size() const;

    // pre: this queue is not empty
    // post: returns the front element of this queue
    T & front() const;
    T & front();



    // mutators

    // pre: this queue is not empty
    // post: the front element has been removed from this queue
    void pop();

    // pre: none
    // post: a copy entry has been added to the rear of this queue
    void push(const T & entry);

private:
    T data[CAPACITY];
    int _front, _rear;
    std::size_t used;

};

template <class T>
queue<T>::queue()
{
    _front = 0;
    _rear = CAPACITY - 1;
    used = 0;
}

template <class T>
bool queue<T>::empty() const
{
    return (used == 0);
}

template <class T>
std::size_t queue<T>::size() const
{
    return used;
}

template <class T>
T & queue<T>::front() const
{
    assert(!empty());
    return data[_front];
}

template <class T>
T & front()
{
    assert(!empty());
    return data[_front];
}

template <class T>
void pop()
{
    assert(!empty());
    _front = (_front + 1) % CAPACITY;
    --used;
}
template <class T>
void push(const T & entry)
{
    assert(used < CAPACITY);
    _rear = (_rear + 1) % CAPACITY;
    data[_rear] = entry;
    ++used;
}
}
#endif // QUEUE_H
