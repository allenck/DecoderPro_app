/********************************************************************************
** Form generated from reading UI file 'commentsdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMMENTSDIALOG_H
#define UI_COMMENTSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_CommentsDialog
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout;
    QLabel *lblUnitAddress;
    QLabel *lblDisplayUnitAddress;
    QLabel *lblDisplayType;
    QLabel *lblDisplayOutput;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lblPort;
    QLabel *lblDisplayPort;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLabel *lblDisplayMode;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLabel *lblDisplayAddress;
    QLabel *label_4;
    QLineEdit *edTitle;
    QLabel *label_5;
    QTextEdit *edTextEdit;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *btnUpdate;
    QPushButton *btnDelete;
    QPushButton *btnCancel;

    void setupUi(QDialog *CommentsDialog)
    {
        if (CommentsDialog->objectName().isEmpty())
            CommentsDialog->setObjectName(QString::fromUtf8("CommentsDialog"));
        CommentsDialog->resize(400, 312);
        gridLayout = new QGridLayout(CommentsDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lblUnitAddress = new QLabel(CommentsDialog);
        lblUnitAddress->setObjectName(QString::fromUtf8("lblUnitAddress"));

        horizontalLayout->addWidget(lblUnitAddress);

        lblDisplayUnitAddress = new QLabel(CommentsDialog);
        lblDisplayUnitAddress->setObjectName(QString::fromUtf8("lblDisplayUnitAddress"));

        horizontalLayout->addWidget(lblDisplayUnitAddress);


        horizontalLayout_6->addLayout(horizontalLayout);

        lblDisplayType = new QLabel(CommentsDialog);
        lblDisplayType->setObjectName(QString::fromUtf8("lblDisplayType"));

        horizontalLayout_6->addWidget(lblDisplayType);

        lblDisplayOutput = new QLabel(CommentsDialog);
        lblDisplayOutput->setObjectName(QString::fromUtf8("lblDisplayOutput"));

        horizontalLayout_6->addWidget(lblDisplayOutput);


        gridLayout->addLayout(horizontalLayout_6, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lblPort = new QLabel(CommentsDialog);
        lblPort->setObjectName(QString::fromUtf8("lblPort"));
        lblPort->setMaximumSize(QSize(55, 16777215));

        horizontalLayout_2->addWidget(lblPort);

        lblDisplayPort = new QLabel(CommentsDialog);
        lblDisplayPort->setObjectName(QString::fromUtf8("lblDisplayPort"));

        horizontalLayout_2->addWidget(lblDisplayPort);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(CommentsDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMaximumSize(QSize(55, 16777215));

        horizontalLayout_3->addWidget(label_2);

        lblDisplayMode = new QLabel(CommentsDialog);
        lblDisplayMode->setObjectName(QString::fromUtf8("lblDisplayMode"));

        horizontalLayout_3->addWidget(lblDisplayMode);


        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_3 = new QLabel(CommentsDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMaximumSize(QSize(55, 16777215));

        horizontalLayout_4->addWidget(label_3);

        lblDisplayAddress = new QLabel(CommentsDialog);
        lblDisplayAddress->setObjectName(QString::fromUtf8("lblDisplayAddress"));

        horizontalLayout_4->addWidget(lblDisplayAddress);


        gridLayout->addLayout(horizontalLayout_4, 3, 0, 1, 1);

        label_4 = new QLabel(CommentsDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 4, 0, 1, 1);

        edTitle = new QLineEdit(CommentsDialog);
        edTitle->setObjectName(QString::fromUtf8("edTitle"));

        gridLayout->addWidget(edTitle, 5, 0, 1, 1);

        label_5 = new QLabel(CommentsDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 6, 0, 1, 1);

        edTextEdit = new QTextEdit(CommentsDialog);
        edTextEdit->setObjectName(QString::fromUtf8("edTextEdit"));

        gridLayout->addWidget(edTextEdit, 7, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        btnUpdate = new QPushButton(CommentsDialog);
        btnUpdate->setObjectName(QString::fromUtf8("btnUpdate"));

        horizontalLayout_5->addWidget(btnUpdate);

        btnDelete = new QPushButton(CommentsDialog);
        btnDelete->setObjectName(QString::fromUtf8("btnDelete"));

        horizontalLayout_5->addWidget(btnDelete);

        btnCancel = new QPushButton(CommentsDialog);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));

        horizontalLayout_5->addWidget(btnCancel);


        gridLayout->addLayout(horizontalLayout_5, 8, 0, 1, 1);


        retranslateUi(CommentsDialog);

        QMetaObject::connectSlotsByName(CommentsDialog);
    } // setupUi

    void retranslateUi(QDialog *CommentsDialog)
    {
        CommentsDialog->setWindowTitle(QCoreApplication::translate("CommentsDialog", "Update Comments", nullptr));
        lblUnitAddress->setText(QCoreApplication::translate("CommentsDialog", "unitAddress:", nullptr));
        lblDisplayUnitAddress->setText(QCoreApplication::translate("CommentsDialog", "0x00/00", nullptr));
        lblDisplayType->setText(QCoreApplication::translate("CommentsDialog", "LocoServo", nullptr));
        lblDisplayOutput->setText(QCoreApplication::translate("CommentsDialog", "Output", nullptr));
        lblPort->setText(QCoreApplication::translate("CommentsDialog", "Port:", nullptr));
        lblDisplayPort->setText(QCoreApplication::translate("CommentsDialog", "1", nullptr));
        label_2->setText(QCoreApplication::translate("CommentsDialog", "Mode:", nullptr));
        lblDisplayMode->setText(QCoreApplication::translate("CommentsDialog", "mode ....", nullptr));
        label_3->setText(QCoreApplication::translate("CommentsDialog", "Address:", nullptr));
        lblDisplayAddress->setText(QCoreApplication::translate("CommentsDialog", "0", nullptr));
        label_4->setText(QCoreApplication::translate("CommentsDialog", "Title", nullptr));
        label_5->setText(QCoreApplication::translate("CommentsDialog", "Description:", nullptr));
        btnUpdate->setText(QCoreApplication::translate("CommentsDialog", "Update", nullptr));
        btnDelete->setText(QCoreApplication::translate("CommentsDialog", "Delete", nullptr));
        btnCancel->setText(QCoreApplication::translate("CommentsDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CommentsDialog: public Ui_CommentsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMMENTSDIALOG_H
