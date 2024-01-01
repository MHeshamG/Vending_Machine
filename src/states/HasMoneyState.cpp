#include <HasMoneyState.h>
#include <ProductSelectedState.h>

using vendingmachine::HasMoneyState;
using VendingMachineState = vendingmachine::VendingMachineState;
using VendingMachineErrorCode = vendingmachine::VendingMachineErrorCode;

HasMoneyState::HasMoneyState(std::shared_ptr<VendingMachine> vm) : VendingMachineState(vm)
{

}

VendingMachineErrorCode HasMoneyState::insertMoney(double money)
{
    double totalInsertedMoney = vm->getInsertedMoneyAmount() + money;
    vm->setInsertedMoneyAmount(totalInsertedMoney);
    std::cout<< "Money inserted: "<<totalInsertedMoney<<std::endl;

    return VendingMachineErrorCode::SUCCESS;
}

VendingMachineErrorCode HasMoneyState::selectProduct(std::string productName)
{
    if(vm->hasProduct(productName)){
        if(vm->hasEnoughMoneyForProduct(productName)){
            vm->setSelectedProduct(productName);
            std::cout<<"Product selected: "<<productName<<std::endl;
            std::unique_ptr<VendingMachineState> productSelectedState = std::make_unique<ProductSelectedState>(vm);
            vm->changeState(std::move(productSelectedState));
        }
        else{
            std::cout<<"NOT_ENOUGH_MONEY "<<std::endl;
            return VendingMachineErrorCode::NOT_ENOUGH_MONEY;
        }
    }
    else{
        std::cout<<"PRODUCT_NOT_FOUND "<<std::endl;
        return VendingMachineErrorCode::PRODUCT_NOT_FOUND;
    }

    return VendingMachineErrorCode::SUCCESS;
}

VendingMachineErrorCode HasMoneyState::dispenseProduct()
{
    return VendingMachineErrorCode::NO_PRODUCT_SELECTED;
}

VendingMachineErrorCode HasMoneyState::lockMachine() 
{
    return VendingMachineErrorCode::GENERAL_ERROR;
}