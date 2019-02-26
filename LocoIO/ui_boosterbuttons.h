/********************************************************************************
** Form generated from reading UI file 'boosterbuttons.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
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
            BoosterButtons->setObjectName(QLatin1String("BoosterButtons"));
        BoosterButtons->resize(175, 300);
        goPushButton = new QPushButton(BoosterButtons);
        goPushButton->setObjectName(QLatin1String("goPushButton"));
        goPushButton->setGeometry(QRect(10, 60, 89, 25));
        goPushButton->setStyleSheet(QLatin1String("background-color: rgb(138, 226, 52);"));
        stopPushButton = new QPushButton(BoosterButtons);
        stopPushButton->setObjectName(QLatin1String("stopPushButton"));
        stopPushButton->setGeometry(QRect(10, 100, 89, 25));
        stopPushButton->setStyleSheet(QLatin1String("background-color: rgb(164, 0, 0);"));
        label = new QLabel(BoosterButtons);
        label->setObjectName(QLatin1String("label"));
        label->setGeometry(QRect(20, 20, 67, 17));
        label_2 = new QLabel(BoosterButtons);
        label_2->setObjectName(QLatin1String("label_2"));
        label_2->setGeometry(QRect(20, 150, 67, 17));

        retranslateUi(BoosterButtons);

        QMetaObject::connectSlotsByName(BoosterButtons);
    } // setupUi

    void retranslateUi(QWidget *BoosterButtons)
    {
        BoosterButtons->setWindowTitle(QApplication::translate("BoosterButtons", "Form", nullptr));
        goPushButton->setText(QApplication::translate("BoosterButtons", "GO", nullptr));
        stopPushButton->setText(QApplication::translate("BoosterButtons", "STOP", nullptr));
        label->setText(QString());
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class BoosterButtons: public Ui_BoosterButtons {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOOSTERBUTTONS_H
