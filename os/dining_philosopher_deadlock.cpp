//this demo show the deadlock
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

using namespace std;

const int N = 5;

mutex forks[N];

void philosopher(int id){
    int left = id;
    int right = (id + 1) % N;

    while(true){
        cout << "philosopher " << id << " is thinking." << endl;
        this_thread::sleep_for(chrono::seconds(1));

        forks[left].lock();
        cout << "philosopher " << id << " picked up left fork." << endl;

        forks[right].lock();
        cout << "philosopher " << id << " picked up right fork." << endl;

        cout << "philosopher " << id << " is eating" << endl;
        this_thread::sleep_for(chrono::seconds(1));

        forks[right].unlock();
        forks[left].unlock();


    }
}

int main() {
    vector<thread> philosophers;

    for(int i = 0; i < N; i++){
        philosophers.emplace_back(philosopher, i);
    }

    for(auto& t : philosophers){
        t.join();
    }

    return 0;
}