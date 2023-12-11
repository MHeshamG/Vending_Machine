#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <iostream>

namespace vendingmachine
{
    class Product
    {
        public:
            Product() = default;
            Product(std::string name, double price, std::string details, int quantity);
            ~Product() = default;

            std::string getName();
            double getPrice() const;
            std::string getDetails();
            int getQuantity() const ;
            void decreaseQuantity();
        private:
            std::string name;
            double price;
            std::string details;
            int quantity;
    };
}

#endif