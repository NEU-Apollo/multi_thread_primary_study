#include "mt_queue.h"
#include <iostream>
#include <vector>
#include <thread>

mt_queue<std::optional<int>> counter_queue;

void counter_result(size_t productor_num) {
    int counter = 0;
    int complete_num = 0;
    while(complete_num < productor_num) {
        auto value = counter_queue.pop();
        if(value.has_value()) {
            counter += value.value();
        } else {
            complete_num++;
        }
    }
    std::cout << counter << std::endl;
}

void compute(int begin, int end) {
    for(int i = begin; i < end; i++) {
        counter_queue.push(1);
    }
    counter_queue.push(std::nullopt);
}

int main() {
    std::vector<std::thread> threads;
    constexpr size_t productor_num = 10;
    for(int i=0; i < productor_num; ++i) {
        threads.emplace_back(compute, i * 1000, (i + 1) * 1000 );
    }
    threads.emplace_back(counter_result, productor_num);
    for(auto& t : threads) {
        t.join();
    }
}