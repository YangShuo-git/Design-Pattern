#pragma once
#include <iostream>
 
using namespace std;
 
#include <iostream>
using namespace std;
 
// 抽象游戏类
class Game 
{
public:
	// 游戏加载
	virtual void load() = 0;
 
	// 游戏退出
	virtual void exit() = 0;
};
 
// 真实游戏类-魔兽世界
class WOW : public Game 
{
public:
	// 游戏加载
	virtual void load() {
		cout << "魔兽世界加载。" << endl;
	}
 
	// 游戏退出
	virtual void exit() {
		cout << "魔兽世界退出。" << endl;
	}
};
 
// 代理类-魔兽代理
class ProxyWOW : public Game 
{
public:
	// 构造函数
	ProxyWOW() {
		m_wow = new WOW();
	}
 
	// 析构函数
	virtual ~ProxyWOW() {
		if (m_wow != nullptr) {
			delete m_wow;
			m_wow = nullptr;
		}
	}
 
	// 充值时间
	void recharge(int money) {
		m_time += money / 100;
		cout << "充值：" << money << endl;
		cout << "获得时长：" << m_time << endl;
	}
 
	// 游戏加载
	virtual void load() {
		cout << "代理启动。" << endl;
		if (m_time > 0) {
			m_wow->load();
			cout << "游戏时长1小时。" << endl;
			m_time -= 1;
			cout << "剩余时长：" << m_time << endl;
			flag = true;
		}
		else {
			cout << "剩余游戏时长不足，请充值。" << endl;
			flag = false;
		}
	}
 
	// 游戏退出
	virtual void exit() {
		if (flag) {
			m_wow->exit();
			flag = false;
		}
		cout << "代理关闭。" << endl;
	}
 
private:
	bool flag = false;
	int m_time = 0;
	WOW* m_wow;
};
 