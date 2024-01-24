#ifndef VENDING_MACHINE_H
#define VENDING_MACHINE_H

#include <bits/stdc++.h>

#include "IVendingMachine.h"
#include "VendingMachineState.h"
namespace vendingmachine
{
    class VendingMachine : public IVendingMachine
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
        VendingMachineErrorCode insertMoney(double money) override;

        /**
         * @brief Method to select a product for purchase.
         * @param productName The name of the product to be selected.
         * @return VendingMachineErrorCode representing the success or failure of the operation.
         */
        VendingMachineErrorCode selectProduct(std::string productName) override;

        /**
         * @brief Method to dispense the selected product.
         * @return VendingMachineErrorCode representing the success or failure of the operation.
         */
        VendingMachineErrorCode dispenseProduct() override;

        /**
         * @brief Method to retrieve the list of available products.
         * @return A vector of Product objects representing the available products.
         */
        std::vector<std::shared_ptr<Product>> getProductsList() override;

        /**
         * @brief Method to add a product to the vending machine's inventory.
         * @param product The Product object to be added.
         * @return VendingMachineErrorCode representing the success or failure of the operation.
         */
        VendingMachineErrorCode addProduct(std::shared_ptr<Product> p) override;

        /**
         * @brief Method to init vending machine with the initial state.
         * @param state Initial state.
         */
        void init(std::shared_ptr<VendingMachineState> state) override;

        /**
         * @brief Method to init vending machine with the initial state.
         * @param state Initial state.
         */
        void setInsertedMoneyAmount(double money) override;

        /**
         * @brief Method to get current amount of money inseted in the machine.
         * @return Amount of money inserted.
         */
        double getInsertedMoneyAmount() override;

        /**
         * @brief Method to change vending machine state.
         * @param state current state.
         */
        void changeState(std::shared_ptr<VendingMachineState> state) override;

        /**
         * @brief Method to get previous state.
         * @return Previous state.
         */
        std::shared_ptr<VendingMachineState> getPreviousState() override;
        
        /**
         * @brief Method to get product from inventory.
         * @param productName product name.
         * @return Product object.
         */
        std::shared_ptr<Product> getProduct(std::string productName) override;

        /**
         * @brief Method to check if product is in inventory.
         * @param productName The name of the product to be selected
         */
        bool hasProduct(std::string productName) override;

        /**
         * @brief Method to check if product is in inventory.
         * @param productName The name of the product to check against.
         */
        bool hasEnoughMoneyForProduct(std::string productName) override;

        /**
         * @brief Method to add the selected product by the customer to the cart.
         * @param productName The name of the product to be selected.
         * @return true if the product was added to the cart, false otherwise.
         */
        bool addToCart(std::string productName) override;

         /**
         * @brief Method to clear the cart.
         */
        void clearCart() override;

        /**
         * @brief Method to get the total price of products in cart.
         * @return The total price of products in cart.
         */
        double getCartPrice() override;

        /**
         * @brief Method to get the cart.
         * @return The cart.
         */
        const std::map<std::string, int> getCart() override;

        void lock() override;

        void unlock() override;

    private:
        double moneyAmount;
        double cartPrice;
        std::map<std::string, int> cart;
        std::shared_ptr<VendingMachineState> currentState;
        std::shared_ptr<VendingMachineState> previousState;
        std::map<std::string, std::shared_ptr<Product>> availableProducts{};
    };
}

#endif