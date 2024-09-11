#include "Observer.h"

/**
 * 1、既是观察者，又是被观察者，怎么实现？
 */

int main()
{
    // 创建Subject
    Subject* subject = new Subject();

    // 创建Observer时，就订阅了Subject
    IObserver* ob1 = new OctalObserver(subject);
    IObserver* ob2 = new BinaryObserver(subject);
    IObserver* ob3 = new HexaObserver(subject);

    ob2->removeFromList();

    // 保证Subject在设置State时，Observer立马能收到通知
    subject->SetState(8);
    cout << " " << endl;
    subject->SetState(10);

    return 0;
}
