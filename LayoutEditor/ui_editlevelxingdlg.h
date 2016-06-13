/********************************************************************************
** Form generated from reading UI file 'editlevelxingdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITLEVELXINGDLG_H
#define UI_EDITLEVELXINGDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_EditLevelXingDlg
{
public:
    QFormLayout *formLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *block1Name;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *block2Name;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *xingEdit1Block;
    QPushButton *xingEdit2Block;
    QPushButton *xingEditDone;
    QPushButton *xingEditCancel;

    void setupUi(QDialog *EditLevelXingDlg)
    {
        if (EditLevelXingDlg->objectName().isEmpty())
            EditLevelXingDlg->setObjectName(QStringLiteral("EditLevelXingDlg"));
        EditLevelXingDlg->resize(325, 155);
        EditLevelXingDlg->setModal(false);
        formLayout = new QFormLayout(EditLevelXingDlg);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(EditLevelXingDlg);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        block1Name = new QLineEdit(EditLevelXingDlg);
        block1Name->setObjectName(QStringLiteral("block1Name"));

        horizontalLayout->addWidget(block1Name);


        formLayout->setLayout(0, QFormLayout::SpanningRole, horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(EditLevelXingDlg);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        block2Name = new QLineEdit(EditLevelXingDlg);
        block2Name->setObjectName(QStringLiteral("block2Name"));

        horizontalLayout_2->addWidget(block2Name);


        formLayout->setLayout(1, QFormLayout::SpanningRole, horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        xingEdit1Block = new QPushButton(EditLevelXingDlg);
        xingEdit1Block->setObjectName(QStringLiteral("xingEdit1Block"));

        horizontalLayout_3->addWidget(xingEdit1Block);

        xingEdit2Block = new QPushButton(EditLevelXingDlg);
        xingEdit2Block->setObjectName(QStringLiteral("xingEdit2Block"));

        horizontalLayout_3->addWidget(xingEdit2Block);


        formLayout->setLayout(2, QFormLayout::SpanningRole, horizontalLayout_3);

        xingEditDone = new QPushButton(EditLevelXingDlg);
        xingEditDone->setObjectName(QStringLiteral("xingEditDone"));

        formLayout->setWidget(3, QFormLayout::LabelRole, xingEditDone);

        xingEditCancel = new QPushButton(EditLevelXingDlg);
        xingEditCancel->setObjectName(QStringLiteral("xingEditCancel"));

        formLayout->setWidget(3, QFormLayout::FieldRole, xingEditCancel);


        retranslateUi(EditLevelXingDlg);

        QMetaObject::connectSlotsByName(EditLevelXingDlg);
    } // setupUi

    void retranslateUi(QDialog *EditLevelXingDlg)
    {
        EditLevelXingDlg->setWindowTitle(QApplication::translate("EditLevelXingDlg", "Edit Level Crossing", 0));
        label->setText(QApplication::translate("EditLevelXingDlg", "Block 1", 0));
#ifndef QT_NO_TOOLTIP
        block1Name->setToolTip(QApplication::translate("EditLevelXingDlg", "<html><head/><body><p>Edit block name to change the linked block. If new name, block will be created. </p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        label_2->setText(QApplication::translate("EditLevelXingDlg", "Block 2 ", 0));
#ifndef QT_NO_TOOLTIP
        block2Name->setToolTip(QApplication::translate("EditLevelXingDlg", "<html><head/><body><p>Edit block name to change the linked block. If new name, block will be created. </p></body></html>", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        xingEdit1Block->setToolTip(QApplication::translate("EditLevelXingDlg", "<html><head/><body><p>Click here to create/edit information for the block shown above. </p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        xingEdit1Block->setText(QApplication::translate("EditLevelXingDlg", "Create/Edit Block 1", 0));
#ifndef QT_NO_TOOLTIP
        xingEdit2Block->setToolTip(QApplication::translate("EditLevelXingDlg", "<html><head/><body><p>Click here to create/edit information for the block shown above. </p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        xingEdit2Block->setText(QApplication::translate("EditLevelXingDlg", "Create/Edit Block 2", 0));
        xingEditDone->setText(QApplication::translate("EditLevelXingDlg", "Done", 0));
        xingEditCancel->setText(QApplication::translate("EditLevelXingDlg", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class EditLevelXingDlg: public Ui_EditLevelXingDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITLEVELXINGDLG_H
