#pragma once
#include "Queue.h"
#include "Stack.h"
#include<iostream>

template <typename T>
class BinaryTree
{
    struct Node
    {
        double val = 0;
        Node* parent = nullptr;
        Node* left = nullptr;
        Node* right = nullptr;

        Node(int val) : val(val) {}
        Node() {}
    };

    Node* root = nullptr;
    int count = 0;

    class iterator {
        Stack<Node*> nodes;
        Node* current;
    public:

        iterator(Node* node)
        {
            nodes.Push(node);
            operator++();
        }
        /*iterator(iterator&& other)
        {
            current = other.current;
            nodes = other.nodes;
        }*/

        iterator& operator++ ()
        {
            if (!nodes.IsEmpty())
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
   
    Node* AddNode(Node* root, T value, Node* parent = nullptr);

    Node* AddNode(Node* root, Node* value, Node* parent = nullptr);

    void DeleteNode(Node*& root, T value);

    //void DeleteNode(Node*& root, Node* node);//rewrite

    bool Search(Node* root, T value) const;

    Node* SearchNode(Node* root, T value) const;

    void PrintPreOrder(Node* node) const;

    void PrintInOrder(Node* node) const; 

    void PrintPostOrder(Node* node) const; 

    void PrintBFS(Node* node); // BFS

    void PrintDFS(Node* node); // DFS !!!

    void PrettyPrint(Node* node);

    int Max(Node* node);

    int Min(Node* node);

    void Clear(Node* node);
public:
    ~BinaryTree();

    void Add(T value);

    void Add(Node* value);

    void Delete(T value);

    //void Delete(Node* node);

    bool Search(T value) const;

    Node* GetRoot() const;

    int GetMax();

    int GetMin();

    int GetSize() const;

    void Print();

    void PrintPreOrder() const; // pre-order

    void PrintInOrder() const; // in-order

    void PrintPostOrder() const; // post-order

    int Height(Node* root) const;

    void BFS();

    void DFS();

    void DeleteTree();

    bool IsEmpty() const;

    int GetHeight();

    iterator begin() {
        return iterator(root);
    }
    
    iterator end()
    {
        return iterator(nullptr);
    }
};

template <typename T>
BinaryTree<T>::~BinaryTree()
{
    if (root)
    {
        DeleteTree();
    }
}

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::AddNode(Node* node, T value, Node* parent)
{
    if (!node)
    {
        node = new Node(value);
        node->parent = parent;
        count++;
        return node;
    }
    else if (node->val < value)
        node->right = AddNode(node->right, value, node);
    else if (node->val > value)
        node->left = AddNode(node->left, value, node);
    else
        return node;
    return node;
}

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::AddNode(Node* node, Node* value, Node* parent)
{
    if (!node)
    {
        node = value;
        node->parent = parent;
        count++;
        return node;
    }
    else if (node->val < value->val)
        node->right = AddNode(node->right, value, node);
    else if (value->val < node->val)
        node->left = AddNode(node->left, value, node);
    else
        return node;
    return node;
    
}

template <typename T>
void BinaryTree<T>::DeleteNode(Node*& root, T value)
{
    if (!root)
        return;
    if (root->val < value)
        DeleteNode(root->right, value);
    else if (root->val > value)
        DeleteNode(root->left, value);
    else
    {
        count--;
       if (root->left && root->right)
        {
            Node* node = root->right;
            while (node->left)
            {
                node = node->left;
            }
            root->val = node->val;
            DeleteNode(root->right, node->val);

        }
        else
        {
            Node* node = root->left ? root->left : root->right;

            if (node)
            {
                node->parent = root->parent;
            }

            delete root;
            root = node;
        }

    }

}
//
//template <typename T>
//void BinaryTree<T>::DeleteNode(Node*& root, Node* node)
//{
//    if (!root || !node)
//        return;
//    if (root->val < node->val)
//        DeleteNode(root->right, node);
//    else if (root->val > node->val)
//        DeleteNode(root->left, node);
//    else
//    {
//        count--;
//        if (root->left && root->right)
//        {
//            Node* node = root->right;
//            while (node->left) node = node->left;
//            root->val = node->val;
//            DeleteNode(root, node);
//        }
//        else
//        {
//            Node* node = root->left ? root->left : root->right;
//
//            if (node)
//            {
//                node->parent = root->parent;
//            }
//
//            delete root;
//            root = node;
//        }
//
//    }
//} //rewrite

template <typename T>
bool BinaryTree<T>::Search(Node* root, T value) const
{
    if (!root)
        return false;
    if (value == root->val)
        return true;
    if (value > root->val)
        return Search(root->right, value);
    else if (value < root->val)
        return Search(root->left, value);
}

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::SearchNode(Node* root, T value) const
{
    if (!root)
        return nullptr;
    if (value == root->val)
        return root;
    if (value < root->val)
        return SearchNode(root->left, value);
    else
        return SearchNode(root->right, value);
    return nullptr;
}

template <typename T>
void BinaryTree<T>::PrintPreOrder(Node* node) const // pre-order
{
    if (!node)
        return;
    if (node->left) PrintPreOrder(node->left);
    cout << node->val << "\n";
    if (node->right) PrintPreOrder(node->right);
}

template <typename T>
void BinaryTree<T>::PrintInOrder(Node* node) const // in-order
{
    if (!node)
        return;
    cout << node->val << "\n";
    if (node->left) PrintInOrder(node->left);
    if (node->right) PrintInOrder(node->right);
}

template <typename T>
void BinaryTree<T>::PrintPostOrder(Node* node) const // post-order
{
    if (!node)
        return;
    if (node->left) PrintPostOrder(node->left);
    if (node->right) PrintPostOrder(node->right);
    cout << node->val << "\n";
}

template <typename T>
void BinaryTree<T>::PrintBFS(Node* node) // BFS !!!
{
    if (!node)
        return;
    Queue<Node*> queue;
    queue.Enqueue(node);
    while (!queue.IsEmpty())
    {
        node = queue.Dequeue();
        cout << "\n";
        if (node->left)
            queue.Enqueue(node->left);
        if (node->right)
            queue.Enqueue(node->right);
    }
}

template <typename T>
void BinaryTree<T>::PrintDFS(Node* node) // DFS !!!
{
    if (!node)
        return;
    cout << node->val << "\n";
    if (node->left) PrintDFS(node->left);

    if (node->right) PrintDFS(node->right);
}

template <typename T>
void BinaryTree<T>::PrettyPrint(Node* node)
{
    if (!node)
        return;
    Queue<Node*>* queue = new Queue<Node*>();
    queue->Enqueue(node);
    int c = 1;
    while (!queue->IsEmpty())
    {
        int level_size = queue->Size();
        cout << "Level " << c++ << ": ";
        for (int i = 0; i < level_size; i++)
        {
            node = queue->Dequeue();
            if (node->left)
                queue->Enqueue(node->left);
            if (node->right)
                queue->Enqueue(node->right);
        }
        cout << "\n";
    }
}

template <typename T>
int BinaryTree<T>::Max(Node* node) {
    if (node->right)
        return Max(node->right);
    else
        return node->val;
}

template <typename T>
int BinaryTree<T>::Min(Node* node) {
    if (node->left)
        return Min(node->left);
    else
    {
        return node->val;
    }

}

template <typename T>
void BinaryTree<T>::Add(T value)
{
    root = AddNode(root, value, nullptr);
}

template <typename T>
void BinaryTree<T>::Add(Node* value)
{
    root = AddNode(root, value, nullptr);
}

template <typename T>
void BinaryTree<T>::Delete(T value)
{
    DeleteNode(root, value);
}

//template <typename T>
//void BinaryTree<T>::Delete(Node* node)
//{
//    DeleteNode(root, node);
//}

template <typename T>
bool BinaryTree<T>::Search(T value) const
{
    return Search(root, value);
}

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::GetRoot() const
{
    return root;
}

template <typename T>
int BinaryTree<T>::GetMax()
{
    return Max(root);
}

template <typename T>
int BinaryTree<T>::GetMin()
{
    return Min(root);
}

template <typename T>
int BinaryTree<T>::GetSize() const
{
    return count;
}

template <typename T>
void BinaryTree<T>::Print()
{
    PrettyPrint(root);
}

template <typename T>
int BinaryTree<T>::Height(Node* root) const
{
    if (!root)
    {
        return -1;
    }
    else
    {
        int left_height = Height(root->left);
        int right_height = Height(root->right);

        return max(left_height, right_height) + 1;
    }
}

template <typename T>
void BinaryTree<T>::PrintInOrder() const
{
    PrintInOrder(root);
}

template <typename T>
void BinaryTree<T>::PrintPostOrder() const
{
    PrintPostOrder(root);
}

template <typename T>
void BinaryTree<T>::PrintPreOrder() const
{
    PrintPreOrder(root);
}

template <typename T>
void BinaryTree<T>::BFS()
{
    PrintBFS(root);
}

template <typename T>
void BinaryTree<T>::DFS()
{

}

template<typename T>
int BinaryTree<T>::GetHeight() 
{
    return Height(root);
}

template <typename T>
void BinaryTree<T>::DeleteTree()
{
    Clear(root);
    root = nullptr;
    count = 0;
}

template <typename T>
void BinaryTree<T>::Clear(Node* node)
{
    if (!node)
        return;
    if(node->left) Clear(node->left);
    if (node->right) Clear(node->right);
    delete node;
}

template <typename T>
bool BinaryTree<T>::IsEmpty() const 
{
    return root == nullptr ? false : true;
}
