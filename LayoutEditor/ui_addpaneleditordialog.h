/********************************************************************************
** Form generated from reading UI file 'addpaneleditordialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDPANELEDITORDIALOG_H
#define UI_ADDPANELEDITORDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
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
            AddPanelEditorDialog->setObjectName(QStringLiteral("AddPanelEditorDialog"));
        AddPanelEditorDialog->resize(332, 427);
        centralwidget = new QWidget(AddPanelEditorDialog);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        edX = new QLineEdit(centralwidget);
        edX->setObjectName(QStringLiteral("edX"));
        edX->setMaximumSize(QSize(60, 16777215));
        edX->setInputMethodHints(Qt::ImhNone);

        horizontalLayout->addWidget(edX);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        edY = new QLineEdit(centralwidget);
        edY->setObjectName(QStringLiteral("edY"));
        edY->setMaximumSize(QSize(60, 16777215));
        edY->setInputMethodHints(Qt::ImhNone);

        horizontalLayout->addWidget(edY);


        verticalLayout_2->addLayout(horizontalLayout);

        btnSetName = new QPushButton(centralwidget);
        btnSetName->setObjectName(QStringLiteral("btnSetName"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnSetName->sizePolicy().hasHeightForWidth());
        btnSetName->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(btnSetName);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_2->addWidget(label_3);

        btnAddText = new QPushButton(centralwidget);
        btnAddText->setObjectName(QStringLiteral("btnAddText"));
        btnAddText->setEnabled(false);

        horizontalLayout_2->addWidget(btnAddText);

        edText = new QLineEdit(centralwidget);
        edText->setObjectName(QStringLiteral("edText"));

        horizontalLayout_2->addWidget(edText);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout->addWidget(label_4);

        cbType = new QComboBox(centralwidget);
        cbType->setObjectName(QStringLiteral("cbType"));

        verticalLayout->addWidget(cbType);


        verticalLayout_2->addLayout(verticalLayout);

        chkPopup = new QCheckBox(centralwidget);
        chkPopup->setObjectName(QStringLiteral("chkPopup"));
        chkPopup->setChecked(true);

        verticalLayout_2->addWidget(chkPopup);

        chkReposition = new QCheckBox(centralwidget);
        chkReposition->setObjectName(QStringLiteral("chkReposition"));
        chkReposition->setChecked(true);

        verticalLayout_2->addWidget(chkReposition);

        chkControlLayout = new QCheckBox(centralwidget);
        chkControlLayout->setObjectName(QStringLiteral("chkControlLayout"));
        chkControlLayout->setChecked(true);

        verticalLayout_2->addWidget(chkControlLayout);

        chkShowHidden = new QCheckBox(centralwidget);
        chkShowHidden->setObjectName(QStringLiteral("chkShowHidden"));
        chkShowHidden->setEnabled(false);

        verticalLayout_2->addWidget(chkShowHidden);

        chkShowTooltips = new QCheckBox(centralwidget);
        chkShowTooltips->setObjectName(QStringLiteral("chkShowTooltips"));
        chkShowTooltips->setChecked(true);

        verticalLayout_2->addWidget(chkShowTooltips);

        chkHasMenu = new QCheckBox(centralwidget);
        chkHasMenu->setObjectName(QStringLiteral("chkHasMenu"));
        chkHasMenu->setChecked(true);

        verticalLayout_2->addWidget(chkHasMenu);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_3->addWidget(label_5);

        cbScrollBars = new QComboBox(centralwidget);
        cbScrollBars->setObjectName(QStringLiteral("cbScrollBars"));

        horizontalLayout_3->addWidget(cbScrollBars);


        verticalLayout_2->addLayout(horizontalLayout_3);

        AddPanelEditorDialog->setCentralWidget(centralwidget);
        menubar = new QMenuBar(AddPanelEditorDialog);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 332, 25));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuWindow = new QMenu(menubar);
        menuWindow->setObjectName(QStringLiteral("menuWindow"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        AddPanelEditorDialog->setMenuBar(menubar);
        statusbar = new QStatusBar(AddPanelEditorDialog);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        AddPanelEditorDialog->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuWindow->menuAction());
        menubar->addAction(menuHelp->menuAction());

        retranslateUi(AddPanelEditorDialog);

        QMetaObject::connectSlotsByName(AddPanelEditorDialog);
    } // setupUi

    void retranslateUi(QMainWindow *AddPanelEditorDialog)
    {
        AddPanelEditorDialog->setWindowTitle(QApplication::translate("AddPanelEditorDialog", "Panel Editor", 0));
        label->setText(QApplication::translate("AddPanelEditorDialog", "x:", 0));
        label_2->setText(QApplication::translate("AddPanelEditorDialog", "y:", 0));
        btnSetName->setText(QApplication::translate("AddPanelEditorDialog", "Set Panel Name", 0));
        label_3->setText(QString());
        btnAddText->setText(QApplication::translate("AddPanelEditorDialog", "Add Text", 0));
        label_4->setText(QApplication::translate("AddPanelEditorDialog", "Select the type of icon to add to panel", 0));
        cbType->clear();
        cbType->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("AddPanelEditorDialog", "Right Hand Turnout", 0)
         << QApplication::translate("AddPanelEditorDialog", "Left hand Turnout", 0)
         << QApplication::translate("AddPanelEditorDialog", "Slip/3-Way Turnout/Scissors", 0)
         << QApplication::translate("AddPanelEditorDialog", "Sensor", 0)
         << QApplication::translate("AddPanelEditorDialog", "Signal Head", 0)
         << QApplication::translate("AddPanelEditorDialog", "Signal Mast", 0)
         << QApplication::translate("AddPanelEditorDialog", "Memory", 0)
         << QApplication::translate("AddPanelEditorDialog", "Reporter", 0)
         << QApplication::translate("AddPanelEditorDialog", "Light", 0)
         << QApplication::translate("AddPanelEditorDialog", "Background", 0)
         << QApplication::translate("AddPanelEditorDialog", "Multisensor", 0)
         << QApplication::translate("AddPanelEditorDialog", "RPS Reporter", 0)
         << QApplication::translate("AddPanelEditorDialog", "Fast Clock", 0)
         << QApplication::translate("AddPanelEditorDialog", "Icon", 0)
        );
        chkPopup->setText(QApplication::translate("AddPanelEditorDialog", "Panel items popup menus active", 0));
        chkReposition->setText(QApplication::translate("AddPanelEditorDialog", "All panel items can be repositioned", 0));
        chkControlLayout->setText(QApplication::translate("AddPanelEditorDialog", "Panel items control layout", 0));
        chkShowHidden->setText(QApplication::translate("AddPanelEditorDialog", "Show all hidden items ", 0));
        chkShowTooltips->setText(QApplication::translate("AddPanelEditorDialog", "Show tooltips for all items", 0));
        chkHasMenu->setText(QApplication::translate("AddPanelEditorDialog", "Panel has menu", 0));
        label_5->setText(QApplication::translate("AddPanelEditorDialog", "Panel scrollbars", 0));
        cbScrollBars->clear();
        cbScrollBars->insertItems(0, QStringList()
         << QApplication::translate("AddPanelEditorDialog", "No Scrollbars", 0)
         << QApplication::translate("AddPanelEditorDialog", "Both scrollbars", 0)
         << QApplication::translate("AddPanelEditorDialog", "Horizontal only", 0)
         << QApplication::translate("AddPanelEditorDialog", "Vertical only", 0)
        );
        menuFile->setTitle(QApplication::translate("AddPanelEditorDialog", "File", 0));
        menuWindow->setTitle(QApplication::translate("AddPanelEditorDialog", "Window", 0));
        menuHelp->setTitle(QApplication::translate("AddPanelEditorDialog", "Help", 0));
    } // retranslateUi

};

namespace Ui {
    class AddPanelEditorDialog: public Ui_AddPanelEditorDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDPANELEDITORDIALOG_H
