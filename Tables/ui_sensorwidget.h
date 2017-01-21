/********************************************************************************
** Form generated from reading UI file 'sensorwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SENSORWIDGET_H
#define UI_SENSORWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SensorWidget
{
public:
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;
    QPushButton *btnAdd;
    QCheckBox *chkShowDebounceInfo;

    void setupUi(QWidget *SensorWidget)
    {
        if (SensorWidget->objectName().isEmpty())
            SensorWidget->setObjectName(QStringLiteral("SensorWidget"));
        SensorWidget->resize(400, 300);
        gridLayout = new QGridLayout(SensorWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tabWidget = new QTabWidget(SensorWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tabWidget->addTab(tab_2, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 2);

        btnAdd = new QPushButton(SensorWidget);
        btnAdd->setObjectName(QStringLiteral("btnAdd"));

        gridLayout->addWidget(btnAdd, 1, 0, 1, 1);

        chkShowDebounceInfo = new QCheckBox(SensorWidget);
        chkShowDebounceInfo->setObjectName(QStringLiteral("chkShowDebounceInfo"));

        gridLayout->addWidget(chkShowDebounceInfo, 1, 1, 1, 1);


        retranslateUi(SensorWidget);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SensorWidget);
    } // setupUi

    void retranslateUi(QWidget *SensorWidget)
    {
        SensorWidget->setWindowTitle(QApplication::translate("SensorWidget", "Form", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("SensorWidget", "Tab 1", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("SensorWidget", "Tab 2", 0));
        btnAdd->setText(QApplication::translate("SensorWidget", "Add", 0));
        chkShowDebounceInfo->setText(QApplication::translate("SensorWidget", "Show Sensor Debounce Information ", 0));
    } // retranslateUi

};

namespace Ui {
    class SensorWidget: public Ui_SensorWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENSORWIDGET_H
