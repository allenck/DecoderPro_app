/********************************************************************************
** Form generated from reading UI file 'inputangledlg.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTANGLEDLG_H
#define UI_INPUTANGLEDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_inputAngleDlg
{
public:
    QFormLayout *formLayout;
    QLabel *textX;
    QSpinBox *spinX;
    QHBoxLayout *horizontalLayout;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *inputAngleDlg)
    {
        if (inputAngleDlg->objectName().isEmpty())
            inputAngleDlg->setObjectName(QString::fromUtf8("inputAngleDlg"));
        inputAngleDlg->resize(215, 108);
        formLayout = new QFormLayout(inputAngleDlg);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        textX = new QLabel(inputAngleDlg);
        textX->setObjectName(QString::fromUtf8("textX"));

        formLayout->setWidget(0, QFormLayout::LabelRole, textX);

        spinX = new QSpinBox(inputAngleDlg);
        spinX->setObjectName(QString::fromUtf8("spinX"));
        spinX->setMinimum(-359);
        spinX->setMaximum(359);

        formLayout->setWidget(1, QFormLayout::LabelRole, spinX);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        okButton = new QPushButton(inputAngleDlg);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        horizontalLayout->addWidget(okButton);

        cancelButton = new QPushButton(inputAngleDlg);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        horizontalLayout->addWidget(cancelButton);


        formLayout->setLayout(2, QFormLayout::LabelRole, horizontalLayout);


        retranslateUi(inputAngleDlg);

        QMetaObject::connectSlotsByName(inputAngleDlg);
    } // setupUi

    void retranslateUi(QDialog *inputAngleDlg)
    {
        inputAngleDlg->setWindowTitle(QCoreApplication::translate("inputAngleDlg", "Enter Angle", nullptr));
        textX->setText(QCoreApplication::translate("inputAngleDlg", "TextLabel", nullptr));
        okButton->setText(QCoreApplication::translate("inputAngleDlg", "OK", nullptr));
        cancelButton->setText(QCoreApplication::translate("inputAngleDlg", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class inputAngleDlg: public Ui_inputAngleDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTANGLEDLG_H
