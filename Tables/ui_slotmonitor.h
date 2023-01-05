/********************************************************************************
** Form generated from reading UI file 'slotmonitor.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SLOTMONITOR_H
#define UI_SLOTMONITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <jtable.h>

QT_BEGIN_NAMESPACE

class Ui_SlotMonitor
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QCheckBox *chkShowUnusedSlots;
    QCheckBox *chkShowSystemSlots;
    QPushButton *estopAllButton;
    JTable *tableView;
    QMenuBar *menubar;
    QMenu *menuWindows;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SlotMonitor)
    {
        if (SlotMonitor->objectName().isEmpty())
            SlotMonitor->setObjectName(QString::fromUtf8("SlotMonitor"));
        SlotMonitor->resize(800, 600);
        centralwidget = new QWidget(SlotMonitor);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        chkShowUnusedSlots = new QCheckBox(centralwidget);
        chkShowUnusedSlots->setObjectName(QString::fromUtf8("chkShowUnusedSlots"));
        chkShowUnusedSlots->setChecked(true);

        horizontalLayout->addWidget(chkShowUnusedSlots);

        chkShowSystemSlots = new QCheckBox(centralwidget);
        chkShowSystemSlots->setObjectName(QString::fromUtf8("chkShowSystemSlots"));
        chkShowSystemSlots->setChecked(true);

        horizontalLayout->addWidget(chkShowSystemSlots);

        estopAllButton = new QPushButton(centralwidget);
        estopAllButton->setObjectName(QString::fromUtf8("estopAllButton"));

        horizontalLayout->addWidget(estopAllButton);


        verticalLayout->addLayout(horizontalLayout);

        tableView = new JTable(centralwidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        verticalLayout->addWidget(tableView);

        SlotMonitor->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SlotMonitor);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 25));
        menuWindows = new QMenu(menubar);
        menuWindows->setObjectName(QString::fromUtf8("menuWindows"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        SlotMonitor->setMenuBar(menubar);
        statusbar = new QStatusBar(SlotMonitor);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        SlotMonitor->setStatusBar(statusbar);

        menubar->addAction(menuWindows->menuAction());
        menubar->addAction(menuHelp->menuAction());

        retranslateUi(SlotMonitor);

        QMetaObject::connectSlotsByName(SlotMonitor);
    } // setupUi

    void retranslateUi(QMainWindow *SlotMonitor)
    {
        SlotMonitor->setWindowTitle(QCoreApplication::translate("SlotMonitor", "LocoNet Slot Monitor", nullptr));
#if QT_CONFIG(tooltip)
        chkShowUnusedSlots->setToolTip(QCoreApplication::translate("SlotMonitor", "if checked, even empty/idle slots will appear", nullptr));
#endif // QT_CONFIG(tooltip)
        chkShowUnusedSlots->setText(QCoreApplication::translate("SlotMonitor", "Show Unused slots", nullptr));
#if QT_CONFIG(tooltip)
        chkShowSystemSlots->setToolTip(QCoreApplication::translate("SlotMonitor", "if checked, slots reserved for system use will be shown", nullptr));
#endif // QT_CONFIG(tooltip)
        chkShowSystemSlots->setText(QCoreApplication::translate("SlotMonitor", "Show System Slots", nullptr));
        estopAllButton->setText(QCoreApplication::translate("SlotMonitor", "estop All", nullptr));
        menuWindows->setTitle(QCoreApplication::translate("SlotMonitor", "Window", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("SlotMonitor", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SlotMonitor: public Ui_SlotMonitor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SLOTMONITOR_H
