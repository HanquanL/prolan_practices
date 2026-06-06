/* Use circular buffer in the queue */
#include <iostream>
#include <stdexcept>

template <typename T>
class Queue{
    private:
        T* data;
        size_t head;    // index of the front element
        size_t count;    //number of elements stored
        size_t capacity;    // slots allocated

        void resize(size_t newCapacity){
            T* newData = new T[newCapacity];
            for(size_t i = 0; i < count ; ++i){
                newData[i] = data[(head + i) % capacity];    // unwrap into order
            }
            delete[] data;
            data = newData;
            capacity = newCapacity;
            head = 0;
        }
    public:
        Queue() : data(nullptr), head(0), count(0), capacity(0) {}

        ~Queue(){
            delete[] data;
        }

        void enqueue(const T& value){
            if(count == capacity){
                size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;
                resize(newCapacity);
            }
            size_t tail = (head + count) % capacity;    // first free slot
            data[tail] = value;
            ++count;
        }

        void dequeue(){
            if(count ==0){
                throw std::out_of_range("dequeue from empty queue");
            }
            head = (head + 1) % capacity;
            --count;
        }

        T& front(){
            if(count ==0){
                throw std::out_of_range("front of empty queue");
            }
            return data[head];
        }

        bool empty() const{
            return count == 0;
        }

        size_t size() const{
            return count;
        }
};

int main() {
    Queue<int> q;

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);                   // front → back: 10 20 30

    std::cout << q.front() << "\n";  // 10
    q.dequeue();                     // removes 10
    std::cout << q.front() << "\n";  // 20
    std::cout << "size: " << q.size() << "\n";   // 2

    while (!q.empty()) {
        std::cout << q.front() << " ";   // 20 30
        q.dequeue();
    }
    std::cout << "\n";
}