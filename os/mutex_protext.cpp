#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include<algorithm>
#include <mutex>

using namespace std;

class Vehicle{
    public:
        Vehicle(int id) : _id(id){}
    private:
        int _id;
};

class WaitingVehicles{
    public:
        //WaitingVehicles() : _tmpVehicles(0){}
        WaitingVehicles() {}

        void printSize(){

            _mtx.lock();
            cout << "#vehicles =  " << _vehicles.size() << endl;
            _mtx.unlock();
        }

        // a vehicle is moved into the vector using an rvalue reference. 
        void pushBakc(Vehicle &&v){
            //_vehicles.push_back(std::move(v)); // data race would cause an exception
            //int oldNum = _tmpVehicles;
            _mtx.lock();
            _vehicles.push_back(std::move(v));
            //this_thread::sleep_for(chrono::milliseconds(1));
            //_tmpVehicles = oldNum + 1;
            _mtx.unlock();
        }
    private:
        vector<Vehicle> _vehicles;
        //int _tmpVehicles;
        mutex _mtx;
};

int main(){
    shared_ptr<WaitingVehicles> queue(new WaitingVehicles);
    vector<future<void>> futures;
    for (int i = 0; i < 1000; i++){
        Vehicle v(i);
                                                  // why pass a method use reference?
        futures.emplace_back(async(launch::async, &WaitingVehicles::pushBakc, queue, move(v)));
    }

    for_each(futures.begin(), futures.end(), [](future<void> &ftr){
        ftr.wait();
    });

    queue -> printSize();

    return 0;
}