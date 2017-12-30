/********************************************************************************
** Form generated from reading UI file 'addeditlightcontroldialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDEDITLIGHTCONTROLDIALOG_H
#define UI_ADDEDITLIGHTCONTROLDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTimeEdit>

QT_BEGIN_NAMESPACE

class Ui_AddEditLightControlDialog
{
public:
    QFormLayout *formLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox;
    QLabel *lblNoControl;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lblSensor;
    QLineEdit *edSensor1;
    QLineEdit *edSensor2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *lblSensorState;
    QComboBox *cbSensorState;
    QGridLayout *gridLayout;
    QLabel *lblTimeOn;
    QTimeEdit *timeEditOn;
    QLabel *lblTimeOff;
    QTimeEdit *timeEditOff;
    QGridLayout *gridLayout_2;
    QLabel *lblTurnoutName;
    QLineEdit *edTurnout;
    QLabel *lblStatusTurnout;
    QComboBox *cbStatusTurnout;
    QGridLayout *gridLayout_3;
    QLabel *lblTriggerSensor;
    QLineEdit *edTriggerSensor;
    QLabel *lblDuration;
    QSpinBox *sbDuration;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnCreate;
    QPushButton *btnCancel;

    void setupUi(QDialog *AddEditLightControlDialog)
    {
        if (AddEditLightControlDialog->objectName().isEmpty())
            AddEditLightControlDialog->setObjectName(QStringLiteral("AddEditLightControlDialog"));
        AddEditLightControlDialog->resize(400, 453);
        formLayout = new QFormLayout(AddEditLightControlDialog);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(AddEditLightControlDialog);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        comboBox = new QComboBox(AddEditLightControlDialog);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout->addWidget(comboBox);


        formLayout->setLayout(0, QFormLayout::LabelRole, horizontalLayout);

        lblNoControl = new QLabel(AddEditLightControlDialog);
        lblNoControl->setObjectName(QStringLiteral("lblNoControl"));

        formLayout->setWidget(1, QFormLayout::LabelRole, lblNoControl);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        lblSensor = new QLabel(AddEditLightControlDialog);
        lblSensor->setObjectName(QStringLiteral("lblSensor"));
        lblSensor->setEnabled(true);

        horizontalLayout_3->addWidget(lblSensor);

        edSensor1 = new QLineEdit(AddEditLightControlDialog);
        edSensor1->setObjectName(QStringLiteral("edSensor1"));

        horizontalLayout_3->addWidget(edSensor1);

        edSensor2 = new QLineEdit(AddEditLightControlDialog);
        edSensor2->setObjectName(QStringLiteral("edSensor2"));

        horizontalLayout_3->addWidget(edSensor2);


        formLayout->setLayout(2, QFormLayout::LabelRole, horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        lblSensorState = new QLabel(AddEditLightControlDialog);
        lblSensorState->setObjectName(QStringLiteral("lblSensorState"));

        horizontalLayout_4->addWidget(lblSensorState);

        cbSensorState = new QComboBox(AddEditLightControlDialog);
        cbSensorState->setObjectName(QStringLiteral("cbSensorState"));

        horizontalLayout_4->addWidget(cbSensorState);


        formLayout->setLayout(3, QFormLayout::LabelRole, horizontalLayout_4);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lblTimeOn = new QLabel(AddEditLightControlDialog);
        lblTimeOn->setObjectName(QStringLiteral("lblTimeOn"));

        gridLayout->addWidget(lblTimeOn, 0, 0, 1, 1);

        timeEditOn = new QTimeEdit(AddEditLightControlDialog);
        timeEditOn->setObjectName(QStringLiteral("timeEditOn"));

        gridLayout->addWidget(timeEditOn, 0, 1, 1, 1);

        lblTimeOff = new QLabel(AddEditLightControlDialog);
        lblTimeOff->setObjectName(QStringLiteral("lblTimeOff"));

        gridLayout->addWidget(lblTimeOff, 1, 0, 1, 1);

        timeEditOff = new QTimeEdit(AddEditLightControlDialog);
        timeEditOff->setObjectName(QStringLiteral("timeEditOff"));

        gridLayout->addWidget(timeEditOff, 1, 1, 1, 1);


        formLayout->setLayout(4, QFormLayout::LabelRole, gridLayout);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        lblTurnoutName = new QLabel(AddEditLightControlDialog);
        lblTurnoutName->setObjectName(QStringLiteral("lblTurnoutName"));

        gridLayout_2->addWidget(lblTurnoutName, 0, 0, 1, 1);

        edTurnout = new QLineEdit(AddEditLightControlDialog);
        edTurnout->setObjectName(QStringLiteral("edTurnout"));

        gridLayout_2->addWidget(edTurnout, 0, 1, 1, 1);

        lblStatusTurnout = new QLabel(AddEditLightControlDialog);
        lblStatusTurnout->setObjectName(QStringLiteral("lblStatusTurnout"));

        gridLayout_2->addWidget(lblStatusTurnout, 1, 0, 1, 1);

        cbStatusTurnout = new QComboBox(AddEditLightControlDialog);
        cbStatusTurnout->setObjectName(QStringLiteral("cbStatusTurnout"));

        gridLayout_2->addWidget(cbStatusTurnout, 1, 1, 1, 1);


        formLayout->setLayout(5, QFormLayout::LabelRole, gridLayout_2);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        lblTriggerSensor = new QLabel(AddEditLightControlDialog);
        lblTriggerSensor->setObjectName(QStringLiteral("lblTriggerSensor"));

        gridLayout_3->addWidget(lblTriggerSensor, 0, 0, 1, 1);

        edTriggerSensor = new QLineEdit(AddEditLightControlDialog);
        edTriggerSensor->setObjectName(QStringLiteral("edTriggerSensor"));

        gridLayout_3->addWidget(edTriggerSensor, 0, 1, 1, 1);

        lblDuration = new QLabel(AddEditLightControlDialog);
        lblDuration->setObjectName(QStringLiteral("lblDuration"));

        gridLayout_3->addWidget(lblDuration, 1, 0, 1, 1);

        sbDuration = new QSpinBox(AddEditLightControlDialog);
        sbDuration->setObjectName(QStringLiteral("sbDuration"));

        gridLayout_3->addWidget(sbDuration, 1, 1, 1, 1);


        formLayout->setLayout(6, QFormLayout::LabelRole, gridLayout_3);

        horizontalSpacer = new QSpacerItem(379, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        formLayout->setItem(7, QFormLayout::LabelRole, horizontalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        btnCreate = new QPushButton(AddEditLightControlDialog);
        btnCreate->setObjectName(QStringLiteral("btnCreate"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnCreate->sizePolicy().hasHeightForWidth());
        btnCreate->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(btnCreate);

        btnCancel = new QPushButton(AddEditLightControlDialog);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));

        horizontalLayout_2->addWidget(btnCancel);


        formLayout->setLayout(8, QFormLayout::LabelRole, horizontalLayout_2);

        label->raise();
        comboBox->raise();
        lblNoControl->raise();
        btnCreate->raise();
        btnCancel->raise();
        btnCancel->raise();
        lblSensor->raise();
        edSensor1->raise();
        lblSensorState->raise();
        cbSensorState->raise();
        lblTimeOn->raise();
        lblTimeOff->raise();
        timeEditOff->raise();
        timeEditOn->raise();
        lblTurnoutName->raise();
        edTurnout->raise();
        lblStatusTurnout->raise();
        cbStatusTurnout->raise();
        lblTriggerSensor->raise();
        edTriggerSensor->raise();
        lblDuration->raise();
        sbDuration->raise();

        retranslateUi(AddEditLightControlDialog);

        QMetaObject::connectSlotsByName(AddEditLightControlDialog);
    } // setupUi

    void retranslateUi(QDialog *AddEditLightControlDialog)
    {
        AddEditLightControlDialog->setWindowTitle(QApplication::translate("AddEditLightControlDialog", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("AddEditLightControlDialog", "Control Type:", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("AddEditLightControlDialog", "None", Q_NULLPTR)
         << QApplication::translate("AddEditLightControlDialog", "By Sensor", Q_NULLPTR)
         << QApplication::translate("AddEditLightControlDialog", "By Fast Clock", Q_NULLPTR)
         << QApplication::translate("AddEditLightControlDialog", "By Turnout Status", Q_NULLPTR)
         << QApplication::translate("AddEditLightControlDialog", "By Timed On", Q_NULLPTR)
         << QApplication::translate("AddEditLightControlDialog", "By Two Sensors", Q_NULLPTR)
        );
        lblNoControl->setText(QApplication::translate("AddEditLightControlDialog", "No Automated Control Selected", Q_NULLPTR));
        lblSensor->setText(QApplication::translate("AddEditLightControlDialog", "Sensor Name:", Q_NULLPTR));
        lblSensorState->setText(QApplication::translate("AddEditLightControlDialog", "Sense for ON", Q_NULLPTR));
        cbSensorState->clear();
        cbSensorState->insertItems(0, QStringList()
         << QApplication::translate("AddEditLightControlDialog", "Active", Q_NULLPTR)
         << QApplication::translate("AddEditLightControlDialog", "Inactive", Q_NULLPTR)
        );
        lblTimeOn->setText(QApplication::translate("AddEditLightControlDialog", "Time on (hh:mm)", Q_NULLPTR));
        lblTimeOff->setText(QApplication::translate("AddEditLightControlDialog", "Time off (hh:mm)", Q_NULLPTR));
        lblTurnoutName->setText(QApplication::translate("AddEditLightControlDialog", "Turnout Name", Q_NULLPTR));
        lblStatusTurnout->setText(QApplication::translate("AddEditLightControlDialog", "Status for ON", Q_NULLPTR));
        cbStatusTurnout->clear();
        cbStatusTurnout->insertItems(0, QStringList()
         << QApplication::translate("AddEditLightControlDialog", "Closed", Q_NULLPTR)
         << QApplication::translate("AddEditLightControlDialog", "Thrown", Q_NULLPTR)
        );
        lblTriggerSensor->setText(QApplication::translate("AddEditLightControlDialog", "Trigger Sensor Name", Q_NULLPTR));
        lblDuration->setText(QApplication::translate("AddEditLightControlDialog", "Duration ON (msec)", Q_NULLPTR));
        btnCreate->setText(QApplication::translate("AddEditLightControlDialog", "Create", Q_NULLPTR));
        btnCancel->setText(QApplication::translate("AddEditLightControlDialog", "Cancel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AddEditLightControlDialog: public Ui_AddEditLightControlDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDEDITLIGHTCONTROLDIALOG_H
