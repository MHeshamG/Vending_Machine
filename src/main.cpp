#include <VendingMachine.h>
#include <Product.h>

using vendingmachine::Product;
using vendingmachine::VendingMachine;

int main()
{
    VendingMachine VM;

    // Add Products to vending machine
    Product p1{"Prod1", 10.0, "Prod1 details", 10};
    VM.addProduct(p1);

    Product p2{"Prod2", 12.0, "Prod2 details", 20};
    VM.addProduct(p2);

    Product p3{"Prod3", 15.0, "Prod3 details", 30};
    VM.addProduct(p3);

    VM.insertMoney(15.5);
    // VM.selectProduct("Prod1", 5);
    // VM.dispenseProduct();

    std::vector<std::string> productsVector = {"Prod1", "Prod2", "Prod3"};
    std::vector<int> quantities = {7, 9, 10};
    VM.selectProducts(productsVector, quantities);
    VM.dispenseProducts();
    return 0;
}