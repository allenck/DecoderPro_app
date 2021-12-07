/********************************************************************************
** Form generated from reading UI file 'factoryresetaction.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FACTORYRESETACTION_H
#define UI_FACTORYRESETACTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_FactoryResetAction
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnOK;
    QPushButton *btnCancel;

    void setupUi(QDialog *FactoryResetAction)
    {
        if (FactoryResetAction->objectName().isEmpty())
            FactoryResetAction->setObjectName(QString::fromUtf8("FactoryResetAction"));
        FactoryResetAction->resize(216, 154);
        gridLayout = new QGridLayout(FactoryResetAction);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(FactoryResetAction);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        comboBox = new QComboBox(FactoryResetAction);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout->addWidget(comboBox, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btnOK = new QPushButton(FactoryResetAction);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));

        horizontalLayout->addWidget(btnOK);

        btnCancel = new QPushButton(FactoryResetAction);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));

        horizontalLayout->addWidget(btnCancel);


        gridLayout->addLayout(horizontalLayout, 2, 0, 1, 1);


        retranslateUi(FactoryResetAction);

        QMetaObject::connectSlotsByName(FactoryResetAction);
    } // setupUi

    void retranslateUi(QDialog *FactoryResetAction)
    {
        FactoryResetAction->setWindowTitle(QCoreApplication::translate("FactoryResetAction", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("FactoryResetAction", "Factory Reset", nullptr));
        btnOK->setText(QCoreApplication::translate("FactoryResetAction", "OK", nullptr));
        btnCancel->setText(QCoreApplication::translate("FactoryResetAction", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FactoryResetAction: public Ui_FactoryResetAction {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FACTORYRESETACTION_H
