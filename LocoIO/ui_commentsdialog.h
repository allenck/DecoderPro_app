/********************************************************************************
** Form generated from reading UI file 'commentsdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMMENTSDIALOG_H
#define UI_COMMENTSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
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
            CommentsDialog->setObjectName(QStringLiteral("CommentsDialog"));
        CommentsDialog->resize(400, 312);
        gridLayout = new QGridLayout(CommentsDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lblUnitAddress = new QLabel(CommentsDialog);
        lblUnitAddress->setObjectName(QStringLiteral("lblUnitAddress"));

        horizontalLayout->addWidget(lblUnitAddress);

        lblDisplayUnitAddress = new QLabel(CommentsDialog);
        lblDisplayUnitAddress->setObjectName(QStringLiteral("lblDisplayUnitAddress"));

        horizontalLayout->addWidget(lblDisplayUnitAddress);


        horizontalLayout_6->addLayout(horizontalLayout);

        lblDisplayType = new QLabel(CommentsDialog);
        lblDisplayType->setObjectName(QStringLiteral("lblDisplayType"));

        horizontalLayout_6->addWidget(lblDisplayType);

        lblDisplayOutput = new QLabel(CommentsDialog);
        lblDisplayOutput->setObjectName(QStringLiteral("lblDisplayOutput"));

        horizontalLayout_6->addWidget(lblDisplayOutput);


        gridLayout->addLayout(horizontalLayout_6, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        lblPort = new QLabel(CommentsDialog);
        lblPort->setObjectName(QStringLiteral("lblPort"));
        lblPort->setMaximumSize(QSize(55, 16777215));

        horizontalLayout_2->addWidget(lblPort);

        lblDisplayPort = new QLabel(CommentsDialog);
        lblDisplayPort->setObjectName(QStringLiteral("lblDisplayPort"));

        horizontalLayout_2->addWidget(lblDisplayPort);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_2 = new QLabel(CommentsDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMaximumSize(QSize(55, 16777215));

        horizontalLayout_3->addWidget(label_2);

        lblDisplayMode = new QLabel(CommentsDialog);
        lblDisplayMode->setObjectName(QStringLiteral("lblDisplayMode"));

        horizontalLayout_3->addWidget(lblDisplayMode);


        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_3 = new QLabel(CommentsDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMaximumSize(QSize(55, 16777215));

        horizontalLayout_4->addWidget(label_3);

        lblDisplayAddress = new QLabel(CommentsDialog);
        lblDisplayAddress->setObjectName(QStringLiteral("lblDisplayAddress"));

        horizontalLayout_4->addWidget(lblDisplayAddress);


        gridLayout->addLayout(horizontalLayout_4, 3, 0, 1, 1);

        label_4 = new QLabel(CommentsDialog);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 4, 0, 1, 1);

        edTitle = new QLineEdit(CommentsDialog);
        edTitle->setObjectName(QStringLiteral("edTitle"));

        gridLayout->addWidget(edTitle, 5, 0, 1, 1);

        label_5 = new QLabel(CommentsDialog);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 6, 0, 1, 1);

        edTextEdit = new QTextEdit(CommentsDialog);
        edTextEdit->setObjectName(QStringLiteral("edTextEdit"));

        gridLayout->addWidget(edTextEdit, 7, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        btnUpdate = new QPushButton(CommentsDialog);
        btnUpdate->setObjectName(QStringLiteral("btnUpdate"));

        horizontalLayout_5->addWidget(btnUpdate);

        btnDelete = new QPushButton(CommentsDialog);
        btnDelete->setObjectName(QStringLiteral("btnDelete"));

        horizontalLayout_5->addWidget(btnDelete);

        btnCancel = new QPushButton(CommentsDialog);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));

        horizontalLayout_5->addWidget(btnCancel);


        gridLayout->addLayout(horizontalLayout_5, 8, 0, 1, 1);


        retranslateUi(CommentsDialog);

        QMetaObject::connectSlotsByName(CommentsDialog);
    } // setupUi

    void retranslateUi(QDialog *CommentsDialog)
    {
        CommentsDialog->setWindowTitle(QApplication::translate("CommentsDialog", "Update Comments", 0));
        lblUnitAddress->setText(QApplication::translate("CommentsDialog", "unitAddress:", 0));
        lblDisplayUnitAddress->setText(QApplication::translate("CommentsDialog", "0x00/00", 0));
        lblDisplayType->setText(QApplication::translate("CommentsDialog", "LocoServo", 0));
        lblDisplayOutput->setText(QApplication::translate("CommentsDialog", "Output", 0));
        lblPort->setText(QApplication::translate("CommentsDialog", "Port:", 0));
        lblDisplayPort->setText(QApplication::translate("CommentsDialog", "1", 0));
        label_2->setText(QApplication::translate("CommentsDialog", "Mode:", 0));
        lblDisplayMode->setText(QApplication::translate("CommentsDialog", "mode ....", 0));
        label_3->setText(QApplication::translate("CommentsDialog", "Address:", 0));
        lblDisplayAddress->setText(QApplication::translate("CommentsDialog", "0", 0));
        label_4->setText(QApplication::translate("CommentsDialog", "Title", 0));
        label_5->setText(QApplication::translate("CommentsDialog", "Description:", 0));
        btnUpdate->setText(QApplication::translate("CommentsDialog", "Update", 0));
        btnDelete->setText(QApplication::translate("CommentsDialog", "Delete", 0));
        btnCancel->setText(QApplication::translate("CommentsDialog", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class CommentsDialog: public Ui_CommentsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMMENTSDIALOG_H
