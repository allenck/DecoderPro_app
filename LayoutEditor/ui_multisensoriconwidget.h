/********************************************************************************
** Form generated from reading UI file 'multisensoriconwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MULTISENSORICONWIDGET_H
#define UI_MULTISENSORICONWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
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
            MultiSensorIconWidget->setObjectName(QString::fromUtf8("MultiSensorIconWidget"));
        MultiSensorIconWidget->resize(398, 312);
        verticalLayout_5 = new QVBoxLayout(MultiSensorIconWidget);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label = new QLabel(MultiSensorIconWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(2, 0));
        label->setWordWrap(true);

        verticalLayout_5->addWidget(label);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetNoConstraint);

        verticalLayout_5->addLayout(gridLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_2 = new QLabel(MultiSensorIconWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(label_2);

        pbInconsistent = new DropPushButton(MultiSensorIconWidget);
        pbInconsistent->setObjectName(QString::fromUtf8("pbInconsistent"));
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
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_3 = new QLabel(MultiSensorIconWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_2->addWidget(label_3);

        pbUnknown = new DropPushButton(MultiSensorIconWidget);
        pbUnknown->setObjectName(QString::fromUtf8("pbUnknown"));
        sizePolicy1.setHeightForWidth(pbUnknown->sizePolicy().hasHeightForWidth());
        pbUnknown->setSizePolicy(sizePolicy1);
        pbUnknown->setMinimumSize(QSize(48, 48));
        pbUnknown->setBaseSize(QSize(80, 80));

        verticalLayout_2->addWidget(pbUnknown);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_4 = new QLabel(MultiSensorIconWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_3->addWidget(label_4);

        pbInactive = new DropPushButton(MultiSensorIconWidget);
        pbInactive->setObjectName(QString::fromUtf8("pbInactive"));
        sizePolicy1.setHeightForWidth(pbInactive->sizePolicy().hasHeightForWidth());
        pbInactive->setSizePolicy(sizePolicy1);
        pbInactive->setMinimumSize(QSize(48, 48));
        pbInactive->setBaseSize(QSize(80, 80));

        verticalLayout_3->addWidget(pbInactive);


        horizontalLayout->addLayout(verticalLayout_3);


        verticalLayout_5->addLayout(horizontalLayout);

        tableWidget_2 = new QWidget(MultiSensorIconWidget);
        tableWidget_2->setObjectName(QString::fromUtf8("tableWidget_2"));
        verticalLayout_6 = new QVBoxLayout(tableWidget_2);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        tableWidget = new QTableWidget(tableWidget_2);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        verticalLayout_4->addWidget(tableWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        rbUpDown = new QRadioButton(tableWidget_2);
        rbUpDown->setObjectName(QString::fromUtf8("rbUpDown"));

        horizontalLayout_2->addWidget(rbUpDown);

        rbRightLeft = new QRadioButton(tableWidget_2);
        rbRightLeft->setObjectName(QString::fromUtf8("rbRightLeft"));

        horizontalLayout_2->addWidget(rbRightLeft);

        pbAddIcon = new QPushButton(tableWidget_2);
        pbAddIcon->setObjectName(QString::fromUtf8("pbAddIcon"));

        horizontalLayout_2->addWidget(pbAddIcon);


        verticalLayout_4->addLayout(horizontalLayout_2);


        verticalLayout_6->addLayout(verticalLayout_4);


        verticalLayout_5->addWidget(tableWidget_2);


        retranslateUi(MultiSensorIconWidget);

        QMetaObject::connectSlotsByName(MultiSensorIconWidget);
    } // setupUi

    void retranslateUi(QWidget *MultiSensorIconWidget)
    {
        MultiSensorIconWidget->setWindowTitle(QCoreApplication::translate("MultiSensorIconWidget", "Form", nullptr));
        label->setText(QCoreApplication::translate("MultiSensorIconWidget", "To add a MultiSensor to the Panel,\n"
"drag Sensors from table into the red boxes, then press Add to Panel.", nullptr));
        label_2->setText(QCoreApplication::translate("MultiSensorIconWidget", "Inconsistent", nullptr));
        pbInconsistent->setText(QString());
        label_3->setText(QCoreApplication::translate("MultiSensorIconWidget", "Unknown", nullptr));
        pbUnknown->setText(QString());
        label_4->setText(QCoreApplication::translate("MultiSensorIconWidget", "Inactive", nullptr));
        pbInactive->setText(QString());
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MultiSensorIconWidget", "System Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MultiSensorIconWidget", "User Name", nullptr));
        rbUpDown->setText(QCoreApplication::translate("MultiSensorIconWidget", "Up - Down", nullptr));
        rbRightLeft->setText(QCoreApplication::translate("MultiSensorIconWidget", "Right - Left", nullptr));
        pbAddIcon->setText(QCoreApplication::translate("MultiSensorIconWidget", "Add Another Icon", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MultiSensorIconWidget: public Ui_MultiSensorIconWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MULTISENSORICONWIDGET_H
