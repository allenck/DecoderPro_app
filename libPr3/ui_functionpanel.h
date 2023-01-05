/********************************************************************************
** Form generated from reading UI file 'functionpanel.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FUNCTIONPANEL_H
#define UI_FUNCTIONPANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "functionbutton.h"

QT_BEGIN_NAMESPACE

class Ui_FunctionPanel
{
public:
    QWidget *dockWidgetContents;
    QGridLayout *gridLayout;
    FunctionButton *btnF1;
    FunctionButton *btnF2;
    FunctionButton *btnF3;
    QPushButton *btnHash;
    FunctionButton *btnF15;
    FunctionButton *btnF12;
    FunctionButton *btnF9;
    FunctionButton *btnF6;
    FunctionButton *btnF5;
    FunctionButton *btnF8;
    FunctionButton *btnLight;
    QPushButton *btnStar;
    FunctionButton *btnF13;
    FunctionButton *btnF10;
    FunctionButton *btnF7;
    FunctionButton *btnF4;
    FunctionButton *btnF11;
    FunctionButton *btnF14;

    void setupUi(QDockWidget *FunctionPanel)
    {
        if (FunctionPanel->objectName().isEmpty())
            FunctionPanel->setObjectName(QString::fromUtf8("FunctionPanel"));
        FunctionPanel->resize(198, 300);
        QFont font;
        font.setPointSize(8);
        FunctionPanel->setFont(font);
        FunctionPanel->setStyleSheet(QString::fromUtf8("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid pink; }"));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        gridLayout = new QGridLayout(dockWidgetContents);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        btnF1 = new FunctionButton(dockWidgetContents);
        btnF1->setObjectName(QString::fromUtf8("btnF1"));
        btnF1->setMaximumSize(QSize(56, 30));

        gridLayout->addWidget(btnF1, 0, 0, 1, 1);

        btnF2 = new FunctionButton(dockWidgetContents);
        btnF2->setObjectName(QString::fromUtf8("btnF2"));
        btnF2->setMaximumSize(QSize(56, 30));

        gridLayout->addWidget(btnF2, 0, 1, 1, 1);

        btnF3 = new FunctionButton(dockWidgetContents);
        btnF3->setObjectName(QString::fromUtf8("btnF3"));
        btnF3->setMaximumSize(QSize(56, 30));

        gridLayout->addWidget(btnF3, 0, 2, 1, 1);

        btnHash = new QPushButton(dockWidgetContents);
        btnHash->setObjectName(QString::fromUtf8("btnHash"));
        btnHash->setMaximumSize(QSize(56, 30));

        gridLayout->addWidget(btnHash, 5, 2, 1, 1);

        btnF15 = new FunctionButton(dockWidgetContents);
        btnF15->setObjectName(QString::fromUtf8("btnF15"));
        btnF15->setMaximumSize(QSize(56, 30));

        gridLayout->addWidget(btnF15, 4, 2, 1, 1);

        btnF12 = new FunctionButton(dockWidgetContents);
        btnF12->setObjectName(QString::fromUtf8("btnF12"));
        btnF12->setMaximumSize(QSize(56, 30));

        gridLayout->addWidget(btnF12, 3, 2, 1, 1);

        btnF9 = new FunctionButton(dockWidgetContents);
        btnF9->setObjectName(QString::fromUtf8("btnF9"));
        btnF9->setMaximumSize(QSize(56, 30));

        gridLayout->addWidget(btnF9, 2, 2, 1, 1);

        btnF6 = new FunctionButton(dockWidgetContents);
        btnF6->setObjectName(QString::fromUtf8("btnF6"));
        btnF6->setMaximumSize(QSize(56, 30));

        gridLayout->addWidget(btnF6, 1, 2, 1, 1);

        btnF5 = new FunctionButton(dockWidgetContents);
        btnF5->setObjectName(QString::fromUtf8("btnF5"));
        btnF5->setMaximumSize(QSize(56, 30));

        gridLayout->addWidget(btnF5, 1, 1, 1, 1);

        btnF8 = new FunctionButton(dockWidgetContents);
        btnF8->setObjectName(QString::fromUtf8("btnF8"));
        btnF8->setMaximumSize(QSize(56, 30));

        gridLayout->addWidget(btnF8, 2, 1, 1, 1);

        btnLight = new FunctionButton(dockWidgetContents);
        btnLight->setObjectName(QString::fromUtf8("btnLight"));
        btnLight->setMaximumSize(QSize(56, 30));

        gridLayout->addWidget(btnLight, 5, 1, 1, 1);

        btnStar = new QPushButton(dockWidgetContents);
        btnStar->setObjectName(QString::fromUtf8("btnStar"));
        btnStar->setMaximumSize(QSize(56, 30));

        gridLayout->addWidget(btnStar, 5, 0, 1, 1);

        btnF13 = new FunctionButton(dockWidgetContents);
        btnF13->setObjectName(QString::fromUtf8("btnF13"));
        btnF13->setMaximumSize(QSize(56, 30));

        gridLayout->addWidget(btnF13, 4, 0, 1, 1);

        btnF10 = new FunctionButton(dockWidgetContents);
        btnF10->setObjectName(QString::fromUtf8("btnF10"));
        btnF10->setMaximumSize(QSize(56, 30));

        gridLayout->addWidget(btnF10, 3, 0, 1, 1);

        btnF7 = new FunctionButton(dockWidgetContents);
        btnF7->setObjectName(QString::fromUtf8("btnF7"));
        btnF7->setMaximumSize(QSize(56, 30));

        gridLayout->addWidget(btnF7, 2, 0, 1, 1);

        btnF4 = new FunctionButton(dockWidgetContents);
        btnF4->setObjectName(QString::fromUtf8("btnF4"));
        btnF4->setMaximumSize(QSize(56, 30));

        gridLayout->addWidget(btnF4, 1, 0, 1, 1);

        btnF11 = new FunctionButton(dockWidgetContents);
        btnF11->setObjectName(QString::fromUtf8("btnF11"));
        btnF11->setMaximumSize(QSize(56, 30));

        gridLayout->addWidget(btnF11, 3, 1, 1, 1);

        btnF14 = new FunctionButton(dockWidgetContents);
        btnF14->setObjectName(QString::fromUtf8("btnF14"));
        btnF14->setMaximumSize(QSize(56, 30));

        gridLayout->addWidget(btnF14, 4, 1, 1, 1);

        FunctionPanel->setWidget(dockWidgetContents);

        retranslateUi(FunctionPanel);

        QMetaObject::connectSlotsByName(FunctionPanel);
    } // setupUi

    void retranslateUi(QDockWidget *FunctionPanel)
    {
        FunctionPanel->setWindowTitle(QCoreApplication::translate("FunctionPanel", "DockWidget", nullptr));
        btnF1->setText(QCoreApplication::translate("FunctionPanel", "F1", nullptr));
        btnF2->setText(QCoreApplication::translate("FunctionPanel", "F2", nullptr));
        btnF3->setText(QCoreApplication::translate("FunctionPanel", "F3", nullptr));
        btnHash->setText(QCoreApplication::translate("FunctionPanel", "#", nullptr));
        btnF15->setText(QCoreApplication::translate("FunctionPanel", "F15", nullptr));
        btnF12->setText(QCoreApplication::translate("FunctionPanel", "F12", nullptr));
        btnF9->setText(QCoreApplication::translate("FunctionPanel", "F9", nullptr));
        btnF6->setText(QCoreApplication::translate("FunctionPanel", "F6", nullptr));
        btnF5->setText(QCoreApplication::translate("FunctionPanel", "F5", nullptr));
        btnF8->setText(QCoreApplication::translate("FunctionPanel", "F8", nullptr));
        btnLight->setText(QCoreApplication::translate("FunctionPanel", "Light", nullptr));
        btnStar->setText(QCoreApplication::translate("FunctionPanel", "*", nullptr));
        btnF13->setText(QCoreApplication::translate("FunctionPanel", "F13", nullptr));
        btnF10->setText(QCoreApplication::translate("FunctionPanel", "F10", nullptr));
        btnF7->setText(QCoreApplication::translate("FunctionPanel", "F7", nullptr));
        btnF4->setText(QCoreApplication::translate("FunctionPanel", "F4", nullptr));
        btnF11->setText(QCoreApplication::translate("FunctionPanel", "F11", nullptr));
        btnF14->setText(QCoreApplication::translate("FunctionPanel", "F14", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FunctionPanel: public Ui_FunctionPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FUNCTIONPANEL_H
