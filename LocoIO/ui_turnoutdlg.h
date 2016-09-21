/********************************************************************************
** Form generated from reading UI file 'turnoutdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TURNOUTDLG_H
#define UI_TURNOUTDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
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
            TurnoutDlg->setObjectName(QStringLiteral("TurnoutDlg"));
        TurnoutDlg->resize(373, 317);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TurnoutDlg->sizePolicy().hasHeightForWidth());
        TurnoutDlg->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(TurnoutDlg);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(TurnoutDlg);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        edV1 = new QLineEdit(TurnoutDlg);
        edV1->setObjectName(QStringLiteral("edV1"));
        edV1->setReadOnly(true);

        horizontalLayout->addWidget(edV1);

        label_2 = new QLabel(TurnoutDlg);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        edV2 = new QLineEdit(TurnoutDlg);
        edV2->setObjectName(QStringLiteral("edV2"));
        edV2->setReadOnly(true);

        horizontalLayout->addWidget(edV2);


        verticalLayout->addLayout(horizontalLayout);

        gbB1Mode = new QGroupBox(TurnoutDlg);
        gbB1Mode->setObjectName(QStringLiteral("gbB1Mode"));
        horizontalLayout_4 = new QHBoxLayout(gbB1Mode);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        rbB1Input = new QRadioButton(gbB1Mode);
        rbB1Input->setObjectName(QStringLiteral("rbB1Input"));

        horizontalLayout_4->addWidget(rbB1Input);

        rbB1Output = new QRadioButton(gbB1Mode);
        rbB1Output->setObjectName(QStringLiteral("rbB1Output"));

        horizontalLayout_4->addWidget(rbB1Output);


        verticalLayout->addWidget(gbB1Mode);

        chkDS54Aux = new QCheckBox(TurnoutDlg);
        chkDS54Aux->setObjectName(QStringLiteral("chkDS54Aux"));

        verticalLayout->addWidget(chkDS54Aux);

        chkClosedOn = new QCheckBox(TurnoutDlg);
        chkClosedOn->setObjectName(QStringLiteral("chkClosedOn"));

        verticalLayout->addWidget(chkClosedOn);

        chkOutputOn = new QCheckBox(TurnoutDlg);
        chkOutputOn->setObjectName(QStringLiteral("chkOutputOn"));

        verticalLayout->addWidget(chkOutputOn);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        lblAddr = new QLabel(TurnoutDlg);
        lblAddr->setObjectName(QStringLiteral("lblAddr"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lblAddr->sizePolicy().hasHeightForWidth());
        lblAddr->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(lblAddr);

        sbAddr = new QSpinBox(TurnoutDlg);
        sbAddr->setObjectName(QStringLiteral("sbAddr"));

        horizontalLayout_2->addWidget(sbAddr);


        verticalLayout->addLayout(horizontalLayout_2);

        chkInputHigh = new QCheckBox(TurnoutDlg);
        chkInputHigh->setObjectName(QStringLiteral("chkInputHigh"));

        verticalLayout->addWidget(chkInputHigh);

        lblHelp = new QLabel(TurnoutDlg);
        lblHelp->setObjectName(QStringLiteral("lblHelp"));

        verticalLayout->addWidget(lblHelp);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        btnCancel = new QPushButton(TurnoutDlg);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(btnCancel->sizePolicy().hasHeightForWidth());
        btnCancel->setSizePolicy(sizePolicy2);

        horizontalLayout_3->addWidget(btnCancel);

        btnOK = new QPushButton(TurnoutDlg);
        btnOK->setObjectName(QStringLiteral("btnOK"));
        sizePolicy2.setHeightForWidth(btnOK->sizePolicy().hasHeightForWidth());
        btnOK->setSizePolicy(sizePolicy2);

        horizontalLayout_3->addWidget(btnOK);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(TurnoutDlg);

        QMetaObject::connectSlotsByName(TurnoutDlg);
    } // setupUi

    void retranslateUi(QDialog *TurnoutDlg)
    {
        TurnoutDlg->setWindowTitle(QApplication::translate("TurnoutDlg", "Dialog", 0));
        label->setText(QApplication::translate("TurnoutDlg", "Val 1: ", 0));
        label_2->setText(QApplication::translate("TurnoutDlg", "Val 2:", 0));
        gbB1Mode->setTitle(QApplication::translate("TurnoutDlg", "B1 mode", 0));
        rbB1Input->setText(QApplication::translate("TurnoutDlg", "Input", 0));
        rbB1Output->setText(QApplication::translate("TurnoutDlg", "Output", 0));
        chkDS54Aux->setText(QApplication::translate("TurnoutDlg", "DS54 Aux Input", 0));
        chkClosedOn->setText(QApplication::translate("TurnoutDlg", "Closed ON", 0));
        chkOutputOn->setText(QApplication::translate("TurnoutDlg", "Output ON", 0));
        lblAddr->setText(QApplication::translate("TurnoutDlg", "Address:", 0));
        chkInputHigh->setText(QApplication::translate("TurnoutDlg", "Input High (> +6V)", 0));
        lblHelp->setText(QApplication::translate("TurnoutDlg", "TextLabel", 0));
        btnCancel->setText(QApplication::translate("TurnoutDlg", "Cancel", 0));
        btnOK->setText(QApplication::translate("TurnoutDlg", "OK", 0));
    } // retranslateUi

};

namespace Ui {
    class TurnoutDlg: public Ui_TurnoutDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TURNOUTDLG_H
