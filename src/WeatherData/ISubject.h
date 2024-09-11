#ifndef _ISUBJECT_H_
#define _ISUBJECT_H_

class IObserver;

class ISubject {
public:
    virtual ~ISubject() = default;

    virtual void addObserver(IObserver* observer) = 0;
    virtual void removeObserver(IObserver* observer) = 0;
    virtual void notiyObservers() = 0;
    virtual void setMeasurements(float temp, float humi, float press) = 0;
};

#endif // _ISUBJECT_H_