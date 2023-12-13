#ifndef VENDING_MACHINE_H
#define VENDING_MACHINE_H

#include <vector>
#include <string>
#include <map>
#include <bits/stdc++.h>

#include <Product.h>

namespace vendingmachine
{
    class VendingMachine
    {
    public:
        enum class VendingMachineStates
        {
            IDLE,
            HAS_MONEY,
            PRODUCT_SELECTED
        };

        enum class VendingMachineErrorCode
        {
            SUCCESS,
            INVALID_OPERATION,
            MACHINE_HAS_NO_MONEY,
            NOT_ENOUGH_MONEY,
            NO_PRODUCT_SELECTED,
            PRODUCT_ALREADY_ADDED,
            PRODUCT_NOT_FOUND,
            STOCK_IS_INSUFFICENT,
            GENERAL_ERROR
        };

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
        VendingMachineErrorCode selectProduct(std::string productName, int quantity);
        VendingMachineErrorCode selectProducts(const std::vector<std::string> &productNames, const std::vector<int> &quantities);

        /**
         * @brief Method to dispense the selected product.
         * @return VendingMachineErrorCode representing the success or failure of the operation.
         */
        VendingMachineErrorCode dispenseProduct();
        VendingMachineErrorCode dispenseProducts();

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
        // for finding index in a vector

        int findIndex(const std::vector<std::string> &vec, const std::string &item);

    private:
        double moneyAmount;
        Product choice;
        VendingMachineStates state;
        std::map<std::string, Product> availableProducts{};
        std::vector<Product> choices;
    };
}

#endif