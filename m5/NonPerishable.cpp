#define _CRT_SECURE_NO_WARNINGS
// lib includes
#include "NonPerishable.h"
using namespace ict;
bool NonPerishable::ok() const
{
	return (m_err[0] == '\0') ? true : false;
}

void NonPerishable::error(const char* message)
{
	strcpy(m_err, message);
}

char NonPerishable::signature() const
{
	return 'N';
}

NonPerishable::NonPerishable()
{
	m_err[0] = '\0';
}

std::fstream& NonPerishable::save(std::fstream & file) const
{
	file << signature() << "," << sku() << "," << name() << "," << price() << "," << (taxed() ? 1 : 0) << "," << quantity();
	return file;
}

std::fstream& NonPerishable::load(std::fstream & file)
{
	char sk[8];
	char pname[2000];
	double pri;
	int tax;
	int quan;
	file.getline(sk, 8, ',');
	file.getline(pname, 2000, ',');
	file >> pri;
	file.ignore(1, ',');
	file >> tax;
	file.ignore(1, ',');
	file >> quan;

	sku(sk);
	name(pname);
	price(pri);
	taxed(tax == 1 ? true : false);
	quantity(quan);
	return file;
}

std::ostream& NonPerishable::write(std::ostream &os, bool linear) const
{
	if (!ok())
	{
		os << m_err;
	}
	else
	{
		if (linear)
		{
			os << std::left
				<< std::setw(MAX_SKU_LEN) << sku() << "|"
				<< std::setw(20) << name() << "|"
				<< std::right
				<< std::fixed << std::setw(7) << std::setprecision(2) << price() << "|"
				<< " " << (taxed() ? "T" : " ") << signature() << "|"
				<< std::setw(4) << quantity() << "|"
				<< std::fixed << std::setw(9) << std::setprecision(2)<<cost()*quantity()<<"|";
		}
		else
		{
			os << "Name:" << std::endl; 
			os << name() << std::endl;
			os << "Sku: " << sku() << std::endl
				<< "Price: " << std::fixed << std::setprecision(2) << price() << std::endl;
			if (taxed())
				os << "Price after tax: " << std::fixed << std::setprecision(2) << cost() << std::endl;
			else
				os << "Price after tax: " << "N/A" << std::endl;
				os<< "Quantity: " << quantity() << std::endl
				<< "Total Cost: " << std::fixed << std::setprecision(2) << cost()*quantity() << std::endl;
		}
	}
	return os;
}

std::istream& NonPerishable::read(std::istream& is)
{
	char buff[2000];
	double dbuf;
	int ibuf;
	error(""); // init err
	std::cout << "Item Entry:" << std::endl
		<< "Sku: ";
	is >> buff;
	sku(buff);
	is.ignore();
	std::cout << "Name:" << std::endl;
	is.getline(buff,80,'\n'); // to get space in name
	name(buff);
	std::cout << "Price: ";
	is >> dbuf;
	if (is.fail())
	{
		error("Invalid Price Entry");
		return is;
	}
	price(dbuf);
	is.ignore();
	std::cout << "Taxed: ";
	is >> buff;
	if (!(buff[0] == 'y' || buff[0] == 'n'))
	{
		is.setstate(std::ios::failbit);
	}
	if (is.fail())
	{
		error("Invalid Taxed Entry, (y)es or (n)o");
		return is;
	}
	taxed(buff[0] == 'y' ? true : false);
	is.ignore();
	std::cout << "Quantity: ";
	is >> ibuf;
	if (is.fail())
	{
		error("Invalid Quantity Entry");
		return is;
	}
	quantity(ibuf);
	is.ignore();
	
	return is;
}
