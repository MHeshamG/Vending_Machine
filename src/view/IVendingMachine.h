#ifndef IVENDING_MACHINE_H
#define IVENDING_MACHINE_H

#include <vector>
#include <map>

#include "Product.h"
#include "VendingMachineErrorCode.h"

namespace vendingmachine
{
    class VendingMachineState;

    class IVendingMachine
    {
    public:
        /**
         * @brief Default constructor for the VendingMachine class.
         * Initializes moneyAmount to 0 and sets the state to IDLE.
         */
        IVendingMachine() = default;

        /**
         * @brief Default destructor for the VendingMachine class.
         */
        virtual ~IVendingMachine() = default;

        /**
         * @brief Method to insert money into the vending machine.
         * @param money The amount of money to be inserted.
         * @return VendingMachineErrorCode representing the success or failure of the operation.
         */
        virtual VendingMachineErrorCode insertMoney(double money) = 0;

        /**
         * @brief Method to select a product for purchase.
         * @param productName The name of the product to be selected.
         * @return VendingMachineErrorCode representing the success or failure of the operation.
         */
        virtual VendingMachineErrorCode selectProduct(std::string productName) = 0;

        /**
         * @brief Method to dispense the selected product.
         * @return VendingMachineErrorCode representing the success or failure of the operation.
         */
        virtual VendingMachineErrorCode dispenseProduct() = 0;

        /**
         * @brief Method to retrieve the list of available products.
         * @return A vector of Product objects representing the available products.
         */
        virtual std::vector<std::shared_ptr<Product>> getProductsList() = 0;

        /**
         * @brief Method to add a product to the vending machine's inventory.
         * @param product The Product object to be added.
         * @return VendingMachineErrorCode representing the success or failure of the operation.
         */
        virtual VendingMachineErrorCode addProduct(std::shared_ptr<Product> p) = 0;

        /**
         * @brief Method to init vending machine with the initial state.
         * @param state Initial state.
         */
        virtual void init(std::shared_ptr<VendingMachineState> state) = 0;

        /**
         * @brief Method to init vending machine with the initial state.
         * @param state Initial state.
         */
        virtual void setInsertedMoneyAmount(double money) = 0;

        /**
         * @brief Method to get current amount of money inseted in the machine.
         * @return Amount of money inserted.
         */
        virtual double getInsertedMoneyAmount() = 0;

        /**
         * @brief Method to change vending machine state.
         * @param state current state.
         */
        virtual void changeState(std::shared_ptr<VendingMachineState> state) = 0;

        /**
         * @brief Method to get previous state.
         * @return Previous state.
         */
        virtual std::shared_ptr<VendingMachineState> getPreviousState() = 0;

        /**
         * @brief Method to get product from inventory.
         * @param productName product name.
         * @return Product object.
         */
        virtual std::shared_ptr<Product> getProduct(std::string productName) = 0;

        /**
         * @brief Method to check if product is in inventory.
         * @param productName The name of the product to be selected
         */
        virtual bool hasProduct(std::string productName) = 0;

        /**
         * @brief Method to check if product is in inventory.
         * @param productName The name of the product to check against.
         */
        virtual bool hasEnoughMoneyForProduct(std::string productName) = 0;

        /**
         * @brief Method to add the selected product by the customer to the cart.
         * @param productName The name of the product to be selected.
         * @return true if the product was added to the cart, false otherwise.
         */
        virtual bool addToCart(std::string productName) = 0;

         /**
         * @brief Method to clear the cart.
         */
        virtual void clearCart() = 0;

        /**
         * @brief Method to get the total price of products in cart.
         * @return The total price of products in cart.
         */
        virtual double getCartPrice() = 0;

        /**
         * @brief Method to get the cart.
         * @return The cart.
         */
        virtual const std::map<std::string, int> getCart() = 0;

        virtual void lock() = 0;

        virtual void unlock() = 0;
    };
}

#endif