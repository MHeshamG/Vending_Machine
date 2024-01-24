#ifndef COMMAND_LINE_VENDING_MACHINE_VIEW_H
#define COMMAND_LINE_VENDING_MACHINE_VIEW_H

#include "IVendingMachineView.h"
#include <vector>
#include <memory>

namespace vendingmachine {

    class CommandLineVendingMachineView : public IVendingMachineView {
    public:
        void displayProducts(const std::vector<std::shared_ptr<Product>>& products) override;
        double requestMoney() override;
        std::string displayProductSelection() override;
        void displayChange(double change) override;
        void dispenseProduct(const std::string& productName) override;
        void displayMessage(const std::string& message) override;
        bool askToSelectAnotherProduct() override;
    };

}

#endif // COMMAND_LINE_VENDING_MACHINE_VIEW_H
