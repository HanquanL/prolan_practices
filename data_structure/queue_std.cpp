#include <iostream>
#include <queue>

int main(){
    std::queue<int> q;

    q.push(1);
    q.push(2);
    q.push(3);

    std::cout <<q.front() << "\n";
    std::cout << q.back() << "\n";
    q.pop();
    std::cout << q.front() << "\n";
    std::cout << "size: " << q.size() << "\n";   // 2

    while (!q.empty()) {
        std::cout << q.front() << " ";   // 20 30
        q.pop();
    }
    std::cout << "\n";
}