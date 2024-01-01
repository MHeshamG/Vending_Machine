#ifndef VENDING_MACHINE_STATE
#define VENDING_MACHINE_STATE

#include <string>
#include <memory>

#include "VendingMachineErrorCode.h"

namespace vendingmachine
{
    class VendingMachine;

    class VendingMachineState
    {
    public:
        /**
         * @brief Default constructor for the VendingMachineState class.
         * @param vm vending machine object ptr.
         * Initializes vendingmachine ptr property to passed vm ptr.
         */
        VendingMachineState(std::shared_ptr<VendingMachine> vm);
        virtual ~VendingMachineState() = default;
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
         * @brief Method to lock the machine.
         * @return VendingMachineErrorCode representing the success or failure of the operation.
         */
        virtual VendingMachineErrorCode lockMachine() =0 ;
        

    protected:
        std::shared_ptr<VendingMachine> vm;
    };

} // namespace vendingMachine

#endif // VENDING_MACHINE_STATE

