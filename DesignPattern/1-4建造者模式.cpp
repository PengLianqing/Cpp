/**
  ****************************(C) COPYRIGHT 2021 Peng****************************
  * @file       建造者模式
  * @brief      https://blog.csdn.net/huangjh2017/article/details/78383389
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
#include <list>

/**
  * @brief      建造者模式    
  * 将一个复杂的对象的构建与它的表示分离，使得同样的构建过程可以创建不同的表示。隐藏了复杂对象的创建过程。
  */
/**
  * @brief      CProudct
  * 获取不同的CBuilder建造者构建出的对象。
  */
class CProudct
{
public:
	CProudct() { }
	~CProudct() { }
 
	void add(std::string strPart)
	{
		m_listParts.push_back(strPart);
	}
 
	void show(void)
	{
		std::cout << "产品创建开始---------" << std::endl;
		for (std::list<std::string>::iterator iter = m_listParts.begin();
			iter != m_listParts.end(); ++iter)
		{
			std::cout << *iter << std::endl;
		}
		std::cout << "产品创建完成---------" << std::endl;
	}
 
private:
	std::list<std::string> m_listParts;
};

/**
  * @brief      CBuilder-基类
  * 为创建一个Product对象的各个部件指定的抽象接口
  */
class CBuilder
{
public:
	CBuilder() { }
	virtual ~CBuilder() { }
 
	virtual void BuilderHead(void) = 0;
	virtual void BuilderBody(void) = 0;
	virtual void BuilderHand(void) = 0;
	virtual void BuilderFoot(void) = 0;
 
	virtual CProudct *GetResult(void)
	{
		return NULL;
	}
};

/**
  * @brief      CxxxxxBuilder-派生类
  * 具体的构建方法
  */
class CConcreteBuilderThin	:	public CBuilder
{
public:
	CConcreteBuilderThin()
	{ 
		try
		{
			m_pProduct = new CProudct();
		}
		catch (std::bad_alloc &ex)
		{
			std::cout << "new CProudct:" << ex.what() << std::endl;
			abort();
		}
	}
 
	~CConcreteBuilderThin()
	{
		delete m_pProduct;
	}
 
	void BuilderHead(void)
	{
		m_pProduct->add("一个瘦的头部形象");
	}
 
	void BuilderBody(void)
	{
		m_pProduct->add("一个瘦的身体形象");
	}
 
	void BuilderHand(void)
	{
		m_pProduct->add("一个瘦的手臂形象");
	}
 
	void BuilderFoot(void)
	{
		m_pProduct->add("一个瘦的腿部形象");
	}
 
	CProudct *GetResult(void)
	{
		return m_pProduct;
	}
 
private:
	CProudct *m_pProduct;
};

class CConcreteBuilderFat : public CBuilder
{
public:
	CConcreteBuilderFat()
	{
		try
		{
			m_pProduct = new CProudct();
		}
		catch (std::bad_alloc &ex)
		{
			std::cout << "new CProudct:" << ex.what() << std::endl;
			abort();
		}
	}
 
	~CConcreteBuilderFat()
	{
		delete m_pProduct;
	}
 
	void BuilderHead(void)
	{
		m_pProduct->add("一个胖的头部形象");
	}
 
	void BuilderBody(void)
	{
		m_pProduct->add("一个胖的身体形象");
	}
 
	void BuilderHand(void)
	{
		m_pProduct->add("一个胖的手臂形象");
	}
 
	void BuilderFoot(void)
	{
		m_pProduct->add("一个胖的腿部形象");
	}
 
	CProudct *GetResult(void)
	{
		return m_pProduct;
	}
 
private:
	CProudct *m_pProduct;
};

/**
  * @brief      CDirector-指挥者
  * 按顺序调用CxxxxxBuilder中的函数，构建出对象。
  */
class CDirector
{
public:
	CDirector() { }
	~CDirector() { }
 
	void Construct(CBuilder *pBuilder)
	{
		if (pBuilder)
		{
			pBuilder->BuilderHead();
			pBuilder->BuilderBody();
			pBuilder->BuilderHand();
			pBuilder->BuilderFoot();
		}
	}
};

int main(void)
{
	CProudct *pPruduct;
	CDirector *pDirector = new CDirector();
	CBuilder *pThinPeople = new CConcreteBuilderThin();
	CBuilder *pFatPeople = new CConcreteBuilderFat();
 
	pDirector->Construct(pThinPeople); // 构建对象
	pPruduct = pThinPeople->GetResult(); // 获取对象
	pPruduct->show();
 
	pDirector->Construct(pFatPeople); // 构建对象
	pPruduct = pFatPeople->GetResult(); // 获取对象
	pPruduct->show();
 
	return 0;
}