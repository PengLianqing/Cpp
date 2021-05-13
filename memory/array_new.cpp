/**
  ****************************(C) COPYRIGHT 2021 Peng****************************
  * @file       
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
#include <string>

using namespace std;

// new的三种用法：new，array new，placement new

/**
  * @brief          new/delete
  */


/**
  * @brief          array new/delete
  */
class A{
    public :
    int id;
    A():id(0) {cout << "default ctor." << this << "," << id << endl;}
    A( int _id ):id(_id) {cout << "user ctor." << this << "," << id << endl;}
    ~A() {cout << "default dtor." << this << "," << id << endl;}
};
/*
default ctor.0x55a2ab8baeb8,0
default ctor.0x55a2ab8baebc,0
default ctor.0x55a2ab8baec0,0 // 调用默认构造函数初始化array
user ctor.0x55a2ab8baeb8,103
user ctor.0x55a2ab8baebc,70
user ctor.0x55a2ab8baec0,105 // 重新使用用户构造函数初始化
default dtor.0x55a2ab8baec0,105
default dtor.0x55a2ab8baebc,70
default dtor.0x55a2ab8baeb8,103 // 调用析构函数,逆序
*/
void test1(){
    int size = 3;
    A *buf = new A[size]; // 调用默认构造函数初始化array

    A *temp = buf;
    for( int i=0;i<size;++i ){
        new(temp++) A( rand()%128 ); // 重新使用用户构造函数初始化
    }

    delete[] buf; // array delete[]
}

/*
int *buf = new int[size]; 如果创建的是int等类型，没有析构函数，使用delete[] buf 与delete buf效果一样
A *buf = new A[size]; 如果创建的是class，delete[] buf;指定了需要调用多次析构函数，[]不可以省略。
内存布局:
如 int *test = new int[10]; 内存布局为：
## 61h
## Debugger Header(debug模式 32字节)
## int
## int
## ..
## int
## no man land(4字节)
## Pad(malloc填充12字节，需要调整到16的整数倍)
## 61h

如 Demo *test = new Demo[3];
## 61h
## Debugger Header(debug模式 32字节)
## 3 (此处声明有3个对象,内存布局发生了变化)
## Demo
## Demo
## Demo
## no man land(4字节)
## Pad(malloc填充12字节，需要调整到16的整数倍)
## 61h

占用空间:
(32+4) + 4 + 3*12 + (4*2) = 84 -> 96(16的整数倍)
(调试+no man land)  + 对象个数 + 对象占用空间 + 2个61h + 边界调整至16的倍数
*/

/**
  * @brief          placement new/delete
  * 允许将对象创建在已分配的内存中
  */
void test2(){
    char *buf = new char[ sizeof(A) * 3];
    A *a = new(buf) A(2); // 直接在已分配的内存上创建对象,并调用用户构造函数
    delete []buf;
}

/**
  * @brief          重载new与delete 
  */
void *myAlloc( size_t size ){
    return malloc(size);
}

void myFree( void *ptr ){
    return free(ptr);
}

inline void *operator new( size_t size ){
    cout << "operator new( size_t size ) " << endl;
    return myAlloc(size);
}

inline void *operator new[]( size_t size ){
    cout << "operator new[]( size_t size ) " << endl;
    return myAlloc(size);
}

inline void operator delete( void *ptr ){
    cout << "operator delete( void *ptr ) " << endl;
    return myFree(ptr);
}

inline void operator delete[]( void *ptr ){
    cout << "operator delete[]( void *ptr ) " << endl;
    return myFree(ptr);
}

class B{ // 类内重载
    public:
    static void *operator new(size_t);
    static void operator delete(void *,size_t); // size_t可无，static因为函数是在类外调用的
    static void *operator new[](size_t);
    static void operator delete[](void *,size_t);
};
void *B::operator new(size_t size){
    cout << "operator new( size_t size ) " << endl;
    return myAlloc(size);
}

void *B::operator new[](size_t size){
    cout << "operator new[]( size_t size ) " << endl;
    return myAlloc(size);
}

void B::operator delete(void *ptr , size_t size){
    cout << "operator delete( void *ptr , size_t size ) " << endl;
    return myFree(ptr);
}

void B::operator delete[](void *ptr , size_t size){
    cout << "operator delete( void *ptr , size_t size ) " << endl;
    return myFree(ptr);
}

void test3(){
    // 调用类内重载函数
    B *b = new B;
    delete b;

    B *array = new B[5];
    delete[] array;

    // 调用全局函数
    B *b1 = ::new B;
    ::delete (void *)b1;

    B *array1 = ::new B[5];
    ::delete[] array1;
}
int main(){
    
    // test1();

    // test2(); 

    test3();
    
}