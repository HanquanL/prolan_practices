#include <iostream>
#include <queue>
#include <functional>

int main(){
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;

    min_heap.push(10);
    min_heap.push(20);
    min_heap.push(3);
    min_heap.push(30);
    min_heap.push(40);
    min_heap.push(11);

    std::cout << "min: " << min_heap.top() << "\n"; 

    while( !min_heap.empty()){
        std::cout << min_heap.top() << " ";
        min_heap.pop();
    }
    std::cout << "\n";


}