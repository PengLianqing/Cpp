/**
  ****************************(C) COPYRIGHT 2021 Peng****************************
  * @file       抽象工厂模式
  * @brief      系统中有多个产品族，每个具体工厂创建同一族但属于不同等级结构的产品。
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
  * 每个基类表示一个族(car、plane)
  */
class Car
{
public:
	Car() {};
	~Car() {};
	virtual void Run() = 0;
};

class Plane
{
    public:
        Plane() {};
        ~Plane() {};
        virtual void Fly() = 0;
};

/**
  * @brief      产品类-派生类   
  * 每个产品具有一个类，产品有族(car、plane)和等级(fast、slow)之分。
  */
class SlowCar : public Car
{
    public:
        void Run() {
            cout << "run slowly" << endl;
        }
    private:
};

class FastCar : public Car
{
    public:
        void Run() {
            cout << "run fast" << endl;
        }
    private:
};

class SlowPlane : public Plane
{
    public:
        void Fly() {
            cout << "fly slowly" << endl;
        }
    private:
};

class FastPlane : public Plane
{
    public:
        void Fly() {
            cout << "fly fast" << endl;
        }
    private:
};

/**
  * @brief      工厂类-基类   
  */
class TrafficFactory
{
    public:
        TrafficFactory() {};
        ~TrafficFactory() {};
        virtual Car* CreateCar() = 0;
        virtual Plane* CreatePlane() = 0;
    private:
};

/**
  * @brief      工厂类-派生类   
  * 每个具体工厂创建同一族但属于不同等级结构的产品。(car、plane)
  */
class SlowTrafficFactory : public TrafficFactory
{
    public:
        Car* CreateCar() {
            return new SlowCar();
        }
        Plane* CreatePlane()
        {
            return new SlowPlane();
        }
    private:
};

class FastTrafficFactory : public TrafficFactory
{
    public:
        Car* CreateCar() {
            return new FastCar();
        }
        Plane* CreatePlane()
        {
            return new FastPlane();
        }
    private:
};

/**
  * @brief      main  
  * Car派生为SlowCar，FastCar;
  * Plane派生为SlowPlane，FastPlane;
  * TrafficFactory派生为SlowTrafficFactory，FastTrafficFactory;
  * 每个工厂可以生产Slow（同一族）的Car和Plane（不同等级结构）产品。
  */
int main()
{
	TrafficFactory* myFac = new SlowTrafficFactory();
	Car* myCar = myFac->CreateCar();
	Plane* myPlane = myFac->CreatePlane();
	myPlane->Fly();
}