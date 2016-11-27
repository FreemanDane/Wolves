#include "Wolves.h"
void Wolves::selectOfficer()
{
	for (int i = 0; i < connectNumber; ++i)
	{
		voteDialog->setUsabel(i);
	}
	voteDialog->canGiveUp(false);
	ui.infoLabel->setText(u8"请选择警长");
	voteDialog->show();
}

void Wolves::setLover()
{
	if (connectNumber < 11 || p[selfNumber].id->getID() != id_cupit)
	{
		selfSocket->write("\\v-1");
	}
	else
	{
		voteDialog->forbidden();
		for (int i = 0; i < connectNumber; ++i)
		{
			if (!p[i].id->getLover())
				voteDialog->setUsabel(i);
		}
		voteDialog->show();
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
		for (int i = 0; i < connectNumber; ++i)
		{
			if (p[i].id->getLastBeProtected() != 0 && !p[i].id->beDead())
				voteDialog->setUsabel(i);
		}
		voteDialog->canGiveUp(true);
		ui.infoLabel->setText(u8"选择保护的人");
		voteDialog->show();
	}
}

void Wolves::vote()
{
	if (p[selfNumber].id->beDead())
	{
		selfSocket->write((QString("\\k") + QString::number(selfNumber) + " -1").toUtf8());
		return;
	}
	else
	{
		voteDialog->forbidden();
		for (int i = 0; i < connectNumber; ++i)
		{
			if (!p[i].id->beDead())
				voteDialog->setUsabel(i);
		}
		voteDialog->show();
	}
}

void Wolves::killPerson()
{
	if (p[selfNumber].id->getID() != id_wolf || p[selfNumber].id->beDead())
	{
		selfSocket->write("\\v-1");
	}
	else
	{
		voteDialog->forbidden();
		for (int i = 0; i < connectNumber; ++i)
		{
			if (!p[i].id->beDead())
				voteDialog->setUsabel(i);
		}
		voteDialog->show();
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
		voteDialog->forbidden();
		for (int i = 0; i < connectNumber; ++i)
		{
			if (p[i].id->getLife() <= 0 && !p[selfNumber].id->beDead() && p[selfNumber].id->getMedicion())
				voteDialog->setUsabel(i);
		}
		voteDialog->show();
		ui.infoLabel->setText(u8"选择救人");
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
		voteDialog->forbidden();
		for (int i = 0; i < connectNumber; ++i)
		{
			if (p[i].id->getLife() > 0 && !p[selfNumber].id->beDead() && p[selfNumber].id->getMedicion())
				voteDialog->setUsabel(i);
		}
		voteDialog->show();
		ui.infoLabel->setText(u8"选择毒人");
	}
}

void Wolves::deadAbility()
{
	if (p[selfNumber].id->getLife() > 0 || !p[selfNumber].id->beDead() || (p[selfNumber].id->getID() != id_hunter &&
		!p[selfNumber].id->getLover() && p[selfNumber].id->getOfficer()))
		selfSocket->write("\\v-1");
	else if (p[selfNumber].id->getID() == id_hunter)
	{
		voteDialog->forbidden();
		for (int i = 0; i < connectNumber; ++i)
		{
			if (!p[i].id->beDead())
				voteDialog->setUsabel(i);
		}
		ui.situLabel->setText(u8"您死了\r\n选择射击对象");
		voteDialog->show();
	}
	if (p[selfNumber].id->getLover())
	{
		for (int i = 0; i < connectNumber; ++i)
		{
			if (p[i].id->getLover() && i != selfNumber)
			{
				selfSocket->write((QByteArray("\\g") + QString::number(i)).toUtf8());
				selfSocket->waitForReadyRead(1000);
			}
		}
	}
	if (p[selfNumber].id->getOfficer())
	{
		voteDialog->forbidden();
		for (int i = 0; i < connectNumber; ++i)
		{
			if (!p[i].id->beDead())
				voteDialog->setUsabel(i);
		}
		ui.situLabel->setText(u8"您死了\r\n选择继任警长");
		voteDialog->show();
	}
}

void Wolves::seeID()
{
	if (examGameOver())
	{
		gameOver();
		return;
	}
	if (p[selfNumber].id->getID() != id_seer)
	{
		selfSocket->write("\\v-1");
	}
	else
	{
		voteDialog->forbidden();
		if (!p[selfNumber].id->beDead())
		{
			for (int i = 0; i < connectNumber; ++i)
			{
				if (!p[i].id->beDead() && !p[selfNumber].id->beDead())
					voteDialog->setUsabel(i);
			}
		}
		voteDialog->canGiveUp(true);
		ui.infoLabel->setText(u8"选择想查看的玩家");
		voteDialog->show();
	}
}