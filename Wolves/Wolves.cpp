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

void Wolves::setName()
{
	name = nameDialog->getName();
}
