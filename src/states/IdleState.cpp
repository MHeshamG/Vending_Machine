#include<iostream>

#include "IdleState.h"
#include <HasMoneyState.h>

using vendingmachine::IdleState;
using VendingMachineState = vendingmachine::VendingMachineState;
using VendingMachineErrorCode = vendingmachine::VendingMachineErrorCode;

IdleState::IdleState(std::shared_ptr<VendingMachine> vm) : VendingMachineState(vm)
{

}

VendingMachineErrorCode IdleState::insertMoney(double money)
{
    int minMoney = 5;// at least 5$ to buy product
    double totalInsertedMoney = vm->getInsertedMoneyAmount() + money;
    vm->setInsertedMoneyAmount(totalInsertedMoney);
    std::cout<< "Money inserted: "<<totalInsertedMoney<<std::endl;
    if(totalInsertedMoney > minMoney)
    {
        std::unique_ptr<VendingMachineState> hasMoneyState = std::make_unique<HasMoneyState>(vm);
        vm->changeState(std::move(hasMoneyState));

    }
    else{
         std::unique_ptr<VendingMachineState> lockstate = std::make_unique<LockState>(vm);
        vm->changeState(std::move(lockstate));

    }

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