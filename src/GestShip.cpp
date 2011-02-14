#include "GestShip.h"

using namespace std;

GestShip::GestShip()
{
   lstShip.clear();
}

GestShip::~GestShip()
{
}

void GestShip::addShip(ShipAbstract * ship)
{
    lstShip.push_back(ship);
}


void GestShip::updateShips()
{
    vector<ShipAbstract *>::iterator itShip;
    for(itShip=lstShip.begin(); itShip<lstShip.end();itShip++)
    {
        (*itShip)->updatePosition();
		if ((*itShip)->getSpeed()<1)
		{
			(*itShip)->setSpeed((*itShip)->getSpeed()+1);
		}
		(*itShip)->updatePosition();
    }
}

void GestShip::deleteAllShips()
{
    vector<ShipAbstract *>::iterator itShip;
    for(itShip=lstShip.begin(); itShip<lstShip.end();itShip++)
    {
        delete (*itShip);
    }
}


