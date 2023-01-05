/********************************************************************************
** Form generated from reading UI file 'locoiodialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOCOIODIALOG_H
#define UI_LOCOIODIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_LocoIODialog
{
public:
    QGridLayout *gridLayout;
    QPushButton *btnChangeAddress;
    QVBoxLayout *verticalLayout_4;
    QCheckBox *chkInputStatus;
    QRadioButton *rbCheckAll;
    QRadioButton *rbCheckBlockAndPoints;
    QRadioButton *rbCheckBlock;
    QLabel *lblJP1;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *rbFixCodeForPBs;
    QRadioButton *rbAltCodeForPBs;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lblUnitAddr;
    QLineEdit *edNewAddr;
    QPushButton *btnSave;
    QPushButton *btnCapture;
    QVBoxLayout *verticalLayout;
    QCheckBox *chkHex;
    QCheckBox *chkAllowEdit;
    QPushButton *btnProbe;
    QPushButton *btnWriteAll;
    QTableWidget *tableWidget;
    QLabel *lblStatus;
    QPushButton *btnHide;
    QGroupBox *gbExtraOpCodes;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QCheckBox *chkExtra1;
    QCheckBox *chkExtra2;
    QPushButton *btnSetDefaults;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *chkSpecialPorts;
    QCheckBox *chkModule;
    QCheckBox *chk4PosServo;
    QPushButton *btnRestore;
    QPushButton *btnReadAll;
    QFormLayout *formLayout;
    QLabel *label_3;
    QLabel *lblFirmware;
    QLabel *label_4;
    QLabel *lblLocoBuffer;
    QHBoxLayout *horizontalLayout_4;
    QLabel *lblCurrentAddress;

    void setupUi(QDialog *LocoIODialog)
    {
        if (LocoIODialog->objectName().isEmpty())
            LocoIODialog->setObjectName(QString::fromUtf8("LocoIODialog"));
        LocoIODialog->resize(886, 630);
        QFont font;
        font.setPointSize(7);
        LocoIODialog->setFont(font);
        LocoIODialog->setSizeGripEnabled(true);
        gridLayout = new QGridLayout(LocoIODialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        btnChangeAddress = new QPushButton(LocoIODialog);
        btnChangeAddress->setObjectName(QString::fromUtf8("btnChangeAddress"));
        QFont font1;
        font1.setPointSize(8);
        font1.setBold(true);
        font1.setItalic(true);
        font1.setWeight(75);
        btnChangeAddress->setFont(font1);

        gridLayout->addWidget(btnChangeAddress, 3, 3, 1, 1);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(1);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        chkInputStatus = new QCheckBox(LocoIODialog);
        chkInputStatus->setObjectName(QString::fromUtf8("chkInputStatus"));

        verticalLayout_4->addWidget(chkInputStatus);

        rbCheckAll = new QRadioButton(LocoIODialog);
        rbCheckAll->setObjectName(QString::fromUtf8("rbCheckAll"));

        verticalLayout_4->addWidget(rbCheckAll);

        rbCheckBlockAndPoints = new QRadioButton(LocoIODialog);
        rbCheckBlockAndPoints->setObjectName(QString::fromUtf8("rbCheckBlockAndPoints"));

        verticalLayout_4->addWidget(rbCheckBlockAndPoints);

        rbCheckBlock = new QRadioButton(LocoIODialog);
        rbCheckBlock->setObjectName(QString::fromUtf8("rbCheckBlock"));

        verticalLayout_4->addWidget(rbCheckBlock);

        lblJP1 = new QLabel(LocoIODialog);
        lblJP1->setObjectName(QString::fromUtf8("lblJP1"));

        verticalLayout_4->addWidget(lblJP1);


        gridLayout->addLayout(verticalLayout_4, 2, 4, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        rbFixCodeForPBs = new QRadioButton(LocoIODialog);
        rbFixCodeForPBs->setObjectName(QString::fromUtf8("rbFixCodeForPBs"));

        verticalLayout_3->addWidget(rbFixCodeForPBs);

        rbAltCodeForPBs = new QRadioButton(LocoIODialog);
        rbAltCodeForPBs->setObjectName(QString::fromUtf8("rbAltCodeForPBs"));

        verticalLayout_3->addWidget(rbAltCodeForPBs);


        gridLayout->addLayout(verticalLayout_3, 2, 5, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        lblUnitAddr = new QLabel(LocoIODialog);
        lblUnitAddr->setObjectName(QString::fromUtf8("lblUnitAddr"));
        lblUnitAddr->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(lblUnitAddr);

        edNewAddr = new QLineEdit(LocoIODialog);
        edNewAddr->setObjectName(QString::fromUtf8("edNewAddr"));
        edNewAddr->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_3->addWidget(edNewAddr);


        gridLayout->addLayout(horizontalLayout_3, 1, 2, 1, 2);

        btnSave = new QPushButton(LocoIODialog);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));

        gridLayout->addWidget(btnSave, 2, 3, 1, 1);

        btnCapture = new QPushButton(LocoIODialog);
        btnCapture->setObjectName(QString::fromUtf8("btnCapture"));

        gridLayout->addWidget(btnCapture, 2, 2, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        chkHex = new QCheckBox(LocoIODialog);
        chkHex->setObjectName(QString::fromUtf8("chkHex"));
        chkHex->setChecked(true);

        verticalLayout->addWidget(chkHex);

        chkAllowEdit = new QCheckBox(LocoIODialog);
        chkAllowEdit->setObjectName(QString::fromUtf8("chkAllowEdit"));

        verticalLayout->addWidget(chkAllowEdit);


        gridLayout->addLayout(verticalLayout, 2, 6, 1, 1);

        btnProbe = new QPushButton(LocoIODialog);
        btnProbe->setObjectName(QString::fromUtf8("btnProbe"));

        gridLayout->addWidget(btnProbe, 2, 0, 1, 1);

        btnWriteAll = new QPushButton(LocoIODialog);
        btnWriteAll->setObjectName(QString::fromUtf8("btnWriteAll"));

        gridLayout->addWidget(btnWriteAll, 3, 1, 1, 1);

        tableWidget = new QTableWidget(LocoIODialog);
        if (tableWidget->columnCount() < 17)
            tableWidget->setColumnCount(17);
        if (tableWidget->rowCount() < 5)
            tableWidget->setRowCount(5);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setBaseSize(QSize(800, 400));
        tableWidget->setRowCount(5);
        tableWidget->setColumnCount(17);
        tableWidget->horizontalHeader()->setStretchLastSection(true);
        tableWidget->verticalHeader()->setVisible(false);

        gridLayout->addWidget(tableWidget, 0, 0, 1, 7);

        lblStatus = new QLabel(LocoIODialog);
        lblStatus->setObjectName(QString::fromUtf8("lblStatus"));
        lblStatus->setFrameShape(QFrame::NoFrame);

        gridLayout->addWidget(lblStatus, 4, 0, 1, 1);

        btnHide = new QPushButton(LocoIODialog);
        btnHide->setObjectName(QString::fromUtf8("btnHide"));

        gridLayout->addWidget(btnHide, 3, 5, 1, 1);

        gbExtraOpCodes = new QGroupBox(LocoIODialog);
        gbExtraOpCodes->setObjectName(QString::fromUtf8("gbExtraOpCodes"));
        horizontalLayout_2 = new QHBoxLayout(gbExtraOpCodes);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        chkExtra1 = new QCheckBox(gbExtraOpCodes);
        chkExtra1->setObjectName(QString::fromUtf8("chkExtra1"));

        horizontalLayout->addWidget(chkExtra1);

        chkExtra2 = new QCheckBox(gbExtraOpCodes);
        chkExtra2->setObjectName(QString::fromUtf8("chkExtra2"));

        horizontalLayout->addWidget(chkExtra2);


        horizontalLayout_2->addLayout(horizontalLayout);


        gridLayout->addWidget(gbExtraOpCodes, 1, 4, 1, 1);

        btnSetDefaults = new QPushButton(LocoIODialog);
        btnSetDefaults->setObjectName(QString::fromUtf8("btnSetDefaults"));

        gridLayout->addWidget(btnSetDefaults, 3, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(1);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        chkSpecialPorts = new QCheckBox(LocoIODialog);
        chkSpecialPorts->setObjectName(QString::fromUtf8("chkSpecialPorts"));

        verticalLayout_2->addWidget(chkSpecialPorts);

        chkModule = new QCheckBox(LocoIODialog);
        chkModule->setObjectName(QString::fromUtf8("chkModule"));
        chkModule->setEnabled(false);

        verticalLayout_2->addWidget(chkModule);

        chk4PosServo = new QCheckBox(LocoIODialog);
        chk4PosServo->setObjectName(QString::fromUtf8("chk4PosServo"));

        verticalLayout_2->addWidget(chk4PosServo);


        gridLayout->addLayout(verticalLayout_2, 1, 5, 1, 1);

        btnRestore = new QPushButton(LocoIODialog);
        btnRestore->setObjectName(QString::fromUtf8("btnRestore"));

        gridLayout->addWidget(btnRestore, 3, 2, 1, 1);

        btnReadAll = new QPushButton(LocoIODialog);
        btnReadAll->setObjectName(QString::fromUtf8("btnReadAll"));

        gridLayout->addWidget(btnReadAll, 2, 1, 1, 1);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setHorizontalSpacing(2);
        formLayout->setVerticalSpacing(2);
        label_3 = new QLabel(LocoIODialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_3);

        lblFirmware = new QLabel(LocoIODialog);
        lblFirmware->setObjectName(QString::fromUtf8("lblFirmware"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lblFirmware);

        label_4 = new QLabel(LocoIODialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_4);

        lblLocoBuffer = new QLabel(LocoIODialog);
        lblLocoBuffer->setObjectName(QString::fromUtf8("lblLocoBuffer"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lblLocoBuffer);


        gridLayout->addLayout(formLayout, 1, 6, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(2);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        lblCurrentAddress = new QLabel(LocoIODialog);
        lblCurrentAddress->setObjectName(QString::fromUtf8("lblCurrentAddress"));

        horizontalLayout_4->addWidget(lblCurrentAddress);


        gridLayout->addLayout(horizontalLayout_4, 1, 0, 1, 1);


        retranslateUi(LocoIODialog);

        QMetaObject::connectSlotsByName(LocoIODialog);
    } // setupUi

    void retranslateUi(QDialog *LocoIODialog)
    {
        LocoIODialog->setWindowTitle(QCoreApplication::translate("LocoIODialog", "Dialog", nullptr));
#if QT_CONFIG(tooltip)
        btnChangeAddress->setToolTip(QCoreApplication::translate("LocoIODialog", "<html><head/><body><p><span style=\" font-weight:400; font-style:normal;\">Change the address of a module. </span><span style=\" font-style:normal;\">Warning! If the old address is 00/00, this command will set the address of all LocoIO, LocoBooster and LocoServo modules currently connected to the Loconet!</span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        btnChangeAddress->setText(QCoreApplication::translate("LocoIODialog", "Change Address", nullptr));
        chkInputStatus->setText(QCoreApplication::translate("LocoIODialog", "inputStatus by Power ON and GPON", nullptr));
        rbCheckAll->setText(QCoreApplication::translate("LocoIODialog", "Check All Inputs", nullptr));
        rbCheckBlockAndPoints->setText(QCoreApplication::translate("LocoIODialog", "Check Block and Point Feedbacks", nullptr));
        rbCheckBlock->setText(QCoreApplication::translate("LocoIODialog", "Check Block Feedbacks", nullptr));
        lblJP1->setText(QCoreApplication::translate("LocoIODialog", "Set jumper JP1 for this module", nullptr));
        rbFixCodeForPBs->setText(QCoreApplication::translate("LocoIODialog", "Fix code for PBs", nullptr));
        rbAltCodeForPBs->setText(QCoreApplication::translate("LocoIODialog", "Alt code for PBs", nullptr));
        lblUnitAddr->setText(QCoreApplication::translate("LocoIODialog", "New Unit Address:", nullptr));
#if QT_CONFIG(tooltip)
        btnSave->setToolTip(QCoreApplication::translate("LocoIODialog", "<html><head/><body><p>Save all configuration settings for a module.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        btnSave->setText(QCoreApplication::translate("LocoIODialog", "Save Module", nullptr));
        btnCapture->setText(QCoreApplication::translate("LocoIODialog", "Capture", nullptr));
        chkHex->setText(QCoreApplication::translate("LocoIODialog", "Display values in hex", nullptr));
#if QT_CONFIG(tooltip)
        chkAllowEdit->setToolTip(QCoreApplication::translate("LocoIODialog", "<html><head/><body><p>Check to allow editing of configuration, Value 1 and Value 2 CVs.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        chkAllowEdit->setText(QCoreApplication::translate("LocoIODialog", "Allow edits", nullptr));
#if QT_CONFIG(tooltip)
        btnProbe->setToolTip(QCoreApplication::translate("LocoIODialog", "<html><head/><body><p>Find the addresses of all LocoIo, LocoBooster and LocoServo modules currently connected to LocoNet.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        btnProbe->setText(QCoreApplication::translate("LocoIODialog", "Probe", nullptr));
        btnWriteAll->setText(QCoreApplication::translate("LocoIODialog", "Write all", nullptr));
        lblStatus->setText(QCoreApplication::translate("LocoIODialog", "status", nullptr));
        btnHide->setText(QCoreApplication::translate("LocoIODialog", "Hide", nullptr));
        gbExtraOpCodes->setTitle(QCoreApplication::translate("LocoIODialog", "Extra Op Codes", nullptr));
        chkExtra1->setText(QCoreApplication::translate("LocoIODialog", "1", nullptr));
        chkExtra2->setText(QCoreApplication::translate("LocoIODialog", "2", nullptr));
#if QT_CONFIG(tooltip)
        btnSetDefaults->setToolTip(QCoreApplication::translate("LocoIODialog", "<html><head/><body><p>Set default values for all the CV's in the module. </p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        btnSetDefaults->setText(QCoreApplication::translate("LocoIODialog", "Set Defaults", nullptr));
        chkSpecialPorts->setText(QCoreApplication::translate("LocoIODialog", "Special Ports", nullptr));
        chkModule->setText(QCoreApplication::translate("LocoIODialog", "Servo", nullptr));
        chk4PosServo->setText(QCoreApplication::translate("LocoIODialog", "4 Position Servo", nullptr));
#if QT_CONFIG(tooltip)
        btnRestore->setToolTip(QCoreApplication::translate("LocoIODialog", "<html><head/><body><p>Restore a previously saved set of configuration settings for a module.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        btnRestore->setText(QCoreApplication::translate("LocoIODialog", "Restore module", nullptr));
#if QT_CONFIG(tooltip)
        btnReadAll->setToolTip(QCoreApplication::translate("LocoIODialog", "<html><head/><body><p>Read all the configuration variables for the selected module address. </p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        btnReadAll->setText(QCoreApplication::translate("LocoIODialog", "Read All", nullptr));
        label_3->setText(QCoreApplication::translate("LocoIODialog", "Firmware:", nullptr));
        lblFirmware->setText(QCoreApplication::translate("LocoIODialog", "<unknown>", nullptr));
        label_4->setText(QCoreApplication::translate("LocoIODialog", "<html><head/><body><p>LocoBuffer:</p></body></html>", nullptr));
        lblLocoBuffer->setText(QCoreApplication::translate("LocoIODialog", "<unknown>", nullptr));
        lblCurrentAddress->setText(QCoreApplication::translate("LocoIODialog", "Current address: 0x51/1", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LocoIODialog: public Ui_LocoIODialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOCOIODIALOG_H
