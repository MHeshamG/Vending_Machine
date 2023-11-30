#ifndef VENDING_MACHINE_H
#define VENDING_MACHINE_H

#include <vector>
#include <map>
#include <bits/stdc++.h>

#include "Product.h"
#include "VendingMachineState.h"
#include "VendingMachineErrorCode.h"

namespace vendingmachine
{
    class VendingMachine : public std::enable_shared_from_this<VendingMachine>
    {
    public:
        /**
         * @brief Default constructor for the VendingMachine class.
         * Initializes moneyAmount to 0 and sets the state to IDLE.
         */
        VendingMachine();

        /**
         * @brief Default destructor for the VendingMachine class.
         */
        ~VendingMachine() = default;

        /**
         * @brief Method to insert money into the vending machine.
         * @param money The amount of money to be inserted.
         * @return VendingMachineErrorCode representing the success or failure of the operation.
         */
        VendingMachineErrorCode insertMoney(double money);

        /**
         * @brief Method to select a product for purchase.
         * @param productName The name of the product to be selected.
         * @return VendingMachineErrorCode representing the success or failure of the operation.
         */
        VendingMachineErrorCode selectProduct(std::string productName);

        /**
         * @brief Method to dispense the selected product.
         * @return VendingMachineErrorCode representing the success or failure of the operation.
         */
        VendingMachineErrorCode dispenseProduct();

        /**
         * @brief Method to retrieve the list of available products.
         * @return A vector of Product objects representing the available products.
         */
        std::vector<Product> getProductsList();

        /**
         * @brief Method to add a product to the vending machine's inventory.
         * @param product The Product object to be added.
         * @return VendingMachineErrorCode representing the success or failure of the operation.
         */
        VendingMachineErrorCode addProduct(Product p);

        void init(std::unique_ptr<VendingMachineState> state);
        void setInsertedMoneyAmount(double money);
        double getInsertedMoneyAmount();
        void changeState(std::unique_ptr<VendingMachineState> state);
        bool hasProduct(std::string productName);
        bool hasEnoughMoneyForProduct(std::string productName);
        bool setSelectedProduct(std::string productName);
        Product getSelectedProduct();

    private:
        double moneyAmount;
        Product choice;
        std::unique_ptr<VendingMachineState> currentState;
        std::map<std::string, Product> availableProducts{};

        std::pair<bool, Product> getProduct(std::string productName);
    };
}

#endif