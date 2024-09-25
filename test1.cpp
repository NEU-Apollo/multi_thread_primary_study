#include <mutex>
#include <thread>
#include <vector>
#include <iostream>
#include <string>

std::string a = "hello";
std::mutex mtx_a;

void t1() {
    std::unique_lock<std::mutex> lck(mtx_a);
    a = "world1";
}

void t2() {
    std::unique_lock<std::mutex> lck(mtx_a); //比lock_guard更方便，允许中途调用lck.unlock
    a = "world2";
}   

int main() {
    std::vector<std::thread> pool;
    pool.push_back(std::thread(t1));
    pool.push_back(std::thread(t2));
    for (auto& t : pool) t.join();
    //C++ 20引入jthread，其析构函数中调用join，可以直接通过pool.clear()实现上一行代码一样的功能
    std::cout << a << std::endl;
}