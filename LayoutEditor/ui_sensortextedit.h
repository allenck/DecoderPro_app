/********************************************************************************
** Form generated from reading UI file 'sensortextedit.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SENSORTEXTEDIT_H
#define UI_SENSORTEXTEDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SensorTextEdit
{
public:
    QGridLayout *gridLayout;
    QLabel *labelName;
    QLabel *nameText;
    QLabel *textInact;
    QLineEdit *inactTextField;
    QLabel *textAct;
    QLineEdit *actTextField;
    QLabel *textIncon;
    QLineEdit *inconTextField;
    QLabel *textUnknown;
    QLineEdit *unknownTextField;
    QPushButton *cancelButton;
    QPushButton *okButton;

    void setupUi(QDialog *SensorTextEdit)
    {
        if (SensorTextEdit->objectName().isEmpty())
            SensorTextEdit->setObjectName(QString::fromUtf8("SensorTextEdit"));
        SensorTextEdit->resize(334, 200);
        gridLayout = new QGridLayout(SensorTextEdit);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        labelName = new QLabel(SensorTextEdit);
        labelName->setObjectName(QString::fromUtf8("labelName"));

        gridLayout->addWidget(labelName, 0, 0, 1, 1);

        nameText = new QLabel(SensorTextEdit);
        nameText->setObjectName(QString::fromUtf8("nameText"));

        gridLayout->addWidget(nameText, 0, 1, 1, 1);

        textInact = new QLabel(SensorTextEdit);
        textInact->setObjectName(QString::fromUtf8("textInact"));

        gridLayout->addWidget(textInact, 1, 0, 1, 1);

        inactTextField = new QLineEdit(SensorTextEdit);
        inactTextField->setObjectName(QString::fromUtf8("inactTextField"));

        gridLayout->addWidget(inactTextField, 1, 1, 1, 1);

        textAct = new QLabel(SensorTextEdit);
        textAct->setObjectName(QString::fromUtf8("textAct"));

        gridLayout->addWidget(textAct, 2, 0, 1, 1);

        actTextField = new QLineEdit(SensorTextEdit);
        actTextField->setObjectName(QString::fromUtf8("actTextField"));

        gridLayout->addWidget(actTextField, 2, 1, 1, 1);

        textIncon = new QLabel(SensorTextEdit);
        textIncon->setObjectName(QString::fromUtf8("textIncon"));

        gridLayout->addWidget(textIncon, 3, 0, 1, 1);

        inconTextField = new QLineEdit(SensorTextEdit);
        inconTextField->setObjectName(QString::fromUtf8("inconTextField"));

        gridLayout->addWidget(inconTextField, 3, 1, 1, 1);

        textUnknown = new QLabel(SensorTextEdit);
        textUnknown->setObjectName(QString::fromUtf8("textUnknown"));

        gridLayout->addWidget(textUnknown, 4, 0, 1, 1);

        unknownTextField = new QLineEdit(SensorTextEdit);
        unknownTextField->setObjectName(QString::fromUtf8("unknownTextField"));

        gridLayout->addWidget(unknownTextField, 4, 1, 1, 1);

        cancelButton = new QPushButton(SensorTextEdit);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        gridLayout->addWidget(cancelButton, 5, 0, 1, 1);

        okButton = new QPushButton(SensorTextEdit);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        gridLayout->addWidget(okButton, 5, 1, 1, 1);


        retranslateUi(SensorTextEdit);

        QMetaObject::connectSlotsByName(SensorTextEdit);
    } // setupUi

    void retranslateUi(QDialog *SensorTextEdit)
    {
        SensorTextEdit->setWindowTitle(QCoreApplication::translate("SensorTextEdit", "Set Text for Sensor States", nullptr));
        labelName->setText(QCoreApplication::translate("SensorTextEdit", "Name:", nullptr));
        nameText->setText(QCoreApplication::translate("SensorTextEdit", "xxxxx", nullptr));
        textInact->setText(QCoreApplication::translate("SensorTextEdit", "Inactive = Inactive", nullptr));
        inactTextField->setText(QCoreApplication::translate("SensorTextEdit", "Inactive", nullptr));
        textAct->setText(QCoreApplication::translate("SensorTextEdit", "Active = Active", nullptr));
        actTextField->setText(QCoreApplication::translate("SensorTextEdit", "Active", nullptr));
        textIncon->setText(QCoreApplication::translate("SensorTextEdit", "Inconsistent - <inconsistent>", nullptr));
        inconTextField->setText(QCoreApplication::translate("SensorTextEdit", "<inconsistent>", nullptr));
        textUnknown->setText(QCoreApplication::translate("SensorTextEdit", "Unknown= <unknown>", nullptr));
        unknownTextField->setText(QCoreApplication::translate("SensorTextEdit", "<unknown>", nullptr));
        cancelButton->setText(QCoreApplication::translate("SensorTextEdit", "Cancel", nullptr));
        okButton->setText(QCoreApplication::translate("SensorTextEdit", "Set", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SensorTextEdit: public Ui_SensorTextEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENSORTEXTEDIT_H
