#include <iostream>
#include <thread>
#include <future>
#include <cmath>
#include <memory>

using namespace std;

//void divideByNumber(promise<double> &&prms, double num, double denom){
double divideByNumber(double num, double denom){
    //print system id of worker thread
    cout << "worker thread id = " << this_thread::get_id() << endl;

    this_thread::sleep_for(chrono::milliseconds(500));
    // try{
    //     if(denom == 0){
    //         throw runtime_error("Exception from thread: Division by zero!");
    //     }else{
    //         prms.set_value(num / denom);
    //     }
    // }catch(...){
    //     prms.set_exception(current_exception());
    // }
    if(denom == 0){
        throw runtime_error("Exception from thread: Division by zero!");
    }
    return num / denom;
}

int main(){
    // promise<double> prms;
    // future<double> ftr = prms.get_future();

    // print system id of worker thread
    std::cout << "Main thread id = " << std::this_thread::get_id() << std::endl;

    // use async to start a task
    double num = 42.0, denom = 2.0;
    // thread t(divideByNumber, move(prms), num, denom);
    //synchronously or asynchronously
    //future<double> ftr = async(divideByNumber, num, denom);
    future<double> ftr = async(launch::deferred, divideByNumber, num, denom);

    try{
        double result = ftr.get();
        cout << "Result = " << result << endl;
    }catch(runtime_error e){
        cout << e.what() << endl;
    }

    //t.join();

    return 0;
}