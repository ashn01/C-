#ifndef ICT_NONPERISHABLE_H__
#define ICT_NONPERISHABLE_H__
#include "Item.h"

namespace ict
{
	class NonPerishable : public Item
	{
	private:
		char m_err[50];
	protected:
		bool ok() const;
		void error(const char* message);
		virtual char signature()const;

	public:
		NonPerishable();
		std::fstream& save(std::fstream& file)const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream&, bool)const;
		std::istream& read(std::istream&);

	};
}
#endif