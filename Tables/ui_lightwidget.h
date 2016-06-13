/********************************************************************************
** Form generated from reading UI file 'lightwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LIGHTWIDGET_H
#define UI_LIGHTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LightWidget
{
public:
    QGridLayout *gridLayout;
    QPushButton *btnAdd;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;
    QLabel *label;

    void setupUi(QDialog *LightWidget)
    {
        if (LightWidget->objectName().isEmpty())
            LightWidget->setObjectName(QStringLiteral("LightWidget"));
        LightWidget->resize(400, 300);
        gridLayout = new QGridLayout(LightWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        btnAdd = new QPushButton(LightWidget);
        btnAdd->setObjectName(QStringLiteral("btnAdd"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnAdd->sizePolicy().hasHeightForWidth());
        btnAdd->setSizePolicy(sizePolicy);

        gridLayout->addWidget(btnAdd, 1, 1, 1, 1);

        tabWidget = new QTabWidget(LightWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tabWidget->addTab(tab_2, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 4);

        label = new QLabel(LightWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 1, 2, 1, 1);


        retranslateUi(LightWidget);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(LightWidget);
    } // setupUi

    void retranslateUi(QDialog *LightWidget)
    {
        LightWidget->setWindowTitle(QApplication::translate("LightWidget", "Dialog", 0));
        btnAdd->setText(QApplication::translate("LightWidget", "Add", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("LightWidget", "All", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("LightWidget", "Internal", 0));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LightWidget: public Ui_LightWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LIGHTWIDGET_H
