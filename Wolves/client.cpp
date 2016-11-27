#include "Wolves.h"

void Wolves::connectToServer()
{
	if (selfSocket == nullptr)
		return;
	selfSocket = new QTcpSocket;
	selfSocket->connectToHost(addServer->getIP(), addServer->getPort().toInt());
	selfSocket->waitForConnected(1000);
	if (selfSocket->waitForReadyRead(1000))
	{
		QByteArray new_info = selfSocket->readAll();
		connectNumber = new_info.toInt();
		selfNumber = connectNumber - 1;
		connect(selfSocket, SIGNAL(readyRead()), this, SLOT(receiveInfo()));
		selfSocket->write(name.toUtf8());
	}
	else
	{
		QMessageBox::warning(this, u8"连接错误", u8"不能连接到服务器", QMessageBox::Ok);
	}
}

void Wolves::receiveInfo()
{
	QByteArray t_info = selfSocket->readAll();
	while (t_info.length() != 0)
	{
		if (t_info[0] == '\\')
			t_info.remove(0, 1);
		int index = t_info.indexOf('\\');
		QByteArray new_info;
		if (index != -1)
		{
			new_info = t_info.left(index);
			t_info.remove(0, index);
		}
		else
		{
			new_info = t_info;
			t_info.remove(0, t_info.length());
		}
		if (new_info[0] >= '0' && new_info[0] <= '9')
		{
			int last_index = new_info.indexOf(' ');
			QByteArray a = new_info.left(last_index);
			p[a.toInt()].name = new_info.remove(0, last_index + 1);
			emit newOneJoin();
		}
		else if (new_info[0] == 'p')
		{
			connectNumber = new_info.remove(0, 1).toInt();
		}
		else if (new_info[0] == 'k')
		{
			int index = new_info.remove(0, 1).toInt();
			p[index].id->BeHurted();
		}
		else if (new_info[0] == 's')
		{
			int index = new_info.remove(0, 1).toInt();
			p[index].id->BeSaved();
			pro->timeGoOn();
		}
		else if (new_info[0] == 'i')
		{
			new_info.remove(0, 1);
			int index = new_info.indexOf(' ');
			int num = new_info.left(index).toInt();
			new_info.remove(0, index + 1);
			int id_num = new_info.toInt();
			switch (id_num)
			{
			case 1:
				p[num].id = new identity(id_villager);
				break;
			case 2:
				p[num].id = new identity(id_wolf);
				break;
			case 3:
				p[num].id = new identity(id_seer);
				break;
			case 4:
				p[num].id = new identity(id_guard);
				break;
			case 5:
				p[num].id = new identity(id_cupit);
				break;
			case 6:
				p[num].id = new identity(id_witch);
				break;
			case 7:
				p[num].id = new identity(id_hunter);
				break;
			default:
				break;
			}
			if (p[selfNumber].id != nullptr)
				outputIdentity();
		}
		else if (new_info[0] == 'w')
		{
			new_info.remove(0, 1);
			int index = new_info.lastIndexOf(' ');
			int source = new_info.left(index).toInt();
			new_info.remove(0, index + 1);
			wolfChat->addNewMessage(p[source].name + ':' + new_info);
		}
		else if (new_info[0] == 'a')
		{
			new_info.remove(0, 1);
			int index = new_info.lastIndexOf(' ');
			int source = new_info.left(index).toInt();
			new_info.remove(0, index + 1);
			commonChat->addNewMessage(p[source].name + ':' + new_info);
		}
		else if (new_info[0] == 'o')
		{
			new_info.remove(0, 1);
			int index = new_info.toInt();
			p[index].id->setOfficer();
			showPlayer();
		}
		else if (new_info[0] == 'e')
		{
			new_info.remove(0, 1);
			int number_info = new_info.toInt();
			if (pro->getDay() == 0)
			{
				if (pro->getTime() == 0)
				{
					p[number_info].id->setOfficer();
					pro->timeGoOn();
					ui.infoLabel->setText(p[number_info].name + u8"是警长");
					showPlayer();
					emit timeToSetLover();
				}
				else if (pro->getTime() == 1 || pro->getTime() == 2)
				{
					if (number_info != -1)
						p[number_info].id->setLover();
					if (pro->getTime() == 2 && p[selfNumber].id->getLover())
					{
						QString lover_info = "";
						for (int i = 0; i < connectNumber; ++i)
						{
							if (p[i].id->getLover())
								lover_info += p[i].name + "\r\n";
						}
						lover_info += u8"是情侣\r\n等待预言家验身份";
						ui.infoLabel->setText(lover_info);
					}
					else
					{
						ui.infoLabel->setText(u8"你没有被设置为情侣\r\n等待预言家验身份");
					}
					pro->timeGoOn();
					if (pro->getTime() == 1)
						emit timeToSetLover();
					else
						emit timeToSeer();
				}
			}
			else
			{
				if (pro->getTime() == 0)
				{
					pro->timeGoOn();
					ui.infoLabel->setText(u8"等待守卫保护人");
					emit protectPeople();
				}
				else if (pro->getTime() == 1)
				{
					for (int i = 0; i < connectNumber; ++i)
					{
						p[i].id->cancelProtected();
					}
					if (number_info != -1)
					{
						p[number_info].id->beProtected();
					}
					pro->timeGoOn();
					ui.infoLabel->setText(u8"狼人杀人中");
					emit timeToWolves();
				}
				else if (pro->getTime() == 2)
				{
					if (number_info != -1)
					{
						p[number_info].id->BeHurted();
					}
					pro->timeGoOn();
					ui.infoLabel->setText(u8"女巫用药中");
					emit timeToSavePerson();
				}
				else if (pro->getTime() == 3)
				{
					if (number_info != -1)
					{
						p[number_info].id->BeHurted();
						for (int i = 0; i < connectNumber; ++i)
						{
							if (p[i].id->getID() == id_witch)
							{
								p[i].id->usePoison();
								break;
							}
						}
						pro->timeGoOn();
						emit timeToPoisonPerson();
					}
				}
				else if (pro->getTime() == 4)
				{
					if (number_info != -1)
					{
						p[number_info].id->BeSaved();
						for (int i = 0; i < connectNumber; ++i)
						{
							if (p[i].id->getID() == id_witch)
							{
								p[i].id->useMedicion();
								break;
							}
						}
						pro->timeGoOn();
						emit timeToTheDead();
					}
				}
				else if (pro->getTime() == 5)
				{
					QString deadList = "";
					for (int i = 0; i < connectNumber; ++i)
					{
						if (p[i].id->getLife() <= 0 && !p[i].id->beDead())
						{
							deadList += (p[i].name + u8"死亡\r\n");
							p[i].id->goDie();
							if (i == selfNumber)
							{
								ui.situLabel->setText(u8"死亡");
							}
						}
					}
					showPlayer();
					deadList += u8"请投票";
					ui.infoLabel->setText(deadList);
					pro->timeGoOn();
					emit timeToVote();
				}
				else if (pro->getTime() == 6)
				{
					if (number_info != -1)
					{
						p[number_info].id->goDie();
					}
					if (selfNumber == number_info)
						ui.situLabel->setText(u8"死亡");
					ui.infoLabel->setText(p[number_info].name + u8"被投死\r\n等待预言家验身份");
					pro->timeGoOn();
					emit timeToSeer();
				}
			}
		}
	}
}

