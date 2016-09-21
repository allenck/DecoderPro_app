/********************************************************************************
** Form generated from reading UI file 'transitwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRANSITWIDGET_H
#define UI_TRANSITWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "jtable.h"

QT_BEGIN_NAMESPACE

class Ui_TransitWidget
{
public:
    QVBoxLayout *verticalLayout;
    JTable *tableView;
    QPushButton *pushButton;

    void setupUi(QWidget *TransitWidget)
    {
        if (TransitWidget->objectName().isEmpty())
            TransitWidget->setObjectName(QStringLiteral("TransitWidget"));
        TransitWidget->resize(400, 300);
        verticalLayout = new QVBoxLayout(TransitWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tableView = new JTable(TransitWidget);
        tableView->setObjectName(QStringLiteral("tableView"));

        verticalLayout->addWidget(tableView);

        pushButton = new QPushButton(TransitWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(pushButton);


        retranslateUi(TransitWidget);

        QMetaObject::connectSlotsByName(TransitWidget);
    } // setupUi

    void retranslateUi(QWidget *TransitWidget)
    {
        TransitWidget->setWindowTitle(QApplication::translate("TransitWidget", "Form", 0));
        pushButton->setText(QApplication::translate("TransitWidget", "Add", 0));
    } // retranslateUi

};

namespace Ui {
    class TransitWidget: public Ui_TransitWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRANSITWIDGET_H
