#include <iostream>
#include <thread>

class Vehicle
{
public:
    Vehicle(int id) : _id(id){}
    void operator()()
    {
        std::cout << "Vehicle #" << _id << " has been created" << std::endl;
    }
private:
    int _id;
};


int main()
{
    // create thread 
    //std::thread t0(Vehicle()); // C++'s most vexing parse
    
    //std::thread t1( (Vehicle()) ); // Add an extra pair of parantheses
    
    std::thread t2 = std::thread( Vehicle(1) ); // Use copy initialization
    
    //std::thread t3{ Vehicle() };// Use uniform initialization with braces

    // do something in main()
    std::cout << "Finished work in main \n";

    // wait for thread to finish
    //t1.join();
    t2.join();
    //t3.join();

    return 0;
}