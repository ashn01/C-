#include "SavingsAccount.h"

using namespace std;

namespace ict {
	SavingsAccount::SavingsAccount(double bal, double inte)
	{
		bal >= 0 ? setBalance(bal) : setBalance(1.0);
		interestRate = inte < 0 ? 0 : inte;
	}
	void SavingsAccount::display(ostream& os)
	{
		os << "Account type: Saving" << endl
			<< "Balance: $ " << fixed << setprecision(2) << getBalance() << endl
			<< "Interest Rate (%): " << fixed << setprecision(2) << interestRate * 100 << endl;
	}
	double SavingsAccount::calculateInterest()
	{
		return interestRate * getBalance();
	}
	// TODO: Implement SavingsAccount member functions here
}