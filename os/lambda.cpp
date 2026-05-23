#include <iostream>

using namespace std;

int main(){
    int id = 0;

    //auto f0 = []() { std::cout << "ID = " << id << std::endl; }; // Error: 'id' cannot be accessed

    id++;
    auto f1 = [id](){cout << "ID = " << id << endl;}; // id captured by value

    id++;
    auto f2 = [&id](){cout << "ID = " << id << endl;};   // id captured by ref

    //auto f3 = [id]() { std::cout << "ID = " << ++id << std::endl; }; // Error, 'id' may not be modified

    auto f4 = [id]() mutable { cout << "ID = " << ++id << endl;};

    auto f5 = [](const int *id){cout << "ID = " << *id << endl;};  //id is passed as a parameter

    // execute lambdas
    f1();
    f2();
    f4();
    f5(&id);

    return 0;
}