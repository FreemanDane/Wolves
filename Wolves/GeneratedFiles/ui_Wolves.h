/********************************************************************************
** Form generated from reading UI file 'Wolves.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WOLVES_H
#define UI_WOLVES_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WolvesClass
{
public:
    QAction *actionBackground1;
    QAction *actionBackground2;
    QAction *actionBackground3;
    QAction *actionBackground4;
    QAction *actionBackground5;
    QAction *actionBackground6;
    QWidget *centralWidget;
    QLabel *label;
    QMenuBar *menuBar;
    QMenu *menu;

    void setupUi(QMainWindow *WolvesClass)
    {
        if (WolvesClass->objectName().isEmpty())
            WolvesClass->setObjectName(QStringLiteral("WolvesClass"));
        WolvesClass->resize(600, 400);
        WolvesClass->setMinimumSize(QSize(600, 400));
        WolvesClass->setMaximumSize(QSize(600, 400));
        actionBackground1 = new QAction(WolvesClass);
        actionBackground1->setObjectName(QStringLiteral("actionBackground1"));
        actionBackground2 = new QAction(WolvesClass);
        actionBackground2->setObjectName(QStringLiteral("actionBackground2"));
        actionBackground3 = new QAction(WolvesClass);
        actionBackground3->setObjectName(QStringLiteral("actionBackground3"));
        actionBackground4 = new QAction(WolvesClass);
        actionBackground4->setObjectName(QStringLiteral("actionBackground4"));
        actionBackground5 = new QAction(WolvesClass);
        actionBackground5->setObjectName(QStringLiteral("actionBackground5"));
        actionBackground6 = new QAction(WolvesClass);
        actionBackground6->setObjectName(QStringLiteral("actionBackground6"));
        centralWidget = new QWidget(WolvesClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, -20, 600, 400));
        label->setPixmap(QPixmap(QString::fromUtf8(":/Wolves/bg1.png")));
        WolvesClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(WolvesClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 26));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        WolvesClass->setMenuBar(menuBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(actionBackground1);
        menu->addAction(actionBackground2);
        menu->addAction(actionBackground3);
        menu->addAction(actionBackground4);
        menu->addAction(actionBackground5);
        menu->addAction(actionBackground6);

        retranslateUi(WolvesClass);

        QMetaObject::connectSlotsByName(WolvesClass);
    } // setupUi

    void retranslateUi(QMainWindow *WolvesClass)
    {
        WolvesClass->setWindowTitle(QApplication::translate("WolvesClass", "Wolves", 0));
        actionBackground1->setText(QApplication::translate("WolvesClass", "background1", 0));
        actionBackground2->setText(QApplication::translate("WolvesClass", "background2", 0));
        actionBackground3->setText(QApplication::translate("WolvesClass", "background3", 0));
        actionBackground4->setText(QApplication::translate("WolvesClass", "background4", 0));
        actionBackground5->setText(QApplication::translate("WolvesClass", "background5", 0));
        actionBackground6->setText(QApplication::translate("WolvesClass", "background6", 0));
        label->setText(QString());
        menu->setTitle(QApplication::translate("WolvesClass", "\346\233\264\346\215\242\350\203\214\346\231\257", 0));
    } // retranslateUi

};

namespace Ui {
    class WolvesClass: public Ui_WolvesClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WOLVES_H
