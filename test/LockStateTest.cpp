#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "LockState.h"
#include "MockVendingMachine.h"

using ::testing::_;
using ::testing::Return;

using vendingmachine::LockState;
using vendingmachine::VendingMachineErrorCode;
using vendingmachine::MockVendingMachine;

class LockStateTest : public ::testing::Test {
protected:
    std::shared_ptr<MockVendingMachine> mockVM;
    std::shared_ptr<LockState> lockState;

    void SetUp() override {
        mockVM = std::make_shared<MockVendingMachine>();
        lockState = std::make_shared<LockState>(mockVM);
    }
};

TEST_F(LockStateTest, InsertMoney_ReturnsInvalidOperation) {
    auto result = lockState->insertMoney(50.0);
    EXPECT_EQ(result, VendingMachineErrorCode::INVALID_OPERATION);
}

TEST_F(LockStateTest, SelectProduct_ReturnsInvalidOperation) {
    auto result = lockState->selectProduct("Coke");
    EXPECT_EQ(result, VendingMachineErrorCode::INVALID_OPERATION);
}

TEST_F(LockStateTest, DispenseProduct_ReturnsInvalidOperation) {
    auto result = lockState->dispenseProduct();
    EXPECT_EQ(result, VendingMachineErrorCode::INVALID_OPERATION);
}
