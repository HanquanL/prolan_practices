#include <iostream>
#include <thread>

using namespace std;

int main(){
    int id = 0;

    auto f0 = [&id](){
        this_thread::sleep_for(chrono::milliseconds(100));
        cout << "a) ID in Thread (call-by-reference) = " << id << endl;
    };
    thread t1(f0);

    thread t2([id]()mutable{
        this_thread::sleep_for(chrono::milliseconds(50));
        cout << "b) ID in Thread (call-by-value) = " << id << endl;
    });

    ++id;
    cout <<  "c) ID in Main (call-by-value) = " << id << std::endl;

    t1.join();
    t2.join();

    return 0;
}