/********************************************************************************
** Form generated from reading UI file 'routewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROUTEWIDGET_H
#define UI_ROUTEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_RouteWidget
{
public:
    QGridLayout *gridLayout;
    QPushButton *btnAdd;
    QLabel *label;
    QTableWidget *tableWidget;

    void setupUi(QDialog *RouteWidget)
    {
        if (RouteWidget->objectName().isEmpty())
            RouteWidget->setObjectName(QStringLiteral("RouteWidget"));
        RouteWidget->resize(400, 272);
        gridLayout = new QGridLayout(RouteWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        btnAdd = new QPushButton(RouteWidget);
        btnAdd->setObjectName(QStringLiteral("btnAdd"));
        btnAdd->setMaximumSize(QSize(80, 16777215));

        gridLayout->addWidget(btnAdd, 1, 0, 1, 1);

        label = new QLabel(RouteWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 1, 1, 1, 1);

        tableWidget = new QTableWidget(RouteWidget);
        if (tableWidget->columnCount() < 8)
            tableWidget->setColumnCount(8);
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
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        gridLayout->addWidget(tableWidget, 0, 0, 1, 2);


        retranslateUi(RouteWidget);

        QMetaObject::connectSlotsByName(RouteWidget);
    } // setupUi

    void retranslateUi(QDialog *RouteWidget)
    {
        RouteWidget->setWindowTitle(QApplication::translate("RouteWidget", "Dialog", 0));
        btnAdd->setText(QApplication::translate("RouteWidget", "Add", 0));
        label->setText(QString());
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("RouteWidget", "System Name", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("RouteWidget", "User Name", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem2->setText(QApplication::translate("RouteWidget", "Comment", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem3->setText(QApplication::translate("RouteWidget", "Enabled", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem4->setText(QApplication::translate("RouteWidget", "Locked", 0));
    } // retranslateUi

};

namespace Ui {
    class RouteWidget: public Ui_RouteWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROUTEWIDGET_H
