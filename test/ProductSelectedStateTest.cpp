#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ProductSelectedState.h"
#include "MockVendingMachine.h"
#include "Product.h"
#include <memory>

using ::testing::Return;
using ::testing::_;

using vendingmachine::ProductSelectedState;
using vendingmachine::VendingMachineErrorCode;
using vendingmachine::MockVendingMachine;
using vendingmachine::Product;


class ProductSelectedStateTest : public ::testing::Test {
protected:
    std::shared_ptr<MockVendingMachine> mockVM;
    std::shared_ptr<ProductSelectedState> productSelectedState;

    void SetUp() override {
        mockVM = std::make_shared<MockVendingMachine>();
        productSelectedState = std::make_shared<ProductSelectedState>(mockVM);
    }
};

TEST_F(ProductSelectedStateTest, InsertMoney_Success) {
    auto result = productSelectedState->insertMoney(100.0);
    ASSERT_EQ(result, VendingMachineErrorCode::INVALID_OPERATION);
}

TEST_F(ProductSelectedStateTest, SelectProduct_Success) {
    EXPECT_CALL(*mockVM, hasProduct("Coke")).WillOnce(Return(true));
    EXPECT_CALL(*mockVM, hasEnoughMoneyForProduct("Coke")).WillOnce(Return(true));
    EXPECT_CALL(*mockVM, addToCart("Coke")).WillOnce(Return(true));

    auto result = productSelectedState->selectProduct("Coke");
    EXPECT_EQ(result, VendingMachineErrorCode::SUCCESS);
}

TEST_F(ProductSelectedStateTest, SelectProduct_ProductNotFound) {
    EXPECT_CALL(*mockVM, hasProduct("Sprite")).WillOnce(Return(false));

    auto result = productSelectedState->selectProduct("Sprite");
    EXPECT_EQ(result, VendingMachineErrorCode::PRODUCT_NOT_FOUND);
}

TEST_F(ProductSelectedStateTest, DispenseProduct_SUCCESS_NoChange) {
    EXPECT_CALL(*mockVM, setInsertedMoneyAmount(0)).Times(1);
    EXPECT_CALL(*mockVM, getInsertedMoneyAmount())
    .WillOnce(Return(50.0))
    .WillOnce(Return(0.0));
    EXPECT_CALL(*mockVM, getCartPrice()).WillOnce(Return(50.0));
    EXPECT_CALL(*mockVM, clearCart()).Times(1);
    EXPECT_CALL(*mockVM, changeState(_)).Times(1);

    auto result = productSelectedState->dispenseProduct();
    EXPECT_EQ(result, VendingMachineErrorCode::SUCCESS);
}

TEST_F(ProductSelectedStateTest, DispenseProduct_SUCCESS_ReturnChange) {
    double insertedMoney = 100, cartPrice = 50, insertedMoneyAfterDeduction = insertedMoney - cartPrice;
    std::map<std::string, int> fakeCart = {{"Coke", 1}};

    EXPECT_CALL(*mockVM, getInsertedMoneyAmount())
    .WillOnce(Return(insertedMoney))
    .WillOnce(Return(insertedMoneyAfterDeduction))
    .WillOnce(Return(insertedMoneyAfterDeduction));
    EXPECT_CALL(*mockVM, getCartPrice()).WillOnce(Return(cartPrice));
    EXPECT_CALL(*mockVM, setInsertedMoneyAmount(cartPrice)).Times(1);
    EXPECT_CALL(*mockVM, setInsertedMoneyAmount(0)).Times(1);
    EXPECT_CALL(*mockVM, getCart()).WillOnce(Return(fakeCart));
    EXPECT_CALL(*mockVM, getProduct(_)).WillOnce(Return(std::make_shared<Product>("Coke", 50.0, "Details")));
    EXPECT_CALL(*mockVM, clearCart()).Times(1);
    EXPECT_CALL(*mockVM, changeState(_)).Times(1);

    auto result = productSelectedState->dispenseProduct();
    EXPECT_EQ(result, VendingMachineErrorCode::SUCCESS);
}
