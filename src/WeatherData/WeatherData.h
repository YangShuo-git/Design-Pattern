#ifndef _WEATHERDATA_H_
#define _WEATHERDATA_H_

#include "ISubject.h"
#include "IObserver.h"
#include <list>

class WeatherData : public ISubject {
public:
    virtual void addObserver(IObserver* observer) override {
        m_observers.push_back(observer);
    }

    virtual void removeObserver(IObserver* observer) override {
        m_observers.remove(observer);
    }

    virtual void notiyObservers() override {
        for (IObserver* observer : m_observers)
        {
            observer->update(m_temp, m_humi, m_press);
        }
    }

    virtual void setMeasurements(float temp, float humi, float press) override {
        m_temp = temp;
        m_humi = humi;
        m_press = press;

        onMeasurementsChanged();
    }

    void onMeasurementsChanged() {
        notiyObservers();
    }

private:
    std::list<IObserver*> m_observers;
    float m_temp;
    float m_humi;
    float m_press;
};

#endif // _WEATHERDATA_H_