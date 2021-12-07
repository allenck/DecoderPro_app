/********************************************************************************
** Form generated from reading UI file 'booster7widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BOOSTER7WIDGET_H
#define UI_BOOSTER7WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Booster7Widget
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *lblfiller;
    QLineEdit *edStatus;
    QLabel *lblfiller_2;
    QLabel *lblfiller_3;
    QLabel *lblfiller_4;
    QLabel *lblfiller_11;
    QLabel *lblfiller_5;
    QLabel *lblfiller_6;
    QLabel *lblfiller_7;
    QLabel *lblfiller_8;
    QLabel *lblfiller_10;
    QLabel *lblfiller_9;
    QLabel *lblfiller_12;
    QLabel *lblfiller_13;

    void setupUi(QWidget *Booster7Widget)
    {
        if (Booster7Widget->objectName().isEmpty())
            Booster7Widget->setObjectName(QString::fromUtf8("Booster7Widget"));
        Booster7Widget->resize(38, 314);
        verticalLayout = new QVBoxLayout(Booster7Widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lblfiller = new QLabel(Booster7Widget);
        lblfiller->setObjectName(QString::fromUtf8("lblfiller"));
        lblfiller->setMaximumSize(QSize(16777215, 20));

        verticalLayout->addWidget(lblfiller);

        edStatus = new QLineEdit(Booster7Widget);
        edStatus->setObjectName(QString::fromUtf8("edStatus"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(edStatus->sizePolicy().hasHeightForWidth());
        edStatus->setSizePolicy(sizePolicy);
        edStatus->setMaximumSize(QSize(20, 20));
        edStatus->setStyleSheet(QString::fromUtf8("QLabel { background-color : yellow; color : black; }"));
        edStatus->setReadOnly(true);

        verticalLayout->addWidget(edStatus);

        lblfiller_2 = new QLabel(Booster7Widget);
        lblfiller_2->setObjectName(QString::fromUtf8("lblfiller_2"));
        lblfiller_2->setMaximumSize(QSize(16777215, 20));

        verticalLayout->addWidget(lblfiller_2);

        lblfiller_3 = new QLabel(Booster7Widget);
        lblfiller_3->setObjectName(QString::fromUtf8("lblfiller_3"));
        lblfiller_3->setMaximumSize(QSize(16777215, 20));

        verticalLayout->addWidget(lblfiller_3);

        lblfiller_4 = new QLabel(Booster7Widget);
        lblfiller_4->setObjectName(QString::fromUtf8("lblfiller_4"));
        lblfiller_4->setMaximumSize(QSize(16777215, 20));

        verticalLayout->addWidget(lblfiller_4);

        lblfiller_11 = new QLabel(Booster7Widget);
        lblfiller_11->setObjectName(QString::fromUtf8("lblfiller_11"));
        lblfiller_11->setMaximumSize(QSize(16777215, 20));

        verticalLayout->addWidget(lblfiller_11);

        lblfiller_5 = new QLabel(Booster7Widget);
        lblfiller_5->setObjectName(QString::fromUtf8("lblfiller_5"));
        lblfiller_5->setMaximumSize(QSize(16777215, 20));

        verticalLayout->addWidget(lblfiller_5);

        lblfiller_6 = new QLabel(Booster7Widget);
        lblfiller_6->setObjectName(QString::fromUtf8("lblfiller_6"));
        lblfiller_6->setMaximumSize(QSize(16777215, 20));

        verticalLayout->addWidget(lblfiller_6);

        lblfiller_7 = new QLabel(Booster7Widget);
        lblfiller_7->setObjectName(QString::fromUtf8("lblfiller_7"));
        lblfiller_7->setMaximumSize(QSize(16777215, 20));

        verticalLayout->addWidget(lblfiller_7);

        lblfiller_8 = new QLabel(Booster7Widget);
        lblfiller_8->setObjectName(QString::fromUtf8("lblfiller_8"));
        lblfiller_8->setMaximumSize(QSize(16777215, 20));

        verticalLayout->addWidget(lblfiller_8);

        lblfiller_10 = new QLabel(Booster7Widget);
        lblfiller_10->setObjectName(QString::fromUtf8("lblfiller_10"));
        lblfiller_10->setMaximumSize(QSize(16777215, 20));

        verticalLayout->addWidget(lblfiller_10);

        lblfiller_9 = new QLabel(Booster7Widget);
        lblfiller_9->setObjectName(QString::fromUtf8("lblfiller_9"));
        lblfiller_9->setMaximumSize(QSize(16777215, 20));

        verticalLayout->addWidget(lblfiller_9);

        lblfiller_12 = new QLabel(Booster7Widget);
        lblfiller_12->setObjectName(QString::fromUtf8("lblfiller_12"));
        lblfiller_12->setMaximumSize(QSize(16777215, 20));

        verticalLayout->addWidget(lblfiller_12);

        lblfiller_13 = new QLabel(Booster7Widget);
        lblfiller_13->setObjectName(QString::fromUtf8("lblfiller_13"));
        lblfiller_13->setMaximumSize(QSize(16777215, 20));

        verticalLayout->addWidget(lblfiller_13);


        retranslateUi(Booster7Widget);

        QMetaObject::connectSlotsByName(Booster7Widget);
    } // setupUi

    void retranslateUi(QWidget *Booster7Widget)
    {
        Booster7Widget->setWindowTitle(QCoreApplication::translate("Booster7Widget", "Form", nullptr));
        lblfiller->setText(QString());
        lblfiller_2->setText(QString());
        lblfiller_3->setText(QString());
        lblfiller_4->setText(QString());
        lblfiller_11->setText(QString());
        lblfiller_5->setText(QString());
        lblfiller_6->setText(QString());
        lblfiller_7->setText(QString());
        lblfiller_8->setText(QString());
        lblfiller_10->setText(QString());
        lblfiller_9->setText(QString());
        lblfiller_12->setText(QString());
        lblfiller_13->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Booster7Widget: public Ui_Booster7Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOOSTER7WIDGET_H
