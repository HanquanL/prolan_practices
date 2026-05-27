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

        void clear(){
            Node* current = head;
            while(current != nullptr){
                Node* temp = current;
                current = current -> next;
                delete temp;
            }

            head = nullptr;
        }

        bool isEmpty() const {
            return head == nullptr;
        }
};