/**
  ****************************(C) COPYRIGHT 2021 Peng****************************
  * @file       代理模式
  * @brief      https://www.cnblogs.com/daniels/p/8242592.html
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

/**
  * @brief      代理模式   
  * 
  */
/**
  * @brief      CGraphic-基类 
  * 
  */
class CGraphic
{
public:
	CGraphic() { }
	virtual ~CGraphic() { }
 
	virtual void Draw(void) = 0;
};

/**
  * @brief      CImage-委托类    
  * 
  */
class CImage : public CGraphic
{
public:
	CImage() 
	{
		std::cout << "某个图像对象，创建开销很大，速度慢" << std::endl;
	}
	~CImage() { }
 
	void Draw(void)
	{
		std::cout << "绘制出这个开销很大的图像对象" << std::endl;
	}
};

/**
  * @brief      CImageProxy-代理类   
  * 
  */
class CImageProxy : public CGraphic
{
public:
	CImageProxy()
		:m_pImage(NULL)
	{
		std::cout << "图像Proxy，替代那个真正的图像，创建很快" << std::endl;
	}
	~CImageProxy()
	{
		if (m_pImage)
			delete m_pImage;
	}
 
	void Draw(void)
	{
		try
		{
			if (m_pImage == NULL)
				m_pImage = new CImage();
		}
		catch (std::bad_alloc &ex)
		{
			std::cout << "Throw bad_alloc: " << ex.what() << std::endl;
			abort();
		}
		m_pImage->Draw();
	}
 
private:
	CImage *m_pImage;
};

// 代理类对象和委托类对象都通过基类派生得到。
// 委托类对象实现功能。
// 代理类对象作为委托类对象的代理，负责封装、调用委托类对象，包含一个委托类对象的引用。
int main(void)
{
	//例如这里打开文档，文档里面有个开销很大的对象，该对象并不在文档开始可见,使用代理模式避免上来直接打开的问题
	std::cout << "打开文档——创建图像Proxy" << std::endl;
	CGraphic *pImageProxy = new CImageProxy();
	
    //文档打开后，浏览到该图像对象时再进行绘制
	std::cout << "浏览到该对象——需要创建和绘制" << std::endl;
	pImageProxy->Draw();
 
	return 0;
}