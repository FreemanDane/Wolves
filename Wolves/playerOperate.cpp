#include "Wolves.h"
void Wolves::selectOfficer()
{
	int result = voteDialog->getChosen();
	selfSocket->write((QString("\\v") + QString::number(result)).toUtf8());
}

void Wolves::setLover()
{
	if (connectNumber < 11 || p[selfNumber].id->getID() != id_cupit)
	{
		selfSocket->write("\\v-1");
	}
	else
	{
		int result = voteDialog->getChosen();
		selfSocket->write((QString("\\v") + QString::number(result)).toUtf8());
	}
}

void Wolves::protectPeople()
{
	if (p[selfNumber].id->getID() != id_guard)
	{
		selfSocket->write("\\v-1");
	}
	else
	{
		int result = voteDialog->getChosen();
		selfSocket->write((QString("\\v") + QString::number(result)).toUtf8());
	}
}

void Wolves::vote()
{
	if (p[selfNumber].id->beDead())
	{
		selfSocket->write((QString("\\k") + QString::number(selfNumber) + " -1").toUtf8());
		return;
	}
	int result = voteDialog->getChosen();
	selfSocket->write((QString("\\k") + QString::number(selfNumber) + ' ' + QString::number(result)).toUtf8());
}

void Wolves::killPerson()
{
	if (p[selfNumber].id->getID() != id_wolf || p[selfNumber].id->beDead())
	{
		selfSocket->write("\\v-1");
	}
	else
	{
		int result = voteDialog->getChosen();
		selfSocket->write((QString("\\v") + QString::number(result)).toUtf8());
	}
}

void Wolves::savePerson()
{
	if (p[selfNumber].id->getID() != id_witch)
	{
		selfSocket->write("\\v-1");
	}
	else
	{
		int result = voteDialog->getChosen();
		if (result != -1)
		{
			p[selfNumber].id->useMedicion();
		}
		selfSocket->write((QString("\\v") + QString::number(result)).toUtf8());
	}
}

void Wolves::poisonPerson()
{
	if (p[selfNumber].id->getID() != id_witch)
	{
		selfSocket->write("\\v-1");
	}
	else
	{
		int result = voteDialog->getChosen();
		if (result != -1)
		{
			p[selfNumber].id->usePoison();
		}
		selfSocket->write((QString("\\v") + QString::number(result)).toUtf8());
	}
}

void Wolves::deadAbility()
{
	if (!p[selfNumber].id->getLover() || p[selfNumber].id->getID() != id_hunter || !p[selfNumber].id->beDead())
	{
		selfSocket->write("\\v-1");
	}
	else
	{
		int result = voteDialog->getChosen();
		selfSocket->write((QString("\\v") + QString::number(result)).toUtf8());
	}
}

void Wolves::seeID()
{
	if (p[selfNumber].id->getID() != id_seer)
	{
		selfSocket->write("\\e");
	}
	else
	{
		int result = voteDialog->getChosen();
		if (result == -1)
		{
			selfSocket->write("\\e");
			return;
		}
		QString a = QString::number(result + 1) + u8"�����\r\n";
		switch (p[result].id->getID())
		{	
		case id_villager:
			a += u8"ƽ��";
			break;
		case id_wolf:
			a += u8"����";
			break;
		case id_seer:
			a += u8"Ԥ�Լ�";
			break;
		case id_witch:
			a += u8"Ů��";
			break;
		case id_hunter:
			a += u8"����";
			break;
		case id_guard:
			a += u8"����";
			break;
		case id_cupit:
			a += u8"�����";
			break;
		}
		ui.situLabel->setText(a);
		selfSocket->write("\\e");
	}
}