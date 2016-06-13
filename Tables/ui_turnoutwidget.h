/********************************************************************************
** Form generated from reading UI file 'turnoutwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TURNOUTWIDGET_H
#define UI_TURNOUTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TurnoutWidget
{
public:
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab1;
    QWidget *tab2;
    QPushButton *btnAdd;
    QCheckBox *chkFeedback;
    QCheckBox *chkLockInfo;
    QCheckBox *chkAuto;
    QCheckBox *chkSpeedDetails;

    void setupUi(QWidget *TurnoutWidget)
    {
        if (TurnoutWidget->objectName().isEmpty())
            TurnoutWidget->setObjectName(QStringLiteral("TurnoutWidget"));
        TurnoutWidget->resize(825, 300);
        gridLayout = new QGridLayout(TurnoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tabWidget = new QTabWidget(TurnoutWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab1 = new QWidget();
        tab1->setObjectName(QStringLiteral("tab1"));
        tabWidget->addTab(tab1, QString());
        tab2 = new QWidget();
        tab2->setObjectName(QStringLiteral("tab2"));
        tabWidget->addTab(tab2, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 5);

        btnAdd = new QPushButton(TurnoutWidget);
        btnAdd->setObjectName(QStringLiteral("btnAdd"));
        btnAdd->setMaximumSize(QSize(80, 16777215));

        gridLayout->addWidget(btnAdd, 1, 0, 1, 1);

        chkFeedback = new QCheckBox(TurnoutWidget);
        chkFeedback->setObjectName(QStringLiteral("chkFeedback"));

        gridLayout->addWidget(chkFeedback, 1, 1, 1, 1);

        chkLockInfo = new QCheckBox(TurnoutWidget);
        chkLockInfo->setObjectName(QStringLiteral("chkLockInfo"));

        gridLayout->addWidget(chkLockInfo, 1, 2, 1, 1);

        chkAuto = new QCheckBox(TurnoutWidget);
        chkAuto->setObjectName(QStringLiteral("chkAuto"));

        gridLayout->addWidget(chkAuto, 1, 3, 1, 1);

        chkSpeedDetails = new QCheckBox(TurnoutWidget);
        chkSpeedDetails->setObjectName(QStringLiteral("chkSpeedDetails"));

        gridLayout->addWidget(chkSpeedDetails, 1, 4, 1, 1);


        retranslateUi(TurnoutWidget);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(TurnoutWidget);
    } // setupUi

    void retranslateUi(QWidget *TurnoutWidget)
    {
        TurnoutWidget->setWindowTitle(QApplication::translate("TurnoutWidget", "Form", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab1), QApplication::translate("TurnoutWidget", "All", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab2), QApplication::translate("TurnoutWidget", "Internal", 0));
        btnAdd->setText(QApplication::translate("TurnoutWidget", "Add", 0));
#ifndef QT_NO_TOOLTIP
        chkFeedback->setToolTip(QApplication::translate("TurnoutWidget", "<html><head/><body><p>Show extra columns for configuring turnout feedback?</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        chkFeedback->setText(QApplication::translate("TurnoutWidget", "Show feedback information", 0));
#ifndef QT_NO_TOOLTIP
        chkLockInfo->setToolTip(QApplication::translate("TurnoutWidget", "<html><head/><body><p>Show extra columns for configuring turnout lock?</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        chkLockInfo->setText(QApplication::translate("TurnoutWidget", "Show lock information", 0));
        chkAuto->setText(QApplication::translate("TurnoutWidget", "Automatic retry", 0));
#ifndef QT_NO_TOOLTIP
        chkSpeedDetails->setToolTip(QApplication::translate("TurnoutWidget", "<html><head/><body><p>Show extra columns for configuring turnout Speeds, when used with Signalling?</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        chkSpeedDetails->setText(QApplication::translate("TurnoutWidget", "Show speed details", 0));
    } // retranslateUi

};

namespace Ui {
    class TurnoutWidget: public Ui_TurnoutWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TURNOUTWIDGET_H
