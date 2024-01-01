#include <iostream>
#include <LockedState.hpp>


using vendingmachine::LockedState;
using VendingMachineState = vendingmachine::VendingMachineState;
using VendingMachineErrorCode = vendingmachine::VendingMachineErrorCode;

LockedState::LockedState(std::shared_ptr<VendingMachine> vm) : VendingMachineState(vm)
{

}
VendingMachineErrorCode LockedState::insertMoney(double money)
{
    return VendingMachineErrorCode::MACHINE_LOCKED;
}

VendingMachineErrorCode LockedState::selectProduct(std::string productName)
{
    return VendingMachineErrorCode::MACHINE_LOCKED;
}

VendingMachineErrorCode LockedState::dispenseProduct()
{
    return VendingMachineErrorCode::MACHINE_LOCKED;
}
VendingMachineErrorCode LockedState::lockMachine()
{
    /* Store the old machine state */
    previousState = std::move(vm->getCurrentState());
    std::cout<<"Locking..."<<std::endl;
    std::unique_ptr<VendingMachineState> state_locked = std::make_unique<LockedState>(vm);
    vm->changeState(std::move(state_locked));
    std::cout<<"Machine Locked"<<std::endl;

    return VendingMachineErrorCode::MACHINE_LOCKED;
}

VendingMachineErrorCode LockedState::UnLock(std::shared_ptr<VendingMachine>vm)
{
    std::cout<<"UnLocking..."<<std::endl;
    vm->changeState(std::move(previousState));
    std::cout<<"Machine UnLocked"<<std::endl;

    return VendingMachineErrorCode::MACHINE_UNLOCKED;
}
