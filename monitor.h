#pragma once

const float TEMPERATURE_CRITICAL_HIGH = 102.0f;
const float TEMPERATURE_CRITICAL_LOW = 95.0f;
const float PULSE_RATE_LOW = 60.0f;
const float PULSE_RATE_HIGH = 100.0f;
const float SPO2_CRITICAL_LOW = 90.0f;

bool isTemperatureCritical(float temperature);
bool isPulseRateOutOfRange(float pulseRate);
bool isSpO2OutOfRange(float spo2);
int vitalsOk(float temperature, float pulseRate, float spo2);