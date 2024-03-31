#ifndef _CONDITIONSDISPLAY_H_
#define _CONDITIONSDISPLAY_H_

#include "IObserver.h"

class ConditionsDisplay : public IObserver {
public:
    void update(float temp, float humidity, float pressure) override {

    }
};

#endif // _CONDITIONSDISPLAY_H_