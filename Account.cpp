//
// Created by sorer on 10/04/2022.
//

#include "Account.h"
Account::Account() {
    this->m_transactionList = NULL;
    this->m_numberOfTransaction = 0;
    this->m_persons = NULL;
    this->m_totalPersons = NULL;
    this->m_accountNumber = NULL;
    this->m_balance = NULL;
}
Account::Account(const Account &other) {
    int iteration;
    this->m_accountNumber = other.m_accountNumber;
    this->m_balance = other.m_balance;
    this->m_numberOfTransaction = other.m_numberOfTransaction;
    this->m_totalPersons = other.m_totalPersons;

    this->m_persons = new Person*[this->m_totalPersons];
    for (iteration =  0; iteration < this->m_totalPersons; iteration++) {
        this->m_persons[iteration] = new Person(*other.m_persons[iteration]);
    }

    this->m_transactionList = new Transaction*[this->m_numberOfTransaction];
    for (iteration = 0; iteration < this->m_numberOfTransaction; iteration++) {
        this->m_transactionList[iteration] = new Transaction(*other.m_transactionList[iteration]);
    }
}
Account::Account(const Person &person, double balance) {
    this->m_numberOfTransaction = 0;
    this->m_transactionList = NULL;
    this->m_accountNumber = 0;
    this->m_balance = balance;
    this->m_totalPersons = 1;

    this->m_persons = new Person*[this->m_totalPersons];
    this->m_persons[0] = new Person(person);
}
Account::Account(Person **persons, int count, double balance) {
    int iteration;
    this->m_numberOfTransaction = 0;
    this->m_transactionList = NULL;
    this->m_accountNumber = 0;
    this->m_balance = balance;
    this->m_totalPersons = count;

    this->m_persons = new Person*[this->m_totalPersons];
    for (iteration = 0; iteration < this->m_totalPersons; iteration++) {
        this->m_persons[iteration] = new Person(*persons[iteration]);
    }
}
Account::~Account() {
    int iteration;
    for (iteration = 0; iteration < this->m_numberOfTransaction; iteration++) {
        delete this->m_persons[iteration];
    }
    delete[] this->m_persons;

    for (iteration = 0; iteration < this->m_totalPersons; iteration++) {
        delete this->m_transactionList[iteration];
    }
    delete[] this->m_transactionList;
}

Person** Account::GetPersons() const { return this->m_persons; }
int Account::GetAccountNumber() const { return this->m_accountNumber; }
double Account::GetBalance() const { return this->m_balance; }
int Account::GetNumOfTransactions() { return this->m_numberOfTransaction; }
int Account::GetTotalPersons() const { return this->m_totalPersons; }
Transaction **Account::GetTransactions() { return this->m_transactionList; }

void Account::SetAccountNumber(int number) { this->m_accountNumber = number; }
void Account::SetBalance(double balance) { this->m_balance = balance; }

void Account::SetPersons(Person **persons, int count) {
    int iteration;
    for (iteration = 0; iteration < this->m_totalPersons; iteration++) {
        delete this->m_persons[iteration];
    }
    delete[] this->m_persons;
    this->m_totalPersons = count;
    this->m_persons = new Person*[this->m_totalPersons];
    for (iteration = 0; iteration < this->m_totalPersons; iteration++) {
        this->m_persons[iteration] = new Person(*persons[iteration]);
    }
}

void Account::SetTransactions(Transaction **newTransaction, int count) {
    int iteration;
    for (iteration = 0; iteration < this->m_numberOfTransaction; iteration++) {
        delete this->m_transactionList[iteration];
    }
    delete this->m_transactionList;

    this->m_numberOfTransaction = count;
    this->m_transactionList = new Transaction*[this->m_numberOfTransaction];
    for (iteration = 0; iteration < this->m_numberOfTransaction; iteration++) {
        this->m_transactionList[iteration] = new Transaction(*newTransaction[iteration]);
    }
}

void Account::clearPersons() {
    int iteration;
    for (iteration = 0; iteration < this->m_totalPersons; iteration++) {
        delete this->m_persons[iteration];
    }
    delete[] this->m_persons;
    this->m_totalPersons = 0;
}

