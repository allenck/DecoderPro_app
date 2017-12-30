/********************************************************************************
** Form generated from reading UI file 'factoryresetaction.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FACTORYRESETACTION_H
#define UI_FACTORYRESETACTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
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
            FactoryResetAction->setObjectName(QStringLiteral("FactoryResetAction"));
        FactoryResetAction->resize(216, 154);
        gridLayout = new QGridLayout(FactoryResetAction);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(FactoryResetAction);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        comboBox = new QComboBox(FactoryResetAction);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        gridLayout->addWidget(comboBox, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        btnOK = new QPushButton(FactoryResetAction);
        btnOK->setObjectName(QStringLiteral("btnOK"));

        horizontalLayout->addWidget(btnOK);

        btnCancel = new QPushButton(FactoryResetAction);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));

        horizontalLayout->addWidget(btnCancel);


        gridLayout->addLayout(horizontalLayout, 2, 0, 1, 1);


        retranslateUi(FactoryResetAction);

        QMetaObject::connectSlotsByName(FactoryResetAction);
    } // setupUi

    void retranslateUi(QDialog *FactoryResetAction)
    {
        FactoryResetAction->setWindowTitle(QApplication::translate("FactoryResetAction", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("FactoryResetAction", "Factory Reset", Q_NULLPTR));
        btnOK->setText(QApplication::translate("FactoryResetAction", "OK", Q_NULLPTR));
        btnCancel->setText(QApplication::translate("FactoryResetAction", "Cancel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class FactoryResetAction: public Ui_FactoryResetAction {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FACTORYRESETACTION_H
