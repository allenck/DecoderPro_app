/********************************************************************************
** Form generated from reading UI file 'extraopcodewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXTRAOPCODEWIDGET_H
#define UI_EXTRAOPCODEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ExtraOpcodeWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *lblBigRedX;
    QRadioButton *rbOff;
    QRadioButton *rbDirect;
    QRadioButton *rbIndirect;
    QRadioButton *rbContact1;
    QRadioButton *rbContact2;
    QLineEdit *edAddr;
    QLineEdit *edCfg;
    QLineEdit *edVal1;
    QLineEdit *edVal2;

    void setupUi(QWidget *ExtraOpcodeWidget)
    {
        if (ExtraOpcodeWidget->objectName().isEmpty())
            ExtraOpcodeWidget->setObjectName(QString::fromUtf8("ExtraOpcodeWidget"));
        ExtraOpcodeWidget->resize(32, 258);
        QFont font;
        font.setPointSize(7);
        font.setItalic(false);
        ExtraOpcodeWidget->setFont(font);
        verticalLayout_2 = new QVBoxLayout(ExtraOpcodeWidget);
        verticalLayout_2->setSpacing(2);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lblBigRedX = new QLabel(ExtraOpcodeWidget);
        lblBigRedX->setObjectName(QString::fromUtf8("lblBigRedX"));
        QPalette palette;
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush1(QColor(159, 158, 158, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        lblBigRedX->setPalette(palette);
        QFont font1;
        font1.setPointSize(24);
        lblBigRedX->setFont(font1);
        lblBigRedX->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(lblBigRedX);

        rbOff = new QRadioButton(ExtraOpcodeWidget);
        rbOff->setObjectName(QString::fromUtf8("rbOff"));
        rbOff->setChecked(true);

        verticalLayout->addWidget(rbOff);

        rbDirect = new QRadioButton(ExtraOpcodeWidget);
        rbDirect->setObjectName(QString::fromUtf8("rbDirect"));

        verticalLayout->addWidget(rbDirect);

        rbIndirect = new QRadioButton(ExtraOpcodeWidget);
        rbIndirect->setObjectName(QString::fromUtf8("rbIndirect"));

        verticalLayout->addWidget(rbIndirect);

        rbContact1 = new QRadioButton(ExtraOpcodeWidget);
        rbContact1->setObjectName(QString::fromUtf8("rbContact1"));

        verticalLayout->addWidget(rbContact1);

        rbContact2 = new QRadioButton(ExtraOpcodeWidget);
        rbContact2->setObjectName(QString::fromUtf8("rbContact2"));

        verticalLayout->addWidget(rbContact2);

        edAddr = new QLineEdit(ExtraOpcodeWidget);
        edAddr->setObjectName(QString::fromUtf8("edAddr"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(edAddr->sizePolicy().hasHeightForWidth());
        edAddr->setSizePolicy(sizePolicy);
        edAddr->setMaximumSize(QSize(30, 16777215));
        edAddr->setMaxLength(5);

        verticalLayout->addWidget(edAddr);

        edCfg = new QLineEdit(ExtraOpcodeWidget);
        edCfg->setObjectName(QString::fromUtf8("edCfg"));
        sizePolicy.setHeightForWidth(edCfg->sizePolicy().hasHeightForWidth());
        edCfg->setSizePolicy(sizePolicy);
        edCfg->setMaximumSize(QSize(30, 16777215));
        edCfg->setMaxLength(5);

        verticalLayout->addWidget(edCfg);

        edVal1 = new QLineEdit(ExtraOpcodeWidget);
        edVal1->setObjectName(QString::fromUtf8("edVal1"));
        edVal1->setMaximumSize(QSize(30, 16777215));
        edVal1->setMaxLength(5);

        verticalLayout->addWidget(edVal1);

        edVal2 = new QLineEdit(ExtraOpcodeWidget);
        edVal2->setObjectName(QString::fromUtf8("edVal2"));
        sizePolicy.setHeightForWidth(edVal2->sizePolicy().hasHeightForWidth());
        edVal2->setSizePolicy(sizePolicy);
        edVal2->setMaximumSize(QSize(30, 16777215));
        edVal2->setMaxLength(5);

        verticalLayout->addWidget(edVal2);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(ExtraOpcodeWidget);

        QMetaObject::connectSlotsByName(ExtraOpcodeWidget);
    } // setupUi

    void retranslateUi(QWidget *ExtraOpcodeWidget)
    {
        ExtraOpcodeWidget->setWindowTitle(QCoreApplication::translate("ExtraOpcodeWidget", "Form", nullptr));
        lblBigRedX->setText(QCoreApplication::translate("ExtraOpcodeWidget", "X", nullptr));
        rbOff->setText(QString());
        rbDirect->setText(QString());
        rbIndirect->setText(QString());
        rbContact1->setText(QString());
        rbContact2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ExtraOpcodeWidget: public Ui_ExtraOpcodeWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXTRAOPCODEWIDGET_H
