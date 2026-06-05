#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <mutex>
#include <algorithm>

class Vehicle{
    private:
        int _id;
    public:
        Vehicle(int id) : _id(id) {};
        int getID() {return _id; }
};

class WaitingVehicles{
    private:
        std::vector<Vehicle> _vehicles;
        std::mutex _mtx;
    public:
        WaitingVehicles() {};

        void printIDs(){
            std::lock_guard<std::mutex> mylock(_mtx);      // lock is release when mylock goes out of scope
            for(auto &v : _vehicles){
                std::cout << " Vehicle #" << v.getID() << " is now waiting in the queue" << std::endl;
            }
        }

        void pushback(Vehicle &&v){
            //perform vector modification under the lock
            std::lock_guard<std::mutex> ulock(_mtx);
            std::cout << "   Vehicle #" << v.getID() << " will be added to the queue" << std::endl; 
            _vehicles.emplace_back(std::move(v));

            // simulate some work
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
};

int main(){
    // create monitor object as a shared pointer to enable access by multiple threads
    std::shared_ptr<WaitingVehicles> queue(new WaitingVehicles);

    std::cout << "Spawning thread..." << std::endl;
    std::vector<std::future<void>> futures;
    for(int i = 0; i < 10; ++i){
        // create a new Vehicle instance and move it into the queue
        Vehicle v(i);
        futures.emplace_back(std::async(std::launch::async, &WaitingVehicles::pushback, queue, std::move(v)));
    }

    std::for_each(futures.begin(), futures.end(), [](std::future<void> &ftr){
        ftr.wait();
    });

    std::cout << "Vollecting results...." << std::endl;
    queue -> printIDs();

    return 0;
}