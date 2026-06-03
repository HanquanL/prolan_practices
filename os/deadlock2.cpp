#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex mtx1, mtx2;

void ThreadA(){
    // mtx2.lock();
    mtx1.lock();    //this is the solution
    cout << "Thread A" << endl;
    //mtx1.lock();
    mtx2.lock();    //this is the solution
    mtx2.unlock();
    mtx1.unlock();
}

void ThreadB(){
    mtx1.lock();
    cout << "Thread B" << endl;
    mtx2.lock();
    mtx1.unlock();
    mtx2.unlock();
}

void ExecuteThreads(){
    thread t1( ThreadA );
    thread t2( ThreadB );

    t1.join();
    t2.join();

    cout << "Finished" << endl;
}

int main(){
    ExecuteThreads();
    return 0;   
}