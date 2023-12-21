#include<iostream>
#include <LockState.h>
#include <IdleState.h>
#include <HasMoneyState.h>

using vendingmachine::LockState;
using VendingMachineState = vendingmachine::VendingMachineState;
using VendingMachineErrorCode = vendingmachine::VendingMachineErrorCode;

LockState::LockState(std::shared_ptr<VendingMachine> vm) : VendingMachineState(vm)
{

}

VendingMachineErrorCode LockState::insertMoney(double money)
{
    std::cout<<"MACHINE_LOCKED"<<std::endl;

    return VendingMachineErrorCode::MACHINE_LOCKED;
}

VendingMachineErrorCode LockState::selectProduct(std::string productName)
{
    std::cout<<"MACHINE_LOCKED"<<std::endl;
    return VendingMachineErrorCode::MACHINE_LOCKED;
    
}

VendingMachineErrorCode LockState::dispenseProduct()
{
    std::cout<<"MACHINE_LOCKED"<<std::endl;
    return VendingMachineErrorCode::MACHINE_LOCKED;
}

VendingMachineErrorCode LockState::requestLock()
{
    std::cout<<"MACHINE ALREADY LOCKED"<<std::endl;
    return VendingMachineErrorCode::MACHINE_LOCKED;
}

VendingMachineErrorCode LockState::requestUnLock()
{
    std::cout<< "UnLock requested! moving to IdleState!"<<std::endl;
    std::unique_ptr<VendingMachineState> idleState = std::make_unique<IdleState>(vm);
    vm->changeState(std::move(idleState));
    return VendingMachineErrorCode::SUCCESS;
}