#include <memory>
#include <iostream>

#include <VendingMachine.h>
#include <Product.h>
#include <IdleState.h>

using vendingmachine::IVendingMachine;
using vendingmachine::VendingMachine;
using vendingmachine::Product;
using vendingmachine::IdleState;

int main() {
    std::shared_ptr<IVendingMachine> VM = std::make_shared<VendingMachine>();

    //Add Products to vending machine
    auto p1 = std::make_shared<Product>("Prod1",10.0,"Prod1 details");
    p1->setQuantity(5);
    VM->addProduct(p1);

    auto p2 = std::make_shared<Product>("Prod2",12.0,"Prod2 details");
    p2->setQuantity(10);
    VM->addProduct(p2);

    auto p3 = std::make_shared<Product>("Prod3",15.0,"Prod3 details");
    p3->setQuantity(15);
    VM->addProduct(p3);

    VM->init(std::make_unique<IdleState>(VM));

    VM->insertMoney(35.5);
    VM->selectProduct("Prod1");
    VM->selectProduct("Prod1");
    VM->lock();
    VM->selectProduct("Prod1");
    VM->selectProduct("Prod1");
    VM->unlock();
    VM->selectProduct("Prod1");
    VM->selectProduct("Prod1");
    VM->dispenseProduct();

    VM->insertMoney(1000);
    VM->selectProduct("Prod1");
    VM->selectProduct("Prod2");
    VM->selectProduct("Prod2");
    VM->selectProduct("Prod3");
    VM->selectProduct("Prod1");
    VM->selectProduct("Prod1");
    VM->selectProduct("Prod1");
    VM->selectProduct("Prod1");
    VM->selectProduct("Prod1");
    VM->selectProduct("Prod1");
    VM->dispenseProduct();

    return 0;
}