/*
建造者模式
组装电脑：显示器  主机  键盘  鼠标
*/
#ifndef _BUILDER_COMPUTER_H_
#define _BUILDER_COMPUTER_H_

#include <string>
#include <vector>
#include <iostream>
using namespace std;

// 1. 抽象产品类
class AbstractProduct
{
public:
    virtual ~AbstractProduct(){};
    virtual void setDisplay(string display) = 0;
    virtual void setHost(string host) = 0;
	virtual void setKeyBoard(string KeyBoard) = 0;
	virtual void setMouse(string mouse) = 0;

	virtual void show() = 0;
};

// 2. 具体产品类
class ComputerA:public AbstractProduct
{
public:
    ~ComputerA(){};
	void setDisplay(string display)
	{
		m_vec.emplace_back(display);
	}
	void setHost(string host)
	{
		m_vec.emplace_back(host);
	}
	void setKeyBoard(string KeyBoard)
	{
		m_vec.emplace_back(KeyBoard);
	}
	void setMouse(string mouse)
	{
		m_vec.emplace_back(mouse);
	}
	void show()
	{
		cout << "----------开始组装电脑A---------" << endl;
		for (auto& it : m_vec)
		{
			cout << it << endl;
		}
		cout << "----------成功组装电脑A---------" << endl;
	}

private:
    vector<string> m_vec;
};

// 3. 抽象建造者类
class AbstractBuilder
{
public:
	// 创建电脑产品
	AbstractBuilder():product(new ComputerA) {}
	virtual ~AbstractBuilder() {}

	// 抽象电脑产品创建的统一抽象接口
	virtual void BuildDisplay(string display) = 0;
	virtual void BuildHost(string host) = 0;
	virtual void BuildKeyBoard(string KeyBoard) = 0;
	virtual void BuildMouse(string mouse) = 0;

	AbstractProduct* getProduct()
	{
		return product;
	}

protected:
	AbstractProduct* product;
};

// 4. 具体建造者：具体实现抽象建造者各个部件的接口
class ComputerBuilder :public AbstractBuilder
{
public:
	~ComputerBuilder() {}
	void BuildDisplay(string display)
	{
		product->setDisplay(display);
	}
	void BuildHost(string host)
	{
		product->setHost(host);
	}
	void BuildKeyBoard(string KeyBoard)
	{
		product->setKeyBoard(KeyBoard);
	}
	void BuildMouse(string mouse)
	{
		product->setMouse(mouse);
	}
};

// 5. 管理者：安排和调度复杂对象的创建过程
class Manager
{
public:
	Manager(AbstractBuilder* builder):m_builder(builder) {}
	~Manager() {}
	
	AbstractProduct* createComputer(string display, string host, string KeyBoard, string mouse)
	{
		m_builder->BuildDisplay(display);
		m_builder->BuildHost(host);
		m_builder->BuildKeyBoard(KeyBoard);
		m_builder->BuildMouse(mouse);
		return m_builder->getProduct();
	}
private:
	AbstractBuilder* m_builder;
};


#endif // _BUILDER_COMPUTER_H_