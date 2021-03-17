/**
  ****************************(C) COPYRIGHT 2021 Peng****************************
  * @file       right_quoto.cpp
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

管理线程：
    使用 std::thread::id ， std::this_thread::get_id()标志线程。

    使用vector容器初始化线程并执行回收：
        std::vector< std::thread > threads; // thread对象容器
        for( int i=0; i<10 ;i++){
            threads.push_back( std::thread(f1,i) );
        }
        std::for_each( threads.begin() ,threads.end() ,std::mem_fn( &std::thread::join ) ); // 轮流在每个线程上调用join

    获取可以并发运行的线程数量：
        std::cout << std::thread::hardware_concurrency() << std::endl;
        
*/

#include <iostream>
#include <memory>
#include <thread>

#include <cstring>

#include <stdio.h>
#include <unistd.h>

#include <vector>
#include <functional>
#include <algorithm>

/**
  * @brief          管理线程
  * @retval         none
  */
// 标志线程
std::thread::id master_thread = std::this_thread::get_id(); // 线程标志符，可以用来比较

void f1(unsigned id){
    std::cout << "thread id:" << id << std::endl;
    if( std::this_thread::get_id()==master_thread ){
        std::cout << "master thread." << std::endl;
    }else{
        std::cout << "child thread." << std::endl;
    }
    std::this_thread::sleep_for( std::chrono::milliseconds(10) ); // 延时10ms
}

void vector_thread_test(){

    // 使用vector容器初始化线程并执行回收
    std::vector< std::thread > threads; // thread对象容器
    for( int i=0; i<10 ;i++){
        threads.push_back( std::thread(f1,i) );
    }
    std::for_each( threads.begin() ,threads.end() ,std::mem_fn( &std::thread::join ) ); // 轮流在每个线程上调用join

    // 可以并发运行的线程数量，通常为cpu核心数
    std::cout << std::thread::hardware_concurrency() << std::endl;

    // 通过std::this_thread::get_id()标志线程
    std::cout << master_thread << std::endl; 
    if( std::this_thread::get_id()==master_thread ){
        std::cout << "master thread." << std::endl;
    }else{
        std::cout << "child thread." << std::endl;
    }
}

int main()
{
    
    vector_thread_test();

    std::this_thread::sleep_for( std::chrono::milliseconds(3000) ); // 延时3000ms
    std::cout << "all done." << std::endl;
    
    return 0;
}