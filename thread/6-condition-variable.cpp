/**
  ****************************(C) COPYRIGHT 2021 Peng****************************
  * @file      condition-variable.cpp
  * @brief      
  * @note       
  * @history
  *  Version    Date            Author          Modification
  *  V1.0.0     Jan-1-2021      Peng            1. 完成
  *
  @verbatim
  ==============================================================================
  ==============================================================================
  @endverbatim
  ****************************(C) COPYRIGHT 2021 Peng****************************
  */

/* 大纲：
    <condition_variable>
    condition_variable条件变量

    std::mutex mut;
    std::condition_variable data_cond;

    生产者：
    std::lock_guard<std::mutex> lk(mut); // 加锁
    data_cond.notify_one(); // 条件变量通知一个线程

    消费者：
    std::unique_lock<std::mutex> lk(mut); // unique_lock 灵活锁定，线程在等待期间不对mut加锁 
    data_cond.wait( lk , []{    // 阻塞等待条件变量cond满足并解锁信号量；当条件满足，函数返回时，重新加锁信号量
        return !data_queue.empty(); // 还需要满足队列不为空 ,防止多个线程消费完
    } );
    lk.unlock(); // 解锁

    线程安全的queue：
        template<typename T>
        class threadsafe_queue
        {
        private:
            mutable std::mutex mut; // mut
            std::queue<T> data_queue; // queue
            std::condition_variable data_cond; // data_cond
        public:
            threadsafe_queue() {}
            threadsafe_queue(threadsafe_queue const& other) // 拷贝构造
            void push(T new_value) // push ,lock_guard + notify_one实现
            void wait_and_pop(T& value) // wait_and_pop ,unique_lock + wait实现 , 传出参数
            std::shared_ptr<T> wait_and_pop() // wait_and_pop ,unique_lock + wait ,shared_ptr实现
            bool try_pop(T& value) // try_pop ,lock_guard实现
            std::shared_ptr<T> try_pop() // try_pop ,lock_guard ,shared_ptr实现
            bool empty() const // empty ,lock_guard实现
        };
        
*/

#include <boost/thread/lock_types.hpp>
#include <boost/thread/pthread/shared_mutex.hpp>
#include <iostream>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <thread>

// boost shared_mutex 
#include <boost/thread/shared_mutex.hpp>

#include <cstring>

#include <stdio.h>
#include <unistd.h>

#include <vector>
#include <queue>
#include <string>
#include <functional>
#include <algorithm>

/**
  * @brief          condition-variable 
  * @retval         none
  */
std::mutex mut;
std::queue<int> data_queue;
std::condition_variable data_cond;

// 让等待工作的线程休眠，直到有数据处理
void data_product(){
    int i = 100;
    while(i>0){
        i--;
        int data = rand()%128;
        std::this_thread::sleep_for(std::chrono::milliseconds(1)); // 准备数据

        std::lock_guard<std::mutex> lk(mut); // 加锁

        data_queue.push(data);
        std::cout << "produce data:" << data << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        data_cond.notify_one(); // 条件变量通知一个线程
    }
}

void data_process(){
    while(1){
        
        std::unique_lock<std::mutex> lk(mut); // unique_lock 灵活锁定，线程在等待期间不对mut加锁
        
        data_cond.wait( lk , []{    // 阻塞等待条件变量cond满足并解锁信号量；当条件满足，函数返回时，重新加锁信号量
            return !data_queue.empty(); // 还需要满足队列不为空 ,防止多个线程消费完
        } );

        int data = data_queue.front();
        data_queue.pop();
        std::cout << "get data:" << data << std::endl;
        
        lk.unlock(); // 解锁
        
        if(data==-1) break; // 退出
    }
}

void condition_variable_test(){
    // 使用vector容器初始化线程并执行回收
    std::vector< std::thread > threads; // thread对象容器
    for( int i=0; i<20 ;i++){
        threads.push_back( std::thread(data_product) );
        threads.push_back( std::thread(data_process) );
    }
    std::for_each( threads.begin() ,threads.end() ,std::mem_fn( &std::thread::join ) ); // 轮流在每个线程上调用join
}

/**
  * @brief          condition-variable 实现线程安全队列
  * @retval         none
  */
template<typename T>
class threadsafe_queue
{
private:
    mutable std::mutex mut; // mut
    std::queue<T> data_queue; // queue
    std::condition_variable data_cond; // data_cond
public:
    threadsafe_queue()
    {}
    threadsafe_queue(threadsafe_queue const& other) // 拷贝构造
    {
        std::lock_guard<std::mutex> lk(other.mut);
        data_queue=other.data_queue;
    }

    void push(T new_value) // push ,lock_guard + notify_one实现
    {
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(new_value);
        data_cond.notify_one();
    }

    void wait_and_pop(T& value) // wait_and_pop ,unique_lock + wait实现 , 传出参数
    {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk,[this]{return !data_queue.empty();});
        value=data_queue.front();
        data_queue.pop();
    }

    std::shared_ptr<T> wait_and_pop() // wait_and_pop ,unique_lock + wait ,shared_ptr实现
    {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk,[this]{return !data_queue.empty();});
        std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
        data_queue.pop();
        return res;
    }

    bool try_pop(T& value) // try_pop ,lock_guard实现
    {
        std::lock_guard<std::mutex> lk(mut);
        if(data_queue.empty)
            return false;
        value=data_queue.front();
        data_queue.pop();
    }

    std::shared_ptr<T> try_pop() // try_pop ,lock_guard ,shared_ptr实现
    {
        std::lock_guard<std::mutex> lk(mut);
        if(data_queue.empty())
            return std::shared_ptr<T>();
        std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
        data_queue.pop();
        return res;
    }

    bool empty() const // empty ,lock_guard实现
    {
        std::lock_guard<std::mutex> lk(mut);
        return data_queue.empty();
    }
};

threadsafe_queue<int> thq;

void queue_push(){
    int i = 100;
    while(i>0){
        i--;
        int data = rand()%128;
        std::this_thread::sleep_for(std::chrono::milliseconds(1)); // 准备数据

        thq.push(data);
        std::cout << "produce data:" << data << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void queue_pop(){
    while(1){
        int data;
        std::this_thread::sleep_for(std::chrono::milliseconds(1)); 

        // condition_variable效果可以累积，最终所有生产的数据都会被通知到
        
        // thq.wait_and_pop(data); // 传出参数方式
        data = *thq.wait_and_pop(); // shared_ptr方式

        std::cout << "get data:" << data << std::endl;
    }
}

void threadsafe_queue_test(){
    // 使用vector容器初始化线程并执行回收
    std::vector< std::thread > threads; // thread对象容器
    for( int i=0; i<20 ;i++){
        threads.push_back( std::thread(queue_push) );
        threads.push_back( std::thread(queue_pop) );
    }
    std::for_each( threads.begin() ,threads.end() ,std::mem_fn( &std::thread::join ) ); // 轮流在每个线程上调用join
}

int main()
{
    // condition_variable_test();
    threadsafe_queue_test();
    std::this_thread::sleep_for( std::chrono::milliseconds(10) ); // 延时10ms
    std::cout << "all done." << std::endl;
    
    return 0;
}