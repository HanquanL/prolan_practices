#include <iostream>
#include <unistd.h>
#include <chrono>
#include <ctime>

using namespace std;

int main() {
    auto now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);
    cout << "process starts running. current time is: "<< currentTime << endl;

    sleep(5);

    auto after_now = chrono::system_clock::now();
    time_t afterTime = chrono::system_clock::to_time_t(after_now);
    cout << "Process runs again after sleep. current time is: "<< afterTime << endl;

    return 0;
}