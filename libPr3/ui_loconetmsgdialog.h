/********************************************************************************
** Form generated from reading UI file 'loconetmsgdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOCONETMSGDIALOG_H
#define UI_LOCONETMSGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include "jmripanel.h"

QT_BEGIN_NAMESPACE

class Ui_LocoNetMsgDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QComboBox *cbOpcode;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QPushButton *btnOk;
    QLabel *lblMsg;

    void setupUi(JmriPanel *LocoNetMsgDialog)
    {
        if (LocoNetMsgDialog->objectName().isEmpty())
            LocoNetMsgDialog->setObjectName(QStringLiteral("LocoNetMsgDialog"));
        LocoNetMsgDialog->resize(400, 152);
        gridLayout = new QGridLayout(LocoNetMsgDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(LocoNetMsgDialog);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        cbOpcode = new QComboBox(LocoNetMsgDialog);
        cbOpcode->setObjectName(QStringLiteral("cbOpcode"));

        gridLayout->addWidget(cbOpcode, 0, 1, 1, 1);

        label_2 = new QLabel(LocoNetMsgDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        lineEdit = new QLineEdit(LocoNetMsgDialog);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout->addWidget(lineEdit, 1, 1, 1, 1);

        btnOk = new QPushButton(LocoNetMsgDialog);
        btnOk->setObjectName(QStringLiteral("btnOk"));

        gridLayout->addWidget(btnOk, 3, 0, 1, 1);

        lblMsg = new QLabel(LocoNetMsgDialog);
        lblMsg->setObjectName(QStringLiteral("lblMsg"));

        gridLayout->addWidget(lblMsg, 2, 0, 1, 2);


        retranslateUi(LocoNetMsgDialog);

        QMetaObject::connectSlotsByName(LocoNetMsgDialog);
    } // setupUi

    void retranslateUi(JmriPanel *LocoNetMsgDialog)
    {
        LocoNetMsgDialog->setWindowTitle(QApplication::translate("LocoNetMsgDialog", "Send LocoNet Packet", Q_NULLPTR));
        label->setText(QApplication::translate("LocoNetMsgDialog", "OpCode:", Q_NULLPTR));
        label_2->setText(QApplication::translate("LocoNetMsgDialog", "Data:", Q_NULLPTR));
        btnOk->setText(QApplication::translate("LocoNetMsgDialog", "OK", Q_NULLPTR));
        lblMsg->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LocoNetMsgDialog: public Ui_LocoNetMsgDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOCONETMSGDIALOG_H
