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

            std::string getName()const;
            double getPrice()const;
            std::string getDetails()const;
            int getQuantity()const;
            void setQuantity(int quantity);
            void decreaseQuantity(int decreaseBy);
        private:
            std::string name;
            double price;
            std::string details;
            int quantity;
    };
}

#endif