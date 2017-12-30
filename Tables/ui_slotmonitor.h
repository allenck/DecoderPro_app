/********************************************************************************
** Form generated from reading UI file 'slotmonitor.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SLOTMONITOR_H
#define UI_SLOTMONITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
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
            SlotMonitor->setObjectName(QStringLiteral("SlotMonitor"));
        SlotMonitor->resize(800, 600);
        centralwidget = new QWidget(SlotMonitor);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        chkShowUnusedSlots = new QCheckBox(centralwidget);
        chkShowUnusedSlots->setObjectName(QStringLiteral("chkShowUnusedSlots"));
        chkShowUnusedSlots->setChecked(true);

        horizontalLayout->addWidget(chkShowUnusedSlots);

        chkShowSystemSlots = new QCheckBox(centralwidget);
        chkShowSystemSlots->setObjectName(QStringLiteral("chkShowSystemSlots"));
        chkShowSystemSlots->setChecked(true);

        horizontalLayout->addWidget(chkShowSystemSlots);

        estopAllButton = new QPushButton(centralwidget);
        estopAllButton->setObjectName(QStringLiteral("estopAllButton"));

        horizontalLayout->addWidget(estopAllButton);


        verticalLayout->addLayout(horizontalLayout);

        tableView = new JTable(centralwidget);
        tableView->setObjectName(QStringLiteral("tableView"));

        verticalLayout->addWidget(tableView);

        SlotMonitor->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SlotMonitor);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 25));
        menuWindows = new QMenu(menubar);
        menuWindows->setObjectName(QStringLiteral("menuWindows"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        SlotMonitor->setMenuBar(menubar);
        statusbar = new QStatusBar(SlotMonitor);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        SlotMonitor->setStatusBar(statusbar);

        menubar->addAction(menuWindows->menuAction());
        menubar->addAction(menuHelp->menuAction());

        retranslateUi(SlotMonitor);

        QMetaObject::connectSlotsByName(SlotMonitor);
    } // setupUi

    void retranslateUi(QMainWindow *SlotMonitor)
    {
        SlotMonitor->setWindowTitle(QApplication::translate("SlotMonitor", "LocoNet Slot Monitor", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        chkShowUnusedSlots->setToolTip(QApplication::translate("SlotMonitor", "if checked, even empty/idle slots will appear", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        chkShowUnusedSlots->setText(QApplication::translate("SlotMonitor", "Show Unused slots", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        chkShowSystemSlots->setToolTip(QApplication::translate("SlotMonitor", "if checked, slots reserved for system use will be shown", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        chkShowSystemSlots->setText(QApplication::translate("SlotMonitor", "Show System Slots", Q_NULLPTR));
        estopAllButton->setText(QApplication::translate("SlotMonitor", "estop All", Q_NULLPTR));
        menuWindows->setTitle(QApplication::translate("SlotMonitor", "Window", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("SlotMonitor", "Help", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SlotMonitor: public Ui_SlotMonitor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SLOTMONITOR_H
