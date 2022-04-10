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