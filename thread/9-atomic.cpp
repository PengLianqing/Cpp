/**
  ****************************(C) COPYRIGHT 2021 Peng****************************
  * @file      atomic.cpp
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

    <atomic>

    load();
    store();
    exchange(); // 读 修改 写
    compare_exchange_strong(); // 比较 交换，返回bool
    fetch_add();
    fetch_sub();
    fetch_and();
    fetch_or();
    fetch_xor();
    
    载入、储存、交换、比较/交换操作

    六种内存顺序；
    三种模型：顺序一致顺序（线程必须和时间顺序一致），
    非顺序一致的内存顺序（所有线程对独立变量的修改顺序一致），
    松散顺序（同一个线程对单个原子变量的访问不能重排），
    获得释放顺序（不同线程可以看到不同的排序，但这些顺序是受到限制的），原子载入是获取操作，原子储存是释放操作

    屏障：
    std::atomic_thread_fense( std::memory_order_release );
    std::atomic_thread_fense( std::memory_order_acquire );

    *使用原子操作排序非原子操作

*/
#include <atomic>
#include <thread>
#include <assert.h>

/**
  * @brief          使用原子操作排序非原子操作
  * @retval         none
  */
bool x=false;
std::atomic<bool> y;
std::atomic<int> z;

void write_x_then_y()
{
    std::this_thread::sleep_for( std::chrono::milliseconds(1) ); // 延时1ms

    std::atomic_thread_fence(std::memory_order_release); // 设置屏障

    y.store(true,std::memory_order_relaxed); // 在屏障后储存y

    x=true; // 在屏障前储存x
}

void read_y_then_x()
{
    while(!y.load(std::memory_order_relaxed)); // 等待y

    std::atomic_thread_fence(std::memory_order_acquire); // 解除屏障

    if(x) // 保证此处读取到的是write_x_then_y写入的值
        ++z;
}

int main()
{
    x=false;
    y=false;
    z=0;
    std::thread a(write_x_then_y);
    std::thread b(read_y_then_x);
    a.join();
    b.join();
    assert(z.load()!=0); // 断言z不为0
}
