/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "gamewidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    GameWidget *gameWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLCDNumber *scoreLcd;
    QLabel *label_2;
    QLCDNumber *highScoreLcd;
    QLabel *label_3;
    QLCDNumber *levelLcd;
    QSpacerItem *verticalSpacer;
    QPushButton *tetrisButton;
    QPushButton *snakeButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(450, 450);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        gameWidget = new GameWidget(centralwidget);
        gameWidget->setObjectName(QString::fromUtf8("gameWidget"));

        horizontalLayout->addWidget(gameWidget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        scoreLcd = new QLCDNumber(centralwidget);
        scoreLcd->setObjectName(QString::fromUtf8("scoreLcd"));

        verticalLayout->addWidget(scoreLcd);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        highScoreLcd = new QLCDNumber(centralwidget);
        highScoreLcd->setObjectName(QString::fromUtf8("highScoreLcd"));

        verticalLayout->addWidget(highScoreLcd);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);

        levelLcd = new QLCDNumber(centralwidget);
        levelLcd->setObjectName(QString::fromUtf8("levelLcd"));

        verticalLayout->addWidget(levelLcd);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        tetrisButton = new QPushButton(centralwidget);
        tetrisButton->setObjectName(QString::fromUtf8("tetrisButton"));

        verticalLayout->addWidget(tetrisButton);

        snakeButton = new QPushButton(centralwidget);
        snakeButton->setObjectName(QString::fromUtf8("snakeButton"));

        verticalLayout->addWidget(snakeButton);


        horizontalLayout->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "BrickGame v2.0", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "SCORE", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "HIGH SCORE", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "LEVEL", nullptr));
        tetrisButton->setText(QCoreApplication::translate("MainWindow", "Play Tetris", nullptr));
        snakeButton->setText(QCoreApplication::translate("MainWindow", "Play Snake", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
