/**
  ****************************(C) COPYRIGHT 2021 Peng****************************
  * @file       class.cpp
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

using namespace std;

#pragma pack(4) // 指定结构，联合和类的包对齐方式.对齐模数是该数据成员所占内存与#pragma pack指定的数值中的较小者

/**
  * @brief          sizeof测试
  */
class A{ // 类的大小为普通成员变量的大小
    public:
        int a;
        int aFunc(){
            return this->a;
        }
};

class B{ // 空类占用空间为1
    public:
};

class C{ // 静态变量不占用类的内存
    public:
    static int c;
};

class Base
{
    // 16字节，内存模型：
    // 虚函数表：Base::f() base::g() 
    // char
    private:
        char a; // 单独存在占用1字节，定义虚函数后占用8字节（内存对齐）
    public:
        virtual void f(); // 8字节，声明虚函数后会出现虚函数表指针vfptr，且位于内存模型最前端
        virtual void g();
        
};
class D:public Base
{
    // 16字节，内存模型:
    // 虚函数表：D::f() base::g() 
    // char int
    private:
        int b; // 根据内存模型，与a共用了8字节内存
    public:
        void f();
};
class E:public Base
{
    // 32字节，内存模型:
    // 虚函数表：Base::f() E::g() E::h() 
    // char
    // double
    // int
    private:
        double b; // 根据内存模型，b额外占用了8字节内存
        int c; // 根据内存模型，c额外占用了8字节内存(如果c在b之前占用为24字节)
    public:
        void g();
        virtual void h(); 
};
struct F{

};
/*
对于类来说：
与类大小有关的因素：普通成员变量，虚函数，继承（单一继承，多重继承，重复继承，虚拟继承）；
与类大小无关的因素：静态成员变量，静态成员函数及普通成员函数。
空类的大小为1（类可以被实例化所以必然在内存中占有位置），
含有普通成员变量的类，大小为成员变量的大小（需要考虑内存对齐，可以根据变量的定义顺序优化内存占用），
含有虚函数的类，会在内存模型的最前面添加虚函数表指针vfptr（64位8字节），
继承的类，大小为父类大小+子类的大小。
*/
void sizeofTest() {
    /*
    char:1
    short:2
    int:4
    long:8
    float:4
    double:8
    int*:8
  */
  cout << "char:" << sizeof(char) << endl;
  cout << "short:" << sizeof(short) << endl;
  cout << "int:" << sizeof(int) << endl;
  cout << "long:" << sizeof(long) << endl;
  cout << "float:" << sizeof(float) << endl;
  cout << "double:" << sizeof(double) << endl;
  cout << "int*:" << sizeof(int*) << endl;
  cout << "class:" << sizeof(A) << endl;
  cout << "class:" << sizeof(B) << endl;
  cout << "class:" << sizeof(C) << endl;
  cout << "class:" << sizeof(Base) << endl;
  cout << "class:" << sizeof(D) << endl;
  cout << "class:" << sizeof(E) << endl;
  cout << "struct:" << sizeof(F) << endl;
}

int main() {
  sizeofTest();
  return 0;
}