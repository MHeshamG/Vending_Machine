#include "VendingMachine.h"
#include <algorithm> // for std::find
#include <vector>
#include <iterator> // for std::distance
#include <string>

using vendingmachine::VendingMachine;
using VMErrorCode = vendingmachine::VendingMachine::VendingMachineErrorCode;
using VMState = vendingmachine::VendingMachine::VendingMachineStates;
using Product = vendingmachine::Product;

int VendingMachine::findIndex(const std::vector<std::string> &vec, const std::string &item)
{
    auto it = std::find(vec.begin(), vec.end(), item);
    if (it != vec.end())
    {
        return std::distance(vec.begin(), it);
    }
    else
    {
        return -1;
    }
}

VendingMachine::VendingMachine() : moneyAmount{0}, state{VMState::IDLE}
{
    std::cout << "Vending Machine starting..." << std::endl;
}

VMErrorCode VendingMachine::insertMoney(double money)
{
    switch (state)
    {
    case VMState::IDLE:
        state = VMState::HAS_MONEY;
        moneyAmount += money;
        std::cout << "Money inserted: " << moneyAmount << std::endl;
        break;
    case VMState::HAS_MONEY:
        moneyAmount += money;
        std::cout << "Money inserted: " << moneyAmount << std::endl;
        break;
    case VMState::PRODUCT_SELECTED:
        return VMErrorCode::INVALID_OPERATION;
        break;
    }

    return VMErrorCode::SUCCESS;
}

VMErrorCode VendingMachine::selectProduct(std::string productName, int quantity)
{
    switch (state)
    {
    case VMState::IDLE:
        return VMErrorCode::MACHINE_HAS_NO_MONEY;
        break;
    case VMState::HAS_MONEY:
    case VMState::PRODUCT_SELECTED:
        const auto &it = availableProducts.find(productName);
        if (it != availableProducts.end())
        { // e.g the product was not found
            const double &price = it->second.getPrice();
            const int &availableQuantity = it->second.getQuantity();
            if (moneyAmount >= price && availableQuantity > quantity)
            {
                state = VMState::PRODUCT_SELECTED;
                choice = it->second;
                int newQuantity = availableQuantity - quantity;
                choice.setQuantity(newQuantity); // modifing the current quantity
                std::cout << "Product choosen: " << productName << std::endl;
            }
            else if (choice.getQuantity() < quantity)
            {
                std::cout << "Stock Is Insufficent, this is the remaining stock: " << availableQuantity << std::endl;
                return VMErrorCode::STOCK_IS_INSUFFICENT;
            }
            else
            {
                state = VMState::HAS_MONEY;
                std::cout << "Please insert more money." << productName << std::endl;
                return VMErrorCode::NOT_ENOUGH_MONEY;
            }
        }
        else
        {
            state = VMState::HAS_MONEY;
            std::cout << "Product not found: " << productName << std::endl;
            return VMErrorCode::PRODUCT_NOT_FOUND;
        }
        break;
    }
    return VMErrorCode::SUCCESS;
}
VMErrorCode VendingMachine::dispenseProduct()
{
    switch (state)
    {
    case VMState::IDLE:
        return VMErrorCode::MACHINE_HAS_NO_MONEY;
        break;
    case VMState::HAS_MONEY:
        return VMErrorCode::NO_PRODUCT_SELECTED;
        break;
    case VMState::PRODUCT_SELECTED:
        moneyAmount -= choice.getPrice();
        if (moneyAmount > 0)
        {
            std::cout << "Returning change: " << moneyAmount << std::endl;
            moneyAmount = 0;
        }
        std::cout << "Dispensing product: " << choice.getName() << std::endl;
        std::cout << "remaining quantity: " << choice.getQuantity() << std::endl;
        state = VMState::IDLE;
        break;
    }
    return VMErrorCode::SUCCESS;
}

VMErrorCode VendingMachine::selectProducts(const std::vector<std::string> &productNames, const std::vector<int> &quantities)
{
    switch (state)
    {
    case VMState::IDLE:
        return VMErrorCode::MACHINE_HAS_NO_MONEY;
        break;
    case VMState::HAS_MONEY:
    case VMState::PRODUCT_SELECTED:
        for (const auto &productName : productNames)
        {
            const auto &it = availableProducts.find(productName);
            if (it != availableProducts.end())
            { // e.g the product was found
                // finding the required quantity
                int indexOfTheQuantity = findIndex(productNames, productName);
                const double &price = it->second.getPrice();
                const int &availableQuantity = it->second.getQuantity();
                if (moneyAmount >= price && availableQuantity > quantities[indexOfTheQuantity])
                {
                    state = VMState::PRODUCT_SELECTED;
                    choice = it->second;
                    int newQuantity = availableQuantity - quantities[indexOfTheQuantity];
                    choice.setQuantity(newQuantity); // modifing the current quantity
                    std::cout << "Product choosen: " << productName << std::endl;
                    std::cout << "Product quantity: " << quantities[indexOfTheQuantity] << std::endl;
                }
                else if (choice.getQuantity() < quantities[indexOfTheQuantity])
                {
                    std::cout << "Stock Is Insufficent, this is the remaining stock: " << availableQuantity << std::endl;
                    return VMErrorCode::STOCK_IS_INSUFFICENT;
                }
                else
                {
                    state = VMState::HAS_MONEY;
                    std::cout << "Please insert more money." << productName << std::endl;
                    return VMErrorCode::NOT_ENOUGH_MONEY;
                }
            }
            else
            {
                state = VMState::HAS_MONEY;
                std::cout << "Product not found: " << productName << std::endl;
                return VMErrorCode::PRODUCT_NOT_FOUND;
            }
        }
    }
    return VMErrorCode::SUCCESS;
}

VMErrorCode VendingMachine::dispenseProducts()
{
    switch (state)
    {
    case VMState::IDLE:
        return VMErrorCode::MACHINE_HAS_NO_MONEY;
        break;
    case VMState::HAS_MONEY:
        return VMErrorCode::NO_PRODUCT_SELECTED;
        break;
    case VMState::PRODUCT_SELECTED:
        moneyAmount -= choice.getPrice();
        if (moneyAmount > 0)
        {
            std::cout << "Returning change: " << moneyAmount << std::endl;
            moneyAmount = 0;
        }
        std::cout << "Dispensing product: " << choice.getName() << std::endl;
        std::cout << "remaining quantity: " << choice.getQuantity() << std::endl;
        state = VMState::IDLE;
        break;
    }
    return VMErrorCode::SUCCESS;
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

VMErrorCode VendingMachine::addProduct(Product product)
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
        return VMErrorCode::PRODUCT_ALREADY_ADDED;
    }

    return VMErrorCode::SUCCESS;
}