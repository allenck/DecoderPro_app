/********************************************************************************
** Form generated from reading UI file 'turnoutdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TURNOUTDLG_H
#define UI_TURNOUTDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TurnoutDlg
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *edV1;
    QLabel *label_2;
    QLineEdit *edV2;
    QGroupBox *gbB1Mode;
    QHBoxLayout *horizontalLayout_4;
    QRadioButton *rbB1Input;
    QRadioButton *rbB1Output;
    QCheckBox *chkDS54Aux;
    QCheckBox *chkClosedOn;
    QCheckBox *chkOutputOn;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lblAddr;
    QSpinBox *sbAddr;
    QCheckBox *chkInputHigh;
    QLabel *lblHelp;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btnCancel;
    QPushButton *btnOK;

    void setupUi(QDialog *TurnoutDlg)
    {
        if (TurnoutDlg->objectName().isEmpty())
            TurnoutDlg->setObjectName(QString::fromUtf8("TurnoutDlg"));
        TurnoutDlg->resize(373, 317);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TurnoutDlg->sizePolicy().hasHeightForWidth());
        TurnoutDlg->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(TurnoutDlg);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(TurnoutDlg);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        edV1 = new QLineEdit(TurnoutDlg);
        edV1->setObjectName(QString::fromUtf8("edV1"));
        edV1->setReadOnly(true);

        horizontalLayout->addWidget(edV1);

        label_2 = new QLabel(TurnoutDlg);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        edV2 = new QLineEdit(TurnoutDlg);
        edV2->setObjectName(QString::fromUtf8("edV2"));
        edV2->setReadOnly(true);

        horizontalLayout->addWidget(edV2);


        verticalLayout->addLayout(horizontalLayout);

        gbB1Mode = new QGroupBox(TurnoutDlg);
        gbB1Mode->setObjectName(QString::fromUtf8("gbB1Mode"));
        horizontalLayout_4 = new QHBoxLayout(gbB1Mode);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        rbB1Input = new QRadioButton(gbB1Mode);
        rbB1Input->setObjectName(QString::fromUtf8("rbB1Input"));

        horizontalLayout_4->addWidget(rbB1Input);

        rbB1Output = new QRadioButton(gbB1Mode);
        rbB1Output->setObjectName(QString::fromUtf8("rbB1Output"));

        horizontalLayout_4->addWidget(rbB1Output);


        verticalLayout->addWidget(gbB1Mode);

        chkDS54Aux = new QCheckBox(TurnoutDlg);
        chkDS54Aux->setObjectName(QString::fromUtf8("chkDS54Aux"));

        verticalLayout->addWidget(chkDS54Aux);

        chkClosedOn = new QCheckBox(TurnoutDlg);
        chkClosedOn->setObjectName(QString::fromUtf8("chkClosedOn"));

        verticalLayout->addWidget(chkClosedOn);

        chkOutputOn = new QCheckBox(TurnoutDlg);
        chkOutputOn->setObjectName(QString::fromUtf8("chkOutputOn"));

        verticalLayout->addWidget(chkOutputOn);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lblAddr = new QLabel(TurnoutDlg);
        lblAddr->setObjectName(QString::fromUtf8("lblAddr"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lblAddr->sizePolicy().hasHeightForWidth());
        lblAddr->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(lblAddr);

        sbAddr = new QSpinBox(TurnoutDlg);
        sbAddr->setObjectName(QString::fromUtf8("sbAddr"));

        horizontalLayout_2->addWidget(sbAddr);


        verticalLayout->addLayout(horizontalLayout_2);

        chkInputHigh = new QCheckBox(TurnoutDlg);
        chkInputHigh->setObjectName(QString::fromUtf8("chkInputHigh"));

        verticalLayout->addWidget(chkInputHigh);

        lblHelp = new QLabel(TurnoutDlg);
        lblHelp->setObjectName(QString::fromUtf8("lblHelp"));

        verticalLayout->addWidget(lblHelp);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        btnCancel = new QPushButton(TurnoutDlg);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(btnCancel->sizePolicy().hasHeightForWidth());
        btnCancel->setSizePolicy(sizePolicy2);

        horizontalLayout_3->addWidget(btnCancel);

        btnOK = new QPushButton(TurnoutDlg);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));
        sizePolicy2.setHeightForWidth(btnOK->sizePolicy().hasHeightForWidth());
        btnOK->setSizePolicy(sizePolicy2);

        horizontalLayout_3->addWidget(btnOK);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(TurnoutDlg);

        QMetaObject::connectSlotsByName(TurnoutDlg);
    } // setupUi

    void retranslateUi(QDialog *TurnoutDlg)
    {
        TurnoutDlg->setWindowTitle(QCoreApplication::translate("TurnoutDlg", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("TurnoutDlg", "Val 1: ", nullptr));
        label_2->setText(QCoreApplication::translate("TurnoutDlg", "Val 2:", nullptr));
        gbB1Mode->setTitle(QCoreApplication::translate("TurnoutDlg", "B1 mode", nullptr));
        rbB1Input->setText(QCoreApplication::translate("TurnoutDlg", "Input", nullptr));
        rbB1Output->setText(QCoreApplication::translate("TurnoutDlg", "Output", nullptr));
        chkDS54Aux->setText(QCoreApplication::translate("TurnoutDlg", "DS54 Aux Input", nullptr));
        chkClosedOn->setText(QCoreApplication::translate("TurnoutDlg", "Closed ON", nullptr));
        chkOutputOn->setText(QCoreApplication::translate("TurnoutDlg", "Output ON", nullptr));
        lblAddr->setText(QCoreApplication::translate("TurnoutDlg", "Address:", nullptr));
        chkInputHigh->setText(QCoreApplication::translate("TurnoutDlg", "Input High (> +6V)", nullptr));
        lblHelp->setText(QCoreApplication::translate("TurnoutDlg", "TextLabel", nullptr));
        btnCancel->setText(QCoreApplication::translate("TurnoutDlg", "Cancel", nullptr));
        btnOK->setText(QCoreApplication::translate("TurnoutDlg", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TurnoutDlg: public Ui_TurnoutDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TURNOUTDLG_H
