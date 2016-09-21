/********************************************************************************
** Form generated from reading UI file 'dialogsignalgroupstablewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGSIGNALGROUPSTABLEWIDGET_H
#define UI_DIALOGSIGNALGROUPSTABLEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
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
            DialogSignalGroupsTableWIdget->setObjectName(QStringLiteral("DialogSignalGroupsTableWIdget"));
        DialogSignalGroupsTableWIdget->resize(400, 237);
        formLayout = new QFormLayout(DialogSignalGroupsTableWIdget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        btnAdd = new QPushButton(DialogSignalGroupsTableWIdget);
        btnAdd->setObjectName(QStringLiteral("btnAdd"));

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
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        formLayout->setWidget(0, QFormLayout::SpanningRole, tableWidget);


        retranslateUi(DialogSignalGroupsTableWIdget);

        QMetaObject::connectSlotsByName(DialogSignalGroupsTableWIdget);
    } // setupUi

    void retranslateUi(QDialog *DialogSignalGroupsTableWIdget)
    {
        DialogSignalGroupsTableWIdget->setWindowTitle(QApplication::translate("DialogSignalGroupsTableWIdget", "Dialog", 0));
        btnAdd->setText(QApplication::translate("DialogSignalGroupsTableWIdget", "PushButton", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("DialogSignalGroupsTableWIdget", "System Names", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("DialogSignalGroupsTableWIdget", "User Name", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("DialogSignalGroupsTableWIdget", "Comment", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem3->setText(QApplication::translate("DialogSignalGroupsTableWIdget", "Enabled", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogSignalGroupsTableWIdget: public Ui_DialogSignalGroupsTableWIdget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGSIGNALGROUPSTABLEWIDGET_H
