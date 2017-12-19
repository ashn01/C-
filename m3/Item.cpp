#define _CRT_SECURE_NO_WARNINGS  
// Lib includes

// inlcude Item and POS header files
#include "Item.h"
using namespace std;
namespace ict{
  // class Item implementaion
	Item::Item()
	{
	}
	Item::Item(const char* sku, const char* name, const double price, const bool taxed)
	{
		strcpy(m_sku, sku);
		m_name = new char[strlen(name) + 1];
		strcpy(m_name, name);
		m_price = price;
		m_taxed = taxed;
		m_quantity = 0;
	}
	Item::Item(const Item& ref)
	{
		m_sku[0] = '\0';
		m_name = nullptr;
		m_price = 0;
		m_taxed = false;
		m_quantity = 0;
		if(!ref.isEmpty())
			*this = ref;
	}

	Item::~Item()
	{
		if (m_name != nullptr)
		{
			delete[] m_name;
			m_name = nullptr;
		}
	}

	void Item::sku(const char* sku)
	{
		strcpy(m_sku, sku);
	}
	void Item::name(const char* name)
	{
		if (m_name != nullptr)
		{
			delete[] m_name;
			m_name = nullptr;
		}
		m_name = new char[strlen(name) + 1];
		strcpy(m_name, name);
	}
	void Item::price(const double price)
	{
		m_price = price;
	}
	void Item::taxed(const bool taxed)
	{
		m_taxed = taxed;
	}
	void Item::quantity(const int quantity)
	{
		m_quantity = quantity;
	}

	const char* Item::sku() const
	{
		return m_sku;
	}
	char* Item::name() const
	{
		return m_name;
	} 
	double Item::price() const
	{
		return m_price;
	} 
	bool Item::taxed() const
	{
		return m_taxed;
	}
	int Item::quantity() const
	{
		return m_quantity;
	}
	double Item::cost() const
	{
		return m_taxed ? m_price * (1 + TAX) : m_price;
	}
	bool Item::isEmpty() const
	{
		return m_sku[0] == '\0' && m_name == nullptr && m_price == 0 && m_quantity == 0;
	}

	Item& Item::operator=(const Item& ref)
	{
		if (m_name != nullptr)
		{
			delete[] m_name;
			m_name = nullptr;
		}
		m_name = new char[strlen(ref.m_name) + 1];
		strcpy(m_name, ref.m_name);
		strcpy(m_sku, ref.m_sku);
		m_price = ref.m_price;
		m_quantity = ref.m_quantity;
		m_taxed = ref.m_taxed;
		return *this;
	}

	bool Item::operator==(const char* sku)
	{
		return !strcmp(m_sku, sku);
	}
	int Item::operator+=(const int quantity)
	{
		return m_quantity += quantity;
	}
	int Item::operator-=(const int quantity)
	{
		return m_quantity -= quantity;
	}

	double operator+=(double& d, const Item& I)
	{
		return (d += I.cost()*I.quantity());
	}
	std::ostream& operator<<(std::ostream& os, const Item& I)
	{
		I.write(os, false);
		return os;
	}
	std::istream& operator>> (std::istream& is, Item& I)
	{
		I.read(is);
		return is;
	}


}