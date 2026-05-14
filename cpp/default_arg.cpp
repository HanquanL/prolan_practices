#include <iostream>

using namespace std;

int add (int a = 1, int b = 1){
    cout << a + b << endl;
    return a + b;
}

int main(){
    add();
    add(2, 3);
    add(5, 6);
}