#include <Product.h>

using vendingmachine::Product;

Product::Product(std::string name, double price, std::string details, int quantity)
    : name(name), price(price), details(details), quantity(quantity)
{
}

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

int Product::getQuantity()
{
    return quantity;
}

void Product::setQuantity(int newQuantity)
{
     quantity = newQuantity;
}