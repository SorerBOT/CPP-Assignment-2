//
// Created by sorer on 10/04/2022.
//

#include "Transaction.h"
// Initialised m_date to NULL in order to avoid: Clang-Tidy: Constructor does not initialize these fields: m_date
Transaction::Transaction(Account *s, Account *d, double amount, const char *date): m_date(NULL) {
    this->m_source = s;
    this->m_destination = d;
    this->m_amount = amount;
    strcpy(this->m_date, date);
}
Transaction::Transaction(const Transaction &other): m_date(NULL){
    this->m_source = other.m_source;
    this->m_destination = other.m_destination;
    this->m_amount = other.m_amount;
    strcpy(this->m_date, other.m_date);
}

void Transaction::SetAmount(double amount) {
    this->m_amount = amount;
}
void Transaction::SetDate(const char* date) {
    strcpy(this->m_date, date);
}
void Transaction::SetDes(Account* dst) {
    this->m_destination = dst;
}
void Transaction::SetSource(Account* src) {
    this->m_source = src;
}

Account* Transaction::GetSource() const {
    return this->m_source;
}
Account* Transaction::GetDes() const {
    return this->m_destination;
}
double Transaction::GetAmount() const {
    return this->m_amount;
}
char* Transaction::GetDate() const {
    return this->m_date;
}