#ifndef ICT_ITEM_H__
#define ICT_ITEM_H__
// inlcude PosIO and POS header files
#include "POS.h"
#include "PosIO.h"
#include<iostream>
#include <iomanip>
#include <cstring>

namespace ict{
  // class Item
	class Item : public PosIO{
	private :
		char m_sku[MAX_SKU_LEN+1];
		char* m_name;
		double m_price;
		bool m_taxed;
		int m_quantity;
	public:
		Item();
		Item(const char*, const char*, const double, const bool taxed= true);
		Item(const Item&);
		virtual ~Item();

		void sku(const char*);
		void name(const char*);
		void price(const double);
		void taxed(const bool);
		void quantity(const int);

		const char* sku() const;
		char* name()const;
		double price() const;
		bool taxed() const;
		int quantity() const;
		double cost() const;
		bool isEmpty() const;

		bool operator==(const char*);
		int operator+=(const int);
		int operator-=(const int);
		Item& operator=(const Item&);
		// end class Item
	};
  // operator += 
  double operator+=(double& d, const Item& I);
  // operator << and operator >>
  std::ostream& operator<<(std::ostream&, const Item&);
  std::istream& operator>>(std::istream&, Item&);
}


#endif