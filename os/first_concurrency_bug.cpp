#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <vector>

using namespace std;
int main(){
    vector<thread> threads;
    for(size_t i = 0; i < 10; ++i){
        threads.emplace_back([&i](){
        // threads.emplace_back([i](){
            this_thread::sleep_for(chrono::milliseconds(10 * i));

            cout << "Hello from worker thread #" << i << endl;
        });
    }

    cout << "Hello from Main thread" << endl;

    for(auto &t : threads){
        t.join();
    }

    return 0;
}