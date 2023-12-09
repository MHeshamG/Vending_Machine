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
double VendingMachine::getTotalPrice()
{
    double totalPrice = 0;
    for(auto prod : choice)
    {
        totalPrice+=prod.getPrice();
    }

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
                const double& price = getTotalPrice() + it->second.first.getPrice();
                if(moneyAmount >= price && it->second.second > 0){
                    state = VMState::PRODUCT_SELECTED;
                    choice.push_back (it->second.first);
                    std::cout<< "Product choosen: "<<productName<<std::endl;
                }
                else if(moneyAmount < price){
                    state = VMState::HAS_MONEY;
                    std::cout<< "Please insert more money."<<productName<<std::endl;
                    return VMErrorCode::NOT_ENOUGH_MONEY;
                }
                else 
                {
                    state = VMState::HAS_MONEY;
                    std::cout<< "The product is not available at the moment."<<productName<<std::endl;
                    return VMErrorCode::OUT_OF_PRODUCT;
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

VMErrorCode VendingMachine::decrementQnty()
{
    for(auto product:choice)
    {
        const auto& it = availableProducts.find(product.getName());
        it->second.second--;
    }
}

void VendingMachine::dsiplayProducts()
{
    for(auto product:choice)
    {
        std::cout<<"Dispensing product: "<<product.getName()<<std::endl;
    }
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
                moneyAmount -= getTotalPrice();
                decrementQnty();
                if(moneyAmount > 0){
                    std::cout<<"Returning change: "<<moneyAmount<<std::endl;
                    moneyAmount = 0;
                }
                dsiplayProducts();
                choice.clear();
                state = VMState::IDLE;
        break;
    }
    return VMErrorCode::SUCCESS;
}

std::vector<Product> VendingMachine::getProductsList()
{
    std::vector<Product> availableProductsVector;
    for(const auto& [name,product] : availableProducts){
        availableProductsVector.push_back(product.first);
    }
    return availableProductsVector;
}

VMErrorCode VendingMachine::addProduct(Product product, unsigned char qnt)
{
    const auto& it =  availableProducts.find(product.getName());
    if(it==availableProducts.end()){
        const auto& it = availableProducts.insert({product.getName(),{product, qnt}});
        std::cout<<"Product added successfully "<<product.getName()<<std::endl;
    }
    else{
        //std::cout<<"Product already added: "<<product.getName()<<std::endl;
        //return VMErrorCode::PRODUCT_ALREADY_ADDED;
        it->second.second+=qnt;
        std::cout<<"Product added successfully "<<product.getName()<<std::endl;
    }

    return VMErrorCode::SUCCESS;
}