/**
  ****************************(C) COPYRIGHT 2021 Peng****************************
  * @file       装饰模式
  * @brief      https://www.cnblogs.com/cxjchen/p/3161686.html
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
  * @brief      装饰模式   
  */
/**
  * @brief      CVisualComponent-基类 
  */
class CVisualComponent
{
public:
	CVisualComponent() { }
	virtual ~CVisualComponent() { }
 
	virtual void Draw(void) = 0;
};

/**
  * @brief      CTextView-派生类 
  * 实现基础功能。
  */
class CTextView : public CVisualComponent
{
public:
	CTextView() { }
	~CTextView() { }
 
	void Draw(void)
	{
		std::cout << "在窗口中显示正文" << std::endl;
	}
};

/**
  * @brief      CDecorator-装饰类的基类 
  * 继承自CVisualComponent基类，中封装了基类对象的引用。
  */
class CDecorator : public CVisualComponent
{
public:
	CDecorator(CVisualComponent *pComponent)
		:m_pComponent(pComponent)
	{ 
	
	}
	virtual ~CDecorator() { }
 
	virtual void Draw(void)
	{
		if (m_pComponent != NULL)
			m_pComponent->Draw();
	}
 
private:
	CVisualComponent *m_pComponent;
};

/**
  * @brief      CScrollDecorator-装饰类的派生类 
  * 实现功能扩展。
  */
class CScrollDecorator : public CDecorator
{
public:
	CScrollDecorator(CVisualComponent *pComponent, int iWidth)
		:CDecorator(pComponent)
		, m_iWidth(iWidth)
	{
		
	}
	~CScrollDecorator() { }
 
	void Draw(void)
	{
		CDecorator::Draw();
		DrawScroll();
	}
 
private:
	void DrawScroll(void)
	{
		std::cout << "绘制一个宽度为" << m_iWidth << "的滚动条" << std::endl;
	}
 
	int m_iWidth;
};

class CBorderDecorator : public CDecorator
{
public:
	CBorderDecorator(CVisualComponent *pComponent, int iWidth)
		:CDecorator(pComponent)
		,m_iWidth(iWidth)
	{
		
	}
	~CBorderDecorator() { }
 
	void Draw(void)
	{
		CDecorator::Draw();
		DrawBorder();
	}
 
private:
	void DrawBorder(void)
	{
		std::cout << "绘制一个宽度为" << m_iWidth << "的边框" << std::endl;
	}
 
	int m_iWidth;
};

/*
    假定有一个对象TextView，它可以在窗口中显示正文。
    缺省的TextView没有滚动条，因为我们可能有时候不需要滚动条。当需要滚动条时，我们可以用ScrollDecorator添加滚动条。
    如果我们还想在TextView周围添加一个粗黑边框，可以使用BorderDecorator添加。
    因此只要简单地将这些装饰和TextView进行组合就可以达到预期的效果。
    */
int main()
{
    // 基类派生为对象和装饰类，对象实现了基础的功能，装饰类中封装了对对象的引用。
    // 装饰类派生为不同的装饰类对象，实现对基类对象功能的补充。

    // pTextView 实现基础功能
    CVisualComponent *pTextView = new CTextView(); 

    // 引用pTextView，扩充功能
	CVisualComponent *pScrollDecorator = new CScrollDecorator(pTextView, 2); 
    pScrollDecorator->Draw();

    // 引用pScrollDecorator，进一步扩充功能
	CVisualComponent *pBorderDecorator = new CBorderDecorator(pScrollDecorator, 3); 
	pBorderDecorator->Draw();

    return 0;
}