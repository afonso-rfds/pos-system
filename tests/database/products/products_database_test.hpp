#include "products/products_database/products_database.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

class ProductsDatabaseTest : public ::testing::Test
{
  protected:
    void SetUp() override;

    ProductsDatabase* productsDatabaseInstance;
};