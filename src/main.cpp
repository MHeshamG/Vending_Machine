#include <memory>
#include <iostream>

#include "VendingMachine.h"
#include "VendingMachineState.h"
#include "Product.h"
#include "IdleState.h"
#include "VendingMachinePresenter.h"
#include "CommandLineVendingMachineView.h"

using vendingmachine::IVendingMachine;
using vendingmachine::VendingMachine;
using vendingmachine::VendingMachineState;
using vendingmachine::Product;
using vendingmachine::IdleState;
using vendingmachine::VendingMachinePresenter;
using vendingmachine::IVendingMachineView;
using vendingmachine::CommandLineVendingMachineView;

int main() {
    std::shared_ptr<IVendingMachine> VM = std::make_shared<VendingMachine>();

    //Add Products to vending machine
    auto coke = std::make_shared<Product>("Coke",10.0,"Refreshing beverage");
    coke->setQuantity(5);
    VM->addProduct(coke);

    auto sprite = std::make_shared<Product>("Sprite",12.0,"Lemon-Lime drink");
    sprite->setQuantity(10);
    VM->addProduct(sprite);

    auto chips = std::make_shared<Product>("Chips",15.0,"Fried potato chips");
    chips->setQuantity(15);
    VM->addProduct(chips);

    std::shared_ptr<VendingMachineState> state = std::make_shared<IdleState>(VM);
    VM->init(state);

    std::shared_ptr<IVendingMachineView> view = std::make_shared<CommandLineVendingMachineView>();

    std::unique_ptr presenter = std::make_unique<VendingMachinePresenter>(VM,view);

    presenter->start();

    return 0;
}