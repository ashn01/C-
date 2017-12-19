// TODO: add your headers here
#include "passenger.h"
// TODO: add the namespaces that you will be using here
using namespace std;
	// TODO: holiday namespace here
namespace holiday {
	// TODO: add the default constructor here
	Passenger::Passenger()
	{
		init();
	}
	// TODO: add the constructor with 2 parameters here
	Passenger::Passenger(const char* name, const char* destination)
	{
		if (!(name && *name) || !(destination && *destination)) 
		{
			init();
		}
		else
		{
			strcpy(m_name, name);
			strcpy(m_destination, destination);
			m_departureYear = 2017;
			m_departureMonth = 7;
			m_departureDay = 1;
		}
	}

	void Passenger::init()
	{
		m_departureYear = 0;
		m_departureMonth = 0;
		m_departureDay = 0;
		strcpy(m_name, "");
		strcpy(m_destination, "");
	}
	// TODO: add the canTravelWith(...) function here
	bool Passenger::canTravelWith(const Passenger& pasg) const
	{
		if (pasg.m_departureYear == m_departureYear && pasg.m_departureMonth == m_departureMonth
			&& pasg.m_departureDay == m_departureDay && !strcmp(pasg.m_destination, m_destination))
		{
			return true;
		}
		return false;
	}
	// TODO: add the isEmpty() function here
	bool Passenger::isEmpty() const
	{
		if (!m_departureYear && !m_departureMonth && !m_departureDay
			&& !strcmp(m_name, "") && !strcmp(m_destination, ""))
		{
			return true;
		}
		return false;
	}
	// below is the member function already provided
	// TODO: read it and understand how it accomplishes its task
	void Passenger::display(bool nameOnly) const
	{
		if (false == this->isEmpty())
		{
			cout << this->m_name;
			if (false == nameOnly)
			{
				cout << " will travel to " << this->m_destination << ". "
					<< "The journey will start on "
					<< this->m_departureYear << "-"
					<< this->m_departureMonth << "-"
					<< this->m_departureDay
					<< "." << endl;
			}
		}
		else
		{
			cout << "Invalid passenger!" << endl;
		}
	}

}