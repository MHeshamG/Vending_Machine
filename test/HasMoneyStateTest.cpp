#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "HasMoneyState.h"
#include "MockVendingMachine.h"
#include <memory>

using ::testing::AtLeast;
using ::testing::Return;
using ::testing::_;

using vendingmachine::HasMoneyState;
using vendingmachine::VendingMachineErrorCode;
using vendingmachine::MockVendingMachine;

class HasMoneyStateTest : public ::testing::Test {
protected:
    std::shared_ptr<MockVendingMachine> mockVM;
    std::shared_ptr<HasMoneyState> hasMoneyState;

    void SetUp() override {
        mockVM = std::make_shared<MockVendingMachine>();
        hasMoneyState = std::make_shared<HasMoneyState>(mockVM);
    }
};

TEST_F(HasMoneyStateTest, InsertMoney_Success) {
    EXPECT_CALL(*mockVM, getInsertedMoneyAmount()).WillOnce(Return(50.0));
    EXPECT_CALL(*mockVM, setInsertedMoneyAmount(150.0)).Times(1);

    auto result = hasMoneyState->insertMoney(100.0);
    EXPECT_EQ(result, VendingMachineErrorCode::SUCCESS);
}

TEST_F(HasMoneyStateTest, SelectProduct_Success) {
    EXPECT_CALL(*mockVM, hasProduct("Coke")).WillOnce(Return(true));
    EXPECT_CALL(*mockVM, hasEnoughMoneyForProduct("Coke")).WillOnce(Return(true));
    EXPECT_CALL(*mockVM, addToCart("Coke")).WillOnce(Return(true));
    EXPECT_CALL(*mockVM, changeState(_)).Times(1);

    auto result = hasMoneyState->selectProduct("Coke");
    EXPECT_EQ(result, VendingMachineErrorCode::SUCCESS);
}

TEST_F(HasMoneyStateTest, SelectProduct_ProductNotFound) {
    EXPECT_CALL(*mockVM, hasProduct("Sprite")).WillOnce(Return(false));

    auto result = hasMoneyState->selectProduct("Sprite");
    EXPECT_EQ(result, VendingMachineErrorCode::PRODUCT_NOT_FOUND);
}

TEST_F(HasMoneyStateTest, SelectProduct_NoEnoughMoneyForProduct) {
    EXPECT_CALL(*mockVM, hasProduct("Sprite")).WillOnce(Return(true));
    EXPECT_CALL(*mockVM, hasEnoughMoneyForProduct("Sprite")).WillOnce(Return(false));

    auto result = hasMoneyState->selectProduct("Sprite");
    EXPECT_EQ(result, VendingMachineErrorCode::NOT_ENOUGH_MONEY);
}

TEST_F(HasMoneyStateTest, DispenseProduct_NoProductSelected) {
    auto result = hasMoneyState->dispenseProduct();
    EXPECT_EQ(result, VendingMachineErrorCode::NO_PRODUCT_SELECTED);
}
