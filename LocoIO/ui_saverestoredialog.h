/********************************************************************************
** Form generated from reading UI file 'saverestoredialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAVERESTOREDIALOG_H
#define UI_SAVERESTOREDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SaveRestoreDialog
{
public:
    QFormLayout *formLayout_2;
    QFormLayout *formLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *editAddr;
    QLabel *label_2;
    QLineEdit *editSubUnit;
    QComboBox *cbModules;
    QLineEdit *editDescription;
    QLabel *label_3;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnDelete;
    QPushButton *btnCancel;
    QPushButton *btnOK;
    QLabel *lblHelp;

    void setupUi(QDialog *SaveRestoreDialog)
    {
        if (SaveRestoreDialog->objectName().isEmpty())
            SaveRestoreDialog->setObjectName(QLatin1String("SaveRestoreDialog"));
        SaveRestoreDialog->resize(514, 205);
        formLayout_2 = new QFormLayout(SaveRestoreDialog);
        formLayout_2->setObjectName(QLatin1String("formLayout_2"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QLatin1String("formLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QLatin1String("horizontalLayout"));
        label = new QLabel(SaveRestoreDialog);
        label->setObjectName(QLatin1String("label"));

        horizontalLayout->addWidget(label);

        editAddr = new QLineEdit(SaveRestoreDialog);
        editAddr->setObjectName(QLatin1String("editAddr"));
        editAddr->setReadOnly(true);

        horizontalLayout->addWidget(editAddr);

        label_2 = new QLabel(SaveRestoreDialog);
        label_2->setObjectName(QLatin1String("label_2"));

        horizontalLayout->addWidget(label_2);

        editSubUnit = new QLineEdit(SaveRestoreDialog);
        editSubUnit->setObjectName(QLatin1String("editSubUnit"));
        editSubUnit->setReadOnly(true);

        horizontalLayout->addWidget(editSubUnit);


        formLayout->setLayout(4, QFormLayout::LabelRole, horizontalLayout);

        cbModules = new QComboBox(SaveRestoreDialog);
        cbModules->setObjectName(QLatin1String("cbModules"));
        cbModules->setEditable(false);

        formLayout->setWidget(1, QFormLayout::SpanningRole, cbModules);

        editDescription = new QLineEdit(SaveRestoreDialog);
        editDescription->setObjectName(QLatin1String("editDescription"));

        formLayout->setWidget(3, QFormLayout::SpanningRole, editDescription);

        label_3 = new QLabel(SaveRestoreDialog);
        label_3->setObjectName(QLatin1String("label_3"));

        formLayout->setWidget(2, QFormLayout::SpanningRole, label_3);

        label_4 = new QLabel(SaveRestoreDialog);
        label_4->setObjectName(QLatin1String("label_4"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_4);


        formLayout_2->setLayout(0, QFormLayout::LabelRole, formLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QLatin1String("horizontalLayout_2"));
        btnDelete = new QPushButton(SaveRestoreDialog);
        btnDelete->setObjectName(QLatin1String("btnDelete"));

        horizontalLayout_2->addWidget(btnDelete);

        btnCancel = new QPushButton(SaveRestoreDialog);
        btnCancel->setObjectName(QLatin1String("btnCancel"));

        horizontalLayout_2->addWidget(btnCancel);

        btnOK = new QPushButton(SaveRestoreDialog);
        btnOK->setObjectName(QLatin1String("btnOK"));

        horizontalLayout_2->addWidget(btnOK);


        formLayout_2->setLayout(2, QFormLayout::LabelRole, horizontalLayout_2);

        lblHelp = new QLabel(SaveRestoreDialog);
        lblHelp->setObjectName(QLatin1String("lblHelp"));
        QPalette palette;
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush1(QColor(159, 158, 158, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        lblHelp->setPalette(palette);

        formLayout_2->setWidget(1, QFormLayout::SpanningRole, lblHelp);


        retranslateUi(SaveRestoreDialog);

        QMetaObject::connectSlotsByName(SaveRestoreDialog);
    } // setupUi

    void retranslateUi(QDialog *SaveRestoreDialog)
    {
        SaveRestoreDialog->setWindowTitle(QApplication::translate("SaveRestoreDialog", "Dialog", nullptr));
        label->setText(QApplication::translate("SaveRestoreDialog", "Unit addr:", nullptr));
        label_2->setText(QApplication::translate("SaveRestoreDialog", "SubUnit Addr:", nullptr));
        label_3->setText(QApplication::translate("SaveRestoreDialog", "Description:", nullptr));
        label_4->setText(QApplication::translate("SaveRestoreDialog", "Module:", nullptr));
        btnDelete->setText(QApplication::translate("SaveRestoreDialog", "Delete", nullptr));
        btnCancel->setText(QApplication::translate("SaveRestoreDialog", "Cancel", nullptr));
        btnOK->setText(QApplication::translate("SaveRestoreDialog", "OK", nullptr));
        lblHelp->setText(QApplication::translate("SaveRestoreDialog", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SaveRestoreDialog: public Ui_SaveRestoreDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAVERESTOREDIALOG_H
