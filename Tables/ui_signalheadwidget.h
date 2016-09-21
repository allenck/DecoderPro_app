/********************************************************************************
** Form generated from reading UI file 'signalheadwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNALHEADWIDGET_H
#define UI_SIGNALHEADWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_SignalHeadWidget
{
public:
    QGridLayout *gridLayout;
    QTableWidget *tableWidget;
    QPushButton *btnAdd;

    void setupUi(QDialog *SignalHeadWidget)
    {
        if (SignalHeadWidget->objectName().isEmpty())
            SignalHeadWidget->setObjectName(QStringLiteral("SignalHeadWidget"));
        SignalHeadWidget->resize(400, 294);
        gridLayout = new QGridLayout(SignalHeadWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tableWidget = new QTableWidget(SignalHeadWidget);
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

        gridLayout->addWidget(tableWidget, 0, 0, 1, 1);

        btnAdd = new QPushButton(SignalHeadWidget);
        btnAdd->setObjectName(QStringLiteral("btnAdd"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnAdd->sizePolicy().hasHeightForWidth());
        btnAdd->setSizePolicy(sizePolicy);

        gridLayout->addWidget(btnAdd, 1, 0, 1, 1);


        retranslateUi(SignalHeadWidget);

        QMetaObject::connectSlotsByName(SignalHeadWidget);
    } // setupUi

    void retranslateUi(QDialog *SignalHeadWidget)
    {
        SignalHeadWidget->setWindowTitle(QApplication::translate("SignalHeadWidget", "Dialog", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("SignalHeadWidget", "System Name", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("SignalHeadWidget", "User Name", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("SignalHeadWidget", "State", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("SignalHeadWidget", "Comment", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem4->setText(QApplication::translate("SignalHeadWidget", "Lit", 0));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem5->setText(QApplication::translate("SignalHeadWidget", "Held", 0));
        btnAdd->setText(QApplication::translate("SignalHeadWidget", "Add", 0));
    } // retranslateUi

};

namespace Ui {
    class SignalHeadWidget: public Ui_SignalHeadWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNALHEADWIDGET_H
