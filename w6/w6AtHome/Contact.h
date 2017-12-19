// TODO: add header guard
#ifndef CONTACT_H
#define CONTACT_H
#include <iostream>
#include <string>
#include <cstring>
// TODO: add namespace here
namespace communication
{
	class Contact
	{
		char m_name[21];
		long long* m_phoneNumbers;
		int m_noOfPhoneNumbers;
	public:
		// TODO: add the default constructor here
		Contact();
		// TODO: add the constructor with parameters here
		Contact(const char* name, long long* phoneNumbers, int noOfPhoneNumbers);

		// TODO: add the destructor here
		~Contact();
		// TODO: add the display function here
		void display() const;
		// TODO: add the isEmpty function here
		bool isEmpty() const;

		void addPhoneNumber(long long phoneNumber);
	public:
		Contact(const Contact& other);
		Contact& operator=(const Contact& other);
	};
}
#endif
