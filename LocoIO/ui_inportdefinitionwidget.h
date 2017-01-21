/********************************************************************************
** Form generated from reading UI file 'inportdefinitionwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPORTDEFINITIONWIDGET_H
#define UI_INPORTDEFINITIONWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InPortDefinitionWidget
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *lblDoubleInput;

    void setupUi(QWidget *InPortDefinitionWidget)
    {
        if (InPortDefinitionWidget->objectName().isEmpty())
            InPortDefinitionWidget->setObjectName(QStringLiteral("InPortDefinitionWidget"));
        InPortDefinitionWidget->resize(154, 245);
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush1(QColor(159, 158, 158, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        InPortDefinitionWidget->setPalette(palette);
        QFont font;
        font.setPointSize(7);
        InPortDefinitionWidget->setFont(font);
        verticalLayout = new QVBoxLayout(InPortDefinitionWidget);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(InPortDefinitionWidget);
        label->setObjectName(QStringLiteral("label"));
        QPalette palette1;
        QBrush brush2(QColor(255, 0, 0, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        label->setPalette(palette1);

        verticalLayout->addWidget(label);

        label_2 = new QLabel(InPortDefinitionWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette2.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        label_2->setPalette(palette2);

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(InPortDefinitionWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        QPalette palette3;
        QBrush brush3(QColor(0, 0, 255, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush3);
        palette3.setBrush(QPalette::Active, QPalette::Text, brush3);
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush3);
        palette3.setBrush(QPalette::Inactive, QPalette::Text, brush3);
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        label_3->setPalette(palette3);

        verticalLayout->addWidget(label_3);

        label_4 = new QLabel(InPortDefinitionWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::WindowText, brush3);
        palette4.setBrush(QPalette::Active, QPalette::Text, brush3);
        palette4.setBrush(QPalette::Inactive, QPalette::WindowText, brush3);
        palette4.setBrush(QPalette::Inactive, QPalette::Text, brush3);
        palette4.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        label_4->setPalette(palette4);

        verticalLayout->addWidget(label_4);

        label_5 = new QLabel(InPortDefinitionWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::WindowText, brush3);
        palette5.setBrush(QPalette::Active, QPalette::Text, brush3);
        palette5.setBrush(QPalette::Inactive, QPalette::WindowText, brush3);
        palette5.setBrush(QPalette::Inactive, QPalette::Text, brush3);
        palette5.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette5.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        label_5->setPalette(palette5);

        verticalLayout->addWidget(label_5);

        label_6 = new QLabel(InPortDefinitionWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        QPalette palette6;
        QBrush brush4(QColor(0, 170, 0, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette6.setBrush(QPalette::Active, QPalette::WindowText, brush4);
        palette6.setBrush(QPalette::Active, QPalette::Text, brush4);
        palette6.setBrush(QPalette::Inactive, QPalette::WindowText, brush4);
        palette6.setBrush(QPalette::Inactive, QPalette::Text, brush4);
        palette6.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette6.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        label_6->setPalette(palette6);

        verticalLayout->addWidget(label_6);

        label_7 = new QLabel(InPortDefinitionWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        QPalette palette7;
        palette7.setBrush(QPalette::Active, QPalette::WindowText, brush4);
        palette7.setBrush(QPalette::Active, QPalette::Text, brush4);
        palette7.setBrush(QPalette::Inactive, QPalette::WindowText, brush4);
        palette7.setBrush(QPalette::Inactive, QPalette::Text, brush4);
        palette7.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette7.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        label_7->setPalette(palette7);

        verticalLayout->addWidget(label_7);

        label_8 = new QLabel(InPortDefinitionWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        QPalette palette8;
        palette8.setBrush(QPalette::Active, QPalette::WindowText, brush4);
        palette8.setBrush(QPalette::Active, QPalette::Text, brush4);
        palette8.setBrush(QPalette::Inactive, QPalette::WindowText, brush4);
        palette8.setBrush(QPalette::Inactive, QPalette::Text, brush4);
        palette8.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette8.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        label_8->setPalette(palette8);

        verticalLayout->addWidget(label_8);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        checkBox = new QCheckBox(InPortDefinitionWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        QPalette palette9;
        palette9.setBrush(QPalette::Active, QPalette::WindowText, brush4);
        palette9.setBrush(QPalette::Active, QPalette::Text, brush4);
        palette9.setBrush(QPalette::Inactive, QPalette::WindowText, brush4);
        palette9.setBrush(QPalette::Inactive, QPalette::Text, brush4);
        palette9.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette9.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        checkBox->setPalette(palette9);

        horizontalLayout->addWidget(checkBox);

        checkBox_2 = new QCheckBox(InPortDefinitionWidget);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));
        QPalette palette10;
        palette10.setBrush(QPalette::Active, QPalette::WindowText, brush4);
        palette10.setBrush(QPalette::Active, QPalette::Text, brush4);
        palette10.setBrush(QPalette::Inactive, QPalette::WindowText, brush4);
        palette10.setBrush(QPalette::Inactive, QPalette::Text, brush4);
        palette10.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette10.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        checkBox_2->setPalette(palette10);

        horizontalLayout->addWidget(checkBox_2);


        verticalLayout->addLayout(horizontalLayout);

        label_9 = new QLabel(InPortDefinitionWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        QPalette palette11;
        QBrush brush5(QColor(0, 170, 127, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette11.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        palette11.setBrush(QPalette::Active, QPalette::Text, brush5);
        palette11.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette11.setBrush(QPalette::Inactive, QPalette::Text, brush5);
        palette11.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette11.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        label_9->setPalette(palette11);

        verticalLayout->addWidget(label_9);

        label_10 = new QLabel(InPortDefinitionWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        QPalette palette12;
        palette12.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        palette12.setBrush(QPalette::Active, QPalette::Text, brush5);
        palette12.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette12.setBrush(QPalette::Inactive, QPalette::Text, brush5);
        palette12.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette12.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        label_10->setPalette(palette12);

        verticalLayout->addWidget(label_10);

        label_11 = new QLabel(InPortDefinitionWidget);
        label_11->setObjectName(QStringLiteral("label_11"));
        QPalette palette13;
        palette13.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        palette13.setBrush(QPalette::Active, QPalette::Text, brush5);
        palette13.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette13.setBrush(QPalette::Inactive, QPalette::Text, brush5);
        palette13.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette13.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        label_11->setPalette(palette13);

        verticalLayout->addWidget(label_11);

        lblDoubleInput = new QLabel(InPortDefinitionWidget);
        lblDoubleInput->setObjectName(QStringLiteral("lblDoubleInput"));
        QPalette palette14;
        QBrush brush6(QColor(255, 170, 0, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette14.setBrush(QPalette::Active, QPalette::WindowText, brush6);
        palette14.setBrush(QPalette::Active, QPalette::Text, brush6);
        palette14.setBrush(QPalette::Inactive, QPalette::WindowText, brush6);
        palette14.setBrush(QPalette::Inactive, QPalette::Text, brush6);
        palette14.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette14.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        lblDoubleInput->setPalette(palette14);

        verticalLayout->addWidget(lblDoubleInput);


        retranslateUi(InPortDefinitionWidget);

        QMetaObject::connectSlotsByName(InPortDefinitionWidget);
    } // setupUi

    void retranslateUi(QWidget *InPortDefinitionWidget)
    {
        InPortDefinitionWidget->setWindowTitle(QApplication::translate("InPortDefinitionWidget", "Form", 0));
        label->setText(QApplication::translate("InPortDefinitionWidget", "Port not used", 0));
        label_2->setText(QApplication::translate("InPortDefinitionWidget", "Input", 0));
        label_3->setText(QApplication::translate("InPortDefinitionWidget", "Block Detection Active Low", 0));
        label_4->setText(QApplication::translate("InPortDefinitionWidget", "Block Detection Active High", 0));
        label_5->setText(QApplication::translate("InPortDefinitionWidget", "Block Detection Delay", 0));
        label_6->setText(QApplication::translate("InPortDefinitionWidget", "Toggle Switch", 0));
        label_7->setText(QApplication::translate("InPortDefinitionWidget", "Push Button Active Low", 0));
        label_8->setText(QApplication::translate("InPortDefinitionWidget", "Push Button Active High", 0));
        checkBox->setText(QApplication::translate("InPortDefinitionWidget", "Direct", 0));
        checkBox_2->setText(QApplication::translate("InPortDefinitionWidget", "Indirect", 0));
        label_9->setText(QApplication::translate("InPortDefinitionWidget", "Switch Point Feedback ", 0));
        label_10->setText(QApplication::translate("InPortDefinitionWidget", "Contact 1 Point Feedback", 0));
        label_11->setText(QApplication::translate("InPortDefinitionWidget", "Contact 2 Point Feedback", 0));
        lblDoubleInput->setText(QApplication::translate("InPortDefinitionWidget", "Double Input", 0));
    } // retranslateUi

};

namespace Ui {
    class InPortDefinitionWidget: public Ui_InPortDefinitionWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPORTDEFINITIONWIDGET_H
