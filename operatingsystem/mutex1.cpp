#include<iostream>
#include<thread>
#include<mutex>

using namespace std;

// cv.notify_one() and cv.notify_all() are both used to wake up threads that are waiting 
// on a std::condition_variable, but they differ in how many threads get unblocked.

// cv.notify_one()
// Wakes up exactly one waiting thread.
// The choice of which thread gets woken is unspecified (up to the OS scheduler).

// cv.notify_all()
// Wakes up all threads currently waiting on the condition variable.
// All awakened threads will try to acquire the mutex and check the condition.
// Used when multiple threads can proceed at the same time.

// 💡 Rule of thumb:
// Use notify_one() when only one thread should do the work after the condition is met.
// Use notify_all() when all waiting threads should re-check the condition and 
// potentially proceed.

mutex mx;
condition_variable cv;
int turn = 0;

void job1(){
    unique_lock<mutex> lock(mx);
    while(turn!=0){
        cv.wait(lock);
    }
    cout<<"Job 1 done\n";
    turn =(turn+1)%2;
    cv.notify_all();
}

void job2(){
    unique_lock<mutex> lock(mx);
    while(turn!=1){
        cv.wait(lock);
    }   
    cout<<"Job 2 done\n";
    turn =(turn+1)%2;
    cv.notify_all();
}


int main(int argc, char const *argv[])
{
    thread t1(job1);
    thread t2(job2);

    t2.join();
    t1.join();
    return 0;
}