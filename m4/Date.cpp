#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include <ctime>
using namespace std;
#include "Date.h"
#include "POS.h"


namespace ict {

	// date

	Date::Date()
	{
		m_dateOnly = false;
		set();
	}

	Date::Date(int year, int mon, int day)
	{
		m_dateOnly = true;
		m_year = year;
		m_mon = mon;
		m_day = day;
		m_hour = 0;
		m_min = 0;
		m_readErrorCode = NO_ERROR;
	}

	Date::Date(int year, int mon, int day, int hour, int min)
	{
		m_dateOnly = false;
		set(year, mon, day, hour, min);
	}

	// private

	int Date::value()const {
		return m_year * 535680 + m_mon * 44640 + m_day * 1440 + m_hour * 60 + m_min;
	}

	void Date::errCode(int errorCode)
	{
		m_readErrorCode = errorCode;
	}

	int Date::mdays()const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int mon = m_mon >= 1 && m_mon <= 12 ? m_mon : 13;
		mon--;
		return days[mon] + int((mon == 1)*((m_year % 4 == 0) && (m_year % 100 != 0)) || (m_year % 400 == 0));
		// check yoon dal.
	}

	void Date::set() {
		time_t t = time(NULL);
		tm lt = *localtime(&t);
		m_day = lt.tm_mday;
		m_mon = lt.tm_mon + 1;
		m_year = lt.tm_year + 1900;
		if (dateOnly()) {
			m_hour = m_min = 0;
		}
		else {
			m_hour = lt.tm_hour;
			m_min = lt.tm_min;
		}
	}

	void Date::set(int year, int mon, int day, int hour, int min)
	{
		m_year = year;
		m_mon = mon;
		m_day = day;
		m_hour = hour;
		m_min = min;
		m_readErrorCode = NO_ERROR;
	}

	// operator

	bool Date::operator==(const Date& D)const
	{
		return this->value() == D.value() ? true : false;
	}
	bool Date::operator!=(const Date& D)const
	{
		return this->value() != D.value() ? true : false;
	}
	bool Date::operator<(const Date& D)const
	{
		return this->value() < D.value() ? true : false;
	}
	bool Date::operator>(const Date& D)const
	{
		return this->value() > D.value() ? true : false;
	}
	bool Date::operator<=(const Date& D)const
	{
		return this->value() <= D.value() ? true : false;
	}
	bool Date::operator>=(const Date& D)const
	{
		return this->value() >= D.value() ? true : false;
	}

	// member

	int Date::errCode()const
	{
		return m_readErrorCode;
	}
	bool Date::bad()const
	{
		return m_readErrorCode != 0 ? true : false;
	}
	bool Date::dateOnly()const
	{
		return m_dateOnly;
	}
	void Date::dateOnly(bool value)
	{
		m_dateOnly = value;
		if (value)
		{
			m_hour = 0;
			m_min = 0;
		}
	}

	std::istream& Date::read(std::istream& is)
	{
		m_readErrorCode = NO_ERROR; //  init
		bool format=false; // format check
		int y, m, d, h, mm;

		is >> y;
		if (is.get() == '/')
		{
			is >> m;
			if (is.get() == '/')
			{
				is >> d;
				format=true;
				if (is.get() == ','&& is.get() == ' ')
				{
					is >> h;
					if (is.get() == ':')
					{
						is >> mm;
					}
				}
				else
					is.putback('\n');
			}
		}


		if (is.fail())
			m_readErrorCode = CIN_FAILED;
		else if(format)
		{
			m_year = y;
			m_mon = m;
			m_day = d;
			if (!dateOnly())
			{
				m_hour = h;
				m_min = mm;
			}

			if (y >= MIN_YEAR && y <= MAX_YEAR)
			{
				if (m >= 1 && m <= 12)
				{
					if (d < 1 || d > mdays())
					{
						m_readErrorCode = DAY_ERROR;
					}
				}
				else
				{
					m_readErrorCode = MON_ERROR;
				}
			}
			else
			{
				m_readErrorCode = YEAR_ERROR;
			}
			if (!dateOnly())
			{
				if (h >= 1 && h <= 24)
				{
					if (mm < 0 || mm > 59)
						m_readErrorCode = MIN_ERROR;
				}
				else
				{
					m_readErrorCode = HOUR_ERROR;
				}

			}
		}
		return is;

	}
	std::ostream& Date::write(std::ostream& ostr)const
	{

		ostr << m_year << "/";
		if (m_mon < 10)
			ostr << "0";
		ostr << m_mon << "/";

		if (m_day < 10)
			ostr << "0";
		ostr << m_day;
		if (!m_dateOnly)
		{
			ostr << ", ";
			if (m_hour < 10)
				ostr << "0";
			ostr << m_hour << ":";
			if (m_min < 10)
				ostr << "0";
			ostr << m_min;
		}
		return ostr;
	}


	ostream& operator<<(ostream& os, const Date& B)
	{
		B.write(os);
		return os;
	}
	istream& operator >> (istream& is, Date& B)
	{
		B.read(is);
		return is;
	}
}
