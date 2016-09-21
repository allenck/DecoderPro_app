/********************************************************************************
** Form generated from reading UI file 'functionlabelsmediadlg.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FUNCTIONLABELSMEDIADLG_H
#define UI_FUNCTIONLABELSMEDIADLG_H

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

class Ui_FunctionLabelsMediaDlg
{
public:
    QAction *actionFacttory_Reset;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout;
    QWidget *tab_2;
    QGridLayout *gridLayout_2;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuReset;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *FunctionLabelsMediaDlg)
    {
        if (FunctionLabelsMediaDlg->objectName().isEmpty())
            FunctionLabelsMediaDlg->setObjectName(QStringLiteral("FunctionLabelsMediaDlg"));
        FunctionLabelsMediaDlg->resize(800, 310);
        QFont font;
        font.setPointSize(8);
        FunctionLabelsMediaDlg->setFont(font);
        actionFacttory_Reset = new QAction(FunctionLabelsMediaDlg);
        actionFacttory_Reset->setObjectName(QStringLiteral("actionFacttory_Reset"));
        centralwidget = new QWidget(FunctionLabelsMediaDlg);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout = new QGridLayout(tab);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        gridLayout_2 = new QGridLayout(tab_2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        tabWidget->addTab(tab_2, QString());

        verticalLayout->addWidget(tabWidget);

        FunctionLabelsMediaDlg->setCentralWidget(centralwidget);
        menubar = new QMenuBar(FunctionLabelsMediaDlg);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 20));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuReset = new QMenu(menubar);
        menuReset->setObjectName(QStringLiteral("menuReset"));
        FunctionLabelsMediaDlg->setMenuBar(menubar);
        statusbar = new QStatusBar(FunctionLabelsMediaDlg);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        FunctionLabelsMediaDlg->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuReset->menuAction());
        menuReset->addAction(actionFacttory_Reset);

        retranslateUi(FunctionLabelsMediaDlg);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(FunctionLabelsMediaDlg);
    } // setupUi

    void retranslateUi(QMainWindow *FunctionLabelsMediaDlg)
    {
        FunctionLabelsMediaDlg->setWindowTitle(QApplication::translate("FunctionLabelsMediaDlg", "MainWindow", 0));
        actionFacttory_Reset->setText(QApplication::translate("FunctionLabelsMediaDlg", "Facttory Reset", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("FunctionLabelsMediaDlg", "Function Labels", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("FunctionLabelsMediaDlg", "Roster Media", 0));
        menuFile->setTitle(QApplication::translate("FunctionLabelsMediaDlg", "File", 0));
        menuReset->setTitle(QApplication::translate("FunctionLabelsMediaDlg", "Reset", 0));
    } // retranslateUi

};

namespace Ui {
    class FunctionLabelsMediaDlg: public Ui_FunctionLabelsMediaDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FUNCTIONLABELSMEDIADLG_H
