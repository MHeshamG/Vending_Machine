#include <gmock/gmock.h>
#include "IVendingMachine.h"

namespace vendingmachine {

class MockVendingMachine : public IVendingMachine {
public:
    MOCK_METHOD(VendingMachineErrorCode, insertMoney, (double money), (override));
    MOCK_METHOD(VendingMachineErrorCode, selectProduct, (std::string productName), (override));
    MOCK_METHOD(VendingMachineErrorCode, dispenseProduct, (), (override));
    MOCK_METHOD(std::vector<std::shared_ptr<Product>>, getProductsList, (), (override));
    MOCK_METHOD(VendingMachineErrorCode, addProduct, (std::shared_ptr<Product> p), (override));
    MOCK_METHOD(void, init, (std::shared_ptr<VendingMachineState> state), (override));
    MOCK_METHOD(void, setInsertedMoneyAmount, (double money), (override));
    MOCK_METHOD(double, getInsertedMoneyAmount, (), (override));
    MOCK_METHOD(void, changeState, (std::shared_ptr<VendingMachineState> state), (override));
    MOCK_METHOD(std::shared_ptr<VendingMachineState>, getPreviousState, (), (override));
    MOCK_METHOD(std::shared_ptr<Product>, getProduct, (std::string productName), (override));
    MOCK_METHOD(bool, hasProduct, (std::string productName), (override));
    MOCK_METHOD(bool, hasEnoughMoneyForProduct, (std::string productName), (override));
    MOCK_METHOD(bool, addToCart, (std::string productName), (override));
    MOCK_METHOD(void, clearCart, (), (override));
    MOCK_METHOD(double, getCartPrice, (), (override));
    MOCK_METHOD((const std::map<std::string, int>), getCart, (), (override));
    MOCK_METHOD(void, lock, (), (override));
    MOCK_METHOD(void, unlock, (), (override));
};

} // namespace vendingmachine

