#include "CheckingAccount.h"

using namespace std;

namespace ict{    
	
	// TODO: define CheckingAccount class member functions here  

	void CheckingAccount::chargeFee()
	{
		setBalance(getBalance() - transactionFee);
	}

	CheckingAccount::CheckingAccount(double bal, double tran)
	{
		setBalance(bal);
		transactionFee = tran < 0 ? 0 : tran;
	}

	void CheckingAccount::credit(double bal)
	{
		Account::credit(bal);
		chargeFee();
	}

	bool CheckingAccount::debit(double bal)
	{
		if (Account::debit(bal))
		{
			chargeFee();
			return true;
		}
		return false;
	}

	void CheckingAccount::display(ostream &os)
	{
		os << "Account type: Checking" << endl
			<< "Balance: $ " << fixed << setprecision(2) << getBalance() << endl
			<< "Transaction Fee: " << fixed << setprecision(2) << transactionFee << endl;
	}

}