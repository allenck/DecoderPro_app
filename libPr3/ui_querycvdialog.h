/********************************************************************************
** Form generated from reading UI file 'querycvdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUERYCVDIALOG_H
#define UI_QUERYCVDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QueryCvDialog
{
public:
    QFormLayout *formLayout;
    QGridLayout *gridLayout;
    QLabel *lblUnitAddr;
    QLineEdit *edAddress;
    QLabel *label_2;
    QLineEdit *edCv;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnOK;
    QPushButton *btnCancel;
    QCheckBox *chkHex;

    void setupUi(QWidget *QueryCvDialog)
    {
        if (QueryCvDialog->objectName().isEmpty())
            QueryCvDialog->setObjectName(QString::fromUtf8("QueryCvDialog"));
        QueryCvDialog->resize(276, 143);
        formLayout = new QFormLayout(QueryCvDialog);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lblUnitAddr = new QLabel(QueryCvDialog);
        lblUnitAddr->setObjectName(QString::fromUtf8("lblUnitAddr"));

        gridLayout->addWidget(lblUnitAddr, 0, 0, 1, 1);

        edAddress = new QLineEdit(QueryCvDialog);
        edAddress->setObjectName(QString::fromUtf8("edAddress"));

        gridLayout->addWidget(edAddress, 0, 1, 1, 1);

        label_2 = new QLabel(QueryCvDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        edCv = new QLineEdit(QueryCvDialog);
        edCv->setObjectName(QString::fromUtf8("edCv"));

        gridLayout->addWidget(edCv, 1, 1, 1, 1);


        formLayout->setLayout(0, QFormLayout::LabelRole, gridLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btnOK = new QPushButton(QueryCvDialog);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));

        horizontalLayout->addWidget(btnOK);

        btnCancel = new QPushButton(QueryCvDialog);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));

        horizontalLayout->addWidget(btnCancel);


        formLayout->setLayout(2, QFormLayout::LabelRole, horizontalLayout);

        chkHex = new QCheckBox(QueryCvDialog);
        chkHex->setObjectName(QString::fromUtf8("chkHex"));

        formLayout->setWidget(1, QFormLayout::LabelRole, chkHex);


        retranslateUi(QueryCvDialog);

        QMetaObject::connectSlotsByName(QueryCvDialog);
    } // setupUi

    void retranslateUi(QWidget *QueryCvDialog)
    {
        QueryCvDialog->setWindowTitle(QCoreApplication::translate("QueryCvDialog", "Query Cv", nullptr));
        lblUnitAddr->setText(QCoreApplication::translate("QueryCvDialog", "Address:", nullptr));
        label_2->setText(QCoreApplication::translate("QueryCvDialog", "CV:", nullptr));
        btnOK->setText(QCoreApplication::translate("QueryCvDialog", "OK", nullptr));
        btnCancel->setText(QCoreApplication::translate("QueryCvDialog", "Cancel", nullptr));
        chkHex->setText(QCoreApplication::translate("QueryCvDialog", "Display Hex", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QueryCvDialog: public Ui_QueryCvDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUERYCVDIALOG_H
