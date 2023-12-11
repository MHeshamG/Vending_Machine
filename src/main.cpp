#include <VendingMachine.h>
#include <Product.h>

using vendingmachine::VendingMachine;
using vendingmachine::Product;

int main() {
    VendingMachine VM;

    //Add Products to vending machine
    Product p1{"Prod1", 10.0, "Prod1 details", 3};
    VM.addProduct(p1);

    Product p2{"Prod2", 12.0, "Prod2 details", 3};
    VM.addProduct(p2);

    Product p3{"Prod3", 15.0, "Prod3 details", 7};
    VM.addProduct(p3);


    std::cout << std::endl;
    VM.insertMoney(20);
    std::cout << std::endl;

    // Select and dispense multiple products
    VM.selectProduct("Prod1");
    VM.selectProduct("Prod1");
    
    std::cout << std::endl;
    VM.selectProduct("Prod1");
    // VM.selectProduct("Prod1");
    // VM.selectProduct("Prod1");
    // VM.selectProduct("Prod1");
    // VM.selectProduct("Prod2");
    // VM.selectProduct("Prod3");
    std::cout << std::endl;
    // VM.dispenseProduct();
    // VM.dispenseProduct();

    std::cout << "Total money spent: " << VM.getTotalMoney() << std::endl;


    return 0;
}