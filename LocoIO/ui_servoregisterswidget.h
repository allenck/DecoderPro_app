/********************************************************************************
** Form generated from reading UI file 'servoregisterswidget.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVOREGISTERSWIDGET_H
#define UI_SERVOREGISTERSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ServoRegistersWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *HorizontalLayout_registersWidget;

    void setupUi(QWidget *ServoRegistersWidget)
    {
        if (ServoRegistersWidget->objectName().isEmpty())
            ServoRegistersWidget->setObjectName(QStringLiteral("ServoRegistersWidget"));
        ServoRegistersWidget->resize(400, 36);
        verticalLayout = new QVBoxLayout(ServoRegistersWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        HorizontalLayout_registersWidget = new QHBoxLayout();
        HorizontalLayout_registersWidget->setObjectName(QStringLiteral("HorizontalLayout_registersWidget"));

        verticalLayout->addLayout(HorizontalLayout_registersWidget);


        retranslateUi(ServoRegistersWidget);

        QMetaObject::connectSlotsByName(ServoRegistersWidget);
    } // setupUi

    void retranslateUi(QWidget *ServoRegistersWidget)
    {
        ServoRegistersWidget->setWindowTitle(QApplication::translate("ServoRegistersWidget", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class ServoRegistersWidget: public Ui_ServoRegistersWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVOREGISTERSWIDGET_H
