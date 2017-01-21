/********************************************************************************
** Form generated from reading UI file 'paneprogframe.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PANEPROGFRAME_H
#define UI_PANEPROGFRAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PaneProgFrame
{
public:
    QAction *actionSave;
    QAction *actionFactory_reset;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *rosterEntryTab;
    QGridLayout *gridLayout;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuReset;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *PaneProgFrame)
    {
        if (PaneProgFrame->objectName().isEmpty())
            PaneProgFrame->setObjectName(QStringLiteral("PaneProgFrame"));
        PaneProgFrame->resize(575, 295);
        QFont font;
        font.setFamily(QStringLiteral("Ubuntu"));
        font.setPointSize(8);
        PaneProgFrame->setFont(font);
        actionSave = new QAction(PaneProgFrame);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionFactory_reset = new QAction(PaneProgFrame);
        actionFactory_reset->setObjectName(QStringLiteral("actionFactory_reset"));
        centralwidget = new QWidget(PaneProgFrame);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        QFont font1;
        font1.setPointSize(8);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(50);
        tabWidget->setFont(font1);
        tabWidget->setUsesScrollButtons(true);
        rosterEntryTab = new QWidget();
        rosterEntryTab->setObjectName(QStringLiteral("rosterEntryTab"));
        gridLayout = new QGridLayout(rosterEntryTab);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setVerticalSpacing(2);
        gridLayout->setContentsMargins(-1, 6, -1, 6);
        tabWidget->addTab(rosterEntryTab, QString());

        verticalLayout->addWidget(tabWidget);

        PaneProgFrame->setCentralWidget(centralwidget);
        menubar = new QMenuBar(PaneProgFrame);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 575, 20));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuReset = new QMenu(menubar);
        menuReset->setObjectName(QStringLiteral("menuReset"));
        PaneProgFrame->setMenuBar(menubar);
        statusbar = new QStatusBar(PaneProgFrame);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        PaneProgFrame->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuReset->menuAction());
        menuFile->addAction(actionSave);
        menuReset->addAction(actionFactory_reset);

        retranslateUi(PaneProgFrame);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PaneProgFrame);
    } // setupUi

    void retranslateUi(QMainWindow *PaneProgFrame)
    {
        PaneProgFrame->setWindowTitle(QApplication::translate("PaneProgFrame", "MainWindow", 0));
        actionSave->setText(QApplication::translate("PaneProgFrame", "Save", 0));
        actionFactory_reset->setText(QApplication::translate("PaneProgFrame", "Factory reset", 0));
        tabWidget->setTabText(tabWidget->indexOf(rosterEntryTab), QApplication::translate("PaneProgFrame", "Roster Entry", 0));
        menuFile->setTitle(QApplication::translate("PaneProgFrame", "File", 0));
        menuReset->setTitle(QApplication::translate("PaneProgFrame", "Reset", 0));
    } // retranslateUi

};

namespace Ui {
    class PaneProgFrame: public Ui_PaneProgFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PANEPROGFRAME_H
