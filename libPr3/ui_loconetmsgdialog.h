/********************************************************************************
** Form generated from reading UI file 'loconetmsgdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
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
            LocoNetMsgDialog->setObjectName(QLatin1String("LocoNetMsgDialog"));
        LocoNetMsgDialog->resize(400, 152);
        gridLayout = new QGridLayout(LocoNetMsgDialog);
        gridLayout->setObjectName(QLatin1String("gridLayout"));
        label = new QLabel(LocoNetMsgDialog);
        label->setObjectName(QLatin1String("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        cbOpcode = new QComboBox(LocoNetMsgDialog);
        cbOpcode->setObjectName(QLatin1String("cbOpcode"));

        gridLayout->addWidget(cbOpcode, 0, 1, 1, 1);

        label_2 = new QLabel(LocoNetMsgDialog);
        label_2->setObjectName(QLatin1String("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        lineEdit = new QLineEdit(LocoNetMsgDialog);
        lineEdit->setObjectName(QLatin1String("lineEdit"));

        gridLayout->addWidget(lineEdit, 1, 1, 1, 1);

        btnOk = new QPushButton(LocoNetMsgDialog);
        btnOk->setObjectName(QLatin1String("btnOk"));

        gridLayout->addWidget(btnOk, 3, 0, 1, 1);

        lblMsg = new QLabel(LocoNetMsgDialog);
        lblMsg->setObjectName(QLatin1String("lblMsg"));

        gridLayout->addWidget(lblMsg, 2, 0, 1, 2);


        retranslateUi(LocoNetMsgDialog);

        QMetaObject::connectSlotsByName(LocoNetMsgDialog);
    } // setupUi

    void retranslateUi(JmriPanel *LocoNetMsgDialog)
    {
        LocoNetMsgDialog->setWindowTitle(QApplication::translate("LocoNetMsgDialog", "Send LocoNet Packet", nullptr));
        label->setText(QApplication::translate("LocoNetMsgDialog", "OpCode:", nullptr));
        label_2->setText(QApplication::translate("LocoNetMsgDialog", "Data:", nullptr));
        btnOk->setText(QApplication::translate("LocoNetMsgDialog", "OK", nullptr));
        lblMsg->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LocoNetMsgDialog: public Ui_LocoNetMsgDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOCONETMSGDIALOG_H
