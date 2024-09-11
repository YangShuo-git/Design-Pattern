#include "WeatherData.h"
#include "ConditionsDisplay.h"


int main() {
    std::shared_ptr<WeatherData> w = std::make_shared<WeatherData>();

    ConditionsDisplay* displayBJ = new ConditionsDisplay(w, "Beijing");
    ConditionsDisplay* displaySH = new ConditionsDisplay(w, "Shanghai");
    ConditionsDisplay* displaySZ = new ConditionsDisplay(w, "Suzhou");

    displayBJ->subscribeWeatherData();
    displaySH->subscribeWeatherData();
    displaySZ->subscribeWeatherData();

    w->setMeasurements(15, 20, 50);

    displaySH->unSubscribeWeatherData();

    w->setMeasurements(1, 2, 3);

    delete displayBJ;
    delete displaySH;
    delete displaySZ;

    return 0;
}