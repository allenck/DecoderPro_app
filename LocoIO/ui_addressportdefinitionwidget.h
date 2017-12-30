/********************************************************************************
** Form generated from reading UI file 'addressportdefinitionwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDRESSPORTDEFINITIONWIDGET_H
#define UI_ADDRESSPORTDEFINITIONWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddressPortDefinitionWidget
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

    void setupUi(QWidget *AddressPortDefinitionWidget)
    {
        if (AddressPortDefinitionWidget->objectName().isEmpty())
            AddressPortDefinitionWidget->setObjectName(QStringLiteral("AddressPortDefinitionWidget"));
        AddressPortDefinitionWidget->resize(145, 150);
        QFont font;
        font.setPointSize(7);
        AddressPortDefinitionWidget->setFont(font);
        verticalLayout = new QVBoxLayout(AddressPortDefinitionWidget);
        verticalLayout->setSpacing(2);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(AddressPortDefinitionWidget);
        label->setObjectName(QStringLiteral("label"));
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

        label_2 = new QLabel(AddressPortDefinitionWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        QPalette palette1;
        QBrush brush2(QColor(255, 0, 127, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        label_2->setPalette(palette1);

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(AddressPortDefinitionWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette2.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        label_3->setPalette(palette2);

        verticalLayout->addWidget(label_3);

        label_4 = new QLabel(AddressPortDefinitionWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette3.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette3.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        label_4->setPalette(palette3);

        verticalLayout->addWidget(label_4);

        label_5 = new QLabel(AddressPortDefinitionWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette4.setBrush(QPalette::Active, QPalette::Text, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        label_5->setPalette(palette4);

        verticalLayout->addWidget(label_5);

        label_6 = new QLabel(AddressPortDefinitionWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette5.setBrush(QPalette::Active, QPalette::Text, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette5.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        label_6->setPalette(palette5);

        verticalLayout->addWidget(label_6);

        label_7 = new QLabel(AddressPortDefinitionWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        verticalLayout->addWidget(label_7);


        retranslateUi(AddressPortDefinitionWidget);

        QMetaObject::connectSlotsByName(AddressPortDefinitionWidget);
    } // setupUi

    void retranslateUi(QWidget *AddressPortDefinitionWidget)
    {
        AddressPortDefinitionWidget->setWindowTitle(QApplication::translate("AddressPortDefinitionWidget", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("AddressPortDefinitionWidget", "Address", Q_NULLPTR));
        label_2->setText(QApplication::translate("AddressPortDefinitionWidget", "Configuration", Q_NULLPTR));
        label_3->setText(QApplication::translate("AddressPortDefinitionWidget", "Value 1", Q_NULLPTR));
        label_4->setText(QApplication::translate("AddressPortDefinitionWidget", "Value 2", Q_NULLPTR));
        label_5->setText(QApplication::translate("AddressPortDefinitionWidget", "Read", Q_NULLPTR));
        label_6->setText(QApplication::translate("AddressPortDefinitionWidget", "Write", Q_NULLPTR));
        label_7->setText(QApplication::translate("AddressPortDefinitionWidget", "Edit Value 2", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AddressPortDefinitionWidget: public Ui_AddressPortDefinitionWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDRESSPORTDEFINITIONWIDGET_H
