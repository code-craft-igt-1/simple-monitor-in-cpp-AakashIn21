#include "./monitor.h"
#include "EarlyWarning.h"
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

void displayWarning(const std::string& message) {
    cout << Localization::getInstance().getLocalizedMessage(message) << "\n";
    for (int i = 0; i < 6; i++) {
        cout << "\r* " << flush;
        sleep_for(seconds(1));
        cout << "\r *" << flush;
        sleep_for(seconds(1));
    }
}int checkTemperatureRange(float temperature) {
    if (isTemperatureCritical(temperature)) {
        displayWarning("TemperatureCritical");
        return 0;   // Critical condition found
    }
    return 1;   // No issue
}

int checkPulseRange(float pulseRate) {
    if (isPulseRateOutOfRange(pulseRate)) {
        displayWarning("PulseRateOutOfRange");
        return 0;   // Critical condition found
    }
    return 1;   // No issue
}

int checkSPO2range(float spo2) {
    if (isSpO2OutOfRange(spo2)) {
        displayWarning("SpO2OutOfRange");
        return 0;   // Critical condition found
    }
    return 1;   // No issue
}

int checkOutOfRange(float temperature, float pulseRate, float spo2) {
    int tempStatus = checkTemperatureRange(temperature);
    int pulseStatus = checkPulseRange(pulseRate);
    int spo2Status = checkSPO2range(spo2);
    return (tempStatus && pulseStatus && spo2Status);   // Return true only if all are OK
}

void checkTempWarning(float temperature, bool isCelsius) {
    if (!getTemperatureWarningMessage(temperature, isCelsius).empty()) {
        displayWarning("TemperatureWarning");
    }
}
void checkPulseRateWarning(float pulseRate) {
    if (!getPulseRateWarningMessage(pulseRate).empty()) {
        displayWarning("PulseRateWarning");
    }
}
void checkSpO2Warning(float spo2) {
    if (!getSpO2WarningMessage(spo2).empty()) {
        displayWarning("SpO2Warning");
    }
}
int vitalsOk(float temperature, float pulseRate, float spo2, bool isCelsius) {
    if (!checkOutOfRange(temperature, pulseRate, spo2)) {
        return 0;   // Vitals not OK
    }
    checkTempWarning(temperature, isCelsius);
    checkPulseRateWarning(pulseRate);
    checkSpO2Warning(spo2);
    return 1;   // Vitals are OK
}

