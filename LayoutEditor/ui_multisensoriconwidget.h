/********************************************************************************
** Form generated from reading UI file 'multisensoriconwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MULTISENSORICONWIDGET_H
#define UI_MULTISENSORICONWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "droppushbutton.h"

QT_BEGIN_NAMESPACE

class Ui_MultiSensorIconWidget
{
public:
    QVBoxLayout *verticalLayout_5;
    QLabel *label;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    DropPushButton *pbInconsistent;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    DropPushButton *pbUnknown;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_4;
    DropPushButton *pbInactive;
    QWidget *tableWidget_2;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_4;
    QTableWidget *tableWidget;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *rbUpDown;
    QRadioButton *rbRightLeft;
    QPushButton *pbAddIcon;

    void setupUi(QWidget *MultiSensorIconWidget)
    {
        if (MultiSensorIconWidget->objectName().isEmpty())
            MultiSensorIconWidget->setObjectName(QStringLiteral("MultiSensorIconWidget"));
        MultiSensorIconWidget->resize(398, 312);
        verticalLayout_5 = new QVBoxLayout(MultiSensorIconWidget);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        label = new QLabel(MultiSensorIconWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(2, 0));
        label->setWordWrap(true);

        verticalLayout_5->addWidget(label);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetNoConstraint);

        verticalLayout_5->addLayout(gridLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_2 = new QLabel(MultiSensorIconWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(label_2);

        pbInconsistent = new DropPushButton(MultiSensorIconWidget);
        pbInconsistent->setObjectName(QStringLiteral("pbInconsistent"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pbInconsistent->sizePolicy().hasHeightForWidth());
        pbInconsistent->setSizePolicy(sizePolicy1);
        pbInconsistent->setMinimumSize(QSize(48, 48));
        pbInconsistent->setBaseSize(QSize(80, 80));

        verticalLayout->addWidget(pbInconsistent);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_3 = new QLabel(MultiSensorIconWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_2->addWidget(label_3);

        pbUnknown = new DropPushButton(MultiSensorIconWidget);
        pbUnknown->setObjectName(QStringLiteral("pbUnknown"));
        sizePolicy1.setHeightForWidth(pbUnknown->sizePolicy().hasHeightForWidth());
        pbUnknown->setSizePolicy(sizePolicy1);
        pbUnknown->setMinimumSize(QSize(48, 48));
        pbUnknown->setBaseSize(QSize(80, 80));

        verticalLayout_2->addWidget(pbUnknown);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_4 = new QLabel(MultiSensorIconWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout_3->addWidget(label_4);

        pbInactive = new DropPushButton(MultiSensorIconWidget);
        pbInactive->setObjectName(QStringLiteral("pbInactive"));
        sizePolicy1.setHeightForWidth(pbInactive->sizePolicy().hasHeightForWidth());
        pbInactive->setSizePolicy(sizePolicy1);
        pbInactive->setMinimumSize(QSize(48, 48));
        pbInactive->setBaseSize(QSize(80, 80));

        verticalLayout_3->addWidget(pbInactive);


        horizontalLayout->addLayout(verticalLayout_3);


        verticalLayout_5->addLayout(horizontalLayout);

        tableWidget_2 = new QWidget(MultiSensorIconWidget);
        tableWidget_2->setObjectName(QStringLiteral("tableWidget_2"));
        verticalLayout_6 = new QVBoxLayout(tableWidget_2);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        tableWidget = new QTableWidget(tableWidget_2);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        verticalLayout_4->addWidget(tableWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        rbUpDown = new QRadioButton(tableWidget_2);
        rbUpDown->setObjectName(QStringLiteral("rbUpDown"));

        horizontalLayout_2->addWidget(rbUpDown);

        rbRightLeft = new QRadioButton(tableWidget_2);
        rbRightLeft->setObjectName(QStringLiteral("rbRightLeft"));

        horizontalLayout_2->addWidget(rbRightLeft);

        pbAddIcon = new QPushButton(tableWidget_2);
        pbAddIcon->setObjectName(QStringLiteral("pbAddIcon"));

        horizontalLayout_2->addWidget(pbAddIcon);


        verticalLayout_4->addLayout(horizontalLayout_2);


        verticalLayout_6->addLayout(verticalLayout_4);


        verticalLayout_5->addWidget(tableWidget_2);


        retranslateUi(MultiSensorIconWidget);

        QMetaObject::connectSlotsByName(MultiSensorIconWidget);
    } // setupUi

    void retranslateUi(QWidget *MultiSensorIconWidget)
    {
        MultiSensorIconWidget->setWindowTitle(QApplication::translate("MultiSensorIconWidget", "Form", 0));
        label->setText(QApplication::translate("MultiSensorIconWidget", "To add a MultiSensor to the Panel,\n"
"drag Sensors from table into the red boxes, then press Add to Panel.", 0));
        label_2->setText(QApplication::translate("MultiSensorIconWidget", "Inconsistent", 0));
        pbInconsistent->setText(QString());
        label_3->setText(QApplication::translate("MultiSensorIconWidget", "Unknown", 0));
        pbUnknown->setText(QString());
        label_4->setText(QApplication::translate("MultiSensorIconWidget", "Inactive", 0));
        pbInactive->setText(QString());
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MultiSensorIconWidget", "System Name", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MultiSensorIconWidget", "User Name", 0));
        rbUpDown->setText(QApplication::translate("MultiSensorIconWidget", "Up - Down", 0));
        rbRightLeft->setText(QApplication::translate("MultiSensorIconWidget", "Right - Left", 0));
        pbAddIcon->setText(QApplication::translate("MultiSensorIconWidget", "Add Another Icon", 0));
    } // retranslateUi

};

namespace Ui {
    class MultiSensorIconWidget: public Ui_MultiSensorIconWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MULTISENSORICONWIDGET_H
