#pragma once
#include <QDialog>
#include <QLineEdit>
#include <QLayout>
#include <QPushButton>

class nameInput :public QDialog
{
	Q_OBJECT

private:
	QLineEdit *edit;
	QVBoxLayout *layout;
	QPushButton *okButton;

public:
	nameInput(QWidget *parent);
	~nameInput();
	QString getName();

signals:
	void okClicked();
};
