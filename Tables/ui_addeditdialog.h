/********************************************************************************
** Form generated from reading UI file 'addeditdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDEDITDIALOG_H
#define UI_ADDEDITDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AddEditDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *lbSystemName;
    QLabel *lbUser;
    QPushButton *btnOK;
    QCheckBox *chkAdd;
    QLineEdit *edUserName;
    QLabel *lbSystem;
    QSpinBox *sbAdd;
    QLabel *lbNumToAdd;
    QLineEdit *edSystemName;
    QVBoxLayout *verticalLayout;
    QComboBox *cbSystem;
    QCheckBox *chkAutoGen;

    void setupUi(QDialog *AddEditDialog)
    {
        if (AddEditDialog->objectName().isEmpty())
            AddEditDialog->setObjectName(QStringLiteral("AddEditDialog"));
        AddEditDialog->resize(506, 167);
        gridLayout = new QGridLayout(AddEditDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lbSystemName = new QLabel(AddEditDialog);
        lbSystemName->setObjectName(QStringLiteral("lbSystemName"));

        gridLayout->addWidget(lbSystemName, 2, 0, 1, 1);

        lbUser = new QLabel(AddEditDialog);
        lbUser->setObjectName(QStringLiteral("lbUser"));

        gridLayout->addWidget(lbUser, 3, 0, 1, 1);

        btnOK = new QPushButton(AddEditDialog);
        btnOK->setObjectName(QStringLiteral("btnOK"));

        gridLayout->addWidget(btnOK, 4, 2, 1, 1);

        chkAdd = new QCheckBox(AddEditDialog);
        chkAdd->setObjectName(QStringLiteral("chkAdd"));

        gridLayout->addWidget(chkAdd, 0, 3, 1, 3);

        edUserName = new QLineEdit(AddEditDialog);
        edUserName->setObjectName(QStringLiteral("edUserName"));

        gridLayout->addWidget(edUserName, 3, 2, 1, 1);

        lbSystem = new QLabel(AddEditDialog);
        lbSystem->setObjectName(QStringLiteral("lbSystem"));

        gridLayout->addWidget(lbSystem, 0, 0, 1, 1);

        sbAdd = new QSpinBox(AddEditDialog);
        sbAdd->setObjectName(QStringLiteral("sbAdd"));
        sbAdd->setEnabled(false);
        sbAdd->setMinimum(1);

        gridLayout->addWidget(sbAdd, 2, 5, 1, 1);

        lbNumToAdd = new QLabel(AddEditDialog);
        lbNumToAdd->setObjectName(QStringLiteral("lbNumToAdd"));
        lbNumToAdd->setEnabled(false);

        gridLayout->addWidget(lbNumToAdd, 2, 4, 1, 1);

        edSystemName = new QLineEdit(AddEditDialog);
        edSystemName->setObjectName(QStringLiteral("edSystemName"));

        gridLayout->addWidget(edSystemName, 2, 2, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        cbSystem = new QComboBox(AddEditDialog);
        cbSystem->setObjectName(QStringLiteral("cbSystem"));

        verticalLayout->addWidget(cbSystem);

        chkAutoGen = new QCheckBox(AddEditDialog);
        chkAutoGen->setObjectName(QStringLiteral("chkAutoGen"));

        verticalLayout->addWidget(chkAutoGen);


        gridLayout->addLayout(verticalLayout, 0, 2, 1, 1);


        retranslateUi(AddEditDialog);

        QMetaObject::connectSlotsByName(AddEditDialog);
    } // setupUi

    void retranslateUi(QDialog *AddEditDialog)
    {
        AddEditDialog->setWindowTitle(QApplication::translate("AddEditDialog", "Dialog", 0));
        lbSystemName->setText(QApplication::translate("AddEditDialog", "System Name:", 0));
        lbUser->setText(QApplication::translate("AddEditDialog", "User Name:", 0));
        btnOK->setText(QApplication::translate("AddEditDialog", "OK", 0));
        chkAdd->setText(QApplication::translate("AddEditDialog", "Add a range", 0));
        lbSystem->setText(QApplication::translate("AddEditDialog", "System", 0));
        lbNumToAdd->setText(QApplication::translate("AddEditDialog", "Num to add", 0));
        cbSystem->clear();
        cbSystem->insertItems(0, QStringList()
         << QApplication::translate("AddEditDialog", "Internal", 0)
         << QApplication::translate("AddEditDialog", "LocoNet", 0)
        );
        chkAutoGen->setText(QApplication::translate("AddEditDialog", "Automatically Generate System Name", 0));
    } // retranslateUi

};

namespace Ui {
    class AddEditDialog: public Ui_AddEditDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDEDITDIALOG_H
