#ifndef VENDING_MACHINE_PRESENTER_H
#define VENDING_MACHINE_PRESENTER_H

#include "VendingMachine.h"
#include "IVendingMachineView.h"
#include <memory>

namespace vendingmachine {

    class VendingMachinePresenter {

    public:
        VendingMachinePresenter(std::shared_ptr<IVendingMachine> m, std::shared_ptr<IVendingMachineView> v);
        void start();
        void insertMoney(double amount);
        void selectProduct(const std::string& productName);
        void dispenseProducts();

    private:
        std::shared_ptr<IVendingMachine> model;
        std::shared_ptr<IVendingMachineView> view;
    };
}

#endif // VENDING_MACHINE_PRESENTER_H
