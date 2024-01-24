// IVendingMachineView.h
#ifndef IVENDING_MACHINE_VIEW_H
#define IVENDING_MACHINE_VIEW_H

#include <string>
#include <vector>
#include <memory>
#include "Product.h"

namespace vendingmachine {
    class IVendingMachineView {
    public:
        virtual void displayProducts(const std::vector<std::shared_ptr<Product>>& products) = 0;
        virtual double requestMoney() = 0;
        virtual std::string displayProductSelection() = 0;
        virtual void displayChange(double change) = 0;
        virtual void dispenseProduct(const std::string& productName) = 0;
        virtual void displayMessage(const std::string& message) = 0;
        virtual bool askToSelectAnotherProduct() = 0;
        virtual ~IVendingMachineView() = default;
    };
}

#endif // IVENDING_MACHINE_VIEW_H
