#include "VendingMachine.h"

using vendingmachine::VendingMachine;
using VendingMachineErrorCode = vendingmachine::VendingMachineErrorCode;
using VendingMachineState = vendingmachine::VendingMachineState;
using Product = vendingmachine::Product;

VendingMachine::VendingMachine() : moneyAmount{0}, cartPrice{0}
{
    std::cout << "Vending Machine starting..." << std::endl;
}

void VendingMachine::init(std::shared_ptr<VendingMachineState> state)
{
    if(state != nullptr){
        currentState = state;
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

std::vector<std::shared_ptr<Product>> VendingMachine::getProductsList()
{
    std::vector<std::shared_ptr<Product>> availableProductsVector;
    for (const auto &[name, product] : availableProducts)
    {
        availableProductsVector.push_back(product);
    }
    return availableProductsVector;
}

VendingMachineErrorCode VendingMachine::addProduct(std::shared_ptr<Product> product)
{
    const auto &it = availableProducts.find(product->getName());
    if (it == availableProducts.end())
    {
        const auto &it = availableProducts.insert({product->getName(), product});
        std::cout << "Product added successfully " << product->getName() << std::endl;
    }
    else
    {
        std::cout << "Product already added: " << product->getName() << std::endl;
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

void VendingMachine::changeState(std::shared_ptr<VendingMachineState> state)
{
    previousState = currentState;
    currentState = state;
}

std::shared_ptr<VendingMachineState> VendingMachine::getPreviousState()
{
    return previousState;
}

bool VendingMachine::hasProduct(std::string productName)
{
    const auto &it = availableProducts.find(productName);
    return it != availableProducts.end() && it->second->getQuantity() > 0;
}

std::shared_ptr<Product> VendingMachine::getProduct(std::string productName)
{
    const auto &it = availableProducts.find(productName);
    if (it != availableProducts.end())
    {
        return it->second;
    }

    return nullptr;
}

bool VendingMachine::hasEnoughMoneyForProduct(std::string productName)
{
    auto product = getProduct(productName);
    if (product != nullptr)
    {
        return moneyAmount - cartPrice >= product->getPrice();
    }
    return false;
}

bool VendingMachine::addToCart(std::string productName)
{
    auto product = getProduct(productName);
    if (product == nullptr) {
        return false;
    }

    int currentCartQuantity = cart.count(productName) ? cart[productName] : 0;
    if (product->getQuantity() <= currentCartQuantity) {
        return false;
    }

    cart[productName] = currentCartQuantity + 1;

    cartPrice += product->getPrice();

    return true;
}

void VendingMachine::clearCart()
{
    cart.clear();
    cartPrice = 0.0;
}

double VendingMachine::getCartPrice()
{
    return cartPrice;
}

const std::map<std::string, int> VendingMachine::getCart()
{
    return cart;
}

void VendingMachine::lock()
{
    if(currentState != nullptr){
        currentState->lock();
    }
}

void VendingMachine::unlock()
{
    if(currentState != nullptr){
        currentState->unlock();
    }
}