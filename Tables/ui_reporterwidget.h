/********************************************************************************
** Form generated from reading UI file 'reporterwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REPORTERWIDGET_H
#define UI_REPORTERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ReporterWidget
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QTableWidget *tableWidget;
    QPushButton *btnAdd;

    void setupUi(QWidget *ReporterWidget)
    {
        if (ReporterWidget->objectName().isEmpty())
            ReporterWidget->setObjectName(QStringLiteral("ReporterWidget"));
        ReporterWidget->resize(400, 239);
        gridLayout = new QGridLayout(ReporterWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(ReporterWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 1, 2, 1, 1);

        tableWidget = new QTableWidget(ReporterWidget);
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
        tableWidget->setColumnCount(6);

        gridLayout->addWidget(tableWidget, 0, 0, 1, 3);

        btnAdd = new QPushButton(ReporterWidget);
        btnAdd->setObjectName(QStringLiteral("btnAdd"));

        gridLayout->addWidget(btnAdd, 1, 0, 1, 1);


        retranslateUi(ReporterWidget);

        QMetaObject::connectSlotsByName(ReporterWidget);
    } // setupUi

    void retranslateUi(QWidget *ReporterWidget)
    {
        ReporterWidget->setWindowTitle(QApplication::translate("ReporterWidget", "Form", 0));
        label->setText(QString());
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("ReporterWidget", "System Name", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("ReporterWidget", "UserName", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("ReporterWidget", "Report", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("ReporterWidget", "Comment", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem4->setText(QApplication::translate("ReporterWidget", "Last Report", 0));
        btnAdd->setText(QApplication::translate("ReporterWidget", "Add", 0));
    } // retranslateUi

};

namespace Ui {
    class ReporterWidget: public Ui_ReporterWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REPORTERWIDGET_H
