/********************************************************************************
** Form generated from reading UI file 'locoioframe.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOCOIOFRAME_H
#define UI_LOCOIOFRAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LocoIOFrame
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *tableWidget;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QCheckBox *chkSpecialPorts;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *chkExtra1;
    QCheckBox *chkExtra2;
    QFrame *gbCheck;
    QVBoxLayout *verticalLayout_4;
    QCheckBox *chkInputStatus;
    QRadioButton *rbCheckAll;
    QRadioButton *rbCheckBlockAndPoints;
    QRadioButton *rbCheckBlock;
    QLabel *lblJP1;
    QVBoxLayout *verticalLayout;
    QCheckBox *chkAllowEdit;
    QCheckBox *chkHex;
    QFormLayout *formLayout;
    QLabel *label_3;
    QLabel *lblFirmware;
    QLabel *label_4;
    QLabel *lblLocoBuffer;
    QVBoxLayout *verticalLayout_5;
    QRadioButton *rbFixCodeForPBs;
    QRadioButton *rbAltCodeForPBs;
    QCheckBox *chk4PosServo;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lblAddressIn;
    QLineEdit *edAddrUnitIn;
    QLabel *label_2;
    QLineEdit *edAddrSubUnitIn;
    QPushButton *btnRead;
    QPushButton *btnReadAll;
    QHBoxLayout *horizontalLayout;
    QLabel *lblPic;
    QLineEdit *edPicVersion;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_6;
    QLabel *lblAddressOut;
    QLineEdit *edAddrUnitOut;
    QLabel *label_8;
    QLineEdit *edAddrSubUnitOut;
    QPushButton *pbWrite;
    QPushButton *btnWriteAll;
    QPushButton *pbClear;
    QPushButton *pbInit;
    QLabel *lblStatus;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *LocoIOFrame)
    {
        if (LocoIOFrame->objectName().isEmpty())
            LocoIOFrame->setObjectName(QLatin1String("LocoIOFrame"));
        LocoIOFrame->resize(886, 429);
        QFont font;
        font.setPointSize(7);
        LocoIOFrame->setFont(font);
        centralWidget = new QWidget(LocoIOFrame);
        centralWidget->setObjectName(QLatin1String("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setObjectName(QLatin1String("verticalLayout_2"));
        tableWidget = new QTableWidget(centralWidget);
        if (tableWidget->columnCount() < 17)
            tableWidget->setColumnCount(17);
        if (tableWidget->rowCount() < 5)
            tableWidget->setRowCount(5);
        tableWidget->setObjectName(QLatin1String("tableWidget"));
        tableWidget->setBaseSize(QSize(800, 400));
        tableWidget->setRowCount(5);
        tableWidget->setColumnCount(17);
        tableWidget->horizontalHeader()->setStretchLastSection(true);
        tableWidget->verticalHeader()->setVisible(false);

        verticalLayout_2->addWidget(tableWidget);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QLatin1String("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QLatin1String("gridLayout"));
        chkSpecialPorts = new QCheckBox(groupBox);
        chkSpecialPorts->setObjectName(QLatin1String("chkSpecialPorts"));
        chkSpecialPorts->setFont(font);
        chkSpecialPorts->setStyleSheet(QLatin1String("QCheckBox {background-color: lightgray;}\n"
""));

        gridLayout->addWidget(chkSpecialPorts, 0, 0, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QLatin1String("verticalLayout_3"));
        chkExtra1 = new QCheckBox(groupBox);
        chkExtra1->setObjectName(QLatin1String("chkExtra1"));
        chkExtra1->setFont(font);
        chkExtra1->setStyleSheet(QLatin1String("QCheckBox {background-color: rgb(120, 220, 238); }"));

        verticalLayout_3->addWidget(chkExtra1);

        chkExtra2 = new QCheckBox(groupBox);
        chkExtra2->setObjectName(QLatin1String("chkExtra2"));
        chkExtra2->setFont(font);
        chkExtra2->setStyleSheet(QLatin1String("QCheckBox {background-color: rgb(240, 178, 105); }"));

        verticalLayout_3->addWidget(chkExtra2);


        gridLayout->addLayout(verticalLayout_3, 0, 1, 2, 1);

        gbCheck = new QFrame(groupBox);
        gbCheck->setObjectName(QLatin1String("gbCheck"));
        gbCheck->setFrameShape(QFrame::Panel);
        verticalLayout_4 = new QVBoxLayout(gbCheck);
        verticalLayout_4->setSpacing(1);
        verticalLayout_4->setObjectName(QLatin1String("verticalLayout_4"));
        chkInputStatus = new QCheckBox(gbCheck);
        chkInputStatus->setObjectName(QLatin1String("chkInputStatus"));

        verticalLayout_4->addWidget(chkInputStatus);

        rbCheckAll = new QRadioButton(gbCheck);
        rbCheckAll->setObjectName(QLatin1String("rbCheckAll"));

        verticalLayout_4->addWidget(rbCheckAll);

        rbCheckBlockAndPoints = new QRadioButton(gbCheck);
        rbCheckBlockAndPoints->setObjectName(QLatin1String("rbCheckBlockAndPoints"));

        verticalLayout_4->addWidget(rbCheckBlockAndPoints);

        rbCheckBlock = new QRadioButton(gbCheck);
        rbCheckBlock->setObjectName(QLatin1String("rbCheckBlock"));

        verticalLayout_4->addWidget(rbCheckBlock);

        lblJP1 = new QLabel(gbCheck);
        lblJP1->setObjectName(QLatin1String("lblJP1"));

        verticalLayout_4->addWidget(lblJP1);


        gridLayout->addWidget(gbCheck, 0, 2, 4, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QLatin1String("verticalLayout"));
        chkAllowEdit = new QCheckBox(groupBox);
        chkAllowEdit->setObjectName(QLatin1String("chkAllowEdit"));

        verticalLayout->addWidget(chkAllowEdit);

        chkHex = new QCheckBox(groupBox);
        chkHex->setObjectName(QLatin1String("chkHex"));
        chkHex->setChecked(true);

        verticalLayout->addWidget(chkHex);


        gridLayout->addLayout(verticalLayout, 1, 3, 3, 1);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QLatin1String("formLayout"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QLatin1String("label_3"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_3);

        lblFirmware = new QLabel(groupBox);
        lblFirmware->setObjectName(QLatin1String("lblFirmware"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lblFirmware);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QLatin1String("label_4"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_4);

        lblLocoBuffer = new QLabel(groupBox);
        lblLocoBuffer->setObjectName(QLatin1String("lblLocoBuffer"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lblLocoBuffer);


        gridLayout->addLayout(formLayout, 1, 4, 2, 1);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QLatin1String("verticalLayout_5"));
        rbFixCodeForPBs = new QRadioButton(groupBox);
        rbFixCodeForPBs->setObjectName(QLatin1String("rbFixCodeForPBs"));

        verticalLayout_5->addWidget(rbFixCodeForPBs);

        rbAltCodeForPBs = new QRadioButton(groupBox);
        rbAltCodeForPBs->setObjectName(QLatin1String("rbAltCodeForPBs"));

        verticalLayout_5->addWidget(rbAltCodeForPBs);


        gridLayout->addLayout(verticalLayout_5, 2, 0, 2, 2);

        chk4PosServo = new QCheckBox(groupBox);
        chk4PosServo->setObjectName(QLatin1String("chk4PosServo"));

        gridLayout->addWidget(chk4PosServo, 3, 4, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QLatin1String("horizontalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QLatin1String("horizontalLayout_2"));
        lblAddressIn = new QLabel(groupBox);
        lblAddressIn->setObjectName(QLatin1String("lblAddressIn"));
        QFont font1;
        lblAddressIn->setFont(font1);
        lblAddressIn->setStyleSheet(QLatin1String("QLabel {color:red;}"));

        horizontalLayout_2->addWidget(lblAddressIn);

        edAddrUnitIn = new QLineEdit(groupBox);
        edAddrUnitIn->setObjectName(QLatin1String("edAddrUnitIn"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(edAddrUnitIn->sizePolicy().hasHeightForWidth());
        edAddrUnitIn->setSizePolicy(sizePolicy);
        edAddrUnitIn->setMaximumSize(QSize(31, 16777215));
        edAddrUnitIn->setStyleSheet(QLatin1String("QLineEdit {background-color:rgb(214, 249, 222);}"));
        edAddrUnitIn->setReadOnly(false);

        horizontalLayout_2->addWidget(edAddrUnitIn);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QLatin1String("label_2"));
        label_2->setFont(font1);
        label_2->setStyleSheet(QLatin1String("QLabel {color:red;}"));

        horizontalLayout_2->addWidget(label_2);

        edAddrSubUnitIn = new QLineEdit(groupBox);
        edAddrSubUnitIn->setObjectName(QLatin1String("edAddrSubUnitIn"));
        sizePolicy.setHeightForWidth(edAddrSubUnitIn->sizePolicy().hasHeightForWidth());
        edAddrSubUnitIn->setSizePolicy(sizePolicy);
        edAddrSubUnitIn->setMaximumSize(QSize(31, 16777215));
        edAddrSubUnitIn->setStyleSheet(QLatin1String("QLineEdit {background-color:rgb(214, 249, 222);}"));
        edAddrSubUnitIn->setReadOnly(false);

        horizontalLayout_2->addWidget(edAddrSubUnitIn);

        btnRead = new QPushButton(groupBox);
        btnRead->setObjectName(QLatin1String("btnRead"));
        sizePolicy.setHeightForWidth(btnRead->sizePolicy().hasHeightForWidth());
        btnRead->setSizePolicy(sizePolicy);
        btnRead->setMaximumSize(QSize(30, 16777215));

        horizontalLayout_2->addWidget(btnRead);

        btnReadAll = new QPushButton(groupBox);
        btnReadAll->setObjectName(QLatin1String("btnReadAll"));
        sizePolicy.setHeightForWidth(btnReadAll->sizePolicy().hasHeightForWidth());
        btnReadAll->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(btnReadAll);


        horizontalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QLatin1String("horizontalLayout"));
        lblPic = new QLabel(groupBox);
        lblPic->setObjectName(QLatin1String("lblPic"));
        lblPic->setFont(font);
        lblPic->setStyleSheet(QLatin1String("QLabel {color:red;}"));

        horizontalLayout->addWidget(lblPic);

        edPicVersion = new QLineEdit(groupBox);
        edPicVersion->setObjectName(QLatin1String("edPicVersion"));
        edPicVersion->setMaximumSize(QSize(40, 16777215));
        edPicVersion->setStyleSheet(QLatin1String("QLineEdit {background-color:rgb(214, 249, 222);}"));
        edPicVersion->setReadOnly(true);

        horizontalLayout->addWidget(edPicVersion);


        horizontalLayout_3->addLayout(horizontalLayout);

        horizontalSpacer = new QSpacerItem(92, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QLatin1String("horizontalLayout_6"));
        lblAddressOut = new QLabel(groupBox);
        lblAddressOut->setObjectName(QLatin1String("lblAddressOut"));
        lblAddressOut->setFont(font1);
        lblAddressOut->setStyleSheet(QLatin1String("QLabel {color:red;}"));

        horizontalLayout_6->addWidget(lblAddressOut);

        edAddrUnitOut = new QLineEdit(groupBox);
        edAddrUnitOut->setObjectName(QLatin1String("edAddrUnitOut"));
        sizePolicy.setHeightForWidth(edAddrUnitOut->sizePolicy().hasHeightForWidth());
        edAddrUnitOut->setSizePolicy(sizePolicy);
        edAddrUnitOut->setMaximumSize(QSize(31, 16777215));
        edAddrUnitOut->setStyleSheet(QLatin1String("QLineEdit {background-color:rgb(214, 249, 222);}"));
        edAddrUnitOut->setMaxLength(2);
        edAddrUnitOut->setReadOnly(true);

        horizontalLayout_6->addWidget(edAddrUnitOut);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QLatin1String("label_8"));
        label_8->setFont(font1);
        label_8->setStyleSheet(QLatin1String("QLabel {color:red;}"));

        horizontalLayout_6->addWidget(label_8);

        edAddrSubUnitOut = new QLineEdit(groupBox);
        edAddrSubUnitOut->setObjectName(QLatin1String("edAddrSubUnitOut"));
        sizePolicy.setHeightForWidth(edAddrSubUnitOut->sizePolicy().hasHeightForWidth());
        edAddrSubUnitOut->setSizePolicy(sizePolicy);
        edAddrSubUnitOut->setMaximumSize(QSize(31, 16777215));
        edAddrSubUnitOut->setStyleSheet(QLatin1String("QLineEdit {background-color:rgb(214, 249, 222);}"));
        edAddrSubUnitOut->setMaxLength(2);
        edAddrSubUnitOut->setReadOnly(false);

        horizontalLayout_6->addWidget(edAddrSubUnitOut);

        pbWrite = new QPushButton(groupBox);
        pbWrite->setObjectName(QLatin1String("pbWrite"));
        pbWrite->setMaximumSize(QSize(30, 16777215));

        horizontalLayout_6->addWidget(pbWrite);

        btnWriteAll = new QPushButton(groupBox);
        btnWriteAll->setObjectName(QLatin1String("btnWriteAll"));

        horizontalLayout_6->addWidget(btnWriteAll);


        horizontalLayout_3->addLayout(horizontalLayout_6);

        pbClear = new QPushButton(groupBox);
        pbClear->setObjectName(QLatin1String("pbClear"));
        pbClear->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_3->addWidget(pbClear);

        pbInit = new QPushButton(groupBox);
        pbInit->setObjectName(QLatin1String("pbInit"));
        pbInit->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_3->addWidget(pbInit);


        gridLayout->addLayout(horizontalLayout_3, 4, 0, 1, 5);


        verticalLayout_2->addWidget(groupBox);

        lblStatus = new QLabel(centralWidget);
        lblStatus->setObjectName(QLatin1String("lblStatus"));

        verticalLayout_2->addWidget(lblStatus);

        LocoIOFrame->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(LocoIOFrame);
        menuBar->setObjectName(QLatin1String("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 886, 16));
        LocoIOFrame->setMenuBar(menuBar);

        retranslateUi(LocoIOFrame);

        QMetaObject::connectSlotsByName(LocoIOFrame);
    } // setupUi

    void retranslateUi(QMainWindow *LocoIOFrame)
    {
        LocoIOFrame->setWindowTitle(QApplication::translate("LocoIOFrame", "Dialog", nullptr));
        groupBox->setTitle(QApplication::translate("LocoIOFrame", "Module Settings", nullptr));
        chkSpecialPorts->setText(QApplication::translate("LocoIOFrame", "Special Ports", nullptr));
        chkExtra1->setText(QApplication::translate("LocoIOFrame", "Extra Opcode 1", nullptr));
        chkExtra2->setText(QApplication::translate("LocoIOFrame", "Extra Opcode 2", nullptr));
        chkInputStatus->setText(QApplication::translate("LocoIOFrame", "inputStatus by Power ON and GPON", nullptr));
        rbCheckAll->setText(QApplication::translate("LocoIOFrame", "Check All Inputs", nullptr));
        rbCheckBlockAndPoints->setText(QApplication::translate("LocoIOFrame", "Check Block and Point Feedbacks", nullptr));
        rbCheckBlock->setText(QApplication::translate("LocoIOFrame", "Check Block Feedbacks", nullptr));
        lblJP1->setText(QApplication::translate("LocoIOFrame", "Set jumper JP1 for this module", nullptr));
#ifndef QT_NO_TOOLTIP
        chkAllowEdit->setToolTip(QApplication::translate("LocoIOFrame", "<html><head/><body><p>Check to allow editing of configuration, Value 1 and Value 2 CVs.</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        chkAllowEdit->setText(QApplication::translate("LocoIOFrame", "Allow edits", nullptr));
        chkHex->setText(QApplication::translate("LocoIOFrame", "Display values in hex", nullptr));
        label_3->setText(QApplication::translate("LocoIOFrame", "Firmware:", nullptr));
        lblFirmware->setText(QApplication::translate("LocoIOFrame", "<unknown>", nullptr));
        label_4->setText(QApplication::translate("LocoIOFrame", "<html><head/><body><p>LocoBuffer:</p></body></html>", nullptr));
        lblLocoBuffer->setText(QApplication::translate("LocoIOFrame", "<unknown>", nullptr));
        rbFixCodeForPBs->setText(QApplication::translate("LocoIOFrame", "Fix code for Pushbuttons", nullptr));
        rbAltCodeForPBs->setText(QApplication::translate("LocoIOFrame", "Alternating code for Pushbuttons", nullptr));
        chk4PosServo->setText(QApplication::translate("LocoIOFrame", "4 Position Servo", nullptr));
        lblAddressIn->setText(QApplication::translate("LocoIOFrame", "Address", nullptr));
        label_2->setText(QApplication::translate("LocoIOFrame", "/", nullptr));
#ifndef QT_NO_TOOLTIP
        btnRead->setToolTip(QApplication::translate("LocoIOFrame", "<html><head/><body><p>Read SV0+1+2</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        btnRead->setText(QApplication::translate("LocoIOFrame", "R", nullptr));
#ifndef QT_NO_TOOLTIP
        btnReadAll->setToolTip(QApplication::translate("LocoIOFrame", "<html><head/><body><p>Read all the configuration variables for the selected module address. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        btnReadAll->setText(QApplication::translate("LocoIOFrame", "Read All", nullptr));
        lblPic->setText(QApplication::translate("LocoIOFrame", "Pic version", nullptr));
        lblAddressOut->setText(QApplication::translate("LocoIOFrame", "Address", nullptr));
        label_8->setText(QApplication::translate("LocoIOFrame", "/", nullptr));
        edAddrSubUnitOut->setText(QString());
        pbWrite->setText(QApplication::translate("LocoIOFrame", "W", nullptr));
        btnWriteAll->setText(QApplication::translate("LocoIOFrame", "Write all", nullptr));
#ifndef QT_NO_TOOLTIP
        pbClear->setToolTip(QApplication::translate("LocoIOFrame", "<html><head/><body><p>Clear all SV registers</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        pbClear->setText(QApplication::translate("LocoIOFrame", "Clear", nullptr));
#ifndef QT_NO_TOOLTIP
        pbInit->setToolTip(QApplication::translate("LocoIOFrame", "<html><head/><body><p>!!! Initialize PIC !!!</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        pbInit->setText(QApplication::translate("LocoIOFrame", "Init", nullptr));
        lblStatus->setText(QApplication::translate("LocoIOFrame", "status", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LocoIOFrame: public Ui_LocoIOFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOCOIOFRAME_H
