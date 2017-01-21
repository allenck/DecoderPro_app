/********************************************************************************
** Form generated from reading UI file 'registerswidget.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERSWIDGET_H
#define UI_REGISTERSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegistersWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLineEdit *edAddr;
    QLineEdit *edCfg;
    QLineEdit *edVal1;
    QLineEdit *edVal2;
    QToolButton *btnRead;
    QToolButton *btnWrite;
    QToolButton *btnEditVal;

    void setupUi(QWidget *RegistersWidget)
    {
        if (RegistersWidget->objectName().isEmpty())
            RegistersWidget->setObjectName(QStringLiteral("RegistersWidget"));
        RegistersWidget->resize(32, 231);
        QFont font;
        font.setPointSize(7);
        RegistersWidget->setFont(font);
        verticalLayout_2 = new QVBoxLayout(RegistersWidget);
        verticalLayout_2->setSpacing(2);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        edAddr = new QLineEdit(RegistersWidget);
        edAddr->setObjectName(QStringLiteral("edAddr"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(edAddr->sizePolicy().hasHeightForWidth());
        edAddr->setSizePolicy(sizePolicy);
        edAddr->setMaximumSize(QSize(30, 16777215));
        edAddr->setFont(font);
        edAddr->setStyleSheet(QStringLiteral("QLineEdit { background-color : white; }"));

        verticalLayout->addWidget(edAddr);

        edCfg = new QLineEdit(RegistersWidget);
        edCfg->setObjectName(QStringLiteral("edCfg"));
        sizePolicy.setHeightForWidth(edCfg->sizePolicy().hasHeightForWidth());
        edCfg->setSizePolicy(sizePolicy);
        edCfg->setMaximumSize(QSize(30, 16777215));
        edCfg->setFont(font);
        edCfg->setStyleSheet(QStringLiteral("QLineEdit { background-color : white; }"));

        verticalLayout->addWidget(edCfg);

        edVal1 = new QLineEdit(RegistersWidget);
        edVal1->setObjectName(QStringLiteral("edVal1"));
        sizePolicy.setHeightForWidth(edVal1->sizePolicy().hasHeightForWidth());
        edVal1->setSizePolicy(sizePolicy);
        edVal1->setMaximumSize(QSize(30, 16777215));
        edVal1->setFont(font);
        edVal1->setStyleSheet(QStringLiteral("QLineEdit { background-color : white; }"));

        verticalLayout->addWidget(edVal1);

        edVal2 = new QLineEdit(RegistersWidget);
        edVal2->setObjectName(QStringLiteral("edVal2"));
        sizePolicy.setHeightForWidth(edVal2->sizePolicy().hasHeightForWidth());
        edVal2->setSizePolicy(sizePolicy);
        edVal2->setMaximumSize(QSize(30, 16777215));
        edVal2->setFont(font);
        edVal2->setStyleSheet(QStringLiteral("QLineEdit { background-color : white; }"));

        verticalLayout->addWidget(edVal2);

        btnRead = new QToolButton(RegistersWidget);
        btnRead->setObjectName(QStringLiteral("btnRead"));
        sizePolicy.setHeightForWidth(btnRead->sizePolicy().hasHeightForWidth());
        btnRead->setSizePolicy(sizePolicy);
        btnRead->setMaximumSize(QSize(30, 16777215));

        verticalLayout->addWidget(btnRead);

        btnWrite = new QToolButton(RegistersWidget);
        btnWrite->setObjectName(QStringLiteral("btnWrite"));
        sizePolicy.setHeightForWidth(btnWrite->sizePolicy().hasHeightForWidth());
        btnWrite->setSizePolicy(sizePolicy);
        btnWrite->setMaximumSize(QSize(30, 16777215));

        verticalLayout->addWidget(btnWrite);

        btnEditVal = new QToolButton(RegistersWidget);
        btnEditVal->setObjectName(QStringLiteral("btnEditVal"));
        btnEditVal->setMaximumSize(QSize(30, 16777215));

        verticalLayout->addWidget(btnEditVal);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(RegistersWidget);

        QMetaObject::connectSlotsByName(RegistersWidget);
    } // setupUi

    void retranslateUi(QWidget *RegistersWidget)
    {
        RegistersWidget->setWindowTitle(QApplication::translate("RegistersWidget", "Form", 0));
        edAddr->setText(QApplication::translate("RegistersWidget", "0x000", 0));
        btnRead->setText(QApplication::translate("RegistersWidget", "R", 0));
        btnWrite->setText(QApplication::translate("RegistersWidget", "W", 0));
        btnEditVal->setText(QApplication::translate("RegistersWidget", "Edit", 0));
    } // retranslateUi

};

namespace Ui {
    class RegistersWidget: public Ui_RegistersWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERSWIDGET_H
