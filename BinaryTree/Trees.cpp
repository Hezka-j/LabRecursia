#include <iostream>
#include "BinaryTree.h"
#include <algorithm>
#include <functional>
using namespace std;

/*
1.      Створити шаблон класу бінарного дерева пошуку з такими операціями.

1.1.              +долучення (вставлення) елемента в дерево;
1.2.              +видалення елемента з дерева;
1.3.             + пошук елемента в дереві. Створити два варіанти функції: перша функція повертає значення true, якщо елемент є в дереві, false – якщо його немає; друга функція повертає вказівник на елемент, якщо він є в дереві, і nullptr якщо його там немає.
1.4.           + пошук мінімального і максимального елементів дерева;
1.5.           + визначення кількості елементів у дереві;
1.6.           + визначення висоти дерева;
1.7.           + пошук батька елемента;
1.8.           + прямий, зворотний, центрований обхід дерева;
1.9.           + обхід дерева в ширину;
1.10.          +формування лінійного дужкового запису дерева;
1.11.         + видалення дерева.

2*.      На основі класу бінарного дерева реалізовувати клас «множина», аналогічний класу set стандартної бібліотеки шаблонів С++. Операції класу «множина».

2.1.             + Конструктор, що створює пусту множину.
2.2.              +Конструктор, що створює множину з заданим критерієм сортування.
2.3.              +Конструктор копіювання.
2.4.              +Конструктор, що створює множину, ініціалізовану елементами інтервалу [begin, end).
2.5.              +Конструктор, що створює множину, ініціалізовану елементами інтервалу [begin, end) з заданим критерієм сортування.
2.6.              +Знаходження кількості елементів множини.
2.7.              +Перевірка, чи є множина порожньою.
2.8.              +Перевірка, чи входить елемент у множину.

3.      На основі класу бінарного дерева реалізувати клас збалансованого дерева. Для балансування використовувати додатковий відсортований масив і бінарний пошук.

4.      На основі класу бінарного дерева реалізувати клас збалансованого дерева. Для балансування використовувати алгоритм DSW.

*/
template <typename T>
class Set
{
    BinaryTree<T>* set = nullptr;
    function<bool(const T&, const T&)> comp;

    struct Node {
        T val;
        Node* left = nullptr;
        Node* right = nullptr;
        Node* parent = nullptr;

        Node(T value) : val(value) {}
    };

    class iterator {
        Stack<Node*> nodes;
        Node* current;
    public:

        iterator(Node* node)
        {
            nodes.Push(node);
            operator++();
        }

        iterator& operator++ ()
        {
            if (nodes.IsEmpty())
            {
                Node* node = nodes.Pop();
                current = node;
                if (node->right)
                    nodes.Push(node->right);
            }
            else
                current = nullptr;
            return *this;
        }

        T operator* ()
        {
            return current->val;
        }

        bool operator == (iterator& other)
        {
            return current == other.current;
        }
        bool operator != (iterator& other)
        {
            return current != other.current;
        }
    };

    vector<T>& Pass(Node* node, vector<T>& p)
    {
        p.push_back(node->val);
        if (node->left) Pass(node->left, p);
        if (node->right) Pass(node->right, p);
        return p;
        
    }
public:
    Set(Set<T>& copy) 
    {
        if(!IsEmpty())
            set->DeleteTree();
        set = new BinaryTree<T>(*copy.set);
        comp = copy.comp;
    }
    
    Set(function<bool(const T&, const T&)> comp) : comp(comp)
    {
        set = new BinaryTree<T>();
        if (!comp)
            comp = [](const T& a, const T& b) { return a < b; };
    }

    template <typename Iterator>
    Set(Iterator ita, Iterator itb, function<bool(const T&, const T&)> comp) : Set(comp)
    {
        for (auto it = ita; it != itb; it++)
        {
            set->Add(*it);
        }
    }

    template <typename Iterator>
    Set(Iterator ita, Iterator itb) : Set(ita, itb, nullptr) {}
    
    Set() : Set(nullptr) {}

    ~Set()
    {
        if (set)
        {
            set->DeleteTree();
        }
    }
    void Insert(T value)
    {
        set->Add(value);
    }

    void Erase(T value)
    {
        set->Delete(value);
    }

    void Clear()
    {
        set->DeleteTree();
    }

    bool Contains(T value)
    {
        return set->Search(value);
    }

    int Size()
    {
        return set->GetSize();
    }

    bool IsEmpty() const
    {
        return set->IsEmpty();
    }

    void Print() const
    {
        vector<T> ar = Pass(reinterpret_cast<Node*>(set->GetRoot()), ar);
        
        sort(ar.begin(), ar.end(), comp);
        for (auto it : ar)
            cout << it << "\n";
        /*if (set)
            set->PrintPreOrder();*/
    }

    auto begin() {
        return set->begin();
    }

    auto end() {
        return set->end();
    }
};
int main()
{
    BinaryTree<int> tr;
    tr.Add(15);
    tr.Add(5);
    tr.Add(19);
    tr.Add(20);
    tr.Add(17);
    tr.Add(2);
    cout << tr.Search(17) << "\n";
    tr.Delete(19);
    tr.Print();
    
}
