// LinkedList.h
// - Defines an unsorted singlely linked list.
#pragma once

#include <iterator>
#include <initializer_list>
#include <iostream>

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
        LLIterator(const LLIterator &it) {
            Current = it.Current;
        }
        LLIterator( LLIterator &&it ) {
            this->Current = it.Current;
            it.Current = nullptr;
        }
        LLIterator( _abstract *pN ) : Current{pN} {}
        ~LLIterator() { Current = nullptr; }

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
        LLIterator& operator =( const LLIterator &Right ) {
            Current = Right.Current;
        }
        bool operator ==( const LLIterator<LList> &Right ) {
            return (Current == Right.Current);
        }
        bool operator !=( const LLIterator<LList> &Right ) {
            return (Current != Right.Current);
        }
    private:
        _abstract *Current;
};


template <typename _T>
class LinkedList {
    public:
        struct Node;
        using value_type = _T;
        using Iterator = LLIterator<LinkedList>;
        using Initializer_List = std::initializer_list<_T>;
        using abstract = Node; // LinkedList is an abstract of Node. Used in Iterator.
    public:
        LinkedList() : Head{nullptr}, Size{0} {}
        LinkedList(const LinkedList<_T> &ll);
        LinkedList(const Initializer_List &list);
        ~LinkedList() { Destroy(); }

        LinkedList& operator =(const LinkedList<_T> &right);
        LinkedList& operator =(const Initializer_List &list);

        void Destroy();

        void Insert(_T pData);
        void Insert(std::initializer_list<_T> list);

        Iterator begin() const;
        Iterator end() const;
    private:
        Node *Head;
        unsigned int Size;
};


// LinkedList Member Functions //
template <typename _T>
LinkedList<_T>::LinkedList(const LinkedList<_T> &ll)
    : Head{nullptr}, Size{0}
{
    for (const auto &item : ll)
        Insert(item);
}

template <typename _T>
LinkedList<_T>::LinkedList(const std::initializer_list<_T>& list)
    : Head{nullptr}, Size{0}
{
    Insert(list);
}


template <typename _T>
LinkedList<_T>& LinkedList<_T>::operator =(const LinkedList<_T> &right) {
    Destroy();
    for (const auto &item : right)
        Insert(item);
    return *this;
}

template <typename _T>
LinkedList<_T>& LinkedList<_T>::operator =(const Initializer_List &list) {
    Destroy();
    Insert(list);
    return *this;
}

template <typename _T>
struct LinkedList<_T>::Node {
    Node() = default;
    Node(_T pData) : Data{pData}, Next{nullptr} {}
    _T Data;
    Node* Next;
};


template <typename _T>
void LinkedList<_T>::Destroy() {
    Node *Current = Head;
    Node *tmp = nullptr;
    while (Current != nullptr)
    {
        tmp = Current;
        Current = Current->Next;
        delete tmp;
    }
    Head = nullptr;
    Size = 0;
}

template <typename _T>
void LinkedList<_T>::Insert(_T pData) {
    if (Head == nullptr) // if Head null, allocate Head
        Head = new Node(pData);
    else // Otherwise, traverse until a Node has no next.
    {
        Node *ptr = Head;
        while (ptr->Next != nullptr)
            ptr = ptr->Next;
        ptr->Next = new Node(pData);
    }
    ++Size;
}

template <typename _T>
void LinkedList<_T>::Insert(std::initializer_list<_T> list) {
    for (auto &Val : list)
        Insert(Val);
}

template <typename _T>
LLIterator<LinkedList<_T>> LinkedList<_T>::begin() const {
    return LLIterator<LinkedList<_T>>{Head};
}

template <typename _T>
LLIterator<LinkedList<_T>> LinkedList<_T>::end() const {
    return LLIterator<LinkedList<_T>>{nullptr};
}


// Free Functions for LinkedList //
template <typename _T>
void Print(LinkedList<_T> List)
{
    auto Iter = List.begin();
    std::cout << "[ ";
    if (Iter != List.end())
    {
        std::cout << *(Iter++);
        while (Iter != List.end())
            std::cout << ", " << *(Iter++);
    }
    std::cout << " ]" << std::endl;
}
