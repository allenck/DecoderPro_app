/********************************************************************************
** Form generated from reading UI file 'editturnout.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITTURNOUT_H
#define UI_EDITTURNOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>

QT_BEGIN_NAMESPACE

class Ui_EditTurnout
{
public:
    QMenuBar *menuBar;

    void setupUi(QMainWindow *EditTurnout)
    {
        if (EditTurnout->objectName().isEmpty())
            EditTurnout->setObjectName(QStringLiteral("EditTurnout"));
        EditTurnout->resize(487, 355);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(EditTurnout->sizePolicy().hasHeightForWidth());
        EditTurnout->setSizePolicy(sizePolicy);
        EditTurnout->setMinimumSize(QSize(400, 200));
        menuBar = new QMenuBar(EditTurnout);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 487, 25));
        EditTurnout->setMenuBar(menuBar);

        retranslateUi(EditTurnout);

        QMetaObject::connectSlotsByName(EditTurnout);
    } // setupUi

    void retranslateUi(QMainWindow *EditTurnout)
    {
        EditTurnout->setWindowTitle(QApplication::translate("EditTurnout", "Edit Turnout", 0));
    } // retranslateUi

};

namespace Ui {
    class EditTurnout: public Ui_EditTurnout {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITTURNOUT_H
