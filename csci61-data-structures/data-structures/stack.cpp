
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
