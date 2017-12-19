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


// TODO: include the necessary headers
#include "kingdom.h"
#include <iostream>
#include <string.h>
// TODO: the westeros namespace
using namespace westeros;
using namespace std;
// TODO:definition for display(...) 
void westeros::display(Kingdom kd)
{
	std::cout << kd.m_name << ", population " << kd.m_population << std::endl;
}

void westeros::display(Kingdom kd[], int numOfEl)
{
	int sum = 0;
	cout << "------------------------------" << endl;
	cout << "Kingdoms of Westeros" << endl;
	cout << "------------------------------" << endl;
	for (int i = 0; i < numOfEl; i++)
	{
		cout << i+1<<". "<<kd[i].m_name<<", "<< "population "<<kd[i].m_population << endl;
		sum += kd[i].m_population;
	}
	cout << "------------------------------" << endl;
	cout <<"Total population of Westeros: "<< sum<< endl;
	cout << "------------------------------" << endl;
}

void westeros::display(Kingdom kd[], int numOfEl, int minPeople) 
{
	cout << "------------------------------" << endl;
	cout << "Kingdoms of Westeros with more than " << minPeople << " people" << endl;
	cout << "------------------------------" << endl;
	for (int i = 0; i < numOfEl; i++)
	{
		if (kd[i].m_population >= minPeople)
		{
			cout << kd[i].m_name << ", population " << kd[i].m_population << endl;
		}
	}
	cout << "------------------------------" << endl;
}


void westeros::display(Kingdom kd[], int numOfEl, const char* nameOfKd)
{
	cout << "------------------------------" << endl;
	cout << "Searching for kingdom " << nameOfKd << " in Westeros" << endl;
	cout << "------------------------------" << endl;
	for (int i = 0; i < numOfEl; i++)
	{
		if (!strcmp(nameOfKd, kd[i].m_name))
		{
			cout << kd[i].m_name << ", population " << kd[i].m_population << endl;
			cout << "------------------------------" << endl;
			return;
		}
	}
	cout << nameOfKd << " is not part of Westeros." << endl;
	cout << "------------------------------\n" << endl;
}
