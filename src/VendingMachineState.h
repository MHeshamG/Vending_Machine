class VendingMachineState
{
    public:
        virtual VendingMachineErrorCode insertMoney(double money) = 0;
        virtual VendingMachineErrorCode selectProduct(std::string productName) = 0;
        virtual VendingMachineErrorCode dispenseProduct() = 0;
    protected:
    std::shared_ptr<VendingMachine> vm;
    private:
}
