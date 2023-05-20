#ifndef _PROANDCON_2_H_
#define _PROANDCON_2_H_

#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <iostream>
using namespace std;

class ProAndCon
{
public:
    void produceNumber();
    void consumeNumber();

private:
    mutex proMtx;
    mutex conMtx;
    condition_variable canWrite;
    condition_variable canRead;

    deque<int> dataBuffer;
    const int bufferSize = 10;
    const int number = 50;
    const int waitThreshold = 100;

    int waitCount = 0;
};

void ProAndCon::produceNumber()
{
    auto lastProTime = chrono::high_resolution_clock::now();
    for (int i = 0; i < number; i++)
    {
        unique_lock<mutex> myLock(proMtx);
        auto now = chrono::high_resolution_clock::now();
        auto timeDiff = chrono::duration_cast<chrono::milliseconds>(now - lastProTime).count();
        if (timeDiff < waitThreshold) {
            this_thread::sleep_for(chrono::milliseconds(waitThreshold - timeDiff));
        }

        canWrite.wait(myLock, [&]() {return dataBuffer.size() < bufferSize; });
        dataBuffer.push_back(i);
        cout << "Producer---produce number: " << i << ", bufferSize:" << dataBuffer.size() << endl;
        
        lastProTime = now;
        canRead.notify_one();
    }
}

void ProAndCon::consumeNumber()
{
    while (true)
    {
        unique_lock<mutex> myLock(conMtx);
        canRead.wait(myLock, [&]() {return !dataBuffer.empty(); });
        if (dataBuffer.empty()) {
            break;
        }
        
        int i = dataBuffer.front();
        dataBuffer.pop_front();
        cout << "Consumer---consume number: " << i << ", bufferSize:" << dataBuffer.size() << endl;

        --waitCount;
        if (dataBuffer.size() < bufferSize) {
            canWrite.notify_one();
        }
        else if (waitCount == 0) {
            canRead.wait(myLock);
        }
    }
}

#endif // _PROANDCON_2_H_