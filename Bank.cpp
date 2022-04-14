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
    this->m_name = strdup(name);
}
Bank::~Bank() {
    int iteration;
    for (iteration = 0; iteration < this->m_numbeOfAccounts; iteration++) delete this->m_account[iteration];
    delete[] this->m_account;
}
void Bank::SetBankName(const char *name) { this->m_name = strdup(name); }
void Bank::SetCode(int code)             { this->m_bankCode = code; }
void Bank::SetTotal(double total) { this->m_totalBalance = total; }
void Bank::SetAccount(Account **account, int numbeOfAccounts) {
    int iteration;
    this->m_numbeOfAccounts = numbeOfAccounts;
    this->m_account = new Account*[this->m_numbeOfAccounts];
    for (iteration = 0; iteration < this->m_numbeOfAccounts; iteration++)  {
        this->m_account[iteration] = new Account(*account[iteration]);
    }
}

const char* Bank::GetBankName() const { return this->m_name; }
Account** Bank::GetAccounts() const { return this->m_account; }
int Bank::GetNumberOfAccounts() const { return this->m_numbeOfAccounts; }
double Bank::GetTotal() const { return this->m_totalBalance; }
int Bank::GetCode() const { return this->m_bankCode; }

void Bank::AddAccount(const Account &account) {
    int iteration;
    for (iteration = 0; iteration < this->m_numbeOfAccounts; iteration++)  if (this->m_account[iteration]->GetAccountNumber() == account.GetAccountNumber()) return;
    this->SetTotal(this->GetTotal() + account.GetBalance());
    auto** accountsArray = new Account*[this->m_numbeOfAccounts + 1];
    for (iteration = 0; iteration < this->m_numbeOfAccounts; iteration++) accountsArray[iteration] = new Account(*this->GetAccounts()[iteration]);
    accountsArray[this->m_numbeOfAccounts] = new Account(account);
    this->SetAccount(accountsArray, this->m_numbeOfAccounts + 1);
}
void Bank::AddAccount(const Person &per, double amount) {
    AddAccount(Account(per, amount));
}
void Bank::AddPerson(const Person &newPerson, const Account &account, double amount) {
    int iteration, indicator, index;
    bool flag = false;
    for (iteration = 0; iteration < this->m_numbeOfAccounts; iteration++) {
        if (this->m_account[iteration]->GetAccountNumber() != account.GetAccountNumber()) continue;
        for (indicator = 0; indicator < this->m_account[iteration]->GetTotalPersons(); indicator++) {
            if (this->m_account[iteration]->GetPersons()[indicator]->GetId() == newPerson.GetId()) return;
        }
        index = iteration;
        flag = true;
        break;
    }
    if (flag) { this->m_account[index]->AddPerson(newPerson, amount); return; }
    Account acc(newPerson, amount);
    this->AddAccount(acc);
    this->SetTotal(this->GetTotal() + amount);
}
void Bank::DeleteAccount(const Account& account) {
    delete &account;
}
void Bank::DeletePerson(const Person &p) {
    int iteration;
    for (iteration = 0; iteration < this->m_numbeOfAccounts; iteration++) {
        this->m_account[iteration]->DeletePerson(p);
    }
}