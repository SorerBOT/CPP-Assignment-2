//
// Created by sorer on 10/04/2022.
//

#include "Transaction.h"
// Initalised m_date to NULL in order to avoid: Clang-Tidy: Constructor does not initialize these fields: m_date
Transaction::Transaction(Account *s, Account *d, double amount, const char *date): m_date(NULL) {
    this->m_source = s;
    this->m_destination = d;
    this->m_amount = amount;
    strcpy(this->m_date, date);
}