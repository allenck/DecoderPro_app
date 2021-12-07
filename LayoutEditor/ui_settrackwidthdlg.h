/********************************************************************************
** Form generated from reading UI file 'settrackwidthdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTRACKWIDTHDLG_H
#define UI_SETTRACKWIDTHDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SetTrackWidthDlg
{
public:
    QFormLayout *formLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *sbSidetrack;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpinBox *sbMainline;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *SetTrackWidthDlg)
    {
        if (SetTrackWidthDlg->objectName().isEmpty())
            SetTrackWidthDlg->setObjectName(QString::fromUtf8("SetTrackWidthDlg"));
        SetTrackWidthDlg->resize(230, 119);
        formLayout = new QFormLayout(SetTrackWidthDlg);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(SetTrackWidthDlg);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        sbSidetrack = new QSpinBox(SetTrackWidthDlg);
        sbSidetrack->setObjectName(QString::fromUtf8("sbSidetrack"));
        sbSidetrack->setMinimum(1);
        sbSidetrack->setMaximum(5);

        horizontalLayout->addWidget(sbSidetrack);


        formLayout->setLayout(0, QFormLayout::LabelRole, horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(SetTrackWidthDlg);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        sbMainline = new QSpinBox(SetTrackWidthDlg);
        sbMainline->setObjectName(QString::fromUtf8("sbMainline"));
        sbMainline->setMaximum(5);

        horizontalLayout_2->addWidget(sbMainline);


        formLayout->setLayout(1, QFormLayout::LabelRole, horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        okButton = new QPushButton(SetTrackWidthDlg);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        horizontalLayout_3->addWidget(okButton);

        cancelButton = new QPushButton(SetTrackWidthDlg);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        horizontalLayout_3->addWidget(cancelButton);


        formLayout->setLayout(2, QFormLayout::LabelRole, horizontalLayout_3);


        retranslateUi(SetTrackWidthDlg);

        QMetaObject::connectSlotsByName(SetTrackWidthDlg);
    } // setupUi

    void retranslateUi(QDialog *SetTrackWidthDlg)
    {
        SetTrackWidthDlg->setWindowTitle(QCoreApplication::translate("SetTrackWidthDlg", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("SetTrackWidthDlg", "Side track width", nullptr));
        label_2->setText(QCoreApplication::translate("SetTrackWidthDlg", "Mainline track width", nullptr));
        okButton->setText(QCoreApplication::translate("SetTrackWidthDlg", "Done", nullptr));
        cancelButton->setText(QCoreApplication::translate("SetTrackWidthDlg", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetTrackWidthDlg: public Ui_SetTrackWidthDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTRACKWIDTHDLG_H
