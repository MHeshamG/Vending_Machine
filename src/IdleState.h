class IdleState : public VendingMachineState{
    public:
        IdleState(VendingMachine* vendingMachine);
        VendingMachineErrorCode insertMoney(double money) override;
        VendingMachineErrorCode selectProduct(std::string productName) override;
        VendingMachineErrorCode dispenseProduct() override;
}