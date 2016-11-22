#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Wolves.h"

class Wolves : public QMainWindow
{
    Q_OBJECT

public:
    Wolves(QWidget *parent = Q_NULLPTR);

private:
    Ui::WolvesClass ui;

public slots:
	void changeBackground1();
	void changeBackground2();
	void changeBackground3();
	void changeBackground4();
	void changeBackground5();
	void changeBackground6();
};
