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
        //int _numVehicles;
        std::condition_variable _cond;
    public:
        WaitingVehicles() {};

        // int getNumVehicles(){
        //     std::lock_guard<std::mutex> ulock(_mtx);
        //     return _numVehicles;
        // }

        bool dataIsAvailable(){
            std::lock_guard<std::mutex> mylock(_mtx);
            return !_vehicles.empty();
        }
        // void printIDs(){
        //     std::lock_guard<std::mutex> mylock(_mtx);      // lock is release when mylock goes out of scope
        //     for(auto &v : _vehicles){
        //         std::cout << " Vehicle #" << v.getID() << " is now waiting in the queue" << std::endl;
        //     }
        // }
        Vehicle popBack(){
            // perform vector modification under the lock
            //std::lock_guard<std::mutex> ulock(_mtx);
            std::unique_lock<std::mutex> ulock(_mtx);
            _cond.wait(ulock, [this]{ return !_vehicles.empty();});    // pass unique lock to condition variable
            // remove last vector element from queue
            Vehicle v = std::move(_vehicles.back());
            _vehicles.pop_back();
            //--_numVehicles;
            return v;    // will not be copied due to return value optimization (RVO) in c++
        }

        void pushback(Vehicle &&v){
            // simulate some work
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            //perform vector modification under the lock
            std::lock_guard<std::mutex> ulock(_mtx);
            std::cout << "   Vehicle #" << v.getID() << " will be added to the queue" << std::endl; 
            _vehicles.emplace_back(std::move(v));
            _cond.notify_one();
            //++_numVehicles;
            // simulate some work
            // std::this_thread::sleep_for(std::chrono::milliseconds(500));
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


    std::cout << "ollecting results...." << std::endl;
    // queue -> printIDs();
    while(true){
        // if(queue -> dataIsAvailable()){
            Vehicle v = queue -> popBack();
            std::cout << " Vehicle #" << v.getID() << " has been removed from the queue" << std::endl;

        //     if(queue -> getNumVehicles() <= 0){
        //         std::this_thread::sleep_for(std::chrono::milliseconds(200));
        //         break;
        //     }
        // }
    }

    std::for_each(futures.begin(), futures.end(), [](std::future<void> &ftr){
        ftr.wait();
    });

    //std::cout << "Finished : " << queue->getNumVehicles() << " vehicle(s) left in the queue" << std::endl;
    std::cout << "Finished!" << std::endl;

    return 0;
}