# 多线程初步学习

up:双笙子佯谬

```
std::cout << std::chrono::steady_clock::now().time_since_epoch().count() << std::endl; //计算机开机时间,平时要用这个来测时间
std::cout << std::chrono::system_clock::now().time_since_epoch().count() << std::endl; //全球时间
std::cout << std::chrono::high_resolution_clock::now().time_since_epoch().count() << std::endl; //全球时间别名
```

