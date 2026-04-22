#pragma once
#include <vector>
#include <iostream>

template <typename T>
class Stack
{
    std::vector<T> bottom;
public:
    void Push(T value);

    T Pop();

    T Peek();

    bool IsEmpty();

    void Print() const;
};