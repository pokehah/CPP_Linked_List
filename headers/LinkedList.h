// LinkedList.h
// - Defines an unsorted singlely linked list.
#pragma once

#include <iterator>
#include <initializer_list>
#include <iostream>

// NEEDS Copy+Move Constructors
template <class LList>
class LLIterator {
    public:
        using _T = typename LList::value_type;
        using _abstract = typename LList::abstract;
    public: // Iterator Boilerplate //
        using iterator_category = std::forward_iterator_tag;
        using value_type        = _T;
        using difference_type   = _T;
        using pointer           = _T*;
        using reference         = _T&;
    public:
        LLIterator() : Current{nullptr} {}
        LLIterator( _abstract *pN ) : Current{pN} {}

        _T operator *() {
            if (Current == nullptr)
                throw "LLIterator can't dereference null pointer.";
            return Current->Data;
        }
        LLIterator<LList> operator ++() {
            if (Current != nullptr)
                Current = Current->Next;
            return *this;
        }
        LLIterator<LList> operator ++(int) {
            LLIterator<LList> temp = *this;
            if (Current != nullptr)
                Current = Current->Next;
            return temp;
        }
        bool operator ==( const LLIterator<LList>& Right ) {
            return (Current == Right.Current);
        }
        bool operator !=( const LLIterator<LList>& Right ) {
            return (Current != Right.Current);
        }
    private:
        _abstract *Current;
};


template <typename Type>
class LinkedList {
    public:
        template <typename _T = Type> struct Node;
        using value_type = Type;
        using Iterator = LLIterator<LinkedList>;
        using Initializer_List = std::initializer_list<Type>;
        using abstract = Node<Type>; // LinkedList is an abstract of Node. Used in Iterator.
    public:
        LinkedList() : Head{nullptr}, Size{0} {}
        LinkedList(const LinkedList &ll);
        LinkedList(Initializer_List list);
        ~LinkedList() { Destroy(); }

        LinkedList& operator =(const LinkedList<Type> &right);
        LinkedList& operator =(const Initializer_List& list);

        // Boy I wish I knew how to define templated nested classes externally.
        template <typename _T> struct Node {
            Node() = default;
            Node(_T pData) : Data{pData}, Next{nullptr} {}
            _T Data;
            Node* Next;
        };

        void Destroy();

        void Insert(Type pData);
        void Insert(std::initializer_list<Type> list);

        Iterator begin() const;
        Iterator end() const;
    private:
        Node<Type> *Head;
        unsigned int Size;
};


// LinkedList Member Functions //
template <typename Type>
LinkedList<Type>::LinkedList(const LinkedList &ll)
    : Head{nullptr}, Size{0}
{
    for (const auto &item : ll)
        Insert(item);
}

template <typename Type>
LinkedList<Type>::LinkedList(std::initializer_list<Type> list)
    : Head{nullptr}, Size{0}
{
    Insert(list);
}


template <typename Type>
LinkedList<Type>& LinkedList<Type>::operator =(const LinkedList<Type> &right) {
    Destroy();
    for (const auto &item : right)
        Insert(item);
    return *this;
}

template <typename Type>
LinkedList<Type>& LinkedList<Type>::operator =(const Initializer_List& list) {
    Destroy();
    Insert(list);
    return *this;
}

template <typename Type>
void LinkedList<Type>::Destroy() {
    Node<Type> *Current = Head;
    Node<Type> *tmp = nullptr;
    while (Current != nullptr)
    {
        tmp = Current;
        Current = Current->Next;
        delete tmp;
    }
    Head = nullptr;
    Size = 0;
}

template <typename Type>
void LinkedList<Type>::Insert(Type pData) {
    if (Head == nullptr) // if Head null, allocate Head
        Head = new Node<Type>(pData);
    else // Otherwise, traverse until a Node has no next.
    {
        Node<Type> *ptr = Head;
        while (ptr->Next != nullptr)
            ptr = ptr->Next;
        ptr->Next = new Node<Type>(pData);
    }
    ++Size;
}

template <typename Type>
void LinkedList<Type>::Insert(std::initializer_list<Type> list) {
    for (auto &Val : list)
        Insert(Val);
}

template <typename Type>
LLIterator<LinkedList<Type>> LinkedList<Type>::begin() const {
    return LLIterator<LinkedList<Type>>{Head};
}

template <typename Type>
LLIterator<LinkedList<Type>> LinkedList<Type>::end() const {
    return LLIterator<LinkedList<Type>>{nullptr};
}


// Free Functions for LinkedList //
template <typename Type>
void Print(LinkedList<Type> List)
{
    auto Iter = List.begin();
    std::cout << "[ ";
    if (Iter != List.end())
    {
        std::cout << *Iter;
        ++Iter;
        while (Iter != List.end())
        {
            std::cout << ", " << *Iter;
            ++Iter;
        }
    }
    std::cout << " ]" << std::endl;
}
