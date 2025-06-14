/**
 * 解析produceNumber
 * 条件变量 canWrite，它会在条件不满足的情况下使线程进入等待状态，并释放locker对m_mutex 的独占锁。
 * 当其他线程对共享资源进行修改并通知了该条件变量时，当前线程会重新获得locker对m_mutex的独占锁并检查条件是否满足，如果满足则继续执行，否则继续等待。
 * 在等待期间，该线程会释放对m_mutex 的独占锁，以允许其他线程对共享资源进行修改。
 * 当条件满足时，该线程会重新获得 m_mutex 的独占锁，并继续往 mQueue 中添加新元素。这样可以避免多个线程同时往共享资源中添加元素导致的数据竞争问题。
 * 
 * 问题：
 * 1.生产者线程和消费者线程使用的是同一个互斥锁 mtx，这可能会导致线程之间的竞争和性能瓶颈
 * 2.当生产者线程生产数据的速度非常快时，消费者线程可能无法及时消费数据，即当 mNumber 较大时，导致 mQueue 的大小超过 bufferSize，会陷入等待状态
 * 3.使用了 this_thread::sleep_for() 函数来释放 CPU 占用，这种方法并不高效，因为它会使线程进入睡眠状态，从而浪费 CPU 资源。
 * 4.在 conThread() 函数中，消费者线程每消费一个数据就会唤醒一个生产者线程，这可能会导致生产者线程的数量过多，从而浪费线程资源。
 * 
 * 改进方案：
 * 1.在 proThread() 函数中，通过计算等待时间来控制生产数据的速度，避免过多的数据被积累。
 *   具体来说，可以在每次生产数据时记录当前时间，然后计算当前时间与上次生产数据的时间差。如果时间差小于一个阈值，则等待一段时间后再生产数据，否则直接生产数据。
 * 2.可以考虑使用 std::yield() 函数或者将生产者线程的优先级设置为较低的方式来释放 CPU 资源，从而提高程序的并发性能。
 * 3.在 conThread() 函数中，记录当前等待消费的数据数量，并在消费数据时根据需要唤醒生产者线程。
 *   具体来说，可以声明一个 waitCount 计数器，记录当前等待消费的数据数量。在消费数据时，将 waitCount 减一，并根据需要唤醒生产者线程。
 *   如果 waitCount 为 0，则表示没有数据需要消费，此时可以将消费者线程挂起等待新的数据到来。
 */

#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <iostream>
using namespace std;

#include "ProAndCon_2.h"

class ProducerAndConsumerDemo
{
public:
    void produceNumber();
    void consumeNumber();

private:
    mutex m_mutex;
    condition_variable mCanRead;     // 条件变量：可以读数据了
    condition_variable mCanWrite;    // 条件变量：可以生产数据了
    
    const int mNumber = 50;        // 要产生的总数据量
    queue<int> mQueue;             // 数据缓存区
    const int mQueueMaxSize = 5;   // 数据缓存区大小
};

void ProducerAndConsumerDemo::produceNumber() {
    for (int i = 0; i < mNumber; ++i) {
        {
            unique_lock<mutex> locker(m_mutex);
            mCanWrite.wait(locker, [&]() { return mQueue.size() < mQueueMaxSize; }); // 队列满了则阻塞（为false时阻塞）
            mQueue.push(i);
            cout << "Producer---produce mNumber: " << i << ", mQueueMaxSize:" << mQueue.size() << endl;
        }  // 离开作用域，解锁互斥量

        mCanRead.notify_one();  // 已经produce data，通知消费者可以消费数据
        this_thread::sleep_for(chrono::milliseconds(10));  // 释放cpu占用 为什么呢？
    }
}

void ProducerAndConsumerDemo::consumeNumber() {
    while (true) {
        {
            unique_lock<mutex> locker(m_mutex);
            mCanRead.wait(locker, [&]() {return !mQueue.empty(); }); // 队列为空则阻塞（不要再消费了）
           
            int i = mQueue.front();
            mQueue.pop();
            cout << "Consumer---consume mNumber: " << i << ", mQueueMaxSize:" << mQueue.size() << endl;
        }

        mCanWrite.notify_one(); // 已经consume data，通知生产者可以生产数据
    }
}

int main() {
    /************************第一阶段***************************/
    ProducerAndConsumerDemo pcDemo;
    
    thread producerThread(&ProducerAndConsumerDemo::consumeNumber, &pcDemo);
    thread consumerThread(&ProducerAndConsumerDemo::produceNumber, &pcDemo);

    producerThread.join();
    consumerThread.join();

    /************************第二阶段***************************/
    // ProAndCon pac;
    
    // thread producerThread(&ProAndCon::produceNumber, &pac);
    // thread consumerThread(&ProAndCon::consumeNumber, &pac);

    // producerThread.join();
    // consumerThread.join();

    return 0;
}