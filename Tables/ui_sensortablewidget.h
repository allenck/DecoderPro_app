/********************************************************************************
** Form generated from reading UI file 'sensortablewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SENSORTABLEWIDGET_H
#define UI_SENSORTABLEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <jtable.h>

QT_BEGIN_NAMESPACE

class Ui_SensorTableWidget
{
public:
    QVBoxLayout *verticalLayout;
    JTable *tableView;

    void setupUi(QWidget *SensorTableWidget)
    {
        if (SensorTableWidget->objectName().isEmpty())
            SensorTableWidget->setObjectName(QStringLiteral("SensorTableWidget"));
        SensorTableWidget->resize(274, 210);
        verticalLayout = new QVBoxLayout(SensorTableWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tableView = new JTable(SensorTableWidget);
        tableView->setObjectName(QStringLiteral("tableView"));

        verticalLayout->addWidget(tableView);


        retranslateUi(SensorTableWidget);

        QMetaObject::connectSlotsByName(SensorTableWidget);
    } // setupUi

    void retranslateUi(QWidget *SensorTableWidget)
    {
        SensorTableWidget->setWindowTitle(QApplication::translate("SensorTableWidget", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SensorTableWidget: public Ui_SensorTableWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENSORTABLEWIDGET_H
