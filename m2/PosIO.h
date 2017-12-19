#ifndef ICT_POSIO_H__
#define ICT_POSIO_H__
// includes go here

namespace ict {
	// ict namespace

	class PosIO {
	public:
		// pure virutal methods go here
		std::fstream& save(std::fstream& file)const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear)const;
		std::istream& read(std::istream& is);
	};

}
#endif