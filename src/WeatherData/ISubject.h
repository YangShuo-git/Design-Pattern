#ifndef _ISUBJECT_H_
#define _ISUBJECT_H_

class ISubject {
public:
    virtual void registerObserver() = 0;
    virtual void removeObserver() = 0;
    virtual void notiyObservers() = 0;
};

#endif // _ISUBJECT_H_