#include <gtest/gtest.h>
#include "VendingMachine.h"
#include "Product.h"
#include "IdleState.h"
#include "HasMoneyState.h"
#include "ProductSelectedState.h"
#include "LockState.h"

using vendingmachine::VendingMachine;
using vendingmachine::Product;
using vendingmachine::IdleState;
using vendingmachine::HasMoneyState;
using vendingmachine::ProductSelectedState;
using vendingmachine::LockState;
using vendingmachine::VendingMachineErrorCode;

class VendingMachineIntegrationTest : public ::testing::Test {
protected:
    std::shared_ptr<VendingMachine> vendingMachine;

    void SetUp() override {
        vendingMachine = std::make_shared<VendingMachine>();
        vendingMachine->init(std::make_shared<IdleState>(vendingMachine));
    }
};

TEST_F(VendingMachineIntegrationTest, PurchaseProductFlow) {
    auto coke = std::make_shared<Product>("Coke", 1, "Refreshing beverage");
    coke->setQuantity(10);
    vendingMachine->addProduct(coke);

    vendingMachine->insertMoney(2);
    vendingMachine->selectProduct("Coke");
    auto errorCode = vendingMachine->dispenseProduct();

    EXPECT_EQ(errorCode, VendingMachineErrorCode::SUCCESS);
    EXPECT_EQ(coke->getQuantity(), 9);
}

TEST_F(VendingMachineIntegrationTest, PurchaseMultipleProductsFlow) {
    auto coke = std::make_shared<Product>("Coke", 1.50, "Refreshing beverage");
    auto sprite = std::make_shared<Product>("Sprite", 1.25, "Lemon-lime drink");
    coke->setQuantity(10);
    sprite->setQuantity(10);
    vendingMachine->addProduct(coke);
    vendingMachine->addProduct(sprite);

    vendingMachine->insertMoney(3.00);
    vendingMachine->selectProduct("Coke");
    vendingMachine->selectProduct("Sprite");
    auto errorCode = vendingMachine->dispenseProduct();

    EXPECT_EQ(errorCode, VendingMachineErrorCode::SUCCESS);
    EXPECT_EQ(coke->getQuantity(), 9);
    EXPECT_EQ(sprite->getQuantity(), 9);
}

TEST_F(VendingMachineIntegrationTest, InsufficientFundsFlow) {
    auto coke = std::make_shared<Product>("Coke", 2.00, "Refreshing beverage");
    coke->setQuantity(10);
    vendingMachine->addProduct(coke);

    vendingMachine->insertMoney(1.00);
    auto errorCode = vendingMachine->selectProduct("Coke");

    EXPECT_EQ(errorCode, VendingMachineErrorCode::NOT_ENOUGH_MONEY);
    EXPECT_EQ(coke->getQuantity(), 10); // Quantity should remain the same
}

TEST_F(VendingMachineIntegrationTest, ProductNotFoundFlow) {
    vendingMachine->insertMoney(1.00);
    auto errorCode = vendingMachine->selectProduct("Pepsi"); // Pepsi not added to machine

    EXPECT_EQ(errorCode, VendingMachineErrorCode::PRODUCT_NOT_FOUND);
}

TEST_F(VendingMachineIntegrationTest, MoneyIsEnoughForOneProduct) {
    auto coke = std::make_shared<Product>("Coke", 1.50, "Refreshing beverage");
    auto sprite = std::make_shared<Product>("Sprite", 1.25, "Lemon-lime drink");
    coke->setQuantity(10);
    sprite->setQuantity(10);
    vendingMachine->addProduct(coke);
    vendingMachine->addProduct(sprite);

    vendingMachine->insertMoney(2.00);
    vendingMachine->selectProduct("Coke");
    auto errorCode1 =vendingMachine->selectProduct("Sprite");
    auto errorCode2 = vendingMachine->dispenseProduct();

    EXPECT_EQ(errorCode1, VendingMachineErrorCode::NOT_ENOUGH_MONEY);
    EXPECT_EQ(errorCode2, VendingMachineErrorCode::SUCCESS);
    EXPECT_EQ(coke->getQuantity(), 9);
    EXPECT_EQ(sprite->getQuantity(), 10);
}
