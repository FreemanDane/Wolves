#pragma once

#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include <QtNetwork\QHostAddress>
#include <QtNetwork\QTcpServer>
#include <QtNetwork\QTcpSocket>
#include <QByteArray>
#include <QtNetwork\QNetworkInterface>
#include <QList>
#include "ui_Wolves.h"
#include "chatDialog.h"
#include "voter.h"
#include "nameInput.h"
#include "player.h"
#include "identity.h"
#include "progress.h"
#include "createServerDialog.h"

class Wolves : public QMainWindow
{
    Q_OBJECT

public:
    Wolves(QWidget *parent = Q_NULLPTR);

private:
    Ui::WolvesClass ui;
	chatDialog *commonChat;
	chatDialog *wolfChat;
	nameInput *nameDialog;
	voter *voteDialog;
	CreateServerDialog *createServer;
	CreateServerDialog *addServer;
	QTcpServer *server;
	QTcpSocket *WriteReadSocket[15];
	QTcpSocket *selfSocket;
	bool isServer;
	bool gameStart;
	int selfNumber;
	QString name;
	player p[15];
	int connectNumber;
	QString findAddress();
public slots:
	void setName();
	void setServer();
	void connectToServer();
	void acceptConnection();
	void changeBackground1();
	void changeBackground2();
	void changeBackground3();
	void changeBackground4();
	void changeBackground5();
	void changeBackground6();
	void showAuthorInfo();
	void showVersionInfo();
	void callCommonChat();
	void callWolfChat();
};
