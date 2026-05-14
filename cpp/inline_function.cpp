#include <iostream>

using namespace std;

int add (int a = 1, int b = 1){
    return a + b;
}

int main(){
    cout << add() << endl;
    cout << add(2, 3) << endl;
    cout << add(5, 6) << endl;
    cout << (add(2, 3) < add(5, 6) ? 1 : 2) << endl;
}