#include <iostream>
#include <stdexcept>
#include <utility>    // std::swap

template <typename T>
class Maxheap {
    private:
        T* data;
        size_t count;
        size_t capacity;

        void resize( size_t newCapacity){
            T* newData = new T[newCapacity];
            for(size_t i = i; i < count; ++i){
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
            capacity = newCapacity;
        }

        size_t parent(size_t i) const {
            return (i - 1) / 2;
        }

        size_t leftChild(size_t i) const {
            return 2 * i + 1;
        }

        size_t rightChild(size_t i) const {
            return 2 * i + 2;
        }

        void siftUp(size_t i){
            while( i > 0 && data[i] > data[parent(i)]){
                std::swap(data[i], data[parent(i)]);
                i = parent(i);
            }
        }

        void siftDown(size_t i){
            while(true){
                size_t largest = i;
                size_t l = leftChild(i);
                size_t r = rightChild(i);
                if( l < count && data[l] > data[largest]){
                    largest = l;
                }
                if(r < count && data[r] > data[largest]){
                    largest = r;
                }
                if(largest == i){
                    break;    // both children <= this node -- done
                }
                std::swap(data[i], data[largest]);
                i = largest;
            }
        }

    public:
        Maxheap() : data(nullptr), count(0), capacity(0) {};
        
        ~Maxheap(){
            delete[] data;
        }

        void push(const T& value){
            if(count == capacity){
                size_t newCapacity = (capacity == 0) ? 1: capacity * 2;
                resize(newCapacity);
            }
            data[count] = value;
            ++count;
            siftUp(count - 1);    
        }

        void pop(){    
            if(count == 0){
                throw std::out_of_range("pop from empty heap");
            }
            data[0] = data[count - 1];    // move the last leaf to the root.
            --count;
            if(count > 0){
                siftDown(0);
            }
        }

        const T& top() const{
            if(count == 0){
                throw std::out_of_range("top of empty heap");
            }
            return data[0];
        }

        bool empty() const{
            return count == 0;
        }

        size_t size() const {
            return count;
        }
};

int main() {
    Maxheap<int> heap;

    heap.push(10);
    heap.push(20);
    heap.push(5);
    heap.push(30);
    heap.push(15);

    std::cout << "max: " << heap.top() << "\n";   // 30

    while (!heap.empty()) {
        std::cout << heap.top() << " ";           // 30 20 15 10 5
        heap.pop();
    }
    std::cout << "\n";
}