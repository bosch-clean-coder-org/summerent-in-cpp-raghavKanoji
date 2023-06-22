#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"
#include "typewise-alert.h"

template <typename E, E V> constexpr bool IsValid() {
	std::string name = __FUNCSIG__;
	printf("%s\n", name.c_str());
	int i = strlen(name.c_str());
	for (; i >= 0; --i) {
		if (name[i] == ' ') {
			break;
		}
	}
	char c = name[i + 1];
	printf("%c, \n", c);
	if (c >= '0' && c <= '3') {
		return false;
	}
	return true;
}

TEST_CASE("infers the breach according to Low Limit") {
	REQUIRE(inferBreach(-1, 30) == TOO_LOW);
}

TEST_CASE("infers the breach according to High limits") {
	REQUIRE(inferBreach(32, 30) == TOO_HIGH);
}

TEST_CASE("infers the breach according to Normal limits") {
	REQUIRE(inferBreach(-24, -30) == TOO_LOW);
}

TEST_CASE("infers the breach boundry check") {
	REQUIRE(inferBreach(24, 30) == NORMAL);
}

TEST_CASE("classifyTemperatureBreach CoolingType is PASSIVE_COOLING and temp is normal") {
	bool x = IsValid<CoolingType, PASSIVE_COOLING>();
	if (x)
	{
		printf("This is correct");
		REQUIRE(classifyTemperatureBreach(CoolingType::PASSIVE_COOLING, 25) == NORMAL);
	}
}

TEST_CASE("classifyTemperatureBreach CoolingType is PASSIVE_COOLING and temp is normal invalid") {
	bool x = IsValid<CoolingType, (CoolingType)4>();
	if (x)
	{
		printf("This is correct");
		REQUIRE(classifyTemperatureBreach(CoolingType::PASSIVE_COOLING, 25) == NORMAL);
	}
}

TEST_CASE("classifyTemperatureBreach CoolingType is HI_ACTIVE_COOLING and temp is normal") {
	REQUIRE(classifyTemperatureBreach(CoolingType::HI_ACTIVE_COOLING, 25) == NORMAL);
}

TEST_CASE("classifyTemperatureBreach CoolingType is MED_ACTIVE_COOLING and temp is normal") {
	REQUIRE(classifyTemperatureBreach(CoolingType::MED_ACTIVE_COOLING, 25) == NORMAL);
}

TEST_CASE("classifyTemperatureBreach CoolingType is PASSIVE_COOLING and temp is TOO_LOW") {
	REQUIRE(classifyTemperatureBreach(CoolingType::PASSIVE_COOLING, -25) == TOO_LOW);
}

TEST_CASE("classifyTemperatureBreach CoolingType is HI_ACTIVE_COOLING and temp is TOO_LOW") {
	REQUIRE(classifyTemperatureBreach(CoolingType::HI_ACTIVE_COOLING, -25) == TOO_LOW);
}

TEST_CASE("classifyTemperatureBreach CoolingType is MED_ACTIVE_COOLING and temp is TOO_LOW") {
	REQUIRE(classifyTemperatureBreach(CoolingType::MED_ACTIVE_COOLING, -25) == TOO_LOW);
}

TEST_CASE("classifyTemperatureBreach CoolingType is PASSIVE_COOLING and temp is TOO_HIGH") {
	REQUIRE(classifyTemperatureBreach(CoolingType::PASSIVE_COOLING, 55) == TOO_HIGH);
}

TEST_CASE("classifyTemperatureBreach CoolingType is HI_ACTIVE_COOLING and temp is TOO_HIGH") {
	REQUIRE(classifyTemperatureBreach(CoolingType::HI_ACTIVE_COOLING, 55) == TOO_HIGH);
}

TEST_CASE("classifyTemperatureBreach CoolingType is MED_ACTIVE_COOLING and temp is TOO_HIGH") {
	REQUIRE(classifyTemperatureBreach(CoolingType::MED_ACTIVE_COOLING, 55) == TOO_HIGH);
}