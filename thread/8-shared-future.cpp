/**
  ****************************(C) COPYRIGHT 2021 Peng****************************
  * @file      shared_future.cpp
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
    
std::shared_future 多个实例指向同一个事件
    
    std::promise<int> p;
    std::future<int> f(p.get_future()); // f有效
    std::shared_future<int> sf(std::move(f)); // f不再有效

    直接构造：
    std::shared_future<int> sf( p.get_future() );
    auto sf = p.get_future().share();

有时间限制的等待：
    std::condition_variable::wait_for();
                           ::wait_until();
                           ::wait();
    时钟：
        <chrono>
        std::chrono::system_clock::now(); // 时钟是不匀速的，因为时钟可以调整
        std::chrono::steady_clock(); // 匀速时钟 以均匀速率计时

    基于时间段的等待：
        std::future<int> f=std::async(f);
        if( f.wait_for(std::chrono::milliseconds(35)) == std::future_status::ready ){
            // 35ms内就绪返回std::future_status::ready ， 否则返回std::future_status::deferred
        }

    基于时间点的等待：
        std::condition_variable cv;
        std::mutex m;
        auto const timeout = std::chrono::strady_clock::now() + std::chrono::milliseconds(500);
        std::unique_lock<std::mutex> lk(m);
        if( cv.wait_until(lk,timeout) == std::cv_status::timeout ){

        }
    
*/

/*
通过操作同步简化代码：

    函数式编程风格：FP
        函数调用的结果仅依赖于该函数的参数而不依赖于任何外部的状态。 设计并发时不会碰到共享内存相关的问题。
    eg FP风格（并行）快速排序

    CSP 通信顺序处理：
    线程完全独立，没有共享数据，但是允许消息在它们之间进行传递。
    每个线程等效于状态机，接收到消息时能够根据初始状态进行操作并更新状态；并可以向其他线程发送数据。
    eg ATM实现，处理物理机器、处理ATM逻辑、与银行进行通信三个线程。
    角色模型： 系统中有多个离散的角色，通过相互发送消息来完成自己的任务，除了通过消息传递的状态外，没有任何共享状态。
*/
