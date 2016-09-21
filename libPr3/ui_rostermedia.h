/********************************************************************************
** Form generated from reading UI file 'rostermedia.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROSTERMEDIA_H
#define UI_ROSTERMEDIA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RosterMediaPane
{
public:
    QGridLayout *gridLayout_3;
    QLabel *label_26;
    QLineEdit *edWebReference;
    QLabel *label_27;
    QLabel *label_30;
    QLabel *lblMainImage;
    QLabel *label_29;
    QLabel *label_28;

    void setupUi(QWidget *RosterMediaPane)
    {
        if (RosterMediaPane->objectName().isEmpty())
            RosterMediaPane->setObjectName(QStringLiteral("RosterMediaPane"));
        RosterMediaPane->resize(635, 300);
        QFont font;
        font.setPointSize(8);
        RosterMediaPane->setFont(font);
        gridLayout_3 = new QGridLayout(RosterMediaPane);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setVerticalSpacing(2);
        gridLayout_3->setContentsMargins(-1, 4, -1, 4);
        label_26 = new QLabel(RosterMediaPane);
        label_26->setObjectName(QStringLiteral("label_26"));

        gridLayout_3->addWidget(label_26, 2, 3, 1, 1);

        edWebReference = new QLineEdit(RosterMediaPane);
        edWebReference->setObjectName(QStringLiteral("edWebReference"));

        gridLayout_3->addWidget(edWebReference, 3, 3, 1, 1);

        label_27 = new QLabel(RosterMediaPane);
        label_27->setObjectName(QStringLiteral("label_27"));

        gridLayout_3->addWidget(label_27, 0, 0, 1, 2);

        label_30 = new QLabel(RosterMediaPane);
        label_30->setObjectName(QStringLiteral("label_30"));

        gridLayout_3->addWidget(label_30, 3, 1, 1, 2);

        lblMainImage = new QLabel(RosterMediaPane);
        lblMainImage->setObjectName(QStringLiteral("lblMainImage"));

        gridLayout_3->addWidget(lblMainImage, 1, 2, 1, 2);

        label_29 = new QLabel(RosterMediaPane);
        label_29->setObjectName(QStringLiteral("label_29"));

        gridLayout_3->addWidget(label_29, 2, 0, 1, 3);

        label_28 = new QLabel(RosterMediaPane);
        label_28->setObjectName(QStringLiteral("label_28"));

        gridLayout_3->addWidget(label_28, 1, 0, 1, 2);


        retranslateUi(RosterMediaPane);

        QMetaObject::connectSlotsByName(RosterMediaPane);
    } // setupUi

    void retranslateUi(QWidget *RosterMediaPane)
    {
        RosterMediaPane->setWindowTitle(QApplication::translate("RosterMediaPane", "Form", 0));
        label_26->setText(QApplication::translate("RosterMediaPane", "image icon", 0));
        label_27->setText(QApplication::translate("RosterMediaPane", "Use this tab to add various media to your roster", 0));
        label_30->setText(QApplication::translate("RosterMediaPane", "Web reference:", 0));
        lblMainImage->setText(QApplication::translate("RosterMediaPane", "Image", 0));
        label_29->setText(QApplication::translate("RosterMediaPane", "Image to be used as an icon for that locomotive; head to the right:", 0));
        label_28->setText(QApplication::translate("RosterMediaPane", "Image to be used as main image for this locomotive ", 0));
    } // retranslateUi

};

namespace Ui {
    class RosterMediaPane: public Ui_RosterMediaPane {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROSTERMEDIA_H
