/********************************************************************************
** Form generated from reading UI file 'throttlewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_THROTTLEWINDOW_H
#define UI_THROTTLEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ThrottleWindow
{
public:
    QAction *actionPower_On;
    QAction *actionPower_Off;
    QAction *actionAddress_Panel;
    QAction *actionControl_Panel;
    QAction *actionFunction_Panel;
    QAction *actionReset_function_buttons;
    QAction *actionGet_all_throttle_components_in_bounds;
    QAction *actionSwitch_throttle_frame_view_mode;
    QAction *actionSHow_Hide_throttles_list_window;
    QAction *actionNew_Throttle;
    QAction *actionOpenthrottle;
    QAction *actionSave_current_throttle;
    QAction *actionSave_current_throttle_as;
    QAction *actionOpen_throttles_layout;
    QAction *actionSave_throttles_layout;
    QAction *actionLoad_default_throttles_layout;
    QAction *actionSave_as_defautl_throttles_layout;
    QWidget *centralwidget;
    QFormLayout *formLayout_2;
    QLabel *label;
    QLabel *label_2;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuView;
    QMenu *menuPower;
    QMenu *menuWindow;
    QMenu *menuHelp;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *ThrottleWindow)
    {
        if (ThrottleWindow->objectName().isEmpty())
            ThrottleWindow->setObjectName(QLatin1String("ThrottleWindow"));
        ThrottleWindow->resize(297, 737);
        QFont font;
        font.setPointSize(8);
        ThrottleWindow->setFont(font);
        actionPower_On = new QAction(ThrottleWindow);
        actionPower_On->setObjectName(QLatin1String("actionPower_On"));
        actionPower_Off = new QAction(ThrottleWindow);
        actionPower_Off->setObjectName(QLatin1String("actionPower_Off"));
        actionAddress_Panel = new QAction(ThrottleWindow);
        actionAddress_Panel->setObjectName(QLatin1String("actionAddress_Panel"));
        actionAddress_Panel->setCheckable(true);
        actionAddress_Panel->setChecked(true);
        actionControl_Panel = new QAction(ThrottleWindow);
        actionControl_Panel->setObjectName(QLatin1String("actionControl_Panel"));
        actionControl_Panel->setCheckable(true);
        actionControl_Panel->setChecked(true);
        actionFunction_Panel = new QAction(ThrottleWindow);
        actionFunction_Panel->setObjectName(QLatin1String("actionFunction_Panel"));
        actionFunction_Panel->setCheckable(true);
        actionFunction_Panel->setChecked(true);
        actionReset_function_buttons = new QAction(ThrottleWindow);
        actionReset_function_buttons->setObjectName(QLatin1String("actionReset_function_buttons"));
        actionGet_all_throttle_components_in_bounds = new QAction(ThrottleWindow);
        actionGet_all_throttle_components_in_bounds->setObjectName(QLatin1String("actionGet_all_throttle_components_in_bounds"));
        actionSwitch_throttle_frame_view_mode = new QAction(ThrottleWindow);
        actionSwitch_throttle_frame_view_mode->setObjectName(QLatin1String("actionSwitch_throttle_frame_view_mode"));
        actionSHow_Hide_throttles_list_window = new QAction(ThrottleWindow);
        actionSHow_Hide_throttles_list_window->setObjectName(QLatin1String("actionSHow_Hide_throttles_list_window"));
        actionNew_Throttle = new QAction(ThrottleWindow);
        actionNew_Throttle->setObjectName(QLatin1String("actionNew_Throttle"));
        actionOpenthrottle = new QAction(ThrottleWindow);
        actionOpenthrottle->setObjectName(QLatin1String("actionOpenthrottle"));
        actionSave_current_throttle = new QAction(ThrottleWindow);
        actionSave_current_throttle->setObjectName(QLatin1String("actionSave_current_throttle"));
        actionSave_current_throttle_as = new QAction(ThrottleWindow);
        actionSave_current_throttle_as->setObjectName(QLatin1String("actionSave_current_throttle_as"));
        actionOpen_throttles_layout = new QAction(ThrottleWindow);
        actionOpen_throttles_layout->setObjectName(QLatin1String("actionOpen_throttles_layout"));
        actionSave_throttles_layout = new QAction(ThrottleWindow);
        actionSave_throttles_layout->setObjectName(QLatin1String("actionSave_throttles_layout"));
        actionLoad_default_throttles_layout = new QAction(ThrottleWindow);
        actionLoad_default_throttles_layout->setObjectName(QLatin1String("actionLoad_default_throttles_layout"));
        actionSave_as_defautl_throttles_layout = new QAction(ThrottleWindow);
        actionSave_as_defautl_throttles_layout->setObjectName(QLatin1String("actionSave_as_defautl_throttles_layout"));
        centralwidget = new QWidget(ThrottleWindow);
        centralwidget->setObjectName(QLatin1String("centralwidget"));
        formLayout_2 = new QFormLayout(centralwidget);
        formLayout_2->setObjectName(QLatin1String("formLayout_2"));
        label = new QLabel(centralwidget);
        label->setObjectName(QLatin1String("label"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QLatin1String("label_2"));
        QFont font1;
        font1.setPointSize(9);
        label_2->setFont(font1);

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_2);

        ThrottleWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ThrottleWindow);
        menubar->setObjectName(QLatin1String("menubar"));
        menubar->setGeometry(QRect(0, 0, 297, 22));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QLatin1String("menuFile"));
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName(QLatin1String("menuEdit"));
        menuView = new QMenu(menubar);
        menuView->setObjectName(QLatin1String("menuView"));
        menuPower = new QMenu(menubar);
        menuPower->setObjectName(QLatin1String("menuPower"));
        menuWindow = new QMenu(menubar);
        menuWindow->setObjectName(QLatin1String("menuWindow"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QLatin1String("menuHelp"));
        ThrottleWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(ThrottleWindow);
        statusbar->setObjectName(QLatin1String("statusbar"));
        ThrottleWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(ThrottleWindow);
        toolBar->setObjectName(QLatin1String("toolBar"));
        ThrottleWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuView->menuAction());
        menubar->addAction(menuPower->menuAction());
        menubar->addAction(menuWindow->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionNew_Throttle);
        menuFile->addAction(actionOpenthrottle);
        menuFile->addAction(actionSave_current_throttle);
        menuFile->addAction(actionSave_current_throttle_as);
        menuFile->addSeparator();
        menuFile->addAction(actionOpen_throttles_layout);
        menuFile->addAction(actionSave_throttles_layout);
        menuFile->addSeparator();
        menuFile->addAction(actionLoad_default_throttles_layout);
        menuFile->addAction(actionSave_as_defautl_throttles_layout);
        menuView->addAction(actionAddress_Panel);
        menuView->addAction(actionControl_Panel);
        menuView->addAction(actionFunction_Panel);
        menuView->addSeparator();
        menuView->addAction(actionReset_function_buttons);
        menuView->addAction(actionGet_all_throttle_components_in_bounds);
        menuView->addSeparator();
        menuView->addAction(actionSwitch_throttle_frame_view_mode);
        menuView->addSeparator();
        menuView->addAction(actionSHow_Hide_throttles_list_window);
        menuPower->addAction(actionPower_On);
        menuPower->addAction(actionPower_Off);

        retranslateUi(ThrottleWindow);

        QMetaObject::connectSlotsByName(ThrottleWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ThrottleWindow)
    {
        ThrottleWindow->setWindowTitle(QApplication::translate("ThrottleWindow", "MainWindow", nullptr));
        actionPower_On->setText(QApplication::translate("ThrottleWindow", "Power On", nullptr));
        actionPower_Off->setText(QApplication::translate("ThrottleWindow", "Power Off", nullptr));
        actionAddress_Panel->setText(QApplication::translate("ThrottleWindow", "Address Panel", nullptr));
        actionControl_Panel->setText(QApplication::translate("ThrottleWindow", "Control Panel", nullptr));
        actionFunction_Panel->setText(QApplication::translate("ThrottleWindow", "Function Panel", nullptr));
        actionReset_function_buttons->setText(QApplication::translate("ThrottleWindow", "Reset function buttons", nullptr));
        actionGet_all_throttle_components_in_bounds->setText(QApplication::translate("ThrottleWindow", "Get all throttle components in bounds", nullptr));
        actionSwitch_throttle_frame_view_mode->setText(QApplication::translate("ThrottleWindow", "Switch throttle frame view mode", nullptr));
        actionSHow_Hide_throttles_list_window->setText(QApplication::translate("ThrottleWindow", "Show/Hide throttles list window", nullptr));
        actionNew_Throttle->setText(QApplication::translate("ThrottleWindow", "New Throttle", nullptr));
        actionOpenthrottle->setText(QApplication::translate("ThrottleWindow", "openthrottle", nullptr));
        actionSave_current_throttle->setText(QApplication::translate("ThrottleWindow", "Save current throttle", nullptr));
        actionSave_current_throttle_as->setText(QApplication::translate("ThrottleWindow", "Save current throttle as...", nullptr));
        actionOpen_throttles_layout->setText(QApplication::translate("ThrottleWindow", "Open throttles layout...", nullptr));
        actionSave_throttles_layout->setText(QApplication::translate("ThrottleWindow", "Save throttles layout...", nullptr));
        actionLoad_default_throttles_layout->setText(QApplication::translate("ThrottleWindow", "Load default throttles layout", nullptr));
        actionSave_as_defautl_throttles_layout->setText(QApplication::translate("ThrottleWindow", "Save as defautl throttles layout", nullptr));
        label->setText(QString());
        label_2->setText(QString());
        menuFile->setTitle(QApplication::translate("ThrottleWindow", "File", nullptr));
        menuEdit->setTitle(QApplication::translate("ThrottleWindow", "Edit", nullptr));
        menuView->setTitle(QApplication::translate("ThrottleWindow", "View", nullptr));
        menuPower->setTitle(QApplication::translate("ThrottleWindow", "Power", nullptr));
        menuWindow->setTitle(QApplication::translate("ThrottleWindow", "Window", nullptr));
        menuHelp->setTitle(QApplication::translate("ThrottleWindow", "Help", nullptr));
        toolBar->setWindowTitle(QApplication::translate("ThrottleWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ThrottleWindow: public Ui_ThrottleWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_THROTTLEWINDOW_H
