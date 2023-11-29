#include <VendingMachine.h>
#include <Product.h>

using vendingmachine::VendingMachine;
using vendingmachine::Product;

int main() {
    VendingMachine VM;

    //Add Products to vending machine
    Product p1{"Prod1",10.0,"Prod1 details"};
    VM.addProduct(p1);

    Product p2{"Prod2",12.0,"Prod2 details"};
    VM.addProduct(p2);

    Product p3{"Prod3",15.0,"Prod3 details"};
    VM.addProduct(p3);

    VM.insertMoney(15.5);
    VM.selectProduct("Prod1");
    VM.dispenseProduct();

    return 0;
}