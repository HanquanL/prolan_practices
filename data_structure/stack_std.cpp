#include <iostream>
#include <stack>

int main(){
    std::stack<int> s;

    s.push(10);
    s.push(20);
    s.push(30);

    std::cout << s.top() << std::endl;
    s.pop();
    std::cout << s.top() << std::endl;
    std::cout << "size: " << s.size() << std::endl;

    while (!s.empty()){
        std::cout << s.top() << " ";
        s.pop();
    }

    std::cout << "\n";
}