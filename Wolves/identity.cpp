#include "identity.h"

identity::identity(id_type new_id)
{
	t = new_id;
	protection = false;
	die = false;
	lastBeProtected = 50;
	lover = false;
	officer = false;
	life = 1;
	if (t == id_witch)
	{
		poison = true;
		medicion = true;
	}
	else
	{
		poison = false;
		medicion = false;
	}
}

identity::~identity(){}

bool identity::getProtection()
{
	return protection;
}

void identity::beProtected()
{
	protection = true;
	lastBeProtected = 0;
}

void identity::cancelProtected()
{
	timeGoOn();
	protection = false;
}

bool identity::beDead()
{
	return die;
}

int identity::getLastBeProtected()
{
	return lastBeProtected;
}

void identity::timeGoOn()
{
	lastBeProtected++;
}

bool identity::getPoison()
{
	return poison;
}

void identity::usePoison()
{
	poison = false;
}

bool identity::getMedicion()
{
	return medicion;
}

void identity::useMedicion()
{
	medicion = false;
}

bool identity::getLover()
{
	return lover;
}

void identity::setLover()
{
	lover = true;
}

int identity::getLife()
{
	return life;
}

void identity::BeHurted()
{
	life--;
}

void identity::BeSaved()
{
	life++;
}

bool identity::getOfficer()
{
	return officer;
}

void identity::setOfficer()
{
	officer = true;
}

id_type identity::getID()
{
	return t;
}

void identity::goDie()
{
	die = true;
}

void identity::cancelOfficer()
{
	officer = false;
}