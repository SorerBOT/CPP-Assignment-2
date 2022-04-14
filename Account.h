#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "Person.h"
#include "Transaction.h"

class Transaction;

class Account
{
public:
    // Blank Account constructor.
    Account();
    // Account constructor, generates an account out of an array of pointers to Persons.
    Account( Person** persons, int count, double balance );
    // Account constructor, generates an account out of a Person reference.
    Account( const Person& person, double balance );
    // Account copy constructor.
    Account( const Account& other );
    // Account destructor.
    ~Account();

public:
    // Sets the m_persons member of an Account.
    void			SetPersons( Person** persons, int count );
    // Sets the m_accountNumber member of an Account.
    void			SetAccountNumber( int number );
    // Sets the m_balance member of an Account.
    void			SetBalance( double balance );
    // Sets the m_transactionList member of an account.
    void			SetTransactions( Transaction** newTransaction, int count );
    // Returns the m_transactionList member of an account.
    Transaction**	GetTransactions();
    // Returns the m_numberOfTransaction of an Account.
    int				GetNumOfTransactions();
    // Returns the m_persons member of  an Account.
    Person**		GetPersons() const;
    // Returns the m_totalPersons member of an Account.
    int				GetTotalPersons()const;
    // Returns the m_accountNumber member of an Account.
    int				GetAccountNumber() const;
    // Returns the m_balance member of an Account.
    double			GetBalance() const;

public:
    // Creates a Transaction between a user to himself where money is withdrawn from the Account.
    void Withdraw( double amount, const char* date );
    // Creates a Transaction between a user to himself where money is deposited into the Account.
    void Deposit( double amount, const char* date );
    // Adds a Person to the Account's Persons Array.
    void AddPerson( const Person& newPerson, double	amount );
    // Deletes a Person from the Account's Persons Array.
    void DeletePerson( const Person& oldPerson );
    // Adds a Transaction to the Account's Transactions Array.
    void AddTransaction( const Transaction& newTransaction );

private:
    // Clears all the Transactions associated with an Account.
    void clearTransactions();
    // Clears all the Persons associated with an Account.
    void clearPersons();

private:
    Transaction**	m_transactionList;
    int				m_numberOfTransaction;
    Person**		m_persons;
    int				m_totalPersons;
    int				m_accountNumber;
    double			m_balance;
};


#endif //Account.h

