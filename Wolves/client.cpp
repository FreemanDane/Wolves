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
			pro->timeGoOn();
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
	}
}

void Wolves::showPlayer()
{
	QString a = "";
	for (int i = 0; i < connectNumber; ++i)
	{
		a += (QString::number(i + 1) + ' ' + p[i].name + "\r\n");
	}
	ui.playerLabel->setText(a);
}

void Wolves::outputIdentity()
{
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
}