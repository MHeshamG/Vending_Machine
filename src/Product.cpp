#include <Product.h>

using vendingmachine::Product;

Product::Product(std::string name, double price, std::string details, int quantity) : name{name}, price{price}, details{details}, quantity{quantity}
{

}

std::string Product::getName()
{
    return name;
}

double Product::getPrice() const
{
    return price;
}

std::string Product::getDetails()
{
    return details;
}

int Product::getQuantity() const {
    return quantity;
}

void Product::decreaseQuantity() {
    if (quantity > 0) {
        --quantity;
    } else {
        std::cout << "Sorry, " << name << " is out of stock." << std::endl;
    }
}