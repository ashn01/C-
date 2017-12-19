//TODO: add header guards here
#ifndef HOLIDAY_PASSENGER
#define HOLIDAY_PASSENGER
#include <iostream>
#include <string.h>
// TODO: holiday namespace here
namespace holiday 
{
	// TODO: declare the class Passenger here
	class Passenger
	{
	private:
	// TODO: add the class the attributes,
		char m_name[32];
		char m_destination[32];
		int m_departureYear;
		int m_departureMonth;
		int m_departureDay;
	//       the member function already provided,
	//       and the member functions that you must implement
		void init();
	public:
		Passenger();
		Passenger(const char* name, const char* destination);
		Passenger(const char* name, const char* destination, const int year, const int month, const int day);
		void travelWith(const Passenger* arrPassengers, int size);
		void display(bool onlyNames = false) const;
		bool isEmpty() const;
		bool canTravelWith(const Passenger&) const;
	};
}

#endif
