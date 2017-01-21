/********************************************************************************
** Form generated from reading UI file 'sensorentrywidget.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SENSORENTRYWIDGET_H
#define UI_SENSORENTRYWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
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
            SensorEntryWidget->setObjectName(QStringLiteral("SensorEntryWidget"));
        SensorEntryWidget->resize(197, 148);
        verticalLayout = new QVBoxLayout(SensorEntryWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        frame = new QFrame(SensorEntryWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        formLayout = new QFormLayout(frame);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label);

        edSensor = new SensorLineEdit(frame);
        edSensor->setObjectName(QStringLiteral("edSensor"));
        QFont font;
        font.setPointSize(9);
        edSensor->setFont(font);

        formLayout->setWidget(2, QFormLayout::LabelRole, edSensor);

        btnDelete = new QPushButton(frame);
        btnDelete->setObjectName(QStringLiteral("btnDelete"));

        formLayout->setWidget(3, QFormLayout::LabelRole, btnDelete);

        iconButton = new DropPushButton(frame);
        iconButton->setObjectName(QStringLiteral("iconButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(iconButton->sizePolicy().hasHeightForWidth());
        iconButton->setSizePolicy(sizePolicy);
        iconButton->setMinimumSize(QSize(48, 48));
        iconButton->setBaseSize(QSize(80, 80));

        formLayout->setWidget(2, QFormLayout::FieldRole, iconButton);

        labelPosition = new QLabel(frame);
        labelPosition->setObjectName(QStringLiteral("labelPosition"));

        formLayout->setWidget(1, QFormLayout::FieldRole, labelPosition);


        verticalLayout->addWidget(frame);


        retranslateUi(SensorEntryWidget);

        QMetaObject::connectSlotsByName(SensorEntryWidget);
    } // setupUi

    void retranslateUi(QWidget *SensorEntryWidget)
    {
        SensorEntryWidget->setWindowTitle(QApplication::translate("SensorEntryWidget", "Form", 0));
        label->setText(QApplication::translate("SensorEntryWidget", "Sensor", 0));
        edSensor->setText(QApplication::translate("SensorEntryWidget", "undefined", 0));
        btnDelete->setText(QApplication::translate("SensorEntryWidget", "Delete", 0));
        iconButton->setText(QString());
        labelPosition->setText(QApplication::translate("SensorEntryWidget", "Position x", 0));
    } // retranslateUi

};

namespace Ui {
    class SensorEntryWidget: public Ui_SensorEntryWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENSORENTRYWIDGET_H
