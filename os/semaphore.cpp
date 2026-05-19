// test result shows failed, need to be revised
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

const int N = 100000;
int counter = 0;

class Semaphore{
    private:
        mutex mtx;
        condition_variable cv;
        int count;

    public:
        explicit Semaphore(int initial_count) : count(initial_count) {}

        void acquire(){
            // p(), wait(), down()
            unique_lock<mutex> lock(mtx);

            while(count == 0){
                cv.wait(lock);
            }

            count--;
        }

        void release(){
            // V(), signal(), up()
            unique_lock<mutex> lock(mtx);

            count++;

            cv.notify_one();
        }
};

Semaphore sem(1);

void worker(){
    for(int i = 1; i < N; i++){
        sem.acquire();

        counter ++;

        sem.release();
    }
}

int main() {
    std::thread t1(worker);
    std::thread t2(worker);

    t1.join();
    t2.join();

    std::cout << "counter = " << counter << std::endl;

    return 0;
}