#include "EarlyWarning.h"
#include "Localization.h"


bool isWithinLowWarning(float temperature, float tolerance) {
    return temperature >= TEMPERATURE_CRITICAL_LOW &&
        temperature <= (TEMPERATURE_CRITICAL_LOW + tolerance);
}

bool isWithinHighWarning(float temperature, float tolerance) {
    return temperature <= TEMPERATURE_CRITICAL_HIGH &&
        temperature >= (TEMPERATURE_CRITICAL_HIGH - tolerance);
}

bool isTemperatureWarning(float temperature, bool isCelsius) {
    float tolerance = isCelsius ? 1.5f : TEMPERATURE_CRITICAL_HIGH * TEMPERATURE_WARNING_TOLERANCE;
    return isWithinLowWarning(temperature, tolerance) ||
        isWithinHighWarning(temperature, tolerance);
}

bool isWithinHighPulseRateWarning(float pulseRate, float tolerance) {
    return pulseRate >= (PULSE_RATE_HIGH - tolerance) &&
        pulseRate <= PULSE_RATE_HIGH;
}

bool isWithinLowPulseRateWarning(float pulseRate, float tolerance) {
    return pulseRate <= (PULSE_RATE_LOW + tolerance) &&
        pulseRate >= PULSE_RATE_LOW;
}

bool isPulseRateWarning(float pulseRate) {
    float tolerance = PULSE_RATE_HIGH * PULSE_RATE_WARNING_TOLERANCE;
    return isWithinHighPulseRateWarning(pulseRate, tolerance) ||
        isWithinLowPulseRateWarning(pulseRate, tolerance);
}

bool isSpO2Warning(float spo2) {
    float tolerance = SPO2_CRITICAL_LOW * SPO2_WARNING_TOLERANCE;
    return (spo2 >= SPO2_CRITICAL_LOW - tolerance && spo2 <= SPO2_CRITICAL_LOW) ||
        (spo2 < SPO2_CRITICAL_LOW);
}
bool isApproachingHypothermia(float temperature, float tolerance) {
    return temperature >= TEMPERATURE_CRITICAL_LOW &&
        temperature <= (TEMPERATURE_CRITICAL_LOW + tolerance);
}

bool isApproachingHyperthermia(float temperature, float tolerance) {
    return temperature <= TEMPERATURE_CRITICAL_HIGH &&
        temperature >= (TEMPERATURE_CRITICAL_HIGH - tolerance);
}
float calculateTemperatureTolerance(float temperature, bool isCelsius) {
    return isCelsius ? 1.5f : TEMPERATURE_CRITICAL_HIGH * TEMPERATURE_WARNING_TOLERANCE;
}

std::string getTemperatureWarningMessage(float temperature, bool isCelsius) {
    float tolerance = calculateTemperatureTolerance(temperature, isCelsius);

    if (isApproachingHypothermia(temperature, tolerance)) {
        return Localization::getInstance().getLocalizedMessage("TemperatureApproachingHypothermia");
    } else if (isApproachingHyperthermia(temperature, tolerance)) {
        return
            Localization::getInstance().getLocalizedMessage("TemperatureApproachingHyperthermia");
    }
    return "";
}

bool isApproachingHighPulseRate(float pulseRate, float tolerance) {
    return pulseRate >= (PULSE_RATE_HIGH - tolerance) &&
        pulseRate <= PULSE_RATE_HIGH;
}

bool isApproachingLowPulseRate(float pulseRate, float tolerance) {
    return pulseRate <= (PULSE_RATE_LOW + tolerance) &&
        pulseRate >= PULSE_RATE_LOW;
}

std::string getPulseRateWarningMessage(float pulseRate) {
    float tolerance = PULSE_RATE_HIGH * PULSE_RATE_WARNING_TOLERANCE;

    if (isApproachingHighPulseRate(pulseRate, tolerance)) {
        return Localization::getInstance().getLocalizedMessage("PulseRateApproachingHigh");
    } else if (isApproachingLowPulseRate(pulseRate, tolerance)) {
        return Localization::getInstance().getLocalizedMessage("PulseRateApproachingLow");
    }
    return "";
}


std::string getSpO2WarningMessage(float spo2) {
    if (spo2 >=
        (SPO2_CRITICAL_LOW - SPO2_CRITICAL_LOW * SPO2_WARNING_TOLERANCE) &&
        (spo2 <= SPO2_CRITICAL_LOW)) {
        return Localization::getInstance().getLocalizedMessage("SpO2ApproachingLow");
    }
    return "";
}
