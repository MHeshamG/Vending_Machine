#include <Product.h>

using vendingmachine::Product;

Product::Product(std::string name, double price, std::string details) : name{name}, price{price}, details{details}
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