/********************************************************************************
** Form generated from reading UI file 'setxydlg.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETXYDLG_H
#define UI_SETXYDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
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
            Dialog->setObjectName(QLatin1String("Dialog"));
        Dialog->resize(182, 130);
        gridLayout = new QGridLayout(Dialog);
        gridLayout->setObjectName(QLatin1String("gridLayout"));
        nameText = new QLabel(Dialog);
        nameText->setObjectName(QLatin1String("nameText"));

        gridLayout->addWidget(nameText, 0, 0, 1, 2);

        textX = new QLabel(Dialog);
        textX->setObjectName(QLatin1String("textX"));

        gridLayout->addWidget(textX, 1, 0, 1, 1);

        SpinX = new QSpinBox(Dialog);
        SpinX->setObjectName(QLatin1String("SpinX"));

        gridLayout->addWidget(SpinX, 1, 1, 1, 1);

        textY = new QLabel(Dialog);
        textY->setObjectName(QLatin1String("textY"));

        gridLayout->addWidget(textY, 2, 0, 1, 1);

        spinY = new QSpinBox(Dialog);
        spinY->setObjectName(QLatin1String("spinY"));

        gridLayout->addWidget(spinY, 2, 1, 1, 1);

        cancelButton = new QPushButton(Dialog);
        cancelButton->setObjectName(QLatin1String("cancelButton"));

        gridLayout->addWidget(cancelButton, 3, 0, 1, 1);

        okButton = new QPushButton(Dialog);
        okButton->setObjectName(QLatin1String("okButton"));

        gridLayout->addWidget(okButton, 3, 1, 1, 1);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", nullptr));
        nameText->setText(QApplication::translate("Dialog", "Name: XXXXXX", nullptr));
        textX->setText(QApplication::translate("Dialog", "x= xxxx", nullptr));
        textY->setText(QApplication::translate("Dialog", "y = xxxx", nullptr));
        cancelButton->setText(QApplication::translate("Dialog", "Cancel", nullptr));
        okButton->setText(QApplication::translate("Dialog", "Set", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETXYDLG_H
