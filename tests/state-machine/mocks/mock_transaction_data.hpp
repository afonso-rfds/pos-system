#pragma once

#include "state_machine/transaction_data/transaction_data.hpp"

#include <gmock/gmock.h>
#include <string>

class MockTransactionData : public TransactionData
{
  public:
    MOCK_METHOD1(addRegisteredProduct, void(const Product& product));
    MOCK_METHOD0(cleanPreviousTransactionData, void);
    MOCK_METHOD1(setCurrentOperator, void(std::string operatorIdentifier));
    MOCK_METHOD1(setRemainingToPay, void(float paymentLeft));
    MOCK_METHOD1(setPaymentMethod, void(const std::string& methodToPay));
    MOCK_METHOD1(setCashChange, void(const float changeToSet));
    MOCK_CONST_METHOD0(getCurrentOperator, const std::string());
    MOCK_CONST_METHOD0(getRemainingToPay, const float());
    MOCK_CONST_METHOD0(getSubtotalPrice, const float());
    MOCK_CONST_METHOD0(getTaxPrice, const float());
    MOCK_CONST_METHOD0(getRegisteredProducts, const std::unordered_map<std::string, std::pair<Product, int>>&());
    MOCK_CONST_METHOD0(getPaymentMethod, const std::string&());
    MOCK_METHOD0(getCashChange, float());
    MOCK_METHOD0(getStoreIdentification, std::string());
};
