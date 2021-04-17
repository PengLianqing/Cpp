/**
  ****************************(C) COPYRIGHT 2021 Peng****************************
  * @file       原型模式
  * @brief      https://blog.csdn.net/huangjh2017/article/details/78398029
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
#include <map>

/**
  * @brief      原型模式    
  * 用原型实例指定创建对象的种类，并且通过拷贝这些原型创建新的对象。
  */
/**
  * @brief      CPrototype 
  * 基类，实现原型对象的基本操作
  */
class CPrototype
{
public:
	CPrototype() { }
	virtual ~CPrototype() { }
 
	virtual CPrototype *Clone() = 0;
 
	void Display()
	{
		std::cout << "一封信邮件" << std::endl;
		std::cout << "发送者：" << m_strSender << std::endl;
		std::cout << "接收者：" << m_strReceiver << std::endl;
		std::cout << "标  题：" << m_strTitle << std::endl;
		std::cout << "内  容：" << m_strContent << std::endl;
		std::cout << "日  期：" << m_strDate << std::endl;
	}
 
	void setSender(const std::string &strSender)
	{
		m_strSender = strSender;
	}
 
	void setReceiver(const std::string &strReceiver)
	{
		m_strReceiver = strReceiver;
	}
 
	void setTitle(const std::string &strTitle)
	{
		m_strTitle = strTitle;
	}
 
	void setContent(const std::string &strContent)
	{
		m_strContent = strContent;
	}
 
	void setDate(const std::string &strDate)
	{
		m_strDate = strDate;
	}
 
	void setAdjunct(void *pAdjunct)
	{
		m_pAdjunct = pAdjunct;
	}
 
private:
	std::string m_strSender;
	std::string m_strReceiver;
	std::string m_strTitle;
	std::string m_strContent;
	std::string m_strDate;
	void *m_pAdjunct;	//指代附件
};

/**
  * @brief      CConcretePrototype    
  * 派生类，实现原型对象的拷贝
  */
class CConcretePrototype : public CPrototype
{
public:
	CConcretePrototype() { }
	~CConcretePrototype() { }
 
	CPrototype *Clone()
	{
		return new CConcretePrototype(*this);
	}
};

/**
  * @brief      原型管理器    
  * 使用map存取原型对象
  */
class CPrototypeMng
{
public:
	CPrototypeMng() { }
	~CPrototypeMng() { }
 
	void AddPrototype(const std::string &strKey, CPrototype *pPrototype)
	{
		MapPrototype::iterator iter = m_mapPrototypePair.find(strKey);
		if (iter != m_mapPrototypePair.end())
			return;
		m_mapPrototypePair[strKey] = pPrototype;
	}
 
	void DelPrototype(const std::string &strKey, CPrototype *pPrototype)
	{
		MapPrototype::iterator iter = m_mapPrototypePair.find(strKey);
		if (iter == m_mapPrototypePair.end())
			return;
		m_mapPrototypePair.erase(iter);
	}
 
	CPrototype *GetPrototype(const std::string &strKey)
	{
		MapPrototype::iterator iter = m_mapPrototypePair.find(strKey);
		if (iter == m_mapPrototypePair.end())
			return NULL;
 
		return iter->second;
	}
 
private:
	typedef std::map<std::string, CPrototype*> MapPrototype;
	MapPrototype m_mapPrototypePair;
};

int main(void)
{
    // 原型管理器
    CPrototypeMng *pPrototypeMng = new CPrototypeMng();

    // 创建原型实例
	CPrototype *pPrototypeClass = new CConcretePrototype();
	pPrototypeClass->setSender("何总");
	pPrototypeClass->setReceiver("李四");
	pPrototypeClass->setTitle("重要通知");
	pPrototypeClass->setContent("由于临时的变更需要张三和李四去厦门出差！下面是出差的重要事项。。。");
	pPrototypeClass->setDate("2017年11月1日20:50:22");
	pPrototypeClass->setAdjunct(NULL);
	pPrototypeClass->Display();
    pPrototypeMng->AddPrototype("Mail", pPrototypeClass); // 添加到原型管理器
 
 /*
    // 通过原型创建新对象
	CPrototype *pCloneClass = pPrototypeClass->Clone();
	pCloneClass->setReceiver("张三");
	pCloneClass->Display();
*/

    // 从原型管理器中取出原型并根据原型创建新对象
    CPrototype *pCloneClass = pPrototypeMng->GetPrototype("Mail")->Clone();
    pCloneClass->setReceiver("张三");
	pCloneClass->Display();
 
	return 0;
}