#ifndef _WEATHERDATA_H_
#define _WEATHERDATA_H_

#include "ISubject.h"
#include "IObserver.h"
#include <vector>

class WeatherData : public ISubject {
private:
    std::vector<IObserver> m_observers;
    float m_temp;
    float m_humi;
    float m_press;

public:

    void registerObserver(IObserver*) override {

    }

    void removeObserver(IObserver*) override {

    }

    void notiyObservers() override {

    }

    float getTemperature() {

    }

    float getHumidity() {
        
    }

    float getPressure() {
        
    }

    void measurementsChanged() {
        
    }

};

#endif // _WEATHERDATA_H_