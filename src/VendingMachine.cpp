#include "VendingMachine.h"

using vendingmachine::VendingMachine;
using VendingMachineErrorCode = vendingmachine::VendingMachineErrorCode;
using Product = vendingmachine::Product;

VendingMachine::VendingMachine() : moneyAmount{0}
{
    std::cout << "Vending Machine starting..." << std::endl;
}

void VendingMachine::init(std::unique_ptr<VendingMachineState> state)
{
    if(state != nullptr){
        currentState = std::move(state);
    }
}

VendingMachineErrorCode VendingMachine::insertMoney(double money)
{
    if(currentState != nullptr){
        return currentState->insertMoney(money);
    }
    return VendingMachineErrorCode::INVALID_OPERATION;
}

VendingMachineErrorCode VendingMachine::selectProduct(std::string productName)
{
    if(currentState != nullptr){
        return currentState->selectProduct(productName);
    }
    return VendingMachineErrorCode::INVALID_OPERATION;
}

VendingMachineErrorCode VendingMachine::dispenseProduct()
{
    if(currentState != nullptr){
        return currentState->dispenseProduct();
    }
    return VendingMachineErrorCode::INVALID_OPERATION;
}

std::vector<Product> VendingMachine::getProductsList()
{
    std::vector<Product> availableProductsVector;
    for (const auto &[name, product] : availableProducts)
    {
        availableProductsVector.push_back(product);
    }
    return availableProductsVector;
}

VendingMachineErrorCode VendingMachine::addProduct(Product product)
{
    const auto &it = availableProducts.find(product.getName());
    if (it == availableProducts.end())
    {
        const auto &it = availableProducts.insert({product.getName(), product});
        std::cout << "Product added successfully " << product.getName() << std::endl;
    }
    else
    {
        std::cout << "Product already added: " << product.getName() << std::endl;
        return VendingMachineErrorCode::PRODUCT_ALREADY_ADDED;
    }

    return VendingMachineErrorCode::SUCCESS;
}

void VendingMachine::setInsertedMoneyAmount(double money)
{
    moneyAmount = money;
}

double VendingMachine::getInsertedMoneyAmount()
{
    return moneyAmount;
}

void VendingMachine::changeState(std::unique_ptr<VendingMachineState> state)
{
    currentState = std::move(state);
}

bool VendingMachine::hasProduct(std::string productName)
{
    const auto &it = availableProducts.find(productName);
    return it != availableProducts.end();
}

std::pair<bool, Product> VendingMachine::getProduct(std::string productName)
{
    Product product;
    const auto &it = availableProducts.find(productName);
    if (it != availableProducts.end())
    {
        return {true, it->second};
    }
    return {false, product};
}

bool VendingMachine::hasEnoughMoneyForProduct(std::string productName)
{
    auto [found, product] = getProduct(productName);
    if (found)
    {
        return moneyAmount >= product.getPrice();
    }
    return false;
}

bool VendingMachine::setSelectedProduct(std::string productName)
{
    auto [found, product] = getProduct(productName);
    if (found)
    {
        choice = product;
        return true;
    }
    return false;
}

Product& VendingMachine::getSelectedProduct()
{
    return choice;
}

VendingMachineErrorCode VendingMachine::requestLock(){

    if(currentState != nullptr){
        return currentState->requestLock();
    }
    return VendingMachineErrorCode::INVALID_OPERATION;
}
VendingMachineErrorCode VendingMachine::requestUnLock(){

    if(currentState != nullptr){
        return currentState->requestUnLock();
    }
    return VendingMachineErrorCode::INVALID_OPERATION;
}