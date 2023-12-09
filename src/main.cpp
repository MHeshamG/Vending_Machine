#include <memory>
#include <iostream>

#include <VendingMachine.h>
#include <Product.h>
#include <IdleState.h>

using vendingmachine::VendingMachine;
using vendingmachine::Product;
using vendingmachine::IdleState;

int main() {
    std::shared_ptr<VendingMachine> VM = std::make_shared<VendingMachine>();

    //Add Products to vending machine
    Product p1{"Prod1",20.0,"Prod1 details",2};
    VM->addProduct(p1);

    Product p2{"Prod2",12.0,"Prod2 details",1};
    VM->addProduct(p2);

    Product p3{"Prod3",30.0,"Prod3 details",10};
    VM->addProduct(p3);


    VM->init(std::make_unique<IdleState>(VM));
    VM->insertMoney(50);
    // VM->selectProduct("Prod1");

    VM->addSelectedProduct(p1);
    VM->addSelectedProduct(p2);
    
    // Get and display selected products
    std::vector<Product> selectedProducts = VM->getSelectedProducts();
    std::cout << "Selected Products:" << std::endl;
    for (const auto &product : selectedProducts) {
        std::cout << "Name: " << product.getName() << ", Price: " << product.getPrice() << std::endl;
    }


    VM->dispenseProduct();

    return 0;
}