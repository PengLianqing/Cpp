/**
  ****************************(C) COPYRIGHT 2021 Peng****************************
  * @file       单例模式
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
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

/*
懒汉式单例模式：声明了一个静态对象，在用户第一个调用时才将自己实例化。(多线程存在线程安全问题)
volatile myMutexSingleton* myMutexSingleton::_instance = nullptr;

饿汉式单例模式：在程序运行（main函数）之前就完成初始化。(线程安全的)
volatile myMutexSingleton* myMutexSingleton::_instance = new myMutexSingleton();

双重锁定式单例模式(检测两次_instance为nullptr):一种使用同步块加锁的方法。
*/

/**
  * @brief      单例模式-双重锁定   
  * 整个程序有且仅有一个实例。该类负责创建自己的对象，同时确保只有一个对象被创建。
  * 通过mutex和volatile实现线程安全，
  * mutex保证一个线程对对象进行初始化，
  * volatile保证不会因为指令重排序导致线程获取到分配了内存但未初始化的对象。
  */
class myMutexSingleton
{
public:
	static volatile myMutexSingleton* getInstance()
	{
		if (!_instance) // 初始化
		{ 
			lock_guard<mutex> tmplock(_myMutex);
			if (!_instance)
			{
				_instance = new myMutexSingleton();
			} 
		}
		return _instance; // 返回单例
	}
protected:
	myMutexSingleton() {};
	~myMutexSingleton() {
		if (_instance)
		{
			lock_guard<mutex> tmplock(_myMutex);
			if (_instance)
			{
				delete _instance;
			}
		}
	};
private:
	static std::mutex _myMutex;
	static volatile myMutexSingleton* _instance; // 全局单例
};

// 初始化静态变量
volatile myMutexSingleton* myMutexSingleton::_instance = nullptr;
std::mutex myMutexSingleton::_myMutex;

int main()
{
    myMutexSingleton::getInstance();
    return 0;
}