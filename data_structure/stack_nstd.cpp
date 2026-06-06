#include <iostream>
#include <stdexcept>

template <typename T>
class Stack{
    private:
        T* data;
        size_t count;    // number of elements currently stored
        size_t capacity;    // number of slots allocated

        void resize( size_t newCapacity){
            T* newData = new T[newCapacity];
            for(size_t i = 0; i < count; ++i){
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
            capacity = newCapacity;
        }
    public:
        Stack() : data(nullptr), count(0), capacity(0) {}
        
        ~Stack() {
            delete[] data;
        }

        void push(const T& value){
            if(count == capacity){    // out of room
                size_t newCapacity = (capacity ==0) ? 1 : capacity * 2;
                resize(newCapacity);
            }
            data[count] = value;
            ++count;
        }

        void pop(){
            if(count == 0){
                throw std::out_of_range("pop from empty stack");
            }
            --count;
        }

        T& top(){
            if(count == 0){
                throw std::out_of_range("top of empty stack");
            }
            return data[count - 1];
        }

        bool empty() const {
            return count == 0;
        }

        size_t size() const{
            return count;
        }
};

int main() {
    Stack<int> s;

    s.push(10);
    s.push(20);
    s.push(30);                      // bottom → top: 10 20 30

    std::cout << s.top() << "\n";    // 30
    s.pop();                         // removes 30
    std::cout << s.top() << "\n";    // 20
    std::cout << "size: " << s.size() << "\n";   // 2

    while (!s.empty()) {
        std::cout << s.top() << " "; // 20 10
        s.pop();
    }
    std::cout << "\n";
}