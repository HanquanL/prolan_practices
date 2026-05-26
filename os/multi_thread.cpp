#include <iostream>
#include <thread>
#include <vector>

using namespace std;

void printHello(){
    cout << "Hello from worker thread #" << this_thread::get_id() << endl;
}

int main(){
    vector<thread> threads;
    for(size_t i = 0; i < 5; ++i){
         // copying thread objects causes a compile error
        /*
        std::thread t(printHello);
        threads.push_back(t); 
        */

        // moving thread objects
        threads.emplace_back(thread(printHello));
    }

    // do sth in main()
    cout << "Hello from Main thread #" << this_thread::get_id() << endl;

    for(auto &t : threads){
        t.join();
    }

    return 0;
}