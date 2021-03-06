/*
 * Name: Alon Filler
 * ID: 216872374
 * */

#include "Bank.h"
// Blank Bank constructor.
Bank::Bank() {
    this->m_account = NULL;
    this->m_bankCode = 0;
    this->m_name = NULL;
    this->m_numbeOfAccounts = 0;
    this->m_totalBalance = 0;
}
// Bank constructor, generates a bank instance out of a name and a code.
Bank::Bank(const char *name, int code) {
    this->m_account = NULL;
    this->m_numbeOfAccounts = 0;
    this->m_totalBalance = 0;
    this->m_bankCode = code;
    this->m_name = strdup(name);
}
// Bank destructor.
Bank::~Bank() {
    int iteration;
    for (iteration = 0; iteration < this->m_numbeOfAccounts; iteration++) delete this->m_account[iteration];
    delete[] this->m_account;
}
// Sets the Bank's m_name member.
void Bank::SetBankName(const char *name) { this->m_name = strdup(name); }
// Sets the Bank's m_bankCode member.
void Bank::SetCode(int code)             { this->m_bankCode = code; }
// Sets the Bank's m_totalBalance member.
void Bank::SetTotal(double total) { this->m_totalBalance = total; }
// Sets the Bank's m_account member.
void Bank::SetAccount(Account **account, int numbeOfAccounts) {
    int iteration;
    this->m_numbeOfAccounts = numbeOfAccounts;
    this->m_account = new Account*[this->m_numbeOfAccounts];
    for (iteration = 0; iteration < this->m_numbeOfAccounts; iteration++)  {
        this->m_account[iteration] = new Account(*account[iteration]);
    }
}
// Returns the Ban's m_name member.
const char* Bank::GetBankName() const { return this->m_name; }
// Returns the Bank's m_account member.
Account** Bank::GetAccounts() const { return this->m_account; }
// Returns the Bank's m_numbeOfAccounts member.
int Bank::GetNumberOfAccounts() const { return this->m_numbeOfAccounts; }
// Returns the Bank's m_totalBalance member.
double Bank::GetTotal() const { return this->m_totalBalance; }
// Returns the Bank's m_bankCode member.
int Bank::GetCode() const { return this->m_bankCode; }
// Adds an Account to the Bank's m_account member.
void Bank::AddAccount(const Account &account) {
    int iteration;
    for (iteration = 0; iteration < this->m_numbeOfAccounts; iteration++)  if (this->m_account[iteration]->GetAccountNumber() == account.GetAccountNumber()) return;
    this->SetTotal(this->GetTotal() + account.GetBalance());
    auto** accountsArray = new Account*[this->m_numbeOfAccounts + 1];
    for (iteration = 0; iteration < this->m_numbeOfAccounts; iteration++) accountsArray[iteration] = new Account(*this->GetAccounts()[iteration]);
    accountsArray[this->m_numbeOfAccounts] = new Account(account);
    this->SetAccount(accountsArray, this->m_numbeOfAccounts + 1);
}
// Add-on function to the main AddAcoount function, converts a person and his wealth into an Account instance which it proceeds to pass over to the main AddAccount function.
void Bank::AddAccount(const Person &per, double amount) {
    AddAccount(Account(per, amount));
}
// Adds a Person to a given Account that is part of the Bank's m_account member.
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
// Deletes an Account from the Bank's m_account member.
void Bank::DeleteAccount(const Account& account) {
    int iteration, index;
    bool flag = false;

    for(iteration = 0; iteration <  this->GetNumberOfAccounts(); iteration++) {
        if (this->GetAccounts()[iteration]->GetAccountNumber() != account.GetAccountNumber()) continue;
        this->SetTotal(this->GetTotal() - account.GetBalance());
        if (this->GetNumberOfAccounts() == 1) {
            delete this->m_account[0];
            delete this->m_account;
            return;
        }
        flag = true;
        break;
    }
    if (!flag) return;

    auto** accountsArray = new Account*[this->GetNumberOfAccounts() - 1];
    for (index = 0; index < this->GetNumberOfAccounts(); index++) {
        if (index == iteration) continue;
        accountsArray[index] = new Account(*this->GetAccounts()[index]);
    }
    this->SetAccount(accountsArray, this->GetNumberOfAccounts() - 1);
}
// Deletes all instances of a certain Person from the Bank's registered Account's m_person member.
void Bank::DeletePerson(const Person &p) {
    int iteration, initialAmountOfPersons;
    for (iteration = 0; iteration < this->m_numbeOfAccounts; iteration++) {
        initialAmountOfPersons = this->GetAccounts()[iteration]->GetTotalPersons();
        this->GetAccounts()[iteration]->DeletePerson(p);
        if (initialAmountOfPersons > this->GetAccounts()[iteration]->GetTotalPersons()) this->DeleteAccount(*this->GetAccounts()[iteration]);
    }
}