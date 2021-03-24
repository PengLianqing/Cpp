/**
  ****************************(C) COPYRIGHT 2021 Peng****************************
  * @file      future.cpp
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

    <future>
    
    std::future 一个实例指向一个事件
    std::shared_future 多个实例指向同一个事件
    参考std::unique_ptr,std::shared_ptr实现
    future被用来做线程间通信，但是本身不提供同步访问，需要通过同步机制来保护访问

    std::async 来启动一个std::future对象，std::future最终将持有函数的返回值。
    在future上调用get，线程将阻塞到future就绪。

    std::async 通过指定参数可以实现同步或异步执行，还可以对运行的对象提供参数。
    auto f2 = std::async( std::launch::async , f1 , 1 ); // std::launch::async 在新线程中运行(同步执行)
    auto f3 = std::async( std::launch::deferred , f1 , 2 ); // std::launch::deferred 在get/wait中运行（异步执行）

    在线程之间传递任务 
    std::packaged_task<void()> task(f);  将函数封装成任务包
    std::deque<std::packaged_task<void()> > tasks; 将任务包放入任务包队列
    通过 std::future<void> post_task_for_thread(Func f) （将任务放入队列并返回其future对象）、 void thread()（执行任务队列中的任务） 实现任务的生产、消费

    std::promise / std::future 等待中的线程阻塞future，提供数据的线程使用配对中的promise项，来设置相关的值并使future就绪
    .set_value()传入值 / .set_exception()传入异常
    std::promise<int> pr;
    try{
        pr.set_value();
    }catch(...){
        pr.set_exception();
    }

    通过promise实现单个线程中处理多个连接：
    遍历所有的连接，
    当收到消息时，获取到对应连接的promise，将“连接”的promise设置为接收到的消息，使future就绪；
    当有数据要发送时，从消息队列获取要发送的消息，发送完成后将“消息”的promise设置为true，使future就绪。
    
*/

#include <boost/thread/lock_types.hpp>
#include <boost/thread/pthread/shared_mutex.hpp>
#include <iostream>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <future>
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
  * @brief          std::future 
  * @retval         none
  */
int f(){
    int temp = rand()%128;
    std::cout << "f return " << temp << std::endl;
    std::this_thread::sleep_for( std::chrono::milliseconds(1000) ); // 延时1000ms
    return temp;
}

void future_test(){
    std::future<int> ans = std::async( f ); // std::async启动一个std::future对象,并将结果保存在future对象中
    std::this_thread::sleep_for( std::chrono::milliseconds(10) ); // 延时10ms
    std::cout << "future return" << ans.get() << std::endl; // get会阻塞获取future对象返回值
}

/**
  * @brief          std::async
  * @retval         none
  */
int f1(int x){
    std::cout << "f1 :" << x << std::endl;
    return rand()%128;
}

void async_test(){
    auto f2 = std::async( std::launch::async , f1 , 1 ); // std::launch::async 在新线程中运行(同步执行)
    std::this_thread::sleep_for( std::chrono::milliseconds(10) ); // 延时10ms
    std::cout << "f2 :" << f2.get() << std::endl;
    // f2.wait();
    /*
        f1 :1
        f2 :70
    */

    auto f3 = std::async( std::launch::deferred , f1 , 2 ); // std::launch::deferred 在get/wait中运行（异步执行）
    std::this_thread::sleep_for( std::chrono::milliseconds(10) ); // 延时10ms
    std::cout << "f3 :" << f3.get() << std::endl;
    // f3.wait();
    std::cout << f3.get() << std::endl;
    /*
        f3 :f1 :2
        105
    */

   // 默认或std::launch::async | std::launch::deferred 表示由操作系统具体实现来选择
}

/**
  * @brief          在线程之间传递任务 
  * @retval         none
  */
std::mutex m;
std::deque<std::packaged_task<void()> > tasks;

void thread()
{
    while(1)
    {
        std::packaged_task<void()> task; // 可以将任务封装在std::packaged_task中
        { // 从任务队列tasks中取出任务，并传递给task
            std::lock_guard<std::mutex> lk(m);
            if(tasks.empty())
                continue;
            task=std::move(tasks.front()); 
            tasks.pop_front();
        }
        task(); // 运行task中的任务
    }
}

template<typename Func>
std::future<void> post_task_for_thread(Func f)
{
    std::packaged_task<void()> task(f); // 将传入的函数f创建一个任务包
    std::future<void> res=task.get_future(); // 通过get_future成员函数从任务中获取future
    std::lock_guard<std::mutex> lk(m); 
    tasks.push_back(std::move(task)); // 将任务放入队列
    return res;
}

void f4(){
    int temp = rand()%128;
    std::this_thread::sleep_for( std::chrono::milliseconds(100) ); // 延时100ms
    std::cout << "task runs " << temp << std::endl;
}

void post_thread(){
    int i = 10;
    while(i>0){
        --i;
        post_task_for_thread(f4);
        // std::cout << "task return " << post_task_for_thread(f4).get() << std::endl;
        std::this_thread::sleep_for( std::chrono::milliseconds( rand()%200 ) ); // 延时1000ms
    }
    std::cout << "#####produce done." << std::endl;
}

void packaged_task_test(){
    // 使用vector容器初始化线程并执行回收
    std::vector< std::thread > threads; // thread对象容器
    for( int i=0; i<20 ;i++){
        threads.push_back( std::thread(thread) ); // thread线程执行任务队列中的任务
        threads.push_back( std::thread(post_thread) ); // post_thread用于向任务队列中添加任务
    }
    std::for_each( threads.begin() ,threads.end() ,std::mem_fn( &std::thread::join ) ); // 轮流在每个线程上调用join
}

/*
  * @brief          使用promise在单个线程中处理多个连接 
  * @retval         none
  */
void promise_test(){
    // 遍历所有的连接，
    // 当收到消息时，获取到对应连接的promise，将promise设置为接收到的消息，使future就绪；
    // 当有数据要发送时，从消息队列获取要发送的消息，发送完成后将消息的promise设置为true，使future就绪。
}

int main()
{
    // future_test();
    // async_test();
    packaged_task_test();
    std::this_thread::sleep_for( std::chrono::milliseconds(10) ); // 延时10ms
    std::cout << "all done." << std::endl;
    
    return 0;
}