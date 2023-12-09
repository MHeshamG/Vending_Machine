#include <Product.h>
#include <iostream>

using vendingmachine::Product;

Product::Product(std::string name, double price, std::string details, int quantity) : name{name}, price{price}, details{details}, quantity{quantity}
{

}

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