/********************************************************************************
** Form generated from reading UI file 'lroutewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LROUTEWIDGET_H
#define UI_LROUTEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LRouteWidget
{
public:
    QVBoxLayout *verticalLayout;
    QTableView *tableView;
    QPushButton *btnAdd;

    void setupUi(QWidget *LRouteWidget)
    {
        if (LRouteWidget->objectName().isEmpty())
            LRouteWidget->setObjectName(QStringLiteral("LRouteWidget"));
        LRouteWidget->resize(400, 258);
        verticalLayout = new QVBoxLayout(LRouteWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tableView = new QTableView(LRouteWidget);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

        verticalLayout->addWidget(tableView);

        btnAdd = new QPushButton(LRouteWidget);
        btnAdd->setObjectName(QStringLiteral("btnAdd"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnAdd->sizePolicy().hasHeightForWidth());
        btnAdd->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(btnAdd);


        retranslateUi(LRouteWidget);

        QMetaObject::connectSlotsByName(LRouteWidget);
    } // setupUi

    void retranslateUi(QWidget *LRouteWidget)
    {
        LRouteWidget->setWindowTitle(QApplication::translate("LRouteWidget", "Form", 0));
        btnAdd->setText(QApplication::translate("LRouteWidget", "Add", 0));
    } // retranslateUi

};

namespace Ui {
    class LRouteWidget: public Ui_LRouteWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LROUTEWIDGET_H
