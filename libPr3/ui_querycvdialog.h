/********************************************************************************
** Form generated from reading UI file 'querycvdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUERYCVDIALOG_H
#define UI_QUERYCVDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
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
            QueryCvDialog->setObjectName(QStringLiteral("QueryCvDialog"));
        QueryCvDialog->resize(276, 143);
        formLayout = new QFormLayout(QueryCvDialog);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lblUnitAddr = new QLabel(QueryCvDialog);
        lblUnitAddr->setObjectName(QStringLiteral("lblUnitAddr"));

        gridLayout->addWidget(lblUnitAddr, 0, 0, 1, 1);

        edAddress = new QLineEdit(QueryCvDialog);
        edAddress->setObjectName(QStringLiteral("edAddress"));

        gridLayout->addWidget(edAddress, 0, 1, 1, 1);

        label_2 = new QLabel(QueryCvDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        edCv = new QLineEdit(QueryCvDialog);
        edCv->setObjectName(QStringLiteral("edCv"));

        gridLayout->addWidget(edCv, 1, 1, 1, 1);


        formLayout->setLayout(0, QFormLayout::LabelRole, gridLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        btnOK = new QPushButton(QueryCvDialog);
        btnOK->setObjectName(QStringLiteral("btnOK"));

        horizontalLayout->addWidget(btnOK);

        btnCancel = new QPushButton(QueryCvDialog);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));

        horizontalLayout->addWidget(btnCancel);


        formLayout->setLayout(2, QFormLayout::LabelRole, horizontalLayout);

        chkHex = new QCheckBox(QueryCvDialog);
        chkHex->setObjectName(QStringLiteral("chkHex"));

        formLayout->setWidget(1, QFormLayout::LabelRole, chkHex);


        retranslateUi(QueryCvDialog);

        QMetaObject::connectSlotsByName(QueryCvDialog);
    } // setupUi

    void retranslateUi(QWidget *QueryCvDialog)
    {
        QueryCvDialog->setWindowTitle(QApplication::translate("QueryCvDialog", "Query Cv", 0));
        lblUnitAddr->setText(QApplication::translate("QueryCvDialog", "Address:", 0));
        label_2->setText(QApplication::translate("QueryCvDialog", "CV:", 0));
        btnOK->setText(QApplication::translate("QueryCvDialog", "OK", 0));
        btnCancel->setText(QApplication::translate("QueryCvDialog", "Cancel", 0));
        chkHex->setText(QApplication::translate("QueryCvDialog", "Display Hex", 0));
    } // retranslateUi

};

namespace Ui {
    class QueryCvDialog: public Ui_QueryCvDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUERYCVDIALOG_H
