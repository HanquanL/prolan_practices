#include <iostream>
#include <forward_list>    //singly linked list

using namespace std;

class SinglyLinkedList{
    public:
        bool isEmpty() const{
            return data.empty();
        }

        void insertAtBeginning(int value){
            data.push_front(value);
        }

        void insertAtEnd(int value){
            auto prev = data.before_begin();
            auto curr = data.begin();

            while(curr != data.end()){    // end() is one position past the last node
                ++prev;
                ++curr;
            }

            data.insert_after(prev, value);
        }

        bool search(int target) const{
            for(int value : data){
                if(value == target){
                    return true;
                }
            }
            return false;
        }

        void deleteValue(int value){
            data.remove(value);
        }

        void print() const{
            for(int value : data){
                cout << value << " -> ";
            }
            cout << "nullptr" << endl;
        }

        void clear(){
            data.clear();
        }
    private:
        forward_list<int> data;
};

int main() {
    SinglyLinkedList list;

    list.insertAtBeginning(20);
    list.insertAtBeginning(10);
    list.insertAtEnd(30);
    list.insertAtEnd(40);

    list.print();

    if (list.search(30)) {
        cout << "Found: 30" << endl;
    } else {
        cout << "Not found" << endl;
    }

    list.deleteValue(10);
    list.print();

    list.deleteValue(30);
    list.print();

    return 0;
}