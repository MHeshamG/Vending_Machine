#include <HasMoneyState.h>
#include <ProductSelectedState.h>

using vendingmachine::HasMoneyState;
using VendingMachineState = vendingmachine::VendingMachineState;
using VendingMachineErrorCode = vendingmachine::VendingMachineErrorCode;

HasMoneyState::HasMoneyState(std::shared_ptr<IVendingMachine> vm) : VendingMachineState(vm)
{

}

VendingMachineErrorCode HasMoneyState::insertMoney(double money)
{
    std::shared_ptr<IVendingMachine> vmPtr = vm.lock();
    double totalInsertedMoney = vmPtr->getInsertedMoneyAmount() + money;
    vmPtr->setInsertedMoneyAmount(totalInsertedMoney);
    std::cout<< "Money inserted: "<<totalInsertedMoney<<std::endl;

    return VendingMachineErrorCode::SUCCESS;
}

VendingMachineErrorCode HasMoneyState::selectProduct(std::string productName)
{
    std::shared_ptr<IVendingMachine> vmPtr = vm.lock();
    if(vmPtr->hasProduct(productName)){
        if(vmPtr->hasEnoughMoneyForProduct(productName)){
            if(vmPtr->addToCart(productName)){
                std::cout<<"Product added to cart: "<<productName<<std::endl;
                std::shared_ptr<VendingMachineState> productSelectedState = std::make_shared<ProductSelectedState>(vmPtr);
                vmPtr->changeState(productSelectedState);
            }
            else{
                std::cout<<"Product not available: "<<productName<<std::endl;
            }
        }
        else{
            std::cout<<"Not enough money for product"<<std::endl;
            return VendingMachineErrorCode::NOT_ENOUGH_MONEY;
        }
    }
    else{
        std::cout<<"Product not available "<<productName<<std::endl;
        return VendingMachineErrorCode::PRODUCT_NOT_FOUND;
    }

    return VendingMachineErrorCode::SUCCESS;
}

VendingMachineErrorCode HasMoneyState::dispenseProduct()
{
    return VendingMachineErrorCode::NO_PRODUCT_SELECTED;
}