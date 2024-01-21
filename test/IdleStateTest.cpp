#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "IdleState.h"
#include "MockVendingMachine.h"

using ::testing::Return;

using vendingmachine::MockVendingMachine;
using vendingmachine::IdleState;
using vendingmachine::VendingMachineErrorCode;


class IdleStateTest : public ::testing::Test {
protected:
    std::shared_ptr<MockVendingMachine> mockVM;
    std::shared_ptr<IdleState> idleState;

    void SetUp() override {
        mockVM = std::make_shared<MockVendingMachine>();
        idleState = std::make_unique<IdleState>(mockVM);
    }
};

TEST_F(IdleStateTest, InsertMoney_Success) {
    // Set up expectations
    EXPECT_CALL(*mockVM, getInsertedMoneyAmount()).WillOnce(Return(0.0));
    EXPECT_CALL(*mockVM, setInsertedMoneyAmount(100.0)).Times(1);
    EXPECT_CALL(*mockVM, changeState(::testing::_)).Times(1);

    // Execute test
    auto result = idleState->insertMoney(100.0);

    // Verify results
    EXPECT_EQ(result, VendingMachineErrorCode::SUCCESS);
}

TEST_F(IdleStateTest, SelectProduct_Failure) {
    // Execute test
    auto result = idleState->selectProduct("Coke");

    // Verify results
    EXPECT_EQ(result, VendingMachineErrorCode::MACHINE_HAS_NO_MONEY);
}

TEST_F(IdleStateTest, DispenseProduct_Failure) {
    // Execute test
    auto result = idleState->dispenseProduct();

    // Verify results
    EXPECT_EQ(result, VendingMachineErrorCode::MACHINE_HAS_NO_MONEY);
}
