/********************************************************************************
** Form generated from reading UI file 'locoiodialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOCOIODIALOG_H
#define UI_LOCOIODIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
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
    QHBoxLayout *horizontalLayout_4;
    QLabel *lblCurrentAddress;
    QGroupBox *gbExtraOpCodes;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QCheckBox *chkExtra1;
    QCheckBox *chkExtra2;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *chkSpecialPorts;
    QCheckBox *chkModule;
    QCheckBox *chk4PosServo;
    QFormLayout *formLayout;
    QLabel *label_3;
    QLabel *lblFirmware;
    QLabel *label_4;
    QLabel *lblLocoBuffer;
    QPushButton *btnProbe;
    QPushButton *btnReadAll;
    QPushButton *btnCapture;
    QPushButton *btnSave;
    QVBoxLayout *verticalLayout_4;
    QCheckBox *chkInputStatus;
    QRadioButton *rbCheckAll;
    QRadioButton *rbCheckBlockAndPoints;
    QRadioButton *rbCheckBlock;
    QLabel *lblJP1;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *rbFixCodeForPBs;
    QRadioButton *rbAltCodeForPBs;
    QVBoxLayout *verticalLayout;
    QCheckBox *chkHex;
    QCheckBox *chkAllowEdit;
    QPushButton *btnSetDefaults;
    QPushButton *btnWriteAll;
    QPushButton *btnRestore;
    QPushButton *btnChangeAddress;
    QPushButton *btnHide;
    QLabel *lblStatus;
    QTableWidget *tableWidget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lblUnitAddr;
    QLineEdit *edNewAddr;

    void setupUi(QDialog *LocoIODialog)
    {
        if (LocoIODialog->objectName().isEmpty())
            LocoIODialog->setObjectName(QStringLiteral("LocoIODialog"));
        LocoIODialog->resize(886, 630);
        QFont font;
        font.setPointSize(7);
        LocoIODialog->setFont(font);
        LocoIODialog->setSizeGripEnabled(true);
        gridLayout = new QGridLayout(LocoIODialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(2);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        lblCurrentAddress = new QLabel(LocoIODialog);
        lblCurrentAddress->setObjectName(QStringLiteral("lblCurrentAddress"));

        horizontalLayout_4->addWidget(lblCurrentAddress);


        gridLayout->addLayout(horizontalLayout_4, 1, 0, 1, 1);

        gbExtraOpCodes = new QGroupBox(LocoIODialog);
        gbExtraOpCodes->setObjectName(QStringLiteral("gbExtraOpCodes"));
        horizontalLayout_2 = new QHBoxLayout(gbExtraOpCodes);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        chkExtra1 = new QCheckBox(gbExtraOpCodes);
        chkExtra1->setObjectName(QStringLiteral("chkExtra1"));

        horizontalLayout->addWidget(chkExtra1);

        chkExtra2 = new QCheckBox(gbExtraOpCodes);
        chkExtra2->setObjectName(QStringLiteral("chkExtra2"));

        horizontalLayout->addWidget(chkExtra2);


        horizontalLayout_2->addLayout(horizontalLayout);


        gridLayout->addWidget(gbExtraOpCodes, 1, 4, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(1);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        chkSpecialPorts = new QCheckBox(LocoIODialog);
        chkSpecialPorts->setObjectName(QStringLiteral("chkSpecialPorts"));

        verticalLayout_2->addWidget(chkSpecialPorts);

        chkModule = new QCheckBox(LocoIODialog);
        chkModule->setObjectName(QStringLiteral("chkModule"));
        chkModule->setEnabled(false);

        verticalLayout_2->addWidget(chkModule);

        chk4PosServo = new QCheckBox(LocoIODialog);
        chk4PosServo->setObjectName(QStringLiteral("chk4PosServo"));

        verticalLayout_2->addWidget(chk4PosServo);


        gridLayout->addLayout(verticalLayout_2, 1, 5, 1, 1);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setHorizontalSpacing(2);
        formLayout->setVerticalSpacing(2);
        label_3 = new QLabel(LocoIODialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_3);

        lblFirmware = new QLabel(LocoIODialog);
        lblFirmware->setObjectName(QStringLiteral("lblFirmware"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lblFirmware);

        label_4 = new QLabel(LocoIODialog);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_4);

        lblLocoBuffer = new QLabel(LocoIODialog);
        lblLocoBuffer->setObjectName(QStringLiteral("lblLocoBuffer"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lblLocoBuffer);


        gridLayout->addLayout(formLayout, 1, 6, 1, 1);

        btnProbe = new QPushButton(LocoIODialog);
        btnProbe->setObjectName(QStringLiteral("btnProbe"));

        gridLayout->addWidget(btnProbe, 2, 0, 1, 1);

        btnReadAll = new QPushButton(LocoIODialog);
        btnReadAll->setObjectName(QStringLiteral("btnReadAll"));

        gridLayout->addWidget(btnReadAll, 2, 1, 1, 1);

        btnCapture = new QPushButton(LocoIODialog);
        btnCapture->setObjectName(QStringLiteral("btnCapture"));

        gridLayout->addWidget(btnCapture, 2, 2, 1, 1);

        btnSave = new QPushButton(LocoIODialog);
        btnSave->setObjectName(QStringLiteral("btnSave"));

        gridLayout->addWidget(btnSave, 2, 3, 1, 1);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(1);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        chkInputStatus = new QCheckBox(LocoIODialog);
        chkInputStatus->setObjectName(QStringLiteral("chkInputStatus"));

        verticalLayout_4->addWidget(chkInputStatus);

        rbCheckAll = new QRadioButton(LocoIODialog);
        rbCheckAll->setObjectName(QStringLiteral("rbCheckAll"));

        verticalLayout_4->addWidget(rbCheckAll);

        rbCheckBlockAndPoints = new QRadioButton(LocoIODialog);
        rbCheckBlockAndPoints->setObjectName(QStringLiteral("rbCheckBlockAndPoints"));

        verticalLayout_4->addWidget(rbCheckBlockAndPoints);

        rbCheckBlock = new QRadioButton(LocoIODialog);
        rbCheckBlock->setObjectName(QStringLiteral("rbCheckBlock"));

        verticalLayout_4->addWidget(rbCheckBlock);

        lblJP1 = new QLabel(LocoIODialog);
        lblJP1->setObjectName(QStringLiteral("lblJP1"));

        verticalLayout_4->addWidget(lblJP1);


        gridLayout->addLayout(verticalLayout_4, 2, 4, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(2);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        rbFixCodeForPBs = new QRadioButton(LocoIODialog);
        rbFixCodeForPBs->setObjectName(QStringLiteral("rbFixCodeForPBs"));

        verticalLayout_3->addWidget(rbFixCodeForPBs);

        rbAltCodeForPBs = new QRadioButton(LocoIODialog);
        rbAltCodeForPBs->setObjectName(QStringLiteral("rbAltCodeForPBs"));

        verticalLayout_3->addWidget(rbAltCodeForPBs);


        gridLayout->addLayout(verticalLayout_3, 2, 5, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        chkHex = new QCheckBox(LocoIODialog);
        chkHex->setObjectName(QStringLiteral("chkHex"));
        chkHex->setChecked(true);

        verticalLayout->addWidget(chkHex);

        chkAllowEdit = new QCheckBox(LocoIODialog);
        chkAllowEdit->setObjectName(QStringLiteral("chkAllowEdit"));

        verticalLayout->addWidget(chkAllowEdit);


        gridLayout->addLayout(verticalLayout, 2, 6, 1, 1);

        btnSetDefaults = new QPushButton(LocoIODialog);
        btnSetDefaults->setObjectName(QStringLiteral("btnSetDefaults"));

        gridLayout->addWidget(btnSetDefaults, 3, 0, 1, 1);

        btnWriteAll = new QPushButton(LocoIODialog);
        btnWriteAll->setObjectName(QStringLiteral("btnWriteAll"));

        gridLayout->addWidget(btnWriteAll, 3, 1, 1, 1);

        btnRestore = new QPushButton(LocoIODialog);
        btnRestore->setObjectName(QStringLiteral("btnRestore"));

        gridLayout->addWidget(btnRestore, 3, 2, 1, 1);

        btnChangeAddress = new QPushButton(LocoIODialog);
        btnChangeAddress->setObjectName(QStringLiteral("btnChangeAddress"));
        QFont font1;
        font1.setPointSize(8);
        font1.setBold(true);
        font1.setItalic(true);
        font1.setWeight(75);
        btnChangeAddress->setFont(font1);

        gridLayout->addWidget(btnChangeAddress, 3, 3, 1, 1);

        btnHide = new QPushButton(LocoIODialog);
        btnHide->setObjectName(QStringLiteral("btnHide"));

        gridLayout->addWidget(btnHide, 3, 5, 1, 1);

        lblStatus = new QLabel(LocoIODialog);
        lblStatus->setObjectName(QStringLiteral("lblStatus"));
        lblStatus->setFrameShape(QFrame::NoFrame);

        gridLayout->addWidget(lblStatus, 4, 0, 1, 1);

        tableWidget = new QTableWidget(LocoIODialog);
        if (tableWidget->columnCount() < 17)
            tableWidget->setColumnCount(17);
        if (tableWidget->rowCount() < 5)
            tableWidget->setRowCount(5);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setBaseSize(QSize(800, 400));
        tableWidget->setRowCount(5);
        tableWidget->setColumnCount(17);
        tableWidget->horizontalHeader()->setStretchLastSection(true);
        tableWidget->verticalHeader()->setVisible(false);

        gridLayout->addWidget(tableWidget, 0, 0, 1, 7);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        lblUnitAddr = new QLabel(LocoIODialog);
        lblUnitAddr->setObjectName(QStringLiteral("lblUnitAddr"));
        lblUnitAddr->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(lblUnitAddr);

        edNewAddr = new QLineEdit(LocoIODialog);
        edNewAddr->setObjectName(QStringLiteral("edNewAddr"));
        edNewAddr->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_3->addWidget(edNewAddr);


        gridLayout->addLayout(horizontalLayout_3, 1, 2, 1, 2);


        retranslateUi(LocoIODialog);

        QMetaObject::connectSlotsByName(LocoIODialog);
    } // setupUi

    void retranslateUi(QDialog *LocoIODialog)
    {
        LocoIODialog->setWindowTitle(QApplication::translate("LocoIODialog", "Dialog", 0));
        lblCurrentAddress->setText(QApplication::translate("LocoIODialog", "Current address: 0x51/1", 0));
        gbExtraOpCodes->setTitle(QApplication::translate("LocoIODialog", "Extra Op Codes", 0));
        chkExtra1->setText(QApplication::translate("LocoIODialog", "1", 0));
        chkExtra2->setText(QApplication::translate("LocoIODialog", "2", 0));
        chkSpecialPorts->setText(QApplication::translate("LocoIODialog", "Special Ports", 0));
        chkModule->setText(QApplication::translate("LocoIODialog", "Servo", 0));
        chk4PosServo->setText(QApplication::translate("LocoIODialog", "4 Position Servo", 0));
        label_3->setText(QApplication::translate("LocoIODialog", "Firmware:", 0));
        lblFirmware->setText(QApplication::translate("LocoIODialog", "<unknown>", 0));
        label_4->setText(QApplication::translate("LocoIODialog", "<html><head/><body><p>LocoBuffer:</p></body></html>", 0));
        lblLocoBuffer->setText(QApplication::translate("LocoIODialog", "<unknown>", 0));
#ifndef QT_NO_TOOLTIP
        btnProbe->setToolTip(QApplication::translate("LocoIODialog", "<html><head/><body><p>Find the addresses of all LocoIo, LocoBooster and LocoServo modules currently connected to LocoNet.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        btnProbe->setText(QApplication::translate("LocoIODialog", "Probe", 0));
#ifndef QT_NO_TOOLTIP
        btnReadAll->setToolTip(QApplication::translate("LocoIODialog", "<html><head/><body><p>Read all the configuration variables for the selected module address. </p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        btnReadAll->setText(QApplication::translate("LocoIODialog", "Read All", 0));
        btnCapture->setText(QApplication::translate("LocoIODialog", "Capture", 0));
#ifndef QT_NO_TOOLTIP
        btnSave->setToolTip(QApplication::translate("LocoIODialog", "<html><head/><body><p>Save all configuration settings for a module.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        btnSave->setText(QApplication::translate("LocoIODialog", "Save Module", 0));
        chkInputStatus->setText(QApplication::translate("LocoIODialog", "inputStatus by Power ON and GPON", 0));
        rbCheckAll->setText(QApplication::translate("LocoIODialog", "Check All Inputs", 0));
        rbCheckBlockAndPoints->setText(QApplication::translate("LocoIODialog", "Check Block and Point Feedbacks", 0));
        rbCheckBlock->setText(QApplication::translate("LocoIODialog", "Check Block Feedbacks", 0));
        lblJP1->setText(QApplication::translate("LocoIODialog", "Set jumper JP1 for this module", 0));
        rbFixCodeForPBs->setText(QApplication::translate("LocoIODialog", "Fix code for PBs", 0));
        rbAltCodeForPBs->setText(QApplication::translate("LocoIODialog", "Alt code for PBs", 0));
        chkHex->setText(QApplication::translate("LocoIODialog", "Display values in hex", 0));
#ifndef QT_NO_TOOLTIP
        chkAllowEdit->setToolTip(QApplication::translate("LocoIODialog", "<html><head/><body><p>Check to allow editing of configuration, Value 1 and Value 2 CVs.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        chkAllowEdit->setText(QApplication::translate("LocoIODialog", "Allow edits", 0));
#ifndef QT_NO_TOOLTIP
        btnSetDefaults->setToolTip(QApplication::translate("LocoIODialog", "<html><head/><body><p>Set default values for all the CV's in the module. </p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        btnSetDefaults->setText(QApplication::translate("LocoIODialog", "Set Defaults", 0));
        btnWriteAll->setText(QApplication::translate("LocoIODialog", "Write all", 0));
#ifndef QT_NO_TOOLTIP
        btnRestore->setToolTip(QApplication::translate("LocoIODialog", "<html><head/><body><p>Restore a previously saved set of configuration settings for a module.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        btnRestore->setText(QApplication::translate("LocoIODialog", "Restore module", 0));
#ifndef QT_NO_TOOLTIP
        btnChangeAddress->setToolTip(QApplication::translate("LocoIODialog", "<html><head/><body><p><span style=\" font-weight:400; font-style:normal;\">Change the address of a module. </span><span style=\" font-style:normal;\">Warning! If the old address is 00/00, this command will set the address of all LocoIO, LocoBooster and LocoServo modules currently connected to the Loconet!</span></p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        btnChangeAddress->setText(QApplication::translate("LocoIODialog", "Change Address", 0));
        btnHide->setText(QApplication::translate("LocoIODialog", "Hide", 0));
        lblStatus->setText(QApplication::translate("LocoIODialog", "status", 0));
        lblUnitAddr->setText(QApplication::translate("LocoIODialog", "New Unit Address:", 0));
    } // retranslateUi

};

namespace Ui {
    class LocoIODialog: public Ui_LocoIODialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOCOIODIALOG_H
