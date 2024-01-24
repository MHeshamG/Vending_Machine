#include <ProductSelectedState.h>
#include <IdleState.h>

using vendingmachine::ProductSelectedState;
using VendingMachineState = vendingmachine::VendingMachineState;
using VendingMachineErrorCode = vendingmachine::VendingMachineErrorCode;

ProductSelectedState::ProductSelectedState(std::shared_ptr<IVendingMachine> vm) : VendingMachineState(vm)
{

}

VendingMachineErrorCode ProductSelectedState::insertMoney(double money)
{
    return VendingMachineErrorCode::INVALID_OPERATION;
}

VendingMachineErrorCode ProductSelectedState::selectProduct(std::string productName)
{
    std::shared_ptr<IVendingMachine> vmPtr = vm.lock();
    if (vmPtr->hasProduct(productName))
    {
        if (vmPtr->hasEnoughMoneyForProduct(productName))
        {
            vmPtr->addToCart(productName);
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
    std::shared_ptr<IVendingMachine> vmPtr = vm.lock();
    vmPtr->setInsertedMoneyAmount(vmPtr->getInsertedMoneyAmount() - vmPtr->getCartPrice());
    if (vmPtr->getInsertedMoneyAmount() > 0.0)
    {
        std::cout << "Returning change: " << vmPtr->getInsertedMoneyAmount() << std::endl;
        vmPtr->setInsertedMoneyAmount(0.0);
    }

    for (const auto &[name, quantity] : vmPtr->getCart())
    {
        auto product = vmPtr->getProduct(name);
        product->decreaseQuantity(quantity);
    }

    vmPtr->clearCart();

    std::shared_ptr<VendingMachineState> idleState = std::make_shared<IdleState>(vmPtr);
    vmPtr->changeState(idleState);

    return VendingMachineErrorCode::SUCCESS;
}