#include <iostream>
#include <thread>
#include <future>

using namespace std;

class Vehicle{
    public:
        Vehicle() : _id(0), _name(new string("Default Name")){
            cout << "Vehicle #" << _id << " Default constructor called" << endl;
        }

        Vehicle(int id, string name) : _id(id), _name(new string(name)){
            cout << "Vehicle #" << _id << " Initializing constructor called" << endl;
        }

        // setter and getter
        void setID(int id) { _id = id; }
        int getID() { return _id; }
        void setName(std::string name) { *_name = name; }
        std::string getName() { return *_name; }

    private:
        int _id;
        string *_name;
};

int main(){
    Vehicle v0;
    Vehicle v1(1, "Vehicle 1");

    future<void> ftr = async([](Vehicle v){
        this_thread::sleep_for(chrono::milliseconds(500));
        v.setName("Vehicle 2");
    }, v0);

    v0.setName("Vehicle 3");

    ftr.wait();
    cout << v0.getName() << std::endl;

    return 0;
}