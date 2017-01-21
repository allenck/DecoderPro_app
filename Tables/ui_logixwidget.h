/********************************************************************************
** Form generated from reading UI file 'logixwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIXWIDGET_H
#define UI_LOGIXWIDGET_H

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

class Ui_LogixWidget
{
public:
    QVBoxLayout *verticalLayout;
    QTableView *tableView;
    QPushButton *btnAdd;

    void setupUi(QWidget *LogixWidget)
    {
        if (LogixWidget->objectName().isEmpty())
            LogixWidget->setObjectName(QStringLiteral("LogixWidget"));
        LogixWidget->resize(400, 300);
        QFont font;
        font.setPointSize(9);
        LogixWidget->setFont(font);
        verticalLayout = new QVBoxLayout(LogixWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tableView = new QTableView(LogixWidget);
        tableView->setObjectName(QStringLiteral("tableView"));

        verticalLayout->addWidget(tableView);

        btnAdd = new QPushButton(LogixWidget);
        btnAdd->setObjectName(QStringLiteral("btnAdd"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnAdd->sizePolicy().hasHeightForWidth());
        btnAdd->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(btnAdd);


        retranslateUi(LogixWidget);

        QMetaObject::connectSlotsByName(LogixWidget);
    } // setupUi

    void retranslateUi(QWidget *LogixWidget)
    {
        LogixWidget->setWindowTitle(QApplication::translate("LogixWidget", "Form", 0));
        btnAdd->setText(QApplication::translate("LogixWidget", "Add", 0));
    } // retranslateUi

};

namespace Ui {
    class LogixWidget: public Ui_LogixWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIXWIDGET_H
