#include <iostream>
#include <thread>

using namespace std;

void worker(){
    cout <<"Hello from worker thread!" << endl;
}

int main() {
    thread t(worker);

    cout << "Hello from main thread! " << endl;

    t.join();

    return 0;
}