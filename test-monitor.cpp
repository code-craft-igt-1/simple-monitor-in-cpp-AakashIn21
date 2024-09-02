#include "./monitor.h"
#include "gtest/gtest.h"

// Test for pure logic functions
TEST(Monitor, TemperatureCritical) {
    EXPECT_TRUE(isTemperatureCritical(102.1)); // Above critical high
    EXPECT_TRUE(isTemperatureCritical(94.9));  // Below critical low
    EXPECT_FALSE(isTemperatureCritical(98.0)); // Within normal range
    EXPECT_FALSE(isTemperatureCritical(95.0)); // At critical low boundary
    EXPECT_FALSE(isTemperatureCritical(102.0)); // At critical high boundary
}

TEST(Monitor, PulseRateOutOfRange) {
    EXPECT_TRUE(isPulseRateOutOfRange(59));   // Below normal range
    EXPECT_TRUE(isPulseRateOutOfRange(101));  // Above normal range
    EXPECT_FALSE(isPulseRateOutOfRange(70));  // Within normal range
    EXPECT_FALSE(isPulseRateOutOfRange(60));  // At lower boundary
    EXPECT_FALSE(isPulseRateOutOfRange(100)); // At upper boundary
}

TEST(Monitor, SpO2OutOfRange) {
    EXPECT_TRUE(isSpO2OutOfRange(89));  // Below normal range
    EXPECT_FALSE(isSpO2OutOfRange(90)); // At lower boundary
    EXPECT_FALSE(isSpO2OutOfRange(95)); // Within normal range
}

TEST(Monitor, VitalsNotOk) {
    EXPECT_FALSE(vitalsOk(103, 70, 95)); // Temperature critical
    EXPECT_FALSE(vitalsOk(98, 55, 95));  // Pulse Rate out of range
    EXPECT_FALSE(vitalsOk(98, 70, 85));  // SpO2 out of range
    EXPECT_FALSE(vitalsOk(103, 55, 85)); // Temperature critical + Pulse Rate out of range
    EXPECT_FALSE(vitalsOk(98, 55, 85));  // Pulse Rate out of range + SpO2 out of range
    EXPECT_FALSE(vitalsOk(103, 55, 85)); // Temperature critical + Pulse Rate out of range + SpO2 out of range
}

TEST(Monitor, VitalsOk) {
    EXPECT_TRUE(vitalsOk(98, 70, 95));  // All within normal ranges
    EXPECT_TRUE(vitalsOk(99, 80, 92));  // All within normal ranges
    EXPECT_TRUE(vitalsOk(95, 60, 90));  // At boundary values
    EXPECT_TRUE(vitalsOk(102, 100, 90)); // At upper boundary for temperature and pulse rate
    EXPECT_TRUE(vitalsOk(95, 60, 95));  // At boundary values for temperature and SpO2
}
