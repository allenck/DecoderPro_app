/********************************************************************************
** Form generated from reading UI file 'paneleditor.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PANELEDITOR_H
#define UI_PANELEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
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
    QGraphicsView *editPanel;
    QMenuBar *menubar;
    QMenu *menuEdit;
    QMenu *menuMarker;
    QMenu *menuWindow;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *PanelEditor)
    {
        if (PanelEditor->objectName().isEmpty())
            PanelEditor->setObjectName(QString::fromUtf8("PanelEditor"));
        PanelEditor->resize(800, 600);
        actionOpenEditor = new QAction(PanelEditor);
        actionOpenEditor->setObjectName(QString::fromUtf8("actionOpenEditor"));
        actionDelete_this_panel = new QAction(PanelEditor);
        actionDelete_this_panel->setObjectName(QString::fromUtf8("actionDelete_this_panel"));
        actionAdd_loco = new QAction(PanelEditor);
        actionAdd_loco->setObjectName(QString::fromUtf8("actionAdd_loco"));
        actionAdd_Loco_from_roster = new QAction(PanelEditor);
        actionAdd_Loco_from_roster->setObjectName(QString::fromUtf8("actionAdd_Loco_from_roster"));
        actionRemove_markers = new QAction(PanelEditor);
        actionRemove_markers->setObjectName(QString::fromUtf8("actionRemove_markers"));
        centralwidget = new QWidget(PanelEditor);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        editPanel = new QGraphicsView(centralwidget);
        editPanel->setObjectName(QString::fromUtf8("editPanel"));

        verticalLayout->addWidget(editPanel);

        PanelEditor->setCentralWidget(centralwidget);
        menubar = new QMenuBar(PanelEditor);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuMarker = new QMenu(menubar);
        menuMarker->setObjectName(QString::fromUtf8("menuMarker"));
        menuWindow = new QMenu(menubar);
        menuWindow->setObjectName(QString::fromUtf8("menuWindow"));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        PanelEditor->setMenuBar(menubar);
        statusbar = new QStatusBar(PanelEditor);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
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
        PanelEditor->setWindowTitle(QCoreApplication::translate("PanelEditor", "MainWindow", nullptr));
        actionOpenEditor->setText(QCoreApplication::translate("PanelEditor", "Change view to Control Panel Editor", nullptr));
        actionDelete_this_panel->setText(QCoreApplication::translate("PanelEditor", "Delete this panel", nullptr));
        actionAdd_loco->setText(QCoreApplication::translate("PanelEditor", "Add Loco", nullptr));
        actionAdd_Loco_from_roster->setText(QCoreApplication::translate("PanelEditor", "Add Loco from roster", nullptr));
        actionRemove_markers->setText(QCoreApplication::translate("PanelEditor", "Remove markers", nullptr));
        menuEdit->setTitle(QCoreApplication::translate("PanelEditor", "Edit", nullptr));
        menuMarker->setTitle(QCoreApplication::translate("PanelEditor", "Marker", nullptr));
        menuWindow->setTitle(QCoreApplication::translate("PanelEditor", "Window", nullptr));
        menuFile->setTitle(QCoreApplication::translate("PanelEditor", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PanelEditor: public Ui_PanelEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PANELEDITOR_H
