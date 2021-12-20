/********************************************************************************
** Form generated from reading UI file 'boosterpanel.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BOOSTERPANEL_H
#define UI_BOOSTERPANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BoosterPanel
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label_10;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_11;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *lblBoosterStatus;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_9;
    QLabel *label_8;

    void setupUi(QWidget *BoosterPanel)
    {
        if (BoosterPanel->objectName().isEmpty())
            BoosterPanel->setObjectName(QLatin1String("BoosterPanel"));
        BoosterPanel->resize(147, 244);
        QFont font;
        font.setPointSize(7);
        BoosterPanel->setFont(font);
        verticalLayout = new QVBoxLayout(BoosterPanel);
        verticalLayout->setObjectName(QLatin1String("verticalLayout"));
        label_10 = new QLabel(BoosterPanel);
        label_10->setObjectName(QLatin1String("label_10"));
        label_10->setFont(font);

        verticalLayout->addWidget(label_10);

        label = new QLabel(BoosterPanel);
        label->setObjectName(QLatin1String("label"));

        verticalLayout->addWidget(label);

        label_2 = new QLabel(BoosterPanel);
        label_2->setObjectName(QLatin1String("label_2"));

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(BoosterPanel);
        label_3->setObjectName(QLatin1String("label_3"));

        verticalLayout->addWidget(label_3);

        label_11 = new QLabel(BoosterPanel);
        label_11->setObjectName(QLatin1String("label_11"));
        label_11->setFont(font);

        verticalLayout->addWidget(label_11);

        label_4 = new QLabel(BoosterPanel);
        label_4->setObjectName(QLatin1String("label_4"));
        label_4->setFont(font);

        verticalLayout->addWidget(label_4);

        label_5 = new QLabel(BoosterPanel);
        label_5->setObjectName(QLatin1String("label_5"));
        label_5->setFont(font);

        verticalLayout->addWidget(label_5);

        lblBoosterStatus = new QLabel(BoosterPanel);
        lblBoosterStatus->setObjectName(QLatin1String("lblBoosterStatus"));
        lblBoosterStatus->setFont(font);
        lblBoosterStatus->setStyleSheet(QLatin1String("QLabel { color:green}"));

        verticalLayout->addWidget(lblBoosterStatus);

        label_6 = new QLabel(BoosterPanel);
        label_6->setObjectName(QLatin1String("label_6"));
        label_6->setFont(font);

        verticalLayout->addWidget(label_6);

        label_7 = new QLabel(BoosterPanel);
        label_7->setObjectName(QLatin1String("label_7"));
        label_7->setFont(font);

        verticalLayout->addWidget(label_7);

        label_9 = new QLabel(BoosterPanel);
        label_9->setObjectName(QLatin1String("label_9"));
        label_9->setFont(font);

        verticalLayout->addWidget(label_9);

        label_8 = new QLabel(BoosterPanel);
        label_8->setObjectName(QLatin1String("label_8"));
        label_8->setFont(font);

        verticalLayout->addWidget(label_8);


        retranslateUi(BoosterPanel);

        QMetaObject::connectSlotsByName(BoosterPanel);
    } // setupUi

    void retranslateUi(QWidget *BoosterPanel)
    {
        BoosterPanel->setWindowTitle(QApplication::translate("BoosterPanel", "Form", nullptr));
        label_10->setText(QString());
        label->setText(QApplication::translate("BoosterPanel", "5 = Feedback of Booster input", nullptr));
        label_2->setText(QApplication::translate("BoosterPanel", "6 = Feedback of Booster output", nullptr));
        label_3->setText(QApplication::translate("BoosterPanel", "7 = On-Off Booster output", nullptr));
        label_11->setText(QString());
        label_4->setText(QString());
        label_5->setText(QString());
        lblBoosterStatus->setText(QApplication::translate("BoosterPanel", "Booster OK", nullptr));
        label_6->setText(QString());
        label_7->setText(QString());
        label_9->setText(QString());
        label_8->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class BoosterPanel: public Ui_BoosterPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOOSTERPANEL_H
