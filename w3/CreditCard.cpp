#include "CreditCard.h"
using namespace std;
namespace sict {

	CreditCard::CreditCard()
	{
	}


	CreditCard::~CreditCard()
	{
	}

	void CreditCard::name(const char cardHolderName[])
	{
		strcpy(m_cardHolderName, cardHolderName);
	}
	void CreditCard::initialize(unsigned long long creditCardNumber, int instCode, int expiryYear, int expiryMonth, int numberInTheBack)
	{
		m_cardNumber = creditCardNumber;
		m_institutionCode = instCode;
		m_expiryYear = expiryYear;
		m_expiryMonth = expiryMonth;
		m_numberInTheBack = numberInTheBack;
	}
	void CreditCard::write() const
	{
		if (isValid())
		{
			cout << "Cardholder: " << m_cardHolderName << endl;
			cout << "Card Number: " << m_cardNumber << endl;
			cout << "Institution: " << m_institutionCode << endl;
			cout << "Expires: " << m_expiryMonth << "/" << m_expiryYear << endl;
			cout << "Number at the back: " << m_numberInTheBack;
		}
	}
	bool CreditCard::isValid() const
	{
		if (strlen(m_cardHolderName) == 0)
			return false;
		if (m_cardNumber < MIN_CARD_NUMBER || m_cardNumber > MAX_CARD_NUMBER)
			return false;
		if (m_institutionCode < MIN_INST_NUMBER || m_institutionCode > MAX_INST_NUMBER)
			return false;
		if (m_expiryYear < MIN_EXP_YEAR || m_expiryYear > MAX_EXP_YEAR)
			return false;
		if (m_expiryMonth > 12 || m_expiryMonth < 1)
			return false;
		if (m_numberInTheBack >= 100 || m_numberInTheBack < 0)
			return false;
		return true;
	}
}
