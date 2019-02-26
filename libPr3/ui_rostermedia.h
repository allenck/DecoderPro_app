/********************************************************************************
** Form generated from reading UI file 'rostermedia.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROSTERMEDIA_H
#define UI_ROSTERMEDIA_H

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
    DropJLabel *lblMainImage;
    DropJLabel *lblIconImage;
    QLabel *label_27;
    QPushButton *btnRemoveIcon;
    QPushButton *btnRemoveImage;
    QLabel *label_30;
    QLineEdit *edWebReference;

    void setupUi(QWidget *RosterMediaPane)
    {
        if (RosterMediaPane->objectName().isEmpty())
            RosterMediaPane->setObjectName(QLatin1String("RosterMediaPane"));
        RosterMediaPane->resize(635, 202);
        QFont font;
        font.setPointSize(8);
        RosterMediaPane->setFont(font);
        gridLayout_3 = new QGridLayout(RosterMediaPane);
        gridLayout_3->setObjectName(QLatin1String("gridLayout_3"));
        gridLayout_3->setVerticalSpacing(2);
        gridLayout_3->setContentsMargins(-1, 4, -1, 4);
        label_29 = new QLabel(RosterMediaPane);
        label_29->setObjectName(QLatin1String("label_29"));

        gridLayout_3->addWidget(label_29, 3, 0, 1, 3);

        label_28 = new QLabel(RosterMediaPane);
        label_28->setObjectName(QLatin1String("label_28"));

        gridLayout_3->addWidget(label_28, 1, 0, 1, 2);

        lblMainImage = new DropJLabel(RosterMediaPane);
        lblMainImage->setObjectName(QLatin1String("lblMainImage"));
        lblMainImage->setAcceptDrops(true);

        gridLayout_3->addWidget(lblMainImage, 1, 2, 2, 2);

        lblIconImage = new DropJLabel(RosterMediaPane);
        lblIconImage->setObjectName(QLatin1String("lblIconImage"));
        lblIconImage->setAcceptDrops(true);

        gridLayout_3->addWidget(lblIconImage, 3, 3, 1, 1);

        label_27 = new QLabel(RosterMediaPane);
        label_27->setObjectName(QLatin1String("label_27"));

        gridLayout_3->addWidget(label_27, 0, 0, 1, 2);

        btnRemoveIcon = new QPushButton(RosterMediaPane);
        btnRemoveIcon->setObjectName(QLatin1String("btnRemoveIcon"));

        gridLayout_3->addWidget(btnRemoveIcon, 3, 4, 1, 1);

        btnRemoveImage = new QPushButton(RosterMediaPane);
        btnRemoveImage->setObjectName(QLatin1String("btnRemoveImage"));
        btnRemoveImage->setEnabled(true);

        gridLayout_3->addWidget(btnRemoveImage, 1, 4, 1, 1);

        label_30 = new QLabel(RosterMediaPane);
        label_30->setObjectName(QLatin1String("label_30"));

        gridLayout_3->addWidget(label_30, 4, 1, 1, 1);

        edWebReference = new QLineEdit(RosterMediaPane);
        edWebReference->setObjectName(QLatin1String("edWebReference"));

        gridLayout_3->addWidget(edWebReference, 4, 2, 1, 3);


        retranslateUi(RosterMediaPane);

        QMetaObject::connectSlotsByName(RosterMediaPane);
    } // setupUi

    void retranslateUi(QWidget *RosterMediaPane)
    {
        RosterMediaPane->setWindowTitle(QApplication::translate("RosterMediaPane", "Form", nullptr));
        label_29->setText(QApplication::translate("RosterMediaPane", "Image to be used as an icon for that locomotive; head to the right:", nullptr));
        label_28->setText(QApplication::translate("RosterMediaPane", "Image to be used as main image for this locomotive ", nullptr));
#ifndef QT_NO_TOOLTIP
        lblMainImage->setToolTip(QApplication::translate("RosterMediaPane", "<html><head/><body><p>Image to be used for this locomotive,  drop any image file in the frame</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        lblMainImage->setText(QApplication::translate("RosterMediaPane", "Image", nullptr));
#ifndef QT_NO_TOOLTIP
        lblIconImage->setToolTip(QApplication::translate("RosterMediaPane", "<html><head/><body><p>Image to be used as an icon for this locomotive, drop any image file in the frame, have locomotive head to the right (for later rotations)</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        lblIconImage->setText(QApplication::translate("RosterMediaPane", "image icon", nullptr));
        label_27->setText(QApplication::translate("RosterMediaPane", "Use this tab to add various media to your roster", nullptr));
        btnRemoveIcon->setText(QApplication::translate("RosterMediaPane", "Remove", nullptr));
        btnRemoveImage->setText(QApplication::translate("RosterMediaPane", "Remove", nullptr));
        label_30->setText(QApplication::translate("RosterMediaPane", "Web reference:", nullptr));
#ifndef QT_NO_TOOLTIP
        edWebReference->setToolTip(QApplication::translate("RosterMediaPane", "<html><head/><body><p>URL to any web page related to that locomotive</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
    } // retranslateUi

};

namespace Ui {
    class RosterMediaPane: public Ui_RosterMediaPane {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROSTERMEDIA_H
