#pragma once

#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include <QtNetwork\QHostAddress>
#include <QtNetwork\QTcpServer>
#include <QtNetwork\QTcpSocket>
#include <QByteArray>
#include <QtNetwork\QNetworkInterface>
#include <QList>
#include <QSignalMapper>
#include <cstdlib>
#include <ctime>
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
	QSignalMapper *mapper;
	progress *pro;
	bool isServer;
	bool gameStart;
	int selfNumber;
	QString name;
	player p[15];
	int vote_result[16];
	int connectNumber;
	id_type id_player[15];
	QString findAddress();
signals:
	void someoneDied();
	void newOneJoin();
	void timeToOfficer();
	void timeToSetLover();
	void timeToProtectPeople();
	void timeToVote();
	void timeToWolves();
	void timeToSavePerson();
	void timeToPoisonPerson();
	void timeToTheDead();
	void timeToSeer();

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
	void receiveInfo();
	void newGame();
	void serverInfo(int index);
	void showVersionInfo();
	void callCommonChat();
	void callWolfChat();
	void showPlayer();
	void allChatSend();
	void wolvesChatSend();
	void selectOfficer();
	void setLover();
	void protectPeople();
	void vote();
	void killPerson();
	void savePerson();
	void poisonPerson();
	void deadAbility();
	void seeID();
public:
	void outputIdentity();
	bool examGameOver();
	void gameOver();
	void voteInitVoter();
};
