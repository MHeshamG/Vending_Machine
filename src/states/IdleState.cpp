#include<iostream>

#include "IdleState.h"
#include <HasMoneyState.h>

using vendingmachine::IdleState;
using VendingMachineState = vendingmachine::VendingMachineState;
using VendingMachineErrorCode = vendingmachine::VendingMachineErrorCode;

IdleState::IdleState(std::shared_ptr<IVendingMachine> vm) : VendingMachineState(vm)
{

}

VendingMachineErrorCode IdleState::insertMoney(double money)
{
    double totalInsertedMoney = vm->getInsertedMoneyAmount() + money;
    vm->setInsertedMoneyAmount(totalInsertedMoney);
    std::cout<< "Money inserted: "<<totalInsertedMoney<<std::endl;
    std::shared_ptr<VendingMachineState> hasMoneyState = std::make_unique<HasMoneyState>(vm);
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