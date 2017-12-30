/********************************************************************************
** Form generated from reading UI file 'blockwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BLOCKWIDGET_H
#define UI_BLOCKWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <jtable.h>

QT_BEGIN_NAMESPACE

class Ui_BlockWidget
{
public:
    QGridLayout *gridLayout;
    QPushButton *btnAdd;
    QCheckBox *chkInches;
    QCheckBox *chlCentimeters;
    JTable *tableView;

    void setupUi(QWidget *BlockWidget)
    {
        if (BlockWidget->objectName().isEmpty())
            BlockWidget->setObjectName(QStringLiteral("BlockWidget"));
        BlockWidget->resize(440, 238);
        gridLayout = new QGridLayout(BlockWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        btnAdd = new QPushButton(BlockWidget);
        btnAdd->setObjectName(QStringLiteral("btnAdd"));

        gridLayout->addWidget(btnAdd, 1, 0, 1, 1);

        chkInches = new QCheckBox(BlockWidget);
        chkInches->setObjectName(QStringLiteral("chkInches"));

        gridLayout->addWidget(chkInches, 1, 1, 1, 1);

        chlCentimeters = new QCheckBox(BlockWidget);
        chlCentimeters->setObjectName(QStringLiteral("chlCentimeters"));

        gridLayout->addWidget(chlCentimeters, 1, 2, 1, 1);

        tableView = new JTable(BlockWidget);
        tableView->setObjectName(QStringLiteral("tableView"));

        gridLayout->addWidget(tableView, 0, 0, 1, 3);


        retranslateUi(BlockWidget);

        QMetaObject::connectSlotsByName(BlockWidget);
    } // setupUi

    void retranslateUi(QWidget *BlockWidget)
    {
        BlockWidget->setWindowTitle(QApplication::translate("BlockWidget", "Form", Q_NULLPTR));
        btnAdd->setText(QApplication::translate("BlockWidget", "Add...", Q_NULLPTR));
        chkInches->setText(QApplication::translate("BlockWidget", "Length in Inches", Q_NULLPTR));
        chlCentimeters->setText(QApplication::translate("BlockWidget", "Length in Centimeters", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class BlockWidget: public Ui_BlockWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BLOCKWIDGET_H
