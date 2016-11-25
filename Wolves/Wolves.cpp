#include "Wolves.h"

Wolves::Wolves(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	server = nullptr;
	connectNumber = 0;
	selfNumber = -1;
	for (int i = 0; i < 15; ++i)
		WriteReadSocket[i] = nullptr;
	isServer = false;
	gameStart = false;
	ui.startButton->hide();
	name = "default";
	connect(ui.actionBackground1, SIGNAL(triggered()), this, SLOT(changeBackground1()));
	connect(ui.actionBackground2, SIGNAL(triggered()), this, SLOT(changeBackground2()));
	connect(ui.actionBackground3, SIGNAL(triggered()), this, SLOT(changeBackground3()));
	connect(ui.actionBackground4, SIGNAL(triggered()), this, SLOT(changeBackground4()));
	connect(ui.actionBackground5, SIGNAL(triggered()), this, SLOT(changeBackground5()));
	connect(ui.actionBackground6, SIGNAL(triggered()), this, SLOT(changeBackground6()));
	connect(ui.actionAuthor, SIGNAL(triggered()), this, SLOT(showAuthorInfo()));
	connect(ui.actionVersion, SIGNAL(triggered()), this, SLOT(showVersionInfo()));
	commonChat = new chatDialog(this);
	commonChat->setWindowTitle(u8"全体聊天器");
	wolfChat = new chatDialog(this);
	wolfChat->setWindowTitle(u8"狼人聊天器");
	nameDialog = new nameInput(this);
	createServer = new CreateServerDialog(this);
	addServer = new CreateServerDialog(this);
	voteDialog = new voter(this);
	createServer->setWindowTitle(u8"创建服务器");
	addServer->setWindowTitle(u8"加入服务器");
	QString a = findAddress();
	createServer->setIP(a);
	createServer->setPort("3587");
	connect(ui.actionAll, SIGNAL(triggered()), this, SLOT(callCommonChat()));
	connect(ui.actionWolves, SIGNAL(triggered()), this, SLOT(callWolfChat()));
	connect(ui.actionCreate, SIGNAL(triggered()), createServer, SLOT(show()));
	connect(ui.actionAdd, SIGNAL(triggered()), addServer, SLOT(show()));
	connect(ui.actionVoter, SIGNAL(triggered()), voteDialog, SLOT(show()));
	connect(ui.actionName, SIGNAL(triggered()), nameDialog, SLOT(show()));
	connect(nameDialog, SIGNAL(okClicked()), this, SLOT(setName()));
	connect(createServer, SIGNAL(okClicked()), this, SLOT(setServer()));
	connect(addServer, SIGNAL(okClicked()), this, SLOT(connectToServer()));
	connect(this, SIGNAL(newOneJoin()), this, SLOT(showPlayer()));
}

void Wolves::changeBackground1()
{
	ui.label->setPixmap(QPixmap(":/Wolves/bg1.png"));
}

void Wolves::changeBackground2()
{
	ui.label->setPixmap(QPixmap(":/Wolves/bg2.png"));
}

void Wolves::changeBackground3()
{
	ui.label->setPixmap(QPixmap(":/Wolves/bg3.png"));
}

void Wolves::changeBackground4()
{
	ui.label->setPixmap(QPixmap(":/Wolves/bg4.png"));
}

void Wolves::changeBackground5()
{
	ui.label->setPixmap(QPixmap(":/Wolves/bg5.png"));
}

void Wolves::changeBackground6()
{
	ui.label->setPixmap(QPixmap(":/Wolves/bg6.png"));
}

void Wolves::showAuthorInfo()
{
	QMessageBox::information(this, QString(u8"作者信息"), 
		QString(u8"钟离倾\r\n如果发现bug请联系QQ519252730\r\n或发送e-mail至thss15_fengs@163.com"));
}

void Wolves::showVersionInfo()
{
	QMessageBox::information(this, QString(u8"版本信息"),
		QString(u8"tool:Qt\r\nlanguage:c++\r\nversion:1.0\r\nlast version:null\r\nchange:null\r\nAll Rights Reserved"));
}

void Wolves::callCommonChat()
{
	commonChat->show();
}

void Wolves::callWolfChat()
{
	wolfChat->show();
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
}

void Wolves::connectToServer()
{
	if (selfSocket == nullptr)
		return;
	selfSocket = new QTcpSocket;
	selfSocket->connectToHost(addServer->getIP(), addServer->getPort().toInt());
	if (!selfSocket->waitForConnected(1000))
		QMessageBox::warning(this, "2", "2", QMessageBox::Ok);
	if (selfSocket->waitForReadyRead(1000))
	{
		QByteArray new_info = selfSocket->readAll();
		connectNumber = new_info.toInt();
		connect(selfSocket, SIGNAL(readyRead()), this, SLOT(receiveInfo()));
		selfSocket->write(name.toUtf8());
	}
	else
	{
		QMessageBox::warning(this, u8"连接错误", u8"不能连接到服务器", QMessageBox::Ok);
	}
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
		if (!WriteReadSocket[connectNumber]->waitForReadyRead(1000))
			QMessageBox::warning(this, "1", "1", QMessageBox::Ok);
		QByteArray new_player = WriteReadSocket[connectNumber]->readAll();
		p[connectNumber].name = new_player;
		connectNumber++;
		for (int i = 0; i < connectNumber; ++i)
		{
			WriteReadSocket[i]->write(playerNumber);
			for (int j = 0; j < connectNumber; ++j)
			{
				WriteReadSocket[i]->write((QString("\\")+ QString::number(j) + " " + p[j].name).toUtf8());
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
		a += (QString::number(i) + ' ' + p[i].name + "\r\n");
	}
	ui.playerLabel->setText(a);
}

void Wolves::setName()
{
	name = nameDialog->getName();
}
