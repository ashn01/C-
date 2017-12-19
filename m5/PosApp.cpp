#include "PosApp.h"
#define _CRT_SECURE_NO_WARNINGS

ict::PosApp::PosApp(const char *filename, const char *billfname)
{
	strcpy(m_filename, filename);
	strcpy(m_billfname, billfname);
	m_noOfItems = 0;
	loadRecs();
}

void ict::PosApp::run()
{
	int answer=1;
	char sku[MAX_SKU_LEN];
	int index;
	while (answer)
	{
		answer=menu();
		std::cin.ignore();
		switch (answer)
		{
		case 1:
			std::cout << "\n";
			listItems();
			break;
		case 2:
			std::cout << "\n";
			addItem(true);
			break;
		case 3:
			std::cout << "\n";
			addItem(false);
			break;
		case 4:
			std::cout << "\n";
			updateQty();
			break;
		case 5:
			std::cout << "\nPlease enter the SKU: ";
			std::cin >> sku;
			index = searchItems(sku);
			if (index != -1)
			{
				std::cout << "v-----------------------------------v" << std::endl;
				m_items[index]->write(std::cout, false);
				std::cout << "^-----------------------------------^" << std::endl<<std::endl;
			}
			else
				std::cout << "Not found!" << std::endl;
			break;
		case 6:
			std::cout << "\n";
			POS();
			break;
		case 0:
			std::cout << "\nGoodbye!\n";
			break;
		default:
			std::cout << "\n===Invalid Selection, try again===" << std::endl;
		}
	}
}

int ict::PosApp::menu()
{
	int answer = -1;
	std::cout << "The Sene-Store\n1- List items\n2- Add Perishable item\n3- Add Non-Perishable item\n4- Update item quantity\n5- Show Item\n6- POS\n0- exit program\n> ";
	std::cin >> answer;
	if (std::cin.fail() || !(answer >= 0 && answer <= 6))
		answer = -1;
	return answer;
}

void ict::PosApp::deallocateItems()
{
	for (int i = 0; i < m_noOfItems; i++)
		delete m_items[i];
	m_noOfItems = 0;
}

void ict::PosApp::loadRecs()
{
	std::fstream fs;
	deallocateItems();
	fs.open(m_filename,std::ios::in); // need to know open method's parameters.
	if (fs.fail())
	{
		fs.clear();
		fs.close();
		fs.open(m_filename, std::ios::out);
	}
	else
	{
		while (!fs.eof())
		{
			char type;
			fs >> type;
			if ((type == 'P' || type == 'N') && !fs.eof())
			{
				fs.get();
				m_items[m_noOfItems] = (type == 'P' ? new Perishable : new NonPerishable);
				m_items[m_noOfItems]->load(fs);
				m_noOfItems++;
			}
		}
	}
	fs.clear();
	fs.close();
}

void ict::PosApp::saveRecs()
{
	std::fstream fs;
	fs.open(m_filename, std::ios::out);
	for (int i = 0; i < m_noOfItems; i++)
	{
		if (m_items[i]->quantity() > 0)
		{
			if (i != 0)
				fs << '\n';
			m_items[i]->save(fs);
		}
	}
	fs.clear();
	fs.close();
	loadRecs();
}

int ict::PosApp::searchItems(const char *sku) const
{
	for (int i = 0; i < m_noOfItems; i++)
	{
		if (*m_items[i] == sku)
			return i;
	}
	return -1;
}

void ict::PosApp::updateQty()
{
	char sku[MAX_SKU_LEN];
	int index=0;
	std::cout << "Please enter the SKU: ";
	std::cin >> sku;
	index=searchItems(sku);
	if (index != -1)
	{
		int add=0;
		m_items[index]->write(std::cout, false);
		std::cout << "\nPlease enter the number of purchased items: ";
		std::cin >> add;
		*m_items[index] += add;
		std::cout << "Updated!\n"<<std::endl;
	}
	else
	{
		std::cout << "Not found!\n";
	}
}

