#include <iostream>



#include "SuperHero.h"


SuperHero::SuperHero() : Hero()
{
	m_superPowerAttack = 0;
	m_superPowerDefend = 0;
}
        
        
SuperHero::SuperHero( const char* name, unsigned maximumHealth, unsigned attack,
                unsigned superPowerAttack, unsigned superPowerDefend
        )  : Hero(name, maximumHealth, attack)
{ 
	m_superPowerAttack = superPowerAttack;
	m_superPowerDefend = superPowerDefend;
}



  
        
unsigned SuperHero::getAttack() const 
{ 
	return m_superPowerAttack;
}
