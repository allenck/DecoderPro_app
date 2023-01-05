/********************************************************************************
** Form generated from reading UI file 'addpaneleditordialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
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
            AddPanelEditorDialog->setObjectName(QString::fromUtf8("AddPanelEditorDialog"));
        AddPanelEditorDialog->resize(332, 427);
        centralwidget = new QWidget(AddPanelEditorDialog);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        edX = new QLineEdit(centralwidget);
        edX->setObjectName(QString::fromUtf8("edX"));
        edX->setMaximumSize(QSize(60, 16777215));
        edX->setInputMethodHints(Qt::ImhNone);

        horizontalLayout->addWidget(edX);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        edY = new QLineEdit(centralwidget);
        edY->setObjectName(QString::fromUtf8("edY"));
        edY->setMaximumSize(QSize(60, 16777215));
        edY->setInputMethodHints(Qt::ImhNone);

        horizontalLayout->addWidget(edY);


        verticalLayout_2->addLayout(horizontalLayout);

        btnSetName = new QPushButton(centralwidget);
        btnSetName->setObjectName(QString::fromUtf8("btnSetName"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnSetName->sizePolicy().hasHeightForWidth());
        btnSetName->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(btnSetName);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        btnAddText = new QPushButton(centralwidget);
        btnAddText->setObjectName(QString::fromUtf8("btnAddText"));
        btnAddText->setEnabled(false);

        horizontalLayout_2->addWidget(btnAddText);

        edText = new QLineEdit(centralwidget);
        edText->setObjectName(QString::fromUtf8("edText"));

        horizontalLayout_2->addWidget(edText);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

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
        cbType->setObjectName(QString::fromUtf8("cbType"));

        verticalLayout->addWidget(cbType);


        verticalLayout_2->addLayout(verticalLayout);

        chkPopup = new QCheckBox(centralwidget);
        chkPopup->setObjectName(QString::fromUtf8("chkPopup"));
        chkPopup->setChecked(true);

        verticalLayout_2->addWidget(chkPopup);

        chkReposition = new QCheckBox(centralwidget);
        chkReposition->setObjectName(QString::fromUtf8("chkReposition"));
        chkReposition->setChecked(true);

        verticalLayout_2->addWidget(chkReposition);

        chkControlLayout = new QCheckBox(centralwidget);
        chkControlLayout->setObjectName(QString::fromUtf8("chkControlLayout"));
        chkControlLayout->setChecked(true);

        verticalLayout_2->addWidget(chkControlLayout);

        chkShowHidden = new QCheckBox(centralwidget);
        chkShowHidden->setObjectName(QString::fromUtf8("chkShowHidden"));
        chkShowHidden->setEnabled(false);

        verticalLayout_2->addWidget(chkShowHidden);

        chkShowTooltips = new QCheckBox(centralwidget);
        chkShowTooltips->setObjectName(QString::fromUtf8("chkShowTooltips"));
        chkShowTooltips->setChecked(true);

        verticalLayout_2->addWidget(chkShowTooltips);

        chkHasMenu = new QCheckBox(centralwidget);
        chkHasMenu->setObjectName(QString::fromUtf8("chkHasMenu"));
        chkHasMenu->setChecked(true);

        verticalLayout_2->addWidget(chkHasMenu);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_3->addWidget(label_5);

        cbScrollBars = new QComboBox(centralwidget);
        cbScrollBars->addItem(QString());
        cbScrollBars->addItem(QString());
        cbScrollBars->addItem(QString());
        cbScrollBars->addItem(QString());
        cbScrollBars->setObjectName(QString::fromUtf8("cbScrollBars"));

        horizontalLayout_3->addWidget(cbScrollBars);


        verticalLayout_2->addLayout(horizontalLayout_3);

        AddPanelEditorDialog->setCentralWidget(centralwidget);
        menubar = new QMenuBar(AddPanelEditorDialog);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 332, 25));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuWindow = new QMenu(menubar);
        menuWindow->setObjectName(QString::fromUtf8("menuWindow"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        AddPanelEditorDialog->setMenuBar(menubar);
        statusbar = new QStatusBar(AddPanelEditorDialog);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        AddPanelEditorDialog->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuWindow->menuAction());
        menubar->addAction(menuHelp->menuAction());

        retranslateUi(AddPanelEditorDialog);

        QMetaObject::connectSlotsByName(AddPanelEditorDialog);
    } // setupUi

    void retranslateUi(QMainWindow *AddPanelEditorDialog)
    {
        AddPanelEditorDialog->setWindowTitle(QCoreApplication::translate("AddPanelEditorDialog", "Panel Editor", nullptr));
        label->setText(QCoreApplication::translate("AddPanelEditorDialog", "x:", nullptr));
        label_2->setText(QCoreApplication::translate("AddPanelEditorDialog", "y:", nullptr));
        btnSetName->setText(QCoreApplication::translate("AddPanelEditorDialog", "Set Panel Name", nullptr));
        label_3->setText(QString());
        btnAddText->setText(QCoreApplication::translate("AddPanelEditorDialog", "Add Text", nullptr));
        label_4->setText(QCoreApplication::translate("AddPanelEditorDialog", "Select the type of icon to add to panel", nullptr));
        cbType->setItemText(0, QString());
        cbType->setItemText(1, QCoreApplication::translate("AddPanelEditorDialog", "Right Hand Turnout", nullptr));
        cbType->setItemText(2, QCoreApplication::translate("AddPanelEditorDialog", "Left hand Turnout", nullptr));
        cbType->setItemText(3, QCoreApplication::translate("AddPanelEditorDialog", "Slip/3-Way Turnout/Scissors", nullptr));
        cbType->setItemText(4, QCoreApplication::translate("AddPanelEditorDialog", "Sensor", nullptr));
        cbType->setItemText(5, QCoreApplication::translate("AddPanelEditorDialog", "Signal Head", nullptr));
        cbType->setItemText(6, QCoreApplication::translate("AddPanelEditorDialog", "Signal Mast", nullptr));
        cbType->setItemText(7, QCoreApplication::translate("AddPanelEditorDialog", "Memory", nullptr));
        cbType->setItemText(8, QCoreApplication::translate("AddPanelEditorDialog", "Reporter", nullptr));
        cbType->setItemText(9, QCoreApplication::translate("AddPanelEditorDialog", "Light", nullptr));
        cbType->setItemText(10, QCoreApplication::translate("AddPanelEditorDialog", "Background", nullptr));
        cbType->setItemText(11, QCoreApplication::translate("AddPanelEditorDialog", "Multisensor", nullptr));
        cbType->setItemText(12, QCoreApplication::translate("AddPanelEditorDialog", "RPS Reporter", nullptr));
        cbType->setItemText(13, QCoreApplication::translate("AddPanelEditorDialog", "Fast Clock", nullptr));
        cbType->setItemText(14, QCoreApplication::translate("AddPanelEditorDialog", "Icon", nullptr));

        chkPopup->setText(QCoreApplication::translate("AddPanelEditorDialog", "Panel items popup menus active", nullptr));
        chkReposition->setText(QCoreApplication::translate("AddPanelEditorDialog", "All panel items can be repositioned", nullptr));
        chkControlLayout->setText(QCoreApplication::translate("AddPanelEditorDialog", "Panel items control layout", nullptr));
        chkShowHidden->setText(QCoreApplication::translate("AddPanelEditorDialog", "Show all hidden items ", nullptr));
        chkShowTooltips->setText(QCoreApplication::translate("AddPanelEditorDialog", "Show tooltips for all items", nullptr));
        chkHasMenu->setText(QCoreApplication::translate("AddPanelEditorDialog", "Panel has menu", nullptr));
        label_5->setText(QCoreApplication::translate("AddPanelEditorDialog", "Panel scrollbars", nullptr));
        cbScrollBars->setItemText(0, QCoreApplication::translate("AddPanelEditorDialog", "No Scrollbars", nullptr));
        cbScrollBars->setItemText(1, QCoreApplication::translate("AddPanelEditorDialog", "Both scrollbars", nullptr));
        cbScrollBars->setItemText(2, QCoreApplication::translate("AddPanelEditorDialog", "Horizontal only", nullptr));
        cbScrollBars->setItemText(3, QCoreApplication::translate("AddPanelEditorDialog", "Vertical only", nullptr));

        menuFile->setTitle(QCoreApplication::translate("AddPanelEditorDialog", "File", nullptr));
        menuWindow->setTitle(QCoreApplication::translate("AddPanelEditorDialog", "Window", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("AddPanelEditorDialog", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddPanelEditorDialog: public Ui_AddPanelEditorDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDPANELEDITORDIALOG_H
