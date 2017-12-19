#include <iostream>
#include "Contact.h"
#include <crtdbg.h>

using namespace std;
using namespace communication;

int main() {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	communication::Contact theContact("John Doe", nullptr, 0);
	theContact.addPhoneNumber(14161234567);
	theContact.addPhoneNumber(14162345678);
	theContact.addPhoneNumber(14163456789);
	theContact.addPhoneNumber(114164567890);
	theContact.display();

	cout << endl << "Testing! Please wait:" << endl;

	for (int i = 1; i <= 1; i++)
	{
		Contact temp = theContact;
		theContact = temp;
		theContact = theContact;
		if (!(i % 10000))
			cout << ".";
		if (!(i % 500000))
			cout << endl;
	}
	cout << endl;
	theContact.display();
	_CrtDumpMemoryLeaks();

	return 0;
}
