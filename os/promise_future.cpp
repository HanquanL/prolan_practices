#include <iostream>
#include <thread>
#include <future>
#include <string>

using namespace std;

void modifyMessage(promise<string> && prms, string message){
    this_thread::sleep_for(chrono::milliseconds(4000));
    string modifiedMessage = message + " has been modified";
    prms.set_value(modifiedMessage);
}

int main(){
    string msgToThread = "My message";

    //create promise and future
    promise<string> prms;
    future<string> ftr = prms.get_future();

    //start thread and pass promise as argument
    thread t(modifyMessage, move(prms), msgToThread);

    //print original message to console
    cout << "Original message from main(): " << msgToThread << endl;

    //retrieve modified message vio future and print to console
    string msgFromThread = ftr.get();
    cout << "Modified message from thread(): " << msgFromThread << endl;

    // thread barrier
    t.join();

    return 0; 
}