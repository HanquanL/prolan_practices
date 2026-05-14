#include <iostream>
#include <string>

using namespace std;

initializer_list<string> ls;
initializer_list<int> li;

void error_msg(initializer_list<string> il){
    for(auto beg = il.begin(); beg != il.end(); ++beg){
        cout << *beg << " ";
        cout << endl;
    }
}