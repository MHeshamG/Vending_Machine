#include <vector>
#include <unordered_map>
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
                DISPENSING
            };

            enum class VendingMachineErrorCode
            {
                SUCCESS,
                INVALID_OPERATION,
                MACHINE_HAS_NO_MONEY,
                NOT_ENOUGH_MONEY,
                NO_PRODUCT_CHOOSEN,
                GENERAL_ERROR
            };

            VendingMachine();
            ~VendingMachine() = default;

            VendingMachineErrorCode insertMoney(double money);
            VendingMachineErrorCode selectProduct(std::string productName);
            VendingMachineErrorCode dispenseProduct();
            std::vector<Product> getProductsList();
            void addProduct(Product p);

        private:
           double amount;
           double currentTransactionAmount;
           Product choice;
           VendingMachineStates state;
           std::unordered_map<std::string,Product> availableProducts {};
           std::unordered_map<std::string,int> productsCount {};

    };
}