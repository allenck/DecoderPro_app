/********************************************************************************
** Form generated from reading UI file 'sensorentrywidget.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
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
            SensorEntryWidget->setObjectName(QLatin1String("SensorEntryWidget"));
        SensorEntryWidget->resize(197, 148);
        verticalLayout = new QVBoxLayout(SensorEntryWidget);
        verticalLayout->setObjectName(QLatin1String("verticalLayout"));
        frame = new QFrame(SensorEntryWidget);
        frame->setObjectName(QLatin1String("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        formLayout = new QFormLayout(frame);
        formLayout->setObjectName(QLatin1String("formLayout"));
        label = new QLabel(frame);
        label->setObjectName(QLatin1String("label"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label);

        edSensor = new SensorLineEdit(frame);
        edSensor->setObjectName(QLatin1String("edSensor"));
        QFont font;
        font.setPointSize(9);
        edSensor->setFont(font);

        formLayout->setWidget(2, QFormLayout::LabelRole, edSensor);

        btnDelete = new QPushButton(frame);
        btnDelete->setObjectName(QLatin1String("btnDelete"));

        formLayout->setWidget(3, QFormLayout::LabelRole, btnDelete);

        iconButton = new DropPushButton(frame);
        iconButton->setObjectName(QLatin1String("iconButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(iconButton->sizePolicy().hasHeightForWidth());
        iconButton->setSizePolicy(sizePolicy);
        iconButton->setMinimumSize(QSize(48, 48));
        iconButton->setBaseSize(QSize(80, 80));

        formLayout->setWidget(2, QFormLayout::FieldRole, iconButton);

        labelPosition = new QLabel(frame);
        labelPosition->setObjectName(QLatin1String("labelPosition"));

        formLayout->setWidget(1, QFormLayout::FieldRole, labelPosition);


        verticalLayout->addWidget(frame);


        retranslateUi(SensorEntryWidget);

        QMetaObject::connectSlotsByName(SensorEntryWidget);
    } // setupUi

    void retranslateUi(QWidget *SensorEntryWidget)
    {
        SensorEntryWidget->setWindowTitle(QApplication::translate("SensorEntryWidget", "Form", nullptr));
        label->setText(QApplication::translate("SensorEntryWidget", "Sensor", nullptr));
        edSensor->setText(QApplication::translate("SensorEntryWidget", "undefined", nullptr));
        btnDelete->setText(QApplication::translate("SensorEntryWidget", "Delete", nullptr));
        iconButton->setText(QString());
        labelPosition->setText(QApplication::translate("SensorEntryWidget", "Position x", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SensorEntryWidget: public Ui_SensorEntryWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENSORENTRYWIDGET_H
