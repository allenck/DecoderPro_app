/********************************************************************************
** Form generated from reading UI file 'inputangledlg.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
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
            inputAngleDlg->setObjectName(QLatin1String("inputAngleDlg"));
        inputAngleDlg->resize(215, 108);
        formLayout = new QFormLayout(inputAngleDlg);
        formLayout->setObjectName(QLatin1String("formLayout"));
        textX = new QLabel(inputAngleDlg);
        textX->setObjectName(QLatin1String("textX"));

        formLayout->setWidget(0, QFormLayout::LabelRole, textX);

        spinX = new QSpinBox(inputAngleDlg);
        spinX->setObjectName(QLatin1String("spinX"));
        spinX->setMinimum(-359);
        spinX->setMaximum(359);

        formLayout->setWidget(1, QFormLayout::LabelRole, spinX);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QLatin1String("horizontalLayout"));
        okButton = new QPushButton(inputAngleDlg);
        okButton->setObjectName(QLatin1String("okButton"));

        horizontalLayout->addWidget(okButton);

        cancelButton = new QPushButton(inputAngleDlg);
        cancelButton->setObjectName(QLatin1String("cancelButton"));

        horizontalLayout->addWidget(cancelButton);


        formLayout->setLayout(2, QFormLayout::LabelRole, horizontalLayout);


        retranslateUi(inputAngleDlg);

        QMetaObject::connectSlotsByName(inputAngleDlg);
    } // setupUi

    void retranslateUi(QDialog *inputAngleDlg)
    {
        inputAngleDlg->setWindowTitle(QApplication::translate("inputAngleDlg", "Enter Angle", nullptr));
        textX->setText(QApplication::translate("inputAngleDlg", "TextLabel", nullptr));
        okButton->setText(QApplication::translate("inputAngleDlg", "OK", nullptr));
        cancelButton->setText(QApplication::translate("inputAngleDlg", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class inputAngleDlg: public Ui_inputAngleDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTANGLEDLG_H
