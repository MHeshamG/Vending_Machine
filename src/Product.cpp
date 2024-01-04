#include <Product.h>
#include <iostream>

using vendingmachine::Product;

Product::Product(std::string name, double price, std::string details) : name{name}, price{price}, details{details}, quantity{0}
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

int Product::getQuantity() const
{
    return quantity;
}

void Product::setQuantity(int quantity)
{
    this->quantity = quantity;
}

void Product::decreaseQuantity(int decreaseBy)
{
    quantity -= decreaseBy;
}