#include "Contact.h"

using namespace communication;

// TODO: add the default constructor here
Contact::Contact()
{
	// safe empty
	m_name[0] = '\0';
	m_phoneNumbers = nullptr;
	m_noOfPhoneNumbers = 0;
}
// TODO: add the constructor with parameters here
Contact::Contact(const char* name, long long* phoneNumbers, int noOfPhoneNumbers)
{
	if (name)
	{
		m_phoneNumbers = new long long[noOfPhoneNumbers];
		strncpy(m_name,name, sizeof(m_name) - 1);
		m_name[sizeof(m_name)-1] = '\0';
		m_noOfPhoneNumbers = noOfPhoneNumbers;
		//memcpy(m_phoneNumbers, phoneNumbers, sizeof(m_phoneNumbers));
		for (int i = 0; i < noOfPhoneNumbers; i++)
		{
			m_phoneNumbers[i] = phoneNumbers[i];
		}
	}
	else
	{
		m_name[0] = '\0';
		m_phoneNumbers = nullptr;
		m_noOfPhoneNumbers = 0;
	}
}


Contact::Contact(const Contact& ref)
{
	m_phoneNumbers = nullptr;
	*this = ref;
}

// TODO: add the destructor here
Contact::~Contact()
{
	if (m_phoneNumbers != nullptr)
	{
		delete[] m_phoneNumbers;
	}
}


Contact& Contact::operator=(const Contact& ref)
{
	if (&ref != this) {
		strcpy(m_name, ref.m_name);
		m_noOfPhoneNumbers = ref.m_noOfPhoneNumbers;
		if (m_phoneNumbers != nullptr)
		{
			delete[] m_phoneNumbers;
		}

		m_phoneNumbers = new long long[m_noOfPhoneNumbers];

		for (int i = 0; i < m_noOfPhoneNumbers; i++)
		{
			m_phoneNumbers[i] = ref.m_phoneNumbers[i];
		}
	}
	return *this;
}


// TODO: add the display function here
void Contact::display() const
{
	if (isEmpty())
	{
		std::cout << "Empty contact!" << std::endl;
	}
	else
	{
		std::cout << m_name << std::endl;
		for (int i = 0; i < m_noOfPhoneNumbers; i++)
		{
			//std::cout << m_phoneNumbers[i] << std::endl;

			std::string str = std::to_string(m_phoneNumbers[i]);
			if (str.length() > 10 && str.length() < 13)
			{
				int temp = str.length() == 11 ? 1 : 2;
				std::cout << "(+" << str.substr(0,temp) << ") "
					<< str.substr(temp,3) << " "
					<< str.substr(temp+3,3) << "-"
					<< str.substr(temp+6,4)
					<< std::endl;
			}
		}
	}
}
// TODO: add the isEmpty function here
bool Contact::isEmpty() const
{
	return !m_name || !(*m_name) ? true : false;
}


void Contact::addPhoneNumber(long long phoneNumber)
{
	long long* temp = new long long[m_noOfPhoneNumbers+1];
	for (int i = 0; i < m_noOfPhoneNumbers; i++)
	{
		temp[i] = m_phoneNumbers[i];
	}
	temp[m_noOfPhoneNumbers] = phoneNumber;

	if (m_phoneNumbers != nullptr)
	{
		delete[] m_phoneNumbers;
	}

	m_noOfPhoneNumbers++;
	m_phoneNumbers = new long long[m_noOfPhoneNumbers];

	for (int i = 0; i < m_noOfPhoneNumbers; i++)
	{
		m_phoneNumbers[i] = temp[i];
	}

	delete[] temp;
}