#include "Wolves.h"

void Wolves::setServer()
{
	if (gameStart || isServer || connectNumber != 0)
		return;
	id_player[0] = id_seer;
	id_player[1] = id_guard;
	id_player[2] = id_witch;
	id_player[3] = id_wolf;
	id_player[4] = id_wolf;
	id_player[5] = id_villager;
	id_player[6] = id_villager;
	id_player[7] = id_villager;
	id_player[8] = id_wolf;
	id_player[9] = id_hunter;
	id_player[10] = id_cupit;
	id_player[11] = id_wolf;
	id_player[12] = id_villager;
	id_player[13] = id_villager;
	id_player[14] = id_villager;
	server = new QTcpServer;
	QString pt = createServer->getPort();
	server->listen(QHostAddress::Any, pt.toInt());
	connect(server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
	isServer = true;
	selfSocket = new QTcpSocket;
	selfSocket->connectToHost(createServer->getIP(), pt.toInt());
	connect(selfSocket, SIGNAL(readyRead()), this, SLOT(receiveInfo()));
	ui.startButton->show();
}

void Wolves::acceptConnection()
{
	if (connectNumber >= 15)
		return;
	WriteReadSocket[connectNumber] = server->nextPendingConnection();
	if (connectNumber != 0)
	{
		WriteReadSocket[connectNumber]->write(QString::number(connectNumber + 1).toUtf8());
		QByteArray playerNumber = "\\p";
		playerNumber += playerNumber.number(connectNumber + 1);
		WriteReadSocket[connectNumber]->waitForReadyRead(1000);
		QByteArray new_player = WriteReadSocket[connectNumber]->readAll();
		connect(WriteReadSocket[connectNumber], SIGNAL(readyRead()), mapper, SLOT(map()));
		mapper->setMapping(WriteReadSocket[connectNumber], connectNumber);
		p[connectNumber].name = new_player;
		connectNumber++;
		for (int i = 0; i < connectNumber; ++i)
		{
			WriteReadSocket[i]->write(playerNumber);
			for (int j = 0; j < connectNumber; ++j)
			{
				WriteReadSocket[i]->write((QString("\\") + QString::number(j) + " " + p[j].name).toUtf8());
			}
		}
	}
	else
	{
		connect(WriteReadSocket[0], SIGNAL(readyRead()), mapper, SLOT(map()));
		mapper->setMapping(WriteReadSocket[0], connectNumber);
		p[0].name = name;
		connectNumber++;
		selfNumber = 0;
		showPlayer();
	}
}

QString Wolves::findAddress()
{
	QString ipAddress;
	QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
	for (int i = 0; i < ipAddressesList.size(); ++i)
	{
		if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
			ipAddressesList.at(i).toIPv4Address())
		{
			if (ipAddressesList.at(i).toString().contains("169.254"))
				continue;
			ipAddress = ipAddressesList.at(i).toString();
		}
	}
	if (ipAddress.isEmpty())
		ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
	return ipAddress;
}

void Wolves::serverInfo(int infoNumber)
{
	QByteArray t_info = WriteReadSocket[infoNumber]->readAll();
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
		if (new_info[0] == 'a' || new_info[0] == 'w')
		{
			QByteArray a = (QString('\\') + new_info).toUtf8();
			for (int i = 0; i < connectNumber; ++i)
			{
				WriteReadSocket[i]->write(a);
			}
		}
		else if (new_info[0] == 'k')
		{
			new_info.remove(0, 1);
			int mid_index = new_info.indexOf(' ');
			int num = new_info.left(mid_index).toInt();
			int vote_tg = new_info.remove(0, mid_index + 1).toInt();
			has_vote++;
			if (vote_tg == -1)
			{
				vote_result[15]++;
			}
			else
			{
				if (p[num].id->getOfficer())
				{
					vote_result[vote_tg] += 2;
				}
				else
				{
					vote_result[vote_tg]++;
				}
			}
			if (has_vote == connectNumber)
			{
				int max_index = -1;
				int max_get = 0;
				for (int i = 0; i < connectNumber; ++i)
				{
					if (vote_result[i] > max_get)
					{
						max_get = vote_result[i];
						max_index = i;
					}
				}
				for (int i = 0; i < connectNumber; ++i)
				{
					WriteReadSocket[i]->write((QString("\\e") + QString::number(max_index)).toUtf8());
					vote_result[i] = 0;
				}
				has_vote = 0;
			}
		}
		else if (new_info[0] == 'v')
		{
			new_info.remove(0, 1);
			int vote_target = new_info.toInt();
			has_vote++;
			if (vote_target == -1)
				vote_result[15]++;
			else
			{
				vote_result[vote_target]++;
			}
			if (has_vote == connectNumber)
			{
				int max_index = -1;
				int max_get = 0;
				for (int i = 0; i < connectNumber; ++i)
				{
					if (vote_result[i] > max_get)
					{
						max_get = vote_result[i];
						max_index = i;
					}
				}
				for (int i = 0; i < connectNumber; ++i)
				{
					WriteReadSocket[i]->write((QString("\\e") + QString::number(max_index)).toUtf8());
					vote_result[i] = 0;
				}
				has_vote = 0;
			}
		}
	}
}

void Wolves::newGame()
{
	srand(time(NULL));
	for (int i = connectNumber - 1; i > 0; --i)
	{
		int r = rand() % (i + 1);
		id_type temp;
		temp = id_player[r];
		id_player[r] = id_player[i];
		id_player[i] = temp;
	}
	for (int i = 0; i < connectNumber; ++i)
	{
		QByteArray a("\\i");
		a += (QString::number(i) + ' ');
		switch (id_player[i])
		{
		case id_villager:
			a += QString::number(1);
			break;
		case id_wolf:
			a += QString::number(2);
			break;
		case id_seer:
			a += QString::number(3);
			break;
		case id_guard:
			a += QString::number(4);
			break;
		case id_cupit:
			a += QString::number(5);
			break;
		case id_witch:
			a += QString::number(6);
			break;
		case id_hunter:
			a += QString::number(7);
			break;
		default:
			break;
		}
		for (int j = 0; j < connectNumber; ++j)
			WriteReadSocket[j]->write(a);
	}
	ui.startButton->hide();
}