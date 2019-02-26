/********************************************************************************
** Form generated from reading UI file 'sensortextedit.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
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
            SensorTextEdit->setObjectName(QLatin1String("SensorTextEdit"));
        SensorTextEdit->resize(334, 200);
        gridLayout = new QGridLayout(SensorTextEdit);
        gridLayout->setObjectName(QLatin1String("gridLayout"));
        labelName = new QLabel(SensorTextEdit);
        labelName->setObjectName(QLatin1String("labelName"));

        gridLayout->addWidget(labelName, 0, 0, 1, 1);

        nameText = new QLabel(SensorTextEdit);
        nameText->setObjectName(QLatin1String("nameText"));

        gridLayout->addWidget(nameText, 0, 1, 1, 1);

        textInact = new QLabel(SensorTextEdit);
        textInact->setObjectName(QLatin1String("textInact"));

        gridLayout->addWidget(textInact, 1, 0, 1, 1);

        inactTextField = new QLineEdit(SensorTextEdit);
        inactTextField->setObjectName(QLatin1String("inactTextField"));

        gridLayout->addWidget(inactTextField, 1, 1, 1, 1);

        textAct = new QLabel(SensorTextEdit);
        textAct->setObjectName(QLatin1String("textAct"));

        gridLayout->addWidget(textAct, 2, 0, 1, 1);

        actTextField = new QLineEdit(SensorTextEdit);
        actTextField->setObjectName(QLatin1String("actTextField"));

        gridLayout->addWidget(actTextField, 2, 1, 1, 1);

        textIncon = new QLabel(SensorTextEdit);
        textIncon->setObjectName(QLatin1String("textIncon"));

        gridLayout->addWidget(textIncon, 3, 0, 1, 1);

        inconTextField = new QLineEdit(SensorTextEdit);
        inconTextField->setObjectName(QLatin1String("inconTextField"));

        gridLayout->addWidget(inconTextField, 3, 1, 1, 1);

        textUnknown = new QLabel(SensorTextEdit);
        textUnknown->setObjectName(QLatin1String("textUnknown"));

        gridLayout->addWidget(textUnknown, 4, 0, 1, 1);

        unknownTextField = new QLineEdit(SensorTextEdit);
        unknownTextField->setObjectName(QLatin1String("unknownTextField"));

        gridLayout->addWidget(unknownTextField, 4, 1, 1, 1);

        cancelButton = new QPushButton(SensorTextEdit);
        cancelButton->setObjectName(QLatin1String("cancelButton"));

        gridLayout->addWidget(cancelButton, 5, 0, 1, 1);

        okButton = new QPushButton(SensorTextEdit);
        okButton->setObjectName(QLatin1String("okButton"));

        gridLayout->addWidget(okButton, 5, 1, 1, 1);


        retranslateUi(SensorTextEdit);

        QMetaObject::connectSlotsByName(SensorTextEdit);
    } // setupUi

    void retranslateUi(QDialog *SensorTextEdit)
    {
        SensorTextEdit->setWindowTitle(QApplication::translate("SensorTextEdit", "Set Text for Sensor States", nullptr));
        labelName->setText(QApplication::translate("SensorTextEdit", "Name:", nullptr));
        nameText->setText(QApplication::translate("SensorTextEdit", "xxxxx", nullptr));
        textInact->setText(QApplication::translate("SensorTextEdit", "Inactive = Inactive", nullptr));
        inactTextField->setText(QApplication::translate("SensorTextEdit", "Inactive", nullptr));
        textAct->setText(QApplication::translate("SensorTextEdit", "Active = Active", nullptr));
        actTextField->setText(QApplication::translate("SensorTextEdit", "Active", nullptr));
        textIncon->setText(QApplication::translate("SensorTextEdit", "Inconsistent - <inconsistent>", nullptr));
        inconTextField->setText(QApplication::translate("SensorTextEdit", "<inconsistent>", nullptr));
        textUnknown->setText(QApplication::translate("SensorTextEdit", "Unknown= <unknown>", nullptr));
        unknownTextField->setText(QApplication::translate("SensorTextEdit", "<unknown>", nullptr));
        cancelButton->setText(QApplication::translate("SensorTextEdit", "Cancel", nullptr));
        okButton->setText(QApplication::translate("SensorTextEdit", "Set", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SensorTextEdit: public Ui_SensorTextEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENSORTEXTEDIT_H
