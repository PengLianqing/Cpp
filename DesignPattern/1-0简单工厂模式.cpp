/**
  ****************************(C) COPYRIGHT 2021 Peng****************************
  * @file       简单工厂模式
  * @brief      定义一个简单工厂类，它可以根据参数的不同返回不同类的实例，
  *             被创建的实例通常都具有共同的父类。
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

/**
  * @brief      产品类-基类   
  * 
  */
class Car
{
    public:
        Car() {}
        ~Car() {}
        virtual void Run() = 0;
    private:
};

/**
  * @brief      产品类-派生类   
  * 
  */
class SlowCar : public Car
{
    public:
        void Run()
        {
            cout << "run slowly" << endl;
        }
};

class FastCar : public Car
{
    public:
        void Run()
        {
            cout << "run fast" << endl;
        }
    private:
};

/**
  * @brief      工厂类 
  * 工厂类对应多个产品类 
  */
class CarFactory
{
    public:
        CarFactory() {}
        ~CarFactory() {}
        Car* CreateCar( int type ){
            Car* car = nullptr;
            switch( type ){
                case 0:
                    car = new SlowCar();
                    break;
                case 1:
                    car = new SlowCar();
                    break;
                default:
                    break;
            }
            return car;
        }
    private:
};

/**
  * @brief      main  
  * Car派生为SlowCar，FastCar;
  * Factory根据参数返回不同类的实例。
  */
int main()
{
	CarFactory *myFac = new CarFactory();
	Car *myCar = myFac->CreateCar( 0 );
	myCar->Run();
}