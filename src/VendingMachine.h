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

        /**
         * @brief Method to init vending machine with the initial state.
         * @param state Initial state.
         */
        void init(std::unique_ptr<VendingMachineState> state);

        /**
         * @brief Method to init vending machine with the initial state.
         * @param state Initial state.
         */
        void setInsertedMoneyAmount(double money);

        /**
         * @brief Method to get current amount of money inseted in the machine.
         * @return Amount of money inserted.
         */
        double getInsertedMoneyAmount();

        /**
         * @brief Method to change vending machine state.
         * @param state current state.
         */
        void changeState(std::unique_ptr<VendingMachineState> state);

        /**
         * @brief Method to check if product is in inventory.
         * @param productName product name.
         */
        bool hasProduct(std::string productName);

        /**
         * @brief Method to check if product is in inventory.
         * @param productName The name of the product to check against.
         */
        bool hasEnoughMoneyForProduct(std::string productName);

        /**
         * @brief Method to set the selected product by the customer.
         * @param productName The name of the product to be selected.
         */
        bool setSelectedProduct(std::string productName);

        /**
         * @brief Method to get the selected product by the customer.
         * @param productName The name of the product selected.
         */
        Product &getSelectedProduct();

    private:
        double moneyAmount;
        Product choice;
        std::unique_ptr<VendingMachineState> currentState;
        std::map<std::string, Product> availableProducts{};

        std::pair<bool, Product> getProduct(std::string productName);
    };
}

#endif