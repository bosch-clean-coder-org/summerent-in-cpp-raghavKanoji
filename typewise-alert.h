#pragma once
#include <string>

enum class CoolingType {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
};

 enum class BreachType{
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} ;

BreachType inferBreach(double value, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);

enum class AlertTarget {
  TO_CONTROLLER,
  TO_EMAIL
} ;

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

void checkAndAlert(
  AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);

void sendToController(BreachType breachType);
void sendToEmail(std::string str);
