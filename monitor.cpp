#include "./monitor.h"
#include <iostream>
#include <thread>
#include <chrono>
using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

bool isTemperatureCritical(float temperature) {
    return temperature > TEMPERATURE_CRITICAL_HIGH || temperature < TEMPERATURE_CRITICAL_LOW;
}

bool isPulseRateOutOfRange(float pulseRate) {
    return pulseRate < PULSE_RATE_LOW || pulseRate > PULSE_RATE_HIGH;
}

bool isSpO2OutOfRange(float spo2) {
    return spo2 < SPO2_CRITICAL_LOW;
}

// Display on console
void displayWarning(const std::string& message) {
    cout << message << "\n";
    for (int i = 0; i < 6; i++) {
        cout << "\r* " << flush;
        sleep_for(seconds(1));
        cout << "\r *" << flush;
        sleep_for(seconds(1));
    }
}

int vitalsOk(float temperature, float pulseRate, float spo2) {
    if (isTemperatureCritical(temperature)) {
        displayWarning("Temperature is critical!");
        return 0;
    }else if (isPulseRateOutOfRange(pulseRate)) {
        displayWarning("Pulse Rate is out of range!");
        return 0;
    }else if (isSpO2OutOfRange(spo2)) {
        displayWarning("Oxygen Saturation out of range!");
        return 0;
    }
    return 1;
}
