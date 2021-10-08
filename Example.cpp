#include <iostream>
#include <algorithm> //std::find
#include "./headers/LinkedList.h"

void LLInitTest();
void LLFindTest();
void working();

void working() { std::cout << "\nworking() commented out." << std::endl; }

int main() {
    LinkedList<int> List{1, 2, 3, 4, 1056, 5, 6, 7, 8};
    List.Destroy();

    LLFindTest();

    LLInitTest();

    working();

    return 0;
}

void LLFindTest() {
    LinkedList<int> List{1, 2, 3, 4, 1056, 5, 6, 7, 8};
    
    std::cout << "Searching List for value 1056." << std::endl;
    auto i = std::find(List.begin(), List.end(), 1056);
    if (i != List.end())
        std::cout << "List contains value: " << *i << std::endl;
    
    std::cout << "List Contents: ";
    Print(List);
}

void LLInitTest() {
    LinkedList<int> list;
    LinkedList<int> l2{5, 2, 3, 4}; // yooo initializer list contructor implemented.
                                    // it's the small things in life
    std::cout << "\nlist = ";
    Print(list); // Empty
    std::cout << "  l2 = ";
    Print(l2);

    list.Insert({5, 4, 2, 3, 1, 10});
    l2 = {1, 2, 3, 4};

    std::cout << "list = ";
    Print(list);
    std::cout << "  l2 = ";
    Print(l2);

    l2.Insert(5);
    l2.Insert({6, 7, 8});

    std::cout << "  l2 = ";
    Print(l2);
}
