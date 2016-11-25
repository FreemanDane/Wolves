#include "Wolves.h"

void Wolves::setServer()
{
	if (gameStart || isServer)
		return;
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
		p[0].name = name;
		connectNumber++;
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