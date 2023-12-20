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
            Product(std::string name, double price, std::string details, int amount);
            ~Product() = default;

            std::string getName()const;
            double getPrice()const;
            std::string getDetails()const;
            int getAmount();  
        private:
            std::string name;
            double price;
            std::string details;
            int amount;
    };
}
#endif