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
    if (vm->hasProduct(productName))
    {
        if (vm->hasEnoughMoneyForProduct(productName))
        {
            if(vm->addToCart(productName)){
                std::cout<<"Product added to cart: "<<productName<<std::endl;
            }
            else{
                std::cout<<"Product not available: "<<productName<<std::endl;
            }
        }
        else
        {
            std::cout<<"Not enough money for product "<<productName<<std::endl;
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
    vm->setInsertedMoneyAmount(vm->getInsertedMoneyAmount() - vm->getCartPrice());
    if (vm->getInsertedMoneyAmount() > 0.0)
    {
        std::cout << "Returning change: " << vm->getInsertedMoneyAmount() << std::endl;
        vm->setInsertedMoneyAmount(0.0);
    }

    for (const auto &[name, quantity] : vm->getCart())
    {
        auto product = vm->getProduct(name);
        std::cout << "Dispensing product: " << product->getName() << " with quantity: "<<quantity<<std::endl;
        product->decreaseQuantity(quantity);
    }

    vm->clearCart();

    std::shared_ptr<VendingMachineState> idleState = std::make_unique<IdleState>(vm);
    vm->changeState(std::move(idleState));

    return VendingMachineErrorCode::SUCCESS;
}