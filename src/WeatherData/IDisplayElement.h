#ifndef _IDISPLAYELEMENT_H_
#define _IDISPLAYELEMENT_H_

class IDisplayElement {
public:
    virtual ~IDisplayElement() = default;

    virtual void display() = 0;
};

#endif // _IDISPLAYELEMENT_H_