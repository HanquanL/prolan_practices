#include <iostream>

using namespace std;

template <typename T>    //placeholder for "some type to be decided later."
class DoublyLinkedList{
    private:
        struct Node {
            T data;
            Node* prev;
            Node* next;
            Node(const T& value) : data(value), prev(nullptr), next(nullptr){}
        };

        Node* head;
        Node* tail;
        size_t count;    //non-nagitive, large enough
    
    public:
        DoublyLinkedList() : head(nullptr), tail(nullptr), count(0){}
        ~DoublyLinkedList() { clear(); }

        void push_front(const T& value){
            Node* node = new Node(value);
            if(head == nullptr){
                head = tail = node;
            }else{
                node -> next = head;
                head -> prev = node;
                head = node;
            }
            ++count;
        }

        void push_back(const T& value){
            Node* node = new Node(value);
            if(tail == nullptr){
                head = tail = node;
            }else{
                node -> prev = tail;
                tail -> next = node;
                tail = node;
            }
            ++count;
        }

        void pop_front() {
            if (head == nullptr) return;
            Node* old = head;
            head = head -> next;
            if(head != nullptr){
                head -> prev = nullptr;
            }else{
                tail = nullptr;    // list becam empty
            }
            delete old;
            --count;
        }

        void pop_back(){
            if(tail == nullptr) return;
            Node* old = tail;
            tail = tail -> prev;
            if(tail != nullptr){
                tail -> next = nullptr;
            }else{
                head = nullptr;    //list became empty
            }
            delete old;
            --count;
        }

        bool remove(const T& value){
            for (Node* current = head; current != nullptr; current = current -> next){
                if(current -> data == value){
                    if(current -> prev){
                        current -> prev -> next = current -> next;
                    }else{
                        head = current -> next;     // removing the head;
                    }
                    if(current -> next){
                        current -> next -> prev = current -> prev;
                    }else{
                        tail = current -> prev;
                    }
                    delete current;
                    --count;
                    return true;
                }
            }
            return false;
        }

        void print_forward() const{
            std::cout <<"[ ";
            for(Node* current = head; current != nullptr; current = current -> next){
                std::cout << current -> data << " ";
            }
            std::cout << " ]\n";
        }

        void print_backward() const{
            std::cout <<"[ ";
            for(Node* current = tail; current != nullptr; current = current -> prev){
                std::cout << current -> data << " ";
            }
            std::cout << " ]\n";
        }

        size_t size() const { return count; }

        bool empty() const { return count == 0; }

        void clear(){
            Node* current = head;
            while (current != nullptr){
                Node* next = current -> next;
                delete current;
                current = next;
            }
            head = tail = nullptr;
            count = 0;
        }
};


// testing
int main(){
    DoublyLinkedList<int> list;

    list.push_back(10);
    list.push_back(20);
    list.push_front(5);     // list: 5 10 20

    list.print_forward();   // [ 5 10 20 ]
    list.print_backward();  // [ 20 10 5 ]

    list.pop_front();       // 10 20
    list.pop_back();        // 10

    list.push_back(30);
    list.push_back(40);     // 10 30 40
    list.remove(30);        // 10 40
    list.print_forward();   // [ 10 40 ]

    std::cout << "size: " << list.size() << "\n";  // 2
}