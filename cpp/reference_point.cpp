#include <iostream>

using namespace std;

int main(){
    int i = 1024;
    int &ref_i = i;
    int *p_i = &ref_i;
    cout << ref_i << endl;  //1024
    cout << &ref_i << endl; //0x61ff04
    cout << &i << endl; //0x61ff04
    cout << *p_i << endl; //1024
    cout << p_i << endl; //0x61ff04
    cout << &p_i << endl; //0x61ff08
    ref_i = 2048;
    cout << "ref_i was changed to: " << ref_i << " and its address now: " << &ref_i << endl;
}