#include <iostream>
#include <thread>
#include <future>
#include <cmath>
#include <memory>

using namespace std;

void divideByNumber(promise<double> &&prms, double num, double denom){
    this_thread::sleep_for(chrono::milliseconds(500));
    try{
        if(denom == 0){
            throw runtime_error("Exception from thread: Division by zero!");
        }else{
            prms.set_value(num / denom);
        }
    }catch(...){
        prms.set_exception(current_exception());
    }
}

int main(){
    promise<double> prms;
    future<double> ftr = prms.get_future();

    double num = 42.0, denom = 0.0;
    thread t(divideByNumber, move(prms), num, denom);

    try{
        double result = ftr.get();
        cout << "Result = " << result << endl;
    }catch(runtime_error e){
        cout << e.what() << endl;
    }

    t.join();

    return 0;
}