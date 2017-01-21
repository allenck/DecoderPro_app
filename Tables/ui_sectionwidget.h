/********************************************************************************
** Form generated from reading UI file 'sectionwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SECTIONWIDGET_H
#define UI_SECTIONWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <jtable.h>

QT_BEGIN_NAMESPACE

class Ui_SectionWidget
{
public:
    QVBoxLayout *verticalLayout;
    JTable *tableView;
    QPushButton *btnAdd;

    void setupUi(QWidget *SectionWidget)
    {
        if (SectionWidget->objectName().isEmpty())
            SectionWidget->setObjectName(QStringLiteral("SectionWidget"));
        SectionWidget->resize(400, 300);
        verticalLayout = new QVBoxLayout(SectionWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tableView = new JTable(SectionWidget);
        tableView->setObjectName(QStringLiteral("tableView"));

        verticalLayout->addWidget(tableView);

        btnAdd = new QPushButton(SectionWidget);
        btnAdd->setObjectName(QStringLiteral("btnAdd"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnAdd->sizePolicy().hasHeightForWidth());
        btnAdd->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(btnAdd);


        retranslateUi(SectionWidget);

        QMetaObject::connectSlotsByName(SectionWidget);
    } // setupUi

    void retranslateUi(QWidget *SectionWidget)
    {
        SectionWidget->setWindowTitle(QApplication::translate("SectionWidget", "Form", 0));
        btnAdd->setText(QApplication::translate("SectionWidget", "Add", 0));
    } // retranslateUi

};

namespace Ui {
    class SectionWidget: public Ui_SectionWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SECTIONWIDGET_H
