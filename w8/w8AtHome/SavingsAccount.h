#ifndef ICT_SAVINGSACCOUNT_H__
#define ICT_SAVINGSACCOUNT_H__

#include "Account.h"
#include <iomanip>

using namespace std;

namespace ict {
	class SavingsAccount : public Account {
	private:
		double interestRate; // interest rate (percentage)
	public:
		// TODO: put prototypes here
		SavingsAccount(double, double);
		virtual void display(ostream&);
		double calculateInterest();
	};
};
#endif
