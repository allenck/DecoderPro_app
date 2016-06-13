/********************************************************************************
** Form generated from reading UI file 'setxydlg.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETXYDLG_H
#define UI_SETXYDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QGridLayout *gridLayout;
    QLabel *nameText;
    QLabel *textX;
    QSpinBox *SpinX;
    QLabel *textY;
    QSpinBox *spinY;
    QPushButton *cancelButton;
    QPushButton *okButton;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(182, 130);
        gridLayout = new QGridLayout(Dialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        nameText = new QLabel(Dialog);
        nameText->setObjectName(QStringLiteral("nameText"));

        gridLayout->addWidget(nameText, 0, 0, 1, 2);

        textX = new QLabel(Dialog);
        textX->setObjectName(QStringLiteral("textX"));

        gridLayout->addWidget(textX, 1, 0, 1, 1);

        SpinX = new QSpinBox(Dialog);
        SpinX->setObjectName(QStringLiteral("SpinX"));

        gridLayout->addWidget(SpinX, 1, 1, 1, 1);

        textY = new QLabel(Dialog);
        textY->setObjectName(QStringLiteral("textY"));

        gridLayout->addWidget(textY, 2, 0, 1, 1);

        spinY = new QSpinBox(Dialog);
        spinY->setObjectName(QStringLiteral("spinY"));

        gridLayout->addWidget(spinY, 2, 1, 1, 1);

        cancelButton = new QPushButton(Dialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        gridLayout->addWidget(cancelButton, 3, 0, 1, 1);

        okButton = new QPushButton(Dialog);
        okButton->setObjectName(QStringLiteral("okButton"));

        gridLayout->addWidget(okButton, 3, 1, 1, 1);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0));
        nameText->setText(QApplication::translate("Dialog", "Name: XXXXXX", 0));
        textX->setText(QApplication::translate("Dialog", "x= xxxx", 0));
        textY->setText(QApplication::translate("Dialog", "y = xxxx", 0));
        cancelButton->setText(QApplication::translate("Dialog", "Cancel", 0));
        okButton->setText(QApplication::translate("Dialog", "Set", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETXYDLG_H
