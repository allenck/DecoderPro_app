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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BoosterOutputWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QToolButton *tbPower;
    QLabel *label_3;
    QRadioButton *rb1On;
    QRadioButton *rb1Off;
    QRadioButton *rb2On;
    QRadioButton *rb2Off;
    QLabel *label_4;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_5;
    QLabel *label_8;

    void setupUi(QWidget *BoosterOutputWidget)
    {
        if (BoosterOutputWidget->objectName().isEmpty())
            BoosterOutputWidget->setObjectName(QStringLiteral("BoosterOutputWidget"));
        BoosterOutputWidget->resize(23, 276);
        verticalLayout_2 = new QVBoxLayout(BoosterOutputWidget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(BoosterOutputWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(7);
        label->setFont(font);

        verticalLayout->addWidget(label);

        label_2 = new QLabel(BoosterOutputWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);

        verticalLayout->addWidget(label_2);

        tbPower = new QToolButton(BoosterOutputWidget);
        tbPower->setObjectName(QStringLiteral("tbPower"));
        QFont font1;
        font1.setFamily(QStringLiteral("Ubuntu"));
        font1.setPointSize(7);
        tbPower->setFont(font1);

        verticalLayout->addWidget(tbPower);

        label_3 = new QLabel(BoosterOutputWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font);

        verticalLayout->addWidget(label_3);

        rb1On = new QRadioButton(BoosterOutputWidget);
        rb1On->setObjectName(QStringLiteral("rb1On"));

        verticalLayout->addWidget(rb1On);

        rb1Off = new QRadioButton(BoosterOutputWidget);
        rb1Off->setObjectName(QStringLiteral("rb1Off"));

        verticalLayout->addWidget(rb1Off);

        rb2On = new QRadioButton(BoosterOutputWidget);
        rb2On->setObjectName(QStringLiteral("rb2On"));

        verticalLayout->addWidget(rb2On);

        rb2Off = new QRadioButton(BoosterOutputWidget);
        rb2Off->setObjectName(QStringLiteral("rb2Off"));

        verticalLayout->addWidget(rb2Off);

        label_4 = new QLabel(BoosterOutputWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font);

        verticalLayout->addWidget(label_4);

        label_6 = new QLabel(BoosterOutputWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setFont(font);

        verticalLayout->addWidget(label_6);

        label_7 = new QLabel(BoosterOutputWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setFont(font);

        verticalLayout->addWidget(label_7);

        label_5 = new QLabel(BoosterOutputWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font);

        verticalLayout->addWidget(label_5);

        label_8 = new QLabel(BoosterOutputWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setFont(font);

        verticalLayout->addWidget(label_8);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(BoosterOutputWidget);

        QMetaObject::connectSlotsByName(BoosterOutputWidget);
    } // setupUi

    void retranslateUi(QWidget *BoosterOutputWidget)
    {
        BoosterOutputWidget->setWindowTitle(QApplication::translate("BoosterOutputWidget", "Form", Q_NULLPTR));
        label->setText(QString());
        label_2->setText(QString());
        tbPower->setText(QApplication::translate("BoosterOutputWidget", "On", Q_NULLPTR));
        label_3->setText(QString());
#ifndef QT_NO_TOOLTIP
        rb1On->setToolTip(QApplication::translate("BoosterOutputWidget", "<html><head/><body><p>Push button on at power up.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        rb1On->setText(QString());
#ifndef QT_NO_TOOLTIP
        rb1Off->setToolTip(QApplication::translate("BoosterOutputWidget", "<html><head/><body><p>Push button off at power up.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        rb1Off->setText(QString());
#ifndef QT_NO_TOOLTIP
        rb2On->setToolTip(QApplication::translate("BoosterOutputWidget", "<html><head/><body><p>Second output on at power up.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        rb2On->setText(QString());
#ifndef QT_NO_TOOLTIP
        rb2Off->setToolTip(QApplication::translate("BoosterOutputWidget", "<html><head/><body><p>Second output off at power up. </p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        rb2Off->setText(QString());
        label_4->setText(QString());
        label_6->setText(QString());
        label_7->setText(QString());
        label_5->setText(QString());
        label_8->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class BoosterOutputWidget: public Ui_BoosterOutputWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOOSTEROUTPUTWIDGET_H
