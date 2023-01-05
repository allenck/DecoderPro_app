/********************************************************************************
** Form generated from reading UI file 'loconetmsgdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOCONETMSGDIALOG_H
#define UI_LOCONETMSGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
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
            LocoNetMsgDialog->setObjectName(QString::fromUtf8("LocoNetMsgDialog"));
        LocoNetMsgDialog->resize(400, 152);
        gridLayout = new QGridLayout(LocoNetMsgDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(LocoNetMsgDialog);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        cbOpcode = new QComboBox(LocoNetMsgDialog);
        cbOpcode->setObjectName(QString::fromUtf8("cbOpcode"));

        gridLayout->addWidget(cbOpcode, 0, 1, 1, 1);

        label_2 = new QLabel(LocoNetMsgDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        lineEdit = new QLineEdit(LocoNetMsgDialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 1, 1, 1, 1);

        btnOk = new QPushButton(LocoNetMsgDialog);
        btnOk->setObjectName(QString::fromUtf8("btnOk"));

        gridLayout->addWidget(btnOk, 3, 0, 1, 1);

        lblMsg = new QLabel(LocoNetMsgDialog);
        lblMsg->setObjectName(QString::fromUtf8("lblMsg"));

        gridLayout->addWidget(lblMsg, 2, 0, 1, 2);


        retranslateUi(LocoNetMsgDialog);

        QMetaObject::connectSlotsByName(LocoNetMsgDialog);
    } // setupUi

    void retranslateUi(JmriPanel *LocoNetMsgDialog)
    {
        LocoNetMsgDialog->setWindowTitle(QCoreApplication::translate("LocoNetMsgDialog", "Send LocoNet Packet", nullptr));
        label->setText(QCoreApplication::translate("LocoNetMsgDialog", "OpCode:", nullptr));
        label_2->setText(QCoreApplication::translate("LocoNetMsgDialog", "Data:", nullptr));
        btnOk->setText(QCoreApplication::translate("LocoNetMsgDialog", "OK", nullptr));
        lblMsg->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LocoNetMsgDialog: public Ui_LocoNetMsgDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOCONETMSGDIALOG_H
