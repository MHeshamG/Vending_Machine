#include <ProductSelectedState.h>
#include <IdleState.h>

using vendingmachine::ProductSelectedState;
using VendingMachineState = vendingmachine::VendingMachineState;
using VendingMachineErrorCode = vendingmachine::VendingMachineErrorCode;

ProductSelectedState::ProductSelectedState(std::shared_ptr<VendingMachine> vm) : VendingMachineState(vm)
{

}

VendingMachineErrorCode ProductSelectedState::insertMoney(double money)
{
    return VendingMachineErrorCode::INVALID_OPERATION;
}

VendingMachineErrorCode ProductSelectedState::selectProduct(std::string productName)
{
    if (vm->hasProduct(productName))
    {
        if (vm->hasEnoughMoneyForProduct(productName))
        {
            vm->setSelectedProduct(productName);
        }
        else
        {
            return VendingMachineErrorCode::NOT_ENOUGH_MONEY;
        }
    }
    else
    {
        return VendingMachineErrorCode::PRODUCT_NOT_FOUND;
    }

    return VendingMachineErrorCode::SUCCESS;
}

VendingMachineErrorCode ProductSelectedState::dispenseProduct()
{
    vm->setInsertedMoneyAmount(vm->getInsertedMoneyAmount() - vm->getSelectedProduct().getPrice());
    if (vm->getInsertedMoneyAmount() > 0.0)
    {
        std::cout << "Returning change: " << vm->getInsertedMoneyAmount() << std::endl;
        vm->setInsertedMoneyAmount(0.0);
    }
    std::cout << "Dispensing product: " << vm->getSelectedProduct().getName() << std::endl;

    std::unique_ptr<VendingMachineState> idleState = std::make_unique<IdleState>(vm);
    vm->changeState(std::move(idleState));

    return VendingMachineErrorCode::SUCCESS;
}