#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include <iostream>
#include <list>
#include <algorithm>
#include <bitset>
using namespace std;

// 创建Observer接口类，有一个数据更新接口，并且需要传进来一个被观察者Subject、
class Subject;
class Observer {
public:
    Observer(Subject* subject):subject_(subject){}
    virtual ~Observer(){}
    virtual void update()=0;

protected:
    Subject* subject_;
};

// 创建Subject类（被观察者），有一个数据通知接口，和一个观察者列表List
class Subject {
private:
    list<Observer*> observers_;  //观察者
    int state_;                  //状态

public:
    //获取状态
    int GetState()
    {
        return state_;
    }

    //设置状态
    void SetState(int state)
    {
        state_ = state;
        NotifyAllObservers();
    }

    //绑定观察者
    void AttachObserver(Observer* observer)
    {
        observers_.push_back(observer);
    }

    //通知所有观察者
    void NotifyAllObservers()
    {
        for_each(observers_.begin(),observers_.end(),
                 [](Observer* x)
                 {
                     x->update();
                 });
    }
};

// 创建观察者类的实例，实现Observer接口
// 观察者1
class BinaryObserver : public Observer 
{
public:
    BinaryObserver(Subject* subject):Observer(subject)
    {
        subject_->AttachObserver(this);  //通过this，将该观察者绑定到被观察者上
    }
    void update() override 
    {
        cout << "Binary: " << bitset<16>(subject_->GetState()) << endl;
    }
};

// 观察者2
class OctalObserver : public Observer 
{
public:
    OctalObserver(Subject* subject):Observer(subject)
    {
        subject_->AttachObserver(this);
    }

    void update() override 
    {
        cout << "Octal: " << oct << subject_->GetState() << endl;
    }
};

// 观察者3
class HexaObserver : public Observer 
{
public:
    HexaObserver(Subject* subject):Observer(subject)
    {
        subject_->AttachObserver(this);
    }

    void update() override 
    {
        cout << "Hex: " << hex << subject_->GetState() << endl;
    }
};

#endif // _OBSERVER_H_