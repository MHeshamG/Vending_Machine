VendingMachineErrorCode IdleState::insertMoney(double money)
{
    vm->setInsertedMoney(money);
    std::cout<<"Money Inserted"<<std::endl;
}

VendingMachineErrorCode IdleState::selectProduct(std::string productName)
{
    return VendingMachineErrorCode::INVALID_OPERATION;
}
VendingMachineErrorCode IdleState::dispenseProduct()
{
    return VendingMachineErrorCode::INVALID_OPERATION;
}