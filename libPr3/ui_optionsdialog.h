/********************************************************************************
** Form generated from reading UI file 'optionsdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONSDIALOG_H
#define UI_OPTIONSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_OptionsDialog
{
public:
    QLabel *label;
    QComboBox *comboBox;
    QPushButton *btnOK;
    QPushButton *btnCancel;

    void setupUi(QDialog *OptionsDialog)
    {
        if (OptionsDialog->objectName().isEmpty())
            OptionsDialog->setObjectName(QLatin1String("OptionsDialog"));
        OptionsDialog->resize(301, 149);
        label = new QLabel(OptionsDialog);
        label->setObjectName(QLatin1String("label"));
        label->setGeometry(QRect(20, 10, 331, 17));
        comboBox = new QComboBox(OptionsDialog);
        comboBox->setObjectName(QLatin1String("comboBox"));
        comboBox->setGeometry(QRect(20, 40, 271, 27));
        btnOK = new QPushButton(OptionsDialog);
        btnOK->setObjectName(QLatin1String("btnOK"));
        btnOK->setGeometry(QRect(20, 90, 99, 27));
        btnCancel = new QPushButton(OptionsDialog);
        btnCancel->setObjectName(QLatin1String("btnCancel"));
        btnCancel->setGeometry(QRect(130, 90, 99, 27));

        retranslateUi(OptionsDialog);

        QMetaObject::connectSlotsByName(OptionsDialog);
    } // setupUi

    void retranslateUi(QDialog *OptionsDialog)
    {
        OptionsDialog->setWindowTitle(QApplication::translate("OptionsDialog", "Dialog", nullptr));
        label->setText(QApplication::translate("OptionsDialog", "TextLabel", nullptr));
        btnOK->setText(QApplication::translate("OptionsDialog", "OK", nullptr));
        btnCancel->setText(QApplication::translate("OptionsDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OptionsDialog: public Ui_OptionsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONSDIALOG_H
