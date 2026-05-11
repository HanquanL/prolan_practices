#include <iostream>
#include <typeinfo>

using namespace std;

int main(){
    typedef double wages;
    typedef wages base, *p;
    cout << typeid(base).name() << endl;

    using MI = int;
    MI my_item = 1;
    cout << typeid(my_item).name() << ":" << my_item << endl;


}