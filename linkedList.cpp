#include "linkedList.hpp"

int main() {
    LINKED_LIST<int> myList1 = { 4, 5, 6 };
    LINKED_LIST<int> myList2 = { 1, 2, 3 };
    LINKED_LIST<std::string> myList3 = { "apple", "banana", "cherry"};

    myList1 + myList1;
    myList1.reverse();

    myList1.pop_bottom();

    std::cout << "myList1: " << myList1 << " | length : " << myList1.length() << std::endl;
    std::cout << "myList2: " << myList2 << " | length : " << myList2.length() << std::endl;
    std::cout << "myList3: " << myList3 << " | length : " << myList3.length() << std::endl;

    return 0;
}