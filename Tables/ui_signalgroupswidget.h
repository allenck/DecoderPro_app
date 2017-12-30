/********************************************************************************
** Form generated from reading UI file 'signalgroupswidget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNALGROUPSWIDGET_H
#define UI_SIGNALGROUPSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_SignalGroupsWidget
{
public:
    QGridLayout *gridLayout;
    QPushButton *btnAdd;
    QTableView *tableView;

    void setupUi(QDialog *SignalGroupsWidget)
    {
        if (SignalGroupsWidget->objectName().isEmpty())
            SignalGroupsWidget->setObjectName(QStringLiteral("SignalGroupsWidget"));
        SignalGroupsWidget->resize(400, 253);
        gridLayout = new QGridLayout(SignalGroupsWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        btnAdd = new QPushButton(SignalGroupsWidget);
        btnAdd->setObjectName(QStringLiteral("btnAdd"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnAdd->sizePolicy().hasHeightForWidth());
        btnAdd->setSizePolicy(sizePolicy);

        gridLayout->addWidget(btnAdd, 1, 0, 1, 1);

        tableView = new QTableView(SignalGroupsWidget);
        tableView->setObjectName(QStringLiteral("tableView"));

        gridLayout->addWidget(tableView, 0, 0, 1, 1);


        retranslateUi(SignalGroupsWidget);

        QMetaObject::connectSlotsByName(SignalGroupsWidget);
    } // setupUi

    void retranslateUi(QDialog *SignalGroupsWidget)
    {
        SignalGroupsWidget->setWindowTitle(QApplication::translate("SignalGroupsWidget", "Dialog", Q_NULLPTR));
        btnAdd->setText(QApplication::translate("SignalGroupsWidget", "Add", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SignalGroupsWidget: public Ui_SignalGroupsWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNALGROUPSWIDGET_H
