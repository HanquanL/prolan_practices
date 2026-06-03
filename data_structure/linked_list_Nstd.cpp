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

        void insertAtBegining(int value){
            Node* newNode = new Node(value);
            newNode -> next = head;
            head = newNode;
        }

        void insertAtEnd(int value){
            Node* newNode = new Node(value);

            if(head == nullptr){
                head = newNode;
                return;
            }

            Node* current = head;
            while(current -> next != nullptr){
                current = current -> next;
            }

            current -> next = newNode;
        }

        Node* search(int target) const{
            Node* current = head;

            while(current != nullptr){
                if(current -> data == target){
                    return current;
                }
                current = current->next;
            }

            return nullptr;
        }

        
};