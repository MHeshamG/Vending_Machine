#include<iostream>

#include <IdleState.h>
#include <HasMoneyState.h>
#include <LockState.h>

using vendingmachine::IdleState;
using VendingMachineState = vendingmachine::VendingMachineState;
using VendingMachineErrorCode = vendingmachine::VendingMachineErrorCode;

IdleState::IdleState(std::shared_ptr<VendingMachine> vm) : VendingMachineState(vm)
{

}

VendingMachineErrorCode IdleState::insertMoney(double money)
{
    double totalInsertedMoney = vm->getInsertedMoneyAmount() + money;
    vm->setInsertedMoneyAmount(totalInsertedMoney);
    std::cout<< "Money inserted: "<<totalInsertedMoney<<std::endl;
    std::unique_ptr<VendingMachineState> hasMoneyState = std::make_unique<HasMoneyState>(vm);
    vm->changeState(std::move(hasMoneyState));

    return VendingMachineErrorCode::SUCCESS;
}

VendingMachineErrorCode IdleState::selectProduct(std::string productName)
{
    return VendingMachineErrorCode::MACHINE_HAS_NO_MONEY;
}

VendingMachineErrorCode IdleState::dispenseProduct()
{
    return VendingMachineErrorCode::MACHINE_HAS_NO_MONEY;
}

VendingMachineErrorCode IdleState::requestLock()
{
    std::cout<< "Lock requested from Ideal State!"<<std::endl;
    std::unique_ptr<VendingMachineState> lockState = std::make_unique<LockState>(vm);
    vm->changeState(std::move(lockState));
    return VendingMachineErrorCode::SUCCESS;
}

VendingMachineErrorCode IdleState::requestUnLock()
{
    std::cout<< "Unlock requested from Ideal State! but the machine is not locked!"<<std::endl;
    return VendingMachineErrorCode::SUCCESS;
}