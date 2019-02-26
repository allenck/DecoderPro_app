/********************************************************************************
** Form generated from reading UI file 'slotmonitor.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
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
            SlotMonitor->setObjectName(QLatin1String("SlotMonitor"));
        SlotMonitor->resize(800, 600);
        centralwidget = new QWidget(SlotMonitor);
        centralwidget->setObjectName(QLatin1String("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QLatin1String("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QLatin1String("horizontalLayout"));
        chkShowUnusedSlots = new QCheckBox(centralwidget);
        chkShowUnusedSlots->setObjectName(QLatin1String("chkShowUnusedSlots"));
        chkShowUnusedSlots->setChecked(true);

        horizontalLayout->addWidget(chkShowUnusedSlots);

        chkShowSystemSlots = new QCheckBox(centralwidget);
        chkShowSystemSlots->setObjectName(QLatin1String("chkShowSystemSlots"));
        chkShowSystemSlots->setChecked(true);

        horizontalLayout->addWidget(chkShowSystemSlots);

        estopAllButton = new QPushButton(centralwidget);
        estopAllButton->setObjectName(QLatin1String("estopAllButton"));

        horizontalLayout->addWidget(estopAllButton);


        verticalLayout->addLayout(horizontalLayout);

        tableView = new JTable(centralwidget);
        tableView->setObjectName(QLatin1String("tableView"));

        verticalLayout->addWidget(tableView);

        SlotMonitor->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SlotMonitor);
        menubar->setObjectName(QLatin1String("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 25));
        menuWindows = new QMenu(menubar);
        menuWindows->setObjectName(QLatin1String("menuWindows"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QLatin1String("menuHelp"));
        SlotMonitor->setMenuBar(menubar);
        statusbar = new QStatusBar(SlotMonitor);
        statusbar->setObjectName(QLatin1String("statusbar"));
        SlotMonitor->setStatusBar(statusbar);

        menubar->addAction(menuWindows->menuAction());
        menubar->addAction(menuHelp->menuAction());

        retranslateUi(SlotMonitor);

        QMetaObject::connectSlotsByName(SlotMonitor);
    } // setupUi

    void retranslateUi(QMainWindow *SlotMonitor)
    {
        SlotMonitor->setWindowTitle(QApplication::translate("SlotMonitor", "LocoNet Slot Monitor", nullptr));
#ifndef QT_NO_TOOLTIP
        chkShowUnusedSlots->setToolTip(QApplication::translate("SlotMonitor", "if checked, even empty/idle slots will appear", nullptr));
#endif // QT_NO_TOOLTIP
        chkShowUnusedSlots->setText(QApplication::translate("SlotMonitor", "Show Unused slots", nullptr));
#ifndef QT_NO_TOOLTIP
        chkShowSystemSlots->setToolTip(QApplication::translate("SlotMonitor", "if checked, slots reserved for system use will be shown", nullptr));
#endif // QT_NO_TOOLTIP
        chkShowSystemSlots->setText(QApplication::translate("SlotMonitor", "Show System Slots", nullptr));
        estopAllButton->setText(QApplication::translate("SlotMonitor", "estop All", nullptr));
        menuWindows->setTitle(QApplication::translate("SlotMonitor", "Window", nullptr));
        menuHelp->setTitle(QApplication::translate("SlotMonitor", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SlotMonitor: public Ui_SlotMonitor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SLOTMONITOR_H
