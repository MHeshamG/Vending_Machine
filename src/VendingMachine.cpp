#include "VendingMachine.h"

using vendingmachine::VendingMachine;
using VendingMachineErrorCode = vendingmachine::VendingMachineErrorCode;
using Product = vendingmachine::Product;

<<<<<<< HEAD

VendingMachine::VendingMachine() : moneyAmount{0}, currentState{std::make_unique<IdleState>()}
=======
VendingMachine::VendingMachine() : moneyAmount{0}
>>>>>>> vending-machine-state-pattern
{
    std::cout << "Vending Machine starting..." << std::endl;
}

void VendingMachine::init(std::unique_ptr<VendingMachineState> state)
{
<<<<<<< HEAD
    /* Delegate */
    // currentState->insertMoney(money);
    // switch(state)
    // {
    //     case VMState::IDLE:
    //         state = VMState::HAS_MONEY;
    //         moneyAmount += money;
    //         std::cout<< "Money inserted: "<<moneyAmount<<std::endl;
    //     break;
    //     case VMState::HAS_MONEY:
    //         moneyAmount += money;
    //         std::cout<< "Money inserted: "<<moneyAmount<<std::endl;
    //     break;
    //     case VMState::PRODUCT_SELECTED:
    //         return VMErrorCode::INVALID_OPERATION;       
    //     break;
    // }
    
    return VMErrorCode::SUCCESS;
=======
    if(state != nullptr){
        currentState = std::move(state);
    }
>>>>>>> vending-machine-state-pattern
}

VendingMachineErrorCode VendingMachine::insertMoney(double money)
{
<<<<<<< HEAD
    // switch(state)
    // {
    //     case VMState::IDLE:
    //         return VMErrorCode::MACHINE_HAS_NO_MONEY;
    //     break;
    //     case VMState::HAS_MONEY:
    //     case VMState::PRODUCT_SELECTED:
    //         const auto& it = availableProducts.find(productName);
    //         if(it != availableProducts.end()){
    //             const double& price = it->second.getPrice();
    //             if(moneyAmount >= price){
    //                 state = VMState::PRODUCT_SELECTED;
    //                 choice = it->second;
    //                 std::cout<< "Product choosen: "<<productName<<std::endl;
    //             }
    //             else{
    //                 state = VMState::HAS_MONEY;
    //                 std::cout<< "Please insert more money."<<productName<<std::endl;
    //                 return VMErrorCode::NOT_ENOUGH_MONEY;
    //             }
    //         }
    //         else{
    //             state = VMState::HAS_MONEY;
    //             std::cout<< "Product not found: "<<productName<<std::endl;
    //             return VMErrorCode::PRODUCT_NOT_FOUND;
    //         }
    //     break;
    // }
    return VMErrorCode::SUCCESS;
}

int VendingMachine::getProductQuantity(std::string ProductName)
{
    // switch (state)
    // {
    //     case VMState::IDLE:
    //         return -1;
    //     break;
    //     // case VMState::HAS_MONEY:
    //     case VMState::PRODUCT_SELECTED:
    //         const auto& it = availableProducts.find(ProductName);
    //         if(it != availableProducts.end()){
    //             return it->second.getAmount();
    //         }
    //         else{   /**/ }
    //     break;           
    // }
    return -1;
}

VMErrorCode VendingMachine::dispenseProduct()
{
    // switch(state)
    // {
    //     case VMState::IDLE:
    //         return VMErrorCode::MACHINE_HAS_NO_MONEY;
    //     break;
    //     case VMState::HAS_MONEY:
    //         return VMErrorCode::NO_PRODUCT_SELECTED;
    //     break;
    //     case VMState::PRODUCT_SELECTED:
    //             moneyAmount -= choice.getPrice();
    //             if(moneyAmount > 0){
    //                 std::cout<<"Returning change: "<<moneyAmount<<std::endl;
    //                 moneyAmount = 0;
    //             }
    //             std::cout<<"Dispensing product: "<<choice.getName()<<std::endl;
    //             state = VMState::IDLE;
    //     break;
    // }
    return VMErrorCode::SUCCESS;
=======
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
>>>>>>> vending-machine-state-pattern
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

<<<<<<< HEAD
    return VMErrorCode::SUCCESS;
}

void VendingMachine::setInsertedMoney(double money)
{
    moneyAmount +=money;
=======
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
>>>>>>> vending-machine-state-pattern
}