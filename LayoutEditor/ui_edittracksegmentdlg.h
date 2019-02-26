/********************************************************************************
** Form generated from reading UI file 'edittracksegmentdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITTRACKSEGMENTDLG_H
#define UI_EDITTRACKSEGMENTDLG_H

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
            EditTrackSegmentDlg->setObjectName(QLatin1String("EditTrackSegmentDlg"));
        EditTrackSegmentDlg->resize(318, 253);
        centralwidget = new QWidget(EditTrackSegmentDlg);
        centralwidget->setObjectName(QLatin1String("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QLatin1String("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QLatin1String("horizontalLayout_3"));
        label = new QLabel(centralwidget);
        label->setObjectName(QLatin1String("label"));

        horizontalLayout_3->addWidget(label);

        cbStyle = new QComboBox(centralwidget);
        cbStyle->addItem(QString());
        cbStyle->addItem(QString());
        cbStyle->setObjectName(QLatin1String("cbStyle"));

        horizontalLayout_3->addWidget(cbStyle);


        verticalLayout->addLayout(horizontalLayout_3);

        cbTrackType = new QComboBox(centralwidget);
        cbTrackType->addItem(QString());
        cbTrackType->addItem(QString());
        cbTrackType->setObjectName(QLatin1String("cbTrackType"));

        verticalLayout->addWidget(cbTrackType);

        chkHide = new QCheckBox(centralwidget);
        chkHide->setObjectName(QLatin1String("chkHide"));

        verticalLayout->addWidget(chkHide);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QLatin1String("horizontalLayout_2"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QLatin1String("label_2"));

        horizontalLayout_2->addWidget(label_2);

        edBlockName = new QLineEdit(centralwidget);
        edBlockName->setObjectName(QLatin1String("edBlockName"));

        horizontalLayout_2->addWidget(edBlockName);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QLatin1String("horizontalLayout"));
        pbEditBlock = new QPushButton(centralwidget);
        pbEditBlock->setObjectName(QLatin1String("pbEditBlock"));

        horizontalLayout->addWidget(pbEditBlock);

        pbDone = new QPushButton(centralwidget);
        pbDone->setObjectName(QLatin1String("pbDone"));

        horizontalLayout->addWidget(pbDone);

        pbCancel = new QPushButton(centralwidget);
        pbCancel->setObjectName(QLatin1String("pbCancel"));

        horizontalLayout->addWidget(pbCancel);


        verticalLayout->addLayout(horizontalLayout);

        EditTrackSegmentDlg->setCentralWidget(centralwidget);
        menubar = new QMenuBar(EditTrackSegmentDlg);
        menubar->setObjectName(QLatin1String("menubar"));
        menubar->setGeometry(QRect(0, 0, 318, 25));
        menuWindow = new QMenu(menubar);
        menuWindow->setObjectName(QLatin1String("menuWindow"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QLatin1String("menuHelp"));
        EditTrackSegmentDlg->setMenuBar(menubar);
        statusbar = new QStatusBar(EditTrackSegmentDlg);
        statusbar->setObjectName(QLatin1String("statusbar"));
        EditTrackSegmentDlg->setStatusBar(statusbar);

        menubar->addAction(menuWindow->menuAction());
        menubar->addAction(menuHelp->menuAction());

        retranslateUi(EditTrackSegmentDlg);

        QMetaObject::connectSlotsByName(EditTrackSegmentDlg);
    } // setupUi

    void retranslateUi(QMainWindow *EditTrackSegmentDlg)
    {
        EditTrackSegmentDlg->setWindowTitle(QApplication::translate("EditTrackSegmentDlg", "MainWindow", nullptr));
        label->setText(QApplication::translate("EditTrackSegmentDlg", "Style:", nullptr));
        cbStyle->setItemText(0, QApplication::translate("EditTrackSegmentDlg", "Solid", nullptr));
        cbStyle->setItemText(1, QApplication::translate("EditTrackSegmentDlg", "Dashed", nullptr));

        cbTrackType->setItemText(0, QApplication::translate("EditTrackSegmentDlg", "Side Track", nullptr));
        cbTrackType->setItemText(1, QApplication::translate("EditTrackSegmentDlg", "Mainline Track", nullptr));

        chkHide->setText(QApplication::translate("EditTrackSegmentDlg", "Hide Track", nullptr));
        label_2->setText(QApplication::translate("EditTrackSegmentDlg", "Block Name: ", nullptr));
        pbEditBlock->setText(QApplication::translate("EditTrackSegmentDlg", "Create/Edit Block", nullptr));
        pbDone->setText(QApplication::translate("EditTrackSegmentDlg", "Done", nullptr));
        pbCancel->setText(QApplication::translate("EditTrackSegmentDlg", "Cancel", nullptr));
        menuWindow->setTitle(QApplication::translate("EditTrackSegmentDlg", "Window", nullptr));
        menuHelp->setTitle(QApplication::translate("EditTrackSegmentDlg", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditTrackSegmentDlg: public Ui_EditTrackSegmentDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITTRACKSEGMENTDLG_H
