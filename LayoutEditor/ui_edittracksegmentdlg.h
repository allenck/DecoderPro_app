/********************************************************************************
** Form generated from reading UI file 'edittracksegmentdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITTRACKSEGMENTDLG_H
#define UI_EDITTRACKSEGMENTDLG_H

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

class Ui_EditTrackSegmentDlg
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QComboBox *cbStyle;
    QComboBox *cbTrackType;
    QCheckBox *chkHide;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *edBlockName;
    QHBoxLayout *horizontalLayout;
    QPushButton *pbEditBlock;
    QPushButton *pbDone;
    QPushButton *pbCancel;
    QMenuBar *menubar;
    QMenu *menuWindow;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *EditTrackSegmentDlg)
    {
        if (EditTrackSegmentDlg->objectName().isEmpty())
            EditTrackSegmentDlg->setObjectName(QStringLiteral("EditTrackSegmentDlg"));
        EditTrackSegmentDlg->resize(318, 253);
        centralwidget = new QWidget(EditTrackSegmentDlg);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_3->addWidget(label);

        cbStyle = new QComboBox(centralwidget);
        cbStyle->setObjectName(QStringLiteral("cbStyle"));

        horizontalLayout_3->addWidget(cbStyle);


        verticalLayout->addLayout(horizontalLayout_3);

        cbTrackType = new QComboBox(centralwidget);
        cbTrackType->setObjectName(QStringLiteral("cbTrackType"));

        verticalLayout->addWidget(cbTrackType);

        chkHide = new QCheckBox(centralwidget);
        chkHide->setObjectName(QStringLiteral("chkHide"));

        verticalLayout->addWidget(chkHide);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        edBlockName = new QLineEdit(centralwidget);
        edBlockName->setObjectName(QStringLiteral("edBlockName"));

        horizontalLayout_2->addWidget(edBlockName);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pbEditBlock = new QPushButton(centralwidget);
        pbEditBlock->setObjectName(QStringLiteral("pbEditBlock"));

        horizontalLayout->addWidget(pbEditBlock);

        pbDone = new QPushButton(centralwidget);
        pbDone->setObjectName(QStringLiteral("pbDone"));

        horizontalLayout->addWidget(pbDone);

        pbCancel = new QPushButton(centralwidget);
        pbCancel->setObjectName(QStringLiteral("pbCancel"));

        horizontalLayout->addWidget(pbCancel);


        verticalLayout->addLayout(horizontalLayout);

        EditTrackSegmentDlg->setCentralWidget(centralwidget);
        menubar = new QMenuBar(EditTrackSegmentDlg);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 318, 25));
        menuWindow = new QMenu(menubar);
        menuWindow->setObjectName(QStringLiteral("menuWindow"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        EditTrackSegmentDlg->setMenuBar(menubar);
        statusbar = new QStatusBar(EditTrackSegmentDlg);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        EditTrackSegmentDlg->setStatusBar(statusbar);

        menubar->addAction(menuWindow->menuAction());
        menubar->addAction(menuHelp->menuAction());

        retranslateUi(EditTrackSegmentDlg);

        QMetaObject::connectSlotsByName(EditTrackSegmentDlg);
    } // setupUi

    void retranslateUi(QMainWindow *EditTrackSegmentDlg)
    {
        EditTrackSegmentDlg->setWindowTitle(QApplication::translate("EditTrackSegmentDlg", "MainWindow", 0));
        label->setText(QApplication::translate("EditTrackSegmentDlg", "Style:", 0));
        cbStyle->clear();
        cbStyle->insertItems(0, QStringList()
         << QApplication::translate("EditTrackSegmentDlg", "Solid", 0)
         << QApplication::translate("EditTrackSegmentDlg", "Dashed", 0)
        );
        cbTrackType->clear();
        cbTrackType->insertItems(0, QStringList()
         << QApplication::translate("EditTrackSegmentDlg", "Side Track", 0)
         << QApplication::translate("EditTrackSegmentDlg", "Mainline Track", 0)
        );
        chkHide->setText(QApplication::translate("EditTrackSegmentDlg", "Hide Track", 0));
        label_2->setText(QApplication::translate("EditTrackSegmentDlg", "Block Name: ", 0));
        pbEditBlock->setText(QApplication::translate("EditTrackSegmentDlg", "Create/Edit Block", 0));
        pbDone->setText(QApplication::translate("EditTrackSegmentDlg", "Done", 0));
        pbCancel->setText(QApplication::translate("EditTrackSegmentDlg", "Cancel", 0));
        menuWindow->setTitle(QApplication::translate("EditTrackSegmentDlg", "Window", 0));
        menuHelp->setTitle(QApplication::translate("EditTrackSegmentDlg", "Help", 0));
    } // retranslateUi

};

namespace Ui {
    class EditTrackSegmentDlg: public Ui_EditTrackSegmentDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITTRACKSEGMENTDLG_H
