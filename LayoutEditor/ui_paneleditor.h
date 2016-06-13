/********************************************************************************
** Form generated from reading UI file 'paneleditor.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PANELEDITOR_H
#define UI_PANELEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PanelEditor
{
public:
    QAction *actionOpenEditor;
    QAction *actionDelete_this_panel;
    QAction *actionAdd_loco;
    QAction *actionAdd_Loco_from_roster;
    QAction *actionRemove_markers;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QWidget *editPanel;
    QMenuBar *menubar;
    QMenu *menuEdit;
    QMenu *menuMarker;
    QMenu *menuWindow;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *PanelEditor)
    {
        if (PanelEditor->objectName().isEmpty())
            PanelEditor->setObjectName(QStringLiteral("PanelEditor"));
        PanelEditor->resize(800, 600);
        actionOpenEditor = new QAction(PanelEditor);
        actionOpenEditor->setObjectName(QStringLiteral("actionOpenEditor"));
        actionDelete_this_panel = new QAction(PanelEditor);
        actionDelete_this_panel->setObjectName(QStringLiteral("actionDelete_this_panel"));
        actionAdd_loco = new QAction(PanelEditor);
        actionAdd_loco->setObjectName(QStringLiteral("actionAdd_loco"));
        actionAdd_Loco_from_roster = new QAction(PanelEditor);
        actionAdd_Loco_from_roster->setObjectName(QStringLiteral("actionAdd_Loco_from_roster"));
        actionRemove_markers = new QAction(PanelEditor);
        actionRemove_markers->setObjectName(QStringLiteral("actionRemove_markers"));
        centralwidget = new QWidget(PanelEditor);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        editPanel = new QWidget(centralwidget);
        editPanel->setObjectName(QStringLiteral("editPanel"));

        verticalLayout->addWidget(editPanel);

        PanelEditor->setCentralWidget(centralwidget);
        menubar = new QMenuBar(PanelEditor);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 25));
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuMarker = new QMenu(menubar);
        menuMarker->setObjectName(QStringLiteral("menuMarker"));
        menuWindow = new QMenu(menubar);
        menuWindow->setObjectName(QStringLiteral("menuWindow"));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        PanelEditor->setMenuBar(menubar);
        statusbar = new QStatusBar(PanelEditor);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        PanelEditor->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuMarker->menuAction());
        menubar->addAction(menuWindow->menuAction());
        menuEdit->addSeparator();
        menuEdit->addAction(actionOpenEditor);
        menuEdit->addAction(actionDelete_this_panel);
        menuMarker->addAction(actionAdd_loco);
        menuMarker->addAction(actionAdd_Loco_from_roster);
        menuMarker->addAction(actionRemove_markers);

        retranslateUi(PanelEditor);

        QMetaObject::connectSlotsByName(PanelEditor);
    } // setupUi

    void retranslateUi(QMainWindow *PanelEditor)
    {
        PanelEditor->setWindowTitle(QApplication::translate("PanelEditor", "MainWindow", 0));
        actionOpenEditor->setText(QApplication::translate("PanelEditor", "Change view to Control Panel Editor", 0));
        actionDelete_this_panel->setText(QApplication::translate("PanelEditor", "Delete this panel", 0));
        actionAdd_loco->setText(QApplication::translate("PanelEditor", "Add Loco", 0));
        actionAdd_Loco_from_roster->setText(QApplication::translate("PanelEditor", "Add Loco from roster", 0));
        actionRemove_markers->setText(QApplication::translate("PanelEditor", "Remove markers", 0));
        menuEdit->setTitle(QApplication::translate("PanelEditor", "Edit", 0));
        menuMarker->setTitle(QApplication::translate("PanelEditor", "Marker", 0));
        menuWindow->setTitle(QApplication::translate("PanelEditor", "Window", 0));
        menuFile->setTitle(QApplication::translate("PanelEditor", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class PanelEditor: public Ui_PanelEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PANELEDITOR_H
