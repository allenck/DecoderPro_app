/********************************************************************************
** Form generated from reading UI file 'boosterbuttons.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BOOSTERBUTTONS_H
#define UI_BOOSTERBUTTONS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BoosterButtons
{
public:
    QPushButton *goPushButton;
    QPushButton *stopPushButton;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *BoosterButtons)
    {
        if (BoosterButtons->objectName().isEmpty())
            BoosterButtons->setObjectName(QString::fromUtf8("BoosterButtons"));
        BoosterButtons->resize(175, 300);
        goPushButton = new QPushButton(BoosterButtons);
        goPushButton->setObjectName(QString::fromUtf8("goPushButton"));
        goPushButton->setGeometry(QRect(10, 60, 89, 25));
        goPushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(138, 226, 52);"));
        stopPushButton = new QPushButton(BoosterButtons);
        stopPushButton->setObjectName(QString::fromUtf8("stopPushButton"));
        stopPushButton->setGeometry(QRect(10, 100, 89, 25));
        stopPushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(164, 0, 0);"));
        label = new QLabel(BoosterButtons);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 67, 17));
        label_2 = new QLabel(BoosterButtons);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 150, 67, 17));

        retranslateUi(BoosterButtons);

        QMetaObject::connectSlotsByName(BoosterButtons);
    } // setupUi

    void retranslateUi(QWidget *BoosterButtons)
    {
        BoosterButtons->setWindowTitle(QCoreApplication::translate("BoosterButtons", "Form", nullptr));
        goPushButton->setText(QCoreApplication::translate("BoosterButtons", "GO", nullptr));
        stopPushButton->setText(QCoreApplication::translate("BoosterButtons", "STOP", nullptr));
        label->setText(QString());
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class BoosterButtons: public Ui_BoosterButtons {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOOSTERBUTTONS_H
