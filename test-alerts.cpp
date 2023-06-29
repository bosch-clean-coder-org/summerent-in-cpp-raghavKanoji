#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "./test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to Low Limit") {
	REQUIRE(inferBreach(-1, 30) == BreachType::TOO_LOW);
}

TEST_CASE("infers the breach according to High limits") {
	REQUIRE(inferBreach(32, 30) == BreachType::TOO_HIGH);
}

TEST_CASE("infers the breach according to Normal limits") {
	REQUIRE(inferBreach(-24, -30) == BreachType::TOO_LOW);
}

TEST_CASE("infers the breach boundry check") {
	REQUIRE(inferBreach(24, 30) == BreachType::NORMAL);
}

TEST_CASE("classifyTemperatureBreach CoolingType is PASSIVE_COOLING and temp is normal") {
	REQUIRE(classifyTemperatureBreach(CoolingType::PASSIVE_COOLING, 25) == BreachType::NORMAL);
}

TEST_CASE("classifyTemperatureBreach CoolingType is HI_ACTIVE_COOLING and temp is normal") {
	REQUIRE(classifyTemperatureBreach(CoolingType::HI_ACTIVE_COOLING, 25) == BreachType::NORMAL);
}

TEST_CASE("classifyTemperatureBreach CoolingType is MED_ACTIVE_COOLING and temp is normal") {
	REQUIRE(classifyTemperatureBreach(CoolingType::MED_ACTIVE_COOLING, 25) == BreachType::NORMAL);
}

TEST_CASE("classifyTemperatureBreach CoolingType is PASSIVE_COOLING and temp is TOO_LOW") {
	REQUIRE(classifyTemperatureBreach(CoolingType::PASSIVE_COOLING, -25) == BreachType::TOO_LOW);
}

TEST_CASE("classifyTemperatureBreach CoolingType is HI_ACTIVE_COOLING and temp is TOO_LOW") {
	REQUIRE(classifyTemperatureBreach(CoolingType::HI_ACTIVE_COOLING, -25) == BreachType::TOO_LOW);
}

TEST_CASE("classifyTemperatureBreach CoolingType is MED_ACTIVE_COOLING and temp is TOO_LOW") {
	REQUIRE(classifyTemperatureBreach(CoolingType::MED_ACTIVE_COOLING, -25) == BreachType::TOO_LOW);
}

TEST_CASE("classifyTemperatureBreach CoolingType is PASSIVE_COOLING and temp is TOO_HIGH") {
	REQUIRE(classifyTemperatureBreach(CoolingType::PASSIVE_COOLING, 55) == BreachType::TOO_HIGH);
}

TEST_CASE("classifyTemperatureBreach CoolingType is HI_ACTIVE_COOLING and temp is TOO_HIGH") {
	REQUIRE(classifyTemperatureBreach(CoolingType::HI_ACTIVE_COOLING, 55) == BreachType::TOO_HIGH);
}

TEST_CASE("classifyTemperatureBreach CoolingType is MED_ACTIVE_COOLING and temp is TOO_HIGH") {
	REQUIRE(classifyTemperatureBreach(CoolingType::MED_ACTIVE_COOLING, 55) == BreachType::TOO_HIGH);
}