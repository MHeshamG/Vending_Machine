#include "LockState.h"

using vendingmachine::VendingMachineState;

VendingMachineState::VendingMachineState(std::shared_ptr<IVendingMachine> vm) : vm{vm} {};

void VendingMachineState::lock()
{
    std::cout << "Locking the vending machine" << std::endl;
    std::shared_ptr<VendingMachineState> lockState = std::make_unique<LockState>(vm);
    vm->changeState(std::move(lockState));
}

void VendingMachineState::unlock()
{
    std::cout << "unlocking the vending machine" << std::endl;
    vm->changeState(vm->getPreviousState());
}