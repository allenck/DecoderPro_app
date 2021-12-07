/********************************************************************************
** Form generated from reading UI file 'sensorentrywidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SENSORENTRYWIDGET_H
#define UI_SENSORENTRYWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "droppushbutton.h"
#include "sensorlineedit.h"

QT_BEGIN_NAMESPACE

class Ui_SensorEntryWidget
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QFormLayout *formLayout;
    QLabel *label;
    SensorLineEdit *edSensor;
    QPushButton *btnDelete;
    DropPushButton *iconButton;
    QLabel *labelPosition;

    void setupUi(QWidget *SensorEntryWidget)
    {
        if (SensorEntryWidget->objectName().isEmpty())
            SensorEntryWidget->setObjectName(QString::fromUtf8("SensorEntryWidget"));
        SensorEntryWidget->resize(197, 148);
        verticalLayout = new QVBoxLayout(SensorEntryWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame = new QFrame(SensorEntryWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        formLayout = new QFormLayout(frame);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label);

        edSensor = new SensorLineEdit(frame);
        edSensor->setObjectName(QString::fromUtf8("edSensor"));
        QFont font;
        font.setPointSize(9);
        edSensor->setFont(font);

        formLayout->setWidget(2, QFormLayout::LabelRole, edSensor);

        btnDelete = new QPushButton(frame);
        btnDelete->setObjectName(QString::fromUtf8("btnDelete"));

        formLayout->setWidget(3, QFormLayout::LabelRole, btnDelete);

        iconButton = new DropPushButton(frame);
        iconButton->setObjectName(QString::fromUtf8("iconButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(iconButton->sizePolicy().hasHeightForWidth());
        iconButton->setSizePolicy(sizePolicy);
        iconButton->setMinimumSize(QSize(48, 48));
        iconButton->setBaseSize(QSize(80, 80));

        formLayout->setWidget(2, QFormLayout::FieldRole, iconButton);

        labelPosition = new QLabel(frame);
        labelPosition->setObjectName(QString::fromUtf8("labelPosition"));

        formLayout->setWidget(1, QFormLayout::FieldRole, labelPosition);


        verticalLayout->addWidget(frame);


        retranslateUi(SensorEntryWidget);

        QMetaObject::connectSlotsByName(SensorEntryWidget);
    } // setupUi

    void retranslateUi(QWidget *SensorEntryWidget)
    {
        SensorEntryWidget->setWindowTitle(QCoreApplication::translate("SensorEntryWidget", "Form", nullptr));
        label->setText(QCoreApplication::translate("SensorEntryWidget", "Sensor", nullptr));
        edSensor->setText(QCoreApplication::translate("SensorEntryWidget", "undefined", nullptr));
        btnDelete->setText(QCoreApplication::translate("SensorEntryWidget", "Delete", nullptr));
        iconButton->setText(QString());
        labelPosition->setText(QCoreApplication::translate("SensorEntryWidget", "Position x", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SensorEntryWidget: public Ui_SensorEntryWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENSORENTRYWIDGET_H
