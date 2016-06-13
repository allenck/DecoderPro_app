/********************************************************************************
** Form generated from reading UI file 'extraopcodedefinitionwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXTRAOPCODEDEFINITIONWIDGET_H
#define UI_EXTRAOPCODEDEFINITIONWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ExtraOpcodeDefinitionWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *lblHeading;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;

    void setupUi(QWidget *ExtraOpcodeDefinitionWidget)
    {
        if (ExtraOpcodeDefinitionWidget->objectName().isEmpty())
            ExtraOpcodeDefinitionWidget->setObjectName(QStringLiteral("ExtraOpcodeDefinitionWidget"));
        ExtraOpcodeDefinitionWidget->resize(95, 119);
        QFont font;
        font.setPointSize(7);
        font.setItalic(false);
        ExtraOpcodeDefinitionWidget->setFont(font);
        verticalLayout_2 = new QVBoxLayout(ExtraOpcodeDefinitionWidget);
        verticalLayout_2->setSpacing(2);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(ExtraOpcodeDefinitionWidget);
        label->setObjectName(QStringLiteral("label"));
        QPalette palette;
        QBrush brush(QColor(0, 170, 0, 255));
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

        horizontalLayout->addWidget(label);

        lblHeading = new QLabel(ExtraOpcodeDefinitionWidget);
        lblHeading->setObjectName(QStringLiteral("lblHeading"));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        lblHeading->setFont(font1);

        horizontalLayout->addWidget(lblHeading);


        verticalLayout->addLayout(horizontalLayout);

        label_2 = new QLabel(ExtraOpcodeDefinitionWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        label_2->setPalette(palette1);

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(ExtraOpcodeDefinitionWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Active, QPalette::Text, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        label_3->setPalette(palette2);

        verticalLayout->addWidget(label_3);

        label_4 = new QLabel(ExtraOpcodeDefinitionWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        QPalette palette3;
        QBrush brush2(QColor(0, 0, 255, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette3.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette3.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        label_4->setPalette(palette3);

        verticalLayout->addWidget(label_4);

        label_5 = new QLabel(ExtraOpcodeDefinitionWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette4.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette4.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette4.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette4.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        label_5->setPalette(palette4);

        verticalLayout->addWidget(label_5);

        label_6 = new QLabel(ExtraOpcodeDefinitionWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        QPalette palette5;
        QBrush brush3(QColor(255, 0, 0, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette5.setBrush(QPalette::Active, QPalette::WindowText, brush3);
        palette5.setBrush(QPalette::Active, QPalette::Text, brush3);
        palette5.setBrush(QPalette::Inactive, QPalette::WindowText, brush3);
        palette5.setBrush(QPalette::Inactive, QPalette::Text, brush3);
        palette5.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette5.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        label_6->setPalette(palette5);

        verticalLayout->addWidget(label_6);

        label_7 = new QLabel(ExtraOpcodeDefinitionWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        QPalette palette6;
        QBrush brush4(QColor(255, 170, 0, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette6.setBrush(QPalette::Active, QPalette::WindowText, brush4);
        palette6.setBrush(QPalette::Active, QPalette::Text, brush4);
        palette6.setBrush(QPalette::Inactive, QPalette::WindowText, brush4);
        palette6.setBrush(QPalette::Inactive, QPalette::Text, brush4);
        palette6.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette6.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        label_7->setPalette(palette6);

        verticalLayout->addWidget(label_7);

        label_8 = new QLabel(ExtraOpcodeDefinitionWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        QPalette palette7;
        palette7.setBrush(QPalette::Active, QPalette::WindowText, brush4);
        palette7.setBrush(QPalette::Active, QPalette::Text, brush4);
        palette7.setBrush(QPalette::Inactive, QPalette::WindowText, brush4);
        palette7.setBrush(QPalette::Inactive, QPalette::Text, brush4);
        palette7.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette7.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        label_8->setPalette(palette7);

        verticalLayout->addWidget(label_8);

        label_9 = new QLabel(ExtraOpcodeDefinitionWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        QPalette palette8;
        palette8.setBrush(QPalette::Active, QPalette::WindowText, brush4);
        palette8.setBrush(QPalette::Active, QPalette::Text, brush4);
        palette8.setBrush(QPalette::Inactive, QPalette::WindowText, brush4);
        palette8.setBrush(QPalette::Inactive, QPalette::Text, brush4);
        palette8.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette8.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        label_9->setPalette(palette8);

        verticalLayout->addWidget(label_9);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(ExtraOpcodeDefinitionWidget);

        QMetaObject::connectSlotsByName(ExtraOpcodeDefinitionWidget);
    } // setupUi

    void retranslateUi(QWidget *ExtraOpcodeDefinitionWidget)
    {
        ExtraOpcodeDefinitionWidget->setWindowTitle(QApplication::translate("ExtraOpcodeDefinitionWidget", "Form", 0));
        label->setText(QApplication::translate("ExtraOpcodeDefinitionWidget", "Off", 0));
        lblHeading->setText(QApplication::translate("ExtraOpcodeDefinitionWidget", "Extra Opcode x", 0));
        label_2->setText(QApplication::translate("ExtraOpcodeDefinitionWidget", "Direct Code", 0));
        label_3->setText(QApplication::translate("ExtraOpcodeDefinitionWidget", "Indirect Code", 0));
        label_4->setText(QApplication::translate("ExtraOpcodeDefinitionWidget", "Contact 1", 0));
        label_5->setText(QApplication::translate("ExtraOpcodeDefinitionWidget", "Contact 2", 0));
        label_6->setText(QApplication::translate("ExtraOpcodeDefinitionWidget", "Address", 0));
        label_7->setText(QApplication::translate("ExtraOpcodeDefinitionWidget", "<OPC>", 0));
        label_8->setText(QApplication::translate("ExtraOpcodeDefinitionWidget", "<ARG 1>", 0));
        label_9->setText(QApplication::translate("ExtraOpcodeDefinitionWidget", "<ARG 2>", 0));
    } // retranslateUi

};

namespace Ui {
    class ExtraOpcodeDefinitionWidget: public Ui_ExtraOpcodeDefinitionWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXTRAOPCODEDEFINITIONWIDGET_H
