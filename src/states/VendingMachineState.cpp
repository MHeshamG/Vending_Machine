#include <iostream>
#include "VendingMachineState.h"
#include "LockedState.hpp"

using vendingmachine::VendingMachineState;

VendingMachineState::VendingMachineState(std::shared_ptr<VendingMachine> vm) : vm{vm} {};
vendingmachine::VendingMachineErrorCode VendingMachineState::lockMachine()
{
    std::cout<<"General locking behaviour, have no effect "<<std::endl;
    // vm->LockedState::lockMachine();
    return::vendingmachine::VendingMachineErrorCode::GENERAL_ERROR;
}