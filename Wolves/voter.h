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
	QVBoxLayout *layout;
	QPushButton *okButton;
public:
	voter(QWidget *parent);
	~voter();
	void setUsabel(int l);
	int getChosen();
signals:
	void okClicked();
};
