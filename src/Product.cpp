#include <Product.h>
#include <iostream>

using vendingmachine::Product;

Product::Product(std::string name, double price, std::string details) : name{name}, price{price}, details{details}
{
    amount = 0;
}

Product::Product(std::string name, double price, std::string details, int amount) : name{name}, price{price}, details{details}, amount(amount) { /*to do*/}

std::string Product::getName() const
{
    return name;
}

double Product::getPrice() const
{
    return price;
}

std::string Product::getDetails() const
{
    return details;
}

int Product::getAmount()
{
    return amount;
}