/********************************************************************************
** Form generated from reading UI file 'inputangledlg.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTANGLEDLG_H
#define UI_INPUTANGLEDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
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
            inputAngleDlg->setObjectName(QStringLiteral("inputAngleDlg"));
        inputAngleDlg->resize(217, 108);
        formLayout = new QFormLayout(inputAngleDlg);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        textX = new QLabel(inputAngleDlg);
        textX->setObjectName(QStringLiteral("textX"));

        formLayout->setWidget(0, QFormLayout::LabelRole, textX);

        spinX = new QSpinBox(inputAngleDlg);
        spinX->setObjectName(QStringLiteral("spinX"));
        spinX->setMinimum(-359);
        spinX->setMaximum(359);

        formLayout->setWidget(1, QFormLayout::LabelRole, spinX);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        okButton = new QPushButton(inputAngleDlg);
        okButton->setObjectName(QStringLiteral("okButton"));

        horizontalLayout->addWidget(okButton);

        cancelButton = new QPushButton(inputAngleDlg);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        horizontalLayout->addWidget(cancelButton);


        formLayout->setLayout(2, QFormLayout::LabelRole, horizontalLayout);


        retranslateUi(inputAngleDlg);

        QMetaObject::connectSlotsByName(inputAngleDlg);
    } // setupUi

    void retranslateUi(QDialog *inputAngleDlg)
    {
        inputAngleDlg->setWindowTitle(QApplication::translate("inputAngleDlg", "Enter Angle", Q_NULLPTR));
        textX->setText(QApplication::translate("inputAngleDlg", "TextLabel", Q_NULLPTR));
        okButton->setText(QApplication::translate("inputAngleDlg", "OK", Q_NULLPTR));
        cancelButton->setText(QApplication::translate("inputAngleDlg", "Cancel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class inputAngleDlg: public Ui_inputAngleDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTANGLEDLG_H
