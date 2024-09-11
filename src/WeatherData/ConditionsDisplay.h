#ifndef _CONDITIONSDISPLAY_H_
#define _CONDITIONSDISPLAY_H_

#include "IObserver.h"
#include "IDisplayElement.h"
#include <memory>
#include <iostream>
#include <string>

class ConditionsDisplay : public IObserver, public IDisplayElement{
public:
    // 理解move的使用
    ConditionsDisplay(std::shared_ptr<ISubject> w, std::string address) : 
        m_temp(0.0f), 
        m_humi(0.0f), 
        m_press(0.0f), 
        m_address(std::move(address)), 
        m_weaterData(std::move(w)) {
    }

    ~ConditionsDisplay() {
        if (this != nullptr)
        {
            unSubscribeWeatherData();
        }
    }

    void subscribeWeatherData() {
        m_weaterData->addObserver(this);
    }

    void unSubscribeWeatherData() {
        m_weaterData->removeObserver(this);
    }

    virtual void update(float temp, float humi, float press) override {
        m_temp = temp;
        m_humi = humi;
        m_press = press;
        
        display();
    }

    virtual void display() override {
        std::cout << m_address 
            << " Current condidions: \n" 
            << m_temp << "F degrees \n" 
            << m_humi << "% humidity \n" 
            << m_press << "% pressure \n" 
            << std::endl;
    }
    
private:
    std::string m_address;
    float m_temp;
    float m_humi;
    float m_press;

    std::shared_ptr<ISubject> m_weaterData;
};

#endif // _CONDITIONSDISPLAY_H_