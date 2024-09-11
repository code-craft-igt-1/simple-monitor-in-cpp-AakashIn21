#pragma once

#include <string>


const float TEMPERATURE_CRITICAL_HIGH = 102.0f;
const float TEMPERATURE_CRITICAL_LOW = 95.0f;
const float PULSE_RATE_LOW = 60.0f;
const float PULSE_RATE_HIGH = 100.0f;
const float SPO2_CRITICAL_LOW = 90.0f;

// Early warning thresholds
const float TEMPERATURE_WARNING_TOLERANCE = 0.015f;   // 1.5%
const float PULSE_RATE_WARNING_TOLERANCE = 0.015f;   // 1.5%
const float SPO2_WARNING_TOLERANCE = 0.015f;         // 1.5%

bool isApproachingHighPulseRate(float pulseRate, float tolerance);
bool isApproachingLowPulseRate(float pulseRate, float tolerance);
bool isApproachingHypothermia(float temperature, float tolerance);
bool isApproachingHyperthermia(float temperature, float tolerance);
bool isWithinHighPulseRateWarning(float pulseRate, float tolerance);
bool isWithinLowPulseRateWarning(float pulseRate, float tolerance);
bool isWithinLowWarning(float temperature, float tolerance);
bool isWithinHighWarning(float temperature, float tolerance);

float calculateTemperatureTolerance(float temperature, bool isCelsius);
bool isTemperatureWarning(float temperature, bool isCelsius);
bool isPulseRateWarning(float pulseRate);
bool isSpO2Warning(float spo2);
std::string getTemperatureWarningMessage(float temperature, bool isCelsius);
std::string getPulseRateWarningMessage(float pulseRate);
std::string getSpO2WarningMessage(float spo2);
