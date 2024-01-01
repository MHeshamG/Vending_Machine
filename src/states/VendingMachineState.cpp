#include <iostream>
#include "VendingMachineState.h"

using vendingmachine::VendingMachineState;

VendingMachineState::VendingMachineState(std::shared_ptr<VendingMachine> vm) : vm{vm} {};
// vendingmachine::VendingMachineErrorCode VendingMachineState::lockMachine()
// {
//     std::cout<<"General locking behaviour, have no effect "<<std::endl;
//     return::vendingmachine::VendingMachineErrorCode::GENERAL_ERROR;
// }