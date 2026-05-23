#include <iostream>
#include <thread>
#include <string>

using namespace std;

void printName(string name, int waitTime){
    this_thread::sleep_for(chrono::milliseconds(waitTime));
    cout << "Name (from Thread) = " << name << std::endl;
}

int main(){
    string name1 = "Thread1";
    string name2 = "Thread2";

    thread t1(printName, name1, 50);
    thread t2(printName, move(name2), 100);

    t1.join();
    t2.join();

    std::cout << "Name (from Main) = " << name1 << std::endl;
    std::cout << "Name (from Main) = " << name2 << std::endl;

    return 0;
}