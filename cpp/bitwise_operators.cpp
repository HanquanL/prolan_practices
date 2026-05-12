#include <iostream>

using namespace std;

int main(){
    unsigned long quiz1 = 0;

    quiz1 |= 1UL << 27;

    bool status = quiz1 & (1UL << 27);
}