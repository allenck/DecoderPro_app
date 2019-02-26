/********************************************************************************
** Form generated from reading UI file 'paneprogframe.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PANEPROGFRAME_H
#define UI_PANEPROGFRAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
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
            PaneProgFrame->setObjectName(QLatin1String("PaneProgFrame"));
        PaneProgFrame->resize(575, 295);
        QFont font;
        font.setFamily(QLatin1String("Ubuntu"));
        font.setPointSize(8);
        PaneProgFrame->setFont(font);
        actionSave = new QAction(PaneProgFrame);
        actionSave->setObjectName(QLatin1String("actionSave"));
        actionFactory_reset = new QAction(PaneProgFrame);
        actionFactory_reset->setObjectName(QLatin1String("actionFactory_reset"));
        centralwidget = new QWidget(PaneProgFrame);
        centralwidget->setObjectName(QLatin1String("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QLatin1String("verticalLayout"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QLatin1String("tabWidget"));
        QFont font1;
        font1.setPointSize(8);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(50);
        tabWidget->setFont(font1);
        tabWidget->setUsesScrollButtons(true);
        rosterEntryTab = new QWidget();
        rosterEntryTab->setObjectName(QLatin1String("rosterEntryTab"));
        gridLayout = new QGridLayout(rosterEntryTab);
        gridLayout->setObjectName(QLatin1String("gridLayout"));
        gridLayout->setVerticalSpacing(2);
        gridLayout->setContentsMargins(-1, 6, -1, 6);
        tabWidget->addTab(rosterEntryTab, QString());

        verticalLayout->addWidget(tabWidget);

        PaneProgFrame->setCentralWidget(centralwidget);
        menubar = new QMenuBar(PaneProgFrame);
        menubar->setObjectName(QLatin1String("menubar"));
        menubar->setGeometry(QRect(0, 0, 575, 20));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QLatin1String("menuFile"));
        menuReset = new QMenu(menubar);
        menuReset->setObjectName(QLatin1String("menuReset"));
        PaneProgFrame->setMenuBar(menubar);
        statusbar = new QStatusBar(PaneProgFrame);
        statusbar->setObjectName(QLatin1String("statusbar"));
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
        PaneProgFrame->setWindowTitle(QApplication::translate("PaneProgFrame", "MainWindow", nullptr));
        actionSave->setText(QApplication::translate("PaneProgFrame", "Save", nullptr));
        actionFactory_reset->setText(QApplication::translate("PaneProgFrame", "Factory reset", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(rosterEntryTab), QApplication::translate("PaneProgFrame", "Roster Entry", nullptr));
        menuFile->setTitle(QApplication::translate("PaneProgFrame", "File", nullptr));
        menuReset->setTitle(QApplication::translate("PaneProgFrame", "Reset", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PaneProgFrame: public Ui_PaneProgFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PANEPROGFRAME_H
