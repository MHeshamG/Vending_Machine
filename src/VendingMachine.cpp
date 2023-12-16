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
            auto it = availableProducts.find(productName);
            if (it != availableProducts.end()) {
                double price = it->second.getPrice();
                int quantity = it->second.getQuantity();

                if (quantity > 0 && (moneyAmount - totalMoney >= price)) {
                    state = VMState::PRODUCT_SELECTED;
                    selectedProducts.push_back(it->second);

                    // Decrease product quantity
                    it->second.decreaseQuantity();

                    std::cout << "Product chosen: " << productName << std::endl;
                    std::cout << "Remaining quantity: " << it->second.getQuantity() << std::endl;

                    // Update total price
                    totalMoney += price;
                }
                else {
                    state = VMState::HAS_MONEY;

                    if (quantity <= 0) {
                        std::cout << "Sorry, " << productName << " is out of stock." << std::endl;
                        return VMErrorCode::PRODUCT_NOT_FOUND;
                    }
                    else {
                        std::cout << "Not enough money to purchase: " << productName << std::endl;
                        std::cout << "Total money spent so far: " << totalMoney << std::endl;

                        moneyAmount = 0;
                        state = VMState::HAS_MONEY;
                        // selectedProducts.clear();
                        return VMErrorCode::NOT_ENOUGH_MONEY;
                    }
                }
            }
            else {
                state = VMState::HAS_MONEY;
                std::cout << "Product not found: " << productName << std::endl;
                return VMErrorCode::PRODUCT_NOT_FOUND;
            }
            break;
    }
    return VMErrorCode::SUCCESS;
}

double VendingMachine::getTotalMoneyOfSelectedProducts() const {
    double totalMoneyOfSelectedProducts = 0;
    for (const auto& product : selectedProducts) {
        totalMoneyOfSelectedProducts += product.getPrice();
    }
    return totalMoneyOfSelectedProducts;
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
                moneyAmount -= getTotalMoneyOfSelectedProducts();
                if (moneyAmount > 0) {
                    std::cout << "Returning change: " << moneyAmount << std::endl;
                    moneyAmount = 0;
                }

                for(auto p : selectedProducts)
                {
                    std::cout << "Dispensing product: " << p.getName() << std::endl;
                }
                state = VMState::IDLE;

                // Clear selected products vector after dispensing
                selectedProducts.clear();
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


   int VendingMachine::getProductQuantity(const std::string& productName) const {
        auto it = availableProducts.find(productName);
        if (it != availableProducts.end()) {
            return it->second.getQuantity();
        } else {
            std::cout << "Product not found: " << productName << std::endl;
            return -1;  // Return -1 to indicate product not found
        }
    }

    double VendingMachine::getTotalMoney() const {
        return totalMoney;
    }
