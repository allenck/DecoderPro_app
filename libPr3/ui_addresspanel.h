/********************************************************************************
** Form generated from reading UI file 'addresspanel.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDRESSPANEL_H
#define UI_ADDRESSPANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHBoxLayout>
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
            AddressPanel->setObjectName(QLatin1String("AddressPanel"));
        AddressPanel->resize(291, 179);
        QFont font;
        font.setPointSize(8);
        AddressPanel->setFont(font);
        AddressPanel->setAllowedAreas(Qt::BottomDockWidgetArea|Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QLatin1String("dockWidgetContents"));
        verticalLayout = new QVBoxLayout(dockWidgetContents);
        verticalLayout->setObjectName(QLatin1String("verticalLayout"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QLatin1String("horizontalLayout_5"));
        edAddress = new JTextField(dockWidgetContents);
        edAddress->setObjectName(QLatin1String("edAddress"));
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
        setButton->setObjectName(QLatin1String("setButton"));
        sizePolicy.setHeightForWidth(setButton->sizePolicy().hasHeightForWidth());
        setButton->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(setButton);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QLatin1String("horizontalLayout_4"));
        dispatchButton = new QPushButton(dockWidgetContents);
        dispatchButton->setObjectName(QLatin1String("dispatchButton"));
        sizePolicy.setHeightForWidth(dispatchButton->sizePolicy().hasHeightForWidth());
        dispatchButton->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(dispatchButton);

        releaseButton = new QPushButton(dockWidgetContents);
        releaseButton->setObjectName(QLatin1String("releaseButton"));
        sizePolicy.setHeightForWidth(releaseButton->sizePolicy().hasHeightForWidth());
        releaseButton->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(releaseButton);

        progButton = new QPushButton(dockWidgetContents);
        progButton->setObjectName(QLatin1String("progButton"));
        sizePolicy.setHeightForWidth(progButton->sizePolicy().hasHeightForWidth());
        progButton->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(progButton);


        verticalLayout->addLayout(horizontalLayout_4);

        rosterBox = new RosterEntrySelectorPanel(dockWidgetContents);
        rosterBox->setObjectName(QLatin1String("rosterBox"));

        verticalLayout->addWidget(rosterBox);

        AddressPanel->setWidget(dockWidgetContents);

        retranslateUi(AddressPanel);

        QMetaObject::connectSlotsByName(AddressPanel);
    } // setupUi

    void retranslateUi(QDockWidget *AddressPanel)
    {
        AddressPanel->setWindowTitle(QApplication::translate("AddressPanel", "AddressPanel", nullptr));
        edAddress->setText(QApplication::translate("AddressPanel", "0000", nullptr));
        setButton->setText(QApplication::translate("AddressPanel", "Set", nullptr));
        dispatchButton->setText(QApplication::translate("AddressPanel", "Dispatch", nullptr));
        releaseButton->setText(QApplication::translate("AddressPanel", "Release", nullptr));
        progButton->setText(QApplication::translate("AddressPanel", "Program", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddressPanel: public Ui_AddressPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDRESSPANEL_H
