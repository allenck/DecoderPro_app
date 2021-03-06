/********************************************************************************
** Form generated from reading UI file 'rosterentrypane.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROSTERENTRYPANE_H
#define UI_ROSTERENTRYPANE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
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
            RosterEntryPane->setObjectName(QLatin1String("RosterEntryPane"));
        RosterEntryPane->resize(387, 386);
        QFont font;
        font.setPointSize(8);
        RosterEntryPane->setFont(font);
        formLayout = new QFormLayout(RosterEntryPane);
        formLayout->setObjectName(QLatin1String("formLayout"));
        edID = new QLineEdit(RosterEntryPane);
        edID->setObjectName(QLatin1String("edID"));

        formLayout->setWidget(0, QFormLayout::FieldRole, edID);

        label_2 = new QLabel(RosterEntryPane);
        label_2->setObjectName(QLatin1String("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        edRoadName = new QLineEdit(RosterEntryPane);
        edRoadName->setObjectName(QLatin1String("edRoadName"));

        formLayout->setWidget(1, QFormLayout::FieldRole, edRoadName);

        label_3 = new QLabel(RosterEntryPane);
        label_3->setObjectName(QLatin1String("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        edRoadNumber = new QLineEdit(RosterEntryPane);
        edRoadNumber->setObjectName(QLatin1String("edRoadNumber"));

        formLayout->setWidget(2, QFormLayout::FieldRole, edRoadNumber);

        label_4 = new QLabel(RosterEntryPane);
        label_4->setObjectName(QLatin1String("label_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        edManufacturer = new QLineEdit(RosterEntryPane);
        edManufacturer->setObjectName(QLatin1String("edManufacturer"));

        formLayout->setWidget(3, QFormLayout::FieldRole, edManufacturer);

        label_5 = new QLabel(RosterEntryPane);
        label_5->setObjectName(QLatin1String("label_5"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_5);

        edOwner = new QLineEdit(RosterEntryPane);
        edOwner->setObjectName(QLatin1String("edOwner"));

        formLayout->setWidget(4, QFormLayout::FieldRole, edOwner);

        label_6 = new QLabel(RosterEntryPane);
        label_6->setObjectName(QLatin1String("label_6"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_6);

        edModel = new QLineEdit(RosterEntryPane);
        edModel->setObjectName(QLatin1String("edModel"));

        formLayout->setWidget(5, QFormLayout::FieldRole, edModel);

        label_7 = new QLabel(RosterEntryPane);
        label_7->setObjectName(QLatin1String("label_7"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_7);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QLatin1String("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetFixedSize);
        edDccAddr = new QLineEdit(RosterEntryPane);
        edDccAddr->setObjectName(QLatin1String("edDccAddr"));
        edDccAddr->setMaximumSize(QSize(40, 16777215));
        edDccAddr->setMaxLength(6);

        horizontalLayout->addWidget(edDccAddr);

        cbDCCAddr = new QComboBox(RosterEntryPane);
        cbDCCAddr->addItem(QString());
        cbDCCAddr->addItem(QString());
        cbDCCAddr->setObjectName(QLatin1String("cbDCCAddr"));
        cbDCCAddr->setMaximumSize(QSize(100, 16777215));

        horizontalLayout->addWidget(cbDCCAddr);


        formLayout->setLayout(6, QFormLayout::FieldRole, horizontalLayout);

        label_9 = new QLabel(RosterEntryPane);
        label_9->setObjectName(QLatin1String("label_9"));

        formLayout->setWidget(7, QFormLayout::LabelRole, label_9);

        sbSpeed = new QSpinBox(RosterEntryPane);
        sbSpeed->setObjectName(QLatin1String("sbSpeed"));
        sbSpeed->setMaximumSize(QSize(55, 16777215));
        sbSpeed->setMaximum(100);
        sbSpeed->setValue(100);

        formLayout->setWidget(7, QFormLayout::FieldRole, sbSpeed);

        label_10 = new QLabel(RosterEntryPane);
        label_10->setObjectName(QLatin1String("label_10"));

        formLayout->setWidget(8, QFormLayout::LabelRole, label_10);

        edComment = new QPlainTextEdit(RosterEntryPane);
        edComment->setObjectName(QLatin1String("edComment"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(edComment->sizePolicy().hasHeightForWidth());
        edComment->setSizePolicy(sizePolicy);
        edComment->setMinimumSize(QSize(237, 20));
        edComment->setMaximumSize(QSize(237, 20));

        formLayout->setWidget(8, QFormLayout::FieldRole, edComment);

        label_11 = new QLabel(RosterEntryPane);
        label_11->setObjectName(QLatin1String("label_11"));

        formLayout->setWidget(9, QFormLayout::LabelRole, label_11);

        lblDecoderFamily = new QLabel(RosterEntryPane);
        lblDecoderFamily->setObjectName(QLatin1String("lblDecoderFamily"));

        formLayout->setWidget(9, QFormLayout::FieldRole, lblDecoderFamily);

        label_13 = new QLabel(RosterEntryPane);
        label_13->setObjectName(QLatin1String("label_13"));

        formLayout->setWidget(10, QFormLayout::LabelRole, label_13);

        lblDecoderModel = new QLabel(RosterEntryPane);
        lblDecoderModel->setObjectName(QLatin1String("lblDecoderModel"));

        formLayout->setWidget(10, QFormLayout::FieldRole, lblDecoderModel);

        label_15 = new QLabel(RosterEntryPane);
        label_15->setObjectName(QLatin1String("label_15"));

        formLayout->setWidget(11, QFormLayout::LabelRole, label_15);

        edDecoderComment = new QPlainTextEdit(RosterEntryPane);
        edDecoderComment->setObjectName(QLatin1String("edDecoderComment"));
        sizePolicy.setHeightForWidth(edDecoderComment->sizePolicy().hasHeightForWidth());
        edDecoderComment->setSizePolicy(sizePolicy);
        edDecoderComment->setMinimumSize(QSize(0, 20));
        edDecoderComment->setMaximumSize(QSize(16777215, 40));

        formLayout->setWidget(11, QFormLayout::FieldRole, edDecoderComment);

        label_16 = new QLabel(RosterEntryPane);
        label_16->setObjectName(QLatin1String("label_16"));

        formLayout->setWidget(12, QFormLayout::LabelRole, label_16);

        lblFilename = new QLabel(RosterEntryPane);
        lblFilename->setObjectName(QLatin1String("lblFilename"));

        formLayout->setWidget(12, QFormLayout::FieldRole, lblFilename);

        label_18 = new QLabel(RosterEntryPane);
        label_18->setObjectName(QLatin1String("label_18"));

        formLayout->setWidget(13, QFormLayout::LabelRole, label_18);

        lblDateModified = new QLabel(RosterEntryPane);
        lblDateModified->setObjectName(QLatin1String("lblDateModified"));

        formLayout->setWidget(13, QFormLayout::FieldRole, lblDateModified);

        label_21 = new QLabel(RosterEntryPane);
        label_21->setObjectName(QLatin1String("label_21"));

        formLayout->setWidget(14, QFormLayout::LabelRole, label_21);


        retranslateUi(RosterEntryPane);

        QMetaObject::connectSlotsByName(RosterEntryPane);
    } // setupUi

    void retranslateUi(QWidget *RosterEntryPane)
    {
        RosterEntryPane->setWindowTitle(QApplication::translate("RosterEntryPane", "Form", nullptr));
#ifndef QT_NO_TOOLTIP
        edID->setToolTip(QApplication::translate("RosterEntryPane", "<html><head/><body><p>Identifies this locomotive in the roster</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        label_2->setText(QApplication::translate("RosterEntryPane", "Road Name:", nullptr));
#ifndef QT_NO_TOOLTIP
        edRoadName->setToolTip(QApplication::translate("RosterEntryPane", "<html><head/><body><p><br/></p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        label_3->setText(QApplication::translate("RosterEntryPane", "Road Number:", nullptr));
#ifndef QT_NO_TOOLTIP
        edRoadNumber->setToolTip(QApplication::translate("RosterEntryPane", "<html><head/><body><p><br/></p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        label_4->setText(QApplication::translate("RosterEntryPane", "Manufacturer:", nullptr));
#ifndef QT_NO_TOOLTIP
        edManufacturer->setToolTip(QApplication::translate("RosterEntryPane", "<html><head/><body><p><br/></p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        label_5->setText(QApplication::translate("RosterEntryPane", "Owner: ", nullptr));
        label_6->setText(QApplication::translate("RosterEntryPane", "Model:", nullptr));
        label_7->setText(QApplication::translate("RosterEntryPane", "DCC Address:", nullptr));
        cbDCCAddr->setItemText(0, QApplication::translate("RosterEntryPane", "DCC Short", nullptr));
        cbDCCAddr->setItemText(1, QApplication::translate("RosterEntryPane", "DCC Long", nullptr));

#ifndef QT_NO_TOOLTIP
        cbDCCAddr->setToolTip(QApplication::translate("RosterEntryPane", "<html><head/><body><p>This is the current address type; you can't update it here. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        label_9->setText(QApplication::translate("RosterEntryPane", "Throttle Speed Limit (%):", nullptr));
        label_10->setText(QApplication::translate("RosterEntryPane", "Comment:", nullptr));
        label_11->setText(QApplication::translate("RosterEntryPane", "Decoder Family:", nullptr));
#ifndef QT_NO_TOOLTIP
        lblDecoderFamily->setToolTip(QApplication::translate("RosterEntryPane", "<html><head/><body><p>This is filled in automatically by your earlier selections</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        lblDecoderFamily->setText(QApplication::translate("RosterEntryPane", "Family", nullptr));
        label_13->setText(QApplication::translate("RosterEntryPane", "Decoder Model:", nullptr));
#ifndef QT_NO_TOOLTIP
        lblDecoderModel->setToolTip(QApplication::translate("RosterEntryPane", "<html><head/><body><p>This is filled in automatically by your earlier selections</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        lblDecoderModel->setText(QApplication::translate("RosterEntryPane", "dec model", nullptr));
        label_15->setText(QApplication::translate("RosterEntryPane", "Decoder Comment: ", nullptr));
        label_16->setText(QApplication::translate("RosterEntryPane", "Filename:", nullptr));
#ifndef QT_NO_TOOLTIP
        lblFilename->setToolTip(QApplication::translate("RosterEntryPane", "<html><head/><body><p>This is filled in automatically by the program</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        lblFilename->setText(QApplication::translate("RosterEntryPane", "xxx.xml", nullptr));
        label_18->setText(QApplication::translate("RosterEntryPane", "Date modified:", nullptr));
#ifndef QT_NO_TOOLTIP
        lblDateModified->setToolTip(QApplication::translate("RosterEntryPane", "<html><head/><body><p>The time and date this entry last stored</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        lblDateModified->setText(QApplication::translate("RosterEntryPane", "Jan 22, 2014 8:27:01 AM", nullptr));
        label_21->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class RosterEntryPane: public Ui_RosterEntryPane {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROSTERENTRYPANE_H
