#include<iostream>
#include<thread>
#include<condition_variable>
#include<mutex>
#include<chrono>

int num = 1;
std::condition_variable odd_cv;
std::condition_variable even_cv;
std::mutex mtx;
void PrintOdd(){
    while(true){
        std::unique_lock<std::mutex> m(mtx);
        std::cout<<"线程ID "<<std::this_thread::get_id()<<" nums为"<<num++<<"\n";
        even_cv.notify_one();
        odd_cv.wait(m);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void PrintEven(){
    while(true){
        std::unique_lock<std::mutex> m(mtx);
        std::cout<<"线程ID "<<std::this_thread::get_id()<<" nums为"<<num++<<"\n";
        odd_cv.notify_one();
        even_cv.wait(m);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

int main(int argc, char const *argv[])
{
    std::thread odd_print_func(PrintOdd);
    std::thread even_print_func(PrintEven);
    odd_print_func.join();
    even_print_func.join();
    return 0;
}