#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <vector>

using namespace std;


const int BUFFER_SIZE = 5;
const int ITEMS_TO_PRODUCE = 10;

class Semaphore{
    private:
        mutex mtx;
        condition_variable cv;
        int count;
    
    public:
        explicit Semaphore(int initial_count) : count(initial_count) {}

        void acquire() { // P(), wait(), down()
        unique_lock<mutex> lock(mtx);

        cv.wait(lock, [this]() {
            return count > 0;
        });

        --count;
    }

    void release() { // V(), signal(), up()
        {
            lock_guard<mutex> lock(mtx);
            ++count;
        }

        cv.notify_one();
    }
};

vector<int> buffer(BUFFER_SIZE);
int in = 0;
int out = 0;

Semaphore empty_slots(BUFFER_SIZE);
Semaphore full_slots(0);
Semaphore mutex_sem(1);

void producer(){
    for(int item = 1; item <= ITEMS_TO_PRODUCE; item++){
        empty_slots.acquire();    //P(empty): wait for empty slot
        mutex_sem.acquire();    //P(mutex): enter critical region

        buffer[in] = item;
        cout << "Producer produced item " << item
            << " at slot " << in << std::endl;
        in = (in + 1) % BUFFER_SIZE;

        mutex_sem.release();   // V(mutex): leave critical region
        full_slots.release();  // V(full): one more full slot

        this_thread::sleep_for(chrono::seconds(1));
    }
}

void consumer() {
    for (int i = 1; i <= ITEMS_TO_PRODUCE; i++) {
        full_slots.acquire(); // P(full): wait for available item
        mutex_sem.acquire();  // P(mutex): enter critical region

        int item = buffer[out];
        std::cout << "Consumer consumed item " << item
                  << " from slot " << out << std::endl;
        out = (out + 1) % BUFFER_SIZE;

        mutex_sem.release();   // V(mutex): leave critical region
        empty_slots.release(); // V(empty): one more empty slot

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

int main() {
    std::thread p(producer);
    std::thread c(consumer);

    p.join();
    c.join();

    return 0;
}