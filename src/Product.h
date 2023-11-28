#include <string>

namespace vendingmachine
{
    class Product
    {
        public:
            Product() = default;
            Product(std::string name, double price, std::string details, int calories);
            ~Product() = default;

            std::string getName();
            double getPrice();
            std::string getDetails();
            int getCalories();
        private:
            std::string name;
            double price;
            std::string details;
            int calories;
    };
}