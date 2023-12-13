#include <Product.h>

using vendingmachine::Product;

Product::Product(std::string name, double price, std::string details) : name{name}, price{price}, details{details}
{
    amount = 0;
}

Product::Product(std::string name, double price, std::string details, int amount) : name{name}, price{price}, details{details}, amount(amount) { /*to do*/}

std::string Product::getName()
{
    return name;
}

double Product::getPrice()
{
    return price;
}

std::string Product::getDetails()
{
    return details;
}

int Product::getAmount()
{
    return amount;
}