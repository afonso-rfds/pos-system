#include "products_database_test.hpp"

void ProductsDatabaseTest::SetUp()
{
    productsDatabaseInstance = ProductsDatabase::getInstance();
}

TEST_F(ProductsDatabaseTest, getInstance)
{
    ASSERT_NO_THROW(ProductsDatabase::getInstance());
    ASSERT_NO_THROW(productsDatabaseInstance->getInstance());
}

TEST_F(ProductsDatabaseTest, findProduct_validProduct)
{
    Product* product = ProductsDatabase::getInstance()->findProduct("0000000000000");

    // Verify that the product was found
    ASSERT_TRUE(product != nullptr);

    EXPECT_EQ(product->EAN13, "0000000000000");
    EXPECT_EQ(product->productName, "Apple");
    EXPECT_DOUBLE_EQ(product->price, 0.5);
    EXPECT_DOUBLE_EQ(product->taxRate, 23);
}

TEST_F(ProductsDatabaseTest, findProduct_invalidProduct)
{
    Product* product = ProductsDatabase::getInstance()->findProduct("0000000000005");

    // Verify that the product was NOT found
    ASSERT_TRUE(product == nullptr);
}