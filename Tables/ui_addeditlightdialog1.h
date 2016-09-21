/********************************************************************************
** Form generated from reading UI file 'addeditlightdialog1.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDEDITLIGHTDIALOG1_H
#define UI_ADDEDITLIGHTDIALOG1_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddEditLightDialog1
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_7;
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
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *AddEditLightDialog1)
    {
        if (AddEditLightDialog1->objectName().isEmpty())
            AddEditLightDialog1->setObjectName(QStringLiteral("AddEditLightDialog1"));
        AddEditLightDialog1->resize(800, 600);
        centralwidget = new QWidget(AddEditLightDialog1);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout_4 = new QVBoxLayout(centralwidget);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_6->addWidget(label_7);

        prefixBox = new QComboBox(centralwidget);
        prefixBox->setObjectName(QStringLiteral("prefixBox"));

        horizontalLayout_6->addWidget(prefixBox);

        addRangeBox = new QCheckBox(centralwidget);
        addRangeBox->setObjectName(QStringLiteral("addRangeBox"));

        horizontalLayout_6->addWidget(addRangeBox);


        verticalLayout_4->addLayout(horizontalLayout_6);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_3->addWidget(label_5);

        fieldHardwareAddress = new QLineEdit(centralwidget);
        fieldHardwareAddress->setObjectName(QStringLiteral("fieldHardwareAddress"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(fieldHardwareAddress->sizePolicy().hasHeightForWidth());
        fieldHardwareAddress->setSizePolicy(sizePolicy);
        fieldHardwareAddress->setInputMethodHints(Qt::ImhDigitsOnly|Qt::ImhPreferNumbers);
        fieldHardwareAddress->setMaxLength(4);

        horizontalLayout_3->addWidget(fieldHardwareAddress);

        lblNbrToAdd = new QLabel(centralwidget);
        lblNbrToAdd->setObjectName(QStringLiteral("lblNbrToAdd"));

        horizontalLayout_3->addWidget(lblNbrToAdd);

        fieldNumToAdd = new QSpinBox(centralwidget);
        fieldNumToAdd->setObjectName(QStringLiteral("fieldNumToAdd"));
        fieldNumToAdd->setMinimum(1);

        horizontalLayout_3->addWidget(fieldNumToAdd);


        verticalLayout_4->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_4->addWidget(label_6);

        userName = new QLineEdit(centralwidget);
        userName->setObjectName(QStringLiteral("userName"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(userName->sizePolicy().hasHeightForWidth());
        userName->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(userName);


        verticalLayout_4->addLayout(horizontalLayout_4);

        groupBox = new QGroupBox(centralwidget);
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
        fieldMaxIntensity->setValue(1);

        horizontalLayout->addWidget(fieldMaxIntensity);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout->addWidget(label_4);

        fieldTransitionTime = new QDoubleSpinBox(groupBox);
        fieldTransitionTime->setObjectName(QStringLiteral("fieldTransitionTime"));

        horizontalLayout->addWidget(fieldTransitionTime);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout_4->addWidget(groupBox);

        groupBox_2 = new QGroupBox(centralwidget);
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


        verticalLayout_4->addWidget(groupBox_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        btnCreate = new QPushButton(centralwidget);
        btnCreate->setObjectName(QStringLiteral("btnCreate"));
        sizePolicy2.setHeightForWidth(btnCreate->sizePolicy().hasHeightForWidth());
        btnCreate->setSizePolicy(sizePolicy2);

        horizontalLayout_5->addWidget(btnCreate);

        btnUpdate = new QPushButton(centralwidget);
        btnUpdate->setObjectName(QStringLiteral("btnUpdate"));
        sizePolicy2.setHeightForWidth(btnUpdate->sizePolicy().hasHeightForWidth());
        btnUpdate->setSizePolicy(sizePolicy2);

        horizontalLayout_5->addWidget(btnUpdate);

        btnCancel = new QPushButton(centralwidget);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));
        sizePolicy2.setHeightForWidth(btnCancel->sizePolicy().hasHeightForWidth());
        btnCancel->setSizePolicy(sizePolicy2);

        horizontalLayout_5->addWidget(btnCancel);


        verticalLayout_4->addLayout(horizontalLayout_5);

        AddEditLightDialog1->setCentralWidget(centralwidget);
        menubar = new QMenuBar(AddEditLightDialog1);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 25));
        AddEditLightDialog1->setMenuBar(menubar);
        statusbar = new QStatusBar(AddEditLightDialog1);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        AddEditLightDialog1->setStatusBar(statusbar);
        toolBar = new QToolBar(AddEditLightDialog1);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        AddEditLightDialog1->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(AddEditLightDialog1);

        QMetaObject::connectSlotsByName(AddEditLightDialog1);
    } // setupUi

    void retranslateUi(QMainWindow *AddEditLightDialog1)
    {
        AddEditLightDialog1->setWindowTitle(QApplication::translate("AddEditLightDialog1", "MainWindow", 0));
        label_7->setText(QApplication::translate("AddEditLightDialog1", "System:", 0));
        prefixBox->clear();
        prefixBox->insertItems(0, QStringList()
         << QApplication::translate("AddEditLightDialog1", "Internal", 0)
        );
#ifndef QT_NO_TOOLTIP
        prefixBox->setToolTip(QApplication::translate("AddEditLightDialog1", "<html><head/><body><p>Select a system for the new light.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        addRangeBox->setToolTip(QApplication::translate("AddEditLightDialog1", "<html><head/><body><p>Check to add more than one Light with sequential addresses.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        addRangeBox->setText(QApplication::translate("AddEditLightDialog1", "Add a sequential range", 0));
        label_5->setText(QApplication::translate("AddEditLightDialog1", "Hardware Address:", 0));
#ifndef QT_NO_TOOLTIP
        fieldHardwareAddress->setToolTip(QApplication::translate("AddEditLightDialog1", "<html><head/><body><p>Enter a hardware address for a new Light; e.g. 13</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        lblNbrToAdd->setText(QApplication::translate("AddEditLightDialog1", "Number to add:", 0));
        label_6->setText(QApplication::translate("AddEditLightDialog1", "User Name:", 0));
#ifndef QT_NO_TOOLTIP
        userName->setToolTip(QApplication::translate("AddEditLightDialog1", "<html><head/><body><p>Enter user name for new Light, e.g. Jones House.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        groupBox->setTitle(QApplication::translate("AddEditLightDialog1", "Variable Intensity", 0));
        label_2->setText(QApplication::translate("AddEditLightDialog1", "Minimum Intensity", 0));
#ifndef QT_NO_TOOLTIP
        fieldMinIntensity->setToolTip(QApplication::translate("AddEditLightDialog1", "<html><head/><body><p>0 to 100%. Must be less than Max.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        label_3->setText(QApplication::translate("AddEditLightDialog1", "Maximum Intensity", 0));
#ifndef QT_NO_TOOLTIP
        fieldMaxIntensity->setToolTip(QApplication::translate("AddEditLightDialog1", "<html><head/><body><p>0 to 100%. Must be equal to or greater than min. </p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        label_4->setText(QApplication::translate("AddEditLightDialog1", "Transition Time", 0));
#ifndef QT_NO_TOOLTIP
        fieldTransitionTime->setToolTip(QApplication::translate("AddEditLightDialog1", "<html><head/><body><p>Time in fast minutes to go from 0 to 100%</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        groupBox_2->setTitle(QApplication::translate("AddEditLightDialog1", "Light Control", 0));
#ifndef QT_NO_TOOLTIP
        addControl->setToolTip(QApplication::translate("AddEditLightDialog1", "<html><head/><body><p>Press to add a Light control to this light.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        addControl->setText(QApplication::translate("AddEditLightDialog1", "Add Control", 0));
        status1->setText(QApplication::translate("AddEditLightDialog1", "Select or enter data, then press Create for a new light , or press Cancel.", 0));
        status2->setText(QApplication::translate("AddEditLightDialog1", "TextLabel", 0));
        btnCreate->setText(QApplication::translate("AddEditLightDialog1", "Create", 0));
        btnUpdate->setText(QApplication::translate("AddEditLightDialog1", "Update", 0));
        btnCancel->setText(QApplication::translate("AddEditLightDialog1", "Cancel", 0));
        toolBar->setWindowTitle(QApplication::translate("AddEditLightDialog1", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class AddEditLightDialog1: public Ui_AddEditLightDialog1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDEDITLIGHTDIALOG1_H
