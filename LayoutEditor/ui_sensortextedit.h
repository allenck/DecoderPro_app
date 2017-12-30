/********************************************************************************
** Form generated from reading UI file 'sensortextedit.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
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
        SensorTextEdit->setWindowTitle(QApplication::translate("SensorTextEdit", "Set Text for Sensor States", Q_NULLPTR));
        labelName->setText(QApplication::translate("SensorTextEdit", "Name:", Q_NULLPTR));
        nameText->setText(QApplication::translate("SensorTextEdit", "xxxxx", Q_NULLPTR));
        textInact->setText(QApplication::translate("SensorTextEdit", "Inactive = Inactive", Q_NULLPTR));
        inactTextField->setText(QApplication::translate("SensorTextEdit", "Inactive", Q_NULLPTR));
        textAct->setText(QApplication::translate("SensorTextEdit", "Active = Active", Q_NULLPTR));
        actTextField->setText(QApplication::translate("SensorTextEdit", "Active", Q_NULLPTR));
        textIncon->setText(QApplication::translate("SensorTextEdit", "Inconsistent - <inconsistent>", Q_NULLPTR));
        inconTextField->setText(QApplication::translate("SensorTextEdit", "<inconsistent>", Q_NULLPTR));
        textUnknown->setText(QApplication::translate("SensorTextEdit", "Unknown= <unknown>", Q_NULLPTR));
        unknownTextField->setText(QApplication::translate("SensorTextEdit", "<unknown>", Q_NULLPTR));
        cancelButton->setText(QApplication::translate("SensorTextEdit", "Cancel", Q_NULLPTR));
        okButton->setText(QApplication::translate("SensorTextEdit", "Set", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SensorTextEdit: public Ui_SensorTextEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENSORTEXTEDIT_H
