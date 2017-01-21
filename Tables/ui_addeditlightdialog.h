/********************************************************************************
** Form generated from reading UI file 'addeditlightdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDEDITLIGHTDIALOG_H
#define UI_ADDEDITLIGHTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AddEditLightDialog
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QComboBox *prefixBox;
    QCheckBox *addRangeBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QLineEdit *fieldHardwareAddress;
    QLabel *lblNbrToAdd;
    QSpinBox *fieldNumToAdd;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_6;
    QLineEdit *userName;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QDoubleSpinBox *fieldMinIntensity;
    QLabel *label_3;
    QDoubleSpinBox *fieldMaxIntensity;
    QLabel *label_4;
    QDoubleSpinBox *fieldTransitionTime;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QTableView *tableView;
    QPushButton *addControl;
    QLabel *status1;
    QLabel *status2;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *btnCreate;
    QPushButton *btnUpdate;
    QPushButton *btnCancel;

    void setupUi(QDialog *AddEditLightDialog)
    {
        if (AddEditLightDialog->objectName().isEmpty())
            AddEditLightDialog->setObjectName(QStringLiteral("AddEditLightDialog"));
        AddEditLightDialog->resize(626, 461);
        gridLayout = new QGridLayout(AddEditLightDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(AddEditLightDialog);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        prefixBox = new QComboBox(AddEditLightDialog);
        prefixBox->setObjectName(QStringLiteral("prefixBox"));

        horizontalLayout_2->addWidget(prefixBox);

        addRangeBox = new QCheckBox(AddEditLightDialog);
        addRangeBox->setObjectName(QStringLiteral("addRangeBox"));

        horizontalLayout_2->addWidget(addRangeBox);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_5 = new QLabel(AddEditLightDialog);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_3->addWidget(label_5);

        fieldHardwareAddress = new QLineEdit(AddEditLightDialog);
        fieldHardwareAddress->setObjectName(QStringLiteral("fieldHardwareAddress"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(fieldHardwareAddress->sizePolicy().hasHeightForWidth());
        fieldHardwareAddress->setSizePolicy(sizePolicy);
        fieldHardwareAddress->setInputMethodHints(Qt::ImhDigitsOnly|Qt::ImhPreferNumbers);
        fieldHardwareAddress->setMaxLength(4);

        horizontalLayout_3->addWidget(fieldHardwareAddress);

        lblNbrToAdd = new QLabel(AddEditLightDialog);
        lblNbrToAdd->setObjectName(QStringLiteral("lblNbrToAdd"));

        horizontalLayout_3->addWidget(lblNbrToAdd);

        fieldNumToAdd = new QSpinBox(AddEditLightDialog);
        fieldNumToAdd->setObjectName(QStringLiteral("fieldNumToAdd"));
        fieldNumToAdd->setMinimum(1);

        horizontalLayout_3->addWidget(fieldNumToAdd);


        gridLayout->addLayout(horizontalLayout_3, 1, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_6 = new QLabel(AddEditLightDialog);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_4->addWidget(label_6);

        userName = new QLineEdit(AddEditLightDialog);
        userName->setObjectName(QStringLiteral("userName"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(userName->sizePolicy().hasHeightForWidth());
        userName->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(userName);


        gridLayout->addLayout(horizontalLayout_4, 2, 0, 1, 1);

        groupBox = new QGroupBox(AddEditLightDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        fieldMinIntensity = new QDoubleSpinBox(groupBox);
        fieldMinIntensity->setObjectName(QStringLiteral("fieldMinIntensity"));
        fieldMinIntensity->setMaximum(1);

        horizontalLayout->addWidget(fieldMinIntensity);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);

        fieldMaxIntensity = new QDoubleSpinBox(groupBox);
        fieldMaxIntensity->setObjectName(QStringLiteral("fieldMaxIntensity"));
        fieldMaxIntensity->setMaximum(1);

        horizontalLayout->addWidget(fieldMaxIntensity);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout->addWidget(label_4);

        fieldTransitionTime = new QDoubleSpinBox(groupBox);
        fieldTransitionTime->setObjectName(QStringLiteral("fieldTransitionTime"));

        horizontalLayout->addWidget(fieldTransitionTime);


        verticalLayout_2->addLayout(horizontalLayout);


        gridLayout->addWidget(groupBox, 3, 0, 1, 1);

        groupBox_2 = new QGroupBox(AddEditLightDialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tableView = new QTableView(groupBox_2);
        tableView->setObjectName(QStringLiteral("tableView"));

        verticalLayout->addWidget(tableView);

        addControl = new QPushButton(groupBox_2);
        addControl->setObjectName(QStringLiteral("addControl"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(addControl->sizePolicy().hasHeightForWidth());
        addControl->setSizePolicy(sizePolicy2);

        verticalLayout->addWidget(addControl);


        verticalLayout_3->addLayout(verticalLayout);

        status1 = new QLabel(groupBox_2);
        status1->setObjectName(QStringLiteral("status1"));

        verticalLayout_3->addWidget(status1);

        status2 = new QLabel(groupBox_2);
        status2->setObjectName(QStringLiteral("status2"));

        verticalLayout_3->addWidget(status2);


        gridLayout->addWidget(groupBox_2, 4, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        btnCreate = new QPushButton(AddEditLightDialog);
        btnCreate->setObjectName(QStringLiteral("btnCreate"));
        sizePolicy2.setHeightForWidth(btnCreate->sizePolicy().hasHeightForWidth());
        btnCreate->setSizePolicy(sizePolicy2);

        horizontalLayout_5->addWidget(btnCreate);

        btnUpdate = new QPushButton(AddEditLightDialog);
        btnUpdate->setObjectName(QStringLiteral("btnUpdate"));
        sizePolicy2.setHeightForWidth(btnUpdate->sizePolicy().hasHeightForWidth());
        btnUpdate->setSizePolicy(sizePolicy2);

        horizontalLayout_5->addWidget(btnUpdate);

        btnCancel = new QPushButton(AddEditLightDialog);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));
        sizePolicy2.setHeightForWidth(btnCancel->sizePolicy().hasHeightForWidth());
        btnCancel->setSizePolicy(sizePolicy2);

        horizontalLayout_5->addWidget(btnCancel);


        gridLayout->addLayout(horizontalLayout_5, 5, 0, 1, 1);


        retranslateUi(AddEditLightDialog);

        QMetaObject::connectSlotsByName(AddEditLightDialog);
    } // setupUi

    void retranslateUi(QDialog *AddEditLightDialog)
    {
        AddEditLightDialog->setWindowTitle(QApplication::translate("AddEditLightDialog", "Add Light", 0));
        label->setText(QApplication::translate("AddEditLightDialog", "System:", 0));
        prefixBox->clear();
        prefixBox->insertItems(0, QStringList()
         << QApplication::translate("AddEditLightDialog", "Internal", 0)
        );
#ifndef QT_NO_TOOLTIP
        prefixBox->setToolTip(QApplication::translate("AddEditLightDialog", "<html><head/><body><p>Select a system for the new light.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        addRangeBox->setToolTip(QApplication::translate("AddEditLightDialog", "<html><head/><body><p>Check to add more than one Light with sequential addresses.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        addRangeBox->setText(QApplication::translate("AddEditLightDialog", "Add a sequential range", 0));
        label_5->setText(QApplication::translate("AddEditLightDialog", "Hardware Address:", 0));
#ifndef QT_NO_TOOLTIP
        fieldHardwareAddress->setToolTip(QApplication::translate("AddEditLightDialog", "<html><head/><body><p>Enter a hardware address for a new Light; e.g. 13</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        lblNbrToAdd->setText(QApplication::translate("AddEditLightDialog", "Number to add:", 0));
        label_6->setText(QApplication::translate("AddEditLightDialog", "User Name:", 0));
#ifndef QT_NO_TOOLTIP
        userName->setToolTip(QApplication::translate("AddEditLightDialog", "<html><head/><body><p>Enter user name for new Light, e.g. Jones House.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        groupBox->setTitle(QApplication::translate("AddEditLightDialog", "Variable Intensity", 0));
        label_2->setText(QApplication::translate("AddEditLightDialog", "Minimum Intensity", 0));
#ifndef QT_NO_TOOLTIP
        fieldMinIntensity->setToolTip(QApplication::translate("AddEditLightDialog", "<html><head/><body><p>0 to 100%. Must be less than Max.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        label_3->setText(QApplication::translate("AddEditLightDialog", "Maximum Intensity", 0));
#ifndef QT_NO_TOOLTIP
        fieldMaxIntensity->setToolTip(QApplication::translate("AddEditLightDialog", "<html><head/><body><p>0 to 100%. Must be equal to or greater than min. </p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        label_4->setText(QApplication::translate("AddEditLightDialog", "Transition Time", 0));
#ifndef QT_NO_TOOLTIP
        fieldTransitionTime->setToolTip(QApplication::translate("AddEditLightDialog", "<html><head/><body><p>Time in fast minutes to go from 0 to 100%</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        groupBox_2->setTitle(QApplication::translate("AddEditLightDialog", "Light Control", 0));
#ifndef QT_NO_TOOLTIP
        addControl->setToolTip(QApplication::translate("AddEditLightDialog", "<html><head/><body><p>Press to add a Light control to this light.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        addControl->setText(QApplication::translate("AddEditLightDialog", "Add Control", 0));
        status1->setText(QApplication::translate("AddEditLightDialog", "Select or enter data, then press Create for a new light , or press Cancel.", 0));
        status2->setText(QApplication::translate("AddEditLightDialog", "TextLabel", 0));
        btnCreate->setText(QApplication::translate("AddEditLightDialog", "Create", 0));
        btnUpdate->setText(QApplication::translate("AddEditLightDialog", "Update", 0));
        btnCancel->setText(QApplication::translate("AddEditLightDialog", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class AddEditLightDialog: public Ui_AddEditLightDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDEDITLIGHTDIALOG_H
