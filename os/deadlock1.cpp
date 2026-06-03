#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include<algorithm>

using namespace std;

double result;
mutex mtx;

void printResult(int denom){
    cout << "for denom = " << denom << ", the result is " << result << endl;
}

void divideByNumber(double num, double denom){
    //mtx.lock();    //deadlock solution
    lock_guard<mutex> lck(mtx);    //lock guard solution
    try{
        if(denom != 0){
            result = num / denom;
            this_thread::sleep_for(chrono::milliseconds(1));
            printResult(denom);
        }else{
            throw invalid_argument("Exception from thread: Division by zero!");
        }
    }catch(const invalid_argument &e){
        cout << e.what() << endl;
        return;
    }
    //mtx.unlock();    //deadlock solution
}

int main(){
    vector<future<void>> futures;
    for(double i = -5; i <= +5; ++i){
        futures.emplace_back(async(launch::async, divideByNumber, 50.0, i));
    }

    for_each(futures.begin(), futures.end(), [](future<void> &ftr){
        ftr.wait();
    });

    return 0;
}