#include "Observer.h"

/**
 * 1、既是观察者，又是被观察者，怎么实现？
 */

int main()
{
    // 创建被观察者
    Subject* subject = new Subject();

    // 创建观察者，完成与被观察者的绑定
    Observer* ob1 = new BinaryObserver(subject);
    Observer* ob2 = new OctalObserver(subject);
    Observer* ob3 = new HexaObserver(subject);

    subject->SetState(8);
    subject->SetState(10);

    return 0;
}
