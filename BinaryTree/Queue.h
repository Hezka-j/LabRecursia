#pragma once
#include<iostream>
#include<vector>
using namespace std;

template <typename T>
class Queue
{
    vector<T> queue;
    int count = 0;
public:
    void Enqueue(T value)
    {
        queue.push_back(value);
        count++;
    }

    T Dequeue()
    {
        count--;
        T res = queue[0];
        cout << queue[0]->val << " ";
        queue.erase(queue.begin());
        return res;
    }

    void Print() const
    {
        for (T i : queue) // foreach
            cout << i << " ";
    }

    bool IsEmpty()
    {
        return queue.size() ? false : true;
    }

    int Size()
    {
        return count;
    }
};