void Account::clearTransactions() {
    int iteration;
    for (iteration = 0; iteration < this->m_numberOfTransaction; iteration++) {
        delete this->m_transactionList[iteration];
    }
    delete[] this->m_transactionList;
}
void Account::AddPerson(const Person &newPerson, double amount) {
    int iteration;
    for (iteration = 0; iteration < this->m_totalPersons; iteration++) if (this->m_persons[iteration]->GetId() == newPerson.GetId()) return;
    auto** personArray = new Person*[this->m_totalPersons + 1];
    for (iteration = 0; iteration < this->m_totalPersons; iteration++) personArray[iteration] = new Person(*this->m_persons[iteration]);
    personArray[this->m_totalPersons] = new Person(newPerson);
    this->SetPersons(personArray, this->m_totalPersons + 1);
    this->SetBalance(this->GetBalance() + amount);
    for (iteration = 0; iteration < this->m_totalPersons; iteration++) delete personArray[iteration];
    delete[] personArray;
}
void Account::AddTransaction(const Transaction &newTransaction) {
    int iteration;
    auto** transactionArray = new Transaction*[newTransaction.GetSource()->m_numberOfTransaction + 1];
    for (iteration = 0; iteration < newTransaction.GetSource()->m_numberOfTransaction; iteration++) {
        transactionArray[iteration] = new Transaction(*newTransaction.GetSource()->m_transactionList[iteration]);
    }
    transactionArray[newTransaction.GetSource()->m_numberOfTransaction] = new Transaction(newTransaction.GetSource(), newTransaction.GetDes(), newTransaction.GetAmount(), newTransaction.GetDate());
    newTransaction.GetSource()->SetTransactions(transactionArray, newTransaction.GetSource()->m_numberOfTransaction + 1);

    for (iteration = 0; iteration < newTransaction.GetSource()->m_numberOfTransaction; iteration++) delete newTransaction.GetSource()->m_transactionList[iteration];
    delete[] transactionArray;
    if (newTransaction.GetSource()->m_accountNumber == newTransaction.GetDes()->m_accountNumber) return;
    transactionArray = new Transaction*[newTransaction.GetDes()->m_numberOfTransaction + 1];
    for (iteration = 0; iteration < newTransaction.GetDes()->m_numberOfTransaction; iteration++) {
        transactionArray[iteration] = new Transaction(*newTransaction.GetDes()->m_transactionList[iteration]);
    }
    transactionArray[newTransaction.GetDes()->m_numberOfTransaction] = new Transaction(newTransaction.GetSource(), newTransaction.GetDes(), newTransaction.GetAmount(), newTransaction.GetDate());
    newTransaction.GetDes()->SetTransactions(transactionArray, newTransaction.GetDes()->m_numberOfTransaction + 1);
    for (iteration = 0; iteration < newTransaction.GetDes()->m_numberOfTransaction; iteration++) delete newTransaction.GetSource()->m_transactionList[iteration];
    delete[] transactionArray;
}
void Account::DeletePerson(const Person &oldPerson) {
    int iteration, indicator = 0;
    for (iteration = 0; iteration < this->m_totalPersons; iteration++) {
        if (this->m_persons[iteration]->GetId() == oldPerson.GetId()) { indicator = 1; break; }
    }
    if (!indicator) return;
    auto** personArray = new Person*[this->m_totalPersons];
    for (iteration = 0; iteration < this->m_totalPersons; iteration++) {
        if (this->m_persons[iteration]->GetId() == oldPerson.GetId()) { indicator = 1; continue; }
        personArray[iteration] = new Person(*this->m_persons[iteration]);
    }
    this->SetPersons(personArray, this->m_totalPersons - 1);

    for (iteration = 0; iteration < this->m_totalPersons; iteration++) delete this->m_persons[iteration];
    delete[] this->m_persons;
}
void Account::Withdraw(double amount, const char *date) {
    this->SetBalance(this->m_balance - amount);
    Transaction transaction(this, this, -1 * amount, date);
    this->AddTransaction(transaction);
}
void Account::Deposit(double amount, const char *date) {
    this->SetBalance(this->m_balance + amount);
    Transaction transaction(this, this, amount, date);
    this->AddTransaction(transaction);
}