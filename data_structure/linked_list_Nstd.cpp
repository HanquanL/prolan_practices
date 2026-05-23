#include <iostream>

using namespace std;

class Node {
    public:
        int data;
        Node* next;

        Node(int value) : data(value), next(nullptr){}
};

class SinglyLinkedList {
    private:
        Node* head;
    
    public:
        SinglyLinkedList() : head(nullptr){}

        ~SinglyLinkedList(){
            clear();
        }
};