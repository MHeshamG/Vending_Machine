#pragma once

#include "VendingMachineState.h"
#include "VendingMachine.h"
#include "VendingMachineErrorCode.h"

namespace vendingmachine
{
    class LockedState :  public VendingMachineState
    {
        public:
        /* Inherited functions */
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




        /************ Custom functions *************/
        LockedState(std::shared_ptr<VendingMachine>vm);
        VendingMachineErrorCode Lock(std::shared_ptr<VendingMachine>vm);
        VendingMachineErrorCode UnLock(std::shared_ptr<VendingMachine>vm);


    private:
    std::unique_ptr<VendingMachineState> previousState;
    };
}