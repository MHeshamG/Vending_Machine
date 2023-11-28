#include "VendingMachine.h"

using vendingmachine::VendingMachine;
using VMErrorCode = vendingmachine::VendingMachine::VendingMachineErrorCode;
using VMState = vendingmachine::VendingMachine::VendingMachineStates;
using Product = vendingmachine::Product;


VendingMachine::VendingMachine() : amount{0}, currentTransactionAmount{0}, state{VMState::IDLE}
{

}

VMErrorCode VendingMachine::insertMoney(double money)
{
    switch(state)
    {
        case VMState::IDLE:
            state = VMState::HAS_MONEY;
            currentTransactionAmount += money;
        break;
        case VMState::HAS_MONEY:
            currentTransactionAmount += money;
        break;
        case VMState::DISPENSING:
            return VMErrorCode::INVALID_OPERATION;       
        break;
    }

    return VMErrorCode::SUCCESS;
}

VMErrorCode VendingMachine::selectProduct(std::string productName)
{
    switch(state)
    {
        case VMState::IDLE:
            return VMErrorCode::MACHINE_HAS_NO_MONEY;
        break;
        case VMState::HAS_MONEY:
        case VMState::DISPENSING:
            const auto& it = availableProducts.find(productName);
            if(it != availableProducts.end()){
                const double& price = it->second.getPrice();
                if(currentTransactionAmount >= price){
                    state = VMState::DISPENSING;
                    choice = it->second;
                    std::cout<< "Product choosen: "<<choice.getName()<<std::endl;
                }
                else{
                    state = VMState::HAS_MONEY;
                    std::cout<< "Please insert more money."<<choice.getName()<<std::endl;
                    return VMErrorCode::NOT_ENOUGH_MONEY;
                }
            }
        break;
    }
    return VMErrorCode::SUCCESS;
}

VMErrorCode VendingMachine::dispenseProduct()
{
    switch(state)
    {
        case VMState::IDLE:
            return VMErrorCode::MACHINE_HAS_NO_MONEY;
        break;
        case VMState::HAS_MONEY:
            return VMErrorCode::NO_PRODUCT_CHOOSEN;
        break;
        case VMState::DISPENSING:
                currentTransactionAmount -= choice.getPrice();
                amount += choice.getPrice();
                state = VMState::IDLE;
                std::cout<<"Dispensing Product: "<<choice.getName();
        break;
    }
    return VMErrorCode::SUCCESS;
}

std::vector<Product> getProductsList()
{
    return {};
}

void addProduct(Product p)
{

}