/********************************************************************************
** Form generated from reading UI file 'listthrottles.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LISTTHROTTLES_H
#define UI_LISTTHROTTLES_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ListThrottles
{
public:
    QWidget *centralwidget;
    QFormLayout *formLayout;
    QTableWidget *tableWidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *ListThrottles)
    {
        if (ListThrottles->objectName().isEmpty())
            ListThrottles->setObjectName(QStringLiteral("ListThrottles"));
        ListThrottles->resize(346, 244);
        centralwidget = new QWidget(ListThrottles);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        formLayout = new QFormLayout(centralwidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        tableWidget = new QTableWidget(centralwidget);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setColumnCount(0);
        tableWidget->horizontalHeader()->setVisible(false);
        tableWidget->horizontalHeader()->setStretchLastSection(true);
        tableWidget->verticalHeader()->setStretchLastSection(false);

        formLayout->setWidget(0, QFormLayout::SpanningRole, tableWidget);

        ListThrottles->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ListThrottles);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 346, 25));
        ListThrottles->setMenuBar(menubar);
        statusbar = new QStatusBar(ListThrottles);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        ListThrottles->setStatusBar(statusbar);
        toolBar = new QToolBar(ListThrottles);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        ListThrottles->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(ListThrottles);

        QMetaObject::connectSlotsByName(ListThrottles);
    } // setupUi

    void retranslateUi(QMainWindow *ListThrottles)
    {
        ListThrottles->setWindowTitle(QApplication::translate("ListThrottles", "Local Throttles", 0));
        toolBar->setWindowTitle(QApplication::translate("ListThrottles", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class ListThrottles: public Ui_ListThrottles {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISTTHROTTLES_H
