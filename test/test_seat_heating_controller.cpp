/**
 * @file test_seat_heating_controller.cpp
 * @brief Unit Tests for Seat Heating Controller (C++)
 *
 * @details
 *   Tests the C++ SeatHeatingController behavior and verifies requirement
 *   coverage for SHC-01 through SHC-08.
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../include/seat_heating_controller.h"

using namespace seat_heating;

/**
 * @brief Mock controller to simulate button presses
 */
class MockSeatHeatingController : public SeatHeatingController {
public:
    MOCK_METHOD(tBool, getButtonPressed, (), (override));
};

/**
 * @brief Test fixture for SeatHeatingController
 */
class SeatHeatingControllerTestSuite : public ::testing::Test {
protected:
    MockSeatHeatingController controller;
    void SetUp() override {
        controller.seatOccupied = false;
        controller.powerMgtState = seat_heating::tPowerMgtState::NOK;
        controller.errorStatus = INVALID;
        controller.heatingCoil = 0;
        controller.leds = { false, false, false };
        controller.state = { false, 0 };
        controller.currentTemp = 0;
    }
};

/**
 * @brief Verify activation conditions logic
 */
TEST_F(SeatHeatingControllerTestSuite, Test_CheckConditions_AllConditionsTrue) {
    EXPECT_TRUE(SeatHeatingController::check_conditions(true, OK, NO_ERROR));
}

/**
 * @brief Verify activation conditions fail when seat unoccupied
 */
TEST_F(SeatHeatingControllerTestSuite, Test_CheckConditions_SeatUnoccupied) {
    EXPECT_FALSE(SeatHeatingController::check_conditions(false, OK, NO_ERROR));
}

/**
 * @brief Verify activation conditions fail when power not OK
 */
TEST_F(SeatHeatingControllerTestSuite, Test_CheckConditions_PowerNotOk) {
    EXPECT_FALSE(SeatHeatingController::check_conditions(true, NOK, NO_ERROR));
}

/**
 * @brief Verify activation conditions fail when error flag set
 */
TEST_F(SeatHeatingControllerTestSuite, Test_CheckConditions_ErrorSet) {
    EXPECT_FALSE(SeatHeatingController::check_conditions(true, OK, INVALID));
}


/**
 * @brief Verify stage cycling and outputs across all heating stages
 *
 * @details
 *   Validates initial NO HEATING state and cycling through HIGH, MEDIUM,
 *   and LOW stages on successive button presses.
 */
TEST_F(SeatHeatingControllerTestSuite, Test_Controller_CyclesThroughAllStages) {
    controller.seatOccupied = true;
    controller.powerMgtState = seat_heating::OK;
    controller.errorStatus = NO_ERROR;

    // Use a variable to control the button press
    bool buttonPressed = false;
    ON_CALL(controller, getButtonPressed()).WillByDefault([&]() { return buttonPressed; });

    // No press: 0 -> 0 (SHC-03, SHC-05)
    controller.step();
    EXPECT_EQ(controller.state.temperatureStage, 0);
    EXPECT_EQ(controller.heatingCoil, 0);
    EXPECT_EQ(controller.leds[0], false);
    EXPECT_EQ(controller.leds[1], false);
    EXPECT_EQ(controller.leds[2], false);

    // First press: 0 -> 1 (SHC-04, SHC-08)
    buttonPressed = true;
    controller.step();
    EXPECT_EQ(controller.state.temperatureStage, 1);
    EXPECT_EQ(controller.heatingCoil, 45);
    EXPECT_EQ(controller.leds[0], true);
    EXPECT_EQ(controller.leds[1], true);
    EXPECT_EQ(controller.leds[2], true);

    // Release button
    buttonPressed = false;
    controller.step();

    // Second press: 1 -> 2 (SHC-04, SHC-07)
    buttonPressed = true;
    controller.step();
    EXPECT_EQ(controller.state.temperatureStage, 2);
    EXPECT_EQ(controller.heatingCoil, 35);
    EXPECT_EQ(controller.leds[0], true);
    EXPECT_EQ(controller.leds[1], true);
    EXPECT_EQ(controller.leds[2], false);

    // Release button
    buttonPressed = false;
    controller.step();

    // Third press: 2 -> 3 (SHC-04, SHC-06)
    buttonPressed = true;
    controller.step();
    EXPECT_EQ(controller.state.temperatureStage, 3);
    EXPECT_EQ(controller.heatingCoil, 30);
    EXPECT_EQ(controller.leds[0], true);
    EXPECT_EQ(controller.leds[1], false);
    EXPECT_EQ(controller.leds[2], false);

    // Release button
    buttonPressed = false;
    controller.step();

    // Fourth press: 3 -> 0 (SHC-04, SHC-05)
    buttonPressed = true;
    controller.step();
    EXPECT_EQ(controller.state.temperatureStage, 0);
    EXPECT_EQ(controller.heatingCoil, 0);
    EXPECT_EQ(controller.leds[0], false);
    EXPECT_EQ(controller.leds[1], false);
    EXPECT_EQ(controller.leds[2], false);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
