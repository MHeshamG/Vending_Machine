#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "VendingMachine.h"
#include "MockState.h"

using ::testing::_;
using ::testing::Return;
using ::testing::AtLeast;

using vendingmachine::VendingMachine;
using vendingmachine::MockState;
using vendingmachine::VendingMachineErrorCode;

class VendingMachineTest : public ::testing::Test {
protected:
    std::shared_ptr<VendingMachine> vendingMachine;
    std::shared_ptr<MockState> mockState;

    void SetUp() override {
        vendingMachine = std::make_shared<VendingMachine>();
        mockState = std::make_shared<MockState>(vendingMachine);
        vendingMachine->init(mockState);
    }
};

TEST_F(VendingMachineTest, InsertMoney_ForwardsCallToCurrentState) {
    EXPECT_CALL(*mockState, insertMoney(50.0)).WillOnce(Return(VendingMachineErrorCode::SUCCESS));
    auto result = vendingMachine->insertMoney(50.0);
    EXPECT_EQ(result, VendingMachineErrorCode::SUCCESS);
}

// Add more tests for other methods
