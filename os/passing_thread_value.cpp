#include <iostream>
#include <thread>
#include <future>

using namespace std;

class Vehicle{
    public:
        // default constructor
        Vehicle() : _id(0){
            cout << "Vehicle #" << _id << " Default constructor called" << endl;
        }
        
        // initializing constructor
        Vehicle(int id) : _id(id){
            cout << "Vehicle #" << _id << " Initializing constructor called" << endl;
        }

        // setter and getter
        void setID(int id) { _id = id; }
        int getID() { return _id; }
    
    private:
        int _id;
};

int main(){
    Vehicle v0;
    Vehicle v1(1);

    future<void> ftr = async([](Vehicle v){
        this_thread::sleep_for(chrono::milliseconds(500));
        v.setID(2);
    }, v0);

    v0.setID(3);

    ftr.wait();

    std::cout << "Vehicle #" << v0.getID() << std::endl;

    return 0;
}