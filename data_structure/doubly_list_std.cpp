#include <iostream>
#include <list>

int main(){
    std::list<int> list;

    list.push_back(10);
    list.push_back(20);
    list.push_front(1);

    for(int x : list){
        std::cout << x << " " ;
    }
    std::cout << "\n";

    for(auto it = list.rbegin(); it != list.rend(); ++it){    // backward
        std::cout << *it << " ";
    }
    std::cout << "\n";
    list.pop_front();       // 10 20
    list.pop_back();        // 10

    list.push_back(30);
    list.push_back(40);     // 10 30 40
    list.remove(30);        // 10 40
    std::cout << "size: " << list.size() << "\n"; // 2
}