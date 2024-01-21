#include <gmock/gmock.h>

namespace vendingmachine {

class MockState : public VendingMachineState
{
 public:
    MockState(std::shared_ptr<IVendingMachine> vm) : VendingMachineState(vm){}
    MOCK_METHOD(VendingMachineErrorCode, insertMoney, (double money), (override));
    MOCK_METHOD(VendingMachineErrorCode, selectProduct, (std::string productName), (override));
    MOCK_METHOD(VendingMachineErrorCode, dispenseProduct, (), (override));  
};

}