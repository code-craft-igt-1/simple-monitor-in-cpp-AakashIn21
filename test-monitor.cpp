#include "./monitor.h"
#include "gtest/gtest.h"
#include "Localization.h"

// Initialize translations for different languages
void initializeLocalization() {
    Localization& localization = Localization::getInstance();
    localization.loadTranslations("en", {
        {"TemperatureWarning", "Temperature warning: Approaching hypothermia or hyperthermia"},
        {"TemperatureCritical", "Temperature is critical!"},
        {"PulseRateWarning", "Pulse rate warning"},
        {"PulseRateOutOfRange", "Pulse rate out of range!"},
        {"SpO2Warning", "SpO2 warning"},
        {"SpO2OutOfRange", "SpO2 out of range!"},
        {"TemperatureApproachingHypothermia", "Approaching hypothermia"},
        {"TemperatureApproachingHyperthermia", "Approaching hyperthermia"},
        {"PulseRateApproachingHigh", "Approaching high pulse rate"},
        {"PulseRateApproachingLow", "Approaching low pulse rate"},
        {"SpO2ApproachingLow", "Approaching low SpO2"}
        });

    localization.loadTranslations("de", {
        {"TemperatureWarning", "Temperaturwarnung: Näher an Hypothermie oder Hyperthermie"},
        {"TemperatureCritical", "Temperaturkritisch!"},
        {"PulseRateWarning", "Pulsmessung: Warnung"},
        {"PulseRateOutOfRange", "Pulsmessung außerhalb des Bereichs!"},
        {"SpO2Warning", "Sauerstoffsättigung: Warnung"},
        {"SpO2OutOfRange", "Sauerstoffsättigung außerhalb des Bereichs!"},
        {"TemperatureApproachingHypothermia", "Nähe an Hypothermie"},
        {"TemperatureApproachingHyperthermia", "Nähe an Hyperthermie"},
        {"PulseRateApproachingHigh", "Nähe an hohem Puls"},
        {"PulseRateApproachingLow", "Nähe an niedrigem Puls"},
        {"SpO2ApproachingLow", "Nähe an niedriger SpO2"}
        });

    // Set default language to English for testing
    localization.setLanguage("en");
}

TEST(Monitor, TemperatureCritical) {
    initializeLocalization();
    EXPECT_TRUE(isTemperatureCritical(102.1));   //   Above critical high
    EXPECT_TRUE(isTemperatureCritical(94.9));    //   Below critical low
    EXPECT_FALSE(isTemperatureCritical(98.0));   //   Within normal range
    EXPECT_FALSE(isTemperatureCritical(95.0));   //   At critical low boundary
    EXPECT_FALSE(isTemperatureCritical(102.0));   //   At critical high boundary
}

TEST(Monitor, PulseRateOutOfRange) {
    initializeLocalization();
    EXPECT_TRUE(isPulseRateOutOfRange(59));     //   Below normal range
    EXPECT_TRUE(isPulseRateOutOfRange(101));   //   Above normal range
    EXPECT_FALSE(isPulseRateOutOfRange(70));   //   Within normal range
    EXPECT_FALSE(isPulseRateOutOfRange(60));   //   At lower boundary
    EXPECT_FALSE(isPulseRateOutOfRange(100));   //   At upper boundary
}

TEST(Monitor, SpO2OutOfRange) {
    initializeLocalization();
    EXPECT_TRUE(isSpO2OutOfRange(89));    //   Below normal range
    EXPECT_FALSE(isSpO2OutOfRange(90));   //   At lower boundary
    EXPECT_FALSE(isSpO2OutOfRange(95));   //   Within normal range
}

TEST(Monitor, VitalsNotOk) {
    initializeLocalization();
    EXPECT_FALSE(vitalsOk(103, 70, 95, false));   //   Temperature critical
    EXPECT_FALSE(vitalsOk(98, 55, 95, false));   //   Pulse Rate out of range
    EXPECT_FALSE(vitalsOk(98, 70, 85, false));   //   SpO2 out of range
    EXPECT_FALSE(vitalsOk(103, 55, 85, false));   // Temperature critical + Pulse Rate out of range
    EXPECT_FALSE(vitalsOk(98, 55, 85, false));   //   Pulse Rate out of range + SpO2 out of range
    EXPECT_FALSE(vitalsOk(103, 55, 85, false));
}

TEST(Monitor, VitalsOk) {
    initializeLocalization();
    EXPECT_TRUE(vitalsOk(98, 70, 95, false));   //   All within normal ranges
    EXPECT_TRUE(vitalsOk(99, 80, 92, false));   //   All within normal ranges
    EXPECT_TRUE(vitalsOk(95, 60, 90, false));   //   At boundary values
    EXPECT_TRUE(vitalsOk(102, 100, 90, false));
    EXPECT_TRUE(vitalsOk(95, 60, 95, false));    //   At boundary values for temperature and SpO2
}
