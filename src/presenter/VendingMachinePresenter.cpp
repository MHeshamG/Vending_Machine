#include "VendingMachinePresenter.h"

using vendingmachine::VendingMachinePresenter;

    VendingMachinePresenter::VendingMachinePresenter(std::shared_ptr<IVendingMachine> m, std::shared_ptr<IVendingMachineView> v)
        : model(m), view(v) {}

    void VendingMachinePresenter::start() {
        view->displayProducts(model->getProductsList());
        double amount = view->requestMoney();
        insertMoney(amount);
        bool continueSelectingProducts = true;
        while (continueSelectingProducts) {
            std::string productName = view->displayProductSelection();
            selectProduct(productName);
            continueSelectingProducts = view->askToSelectAnotherProduct();
        }
        dispenseProducts();
    }

    void VendingMachinePresenter::insertMoney(double amount) {
        auto result = model->insertMoney(amount);
        if (result != VendingMachineErrorCode::SUCCESS) {
            view->displayMessage("Failed to insert money.");
        }
    }

    void VendingMachinePresenter::selectProduct(const std::string& productName) {
        auto result = model->selectProduct(productName);
        switch (result) {
            case VendingMachineErrorCode::SUCCESS:
                // Product added to the cart, but not dispensed yet.
                break;
            case VendingMachineErrorCode::PRODUCT_NOT_FOUND:
                view->displayMessage("Product not found.");
                break;
            case VendingMachineErrorCode::NOT_ENOUGH_MONEY:
                view->displayMessage("Not enough money inserted.");
                break;
            default:
                view->displayMessage("Error selecting product.");
                break;
        }
    }

    void VendingMachinePresenter::dispenseProducts() {
        auto change = model->getInsertedMoneyAmount() - model->getCartPrice();
        // Display each product being dispensed
        for (const auto& item : model->getCart()) {
            view->dispenseProduct(item.first);
        }
        model->dispenseProduct();
        view->displayChange(change);
    }
