/**
  ****************************(C) COPYRIGHT 2021 Peng****************************
  * @file       share-data.cpp
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

    所有的std::call_once(a_flag, init_A, num );只会执行一次 ，避免了数据的多次初始化。

    对于单一全局实例的场合，可以通过static简化实现同样的效果
        
*/

#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

#include <cstring>

#include <stdio.h>
#include <unistd.h>

#include <vector>
#include <functional>
#include <algorithm>

/**
  * @brief          std::call_once
  * @retval         none
  */
class A{
    
    public:

    int x;

    A(int x_):x(x_) {}
    
};

std::shared_ptr<A> a_ptr;
std::once_flag a_flag;

void init_A( int x ){
    a_ptr.reset( new A(x) );
}

// 所有的std::call_once(a_flag, init_A, num );只会执行一次 
void f(){
    int num = rand()%128;
    std::call_once(a_flag, init_A, num ); // 所有线程只会对init_A调用一次
    std::cout << num << std::endl; 
    std::cout << "a_ptr->x : " << a_ptr->x << std::endl;  // 之后的call_once执行并不会产生效果
}

class B{
    public:
        int x;
        B(int x_):x(x_) {}
};

B& initB(){
    int temp = rand()%128;
    static B b( temp );
    std::cout << "temp : " << temp << std::endl;  // 之后的getb执行并不会产生效果
    return b;
}

void call_once_test(){
    // 使用vector容器初始化线程并执行回收
    std::vector< std::thread > threads; // thread对象容器
    for( int i=0; i<50 ;i++){
        threads.push_back( std::thread(f) );
    }
    std::for_each( threads.begin() ,threads.end() ,std::mem_fn( &std::thread::join ) ); // 轮流在每个线程上调用join

    std::cout << a_ptr->x << std::endl; 

    // 对于单一全局实例的场合，可以通过static简化实现
    // 使用vector容器初始化线程并执行回收
    std::vector< std::thread > threads2;
    for( int i=0; i<50 ;i++){
        threads2.push_back( std::thread( initB ) );
    }
    std::for_each( threads2.begin() ,threads2.end() ,std::mem_fn( &std::thread::join ) ); // 轮流在每个线程上调用join

    std::cout << initB().x << std::endl; 
}


int main()
{
    call_once_test();

    std::this_thread::sleep_for( std::chrono::milliseconds(10) ); // 延时10ms
    std::cout << "all done." << std::endl;
    
    return 0;
}