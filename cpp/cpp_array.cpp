#include <iostream>

using namespace std;

class RawArray{
    private:
        int data[100];
        int size;
    public:
        RawArray(){
            size = 0;
        }

        int getSize(){
            return size;
        }

        bool isEmpty(){
            return size == 0;
        }

        void printArray(){
            for(int i = 0; i < size; i++){
                cout << data[i] << " ";
            }
            cout << endl;
        }

        void append(int value){
            if(size > 100){
                cout << "Array is full" << endl;
                return;
            }
            data[size] = value;
            size++;
        }

        int get(int index){
            if(index < 0 || index >= size){
                cout << "Invalid Index" << endl;
                return -1;
            }
            return data[index];
        }

        void set(int index, int value){
            if(index < 0 || index >= size){
                cout << "Invalid Index" << endl;
                return ;
            }
            data[index] = value;
        }

        int linearSearch(int target){
            for(int i = 0; i < size; i++){
                if(data[i] == target){
                    return i;
                }
            }
            return -1;
        }

        void insert(int index, int value){
            if (size >= 100) {
                cout << "Array is full." << endl;
                return;
            }

            if (index < 0 || index > size) {
                cout << "Invalid index." << endl;
                return;
            }

            for(int i = size; i > index; i--){
                data[i] = data[i - 1];
            }

            data[index] = value;
            size++;
        }

        void deleteAt(int index){
            if(index < 0 || index >= size){
                cout << "Invalid index" << endl;
                return;
            }

            for(int i = index; i < size - 1; i++){
                data[i] = data[i + 1];
            }

            size--;
        }
};

// test
int main() {
    RawArray arr;

    arr.append(10);
    arr.append(20);
    arr.append(30);
    arr.printArray();

    arr.insert(1, 15);
    arr.printArray();

    arr.deleteAt(2);
    arr.printArray();

    cout << "Index of 15: " << arr.linearSearch(15) << endl;
    cout << "Element at index 1: " << arr.get(1) << endl;

    arr.set(1, 99);
    arr.printArray();

    return 0;
}