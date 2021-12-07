/********************************************************************************
** Form generated from reading UI file 'editlevelxingdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITLEVELXINGDLG_H
#define UI_EDITLEVELXINGDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
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
            EditLevelXingDlg->setObjectName(QString::fromUtf8("EditLevelXingDlg"));
        EditLevelXingDlg->resize(325, 155);
        EditLevelXingDlg->setModal(false);
        formLayout = new QFormLayout(EditLevelXingDlg);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(EditLevelXingDlg);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        block1Name = new QLineEdit(EditLevelXingDlg);
        block1Name->setObjectName(QString::fromUtf8("block1Name"));

        horizontalLayout->addWidget(block1Name);


        formLayout->setLayout(0, QFormLayout::SpanningRole, horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(EditLevelXingDlg);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        block2Name = new QLineEdit(EditLevelXingDlg);
        block2Name->setObjectName(QString::fromUtf8("block2Name"));

        horizontalLayout_2->addWidget(block2Name);


        formLayout->setLayout(1, QFormLayout::SpanningRole, horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        xingEdit1Block = new QPushButton(EditLevelXingDlg);
        xingEdit1Block->setObjectName(QString::fromUtf8("xingEdit1Block"));

        horizontalLayout_3->addWidget(xingEdit1Block);

        xingEdit2Block = new QPushButton(EditLevelXingDlg);
        xingEdit2Block->setObjectName(QString::fromUtf8("xingEdit2Block"));

        horizontalLayout_3->addWidget(xingEdit2Block);


        formLayout->setLayout(2, QFormLayout::SpanningRole, horizontalLayout_3);

        xingEditDone = new QPushButton(EditLevelXingDlg);
        xingEditDone->setObjectName(QString::fromUtf8("xingEditDone"));

        formLayout->setWidget(3, QFormLayout::LabelRole, xingEditDone);

        xingEditCancel = new QPushButton(EditLevelXingDlg);
        xingEditCancel->setObjectName(QString::fromUtf8("xingEditCancel"));

        formLayout->setWidget(3, QFormLayout::FieldRole, xingEditCancel);


        retranslateUi(EditLevelXingDlg);

        QMetaObject::connectSlotsByName(EditLevelXingDlg);
    } // setupUi

    void retranslateUi(QDialog *EditLevelXingDlg)
    {
        EditLevelXingDlg->setWindowTitle(QCoreApplication::translate("EditLevelXingDlg", "Edit Level Crossing", nullptr));
        label->setText(QCoreApplication::translate("EditLevelXingDlg", "Block 1", nullptr));
#if QT_CONFIG(tooltip)
        block1Name->setToolTip(QCoreApplication::translate("EditLevelXingDlg", "<html><head/><body><p>Edit block name to change the linked block. If new name, block will be created. </p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_2->setText(QCoreApplication::translate("EditLevelXingDlg", "Block 2 ", nullptr));
#if QT_CONFIG(tooltip)
        block2Name->setToolTip(QCoreApplication::translate("EditLevelXingDlg", "<html><head/><body><p>Edit block name to change the linked block. If new name, block will be created. </p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        xingEdit1Block->setToolTip(QCoreApplication::translate("EditLevelXingDlg", "<html><head/><body><p>Click here to create/edit information for the block shown above. </p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        xingEdit1Block->setText(QCoreApplication::translate("EditLevelXingDlg", "Create/Edit Block 1", nullptr));
#if QT_CONFIG(tooltip)
        xingEdit2Block->setToolTip(QCoreApplication::translate("EditLevelXingDlg", "<html><head/><body><p>Click here to create/edit information for the block shown above. </p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        xingEdit2Block->setText(QCoreApplication::translate("EditLevelXingDlg", "Create/Edit Block 2", nullptr));
        xingEditDone->setText(QCoreApplication::translate("EditLevelXingDlg", "Done", nullptr));
        xingEditCancel->setText(QCoreApplication::translate("EditLevelXingDlg", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditLevelXingDlg: public Ui_EditLevelXingDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITLEVELXINGDLG_H
