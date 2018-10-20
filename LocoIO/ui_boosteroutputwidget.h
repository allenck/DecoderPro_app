/********************************************************************************
** Form generated from reading UI file 'boosteroutputwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BOOSTEROUTPUTWIDGET_H
#define UI_BOOSTEROUTPUTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BoosterOutputWidget
{
public:
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_4;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_5;
    QLabel *label_8;
    QLabel *label;
    QLabel *label_2;
    QToolButton *tbPower;
    QLabel *label_3;
    QRadioButton *rb1On;
    QRadioButton *rb1Off;

    void setupUi(QWidget *BoosterOutputWidget)
    {
        if (BoosterOutputWidget->objectName().isEmpty())
            BoosterOutputWidget->setObjectName(QStringLiteral("BoosterOutputWidget"));
        BoosterOutputWidget->resize(27, 276);
        label_9 = new QLabel(BoosterOutputWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(10, 100, 16, 16));
        QFont font;
        font.setPointSize(7);
        label_9->setFont(font);
        label_10 = new QLabel(BoosterOutputWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(10, 270, 16, 16));
        label_10->setFont(font);
        label_4 = new QLabel(BoosterOutputWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(1, 125, 16, 16));
        label_4->setFont(font);
        label_6 = new QLabel(BoosterOutputWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(1, 137, 16, 16));
        label_6->setFont(font);
        label_7 = new QLabel(BoosterOutputWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(1, 149, 16, 16));
        label_7->setFont(font);
        label_5 = new QLabel(BoosterOutputWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(1, 161, 16, 16));
        label_5->setFont(font);
        label_8 = new QLabel(BoosterOutputWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(1, 173, 16, 16));
        label_8->setFont(font);
        label = new QLabel(BoosterOutputWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(1, 1, 16, 16));
        label->setFont(font);
        label_2 = new QLabel(BoosterOutputWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(1, 13, 16, 16));
        label_2->setFont(font);
        tbPower = new QToolButton(BoosterOutputWidget);
        tbPower->setObjectName(QStringLiteral("tbPower"));
        tbPower->setGeometry(QRect(1, 25, 25, 18));
        QFont font1;
        font1.setFamily(QStringLiteral("Ubuntu"));
        font1.setPointSize(7);
        tbPower->setFont(font1);
        label_3 = new QLabel(BoosterOutputWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(1, 45, 16, 16));
        label_3->setFont(font);
        rb1On = new QRadioButton(BoosterOutputWidget);
        rb1On->setObjectName(QStringLiteral("rb1On"));
        rb1On->setGeometry(QRect(1, 57, 16, 16));
        rb1Off = new QRadioButton(BoosterOutputWidget);
        rb1Off->setObjectName(QStringLiteral("rb1Off"));
        rb1Off->setGeometry(QRect(1, 74, 16, 16));

        retranslateUi(BoosterOutputWidget);

        QMetaObject::connectSlotsByName(BoosterOutputWidget);
    } // setupUi

    void retranslateUi(QWidget *BoosterOutputWidget)
    {
        BoosterOutputWidget->setWindowTitle(QApplication::translate("BoosterOutputWidget", "Form", Q_NULLPTR));
        label_9->setText(QString());
        label_10->setText(QString());
        label_4->setText(QString());
        label_6->setText(QString());
        label_7->setText(QString());
        label_5->setText(QString());
        label_8->setText(QString());
        label->setText(QString());
        label_2->setText(QString());
#ifndef QT_NO_TOOLTIP
        tbPower->setToolTip(QApplication::translate("BoosterOutputWidget", "<html><head/><body><p><span style=\" font-family:'sans-serif'; font-size:15px;\">The relays will NOT be switched on with a fixed contact output = ON if one or both feedback are not been available or an OPC_GPOFF (0x82) or OPC_IDLE (0x85) command is received</span></p><p><br/></p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        tbPower->setText(QApplication::translate("BoosterOutputWidget", "On", Q_NULLPTR));
        label_3->setText(QString());
#ifndef QT_NO_TOOLTIP
        rb1On->setToolTip(QApplication::translate("BoosterOutputWidget", "<html><head/><body><p>Push button on at power up <span style=\" font-family:'sans-serif'; font-size:15px;\">and when receiving an input signal, will switch on the output.</span></p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        rb1On->setText(QString());
#ifndef QT_NO_TOOLTIP
        rb1Off->setToolTip(QApplication::translate("BoosterOutputWidget", "<html><head/><body><p>Push button off at power up. Booster will have to be switched on by a command.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        rb1Off->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class BoosterOutputWidget: public Ui_BoosterOutputWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOOSTEROUTPUTWIDGET_H
