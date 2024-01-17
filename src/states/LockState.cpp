#include<iostream>

#include "LockState.h"
#include <HasMoneyState.h>

using vendingmachine::LockState;
using VendingMachineState = vendingmachine::VendingMachineState;
using VendingMachineErrorCode = vendingmachine::VendingMachineErrorCode;

LockState::LockState(std::shared_ptr<VendingMachine> vm) : VendingMachineState(vm)
{

}

VendingMachineErrorCode LockState::insertMoney(double money)
{
    std::cout << "Machine is locked, cann't insert money" << std::endl;
    return VendingMachineErrorCode::INVALID_OPERATION;
}

VendingMachineErrorCode LockState::selectProduct(std::string productName)
{
    std::cout << "Machine is locked, cann't select product" << std::endl;
    return VendingMachineErrorCode::INVALID_OPERATION;
}

VendingMachineErrorCode LockState::dispenseProduct()
{
    std::cout << "Machine is locked, cann't dispense product" << std::endl;
    return VendingMachineErrorCode::INVALID_OPERATION;
}