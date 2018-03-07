#include <iostream>
#include <mutex>
#include <thread>

#include "thread_local.hpp"

int main(int argc, char * argv[])
{
    std::mutex lock;
    for( uint32_t i = 1; i <= 5; ++i )
    {
        std::thread([i, &lock]{

            //thread local
            static ThreadLocal<std::string> a; 
            std::string & aa = a.GetData(i, 'a');

            //thread singleton
            std::string & b = ThreadLocal<std::string>::Instance(i, 'b'); 

            lock.lock();
            std::cout << "thread " << i << ": " << aa << std::endl;
            std::cout << "thread " << i << ": " << b << std::endl;
            lock.unlock();

            std::this_thread::sleep_for(std::chrono::microseconds(100));

            aa += "================";
            b += "================";

            lock.lock();
            std::cout << "thread " << i << " modified: " << aa << std::endl;
            std::cout << "thread " << i << " modified: " << b << std::endl;
            lock.unlock();

                }).detach();
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return 0;
}
