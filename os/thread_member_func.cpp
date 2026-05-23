#include <iostream>
#include <thread>

using namespace std;

class Vehicle{
    public:
        Vehicle() : _id(0) {}
        void addID(int id) { _id = id;}
        void printID(){
            cout << "Vehicle ID = " << _id << endl;
        }
    
    private:
        int _id;
};

int main(){

    // Vehicle v1,v2;
    Vehicle v1;
    shared_ptr<Vehicle> v2 (new Vehicle);
    thread t1 = thread(&Vehicle::addID, v1, 1);
    //thread t2 = thread(&Vehicle::addID, &v2, 2);
    thread t2 = thread(&Vehicle::addID, v2, 1);

    t1.join();
    t2.join();

    v1.printID();
    //v2.printID();
    v2 ->printID();

    return 0;
}