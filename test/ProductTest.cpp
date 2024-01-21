#include <gtest/gtest.h>
#include "Product.h"

using vendingmachine::Product;

class ProductTest : public ::testing::Test {
protected:
    // You can initialize objects to be used in the tests here
    Product product{"Coke", 1.50, "Coca-Cola beverage"};
};

TEST_F(ProductTest, GetName_ReturnsCorrectName) {
    EXPECT_EQ(product.getName(), "Coke");
}

TEST_F(ProductTest, GetPrice_ReturnsCorrectPrice) {
    EXPECT_DOUBLE_EQ(product.getPrice(), 1.50);
}

TEST_F(ProductTest, GetDetails_ReturnsCorrectDetails) {
    EXPECT_EQ(product.getDetails(), "Coca-Cola beverage");
}

TEST_F(ProductTest, GetAndSetQuantity) {
    product.setQuantity(10);
    EXPECT_EQ(product.getQuantity(), 10);

    product.decreaseQuantity(3);
    EXPECT_EQ(product.getQuantity(), 7);
}
