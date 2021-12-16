/********************************************************************************
** Form generated from reading UI file 'inputdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTDIALOG_H
#define UI_INPUTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_InputDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *InputDialog)
    {
        if (InputDialog->objectName().isEmpty())
            InputDialog->setObjectName(QLatin1String("InputDialog"));
        InputDialog->resize(202, 126);
        verticalLayout = new QVBoxLayout(InputDialog);
        verticalLayout->setObjectName(QLatin1String("verticalLayout"));
        label = new QLabel(InputDialog);
        label->setObjectName(QLatin1String("label"));

        verticalLayout->addWidget(label);

        lineEdit = new QLineEdit(InputDialog);
        lineEdit->setObjectName(QLatin1String("lineEdit"));

        verticalLayout->addWidget(lineEdit);

        comboBox = new QComboBox(InputDialog);
        comboBox->setObjectName(QLatin1String("comboBox"));

        verticalLayout->addWidget(comboBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QLatin1String("horizontalLayout"));
        okButton = new QPushButton(InputDialog);
        okButton->setObjectName(QLatin1String("okButton"));

        horizontalLayout->addWidget(okButton);

        cancelButton = new QPushButton(InputDialog);
        cancelButton->setObjectName(QLatin1String("cancelButton"));

        horizontalLayout->addWidget(cancelButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(InputDialog);

        QMetaObject::connectSlotsByName(InputDialog);
    } // setupUi

    void retranslateUi(QDialog *InputDialog)
    {
        InputDialog->setWindowTitle(QApplication::translate("InputDialog", "Dialog", nullptr));
        label->setText(QApplication::translate("InputDialog", "TextLabel", nullptr));
        okButton->setText(QApplication::translate("InputDialog", "OK", nullptr));
        cancelButton->setText(QApplication::translate("InputDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InputDialog: public Ui_InputDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTDIALOG_H
