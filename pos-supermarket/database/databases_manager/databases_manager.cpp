#include "databases_manager.hpp"

Product* DatabasesManager::findProduct(const std::string& EAN13)
{
    return ProductsDatabase::getInstance()->findProduct(EAN13);
}

void DatabasesManager::addInvoice(const Invoice& invoice)
{
    InvoiceDatabase::getInstance()->addInvoice(invoice);
}

void DatabasesManager::printAllInvoices()
{
    InvoiceDatabase::getInstance()->printAllInvoices();
}

void DatabasesManager::removeAllInvoices()
{
    InvoiceDatabase::getInstance()->removeAllInvoices();
}