/********************************************************************************
** Form generated from reading UI file 'addpaneleditordialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDPANELEDITORDIALOG_H
#define UI_ADDPANELEDITORDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddPanelEditorDialog
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *edX;
    QLabel *label_2;
    QLineEdit *edY;
    QPushButton *btnSetName;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QPushButton *btnAddText;
    QLineEdit *edText;
    QVBoxLayout *verticalLayout;
    QLabel *label_4;
    QComboBox *cbType;
    QCheckBox *chkPopup;
    QCheckBox *chkReposition;
    QCheckBox *chkControlLayout;
    QCheckBox *chkShowHidden;
    QCheckBox *chkShowTooltips;
    QCheckBox *chkHasMenu;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QComboBox *cbScrollBars;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuWindow;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *AddPanelEditorDialog)
    {
        if (AddPanelEditorDialog->objectName().isEmpty())
            AddPanelEditorDialog->setObjectName(QLatin1String("AddPanelEditorDialog"));
        AddPanelEditorDialog->resize(332, 427);
        centralwidget = new QWidget(AddPanelEditorDialog);
        centralwidget->setObjectName(QLatin1String("centralwidget"));
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QLatin1String("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QLatin1String("horizontalLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QLatin1String("label"));

        horizontalLayout->addWidget(label);

        edX = new QLineEdit(centralwidget);
        edX->setObjectName(QLatin1String("edX"));
        edX->setMaximumSize(QSize(60, 16777215));
        edX->setInputMethodHints(Qt::ImhNone);

        horizontalLayout->addWidget(edX);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QLatin1String("label_2"));

        horizontalLayout->addWidget(label_2);

        edY = new QLineEdit(centralwidget);
        edY->setObjectName(QLatin1String("edY"));
        edY->setMaximumSize(QSize(60, 16777215));
        edY->setInputMethodHints(Qt::ImhNone);

        horizontalLayout->addWidget(edY);


        verticalLayout_2->addLayout(horizontalLayout);

        btnSetName = new QPushButton(centralwidget);
        btnSetName->setObjectName(QLatin1String("btnSetName"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnSetName->sizePolicy().hasHeightForWidth());
        btnSetName->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(btnSetName);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QLatin1String("horizontalLayout_2"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QLatin1String("label_3"));

        horizontalLayout_2->addWidget(label_3);

        btnAddText = new QPushButton(centralwidget);
        btnAddText->setObjectName(QLatin1String("btnAddText"));
        btnAddText->setEnabled(false);

        horizontalLayout_2->addWidget(btnAddText);

        edText = new QLineEdit(centralwidget);
        edText->setObjectName(QLatin1String("edText"));

        horizontalLayout_2->addWidget(edText);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QLatin1String("verticalLayout"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QLatin1String("label_4"));

        verticalLayout->addWidget(label_4);

        cbType = new QComboBox(centralwidget);
        cbType->addItem(QString());
        cbType->addItem(QString());
        cbType->addItem(QString());
        cbType->addItem(QString());
        cbType->addItem(QString());
        cbType->addItem(QString());
        cbType->addItem(QString());
        cbType->addItem(QString());
        cbType->addItem(QString());
        cbType->addItem(QString());
        cbType->addItem(QString());
        cbType->addItem(QString());
        cbType->addItem(QString());
        cbType->addItem(QString());
        cbType->addItem(QString());
        cbType->setObjectName(QLatin1String("cbType"));

        verticalLayout->addWidget(cbType);


        verticalLayout_2->addLayout(verticalLayout);

        chkPopup = new QCheckBox(centralwidget);
        chkPopup->setObjectName(QLatin1String("chkPopup"));
        chkPopup->setChecked(true);

        verticalLayout_2->addWidget(chkPopup);

        chkReposition = new QCheckBox(centralwidget);
        chkReposition->setObjectName(QLatin1String("chkReposition"));
        chkReposition->setChecked(true);

        verticalLayout_2->addWidget(chkReposition);

        chkControlLayout = new QCheckBox(centralwidget);
        chkControlLayout->setObjectName(QLatin1String("chkControlLayout"));
        chkControlLayout->setChecked(true);

        verticalLayout_2->addWidget(chkControlLayout);

        chkShowHidden = new QCheckBox(centralwidget);
        chkShowHidden->setObjectName(QLatin1String("chkShowHidden"));
        chkShowHidden->setEnabled(false);

        verticalLayout_2->addWidget(chkShowHidden);

        chkShowTooltips = new QCheckBox(centralwidget);
        chkShowTooltips->setObjectName(QLatin1String("chkShowTooltips"));
        chkShowTooltips->setChecked(true);

        verticalLayout_2->addWidget(chkShowTooltips);

        chkHasMenu = new QCheckBox(centralwidget);
        chkHasMenu->setObjectName(QLatin1String("chkHasMenu"));
        chkHasMenu->setChecked(true);

        verticalLayout_2->addWidget(chkHasMenu);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QLatin1String("horizontalLayout_3"));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QLatin1String("label_5"));

        horizontalLayout_3->addWidget(label_5);

        cbScrollBars = new QComboBox(centralwidget);
        cbScrollBars->addItem(QString());
        cbScrollBars->addItem(QString());
        cbScrollBars->addItem(QString());
        cbScrollBars->addItem(QString());
        cbScrollBars->setObjectName(QLatin1String("cbScrollBars"));

        horizontalLayout_3->addWidget(cbScrollBars);


        verticalLayout_2->addLayout(horizontalLayout_3);

        AddPanelEditorDialog->setCentralWidget(centralwidget);
        menubar = new QMenuBar(AddPanelEditorDialog);
        menubar->setObjectName(QLatin1String("menubar"));
        menubar->setGeometry(QRect(0, 0, 332, 25));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QLatin1String("menuFile"));
        menuWindow = new QMenu(menubar);
        menuWindow->setObjectName(QLatin1String("menuWindow"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QLatin1String("menuHelp"));
        AddPanelEditorDialog->setMenuBar(menubar);
        statusbar = new QStatusBar(AddPanelEditorDialog);
        statusbar->setObjectName(QLatin1String("statusbar"));
        AddPanelEditorDialog->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuWindow->menuAction());
        menubar->addAction(menuHelp->menuAction());

        retranslateUi(AddPanelEditorDialog);

        QMetaObject::connectSlotsByName(AddPanelEditorDialog);
    } // setupUi

    void retranslateUi(QMainWindow *AddPanelEditorDialog)
    {
        AddPanelEditorDialog->setWindowTitle(QApplication::translate("AddPanelEditorDialog", "Panel Editor", nullptr));
        label->setText(QApplication::translate("AddPanelEditorDialog", "x:", nullptr));
        label_2->setText(QApplication::translate("AddPanelEditorDialog", "y:", nullptr));
        btnSetName->setText(QApplication::translate("AddPanelEditorDialog", "Set Panel Name", nullptr));
        label_3->setText(QString());
        btnAddText->setText(QApplication::translate("AddPanelEditorDialog", "Add Text", nullptr));
        label_4->setText(QApplication::translate("AddPanelEditorDialog", "Select the type of icon to add to panel", nullptr));
        cbType->setItemText(0, QString());
        cbType->setItemText(1, QApplication::translate("AddPanelEditorDialog", "Right Hand Turnout", nullptr));
        cbType->setItemText(2, QApplication::translate("AddPanelEditorDialog", "Left hand Turnout", nullptr));
        cbType->setItemText(3, QApplication::translate("AddPanelEditorDialog", "Slip/3-Way Turnout/Scissors", nullptr));
        cbType->setItemText(4, QApplication::translate("AddPanelEditorDialog", "Sensor", nullptr));
        cbType->setItemText(5, QApplication::translate("AddPanelEditorDialog", "Signal Head", nullptr));
        cbType->setItemText(6, QApplication::translate("AddPanelEditorDialog", "Signal Mast", nullptr));
        cbType->setItemText(7, QApplication::translate("AddPanelEditorDialog", "Memory", nullptr));
        cbType->setItemText(8, QApplication::translate("AddPanelEditorDialog", "Reporter", nullptr));
        cbType->setItemText(9, QApplication::translate("AddPanelEditorDialog", "Light", nullptr));
        cbType->setItemText(10, QApplication::translate("AddPanelEditorDialog", "Background", nullptr));
        cbType->setItemText(11, QApplication::translate("AddPanelEditorDialog", "Multisensor", nullptr));
        cbType->setItemText(12, QApplication::translate("AddPanelEditorDialog", "RPS Reporter", nullptr));
        cbType->setItemText(13, QApplication::translate("AddPanelEditorDialog", "Fast Clock", nullptr));
        cbType->setItemText(14, QApplication::translate("AddPanelEditorDialog", "Icon", nullptr));

        chkPopup->setText(QApplication::translate("AddPanelEditorDialog", "Panel items popup menus active", nullptr));
        chkReposition->setText(QApplication::translate("AddPanelEditorDialog", "All panel items can be repositioned", nullptr));
        chkControlLayout->setText(QApplication::translate("AddPanelEditorDialog", "Panel items control layout", nullptr));
        chkShowHidden->setText(QApplication::translate("AddPanelEditorDialog", "Show all hidden items ", nullptr));
        chkShowTooltips->setText(QApplication::translate("AddPanelEditorDialog", "Show tooltips for all items", nullptr));
        chkHasMenu->setText(QApplication::translate("AddPanelEditorDialog", "Panel has menu", nullptr));
        label_5->setText(QApplication::translate("AddPanelEditorDialog", "Panel scrollbars", nullptr));
        cbScrollBars->setItemText(0, QApplication::translate("AddPanelEditorDialog", "No Scrollbars", nullptr));
        cbScrollBars->setItemText(1, QApplication::translate("AddPanelEditorDialog", "Both scrollbars", nullptr));
        cbScrollBars->setItemText(2, QApplication::translate("AddPanelEditorDialog", "Horizontal only", nullptr));
        cbScrollBars->setItemText(3, QApplication::translate("AddPanelEditorDialog", "Vertical only", nullptr));

        menuFile->setTitle(QApplication::translate("AddPanelEditorDialog", "File", nullptr));
        menuWindow->setTitle(QApplication::translate("AddPanelEditorDialog", "Window", nullptr));
        menuHelp->setTitle(QApplication::translate("AddPanelEditorDialog", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddPanelEditorDialog: public Ui_AddPanelEditorDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDPANELEDITORDIALOG_H
