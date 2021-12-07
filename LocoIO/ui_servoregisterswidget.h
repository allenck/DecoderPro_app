/********************************************************************************
** Form generated from reading UI file 'servoregisterswidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVOREGISTERSWIDGET_H
#define UI_SERVOREGISTERSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
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
            ServoRegistersWidget->setObjectName(QString::fromUtf8("ServoRegistersWidget"));
        ServoRegistersWidget->resize(400, 36);
        verticalLayout = new QVBoxLayout(ServoRegistersWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        HorizontalLayout_registersWidget = new QHBoxLayout();
        HorizontalLayout_registersWidget->setObjectName(QString::fromUtf8("HorizontalLayout_registersWidget"));

        verticalLayout->addLayout(HorizontalLayout_registersWidget);


        retranslateUi(ServoRegistersWidget);

        QMetaObject::connectSlotsByName(ServoRegistersWidget);
    } // setupUi

    void retranslateUi(QWidget *ServoRegistersWidget)
    {
        ServoRegistersWidget->setWindowTitle(QCoreApplication::translate("ServoRegistersWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ServoRegistersWidget: public Ui_ServoRegistersWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVOREGISTERSWIDGET_H
