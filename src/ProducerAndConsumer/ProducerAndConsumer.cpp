#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <iostream>
using namespace std;

class ProducerAndConsumerDemo
{
public:
    void produceNumber();
    void consumeNumber();

private:
    mutex m_mutex;
    condition_variable bufferCanRead;     // 条件变量：可以读数据了
    condition_variable bufferCanWrite;    // 条件变量：可以生产数据了
    
    const int dataSize = 10;    // 产生的总数据量
    queue<int> listBuffer;      // 数据缓存区
    const int bufferSize = 5;   // 缓存区大小
};

void ProducerAndConsumerDemo::produceNumber()
{
    for (int i = 0; i < dataSize; ++i)
    {
        {
            unique_lock<mutex> locker(m_mutex);
            bufferCanWrite.wait(locker, [&]() { return listBuffer.size() < bufferSize; }); // 缓存区满了则阻塞
            listBuffer.push(i);
            cout << "Producer---produce number：" << i << ", bufferSize:" << listBuffer.size() << endl;
        }  // 离开作用域，解锁互斥量

        bufferCanRead.notify_one();  // 通知消费者，可以消费数据
        this_thread::sleep_for(chrono::milliseconds(10));  // 释放cpu占用
    }
}

void ProducerAndConsumerDemo::consumeNumber()
{
    while (true)
    {
        {
            unique_lock<mutex> locker(m_mutex);
            bufferCanRead.wait(locker, [&]() {return !listBuffer.empty(); }); // 缓冲区为空则阻塞
           
            int i = listBuffer.front();
            listBuffer.pop();
            cout << "Consumer---consume number：" << i << ", bufferSize:" << listBuffer.size() << endl;
        }  // 解锁互斥量

        bufferCanWrite.notify_one(); // 通知生产者，可以生产数据
    }
}

int main()
{
    ProducerAndConsumerDemo pcDemo;
    
    thread producerThread(&ProducerAndConsumerDemo::consumeNumber, &pcDemo);
    thread consumerThread(&ProducerAndConsumerDemo::produceNumber, &pcDemo);

    producerThread.join();
    consumerThread.join();

    return 0;
}