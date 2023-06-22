#include "typewise-alert.h"
#include <stdio.h>
#include <map>
#include <string>

BreachType inferBreach(double value, double upperLimit) {
  BreachType returnVal = BreachType::NORMAL;
  if(value < 0) {
      returnVal = BreachType::TOO_LOW;
  }
  else if(value > upperLimit) {
      returnVal = BreachType::TOO_HIGH;
  }
  return returnVal;
}

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) {
  int upperLimit = 0;
  std::map<CoolingType, int> coolingTypemap;
  coolingTypemap[CoolingType::PASSIVE_COOLING] = 35;
  coolingTypemap[CoolingType::HI_ACTIVE_COOLING] = 45;
  coolingTypemap[CoolingType::MED_ACTIVE_COOLING] = 40;
  
  return inferBreach(temperatureInC, coolingTypemap[coolingType]);
}

void checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(
    batteryChar.coolingType, temperatureInC
  );

  std::map<BreachType, std::string> breachTypemap;
  breachTypemap[BreachType::NORMAL] = " \n";
  breachTypemap[BreachType::TOO_LOW] = "Hi, the temperature is too low\n ";
  breachTypemap[BreachType::TOO_HIGH] = "Hi, the temperature is too high\n ";

  if (alertTarget == AlertTarget::TO_EMAIL)
  {
      sendToEmail(breachTypemap[breachType]);
  }
  else if (alertTarget == AlertTarget::TO_CONTROLLER)
  {
      sendToController(breachType);
  }
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(std::string str) {
  const char* recepient = "a.b@c.com";
  printf("To: %s\n", recepient);
  printf(" %s ", str.c_str());
}
