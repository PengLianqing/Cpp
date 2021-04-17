/**
  ****************************(C) COPYRIGHT 2021 Peng****************************
  * @file       any.cpp
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
#include <any>
#include <iostream>
#include <memory>

#include <vector>

using namespace std;

/**
  * @brief          C++17 std::any
  * g++ any.cpp -std=c++2a 指定C++17以上
  */
void stdAnyTest(){

    any a=1,b=string("hello"),c=3.14;
    cout << "type: " << a.type().name() << endl; // a.type()是std::type_info类型
    cout << "value: " << any_cast<int>(a) << endl; // 使用ans_cast必须指定模板参数
    cout << "has_value: " << a.has_value() << endl;
    a.reset(); // 清空any对象
    cout << "has_value: " << a.has_value() << endl;
    a.emplace<string>("hello"); // 修改a的值
    cout << "value: " << any_cast<string>(a) << endl; 
    
    // any使用容器
    vector<any> v;
    v.push_back(a);
    v.push_back(b);
    v.push_back(c);
    for(auto elem:v){
        cout << elem.type().name() << endl;
        // cout << any_cast<int>(elem) << endl;
    }
    
}

/**
  * @brief          通过template模板实现any
  */
class Any {
public:
	template<typename T>
	Any(T t) :base(new Data<T>(t)) {} // 模板构造函数

	template<typename T>
	T _Cast() {
		return dynamic_cast<Data<T>*>(base.get())->value; // base.get()强制转换为Data<T>*
	}
private:
	class Base {
	public:
		virtual ~Base() {} // 确定Base为多态类型
	};

	template <typename T>
	class Data :public Base {
	public:
		Data(T t) :value(t) {}
		T value;
	};

	unique_ptr<Base> base; // 基类指针,通过动态绑定实现any。不能直接使用模板类。
};

void templateAnyTest(){
    Any date( int(10) );
    cout << date._Cast<int>() << endl;
}

/**
  * @brief          通过void*实现any
  */
class A{
    public:
    int x;
    double y;
    string z;
    A(int _x=1,double _y=3.14,string _z="hello"):x(_x),y(_y),z(_z){
        
    }
};

void voidTest(){
    void *any = new A;
    cout << ((A*)any)->x << "," << ((A*)any)->y << "," << ((A*)any)->z << endl;
}

int main(){
    stdAnyTest();
    templateAnyTest();
    voidTest();
    return 0;
}
