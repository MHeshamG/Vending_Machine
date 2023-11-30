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
            Product(const Product&);
            Product(const Product&&);
            Product& operator=(const Product&& other);
            Product& operator=(const Product& other);
            ~Product() = default;

            std::string getName()const;
            double getPrice()const;
            std::string getDetails()const;
        private:
            std::string name;
            double price;
            std::string details;
    };
}

#endif