/********************************************************************************
** Form generated from reading UI file 'outportdefinitionwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OUTPORTDEFINITIONWIDGET_H
#define UI_OUTPORTDEFINITIONWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OutPortDefinitionWidget
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QSpinBox *sbBlinkRate;
    QLabel *label_13;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;

    void setupUi(QWidget *OutPortDefinitionWidget)
    {
        if (OutPortDefinitionWidget->objectName().isEmpty())
            OutPortDefinitionWidget->setObjectName(QString::fromUtf8("OutPortDefinitionWidget"));
        OutPortDefinitionWidget->resize(137, 230);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(OutPortDefinitionWidget->sizePolicy().hasHeightForWidth());
        OutPortDefinitionWidget->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(7);
        OutPortDefinitionWidget->setFont(font);
        verticalLayout = new QVBoxLayout(OutPortDefinitionWidget);
        verticalLayout->setSpacing(2);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(OutPortDefinitionWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QPalette palette;
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush1(QColor(159, 158, 158, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        label->setPalette(palette);

        verticalLayout->addWidget(label);

        label_2 = new QLabel(OutPortDefinitionWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QPalette palette1;
        QBrush brush2(QColor(0, 0, 255, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        label_2->setPalette(palette1);

        verticalLayout->addWidget(label_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_3 = new QLabel(OutPortDefinitionWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QPalette palette2;
        QBrush brush3(QColor(170, 170, 127, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush3);
        palette2.setBrush(QPalette::Active, QPalette::Text, brush3);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush3);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush3);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        label_3->setPalette(palette2);

        horizontalLayout->addWidget(label_3);

        sbBlinkRate = new QSpinBox(OutPortDefinitionWidget);
        sbBlinkRate->setObjectName(QString::fromUtf8("sbBlinkRate"));
        sbBlinkRate->setMaximumSize(QSize(50, 16777215));
        sbBlinkRate->setMaximum(15);

        horizontalLayout->addWidget(sbBlinkRate);

        label_13 = new QLabel(OutPortDefinitionWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush3);
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush3);
        QBrush brush4(QColor(106, 104, 100, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        label_13->setPalette(palette3);

        horizontalLayout->addWidget(label_13);


        verticalLayout->addLayout(horizontalLayout);

        label_4 = new QLabel(OutPortDefinitionWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QPalette palette4;
        QBrush brush5(QColor(0, 170, 0, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette4.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        palette4.setBrush(QPalette::Active, QPalette::Text, brush5);
        palette4.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette4.setBrush(QPalette::Inactive, QPalette::Text, brush5);
        palette4.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        label_4->setPalette(palette4);

        verticalLayout->addWidget(label_4);

        label_5 = new QLabel(OutPortDefinitionWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        palette5.setBrush(QPalette::Active, QPalette::Text, brush5);
        palette5.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette5.setBrush(QPalette::Inactive, QPalette::Text, brush5);
        palette5.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette5.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        label_5->setPalette(palette5);

        verticalLayout->addWidget(label_5);

        label_6 = new QLabel(OutPortDefinitionWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        QPalette palette6;
        palette6.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        palette6.setBrush(QPalette::Active, QPalette::Text, brush5);
        palette6.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette6.setBrush(QPalette::Inactive, QPalette::Text, brush5);
        palette6.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette6.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        label_6->setPalette(palette6);

        verticalLayout->addWidget(label_6);

        label_7 = new QLabel(OutPortDefinitionWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        QPalette palette7;
        palette7.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        palette7.setBrush(QPalette::Active, QPalette::Text, brush5);
        palette7.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette7.setBrush(QPalette::Inactive, QPalette::Text, brush5);
        palette7.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette7.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        label_7->setPalette(palette7);

        verticalLayout->addWidget(label_7);

        label_8 = new QLabel(OutPortDefinitionWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        QPalette palette8;
        palette8.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        palette8.setBrush(QPalette::Active, QPalette::Text, brush5);
        palette8.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette8.setBrush(QPalette::Inactive, QPalette::Text, brush5);
        palette8.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette8.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        label_8->setPalette(palette8);

        verticalLayout->addWidget(label_8);

        label_9 = new QLabel(OutPortDefinitionWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        QPalette palette9;
        QBrush brush6(QColor(85, 85, 255, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette9.setBrush(QPalette::Active, QPalette::WindowText, brush6);
        palette9.setBrush(QPalette::Active, QPalette::Text, brush6);
        palette9.setBrush(QPalette::Inactive, QPalette::WindowText, brush6);
        palette9.setBrush(QPalette::Inactive, QPalette::Text, brush6);
        palette9.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette9.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        label_9->setPalette(palette9);

        verticalLayout->addWidget(label_9);

        label_10 = new QLabel(OutPortDefinitionWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        QPalette palette10;
        palette10.setBrush(QPalette::Active, QPalette::WindowText, brush6);
        palette10.setBrush(QPalette::Active, QPalette::Text, brush6);
        palette10.setBrush(QPalette::Inactive, QPalette::WindowText, brush6);
        palette10.setBrush(QPalette::Inactive, QPalette::Text, brush6);
        palette10.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette10.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        label_10->setPalette(palette10);

        verticalLayout->addWidget(label_10);

        label_11 = new QLabel(OutPortDefinitionWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        QPalette palette11;
        palette11.setBrush(QPalette::Active, QPalette::WindowText, brush6);
        palette11.setBrush(QPalette::Active, QPalette::Text, brush6);
        palette11.setBrush(QPalette::Inactive, QPalette::WindowText, brush6);
        palette11.setBrush(QPalette::Inactive, QPalette::Text, brush6);
        palette11.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette11.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        label_11->setPalette(palette11);

        verticalLayout->addWidget(label_11);

        label_12 = new QLabel(OutPortDefinitionWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        QPalette palette12;
        palette12.setBrush(QPalette::Active, QPalette::WindowText, brush6);
        palette12.setBrush(QPalette::Active, QPalette::Text, brush6);
        palette12.setBrush(QPalette::Inactive, QPalette::WindowText, brush6);
        palette12.setBrush(QPalette::Inactive, QPalette::Text, brush6);
        palette12.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette12.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        label_12->setPalette(palette12);

        verticalLayout->addWidget(label_12);


        retranslateUi(OutPortDefinitionWidget);

        QMetaObject::connectSlotsByName(OutPortDefinitionWidget);
    } // setupUi

    void retranslateUi(QWidget *OutPortDefinitionWidget)
    {
        OutPortDefinitionWidget->setWindowTitle(QCoreApplication::translate("OutPortDefinitionWidget", "Form", nullptr));
        label->setText(QCoreApplication::translate("OutPortDefinitionWidget", "Output", nullptr));
        label_2->setText(QCoreApplication::translate("OutPortDefinitionWidget", "Block Occupancy", nullptr));
        label_3->setText(QCoreApplication::translate("OutPortDefinitionWidget", "Blinking", nullptr));
        label_13->setText(QCoreApplication::translate("OutPortDefinitionWidget", "Frequency", nullptr));
        label_4->setText(QCoreApplication::translate("OutPortDefinitionWidget", "1 - On", nullptr));
        label_5->setText(QCoreApplication::translate("OutPortDefinitionWidget", "1 - Off             Fixed Contact", nullptr));
        label_6->setText(QCoreApplication::translate("OutPortDefinitionWidget", "2 - On", nullptr));
        label_7->setText(QCoreApplication::translate("OutPortDefinitionWidget", "2- Off", nullptr));
        label_8->setText(QCoreApplication::translate("OutPortDefinitionWidget", "4 Way Port ", nullptr));
        label_9->setText(QCoreApplication::translate("OutPortDefinitionWidget", "1 - Soft  Reset ", nullptr));
        label_10->setText(QCoreApplication::translate("OutPortDefinitionWidget", "1 Hard Reset ", nullptr));
        label_11->setText(QCoreApplication::translate("OutPortDefinitionWidget", "2 Soft Reset  Pulse Contact", nullptr));
        label_12->setText(QCoreApplication::translate("OutPortDefinitionWidget", "2 Hard Reset", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OutPortDefinitionWidget: public Ui_OutPortDefinitionWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OUTPORTDEFINITIONWIDGET_H
