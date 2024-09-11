#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include <iostream>
#include <list>
#include <algorithm>
#include <bitset>
using namespace std;


class Subject;

// 创建Observer接口类：构造函数要传入Subject，而且要有数据更新接口
// 为什么要传入Subject呢？保证一创建Observer，Subject就可以调用addObserver方法
class IObserver {
public:
    IObserver(Subject* subject):m_subject(subject){}
    virtual ~IObserver(){}

    virtual void update() = 0;
    virtual void removeFromList() = 0;

protected:
    Subject* m_subject;
};

// 创建Subject类（被观察者）：要有观察者列表，有增删通知观察者的接口
class Subject {
private:
    list<IObserver*> m_observers;  //观察者
    int m_state;                   //状态

public:
    void addObserver(IObserver* observer)
    {
        m_observers.push_back(observer);
    }

    void removeObserver(IObserver* observer)
    {
        m_observers.remove(observer);
    }

    // 通知所有观察者
    void NotifyAllObservers()
    {
        for_each(m_observers.begin(),m_observers.end(),
                 [](IObserver* observer) {
                     observer->update();
                 });
        // 一般写法
        // list<IObserver*>::iterator iter = m_observers.begin();
        // while (iter != m_observers.end()) {
        //     (*iter)->update();
        // }
    }

    // 获取状态
    int GetState()
    {
        return m_state;
    }

    // 设置状态  一设置状态就通知Observer
    void SetState(int state)
    {
        m_state = state;
        NotifyAllObservers();
    }
};

// 创建观察者类的实例，实现Observer接口
class BinaryObserver : public IObserver 
{
public:
    BinaryObserver(Subject* subject):IObserver(subject)
    {
        m_subject->addObserver(this);  //通过this，将该观察者绑定到被观察者上
    }

    void update() override 
    {
        cout << "Binary: " << bitset<16>(m_subject->GetState()) << endl;
    }

    void removeFromList() override 
    {
        m_subject->removeObserver(this);
    }
};

class OctalObserver : public IObserver 
{
public:
    OctalObserver(Subject* subject):IObserver(subject)
    {
        m_subject->addObserver(this);
    }

    void update() override 
    {
        cout << "Octal: " << oct << m_subject->GetState() << endl;
    }

    void removeFromList() override 
    {
        m_subject->removeObserver(this);
    }
};

class HexaObserver : public IObserver 
{
public:
    HexaObserver(Subject* subject):IObserver(subject)
    {
        m_subject->addObserver(this);
    }

    void update() override 
    {
        cout << "Hex: " << hex << m_subject->GetState() << endl;
    }

    void removeFromList() override 
    {
        m_subject->removeObserver(this);
    }
};

#endif // _OBSERVER_H_