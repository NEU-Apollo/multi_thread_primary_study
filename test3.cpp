#include <mutex>
#include <thread>
#include <vector>
#include <iostream>
#include <string>
#include <condition_variable>
#include <chrono>
#include <semaphore.h>

std::string a;
std::mutex mtx_a;
std::condition_variable cv_a;

void t1() {
    std::unique_lock<std::mutex> lck(mtx_a);
    a = "world1world1world1world1world1world1world1world1world1world1world1world1world1";
    cv_a.notify_all();
}

void t2() {
    std::unique_lock<std::mutex> lck(mtx_a); //比lock_guard更方便，允许中途调用lck.unlock
    // while (a == "") { 
    //     lck.unlock();
    //     cv_a.wait(lck);
    //     lck.lock();
    // }

    // while (a == "") { 
    //     cv_a.wait(lck); //这种的必须配合一个while循环来用
    // } //和上面一样，wait(lck)直接完成了unlock和lock的功能  

    cv_a.wait(lck,[&](){return a != "";}); // 把while循环也封装了起来

    // 下面这俩都是等一秒拿不到就继续执行
    // cv_a.wait_for(lck, std::chrono::seconds(1), [&](){return a != "";});
    // cv_a.wait_until(lck, std::chrono::system_clock::now() + std::chrono::seconds(1), [&](){return a != "";});
    std::cout << a << std::endl;
}   

int main() {
    std::vector<std::thread> pool;
    pool.push_back(std::thread(t1));
    pool.push_back(std::thread(t2));
    for (auto& t : pool) t.join();
}