#include "Wolves.h"

Wolves::Wolves(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	server = nullptr;
	mapper = new QSignalMapper;
	has_vote = 0;
	connectNumber = 0;
	selfNumber = -1;
	for (int i = 0; i < 15; ++i)
	{
		vote_result[i] = 0;
		WriteReadSocket[i] = nullptr;
	}
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
	connect(mapper, SIGNAL(mapped(int)), this, SLOT(serverInfo(int)));
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
	connect(commonChat, SIGNAL(clickSend()), this, SLOT(allChatSend()));
	connect(wolfChat, SIGNAL(clickSend()), this, SLOT(wolvesChatSend()));
	connect(ui.actionCreate, SIGNAL(triggered()), createServer, SLOT(show()));
	connect(ui.actionAdd, SIGNAL(triggered()), addServer, SLOT(show()));
	connect(ui.actionVoter, SIGNAL(triggered()), voteDialog, SLOT(show()));
	connect(ui.actionName, SIGNAL(triggered()), nameDialog, SLOT(show()));
	connect(nameDialog, SIGNAL(okClicked()), this, SLOT(setName()));
	connect(createServer, SIGNAL(okClicked()), this, SLOT(setServer()));
	connect(addServer, SIGNAL(okClicked()), this, SLOT(connectToServer()));
	connect(this, SIGNAL(newOneJoin()), this, SLOT(showPlayer()));
	connect(ui.startButton, SIGNAL(clicked()), this, SLOT(newGame()));
	connect(voteDialog, SIGNAL(okClicked()), this, SLOT(sendKeyInfo()));
	connect(this, SIGNAL(timeToOfficer()), this, SLOT(selectOfficer()));
	connect(this, SIGNAL(timeToSetLover()), this, SLOT(setLover()));
	connect(this, SIGNAL(timeToProtectPeople()), this, SLOT(protectPeople()));
	connect(this, SIGNAL(timeToSeer()), this, SLOT(seeID()));
	connect(this, SIGNAL(timeToWolves()), this, SLOT(killPerson()));
	connect(this, SIGNAL(timeToSavePerson()), this, SLOT(savePerson()));
	connect(this, SIGNAL(timeToPoisonPerson()), this, SLOT(poisonPerson()));
	connect(this, SIGNAL(timeToTheDead()), this, SLOT(deadAbility()));
	connect(this, SIGNAL(timeToVote()), this, SLOT(vote()));
}

Wolves::~Wolves()
{
	delete server;
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
		QString(u8"tool:Qt\r\nlanguage:c++\r\nversion:1.1\r\nlast version:1.0\r\nchange:debug the police and \r\nthe lovers will die in the first \r\nday\r\nAll Rights Reserved"));
}

void Wolves::callCommonChat()
{
	commonChat->show();
}

void Wolves::callWolfChat()
{
	if (p[selfNumber].id == nullptr || p[selfNumber].id->getID() == id_wolf)
		wolfChat->show();
	else
		QMessageBox::warning(this, u8"错误", u8"你的身份不能打开狼人聊天", QMessageBox::Ok);
}

void Wolves::setName()
{
	name = nameDialog->getName();
}

bool Wolves::examGameOver()
{
	int person_num = 0;
	int wolves_num = 0;
	for (int i = 0; i < connectNumber; ++i)
	{
		if (p[i].id->getID() == id_wolf && !p[i].id->beDead())
			wolves_num++;
		else if (p[i].id->getID() != id_wolf && !p[i].id->beDead())
			person_num++;
	}
	if (person_num == 0 || wolves_num == 0)
		return true;
	else
		return false;
}

void Wolves::gameOver()
{
	int person_num = 0;
	int wolves_num = 0;
	for (int i = 0; i < connectNumber; ++i)
	{
		if (p[i].id->getID() == id_wolf && !p[i].id->beDead())
			wolves_num++;
		else if (p[i].id->getID() != id_wolf && !p[i].id->beDead())
			person_num++;
	}
	if (p[selfNumber].id->getID() == id_wolf)
	{
		if (wolves_num == 0)
		{
			ui.infoLabel->setText(u8"你输了");
		}
		else
		{
			ui.infoLabel->setText(u8"你赢了");
		}
	}
	else
	{
		if (person_num == 0)
		{
			ui.infoLabel->setText(u8"你输了");
		}
		else
		{
			ui.infoLabel->setText(u8"你赢了");
		}
	}
	for (int i = 0; i < connectNumber; ++i)
	{
		delete p[i].id;
	}
	delete pro;
	if (isServer)
		ui.startButton->show();
}

void Wolves::voteInitVoter()
{
	for (int i = 0; i < connectNumber; ++i)
	{
		if (!p[i].id->beDead())
		{
			voteDialog->setUsabel(i);
		}
	}
}
