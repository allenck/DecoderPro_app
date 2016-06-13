/********************************************************************************
** Form generated from reading UI file 'addresspanel.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDRESSPANEL_H
#define UI_ADDRESSPANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "jtextfield.h"
#include "rosterentryselectorpanel.h"

QT_BEGIN_NAMESPACE

class Ui_AddressPanel
{
public:
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_5;
    JTextField *edAddress;
    QPushButton *setButton;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *dispatchButton;
    QPushButton *releaseButton;
    QPushButton *progButton;
    RosterEntrySelectorPanel *rosterBox;

    void setupUi(QDockWidget *AddressPanel)
    {
        if (AddressPanel->objectName().isEmpty())
            AddressPanel->setObjectName(QStringLiteral("AddressPanel"));
        AddressPanel->resize(291, 196);
        QFont font;
        font.setPointSize(8);
        AddressPanel->setFont(font);
        AddressPanel->setAllowedAreas(Qt::BottomDockWidgetArea|Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        verticalLayout = new QVBoxLayout(dockWidgetContents);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        edAddress = new JTextField(dockWidgetContents);
        edAddress->setObjectName(QStringLiteral("edAddress"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(edAddress->sizePolicy().hasHeightForWidth());
        edAddress->setSizePolicy(sizePolicy);
        edAddress->setMaximumSize(QSize(180, 16777215));
        QFont font1;
        font1.setPointSize(48);
        edAddress->setFont(font1);
        edAddress->setInputMethodHints(Qt::ImhPreferNumbers);

        horizontalLayout_5->addWidget(edAddress);

        setButton = new QPushButton(dockWidgetContents);
        setButton->setObjectName(QStringLiteral("setButton"));
        sizePolicy.setHeightForWidth(setButton->sizePolicy().hasHeightForWidth());
        setButton->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(setButton);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        dispatchButton = new QPushButton(dockWidgetContents);
        dispatchButton->setObjectName(QStringLiteral("dispatchButton"));
        sizePolicy.setHeightForWidth(dispatchButton->sizePolicy().hasHeightForWidth());
        dispatchButton->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(dispatchButton);

        releaseButton = new QPushButton(dockWidgetContents);
        releaseButton->setObjectName(QStringLiteral("releaseButton"));
        sizePolicy.setHeightForWidth(releaseButton->sizePolicy().hasHeightForWidth());
        releaseButton->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(releaseButton);

        progButton = new QPushButton(dockWidgetContents);
        progButton->setObjectName(QStringLiteral("progButton"));
        sizePolicy.setHeightForWidth(progButton->sizePolicy().hasHeightForWidth());
        progButton->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(progButton);


        verticalLayout->addLayout(horizontalLayout_4);

        rosterBox = new RosterEntrySelectorPanel(dockWidgetContents);
        rosterBox->setObjectName(QStringLiteral("rosterBox"));

        verticalLayout->addWidget(rosterBox);

        AddressPanel->setWidget(dockWidgetContents);

        retranslateUi(AddressPanel);

        QMetaObject::connectSlotsByName(AddressPanel);
    } // setupUi

    void retranslateUi(QDockWidget *AddressPanel)
    {
        AddressPanel->setWindowTitle(QApplication::translate("AddressPanel", "AddressPanel", 0));
        edAddress->setText(QApplication::translate("AddressPanel", "0000", 0));
        setButton->setText(QApplication::translate("AddressPanel", "Set", 0));
        dispatchButton->setText(QApplication::translate("AddressPanel", "Dispatch", 0));
        releaseButton->setText(QApplication::translate("AddressPanel", "Release", 0));
        progButton->setText(QApplication::translate("AddressPanel", "Program", 0));
    } // retranslateUi

};

namespace Ui {
    class AddressPanel: public Ui_AddressPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDRESSPANEL_H
