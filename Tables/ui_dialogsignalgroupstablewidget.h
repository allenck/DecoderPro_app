/********************************************************************************
** Form generated from reading UI file 'dialogsignalgroupstablewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGSIGNALGROUPSTABLEWIDGET_H
#define UI_DIALOGSIGNALGROUPSTABLEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogSignalGroupsTableWIdget
{
public:
    QFormLayout *formLayout;
    QPushButton *btnAdd;
    QTableWidget *tableWidget;

    void setupUi(QDialog *DialogSignalGroupsTableWIdget)
    {
        if (DialogSignalGroupsTableWIdget->objectName().isEmpty())
            DialogSignalGroupsTableWIdget->setObjectName(QString::fromUtf8("DialogSignalGroupsTableWIdget"));
        DialogSignalGroupsTableWIdget->resize(400, 237);
        formLayout = new QFormLayout(DialogSignalGroupsTableWIdget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        btnAdd = new QPushButton(DialogSignalGroupsTableWIdget);
        btnAdd->setObjectName(QString::fromUtf8("btnAdd"));

        formLayout->setWidget(1, QFormLayout::LabelRole, btnAdd);

        tableWidget = new QTableWidget(DialogSignalGroupsTableWIdget);
        if (tableWidget->columnCount() < 6)
            tableWidget->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        formLayout->setWidget(0, QFormLayout::SpanningRole, tableWidget);


        retranslateUi(DialogSignalGroupsTableWIdget);

        QMetaObject::connectSlotsByName(DialogSignalGroupsTableWIdget);
    } // setupUi

    void retranslateUi(QDialog *DialogSignalGroupsTableWIdget)
    {
        DialogSignalGroupsTableWIdget->setWindowTitle(QCoreApplication::translate("DialogSignalGroupsTableWIdget", "Dialog", nullptr));
        btnAdd->setText(QCoreApplication::translate("DialogSignalGroupsTableWIdget", "PushButton", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("DialogSignalGroupsTableWIdget", "System Names", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("DialogSignalGroupsTableWIdget", "User Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("DialogSignalGroupsTableWIdget", "Comment", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("DialogSignalGroupsTableWIdget", "Enabled", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogSignalGroupsTableWIdget: public Ui_DialogSignalGroupsTableWIdget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGSIGNALGROUPSTABLEWIDGET_H
