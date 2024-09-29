#pragma once

#include "database/databases_manager/databases_manager.hpp"
#include "invoice/invoice.hpp"
#include "products/products.hpp"

#include <gmock/gmock.h>
#include <string>

class MockDatabasesManager : public DatabasesManager
{
  public:
    MOCK_METHOD1(findProduct, Product*(const std::string& EAN13));
    MOCK_METHOD1(addInvoice, void(const Invoice& invoice));
    MOCK_METHOD0(printAllInvoices, void());
    MOCK_METHOD0(removeAllInvoices, void());
};
