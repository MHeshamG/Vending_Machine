#ifndef VENDING_MACHINE_ERROR_CODE
#define VENDING_MACHINE_ERROR_CODE

namespace vendingmachine
{
    enum class VendingMachineErrorCode
    {
        SUCCESS,
        INVALID_OPERATION,
        MACHINE_HAS_NO_MONEY,
        NOT_ENOUGH_MONEY,
        NO_PRODUCT_SELECTED,
        PRODUCT_ALREADY_ADDED,
        PRODUCT_NOT_FOUND,
        MACHINE_LOCKED,
        GENERAL_ERROR
    };
} // namespace vendingmachine

#endif // VENDING_MACHINE_ERROR_CODE