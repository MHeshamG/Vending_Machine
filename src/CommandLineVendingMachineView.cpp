#include "CommandLineVendingMachineView.h"
#include <iostream>
#include <limits>

using vendingmachine::CommandLineVendingMachineView;

    void CommandLineVendingMachineView::displayProducts(const std::vector<std::shared_ptr<Product>>& products) {
        std::cout << "Available Products:\n";
        for (const auto& product : products) {
            std::cout << product->getName() << " - Price: " << product->getPrice() << "\n";
        }
    }

    double CommandLineVendingMachineView::requestMoney() {
        std::cout << "Please insert money: ";
        double amount;
        std::cin >> amount;
        if (!std::cin) {
            std::cin.clear(); // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Invalid input. Please enter a number.\n";
            return 0.0;
        }
        return amount;
    }

    std::string CommandLineVendingMachineView::displayProductSelection() {
        std::cout << "Please select a product: ";
        std::string productName;
        std::cin >> productName;
        return productName;
    }

    void CommandLineVendingMachineView::displayChange(double change) {
        std::cout << "Returning change: " << change << "\n";
    }

    void CommandLineVendingMachineView::dispenseProduct(const std::string& productName) {
        std::cout << "Dispensing: " << productName << "\n";
    }

    void CommandLineVendingMachineView::displayMessage(const std::string& message) {
        std::cout << message << "\n";
    }

    bool CommandLineVendingMachineView::askToSelectAnotherProduct() {
        displayMessage("Do you want to select another product? (yes/no)");
        std::string response;
        std::cin >> response;
        return (response == "yes" || response == "Yes" || response == "y" || response == "Y");
    }