#define _CRT_SECURE_NO_WARNINGS
// lib includes





#include "Perishable.h"

char ict::Perishable::signature() const
{
	return 'P';
}

ict::Perishable::Perishable()
{
	m_expiry.dateOnly(true);
}

std::fstream& ict::Perishable::save(std::fstream &file) const
{
	NonPerishable::save(file);
	file << ","<< m_expiry;
	return file;
}

std::fstream& ict::Perishable::load(std::fstream &file)
{
	int yy, mm, dd;
	NonPerishable::load(file);
	file.ignore(1, ',');
	file >> yy;
	file.ignore(1, '/');
	file >> mm;
	file.ignore(1, '/');
	file >> dd;
	return file;
}

std::ostream & ict::Perishable::write(std::ostream &os, bool linear) const
{
	NonPerishable::write(os, linear);
	if (ok() && !linear)
	{
		os << "Expiry date: " << m_expiry << std::endl;
	}
	return os;
}

std::istream & ict::Perishable::read(std::istream &is)
{
	error("");
	std::cout << "Perishable ";
	NonPerishable::read(is);
	if (is.fail())
		return is;
	std::cout << "Expiry date (YYYY/MM/DD): ";
	m_expiry.read(is);
	if (m_expiry.errCode() != NO_ERROR)
	{
		is.setstate(std::ios::failbit);
		switch (m_expiry.errCode())
		{
		case CIN_FAILED :
			error("Invalid Date Entry");
			break;
		case YEAR_ERROR:
			error("Invalid Year in Date Entry");
			break;
		case MON_ERROR:
			error("Invalid Month in Date Entry");
			break;
		case DAY_ERROR:
			error("Invalid Day in Date Entry");
			break;
		}
	}
	return is;
}
