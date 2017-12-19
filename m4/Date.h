// compilation safegaurds
#ifndef ICT_DATE_H_
#define ICT_DATE_H_

#include <iostream>
// ict namespace 
namespace ict {
	// Date defined Error values
#define NO_ERROR 0
#define CIN_FAILED 1
#define YEAR_ERROR 2
#define MON_ERROR 3
#define DAY_ERROR 4
#define HOUR_ERROR 5
#define MIN_ERROR 6

	class Date {
	private:
		// member variables
		int m_year;
		int m_mon;
		int m_day;
		int m_hour;
		int m_min;
		int m_readErrorCode;
		bool m_dateOnly;

		// private methods
		int value()const;
		void errCode(int errorCode);
		int mdays()const;
		void set();
		void set(int year, int mon, int day, int hour, int min);

	public:
		// constructors
		Date();
		Date(int year, int mon, int day);
		Date(int year, int mon, int day, int hour, int min = 0);

		// operator ovrloads
		bool operator==(const Date& D)const;
		bool operator!=(const Date& D)const;
		bool operator<(const Date& D)const;
		bool operator>(const Date& D)const;
		bool operator<=(const Date& D)const;
		bool operator>=(const Date& D)const;


		// methods
		int errCode()const;
		bool bad()const;
		bool dateOnly()const;
		void dateOnly(bool value);


		// istream  and ostream read and write methods

		std::istream& read(std::istream& is = std::cin);
		std::ostream& write(std::ostream& ostr = std::cout)const;

		//int mdays()const;



	};
	// operator<< and >> overload prototypes for cout and cin
	std::ostream& operator<<(std::ostream&, const Date&);
	std::istream& operator>>(std::istream&, Date&);
}

#endif