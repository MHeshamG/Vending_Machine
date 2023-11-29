#include "VendingMachine.h"

using vendingmachine::VendingMachine;
using VMErrorCode = vendingmachine::VendingMachine::VendingMachineErrorCode;
using VMState = vendingmachine::VendingMachine::VendingMachineStates;
using Product = vendingmachine::Product;


VendingMachine::VendingMachine() : moneyAmount{0}, state{VMState::IDLE}
{
    std::cout<<"Vending Machine starting..."<<std::endl;
}

VMErrorCode VendingMachine::insertMoney(double money)
{
    switch(state)
    {
        case VMState::IDLE:
            state = VMState::HAS_MONEY;
            moneyAmount += money;
            std::cout<< "Money inserted: "<<moneyAmount<<std::endl;
        break;
        case VMState::HAS_MONEY:
            moneyAmount += money;
            std::cout<< "Money inserted: "<<moneyAmount<<std::endl;
        break;
        case VMState::PRODUCT_SELECTED:
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
        case VMState::PRODUCT_SELECTED:
            const auto& it = availableProducts.find(productName);
            if(it != availableProducts.end()){
                const double& price = it->second.getPrice();
                if(moneyAmount >= price){
                    state = VMState::PRODUCT_SELECTED;
                    choice = it->second;
                    std::cout<< "Product choosen: "<<productName<<std::endl;
                }
                else{
                    state = VMState::HAS_MONEY;
                    std::cout<< "Please insert more money."<<productName<<std::endl;
                    return VMErrorCode::NOT_ENOUGH_MONEY;
                }
            }
            else{
                state = VMState::HAS_MONEY;
                std::cout<< "Product not found: "<<productName<<std::endl;
                return VMErrorCode::PRODUCT_NOT_FOUND;
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
            return VMErrorCode::NO_PRODUCT_SELECTED;
        break;
        case VMState::PRODUCT_SELECTED:
                moneyAmount -= choice.getPrice();
                if(moneyAmount > 0){
                    std::cout<<"Returning change: "<<moneyAmount<<std::endl;
                    moneyAmount = 0;
                }
                std::cout<<"Dispensing product: "<<choice.getName()<<std::endl;
                state = VMState::IDLE;
        break;
    }
    return VMErrorCode::SUCCESS;
}

std::vector<Product> VendingMachine::getProductsList()
{
    std::vector<Product> availableProductsVector;
    for(const auto& [name,product] : availableProducts){
        availableProductsVector.push_back(product);
    }
    return availableProductsVector;
}

VMErrorCode VendingMachine::addProduct(Product product)
{
    const auto& it =  availableProducts.find(product.getName());
    if(it==availableProducts.end()){
        const auto& it = availableProducts.insert({product.getName(),product});
        std::cout<<"Product added successfully "<<product.getName()<<std::endl;
    }
    else{
        std::cout<<"Product already added: "<<product.getName()<<std::endl;
        return VMErrorCode::PRODUCT_ALREADY_ADDED;
    }

    return VMErrorCode::SUCCESS;
}