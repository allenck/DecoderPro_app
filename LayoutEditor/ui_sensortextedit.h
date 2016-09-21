/********************************************************************************
** Form generated from reading UI file 'sensortextedit.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SENSORTEXTEDIT_H
#define UI_SENSORTEXTEDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
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
            SensorTextEdit->setObjectName(QStringLiteral("SensorTextEdit"));
        SensorTextEdit->resize(334, 200);
        gridLayout = new QGridLayout(SensorTextEdit);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        labelName = new QLabel(SensorTextEdit);
        labelName->setObjectName(QStringLiteral("labelName"));

        gridLayout->addWidget(labelName, 0, 0, 1, 1);

        nameText = new QLabel(SensorTextEdit);
        nameText->setObjectName(QStringLiteral("nameText"));

        gridLayout->addWidget(nameText, 0, 1, 1, 1);

        textInact = new QLabel(SensorTextEdit);
        textInact->setObjectName(QStringLiteral("textInact"));

        gridLayout->addWidget(textInact, 1, 0, 1, 1);

        inactTextField = new QLineEdit(SensorTextEdit);
        inactTextField->setObjectName(QStringLiteral("inactTextField"));

        gridLayout->addWidget(inactTextField, 1, 1, 1, 1);

        textAct = new QLabel(SensorTextEdit);
        textAct->setObjectName(QStringLiteral("textAct"));

        gridLayout->addWidget(textAct, 2, 0, 1, 1);

        actTextField = new QLineEdit(SensorTextEdit);
        actTextField->setObjectName(QStringLiteral("actTextField"));

        gridLayout->addWidget(actTextField, 2, 1, 1, 1);

        textIncon = new QLabel(SensorTextEdit);
        textIncon->setObjectName(QStringLiteral("textIncon"));

        gridLayout->addWidget(textIncon, 3, 0, 1, 1);

        inconTextField = new QLineEdit(SensorTextEdit);
        inconTextField->setObjectName(QStringLiteral("inconTextField"));

        gridLayout->addWidget(inconTextField, 3, 1, 1, 1);

        textUnknown = new QLabel(SensorTextEdit);
        textUnknown->setObjectName(QStringLiteral("textUnknown"));

        gridLayout->addWidget(textUnknown, 4, 0, 1, 1);

        unknownTextField = new QLineEdit(SensorTextEdit);
        unknownTextField->setObjectName(QStringLiteral("unknownTextField"));

        gridLayout->addWidget(unknownTextField, 4, 1, 1, 1);

        cancelButton = new QPushButton(SensorTextEdit);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        gridLayout->addWidget(cancelButton, 5, 0, 1, 1);

        okButton = new QPushButton(SensorTextEdit);
        okButton->setObjectName(QStringLiteral("okButton"));

        gridLayout->addWidget(okButton, 5, 1, 1, 1);


        retranslateUi(SensorTextEdit);

        QMetaObject::connectSlotsByName(SensorTextEdit);
    } // setupUi

    void retranslateUi(QDialog *SensorTextEdit)
    {
        SensorTextEdit->setWindowTitle(QApplication::translate("SensorTextEdit", "Set Text for Sensor States", 0));
        labelName->setText(QApplication::translate("SensorTextEdit", "Name:", 0));
        nameText->setText(QApplication::translate("SensorTextEdit", "xxxxx", 0));
        textInact->setText(QApplication::translate("SensorTextEdit", "Inactive = Inactive", 0));
        inactTextField->setText(QApplication::translate("SensorTextEdit", "Inactive", 0));
        textAct->setText(QApplication::translate("SensorTextEdit", "Active = Active", 0));
        actTextField->setText(QApplication::translate("SensorTextEdit", "Active", 0));
        textIncon->setText(QApplication::translate("SensorTextEdit", "Inconsistent - <inconsistent>", 0));
        inconTextField->setText(QApplication::translate("SensorTextEdit", "<inconsistent>", 0));
        textUnknown->setText(QApplication::translate("SensorTextEdit", "Unknown= <unknown>", 0));
        unknownTextField->setText(QApplication::translate("SensorTextEdit", "<unknown>", 0));
        cancelButton->setText(QApplication::translate("SensorTextEdit", "Cancel", 0));
        okButton->setText(QApplication::translate("SensorTextEdit", "Set", 0));
    } // retranslateUi

};

namespace Ui {
    class SensorTextEdit: public Ui_SensorTextEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENSORTEXTEDIT_H
