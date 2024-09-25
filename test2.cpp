#include <mutex>
#include <thread>
#include <vector>
#include <iostream>
#include <string>

std::string a;
std::mutex mtx_a;

void t1() {
    std::unique_lock<std::mutex> lck(mtx_a);
    a = "world1world1world1world1world1world1world1world1world1world1world1world1world1";
}

void t2() {
    // while (a == ""); //可能存在问题：编译器可能优化为 if(a == "") while(true); 未定义行为
    std::unique_lock<std::mutex> lck(mtx_a); //比lock_guard更方便，允许中途调用lck.unlock
    while (a == "") { // 循环等待,占用cpu
        lck.unlock();
        std::this_thread::yield();
        lck.lock();
    }
    std::cout << a << std::endl;
}   

int main() {
    std::vector<std::thread> pool;
    pool.push_back(std::thread(t1));
    pool.push_back(std::thread(t2));
    for (auto& t : pool) t.join();
}