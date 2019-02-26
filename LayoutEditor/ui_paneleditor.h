/********************************************************************************
** Form generated from reading UI file 'paneleditor.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PANELEDITOR_H
#define UI_PANELEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
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
            PanelEditor->setObjectName(QLatin1String("PanelEditor"));
        PanelEditor->resize(800, 600);
        actionOpenEditor = new QAction(PanelEditor);
        actionOpenEditor->setObjectName(QLatin1String("actionOpenEditor"));
        actionDelete_this_panel = new QAction(PanelEditor);
        actionDelete_this_panel->setObjectName(QLatin1String("actionDelete_this_panel"));
        actionAdd_loco = new QAction(PanelEditor);
        actionAdd_loco->setObjectName(QLatin1String("actionAdd_loco"));
        actionAdd_Loco_from_roster = new QAction(PanelEditor);
        actionAdd_Loco_from_roster->setObjectName(QLatin1String("actionAdd_Loco_from_roster"));
        actionRemove_markers = new QAction(PanelEditor);
        actionRemove_markers->setObjectName(QLatin1String("actionRemove_markers"));
        centralwidget = new QWidget(PanelEditor);
        centralwidget->setObjectName(QLatin1String("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QLatin1String("verticalLayout"));
        editPanel = new QWidget(centralwidget);
        editPanel->setObjectName(QLatin1String("editPanel"));

        verticalLayout->addWidget(editPanel);

        PanelEditor->setCentralWidget(centralwidget);
        menubar = new QMenuBar(PanelEditor);
        menubar->setObjectName(QLatin1String("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 25));
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName(QLatin1String("menuEdit"));
        menuMarker = new QMenu(menubar);
        menuMarker->setObjectName(QLatin1String("menuMarker"));
        menuWindow = new QMenu(menubar);
        menuWindow->setObjectName(QLatin1String("menuWindow"));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QLatin1String("menuFile"));
        PanelEditor->setMenuBar(menubar);
        statusbar = new QStatusBar(PanelEditor);
        statusbar->setObjectName(QLatin1String("statusbar"));
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
        PanelEditor->setWindowTitle(QApplication::translate("PanelEditor", "MainWindow", nullptr));
        actionOpenEditor->setText(QApplication::translate("PanelEditor", "Change view to Control Panel Editor", nullptr));
        actionDelete_this_panel->setText(QApplication::translate("PanelEditor", "Delete this panel", nullptr));
        actionAdd_loco->setText(QApplication::translate("PanelEditor", "Add Loco", nullptr));
        actionAdd_Loco_from_roster->setText(QApplication::translate("PanelEditor", "Add Loco from roster", nullptr));
        actionRemove_markers->setText(QApplication::translate("PanelEditor", "Remove markers", nullptr));
        menuEdit->setTitle(QApplication::translate("PanelEditor", "Edit", nullptr));
        menuMarker->setTitle(QApplication::translate("PanelEditor", "Marker", nullptr));
        menuWindow->setTitle(QApplication::translate("PanelEditor", "Window", nullptr));
        menuFile->setTitle(QApplication::translate("PanelEditor", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PanelEditor: public Ui_PanelEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PANELEDITOR_H
