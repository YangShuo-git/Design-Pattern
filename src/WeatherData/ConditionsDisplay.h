#ifndef _CONDITIONSDISPLAY_H_
#define _CONDITIONSDISPLAY_H_

#include "IObserver.h"
#include "IDisplayElement.h"
#include <memory>
#include <iostream>

class ConditionsDisplay : public IObserver, public IDisplayElement{
private:
    float m_temp;
    float m_humi;
    float m_press;

    std::shared_ptr<ISubject> m_weaterData;

public:
    ConditionsDisplay(std::shared_ptr<ISubject> w) : 
        m_temp(0.0f), m_humi(0.0f), m_press(0.0f), m_weaterData(std::move(w)) {

    }

    ~ConditionsDisplay() {
        if (this != nullptr)
        {
            m_weaterData->removeObserver(this);
        }
    }

    void subscribeWeatherData() {
        m_weaterData->registerObserver(this);
    }

    void unSubscribeWeatherData() {
        m_weaterData->removeObserver(this);
    }

    void update(float temp, float humi, float press) override {
        m_temp = temp;
        m_humi = humi;
        m_press = press;
        
        display();
    }

    void display() {
        std::cout << "Current condidions: \n" 
            << m_temp << "F degrees and \n" 
            << m_humi << "% humidity \n" 
            << m_press << "% pressure \n" 
            << std::endl;
    }
};

#endif // _CONDITIONSDISPLAY_H_