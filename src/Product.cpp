#include <Product.h>
#include <iostream>

using vendingmachine::Product;

Product::Product(std::string name, double price, std::string details) : name{name}, price{price}, details{details}
{

}

Product::Product(const Product& p)
{
    std::cout<<"copy constructor called"<<std::endl;
    name = p.name;
    price = p.price;
    details = p.details;
}

Product::Product(const Product&& p)
{
    std::cout<<"move constructor called"<<std::endl;
    name = std::move(p.name);
    price = std::move(p.price);
    details = std::move(p.details);
}

Product& Product::operator=(const Product&& other)
{
    return *this;
}

Product& Product::operator=(const Product& other)
{
    return *this;
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