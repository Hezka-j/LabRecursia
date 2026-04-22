#include "Stack.h"
using namespace std;

template <typename T>
void Stack<T>::Push(T value)
{
    bottom.push_back(value);
}

template <typename T>
T Stack<T>::Pop()
{
    T res = Peek();
    bottom.pop_back();
    return res;
}

template <typename T>
T Stack<T>::Peek()
{
    return bottom[bottom.size() - 1];
}

template <typename T>
bool Stack<T>::IsEmpty()
{
    return bottom.size() ? false : true;
}

template <typename T>
void Stack<T>::Print() const
{
    for (int i = bottom.size() - 1; i >= 0; i--)
        cout << bottom[i] << " ";
}