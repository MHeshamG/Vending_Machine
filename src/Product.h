#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

namespace vendingmachine
{
    class Product
    {
        public:
            Product() = default;
            Product(std::string name, double price, std::string details);
            ~Product() = default;

            std::string getName();
            double getPrice();
            std::string getDetails();
        private:
            std::string name;
            double price;
            std::string details;
    };
}

#endif