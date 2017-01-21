/********************************************************************************
** Form generated from reading UI file 'createeditblock.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEEDITBLOCK_H
#define UI_CREATEEDITBLOCK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CreateEditBlock
{
public:
    QWidget *centralwidget;
    QFormLayout *formLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *blockNameLabel;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLabel *blockUseLabel;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *sensorNameField;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *sensorDebounceGlobalCheck;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_9;
    QLineEdit *sensorDebounceInactiveField;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_10;
    QLineEdit *sensorDebounceActiveField;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_6;
    QComboBox *trackColorBox;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_7;
    QComboBox *occupiedColorBox;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_8;
    QComboBox *extraColorBox;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_5;
    QLineEdit *memoryNameField;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_11;
    QLineEdit *metricField;
    QSpacerItem *horizontalSpacer_4;
    QCheckBox *permissiveCheck;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *blockEditDone;
    QPushButton *blockEditCancel;
    QComboBox *senseBox;
    QSpacerItem *horizontalSpacer_6;
    QMenuBar *menubar;
    QMenu *menuWindow;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *CreateEditBlock)
    {
        if (CreateEditBlock->objectName().isEmpty())
            CreateEditBlock->setObjectName(QStringLiteral("CreateEditBlock"));
        CreateEditBlock->resize(357, 729);
        centralwidget = new QWidget(CreateEditBlock);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        formLayout = new QFormLayout(centralwidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        blockNameLabel = new QLabel(centralwidget);
        blockNameLabel->setObjectName(QStringLiteral("blockNameLabel"));

        horizontalLayout->addWidget(blockNameLabel);


        formLayout->setLayout(0, QFormLayout::LabelRole, horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        blockUseLabel = new QLabel(centralwidget);
        blockUseLabel->setObjectName(QStringLiteral("blockUseLabel"));

        horizontalLayout_2->addWidget(blockUseLabel);


        formLayout->setLayout(1, QFormLayout::LabelRole, horizontalLayout_2);

        horizontalSpacer = new QSpacerItem(334, 15, QSizePolicy::Expanding, QSizePolicy::Minimum);

        formLayout->setItem(2, QFormLayout::SpanningRole, horizontalSpacer);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        sensorNameField = new QLineEdit(centralwidget);
        sensorNameField->setObjectName(QStringLiteral("sensorNameField"));

        horizontalLayout_3->addWidget(sensorNameField);


        formLayout->setLayout(3, QFormLayout::SpanningRole, horizontalLayout_3);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_4);

        horizontalSpacer_2 = new QSpacerItem(334, 15, QSizePolicy::Expanding, QSizePolicy::Minimum);

        formLayout->setItem(6, QFormLayout::SpanningRole, horizontalSpacer_2);

        sensorDebounceGlobalCheck = new QCheckBox(centralwidget);
        sensorDebounceGlobalCheck->setObjectName(QStringLiteral("sensorDebounceGlobalCheck"));

        formLayout->setWidget(7, QFormLayout::LabelRole, sensorDebounceGlobalCheck);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_4->addWidget(label_9);

        sensorDebounceInactiveField = new QLineEdit(centralwidget);
        sensorDebounceInactiveField->setObjectName(QStringLiteral("sensorDebounceInactiveField"));
        sensorDebounceInactiveField->setInputMethodHints(Qt::ImhDigitsOnly);
        sensorDebounceInactiveField->setMaxLength(4);

        horizontalLayout_4->addWidget(sensorDebounceInactiveField);


        formLayout->setLayout(8, QFormLayout::LabelRole, horizontalLayout_4);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_10 = new QLabel(centralwidget);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_11->addWidget(label_10);

        sensorDebounceActiveField = new QLineEdit(centralwidget);
        sensorDebounceActiveField->setObjectName(QStringLiteral("sensorDebounceActiveField"));
        sensorDebounceActiveField->setInputMethodHints(Qt::ImhDigitsOnly);
        sensorDebounceActiveField->setMaxLength(4);

        horizontalLayout_11->addWidget(sensorDebounceActiveField);


        formLayout->setLayout(9, QFormLayout::LabelRole, horizontalLayout_11);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_7->addWidget(label_6);

        trackColorBox = new QComboBox(centralwidget);
        trackColorBox->setObjectName(QStringLiteral("trackColorBox"));

        horizontalLayout_7->addWidget(trackColorBox);


        formLayout->setLayout(11, QFormLayout::SpanningRole, horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_8->addWidget(label_7);

        occupiedColorBox = new QComboBox(centralwidget);
        occupiedColorBox->setObjectName(QStringLiteral("occupiedColorBox"));

        horizontalLayout_8->addWidget(occupiedColorBox);


        formLayout->setLayout(12, QFormLayout::SpanningRole, horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_9->addWidget(label_8);

        extraColorBox = new QComboBox(centralwidget);
        extraColorBox->setObjectName(QStringLiteral("extraColorBox"));

        horizontalLayout_9->addWidget(extraColorBox);


        formLayout->setLayout(13, QFormLayout::SpanningRole, horizontalLayout_9);

        horizontalSpacer_3 = new QSpacerItem(334, 16, QSizePolicy::Expanding, QSizePolicy::Minimum);

        formLayout->setItem(14, QFormLayout::SpanningRole, horizontalSpacer_3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_6->addWidget(label_5);

        memoryNameField = new QLineEdit(centralwidget);
        memoryNameField->setObjectName(QStringLiteral("memoryNameField"));

        horizontalLayout_6->addWidget(memoryNameField);


        formLayout->setLayout(15, QFormLayout::SpanningRole, horizontalLayout_6);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_11 = new QLabel(centralwidget);
        label_11->setObjectName(QStringLiteral("label_11"));

        horizontalLayout_12->addWidget(label_11);

        metricField = new QLineEdit(centralwidget);
        metricField->setObjectName(QStringLiteral("metricField"));
        metricField->setInputMethodHints(Qt::ImhDigitsOnly);
        metricField->setMaxLength(6);

        horizontalLayout_12->addWidget(metricField);


        formLayout->setLayout(16, QFormLayout::SpanningRole, horizontalLayout_12);

        horizontalSpacer_4 = new QSpacerItem(334, 15, QSizePolicy::Expanding, QSizePolicy::Minimum);

        formLayout->setItem(17, QFormLayout::SpanningRole, horizontalSpacer_4);

        permissiveCheck = new QCheckBox(centralwidget);
        permissiveCheck->setObjectName(QStringLiteral("permissiveCheck"));

        formLayout->setWidget(18, QFormLayout::SpanningRole, permissiveCheck);

        horizontalSpacer_5 = new QSpacerItem(334, 16, QSizePolicy::Expanding, QSizePolicy::Minimum);

        formLayout->setItem(19, QFormLayout::SpanningRole, horizontalSpacer_5);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        blockEditDone = new QPushButton(centralwidget);
        blockEditDone->setObjectName(QStringLiteral("blockEditDone"));

        horizontalLayout_5->addWidget(blockEditDone);

        blockEditCancel = new QPushButton(centralwidget);
        blockEditCancel->setObjectName(QStringLiteral("blockEditCancel"));

        horizontalLayout_5->addWidget(blockEditCancel);


        formLayout->setLayout(20, QFormLayout::SpanningRole, horizontalLayout_5);

        senseBox = new QComboBox(centralwidget);
        senseBox->setObjectName(QStringLiteral("senseBox"));

        formLayout->setWidget(4, QFormLayout::FieldRole, senseBox);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        formLayout->setItem(10, QFormLayout::SpanningRole, horizontalSpacer_6);

        CreateEditBlock->setCentralWidget(centralwidget);
        menubar = new QMenuBar(CreateEditBlock);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 357, 25));
        menuWindow = new QMenu(menubar);
        menuWindow->setObjectName(QStringLiteral("menuWindow"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        CreateEditBlock->setMenuBar(menubar);
        statusbar = new QStatusBar(CreateEditBlock);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        CreateEditBlock->setStatusBar(statusbar);

        menubar->addAction(menuWindow->menuAction());
        menubar->addAction(menuHelp->menuAction());

        retranslateUi(CreateEditBlock);

        QMetaObject::connectSlotsByName(CreateEditBlock);
    } // setupUi

    void retranslateUi(QMainWindow *CreateEditBlock)
    {
        CreateEditBlock->setWindowTitle(QApplication::translate("CreateEditBlock", "MainWindow", 0));
        label->setText(QApplication::translate("CreateEditBlock", "Name:", 0));
        blockNameLabel->setText(QApplication::translate("CreateEditBlock", "Block x", 0));
        label_2->setText(QApplication::translate("CreateEditBlock", "Current use count : ", 0));
        blockUseLabel->setText(QApplication::translate("CreateEditBlock", "0", 0));
        label_3->setText(QApplication::translate("CreateEditBlock", "Occupancy Sensor:", 0));
#ifndef QT_NO_TOOLTIP
        sensorNameField->setToolTip(QApplication::translate("CreateEditBlock", "<html><head/><body><p>Enter a sensor number, System name or user name of a sensor. </p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        label_4->setText(QApplication::translate("CreateEditBlock", "Occupied sense:", 0));
        sensorDebounceGlobalCheck->setText(QApplication::translate("CreateEditBlock", "SensorDebounce", 0));
        label_9->setText(QApplication::translate("CreateEditBlock", "Inactive", 0));
        label_10->setText(QApplication::translate("CreateEditBlock", "Active", 0));
        label_6->setText(QApplication::translate("CreateEditBlock", "Track color:", 0));
        trackColorBox->clear();
        trackColorBox->insertItems(0, QStringList()
         << QApplication::translate("CreateEditBlock", "Black", 0)
         << QApplication::translate("CreateEditBlock", "Dark Gray", 0)
         << QApplication::translate("CreateEditBlock", "Gray", 0)
         << QApplication::translate("CreateEditBlock", "Light Gray", 0)
         << QApplication::translate("CreateEditBlock", "White", 0)
         << QApplication::translate("CreateEditBlock", "Red", 0)
         << QApplication::translate("CreateEditBlock", "Pink", 0)
         << QApplication::translate("CreateEditBlock", "Orange", 0)
        );
        label_7->setText(QApplication::translate("CreateEditBlock", "Occupied Track color:", 0));
        occupiedColorBox->clear();
        occupiedColorBox->insertItems(0, QStringList()
         << QApplication::translate("CreateEditBlock", "Black", 0)
         << QApplication::translate("CreateEditBlock", "Dark Gray", 0)
         << QApplication::translate("CreateEditBlock", "Gray", 0)
         << QApplication::translate("CreateEditBlock", "Light Gray", 0)
         << QApplication::translate("CreateEditBlock", "White", 0)
         << QApplication::translate("CreateEditBlock", "Red", 0)
         << QApplication::translate("CreateEditBlock", "Pink", 0)
         << QApplication::translate("CreateEditBlock", "Orange", 0)
        );
        label_8->setText(QApplication::translate("CreateEditBlock", "Alternate track color:", 0));
        extraColorBox->clear();
        extraColorBox->insertItems(0, QStringList()
         << QApplication::translate("CreateEditBlock", "Black", 0)
         << QApplication::translate("CreateEditBlock", "Dark Gray", 0)
         << QApplication::translate("CreateEditBlock", "Gray", 0)
         << QApplication::translate("CreateEditBlock", "Light Gray", 0)
         << QApplication::translate("CreateEditBlock", "White", 0)
         << QApplication::translate("CreateEditBlock", "Red", 0)
         << QApplication::translate("CreateEditBlock", "Pink", 0)
         << QApplication::translate("CreateEditBlock", "Orange", 0)
        );
        label_5->setText(QApplication::translate("CreateEditBlock", "Memory Variable Name: ", 0));
        label_11->setText(QApplication::translate("CreateEditBlock", "Block Metric", 0));
#ifndef QT_NO_TOOLTIP
        metricField->setToolTip(QApplication::translate("CreateEditBlock", "<html><head/><body><p>set the cost for going over this block</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        permissiveCheck->setToolTip(QApplication::translate("CreateEditBlock", "<html><head/><body><p>&quot;Is another train allowed to enter the block when it is already occupied&quot;</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        permissiveCheck->setText(QApplication::translate("CreateEditBlock", "Permissive Working Allowed", 0));
        blockEditDone->setText(QApplication::translate("CreateEditBlock", "Done", 0));
        blockEditCancel->setText(QApplication::translate("CreateEditBlock", "Cancel", 0));
        senseBox->clear();
        senseBox->insertItems(0, QStringList()
         << QApplication::translate("CreateEditBlock", "Active", 0)
         << QApplication::translate("CreateEditBlock", "Inactive", 0)
        );
        menuWindow->setTitle(QApplication::translate("CreateEditBlock", "Window", 0));
        menuHelp->setTitle(QApplication::translate("CreateEditBlock", "Help", 0));
    } // retranslateUi

};

namespace Ui {
    class CreateEditBlock: public Ui_CreateEditBlock {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEEDITBLOCK_H
