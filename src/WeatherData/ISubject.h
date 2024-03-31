#ifndef _ISUBJECT_H_
#define _ISUBJECT_H_

class IObserver;

class ISubject {
public:
    virtual ~ISubject() = default;

    virtual void registerObserver(IObserver*) = 0;
    virtual void removeObserver(IObserver*) = 0;
    virtual void notiyObservers() = 0;
};

#endif // _ISUBJECT_H_