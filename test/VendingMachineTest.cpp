#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "VendingMachine.h"
#include "Product.h"
#include "MockState.h"

using ::testing::_;
using ::testing::Return;
using ::testing::AtLeast;

using vendingmachine::VendingMachine;
using vendingmachine::MockState;
using vendingmachine::VendingMachineErrorCode;
using vendingmachine::Product;

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

// Tests for main functions of vending machine

TEST_F(VendingMachineTest, InsertMoney_ForwardsCallToCurrentState) {
    EXPECT_CALL(*mockState, insertMoney(50.0)).WillOnce(Return(VendingMachineErrorCode::SUCCESS));
    auto result = vendingMachine->insertMoney(50.0);
    EXPECT_EQ(result, VendingMachineErrorCode::SUCCESS);
}

TEST_F(VendingMachineTest, SelectProduct_ForwardsCallToCurrentState) {
    EXPECT_CALL(*mockState, selectProduct("Coke")).WillOnce(Return(VendingMachineErrorCode::SUCCESS));
    auto result = vendingMachine->selectProduct("Coke");
    EXPECT_EQ(result, VendingMachineErrorCode::SUCCESS);
}

TEST_F(VendingMachineTest, dispenseProduct_ForwardsCallToCurrentState) {
    EXPECT_CALL(*mockState, dispenseProduct()).WillOnce(Return(VendingMachineErrorCode::SUCCESS));
    auto result = vendingMachine->dispenseProduct();
    EXPECT_EQ(result, VendingMachineErrorCode::SUCCESS);
}

// Tests for addProduct, getProductsList, etc.

TEST_F(VendingMachineTest, AddProduct_AddsNewProductSuccessfully) {
    auto product = std::make_shared<Product>("Sprite", 1.0, "Details");
    auto result = vendingMachine->addProduct(product);
    EXPECT_EQ(result, VendingMachineErrorCode::SUCCESS);
}

TEST_F(VendingMachineTest, AddProduct_FailsWhenProductAlreadyExists) {
    auto product = std::make_shared<Product>("Coke", 1.0, "Details");
    vendingMachine->addProduct(product); // Adding once
    auto result = vendingMachine->addProduct(product); // Adding again
    EXPECT_EQ(result, VendingMachineErrorCode::PRODUCT_ALREADY_ADDED);
}

TEST_F(VendingMachineTest, GetProductsList_ReturnsCorrectProductList) {
    auto product1 = std::make_shared<Product>("Coke", 1.0, "Details");
    auto product2 = std::make_shared<Product>("Sprite", 1.0, "Details");
    vendingMachine->addProduct(product1);
    vendingMachine->addProduct(product2);

    auto productList = vendingMachine->getProductsList();
    EXPECT_EQ(productList.size(), 2);
    EXPECT_EQ(productList[0]->getName(), "Coke");
    EXPECT_EQ(productList[1]->getName(), "Sprite");
}

TEST_F(VendingMachineTest, SetAndGetInsertedMoneyAmount) {
    vendingMachine->setInsertedMoneyAmount(100.0);
    double amount = vendingMachine->getInsertedMoneyAmount();
    EXPECT_DOUBLE_EQ(amount, 100.0);
}

TEST_F(VendingMachineTest, AddToCart_And_GetCartDetails) {
    auto product = std::make_shared<Product>("Coke", 1.0, "Details");
    product->setQuantity(1);
    vendingMachine->addProduct(product);
    vendingMachine->setInsertedMoneyAmount(100.0);
    bool addedToCart = vendingMachine->addToCart("Coke");
    EXPECT_TRUE(addedToCart);

    auto cart = vendingMachine->getCart();
    EXPECT_EQ(cart.size(), 1);
    EXPECT_EQ(cart["Coke"], 1);
}

TEST_F(VendingMachineTest, ClearCart_ClearsTheCart) {
    auto product = std::make_shared<Product>("Coke", 1.0, "Details");
    vendingMachine->addProduct(product);
    vendingMachine->addToCart("Coke");
    vendingMachine->clearCart();

    auto cart = vendingMachine->getCart();
    EXPECT_TRUE(cart.empty());
}

TEST_F(VendingMachineTest, ChangeState_ChangesTheCurrentState) {
    auto newState = std::make_shared<MockState>(vendingMachine);
    vendingMachine->changeState(newState);

    auto previousState = vendingMachine->getPreviousState();
    EXPECT_EQ(previousState, mockState);
}

// Tests for lock and unlock methods
TEST_F(VendingMachineTest, LockAndUnlockMethods_ForwardCallsToCurrentState) {
    EXPECT_CALL(*mockState, lock()).Times(1);
    vendingMachine->lock();

    EXPECT_CALL(*mockState, unlock()).Times(1);
    vendingMachine->unlock();
}

