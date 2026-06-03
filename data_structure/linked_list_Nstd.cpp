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

        void insertAtBeginning(int value){
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

        void deleteValue(int value){
            if(head == nullptr){
                return;
            }

            if(head -> data == value){
                Node* temp = head;
                head = head -> next;
                delete temp;
                return;
            }

            Node* previous = head;
            Node* current = head -> next;

            while(current != nullptr){
                if(current -> data == value){
                    previous -> next = current -> next;
                    delete current;
                    return;
                }
                previous = current;
                current = current -> next;
            }
        }

        void print() const{
            Node* current = head;

            while(current != nullptr){
                cout << current -> data << " -> ";
                current = current -> next;
            }

            cout << "nullptr" << endl;
        }

};

int main(){
    SinglyLinkedList list;

    list.insertAtBeginning(20);
    list.insertAtBeginning(10);
    list.insertAtEnd(30);
    list.insertAtEnd(40);

    list.print();

    Node* found = list.search(30);

    if (found != nullptr) {
        cout << "Found: " << found->data << endl;
    } else {
        cout << "Not found" << endl;
    }

    list.deleteValue(10);
    list.print();

    list.deleteValue(30);
    list.print();

    return 0;
}