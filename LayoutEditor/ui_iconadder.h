/********************************************************************************
** Form generated from reading UI file 'iconadder.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ICONADDER_H
#define UI_ICONADDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_IconAdder
{
public:

    void setupUi(QDialog *IconAdder)
    {
        if (IconAdder->objectName().isEmpty())
            IconAdder->setObjectName(QStringLiteral("IconAdder"));
        IconAdder->resize(400, 300);

        retranslateUi(IconAdder);

        QMetaObject::connectSlotsByName(IconAdder);
    } // setupUi

    void retranslateUi(QDialog *IconAdder)
    {
        IconAdder->setWindowTitle(QApplication::translate("IconAdder", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class IconAdder: public Ui_IconAdder {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ICONADDER_H
