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

mutex 互斥元
    std::mutex mut;
    std::lock_guard< std::mutex > guard(mut); // 加锁

    为防止对受保护数据的未受保护访问，不要将受保护数据对象的指针和引用传递到锁的范围之外（无论是从函数中返回、存放在外部可见内存，还是作为参数传递给函数）

    线程安全的stack的实现

    锁定多个互斥元且避免死锁：
        std::lock(lhs.m,rhs.m); // std::lock锁定两个互斥元 当对其中的锁获取失败时，会释放之前获取到的锁
        std::lock_guard<std::mutex> lock_a(lhs.m,std::adopt_lock); // 额外提供一个参数std::adopt_lock给互斥元，告知该对象已被锁定，并且告知沿用互斥元上已有的锁的所有权而不是试图在构造函数中锁定互斥元
        std::lock_guard<std::mutex> lock_b(rhs.m,std::adopt_lock);

    死锁的避免：
        避免嵌套锁（持有锁的情况下申请其它锁），使用更多个锁通过std::lock实现；
        在持有锁时避免调用用户提供的代码；
        以固定顺序申请锁（不使用std::lock的情况下申请多个锁）；
        使用锁层次，对锁封装了层次值。
    
    std::unique_lock 灵活锁定
        占用更多空间，执行略慢。
        std::unique_lock<std::mutex> lock_a(lhs.m,std::defer_lock); // 参数std::defer_lock，保留互斥元为未锁定
        std::unique_lock<std::mutex> lock_b(rhs.m,std::defer_lock);
        std::lock(lhs.m,rhs.m); // std::lock锁定两个互斥元 当对其中的锁获取失败时，会释放之前获取到的锁
        unique_lock可以允许：保留互斥元为未锁定；转移所有权；提前撤回锁（通过unlock成员函数提前释放锁）

*/

#include <exception>
#include <iostream>
#include <memory>
#include <thread>
#include <mutex>

#include <cstring>

#include <stdio.h>
#include <unistd.h>

#include <vector>
#include <list>
#include <functional>
#include <algorithm>

/**
  * @brief          mutex 互斥元
  * @retval         none
  */
std::list<int> l;
std::mutex mut;

void add_to_list(int newvalue){
    
    std::lock_guard< std::mutex > guard(mut);

    l.push_back(newvalue);

}

bool list_contains(int value_to_find){

    std::lock_guard< std::mutex > guard(mut);

    return std::find(l.begin() , l.end() , value_to_find)!=l.end();
}

void f1( int id ){
    static int n = 20;
    while( n-->0 ){
        int new_value = rand()%128;
        add_to_list( new_value );
        std::cout << "f1 thread " << id << ":" <<
            "add " << new_value << std::endl;
        std::this_thread::sleep_for( std::chrono::milliseconds(1) ); // 延时1ms
    }
}

void f2( int id ){
    static int n = 20;
    while( n-->0 ){
        int target = rand()%128;
        std::cout << "f2 thread " << id << ":" <<
            target << "find " << list_contains(target) << std::endl;
        std::this_thread::sleep_for( std::chrono::milliseconds(1) ); // 延时1ms
    }
}

void mutex_test(){

    // 使用vector容器初始化线程并执行回收
    std::vector< std::thread > threads; // thread对象容器
    for( int i=0; i<50 ;i++){
        threads.push_back( std::thread(f1,i) );
        threads.push_back( std::thread(f2,i) );
    }
    std::for_each( threads.begin() ,threads.end() ,std::mem_fn( &std::thread::join ) ); // 轮流在每个线程上调用join

}

/**
  * @brief          线程安全的stack
  * shared_ptr , 封装class threadsafe_stack
  * @retval         none
  */
#include <stack>

struct empty_stack: std::exception{

    const char* what() const throw();
};

template<typename T>
class threadsafe_stack{
    private:
        std::stack<T> data;
        mutable std::mutex m; // mutable关键字 被mutable修饰的变量，将永远处于可变的状态，即使在一个const函数中。
    public:
        threadsafe_stack() {}

        threadsafe_stack( const threadsafe_stack& other ){
            std::lock_guard<std::mutex> lock(other.m); // std::lock_guard<std::mutex> lock 加锁
            data = other.data; // 在构造函数中执行复制
        }

        threadsafe_stack& operator=(const threadsafe_stack& ) = delete; // 不使用赋值操作符

        void push(T new_value){
            std::lock_guard<std::mutex> lock(m);
            data.push(new_value);
        }

        std::shared_ptr<T> pop(){
            std::lock_guard<std::mutex> lock(m);
            if(data.empty()) throw empty_stack(); // 检验是否为空
            std::shared_ptr<T> const res( std::make_shared<T>(data.top()) ); // 使用shared_ptr来处理内存分配，避免new、delete的过多调用
            // shared_ptr 共享对象在最后一个强引用离开的时候释放
            // make_shared 类似于new，提高了效率（std::make_shared申请一个单独的内存块来同时存放Widget对象和控制块。这个优化减少了程序的静态大小，只分配一次内存）
            data.pop();
            return res;
        }

