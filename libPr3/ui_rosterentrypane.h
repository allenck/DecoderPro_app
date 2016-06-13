/********************************************************************************
** Form generated from reading UI file 'rosterentrypane.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROSTERENTRYPANE_H
#define UI_ROSTERENTRYPANE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RosterEntryPane
{
public:
    QFormLayout *formLayout;
    QLineEdit *edID;
    QLabel *label_2;
    QLineEdit *edRoadName;
    QLabel *label_3;
    QLineEdit *edRoadNumber;
    QLabel *label_4;
    QLineEdit *edManufacturer;
    QLabel *label_5;
    QLineEdit *edOwner;
    QLabel *label_6;
    QLineEdit *edModel;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout;
    QLineEdit *edDccAddr;
    QComboBox *cbDCCAddr;
    QLabel *label_9;
    QSpinBox *sbSpeed;
    QLabel *label_10;
    QPlainTextEdit *edComment;
    QLabel *label_11;
    QLabel *lblDecoderFamily;
    QLabel *label_13;
    QLabel *lblDecoderModel;
    QLabel *label_15;
    QPlainTextEdit *edDecoderComment;
    QLabel *label_16;
    QLabel *lblFilename;
    QLabel *label_18;
    QLabel *lblDateModified;
    QLabel *label_21;

    void setupUi(QWidget *RosterEntryPane)
    {
        if (RosterEntryPane->objectName().isEmpty())
            RosterEntryPane->setObjectName(QStringLiteral("RosterEntryPane"));
        RosterEntryPane->resize(387, 386);
        QFont font;
        font.setPointSize(8);
        RosterEntryPane->setFont(font);
        formLayout = new QFormLayout(RosterEntryPane);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        edID = new QLineEdit(RosterEntryPane);
        edID->setObjectName(QStringLiteral("edID"));

        formLayout->setWidget(0, QFormLayout::FieldRole, edID);

        label_2 = new QLabel(RosterEntryPane);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        edRoadName = new QLineEdit(RosterEntryPane);
        edRoadName->setObjectName(QStringLiteral("edRoadName"));

        formLayout->setWidget(1, QFormLayout::FieldRole, edRoadName);

        label_3 = new QLabel(RosterEntryPane);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        edRoadNumber = new QLineEdit(RosterEntryPane);
        edRoadNumber->setObjectName(QStringLiteral("edRoadNumber"));

        formLayout->setWidget(2, QFormLayout::FieldRole, edRoadNumber);

        label_4 = new QLabel(RosterEntryPane);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        edManufacturer = new QLineEdit(RosterEntryPane);
        edManufacturer->setObjectName(QStringLiteral("edManufacturer"));

        formLayout->setWidget(3, QFormLayout::FieldRole, edManufacturer);

        label_5 = new QLabel(RosterEntryPane);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_5);

        edOwner = new QLineEdit(RosterEntryPane);
        edOwner->setObjectName(QStringLiteral("edOwner"));

        formLayout->setWidget(4, QFormLayout::FieldRole, edOwner);

        label_6 = new QLabel(RosterEntryPane);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_6);

        edModel = new QLineEdit(RosterEntryPane);
        edModel->setObjectName(QStringLiteral("edModel"));

        formLayout->setWidget(5, QFormLayout::FieldRole, edModel);

        label_7 = new QLabel(RosterEntryPane);
        label_7->setObjectName(QStringLiteral("label_7"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_7);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetFixedSize);
        edDccAddr = new QLineEdit(RosterEntryPane);
        edDccAddr->setObjectName(QStringLiteral("edDccAddr"));
        edDccAddr->setMaximumSize(QSize(40, 16777215));
        edDccAddr->setMaxLength(6);

        horizontalLayout->addWidget(edDccAddr);

        cbDCCAddr = new QComboBox(RosterEntryPane);
        cbDCCAddr->setObjectName(QStringLiteral("cbDCCAddr"));
        cbDCCAddr->setMaximumSize(QSize(100, 16777215));

        horizontalLayout->addWidget(cbDCCAddr);


        formLayout->setLayout(6, QFormLayout::FieldRole, horizontalLayout);

        label_9 = new QLabel(RosterEntryPane);
        label_9->setObjectName(QStringLiteral("label_9"));

        formLayout->setWidget(7, QFormLayout::LabelRole, label_9);

        sbSpeed = new QSpinBox(RosterEntryPane);
        sbSpeed->setObjectName(QStringLiteral("sbSpeed"));
        sbSpeed->setMaximumSize(QSize(55, 16777215));
        sbSpeed->setMaximum(100);
        sbSpeed->setValue(100);

        formLayout->setWidget(7, QFormLayout::FieldRole, sbSpeed);

        label_10 = new QLabel(RosterEntryPane);
        label_10->setObjectName(QStringLiteral("label_10"));

        formLayout->setWidget(8, QFormLayout::LabelRole, label_10);

        edComment = new QPlainTextEdit(RosterEntryPane);
        edComment->setObjectName(QStringLiteral("edComment"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(edComment->sizePolicy().hasHeightForWidth());
        edComment->setSizePolicy(sizePolicy);
        edComment->setMinimumSize(QSize(237, 20));
        edComment->setMaximumSize(QSize(237, 20));

        formLayout->setWidget(8, QFormLayout::FieldRole, edComment);

        label_11 = new QLabel(RosterEntryPane);
        label_11->setObjectName(QStringLiteral("label_11"));

        formLayout->setWidget(9, QFormLayout::LabelRole, label_11);

        lblDecoderFamily = new QLabel(RosterEntryPane);
        lblDecoderFamily->setObjectName(QStringLiteral("lblDecoderFamily"));

        formLayout->setWidget(9, QFormLayout::FieldRole, lblDecoderFamily);

        label_13 = new QLabel(RosterEntryPane);
        label_13->setObjectName(QStringLiteral("label_13"));

        formLayout->setWidget(10, QFormLayout::LabelRole, label_13);

        lblDecoderModel = new QLabel(RosterEntryPane);
        lblDecoderModel->setObjectName(QStringLiteral("lblDecoderModel"));

        formLayout->setWidget(10, QFormLayout::FieldRole, lblDecoderModel);

        label_15 = new QLabel(RosterEntryPane);
        label_15->setObjectName(QStringLiteral("label_15"));

        formLayout->setWidget(11, QFormLayout::LabelRole, label_15);

        edDecoderComment = new QPlainTextEdit(RosterEntryPane);
        edDecoderComment->setObjectName(QStringLiteral("edDecoderComment"));
        sizePolicy.setHeightForWidth(edDecoderComment->sizePolicy().hasHeightForWidth());
        edDecoderComment->setSizePolicy(sizePolicy);
        edDecoderComment->setMinimumSize(QSize(0, 20));
        edDecoderComment->setMaximumSize(QSize(16777215, 40));

        formLayout->setWidget(11, QFormLayout::FieldRole, edDecoderComment);

        label_16 = new QLabel(RosterEntryPane);
        label_16->setObjectName(QStringLiteral("label_16"));

        formLayout->setWidget(12, QFormLayout::LabelRole, label_16);

        lblFilename = new QLabel(RosterEntryPane);
        lblFilename->setObjectName(QStringLiteral("lblFilename"));

        formLayout->setWidget(12, QFormLayout::FieldRole, lblFilename);

        label_18 = new QLabel(RosterEntryPane);
        label_18->setObjectName(QStringLiteral("label_18"));

        formLayout->setWidget(13, QFormLayout::LabelRole, label_18);

        lblDateModified = new QLabel(RosterEntryPane);
        lblDateModified->setObjectName(QStringLiteral("lblDateModified"));

        formLayout->setWidget(13, QFormLayout::FieldRole, lblDateModified);

        label_21 = new QLabel(RosterEntryPane);
        label_21->setObjectName(QStringLiteral("label_21"));

        formLayout->setWidget(14, QFormLayout::LabelRole, label_21);


        retranslateUi(RosterEntryPane);

        QMetaObject::connectSlotsByName(RosterEntryPane);
    } // setupUi

    void retranslateUi(QWidget *RosterEntryPane)
    {
        RosterEntryPane->setWindowTitle(QApplication::translate("RosterEntryPane", "Form", 0));
#ifndef QT_NO_TOOLTIP
        edID->setToolTip(QApplication::translate("RosterEntryPane", "<html><head/><body><p>Identifies this locomotive in the roster</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        label_2->setText(QApplication::translate("RosterEntryPane", "Road Name:", 0));
#ifndef QT_NO_TOOLTIP
        edRoadName->setToolTip(QApplication::translate("RosterEntryPane", "<html><head/><body><p><br/></p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        label_3->setText(QApplication::translate("RosterEntryPane", "Road Number:", 0));
#ifndef QT_NO_TOOLTIP
        edRoadNumber->setToolTip(QApplication::translate("RosterEntryPane", "<html><head/><body><p><br/></p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        label_4->setText(QApplication::translate("RosterEntryPane", "Manufacturer:", 0));
#ifndef QT_NO_TOOLTIP
        edManufacturer->setToolTip(QApplication::translate("RosterEntryPane", "<html><head/><body><p><br/></p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        label_5->setText(QApplication::translate("RosterEntryPane", "Owner: ", 0));
        label_6->setText(QApplication::translate("RosterEntryPane", "Model:", 0));
        label_7->setText(QApplication::translate("RosterEntryPane", "DCC Address:", 0));
        cbDCCAddr->clear();
        cbDCCAddr->insertItems(0, QStringList()
         << QApplication::translate("RosterEntryPane", "DCC Short", 0)
         << QApplication::translate("RosterEntryPane", "DCC Long", 0)
        );
#ifndef QT_NO_TOOLTIP
        cbDCCAddr->setToolTip(QApplication::translate("RosterEntryPane", "<html><head/><body><p>This is the current address type; you can't update it here. </p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        label_9->setText(QApplication::translate("RosterEntryPane", "Throttle Speed Limit (%):", 0));
        label_10->setText(QApplication::translate("RosterEntryPane", "Comment:", 0));
        label_11->setText(QApplication::translate("RosterEntryPane", "Decoder Family:", 0));
#ifndef QT_NO_TOOLTIP
        lblDecoderFamily->setToolTip(QApplication::translate("RosterEntryPane", "<html><head/><body><p>This is filled in automatically by your earlier selections</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        lblDecoderFamily->setText(QApplication::translate("RosterEntryPane", "Family", 0));
        label_13->setText(QApplication::translate("RosterEntryPane", "Decoder Model:", 0));
#ifndef QT_NO_TOOLTIP
        lblDecoderModel->setToolTip(QApplication::translate("RosterEntryPane", "<html><head/><body><p>This is filled in automatically by your earlier selections</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        lblDecoderModel->setText(QApplication::translate("RosterEntryPane", "dec model", 0));
        label_15->setText(QApplication::translate("RosterEntryPane", "Decoder Comment: ", 0));
        label_16->setText(QApplication::translate("RosterEntryPane", "Filename:", 0));
#ifndef QT_NO_TOOLTIP
        lblFilename->setToolTip(QApplication::translate("RosterEntryPane", "<html><head/><body><p>This is filled in automatically by the program</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        lblFilename->setText(QApplication::translate("RosterEntryPane", "xxx.xml", 0));
        label_18->setText(QApplication::translate("RosterEntryPane", "Date modified:", 0));
#ifndef QT_NO_TOOLTIP
        lblDateModified->setToolTip(QApplication::translate("RosterEntryPane", "<html><head/><body><p>The time and date this entry last stored</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        lblDateModified->setText(QApplication::translate("RosterEntryPane", "Jan 22, 2014 8:27:01 AM", 0));
        label_21->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class RosterEntryPane: public Ui_RosterEntryPane {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROSTERENTRYPANE_H
