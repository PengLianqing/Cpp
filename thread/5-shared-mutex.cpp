/**
  ****************************(C) COPYRIGHT 2021 Peng****************************
  * @file       shared-mutex.cpp
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
    
    g++ 5-shared-mutex.cpp -o 5-shared-mutex -pthread -lboost_thread

    sudo ldconfig /home/peng/\u4e0b\u8f7d/boost_1_75_0/stage/lib

    boost::shared_mutex 读写互斥元，单个写线程独占访问或共享，多个读线程并发访问
        boost::shared_lock<boost::shared_mutex> sl(sm); // 读，使用boost::shared_lock,可以并发执行
        std::lock_guard<boost::shared_mutex> sl(sm); // 写，使用std::lock_guard，独享

    递归锁 std::recursive_mutex
        
*/

#include <boost/thread/lock_types.hpp>
#include <boost/thread/pthread/shared_mutex.hpp>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

// boost shared_mutex 
#include <boost/thread/shared_mutex.hpp>

#include <cstring>

#include <stdio.h>
#include <unistd.h>

#include <vector>
#include <string>
#include <functional>
#include <algorithm>

/**
  * @brief          boost::shared_mutex 
  * @retval         none
  */
class cache{
    std::map<std::string,int> m;
    mutable boost::shared_mutex sm;
    public:
        int findfromMap(std::string const& str){ // 读，使用boost::shared_lock,可以并发执行
            boost::shared_lock<boost::shared_mutex> sl(sm);
            std::map<std::string,int>::const_iterator const it = m.find(str);
            // std::this_thread::sleep_for( std::chrono::milliseconds(100) );
            return( it==m.end()?-1:it->second );
        }

        void addtoMap(std::string const& str ,int n){ // 写，使用std::lock_guard，独享
            std::lock_guard<boost::shared_mutex> sl(sm);
            // std::this_thread::sleep_for( std::chrono::milliseconds(100) );
            m.insert( {str,n} );
        }
};

cache c;

void f1(){

    std::cout << c.findfromMap("M202070753") << std::endl;

}

void f2(){
    
    c.addtoMap("M2020707"+std::to_string(rand()%64),rand()%64);
    std::cout << "add." << std::endl;

}

void shared_mutex_test(){

    // 使用vector容器初始化线程并执行回收
    std::vector< std::thread > threads; // thread对象容器
    for( int i=0; i<50 ;i++){
        threads.push_back( std::thread(f1) );
        threads.push_back( std::thread(f2) );
    }
    std::for_each( threads.begin() ,threads.end() ,std::mem_fn( &std::thread::join ) ); // 轮流在每个线程上调用join

}

/**
  * @brief          std::recursive_mutex
  * @retval         none
  */
// std::recursive_mutex
// std::lock_guard<std::recursive_mutex>
// std::unique_lock<std::recursive_mutex>

int main()
{
    shared_mutex_test();

    std::this_thread::sleep_for( std::chrono::milliseconds(10) ); // 延时10ms
    std::cout << "all done." << std::endl;
    
    return 0;
}