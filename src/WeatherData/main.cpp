#include "WeatherData.h"
#include "ConditionsDisplay.h"

// 订阅多个subject, 改为onFunction()

int main() {
    std::shared_ptr<WeatherData> w = std::make_shared<WeatherData>();

    ConditionsDisplay* display1 = new ConditionsDisplay(w);
    ConditionsDisplay* display2 = new ConditionsDisplay(w);
    ConditionsDisplay* display3 = new ConditionsDisplay(w);

    display1->subscribeWeatherData();
    display2->subscribeWeatherData();
    display3->subscribeWeatherData();

    w->setMeasurements(15, 20, 50);

    display2->unSubscribeWeatherData();

    w->setMeasurements(1, 2, 3);

    return 0;
}