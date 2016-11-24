#pragma once
#include <QString>
#include "identity.h"

struct player
{
	QString name;
	identity *id;
	player()
	{
		name = "";
		id = nullptr;
	}
	~player()
	{
		delete id;
	}
};
