// CircularDoublyLinkedList.h
// Defines a Linked List that loops end->begin and
//   traverses backwards, with loop at begin->end.

#include <iterator>

// Iterator has to traverse both directions.
// copied from LinkedList, needs reorginization and slight rewriting.
template <class CDLL>
class CDLLIterator {
    public:
        using _T = typename CDLL::value_type;
        using _abstract = typename CDLL::abstract;
    public: // Iterator Boilerplate //
        using iterator_category = std::forward_iterator_tag;
        using value_type        = _T;
        using difference_type   = _T;
        using pointer           = _T*;
        using reference         = _T&;
    public:
        CDLLIterator() : Current{nullptr} {}
        CDLLIterator( _abstract *pN ) : Current{pN} {}

        _T operator *() {
            if (Current == nullptr)
                throw "LLIterator can't dereference null pointer.";
            return Current->Data;
        }
        CDLLIterator<CDLL> operator ++() {
            if (Current != nullptr)
                Current = Current->Next;
            return *this;
        }
        CDLLIterator<CDLL> operator ++(int) {
            CDLLIterator<CDLL> temp = *this;
            if (Current != nullptr)
                Current = Current->Next;
            return temp;
        }
        bool operator ==( const CDLLIterator<CDLL>& Right ) {
            return (Current == Right.Current);
        }
        bool operator !=( const CDLLIterator<CDLL>& Right ) {
            return (Current != Right.Current);
        }
    private:
        _abstract *Current;
};

template <typename Type>
class CircularDoublyLinkedList {
    public:
    using TType = Type;
    //struct Node;
    //using Node = Node<Type>;
    
    void Insert(Type pData) {   
        if (Head == nullptr) // if Head null, allocate Head
            Head = new Node(pData);
        else // Otherwise, traverse until a Node has no next.
        {
            Node *ptr = Head;
            while (ptr->Next != nullptr)
                ptr = ptr->Next;
            ptr->Next = new Node(pData);
        }
    }
    Type Get() {
        return Head->Data;
    }

    private:
    struct Node;
    
    Node *Head;
    Node *Tail;
    unsigned int Size;

};

template <typename Type>
struct CircularDoublyLinkedList<Type>::Node {
    Node(Type pData) : Data{pData} {}
    Node* Prev;
    Type Data;
    Node* Next;
};
