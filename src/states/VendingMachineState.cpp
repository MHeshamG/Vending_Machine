#include "LockState.h"

using vendingmachine::VendingMachineState;

VendingMachineState::VendingMachineState(std::shared_ptr<IVendingMachine> vm) : vm{vm} {};

void VendingMachineState::lock()
{
    std::cout << "Locking the vending machine" << std::endl;
    std::shared_ptr<IVendingMachine> vmPtr = vm.lock();
    std::shared_ptr<VendingMachineState> lockState = std::make_shared<LockState>(vmPtr);
    vmPtr->changeState(lockState);
}

void VendingMachineState::unlock()
{
    std::cout << "unlocking the vending machine" << std::endl;
    std::shared_ptr<IVendingMachine> vmPtr = vm.lock();
    vmPtr->changeState(vmPtr->getPreviousState());
}