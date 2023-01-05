/********************************************************************************
** Form generated from reading UI file 'rostermediapane.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROSTERMEDIAPANE_H
#define UI_ROSTERMEDIAPANE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "dropjlabel.h"

QT_BEGIN_NAMESPACE

class Ui_RosterMediaPane
{
public:
    QGridLayout *gridLayout_3;
    QLabel *label_29;
    QLabel *label_28;
    QLabel *lblIconImage;
    QLabel *label_27;
    QPushButton *btnRemoveIcon;
    QPushButton *btnRemoveImage;
    QLabel *label_30;
    QLineEdit *edWebReference;
    DropJLabel *lblMainImage;

    void setupUi(QWidget *RosterMediaPane)
    {
        if (RosterMediaPane->objectName().isEmpty())
            RosterMediaPane->setObjectName(QString::fromUtf8("RosterMediaPane"));
        RosterMediaPane->resize(635, 202);
        QFont font;
        font.setPointSize(8);
        RosterMediaPane->setFont(font);
        gridLayout_3 = new QGridLayout(RosterMediaPane);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setVerticalSpacing(2);
        gridLayout_3->setContentsMargins(-1, 4, -1, 4);
        label_29 = new QLabel(RosterMediaPane);
        label_29->setObjectName(QString::fromUtf8("label_29"));

        gridLayout_3->addWidget(label_29, 3, 0, 1, 3);

        label_28 = new QLabel(RosterMediaPane);
        label_28->setObjectName(QString::fromUtf8("label_28"));

        gridLayout_3->addWidget(label_28, 1, 0, 1, 2);

        lblIconImage = new QLabel(RosterMediaPane);
        lblIconImage->setObjectName(QString::fromUtf8("lblIconImage"));
        lblIconImage->setAcceptDrops(true);

        gridLayout_3->addWidget(lblIconImage, 3, 3, 1, 1);

        label_27 = new QLabel(RosterMediaPane);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        gridLayout_3->addWidget(label_27, 0, 0, 1, 2);

        btnRemoveIcon = new QPushButton(RosterMediaPane);
        btnRemoveIcon->setObjectName(QString::fromUtf8("btnRemoveIcon"));

        gridLayout_3->addWidget(btnRemoveIcon, 3, 4, 1, 1);

        btnRemoveImage = new QPushButton(RosterMediaPane);
        btnRemoveImage->setObjectName(QString::fromUtf8("btnRemoveImage"));
        btnRemoveImage->setEnabled(true);

        gridLayout_3->addWidget(btnRemoveImage, 1, 4, 1, 1);

        label_30 = new QLabel(RosterMediaPane);
        label_30->setObjectName(QString::fromUtf8("label_30"));

        gridLayout_3->addWidget(label_30, 4, 1, 1, 1);

        edWebReference = new QLineEdit(RosterMediaPane);
        edWebReference->setObjectName(QString::fromUtf8("edWebReference"));

        gridLayout_3->addWidget(edWebReference, 4, 2, 1, 3);

        lblMainImage = new DropJLabel(RosterMediaPane);
        lblMainImage->setObjectName(QString::fromUtf8("lblMainImage"));
        lblMainImage->setAcceptDrops(true);

        gridLayout_3->addWidget(lblMainImage, 2, 2, 1, 2);


        retranslateUi(RosterMediaPane);

        QMetaObject::connectSlotsByName(RosterMediaPane);
    } // setupUi

    void retranslateUi(QWidget *RosterMediaPane)
    {
        RosterMediaPane->setWindowTitle(QCoreApplication::translate("RosterMediaPane", "Form", nullptr));
        label_29->setText(QCoreApplication::translate("RosterMediaPane", "Image to be used as an icon for that locomotive; head to the right:", nullptr));
        label_28->setText(QCoreApplication::translate("RosterMediaPane", "Image to be used as main image for this locomotive ", nullptr));
#if QT_CONFIG(tooltip)
        lblIconImage->setToolTip(QCoreApplication::translate("RosterMediaPane", "<html><head/><body><p>Image to be used as an icon for this locomotive, drop any image file in the frame, have locomotive head to the right (for later rotations)</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        lblIconImage->setText(QCoreApplication::translate("RosterMediaPane", "image icon", nullptr));
        label_27->setText(QCoreApplication::translate("RosterMediaPane", "Use this tab to add various media to your roster", nullptr));
        btnRemoveIcon->setText(QCoreApplication::translate("RosterMediaPane", "Remove", nullptr));
        btnRemoveImage->setText(QCoreApplication::translate("RosterMediaPane", "Remove", nullptr));
        label_30->setText(QCoreApplication::translate("RosterMediaPane", "Web reference:", nullptr));
#if QT_CONFIG(tooltip)
        edWebReference->setToolTip(QCoreApplication::translate("RosterMediaPane", "<html><head/><body><p>URL to any web page related to that locomotive</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        lblMainImage->setToolTip(QCoreApplication::translate("RosterMediaPane", "<html><head/><body><p>Image to be used for this locomotive,  drop any image file in the frame</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        lblMainImage->setText(QCoreApplication::translate("RosterMediaPane", "Image", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RosterMediaPane: public Ui_RosterMediaPane {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROSTERMEDIAPANE_H
