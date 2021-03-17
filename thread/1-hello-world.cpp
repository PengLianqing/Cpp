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

线程：
    std::thread对象
    初始化可以传入 函数 或 函数对象 或 λ表达式 []{}。

    th0.join(); // 调用线程,等待线程完成。join行为只能调用一次
    th2.detach(); // 调用线程,不等待线程完成。主线程或函数返回后函数可能访问到被销毁的变量

    使用资源获取即初始化语法 RAII ，通过thread_guard实现线程的自动回收。

    向线程传入参数、移动参数。

*/

#include <iostream>
#include <memory>
#include <thread>

#include <cstring>

#include <stdio.h>
#include <unistd.h>

//  g++ hello-world.cpp -o hello-world -pthread

/**
  * @brief          线程创建
  * @retval         none
  */
void hello(){ // 线程处理函数
    std::cout << "hello-world" << std::endl;
}

class func{ // 仿函数
    public:
        int f;

        func(int f_):f(f_){}

        void operator() (){
            std::cout << "thread " << this->f <<" start." << std::endl;
            std::this_thread::sleep_for( std::chrono::milliseconds(1000) ); // 延时1000ms
            std::cout << "thread " << this->f <<" done." << std::endl;
        }
};

void thread_test(){
    // 新建线程 传入函数
    std::thread th0(hello); 
    th0.join(); // 调用线程,等待线程完成

    // 新建线程 传入lambda(λ)表达式
    std::thread th1( []{
        std::cout << "thread1" <<std::endl;
    } );
    th1.join(); 

    // 新建线程 传入仿函数
    func f( 2 );
    std::thread th2(f);
    th2.detach(); // 调用线程,不等待线程完成

    std::cout << "thread_test done." << std::endl;
}

/**
  * @brief          thread_guard
  * @retval         none
  */
// 使用资源获取即初始化语法 RAII ，提供一个类 ，在析构函数中调用join
class thread_guard{
    std::thread& t; // 引用
    public:
        // 显式构造，防止编译器隐式自动转换
        explicit thread_guard(std::thread& t_) :t(t_) {}

        ~thread_guard() {
            std::cout<< "join" <<std::endl;
            if( t.joinable() ){
                t.join();
            }
        }

        thread_guard(thread_guard const&) = delete; // 不使用拷贝构造
        thread_guard& operator=(thread_guard const&) = delete; // 不重载=
};

void thread_guard_test(){
    func f( 3 );
    std::thread th0(f);
    thread_guard g(th0); // 通过thread_guard实现线程的自动回收
    std::this_thread::sleep_for( std::chrono::milliseconds(3000) ); // 延时3000ms
    std::cout << "thread_guard done." << std::endl;
}

/**
  * @brief          传递参数
  * @retval         none
  */
void f1(int x ,std::string const &s){ // 参数传递：普通传递
    std::cout << x << " " << s << std::endl;
}

class mClass{
    public:
        int x;
};

void f2( std::unique_ptr<mClass> c){ // 移动参数：通过移动构造将对象的所有权在std::unique_ptr实例间转移
    std::cout << c->x << std::endl;
}

void var_test(){

    // 参数传递：普通传递
    std::thread th3(f1 ,3 ,"f3 test"); 
    th3.join(); // 调用线程,等待线程完成

    // 移动参数：通过移动构造将对象的所有权在std::unique_ptr实例间转移
    std::unique_ptr<mClass> c(new mClass); // std::unique_ptr
    c->x = 1;
    // std::thread th( f2 , std::move(c) ); // 将c的所有权转给th线程，之后主线程将无法使用c (引发了段错误)

    std::cout << "var_test done." << std::endl;
}


int main()
{
    // thread_test(); // 测试线程创建
    // thread_guard_test(); // 测试资源获取即初始化语法thread_guard封装线程
    var_test(); // 测试参数传递

    std::this_thread::sleep_for( std::chrono::milliseconds(3000) ); // 延时3000ms
    std::cout << "all done." << std::endl;
    
    return 0;
}