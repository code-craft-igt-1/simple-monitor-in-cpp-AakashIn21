#pragma once

#include <string>
#include "Localization.h"

bool isTemperatureCritical(float temperature);
bool isPulseRateOutOfRange(float pulseRate);
bool isSpO2OutOfRange(float spo2);
int vitalsOk(float temperature, float pulseRate, float spo2, bool isCelsius);
int checkOutOfRange(float temperature, float pulseRate, float spo2);
void checkTempWarning(float temperature, bool isCelsius);
void checkPulseRateWarning(float pulseRate);
void checkSpO2Warning(float spo2);
