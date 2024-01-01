#ifndef HAS_MONEY_STATE_H
#define HAS_MONEY_STATE_H

#include "VendingMachineState.h"
#include "VendingMachine.h"
#include "VendingMachineErrorCode.h"

namespace vendingmachine
{
    class HasMoneyState : public VendingMachineState
    {
    public:
        HasMoneyState(std::shared_ptr<VendingMachine> vm);

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
         * @brief Method to lock the machine.
         * @return VendingMachineErrorCode representing the success or failure of the operation.
         */
        VendingMachineErrorCode lockMachine() override;
    };
}
#endif