void Wolves::showPlayer()
{
	QString a = "";
	if (!gameStart)
	{
		for (int i = 0; i < connectNumber; ++i)
		{
			a += (QString::number(i + 1) + ' ' + p[i].name + "\r\n");
		}
	}
	else
	{
		for (int i = 0; i < connectNumber; ++i)
		{
			if (p[i].id->beDead())
				a += u8"死 ";
			else
				a += u8"活 ";
			if (p[i].id->getOfficer())
				a += u8"警 ";
			a += (QString::number(i + 1) + ' ' + p[i].name + "\r\n");
		}
	}
	ui.playerLabel->setText(a);
}

void Wolves::outputIdentity()
{
	pro = new progress;
	QString status = u8"存活";
	gameStart = true;
	switch (p[selfNumber].id->getID())
	{
	case id_villager:
		ui.IDLabel->setText(u8"平民");
		break;
	case id_wolf:
		ui.IDLabel->setText(u8"狼人");
		break;
	case id_seer:
		ui.IDLabel->setText(u8"预言家");
		break;
	case id_witch:
		ui.IDLabel->setText(u8"女巫");
		status += u8"\r\n毒药:是\r\n解药:是";
		break;
	case id_hunter:
		ui.IDLabel->setText(u8"猎人");
		break;
	case id_guard:
		ui.IDLabel->setText(u8"守卫");
		break;
	case id_cupit:
		ui.IDLabel->setText(u8"丘比特");
		break;
	}
	ui.situLabel->setText(status);
	for (int i = 0; i < connectNumber; ++i)
	{
		voteDialog->setUsabel(i);
	}
	voteDialog->canGiveUp(true);
	selectOfficer();
	showPlayer();
	//pro->timeGoOn();
}

void Wolves::allChatSend()
{
	QString info = QString("\\a") + QString::number(selfNumber) + QString(' ') + commonChat->getInput();
	selfSocket->write(info.toUtf8());
}

void Wolves::wolvesChatSend()
{
	QString info = QString("\\w") + QString::number(selfNumber) + QString(' ') + wolfChat->getInput();
	selfSocket->write(info.toUtf8());
}

void Wolves::sendKeyInfo()
{
	int result = voteDialog->getChosen();
	if (pro->getTime() == 6)
	{
		selfSocket->write((QString("\\k") + QString::number(selfNumber) + ' ' + QString::number(result)).toUtf8());
	}
	else if (pro->getTime() == 5)
	{
		if (p[selfNumber].id->getOfficer())
		{
			selfSocket->write(QByteArray("\\o") + QString::number(result).toUtf8());
			selfSocket->waitForReadyRead(1000);
			selfSocket->write("v-1");
			p[selfNumber].id->cancelOfficer();
		}
		else
		{
			selfSocket->write(QByteArray("\\g") + QString::number(result).toUtf8());
			selfSocket->waitForReadyRead(1000);
			selfSocket->write("v-1");
		}
	}
	else if (pro->getTime() == 0 && pro->getDay() != 0)
	{
		int result = voteDialog->getChosen();
		if (result == -1)
		{
			selfSocket->write("\\e-1");
			return;
		}
		QString a = QString::number(result + 1) + u8"号玩家\r\n";
		switch (p[result].id->getID())
		{	
		case id_villager:
			a += u8"平民";
			break;
		case id_wolf:
			a += u8"狼人";
			break;
		case id_seer:
			a += u8"预言家";
			break;
		case id_witch:
			a += u8"女巫";
			break;
		case id_hunter:
			a += u8"猎人";
			break;
		case id_guard:
			a += u8"守卫";
			break;
		case id_cupit:
			a += u8"丘比特";
			break;
		}
		ui.situLabel->setText(a);
		selfSocket->write("v-1");
	}
	else
	{
		selfSocket->write((QString("\\v") + QString::number(result)).toUtf8());
	}
	voteDialog->hide();
	voteDialog->forbidden();
}