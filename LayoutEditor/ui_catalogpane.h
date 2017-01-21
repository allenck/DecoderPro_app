/********************************************************************************
** Form generated from reading UI file 'catalogpane.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CATALOGPANE_H
#define UI_CATALOGPANE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CatalogPane
{
public:
    QVBoxLayout *verticalLayout;
    QTreeView *tree;
    QWidget *previewPanel;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QTableWidget *tableWidget;

    void setupUi(QWidget *CatalogPane)
    {
        if (CatalogPane->objectName().isEmpty())
            CatalogPane->setObjectName(QStringLiteral("CatalogPane"));
        CatalogPane->resize(291, 208);
        verticalLayout = new QVBoxLayout(CatalogPane);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tree = new QTreeView(CatalogPane);
        tree->setObjectName(QStringLiteral("tree"));

        verticalLayout->addWidget(tree);

        previewPanel = new QWidget(CatalogPane);
        previewPanel->setObjectName(QStringLiteral("previewPanel"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(previewPanel->sizePolicy().hasHeightForWidth());
        previewPanel->setSizePolicy(sizePolicy);
        previewPanel->setMinimumSize(QSize(0, 106));
        horizontalLayout_2 = new QHBoxLayout(previewPanel);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(previewPanel);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        tableWidget = new QTableWidget(previewPanel);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setMinimumSize(QSize(0, 100));

        horizontalLayout->addWidget(tableWidget);


        horizontalLayout_2->addLayout(horizontalLayout);


        verticalLayout->addWidget(previewPanel);


        retranslateUi(CatalogPane);

        QMetaObject::connectSlotsByName(CatalogPane);
    } // setupUi

    void retranslateUi(QWidget *CatalogPane)
    {
        CatalogPane->setWindowTitle(QApplication::translate("CatalogPane", "Form", 0));
        label->setText(QApplication::translate("CatalogPane", "File Preview:   ", 0));
    } // retranslateUi

};

namespace Ui {
    class CatalogPane: public Ui_CatalogPane {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CATALOGPANE_H
