#pragma once
#include <QDialog>
#include <QRadioButton>
#include <QPushButton>
#include <QLayout>

class voter: public QDialog
{
	Q_OBJECT

private:
	QRadioButton *target[15];
	QRadioButton *giveUp;
	QVBoxLayout *layout;
	QPushButton *okButton;
public:
	voter(QWidget *parent);
	~voter();
	void setUsabel(int l);
	void forbidden();
	int getChosen();
	void canGiveUp(bool b = false);
signals:
	void okClicked();
};
