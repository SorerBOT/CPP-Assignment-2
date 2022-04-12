//
// Created by sorer on 10/04/2022.
//

#include "Bank.h"

Bank::Bank() {
    this->m_account = NULL;
    this->m_bankCode = 0;
    this->m_name = NULL;
    this->m_numbeOfAccounts = 0;
    this->m_totalBalance = 0;
}
Bank::Bank(const char *name, int code) {
    this->m_account = NULL;
    this->m_numbeOfAccounts = 0;
    this->m_totalBalance = 0;
    this->m_bankCode = code;
    strcpy(this->m_name, name);
}
Bank::~Bank() {
    int iteration;
    for (iteration = 0; iteration < this->m_numbeOfAccounts; iteration++) delete this->m_account[iteration];
    delete[] this->m_account;
}
void Bank::SetBankName(const char *name) { strcpy(this->m_name, name); }
void Bank::SetCode(int code)             { this->m_bankCode = code; }
void Bank::SetTotal(double total) { this->m_totalBalance = total; }
void Bank::SetAccount(Account **account, int numbeOfAccounts) {
    int iteration;
    for (iteration = 0; iteration < this->m_numbeOfAccounts; iteration++) delete this->m_account[iteration];
    delete[] this->m_account;

    this->m_numbeOfAccounts = numbeOfAccounts;
    this->m_account = new Account*[this->m_numbeOfAccounts];

    for (iteration = 0; iteration < this->m_numbeOfAccounts; iteration++) this->m_account[iteration] = new Account(*account[iteration]);

    for (iteration = 0; iteration < numbeOfAccounts; iteration++) delete account[iteration];
    delete[] account;
}

const char* Bank::GetBankName() const { return this->m_name; }
Account** Bank::GetAccounts() const { return this->m_account; }
int Bank::GetNumberOfAccounts() const { return this->m_numbeOfAccounts; }
double Bank::GetTotal() const { return this->m_totalBalance; }
int Bank::GetCode() const { return this->m_bankCode; }

void Bank::AddAccount(const Account &account) {
    int iteration;
    auto** accountsArray = new Account*[this->m_numbeOfAccounts + 1];
    for (iteration = 0; iteration < this->m_numbeOfAccounts; iteration++) accountsArray[iteration] = new Account(*this->m_account[iteration]);
    accountsArray[this->m_numbeOfAccounts] = new Account(account);
    this->SetAccount(accountsArray, this->m_numbeOfAccounts + 1);
    for (iteration = 0; iteration < this->m_numbeOfAccounts; iteration++) delete accountsArray[iteration];
    delete[] accountsArray;
}