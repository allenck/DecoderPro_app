/********************************************************************************
** Form generated from reading UI file 'addreporterdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDREPORTERDLG_H
#define UI_ADDREPORTERDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_AddReporterDlg
{
public:
    QFormLayout *formLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *edReporterName;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *edX;
    QLabel *label_3;
    QLineEdit *edY;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *AddReporterDlg)
    {
        if (AddReporterDlg->objectName().isEmpty())
            AddReporterDlg->setObjectName(QStringLiteral("AddReporterDlg"));
        AddReporterDlg->resize(281, 124);
        formLayout = new QFormLayout(AddReporterDlg);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(AddReporterDlg);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        edReporterName = new QLineEdit(AddReporterDlg);
        edReporterName->setObjectName(QStringLiteral("edReporterName"));

        horizontalLayout->addWidget(edReporterName);


        formLayout->setLayout(0, QFormLayout::LabelRole, horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(AddReporterDlg);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        edX = new QLineEdit(AddReporterDlg);
        edX->setObjectName(QStringLiteral("edX"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(edX->sizePolicy().hasHeightForWidth());
        edX->setSizePolicy(sizePolicy);
        edX->setMaximumSize(QSize(70, 16777215));
        edX->setInputMethodHints(Qt::ImhDigitsOnly);
        edX->setMaxLength(4);

        horizontalLayout_2->addWidget(edX);

        label_3 = new QLabel(AddReporterDlg);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_2->addWidget(label_3);

        edY = new QLineEdit(AddReporterDlg);
        edY->setObjectName(QStringLiteral("edY"));
        sizePolicy.setHeightForWidth(edY->sizePolicy().hasHeightForWidth());
        edY->setSizePolicy(sizePolicy);
        edY->setMaximumSize(QSize(70, 16777215));
        edY->setInputMethodHints(Qt::ImhDigitsOnly);
        edY->setMaxLength(4);

        horizontalLayout_2->addWidget(edY);


        formLayout->setLayout(1, QFormLayout::LabelRole, horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        okButton = new QPushButton(AddReporterDlg);
        okButton->setObjectName(QStringLiteral("okButton"));

        horizontalLayout_3->addWidget(okButton);

        cancelButton = new QPushButton(AddReporterDlg);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        horizontalLayout_3->addWidget(cancelButton);


        formLayout->setLayout(2, QFormLayout::LabelRole, horizontalLayout_3);


        retranslateUi(AddReporterDlg);

        QMetaObject::connectSlotsByName(AddReporterDlg);
    } // setupUi

    void retranslateUi(QDialog *AddReporterDlg)
    {
        AddReporterDlg->setWindowTitle(QApplication::translate("AddReporterDlg", "Dialog", 0));
        label->setText(QApplication::translate("AddReporterDlg", "Reporter Name", 0));
        label_2->setText(QApplication::translate("AddReporterDlg", "Location:  x", 0));
        label_3->setText(QApplication::translate("AddReporterDlg", ", y", 0));
        okButton->setText(QApplication::translate("AddReporterDlg", "Add new label", 0));
        cancelButton->setText(QApplication::translate("AddReporterDlg", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class AddReporterDlg: public Ui_AddReporterDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDREPORTERDLG_H
