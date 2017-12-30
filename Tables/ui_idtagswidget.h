/********************************************************************************
** Form generated from reading UI file 'idtagswidget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IDTAGSWIDGET_H
#define UI_IDTAGSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IdTagsWidget
{
public:
    QGridLayout *gridLayout;
    QPushButton *btnAdd;
    QCheckBox *chkSaveWhen;
    QCheckBox *chkFastClock;
    QTableWidget *tableWidget;

    void setupUi(QWidget *IdTagsWidget)
    {
        if (IdTagsWidget->objectName().isEmpty())
            IdTagsWidget->setObjectName(QStringLiteral("IdTagsWidget"));
        IdTagsWidget->resize(521, 300);
        gridLayout = new QGridLayout(IdTagsWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        btnAdd = new QPushButton(IdTagsWidget);
        btnAdd->setObjectName(QStringLiteral("btnAdd"));

        gridLayout->addWidget(btnAdd, 1, 0, 1, 1);

        chkSaveWhen = new QCheckBox(IdTagsWidget);
        chkSaveWhen->setObjectName(QStringLiteral("chkSaveWhen"));

        gridLayout->addWidget(chkSaveWhen, 1, 1, 1, 1);

        chkFastClock = new QCheckBox(IdTagsWidget);
        chkFastClock->setObjectName(QStringLiteral("chkFastClock"));

        gridLayout->addWidget(chkFastClock, 1, 2, 1, 1);

        tableWidget = new QTableWidget(IdTagsWidget);
        if (tableWidget->columnCount() < 18)
            tableWidget->setColumnCount(18);
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
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setColumnCount(18);

        gridLayout->addWidget(tableWidget, 0, 0, 1, 3);


        retranslateUi(IdTagsWidget);

        QMetaObject::connectSlotsByName(IdTagsWidget);
    } // setupUi

    void retranslateUi(QWidget *IdTagsWidget)
    {
        IdTagsWidget->setWindowTitle(QApplication::translate("IdTagsWidget", "Form", Q_NULLPTR));
        btnAdd->setText(QApplication::translate("IdTagsWidget", "Add...", Q_NULLPTR));
        chkSaveWhen->setText(QApplication::translate("IdTagsWidget", "Save when and where last seen", Q_NULLPTR));
        chkFastClock->setText(QApplication::translate("IdTagsWidget", "Use Fast Clock Time", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("IdTagsWidget", "System Name", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("IdTagsWidget", "User Name", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("IdTagsWidget", "Tag ID", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("IdTagsWidget", "Comment", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem4->setText(QApplication::translate("IdTagsWidget", "Where seen", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem5->setText(QApplication::translate("IdTagsWidget", "When seen", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(8);
        ___qtablewidgetitem6->setText(QApplication::translate("IdTagsWidget", "Roster Id", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class IdTagsWidget: public Ui_IdTagsWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IDTAGSWIDGET_H
