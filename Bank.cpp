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