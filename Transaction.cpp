/*
* Name: Alon Filler
* ID: 216872374
* */

#include "Transaction.h"
// Initialised m_date to NULL in order to avoid: Clang-Tidy: Constructor does not initialize these fields: m_date
// Transaction constructor which generates a Transaction given all the required fields.
Transaction::Transaction(Account *s, Account *d, double amount, const char *date): m_date(NULL) {
    this->m_source = s;
    this->m_destination = d;
    this->m_amount = amount;
    this->m_date = strdup(date);
}
// Transaction copy constructor.
Transaction::Transaction(const Transaction &other): m_date(NULL){
    this->m_source = other.m_source;
    this->m_destination = other.m_destination;
    this->m_amount = other.m_amount;
    this->m_date = strdup(other.m_date);
}
// Sets a Transaction's m_amount member.
void Transaction::SetAmount(double amount) { this->m_amount = amount; }
// Sets a Transaction's m_date member.
void Transaction::SetDate(const char* date) { this->m_date = strdup(date); }
// Sets a Transaction's m_destination member.
void Transaction::SetDes(Account* dst) { this->m_destination = dst; }
// Sets a Transaction's m_source member.
void Transaction::SetSource(Account* src) { this->m_source = src; }
// Returns a Transaction's m_source member.
Account* Transaction::GetSource() const {return this->m_source; }
// Returns a Transaction's m_destination member.
Account* Transaction::GetDes() const { return this->m_destination; }
// Returns a Transaction's m_amount member.
double Transaction::GetAmount() const { return this->m_amount; }
// Returns a Transaction's m_date member.
char* Transaction::GetDate() const { return this->m_date; }