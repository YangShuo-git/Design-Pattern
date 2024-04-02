#ifndef _IOBSERVER_H_
#define _IOBSERVER_H_

class IObserver {
public:
    virtual ~IObserver() = default;
    
    virtual void update(float temp, float humi, float press) = 0;
};

#endif // _IOBSERVER_H_