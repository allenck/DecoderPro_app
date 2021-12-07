/********************************************************************************
** Form generated from reading UI file 'editconditionalframe.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITCONDITIONALFRAME_H
#define UI_EDITCONDITIONALFRAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_editConditionalFrame
{
public:
    QVBoxLayout *verticalLayout_8;
    QWidget *panel1;
    QVBoxLayout *verticalLayout1;
    QHBoxLayout *p1HBoxLayout1;
    QLabel *label;
    QLabel *label_2;
    QHBoxLayout *p1HBoxLayout2;
    QLabel *label_3;
    QLineEdit *conditionalUserName;
    QGroupBox *logicPanel;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_4;
    QTableView *tableView;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_5;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *actionPanel;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_6;
    QTableView *tableView_2;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_3;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;

    void setupUi(QWidget *editConditionalFrame)
    {
        if (editConditionalFrame->objectName().isEmpty())
            editConditionalFrame->setObjectName(QString::fromUtf8("editConditionalFrame"));
        editConditionalFrame->resize(416, 667);
        QFont font;
        font.setPointSize(9);
        editConditionalFrame->setFont(font);
        verticalLayout_8 = new QVBoxLayout(editConditionalFrame);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        panel1 = new QWidget(editConditionalFrame);
        panel1->setObjectName(QString::fromUtf8("panel1"));
        verticalLayout1 = new QVBoxLayout(panel1);
        verticalLayout1->setObjectName(QString::fromUtf8("verticalLayout1"));
        p1HBoxLayout1 = new QHBoxLayout();
        p1HBoxLayout1->setObjectName(QString::fromUtf8("p1HBoxLayout1"));
        label = new QLabel(panel1);
        label->setObjectName(QString::fromUtf8("label"));

        p1HBoxLayout1->addWidget(label);

        label_2 = new QLabel(panel1);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        p1HBoxLayout1->addWidget(label_2);


        verticalLayout1->addLayout(p1HBoxLayout1);

        p1HBoxLayout2 = new QHBoxLayout();
        p1HBoxLayout2->setObjectName(QString::fromUtf8("p1HBoxLayout2"));
        label_3 = new QLabel(panel1);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        p1HBoxLayout2->addWidget(label_3);

        conditionalUserName = new QLineEdit(panel1);
        conditionalUserName->setObjectName(QString::fromUtf8("conditionalUserName"));

        p1HBoxLayout2->addWidget(conditionalUserName);


        verticalLayout1->addLayout(p1HBoxLayout2);


        verticalLayout_8->addWidget(panel1);

        logicPanel = new QGroupBox(editConditionalFrame);
        logicPanel->setObjectName(QString::fromUtf8("logicPanel"));
        verticalLayout_5 = new QVBoxLayout(logicPanel);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label_4 = new QLabel(logicPanel);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        label_4->setFont(font1);
        label_4->setFrameShape(QFrame::NoFrame);
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label_4);

        tableView = new QTableView(logicPanel);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        verticalLayout_5->addWidget(tableView);

        widget_2 = new QWidget(logicPanel);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        verticalLayout_2 = new QVBoxLayout(widget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pushButton = new QPushButton(widget_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(pushButton);

        pushButton_2 = new QPushButton(widget_2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(pushButton_2);


        verticalLayout_2->addLayout(horizontalLayout_3);


        verticalLayout_5->addWidget(widget_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(98, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        widget_3 = new QWidget(logicPanel);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        sizePolicy.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());
        widget_3->setSizePolicy(sizePolicy);
        verticalLayout_4 = new QVBoxLayout(widget_3);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_5 = new QLabel(widget_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_3->addWidget(label_5);

        comboBox = new QComboBox(widget_3);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        verticalLayout_3->addWidget(comboBox);


        verticalLayout_4->addLayout(verticalLayout_3);


        horizontalLayout_4->addWidget(widget_3);

        horizontalSpacer_2 = new QSpacerItem(108, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        verticalLayout_5->addLayout(horizontalLayout_4);


        verticalLayout_8->addWidget(logicPanel);

        actionPanel = new QGroupBox(editConditionalFrame);
        actionPanel->setObjectName(QString::fromUtf8("actionPanel"));
        verticalLayout_7 = new QVBoxLayout(actionPanel);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        label_6 = new QLabel(actionPanel);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font1);
        label_6->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(label_6);

        tableView_2 = new QTableView(actionPanel);
        tableView_2->setObjectName(QString::fromUtf8("tableView_2"));

        verticalLayout_7->addWidget(tableView_2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_3);

        widget_4 = new QWidget(actionPanel);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        verticalLayout_6 = new QVBoxLayout(widget_4);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        pushButton_3 = new QPushButton(widget_4);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        horizontalLayout_5->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(widget_4);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        horizontalLayout_5->addWidget(pushButton_4);


        verticalLayout_6->addLayout(horizontalLayout_5);


        horizontalLayout_6->addWidget(widget_4);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_4);


        verticalLayout_7->addLayout(horizontalLayout_6);


        verticalLayout_8->addWidget(actionPanel);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        pushButton_5 = new QPushButton(editConditionalFrame);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));

        horizontalLayout_7->addWidget(pushButton_5);

        pushButton_6 = new QPushButton(editConditionalFrame);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));

        horizontalLayout_7->addWidget(pushButton_6);

        pushButton_7 = new QPushButton(editConditionalFrame);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));

        horizontalLayout_7->addWidget(pushButton_7);


        verticalLayout_8->addLayout(horizontalLayout_7);


        retranslateUi(editConditionalFrame);

        QMetaObject::connectSlotsByName(editConditionalFrame);
    } // setupUi

    void retranslateUi(QWidget *editConditionalFrame)
    {
        editConditionalFrame->setWindowTitle(QCoreApplication::translate("editConditionalFrame", "Form", nullptr));
        label->setText(QCoreApplication::translate("editConditionalFrame", "Conditional System Name ", nullptr));
        label_2->setText(QCoreApplication::translate("editConditionalFrame", "IX:AUTO:0001C3", nullptr));
        label_3->setText(QCoreApplication::translate("editConditionalFrame", "Conditional User Name", nullptr));
#if QT_CONFIG(tooltip)
        conditionalUserName->setToolTip(QCoreApplication::translate("editConditionalFrame", "<html><head/><body><p><span style=\" color:#008000;\">Enter</span><span style=\" color:#c0c0c0;\"/><span style=\" color:#008000;\">user</span><span style=\" color:#c0c0c0;\"/><span style=\" color:#008000;\">name</span><span style=\" color:#c0c0c0;\"/><span style=\" color:#008000;\">for</span><span style=\" color:#c0c0c0;\"/><span style=\" color:#008000;\">Conditional,</span><span style=\" color:#c0c0c0;\"/><span style=\" color:#008000;\">e.g.</span><span style=\" color:#c0c0c0;\"/><span style=\" color:#008000;\">Signal</span><span style=\" color:#c0c0c0;\"/><span style=\" color:#008000;\">2</span><span style=\" color:#c0c0c0;\"/><span style=\" color:#008000;\">Red</span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        logicPanel->setTitle(QCoreApplication::translate("editConditionalFrame", "Logical Expression", nullptr));
        label_4->setText(QCoreApplication::translate("editConditionalFrame", "Antecedent Variables (the 'if' part)", nullptr));
        pushButton->setText(QCoreApplication::translate("editConditionalFrame", "Add State Variable", nullptr));
        pushButton_2->setText(QCoreApplication::translate("editConditionalFrame", "Check State Variables", nullptr));
        label_5->setText(QCoreApplication::translate("editConditionalFrame", "Logic Operator", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("editConditionalFrame", "AND", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("editConditionalFrame", "OR", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("editConditionalFrame", "Mixed", nullptr));

        actionPanel->setTitle(QCoreApplication::translate("editConditionalFrame", "Actions", nullptr));
        label_6->setText(QCoreApplication::translate("editConditionalFrame", "Consequent Actions (the 'then' part)", nullptr));
        pushButton_3->setText(QCoreApplication::translate("editConditionalFrame", "Add Action", nullptr));
        pushButton_4->setText(QCoreApplication::translate("editConditionalFrame", "Reorder", nullptr));
        pushButton_5->setText(QCoreApplication::translate("editConditionalFrame", "Update Conditional", nullptr));
        pushButton_6->setText(QCoreApplication::translate("editConditionalFrame", "Cancel", nullptr));
        pushButton_7->setText(QCoreApplication::translate("editConditionalFrame", "Delete Conditional", nullptr));
    } // retranslateUi

};

namespace Ui {
    class editConditionalFrame: public Ui_editConditionalFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITCONDITIONALFRAME_H
