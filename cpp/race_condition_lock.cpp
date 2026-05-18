// demo of race condition and lock guard
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

const int N = 100000;

int counter = 0;
mutex mtx;

void worker(){
    for (int i = 0; i < N; i++){
        //lock_guard<mutex> guard(mtx);    //uncomments this line to test guard
        
        counter++;
    }
}

int main(){
    thread t1(worker);
    thread t2(worker);

    t1.join();
    t2.join();

    cout << "counter = " << counter << endl;

    return 0;
}
