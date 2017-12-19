// OOP244 Workshop ??: ??????????
// File ???????
// Version 1.0
// Date ???????????
// Author ?????????
// Description
// ?????????????????????
//
//
// Revision History
///////////////////////////////////////////////////////////
// Name     Date    Reason
// 
///////////////////////////////////////////////////////////


// TODO: header safeguards
#pragma once

// TODO: westeros namespace
namespace westeros {
// TODO: define the class Kingdom in the westeros namespace
	class Kingdom {
		// TODO: add the declaration for the function display(...),
		//         also in the westeros namespace
	public:
		char m_name[32];
		int m_population;
	};
	void display(Kingdom kd);
}