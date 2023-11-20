#include <iostream>
#include <string>
#include <utility>

int main() {
    std::pair<std::string, double> pair {"Vending-Machine Version", 1.0};

    const auto& [str, num] = pair;
    std::cout << str << ": " << num << std::endl;

    return 0;
}