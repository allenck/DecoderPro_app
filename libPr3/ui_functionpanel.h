/********************************************************************************
** Form generated from reading UI file 'functionpanel.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FUNCTIONPANEL_H
#define UI_FUNCTIONPANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
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
            FunctionPanel->setObjectName(QStringLiteral("FunctionPanel"));
        FunctionPanel->resize(198, 300);
        QFont font;
        font.setPointSize(8);
        FunctionPanel->setFont(font);
        FunctionPanel->setStyleSheet(QStringLiteral("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid pink; }"));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        gridLayout = new QGridLayout(dockWidgetContents);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        btnF1 = new FunctionButton(dockWidgetContents);
        btnF1->setObjectName(QStringLiteral("btnF1"));
        btnF1->setMaximumSize(QSize(56, 30));

        gridLayout->addWidget(btnF1, 0, 0, 1, 1);

        btnF2 = new FunctionButton(dockWidgetContents);
        btnF2->setObjectName(QStringLiteral("btnF2"));
        btnF2->setMaximumSize(QSize(56, 30));

        gridLayout->addWidget(btnF2, 0, 1, 1, 1);

        btnF3 = new FunctionButton(dockWidgetContents);
        btnF3->setObjectName(QStringLiteral("btnF3"));
        btnF3->setMaximumSize(QSize(56, 30));

        gridLayout->addWidget(btnF3, 0, 2, 1, 1);

        btnHash = new QPushButton(dockWidgetContents);
        btnHash->setObjectName(QStringLiteral("btnHash"));
        btnHash->setMaximumSize(QSize(56, 30));

        gridLayout->addWidget(btnHash, 5, 2, 1, 1);

        btnF15 = new FunctionButton(dockWidgetContents);
        btnF15->setObjectName(QStringLiteral("btnF15"));
        btnF15->setMaximumSize(QSize(56, 30));

        gridLayout->addWidget(btnF15, 4, 2, 1, 1);

        btnF12 = new FunctionButton(dockWidgetContents);
        btnF12->setObjectName(QStringLiteral("btnF12"));
        btnF12->setMaximumSize(QSize(56, 30));

        gridLayout->addWidget(btnF12, 3, 2, 1, 1);

        btnF9 = new FunctionButton(dockWidgetContents);
        btnF9->setObjectName(QStringLiteral("btnF9"));
        btnF9->setMaximumSize(QSize(56, 30));

        gridLayout->addWidget(btnF9, 2, 2, 1, 1);

        btnF6 = new FunctionButton(dockWidgetContents);
        btnF6->setObjectName(QStringLiteral("btnF6"));
        btnF6->setMaximumSize(QSize(56, 30));

        gridLayout->addWidget(btnF6, 1, 2, 1, 1);

        btnF5 = new FunctionButton(dockWidgetContents);
        btnF5->setObjectName(QStringLiteral("btnF5"));
        btnF5->setMaximumSize(QSize(56, 30));

        gridLayout->addWidget(btnF5, 1, 1, 1, 1);

        btnF8 = new FunctionButton(dockWidgetContents);
        btnF8->setObjectName(QStringLiteral("btnF8"));
        btnF8->setMaximumSize(QSize(56, 30));

        gridLayout->addWidget(btnF8, 2, 1, 1, 1);

        btnLight = new FunctionButton(dockWidgetContents);
        btnLight->setObjectName(QStringLiteral("btnLight"));
        btnLight->setMaximumSize(QSize(56, 30));

        gridLayout->addWidget(btnLight, 5, 1, 1, 1);

        btnStar = new QPushButton(dockWidgetContents);
        btnStar->setObjectName(QStringLiteral("btnStar"));
        btnStar->setMaximumSize(QSize(56, 30));

        gridLayout->addWidget(btnStar, 5, 0, 1, 1);

        btnF13 = new FunctionButton(dockWidgetContents);
        btnF13->setObjectName(QStringLiteral("btnF13"));
        btnF13->setMaximumSize(QSize(56, 30));

        gridLayout->addWidget(btnF13, 4, 0, 1, 1);

        btnF10 = new FunctionButton(dockWidgetContents);
        btnF10->setObjectName(QStringLiteral("btnF10"));
        btnF10->setMaximumSize(QSize(56, 30));

        gridLayout->addWidget(btnF10, 3, 0, 1, 1);

        btnF7 = new FunctionButton(dockWidgetContents);
        btnF7->setObjectName(QStringLiteral("btnF7"));
        btnF7->setMaximumSize(QSize(56, 30));

        gridLayout->addWidget(btnF7, 2, 0, 1, 1);

        btnF4 = new FunctionButton(dockWidgetContents);
        btnF4->setObjectName(QStringLiteral("btnF4"));
        btnF4->setMaximumSize(QSize(56, 30));

        gridLayout->addWidget(btnF4, 1, 0, 1, 1);

        btnF11 = new FunctionButton(dockWidgetContents);
        btnF11->setObjectName(QStringLiteral("btnF11"));
        btnF11->setMaximumSize(QSize(56, 30));

        gridLayout->addWidget(btnF11, 3, 1, 1, 1);

        btnF14 = new FunctionButton(dockWidgetContents);
        btnF14->setObjectName(QStringLiteral("btnF14"));
        btnF14->setMaximumSize(QSize(56, 30));

        gridLayout->addWidget(btnF14, 4, 1, 1, 1);

        FunctionPanel->setWidget(dockWidgetContents);

        retranslateUi(FunctionPanel);

        QMetaObject::connectSlotsByName(FunctionPanel);
    } // setupUi

    void retranslateUi(QDockWidget *FunctionPanel)
    {
        FunctionPanel->setWindowTitle(QApplication::translate("FunctionPanel", "DockWidget", Q_NULLPTR));
        btnF1->setText(QApplication::translate("FunctionPanel", "F1", Q_NULLPTR));
        btnF2->setText(QApplication::translate("FunctionPanel", "F2", Q_NULLPTR));
        btnF3->setText(QApplication::translate("FunctionPanel", "F3", Q_NULLPTR));
        btnHash->setText(QApplication::translate("FunctionPanel", "#", Q_NULLPTR));
        btnF15->setText(QApplication::translate("FunctionPanel", "F15", Q_NULLPTR));
        btnF12->setText(QApplication::translate("FunctionPanel", "F12", Q_NULLPTR));
        btnF9->setText(QApplication::translate("FunctionPanel", "F9", Q_NULLPTR));
        btnF6->setText(QApplication::translate("FunctionPanel", "F6", Q_NULLPTR));
        btnF5->setText(QApplication::translate("FunctionPanel", "F5", Q_NULLPTR));
        btnF8->setText(QApplication::translate("FunctionPanel", "F8", Q_NULLPTR));
        btnLight->setText(QApplication::translate("FunctionPanel", "Light", Q_NULLPTR));
        btnStar->setText(QApplication::translate("FunctionPanel", "*", Q_NULLPTR));
        btnF13->setText(QApplication::translate("FunctionPanel", "F13", Q_NULLPTR));
        btnF10->setText(QApplication::translate("FunctionPanel", "F10", Q_NULLPTR));
        btnF7->setText(QApplication::translate("FunctionPanel", "F7", Q_NULLPTR));
        btnF4->setText(QApplication::translate("FunctionPanel", "F4", Q_NULLPTR));
        btnF11->setText(QApplication::translate("FunctionPanel", "F11", Q_NULLPTR));
        btnF14->setText(QApplication::translate("FunctionPanel", "F14", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class FunctionPanel: public Ui_FunctionPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FUNCTIONPANEL_H
