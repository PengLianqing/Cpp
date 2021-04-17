/**
  ****************************(C) COPYRIGHT 2021 Peng****************************
  * @file       工厂模式
  * @brief      工厂方法模式对简单工厂模式进行了抽象。有一个抽象的Factory类，
  *             这个类将不再负责具体的产品生产，而是只制定一些规范，具体的生产工作由其子类去完成。
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
  * 产品，一个抽象工厂对应一个抽象产品
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
  * @brief      工厂类-基类   
  */
class CarFactory
{
    public:
        CarFactory() {}
        ~CarFactory() {}
        virtual Car* CreateCar() = 0;
    private:
};

/**
  * @brief      工厂类-派生类   
  * 具体生产产品，一个抽象工厂对应一个抽象产品
  */
class SlowCarFactory : public CarFactory
{
    public:
        Car *CreateCar()
        {
            return new SlowCar();
        }
    private:
};

class FastCarFactory : public CarFactory
{
    public:
        Car *CreateCar()
        {
            return new FastCar();
        }
    private:
};

/**
  * @brief      main  
  * Car派生为SlowCar，FastCar;
  * CarFactory派生为SlowCarFactory，FastCarFactory;
  * 产品与工厂一一对应。
  */
int main()
{
	CarFactory *myFac = new FastCarFactory();
	Car *myCar = myFac->CreateCar();
	myCar->Run();
}