void ict::PosApp::addItem(bool isPerishable)
{
	Item* item = isPerishable ? new Perishable : new NonPerishable;
	std::cin >> *item;
	if (std::cin.fail())
	{
		std::cin.clear();
		std::cout << *item<<std::endl;
	}
	else
	{
		m_items[m_noOfItems++] = item;
		saveRecs();
		std::cout << "Item added.\n"<<std::endl;
	}
}

void ict::PosApp::listItems() const
{
	double total = 0;
	std::cout << " Row | SKU    | Item Name          | Price |TX |Qty |   Total |\n-----|--------|--------------------|-------|---|----|---------|"<<std::endl;
	for (int i = 0; i < m_noOfItems; i++)
	{
		std::cout << std::setw(4)<<std::right<<i+1<< " |";
		std::cout <<" "<< *m_items[i] << std::endl;
		total += (m_items[i]->cost()) * (m_items[i]->quantity());
	}
	std::cout << "-----^--------^--------------------^-------^---^----^---------^"<<std::endl;
	std::cout << std::setw(48)<<"Total Asset: $  |" << std::setw(14) << std::fixed << std::right << std::setprecision(2) << total << "|" << std::endl;;
	std::cout << "-----------------------------------------------^--------------^" << std::endl << std::endl;
}

void ict::PosApp::truncateBillFile()
{
	std::fstream fs;
	fs.open(m_billfname,std::ios::out | std::ios::trunc);
	fs.close();
}

void ict::PosApp::showBill()
{
	std::fstream fs;
	fs.open(m_billfname, std::ios::in);
	char type;
	Item *i;
	Date d;
	double total=0;
	
	if (!fs.fail())
	{
		std::cout << "v--------------------------------------------------------v" << std::endl;
		std::cout << "| " <<d << std::setw(39)<<"|" << std::endl;
		std::cout << "| SKU    | Item Name          | Price |TX |Qty |   Total |" << std::endl;
		std::cout << "|--------|--------------------|-------|---|----|---------|" << std::endl;

		while (!fs.eof())
		{
			fs >> type;
			fs.get(); // remove ,

			i = type == 'P' ? new Perishable : new NonPerishable;
			i->load(fs);
			total += i->cost();
			std::cout << "| ";
			std::cout << *i << std::endl;
		}
		std::cout << "^--------^--------------------^-------^---^----^---------^" << std::endl;
		std::cout << "|                               Total: $  |" << std::fixed << std::setprecision(2) <<std::setw(14)<< std::right << total << "|" << std::endl;
		std::cout << "^-----------------------------------------^--------------^" << std::endl<<std::endl;
	}
	fs.clear();
	fs.close();
	truncateBillFile();
}

void ict::PosApp::addToBill(Item &I)
{
	int qt=0;
	std::fstream fs;
	qt = I.quantity();
	I.quantity(1);
	fs.open(m_billfname, std::ios::out | std::ios::app);
	I.save(fs);
	I.quantity(--qt);
	saveRecs();
}

void ict::PosApp::POS()
{
	char sku[MAX_SKU_LEN];
	while (sku[0]!='\0')
	{
		std::cout << "Sku: ";
		std::cin.getline(sku,MAX_SKU_LEN,'\n'); // searched how getline work, and parameters

		if (sku[0] == '\0')
		{
			showBill();
			break;
		}

		if (searchItems(sku) != -1)
		{
			for (int i = 0; i < m_noOfItems; i++)
			{
				if (!strcmp(sku, m_items[i]->sku()))
				{
					std::cout << "v------------------->" << std::endl;
					std::cout << "| " << m_items[i]->name() << std::endl;
					std::cout << "^------------------->" << std::endl;
					addToBill(*m_items[i]);
					break;
				}
			}
		}
		else
		{
			std::cout << "Not found!" << std::endl;
		}
	}
}
