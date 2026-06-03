#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <mutex>
#include<algorithm>

using namespace std;

mutex mtx;
double result;

void printResult(int denom)
{
    cout << "for denom = " << denom << ", the result is " << result << endl;
}

void divideByNumber(double num, double denom){
    unique_lock<mutex> lck(mtx);
    try{
        if(denom != 0){
            result = num / denom;
            this_thread::sleep_for(chrono::milliseconds(100));
            printResult(denom);
            lck.unlock();

            std::this_thread::sleep_for(std::chrono::milliseconds(100)); 

            lck.lock();
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
        }else{
            throw std::invalid_argument("Exception from thread: Division by zero!");
        }
    }catch(const std::invalid_argument &e ){
        cout << e.what() << endl;
        return;
    }
}

int main(){
    vector<future<void>> futures;
    for(double i = -5; i < +5; i++){
        futures.emplace_back(async(launch::async, divideByNumber, 50.0, i));
    }

    for_each(futures.begin(), futures.end(), [](future<void> &ftr){
        ftr.wait();
    });

    return 0;
}