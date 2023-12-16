#include <LockState.h>
#include <ProductSelectedState.h>
#include <HasMoneyState.h>
#include <IdleState.h>

using vendingmachine::LockState;
using VendingMachineState = vendingmachine::VendingMachineState;
using VendingMachineErrorCode = vendingmachine::VendingMachineErrorCode;

LockState::LockState(std::shared_ptr<VendingMachine> vm) : VendingMachineState(vm)
{

}

VendingMachineErrorCode LockState::insertMoney(double money)
{
    return VendingMachineErrorCode::INVALID_OPERATION;
}

VendingMachineErrorCode LockState::selectProduct(std::string productName)
{
    return VendingMachineErrorCode::INVALID_OPERATION;

}

VendingMachineErrorCode LockState::dispenseProduct()
{
    return VendingMachineErrorCode::INVALID_OPERATION;
}