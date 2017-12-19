#include "Account.h"

using namespace std;

namespace ict{ 
	
	// constructor   
	

	// credit (add) an amount to the account balance

	
	// debit (subtract) an amount from the account balance return bool 


	double Account::getBalance() const
	{
		return balance;
	} 

	void Account::setBalance( double newBalance )
	{
		balance = newBalance;
	}

	// TODO: Write a prototype for constructor which initializes balance

	Account::Account()
	{
		setBalance(1.0);
	}

	Account::Account(double bal)
	{
		bal >= 0 ? setBalance(bal) : setBalance(1.0);
	}
	void Account::credit(double bal)
	{
		balance += bal;
	}
	bool Account::debit(double bal)
	{
		if (balance > bal)
		{
			balance -= bal;
			return true;
		}
		return false;
	}
}