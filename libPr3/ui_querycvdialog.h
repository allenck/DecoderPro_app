/********************************************************************************
** Form generated from reading UI file 'querycvdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
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
            QueryCvDialog->setObjectName(QLatin1String("QueryCvDialog"));
        QueryCvDialog->resize(276, 143);
        formLayout = new QFormLayout(QueryCvDialog);
        formLayout->setObjectName(QLatin1String("formLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QLatin1String("gridLayout"));
        lblUnitAddr = new QLabel(QueryCvDialog);
        lblUnitAddr->setObjectName(QLatin1String("lblUnitAddr"));

        gridLayout->addWidget(lblUnitAddr, 0, 0, 1, 1);

        edAddress = new QLineEdit(QueryCvDialog);
        edAddress->setObjectName(QLatin1String("edAddress"));

        gridLayout->addWidget(edAddress, 0, 1, 1, 1);

        label_2 = new QLabel(QueryCvDialog);
        label_2->setObjectName(QLatin1String("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        edCv = new QLineEdit(QueryCvDialog);
        edCv->setObjectName(QLatin1String("edCv"));

        gridLayout->addWidget(edCv, 1, 1, 1, 1);


        formLayout->setLayout(0, QFormLayout::LabelRole, gridLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QLatin1String("horizontalLayout"));
        btnOK = new QPushButton(QueryCvDialog);
        btnOK->setObjectName(QLatin1String("btnOK"));

        horizontalLayout->addWidget(btnOK);

        btnCancel = new QPushButton(QueryCvDialog);
        btnCancel->setObjectName(QLatin1String("btnCancel"));

        horizontalLayout->addWidget(btnCancel);


        formLayout->setLayout(2, QFormLayout::LabelRole, horizontalLayout);

        chkHex = new QCheckBox(QueryCvDialog);
        chkHex->setObjectName(QLatin1String("chkHex"));

        formLayout->setWidget(1, QFormLayout::LabelRole, chkHex);


        retranslateUi(QueryCvDialog);

        QMetaObject::connectSlotsByName(QueryCvDialog);
    } // setupUi

    void retranslateUi(QWidget *QueryCvDialog)
    {
        QueryCvDialog->setWindowTitle(QApplication::translate("QueryCvDialog", "Query Cv", nullptr));
        lblUnitAddr->setText(QApplication::translate("QueryCvDialog", "Address:", nullptr));
        label_2->setText(QApplication::translate("QueryCvDialog", "CV:", nullptr));
        btnOK->setText(QApplication::translate("QueryCvDialog", "OK", nullptr));
        btnCancel->setText(QApplication::translate("QueryCvDialog", "Cancel", nullptr));
        chkHex->setText(QApplication::translate("QueryCvDialog", "Display Hex", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QueryCvDialog: public Ui_QueryCvDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUERYCVDIALOG_H
