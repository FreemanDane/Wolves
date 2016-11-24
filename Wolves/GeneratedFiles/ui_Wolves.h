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
#include <QtWidgets/QPushButton>
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
    QAction *actionAll;
    QAction *actionWolves;
    QAction *actionCreate;
    QAction *actionAdd;
    QAction *actionVersion;
    QAction *actionAuthor;
    QAction *actionVoter;
    QAction *actionName;
    QWidget *centralWidget;
    QLabel *label;
    QLabel *label_2;
    QLabel *IDLabel;
    QLabel *situLabel;
    QPushButton *startButton;
    QLabel *label_3;
    QLabel *playerLabel;
    QLabel *infoLabel;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menu_4;
    QMenu *menu_5;

    void setupUi(QMainWindow *WolvesClass)
    {
        if (WolvesClass->objectName().isEmpty())
            WolvesClass->setObjectName(QStringLiteral("WolvesClass"));
        WolvesClass->resize(600, 400);
        WolvesClass->setMinimumSize(QSize(600, 400));
        WolvesClass->setMaximumSize(QSize(600, 400));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Wolves/wolf_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        WolvesClass->setWindowIcon(icon);
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
        actionAll = new QAction(WolvesClass);
        actionAll->setObjectName(QStringLiteral("actionAll"));
        actionWolves = new QAction(WolvesClass);
        actionWolves->setObjectName(QStringLiteral("actionWolves"));
        actionCreate = new QAction(WolvesClass);
        actionCreate->setObjectName(QStringLiteral("actionCreate"));
        actionAdd = new QAction(WolvesClass);
        actionAdd->setObjectName(QStringLiteral("actionAdd"));
        actionVersion = new QAction(WolvesClass);
        actionVersion->setObjectName(QStringLiteral("actionVersion"));
        actionAuthor = new QAction(WolvesClass);
        actionAuthor->setObjectName(QStringLiteral("actionAuthor"));
        actionVoter = new QAction(WolvesClass);
        actionVoter->setObjectName(QStringLiteral("actionVoter"));
        actionName = new QAction(WolvesClass);
        actionName->setObjectName(QStringLiteral("actionName"));
        centralWidget = new QWidget(WolvesClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, -20, 600, 400));
        label->setPixmap(QPixmap(QString::fromUtf8(":/Wolves/bg1.png")));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 20, 181, 71));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(20);
        label_2->setFont(font);
        IDLabel = new QLabel(centralWidget);
        IDLabel->setObjectName(QStringLiteral("IDLabel"));
        IDLabel->setGeometry(QRect(50, 100, 111, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(18);
        IDLabel->setFont(font1);
        situLabel = new QLabel(centralWidget);
        situLabel->setObjectName(QStringLiteral("situLabel"));
        situLabel->setGeometry(QRect(30, 160, 131, 191));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font2.setPointSize(15);
        situLabel->setFont(font2);
        startButton = new QPushButton(centralWidget);
        startButton->setObjectName(QStringLiteral("startButton"));
        startButton->setGeometry(QRect(230, 310, 131, 41));
        startButton->setFont(font1);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(390, 30, 101, 31));
        label_3->setFont(font2);
        playerLabel = new QLabel(centralWidget);
        playerLabel->setObjectName(QStringLiteral("playerLabel"));
        playerLabel->setGeometry(QRect(400, 80, 151, 231));
        infoLabel = new QLabel(centralWidget);
        infoLabel->setObjectName(QStringLiteral("infoLabel"));
        infoLabel->setGeometry(QRect(220, 50, 131, 221));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font3.setPointSize(12);
        infoLabel->setFont(font3);
        WolvesClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(WolvesClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 26));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        menu_3 = new QMenu(menuBar);
        menu_3->setObjectName(QStringLiteral("menu_3"));
        menu_4 = new QMenu(menuBar);
        menu_4->setObjectName(QStringLiteral("menu_4"));
        menu_5 = new QMenu(menuBar);
        menu_5->setObjectName(QStringLiteral("menu_5"));
        WolvesClass->setMenuBar(menuBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menu_3->menuAction());
        menuBar->addAction(menu_4->menuAction());
        menuBar->addAction(menu_5->menuAction());
        menu->addAction(actionBackground1);
        menu->addAction(actionBackground2);
        menu->addAction(actionBackground3);
        menu->addAction(actionBackground4);
        menu->addAction(actionBackground5);
        menu->addAction(actionBackground6);
        menu_2->addAction(actionAll);
        menu_2->addAction(actionWolves);
        menu_3->addAction(actionCreate);
        menu_3->addAction(actionAdd);
        menu_4->addAction(actionVersion);
        menu_4->addAction(actionAuthor);
        menu_5->addAction(actionVoter);
        menu_5->addAction(actionName);

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
        actionAll->setText(QApplication::translate("WolvesClass", "All", 0));
        actionWolves->setText(QApplication::translate("WolvesClass", "Wolves", 0));
        actionCreate->setText(QApplication::translate("WolvesClass", "Create", 0));
        actionAdd->setText(QApplication::translate("WolvesClass", "Add", 0));
        actionVersion->setText(QApplication::translate("WolvesClass", "Version", 0));
        actionAuthor->setText(QApplication::translate("WolvesClass", "Author", 0));
        actionVoter->setText(QApplication::translate("WolvesClass", "Voter", 0));
        actionName->setText(QApplication::translate("WolvesClass", "Name", 0));
        label->setText(QString());
        label_2->setText(QApplication::translate("WolvesClass", "\344\275\240\347\232\204\350\272\253\344\273\275\357\274\232", 0));
        IDLabel->setText(QApplication::translate("WolvesClass", "\346\227\240", 0));
        situLabel->setText(QApplication::translate("WolvesClass", "\346\270\270\346\210\217\346\234\252\345\274\200\345\247\213", 0));
        startButton->setText(QApplication::translate("WolvesClass", "\346\270\270\346\210\217\345\274\200\345\247\213", 0));
        label_3->setText(QApplication::translate("WolvesClass", "\345\275\223\345\211\215\347\216\251\345\256\266", 0));
        playerLabel->setText(QString());
        infoLabel->setText(QString());
        menu->setTitle(QApplication::translate("WolvesClass", "\346\233\264\346\215\242\350\203\214\346\231\257", 0));
        menu_2->setTitle(QApplication::translate("WolvesClass", "\350\201\212\345\244\251\346\241\206", 0));
        menu_3->setTitle(QApplication::translate("WolvesClass", "\346\210\277\351\227\264", 0));
        menu_4->setTitle(QApplication::translate("WolvesClass", "\344\277\241\346\201\257", 0));
        menu_5->setTitle(QApplication::translate("WolvesClass", "\345\205\266\344\273\226", 0));
    } // retranslateUi

};

namespace Ui {
    class WolvesClass: public Ui_WolvesClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WOLVES_H
