#ifndef ICT_PERISHABLE_H__
#define ICT_PERISHABLE_H__
#include "NonPerishable.h"
#include "Date.h"
namespace ict
{
	class Perishable : public NonPerishable
	{
	private:
		Date m_expiry;
	protected:
		char signature()const;
	public:
		Perishable();
		std::fstream& save(std::fstream&)const;
		std::fstream& load(std::fstream&);
		std::ostream& write(std::ostream&,bool)const;
		std::istream& read(std::istream&);

	};
}






#endif