        void pop(T &value){
            std::lock_guard<std::mutex> lock(m);
            if(data.empty()) throw empty_stack();
            value = data.top();
            data.pop();
        }

        bool empty(){
            std::lock_guard<std::mutex> lock(m);
            return data.empty();
        }
};

/**
  * @brief          锁定多个互斥元且避免死锁
  * shared_ptr , 封装class threadsafe_stack
  * @retval         none
  */
class A{
    public:
        int x;
        A(int x_):x(x_){}
};

void swap(A& lhs,A& rhs){
    // std::swap(lhs.x,rhs.x);
    int temp = lhs.x;
    std::this_thread::sleep_for( std::chrono::milliseconds( rand()%10 ) );
    lhs.x = rhs.x;
    std::this_thread::sleep_for( std::chrono::milliseconds( rand()%10 ) );
    rhs.x = temp;
}

class X // X封装了class A和互斥元，实现线程安全的swap
{
private:
    A a;
    mutable std::mutex m;
public:
    X(A const& a_):a(a_){}

    // 不加锁并发调用swap，会导致数据出错
    // 加锁并发调用swap，正确执行
    friend void swap(X& lhs, X& rhs) // lock_guard 方式管理多个锁
    // 友元声明对X的swap，加锁后调用A的swap
    {
        if(&lhs==&rhs)
            return;
        std::lock(lhs.m,rhs.m); // std::lock锁定两个互斥元 当对其中的锁获取失败时，会释放之前获取到的锁
        std::lock_guard<std::mutex> lock_a(lhs.m,std::adopt_lock); // 额外提供一个参数std::adopt_lock给互斥元，告知该对象已被锁定，并且告知沿用互斥元上已有的锁的所有权而不是试图在构造函数中锁定互斥元
        std::lock_guard<std::mutex> lock_b(rhs.m,std::adopt_lock);

        swap(lhs.a,rhs.a);
    }

    friend void swap_ul(X& lhs, X& rhs) // unique_lock 方式管理多个锁
    {
        if(&lhs==&rhs)
            return;
        
        std::unique_lock<std::mutex> lock_a(lhs.m,std::defer_lock); // 参数std::defer_lock，保留互斥元为未锁定
        std::unique_lock<std::mutex> lock_b(rhs.m,std::defer_lock);

        std::lock(lhs.m,rhs.m); // std::lock锁定两个互斥元 当对其中的锁获取失败时，会释放之前获取到的锁

        swap(lhs.a,rhs.a);
    }

    friend void swap_ns(X& lhs, X& rhs) // 不加锁并发调用swap，会导致数据出错
    {
        if(&lhs==&rhs)
            return;
        swap(lhs.a,rhs.a);
    }

    void print(){
        std::cout << a.x << std::endl;
    }
};


X x1(A(10));
X x2(A(5));

void f3( int i ){
    static int n = 50;
    while(n>0){
        swap(x1,x2);
        std::this_thread::sleep_for( std::chrono::milliseconds(1) );
        --n;
    }
}

void multi_mutex_test(){

    x1.print();
    x2.print();

    // 使用vector容器初始化线程并执行回收
    std::vector< std::thread > threads; // thread对象容器
    for( int i=0; i<50 ;i++){
        threads.push_back( std::thread(f3,i) );
    }
    std::for_each( threads.begin() ,threads.end() ,std::mem_fn( &std::thread::join ) ); // 轮流在每个线程上调用join

    x1.print();
    x2.print();
}

/**
  * @brief          unique_lock
  * @retval         none
  */
std::mutex m;
std::unique_lock<std::mutex> f4(){
    
    std::unique_lock<std::mutex> ul(m);
    
    std::this_thread::sleep_for( std::chrono::milliseconds(1) );

    return ul;
}

void f5(){

    std::this_thread::sleep_for( std::chrono::milliseconds(1) );

}

void f6( int num ){
    
    std::unique_lock<std::mutex> lk( f4() ); // 转移锁的所有权
    // f5(); // 不使用锁
    std::cout << "thread " << num << "unlock." << std::endl;
    std::this_thread::sleep_for( std::chrono::milliseconds(50) );
    lk.unlock(); // 通过unlock成员函数提前释放锁
    std::this_thread::sleep_for( std::chrono::milliseconds(50) );
    std::cout << "thread " << num << "done." << std::endl;

    // unique_lock 可以在不需要访问数据的时候调用unlock ， 需要访问的时候再次调用lock
}

void unique_mut_test(){
    // 使用vector容器初始化线程并执行回收
    std::vector< std::thread > threads; // thread对象容器
    for( int i=0; i<50 ;i++){
        threads.push_back( std::thread(f6,i) );
    }
    std::for_each( threads.begin() ,threads.end() ,std::mem_fn( &std::thread::join ) ); // 轮流在每个线程上调用join
}

int main()
{
    
    // mutex_test();
    // multi_mutex_test();
    unique_mut_test();
    // std::this_thread::sleep_for( std::chrono::milliseconds(3000) ); // 延时3000ms
    std::cout << "all done." << std::endl;
    
    return 0;
}