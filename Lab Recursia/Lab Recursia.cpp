#include <iostream>
#include <vector>
using namespace std;

//Напишіть програму для друку елементів масиву за допомогою рекурсії.
void Print(vector<int> mass, int i) 
{
    if (mass.size() == i)
        return;
    cout << mass[i] << " ";
    Print(mass, i + 1);
}

// Нехай N ⎯ невід'ємне ціле число. Рекурсивно описати функцію від параметра N, яка 
//знаходить найбільшу цифру числа N.

int PrintNumber(int numb, int max)
{
    if (numb == 0)
        return max;
    if (max < numb % 10)
        max = numb % 10;
    return PrintNumber(numb / 10, max);
}

int main()
{
    vector<int> ar = { 1, 2, 3, 4 };
    Print(ar, 0);
    cout << "\n";
    cout << PrintNumber(329051, -1);
}
