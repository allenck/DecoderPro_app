/********************************************************************************
** Form generated from reading UI file 'createeditblock.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEEDITBLOCK_H
#define UI_CREATEEDITBLOCK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
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
            CreateEditBlock->setObjectName(QString::fromUtf8("CreateEditBlock"));
        CreateEditBlock->resize(357, 729);
        centralwidget = new QWidget(CreateEditBlock);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        formLayout = new QFormLayout(centralwidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        blockNameLabel = new QLabel(centralwidget);
        blockNameLabel->setObjectName(QString::fromUtf8("blockNameLabel"));

        horizontalLayout->addWidget(blockNameLabel);


        formLayout->setLayout(0, QFormLayout::LabelRole, horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        blockUseLabel = new QLabel(centralwidget);
        blockUseLabel->setObjectName(QString::fromUtf8("blockUseLabel"));

        horizontalLayout_2->addWidget(blockUseLabel);


        formLayout->setLayout(1, QFormLayout::LabelRole, horizontalLayout_2);

        horizontalSpacer = new QSpacerItem(334, 15, QSizePolicy::Expanding, QSizePolicy::Minimum);

        formLayout->setItem(2, QFormLayout::SpanningRole, horizontalSpacer);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        sensorNameField = new QLineEdit(centralwidget);
        sensorNameField->setObjectName(QString::fromUtf8("sensorNameField"));

        horizontalLayout_3->addWidget(sensorNameField);


        formLayout->setLayout(3, QFormLayout::SpanningRole, horizontalLayout_3);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_4);

        horizontalSpacer_2 = new QSpacerItem(334, 15, QSizePolicy::Expanding, QSizePolicy::Minimum);

        formLayout->setItem(6, QFormLayout::SpanningRole, horizontalSpacer_2);

        sensorDebounceGlobalCheck = new QCheckBox(centralwidget);
        sensorDebounceGlobalCheck->setObjectName(QString::fromUtf8("sensorDebounceGlobalCheck"));

        formLayout->setWidget(7, QFormLayout::LabelRole, sensorDebounceGlobalCheck);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_4->addWidget(label_9);

        sensorDebounceInactiveField = new QLineEdit(centralwidget);
        sensorDebounceInactiveField->setObjectName(QString::fromUtf8("sensorDebounceInactiveField"));
        sensorDebounceInactiveField->setInputMethodHints(Qt::ImhDigitsOnly);
        sensorDebounceInactiveField->setMaxLength(4);

        horizontalLayout_4->addWidget(sensorDebounceInactiveField);


        formLayout->setLayout(8, QFormLayout::LabelRole, horizontalLayout_4);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_10 = new QLabel(centralwidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_11->addWidget(label_10);

        sensorDebounceActiveField = new QLineEdit(centralwidget);
        sensorDebounceActiveField->setObjectName(QString::fromUtf8("sensorDebounceActiveField"));
        sensorDebounceActiveField->setInputMethodHints(Qt::ImhDigitsOnly);
        sensorDebounceActiveField->setMaxLength(4);

        horizontalLayout_11->addWidget(sensorDebounceActiveField);


        formLayout->setLayout(9, QFormLayout::LabelRole, horizontalLayout_11);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_7->addWidget(label_6);

        trackColorBox = new QComboBox(centralwidget);
        trackColorBox->addItem(QString());
        trackColorBox->addItem(QString());
        trackColorBox->addItem(QString());
        trackColorBox->addItem(QString());
        trackColorBox->addItem(QString());
        trackColorBox->addItem(QString());
        trackColorBox->addItem(QString());
        trackColorBox->addItem(QString());
        trackColorBox->setObjectName(QString::fromUtf8("trackColorBox"));

        horizontalLayout_7->addWidget(trackColorBox);


        formLayout->setLayout(11, QFormLayout::SpanningRole, horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_8->addWidget(label_7);

        occupiedColorBox = new QComboBox(centralwidget);
        occupiedColorBox->addItem(QString());
        occupiedColorBox->addItem(QString());
        occupiedColorBox->addItem(QString());
        occupiedColorBox->addItem(QString());
        occupiedColorBox->addItem(QString());
        occupiedColorBox->addItem(QString());
        occupiedColorBox->addItem(QString());
        occupiedColorBox->addItem(QString());
        occupiedColorBox->setObjectName(QString::fromUtf8("occupiedColorBox"));

        horizontalLayout_8->addWidget(occupiedColorBox);


        formLayout->setLayout(12, QFormLayout::SpanningRole, horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_9->addWidget(label_8);

        extraColorBox = new QComboBox(centralwidget);
        extraColorBox->addItem(QString());
        extraColorBox->addItem(QString());
        extraColorBox->addItem(QString());
        extraColorBox->addItem(QString());
        extraColorBox->addItem(QString());
        extraColorBox->addItem(QString());
        extraColorBox->addItem(QString());
        extraColorBox->addItem(QString());
        extraColorBox->setObjectName(QString::fromUtf8("extraColorBox"));

        horizontalLayout_9->addWidget(extraColorBox);


        formLayout->setLayout(13, QFormLayout::SpanningRole, horizontalLayout_9);

        horizontalSpacer_3 = new QSpacerItem(334, 16, QSizePolicy::Expanding, QSizePolicy::Minimum);

        formLayout->setItem(14, QFormLayout::SpanningRole, horizontalSpacer_3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_6->addWidget(label_5);

        memoryNameField = new QLineEdit(centralwidget);
        memoryNameField->setObjectName(QString::fromUtf8("memoryNameField"));

        horizontalLayout_6->addWidget(memoryNameField);


        formLayout->setLayout(15, QFormLayout::SpanningRole, horizontalLayout_6);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_11 = new QLabel(centralwidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_12->addWidget(label_11);

        metricField = new QLineEdit(centralwidget);
        metricField->setObjectName(QString::fromUtf8("metricField"));
        metricField->setInputMethodHints(Qt::ImhDigitsOnly);
        metricField->setMaxLength(6);

        horizontalLayout_12->addWidget(metricField);


        formLayout->setLayout(16, QFormLayout::SpanningRole, horizontalLayout_12);

        horizontalSpacer_4 = new QSpacerItem(334, 15, QSizePolicy::Expanding, QSizePolicy::Minimum);

        formLayout->setItem(17, QFormLayout::SpanningRole, horizontalSpacer_4);

        permissiveCheck = new QCheckBox(centralwidget);
        permissiveCheck->setObjectName(QString::fromUtf8("permissiveCheck"));

        formLayout->setWidget(18, QFormLayout::SpanningRole, permissiveCheck);

        horizontalSpacer_5 = new QSpacerItem(334, 16, QSizePolicy::Expanding, QSizePolicy::Minimum);

        formLayout->setItem(19, QFormLayout::SpanningRole, horizontalSpacer_5);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        blockEditDone = new QPushButton(centralwidget);
        blockEditDone->setObjectName(QString::fromUtf8("blockEditDone"));

        horizontalLayout_5->addWidget(blockEditDone);

        blockEditCancel = new QPushButton(centralwidget);
        blockEditCancel->setObjectName(QString::fromUtf8("blockEditCancel"));

        horizontalLayout_5->addWidget(blockEditCancel);


        formLayout->setLayout(20, QFormLayout::SpanningRole, horizontalLayout_5);

        senseBox = new QComboBox(centralwidget);
        senseBox->addItem(QString());
        senseBox->addItem(QString());
        senseBox->setObjectName(QString::fromUtf8("senseBox"));

        formLayout->setWidget(4, QFormLayout::FieldRole, senseBox);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        formLayout->setItem(10, QFormLayout::SpanningRole, horizontalSpacer_6);

        CreateEditBlock->setCentralWidget(centralwidget);
        menubar = new QMenuBar(CreateEditBlock);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 357, 25));
        menuWindow = new QMenu(menubar);
        menuWindow->setObjectName(QString::fromUtf8("menuWindow"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        CreateEditBlock->setMenuBar(menubar);
        statusbar = new QStatusBar(CreateEditBlock);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        CreateEditBlock->setStatusBar(statusbar);

        menubar->addAction(menuWindow->menuAction());
        menubar->addAction(menuHelp->menuAction());

        retranslateUi(CreateEditBlock);

        QMetaObject::connectSlotsByName(CreateEditBlock);
    } // setupUi

    void retranslateUi(QMainWindow *CreateEditBlock)
    {
        CreateEditBlock->setWindowTitle(QCoreApplication::translate("CreateEditBlock", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("CreateEditBlock", "Name:", nullptr));
        blockNameLabel->setText(QCoreApplication::translate("CreateEditBlock", "Block x", nullptr));
        label_2->setText(QCoreApplication::translate("CreateEditBlock", "Current use count : ", nullptr));
        blockUseLabel->setText(QCoreApplication::translate("CreateEditBlock", "0", nullptr));
        label_3->setText(QCoreApplication::translate("CreateEditBlock", "Occupancy Sensor:", nullptr));
#if QT_CONFIG(tooltip)
        sensorNameField->setToolTip(QCoreApplication::translate("CreateEditBlock", "<html><head/><body><p>Enter a sensor number, System name or user name of a sensor. </p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_4->setText(QCoreApplication::translate("CreateEditBlock", "Occupied sense:", nullptr));
        sensorDebounceGlobalCheck->setText(QCoreApplication::translate("CreateEditBlock", "SensorDebounce", nullptr));
        label_9->setText(QCoreApplication::translate("CreateEditBlock", "Inactive", nullptr));
        label_10->setText(QCoreApplication::translate("CreateEditBlock", "Active", nullptr));
        label_6->setText(QCoreApplication::translate("CreateEditBlock", "Track color:", nullptr));
        trackColorBox->setItemText(0, QCoreApplication::translate("CreateEditBlock", "Black", nullptr));
        trackColorBox->setItemText(1, QCoreApplication::translate("CreateEditBlock", "Dark Gray", nullptr));
        trackColorBox->setItemText(2, QCoreApplication::translate("CreateEditBlock", "Gray", nullptr));
        trackColorBox->setItemText(3, QCoreApplication::translate("CreateEditBlock", "Light Gray", nullptr));
        trackColorBox->setItemText(4, QCoreApplication::translate("CreateEditBlock", "White", nullptr));
        trackColorBox->setItemText(5, QCoreApplication::translate("CreateEditBlock", "Red", nullptr));
        trackColorBox->setItemText(6, QCoreApplication::translate("CreateEditBlock", "Pink", nullptr));
        trackColorBox->setItemText(7, QCoreApplication::translate("CreateEditBlock", "Orange", nullptr));

        label_7->setText(QCoreApplication::translate("CreateEditBlock", "Occupied Track color:", nullptr));
        occupiedColorBox->setItemText(0, QCoreApplication::translate("CreateEditBlock", "Black", nullptr));
        occupiedColorBox->setItemText(1, QCoreApplication::translate("CreateEditBlock", "Dark Gray", nullptr));
        occupiedColorBox->setItemText(2, QCoreApplication::translate("CreateEditBlock", "Gray", nullptr));
        occupiedColorBox->setItemText(3, QCoreApplication::translate("CreateEditBlock", "Light Gray", nullptr));
        occupiedColorBox->setItemText(4, QCoreApplication::translate("CreateEditBlock", "White", nullptr));
        occupiedColorBox->setItemText(5, QCoreApplication::translate("CreateEditBlock", "Red", nullptr));
        occupiedColorBox->setItemText(6, QCoreApplication::translate("CreateEditBlock", "Pink", nullptr));
        occupiedColorBox->setItemText(7, QCoreApplication::translate("CreateEditBlock", "Orange", nullptr));

        label_8->setText(QCoreApplication::translate("CreateEditBlock", "Alternate track color:", nullptr));
        extraColorBox->setItemText(0, QCoreApplication::translate("CreateEditBlock", "Black", nullptr));
        extraColorBox->setItemText(1, QCoreApplication::translate("CreateEditBlock", "Dark Gray", nullptr));
        extraColorBox->setItemText(2, QCoreApplication::translate("CreateEditBlock", "Gray", nullptr));
        extraColorBox->setItemText(3, QCoreApplication::translate("CreateEditBlock", "Light Gray", nullptr));
        extraColorBox->setItemText(4, QCoreApplication::translate("CreateEditBlock", "White", nullptr));
        extraColorBox->setItemText(5, QCoreApplication::translate("CreateEditBlock", "Red", nullptr));
        extraColorBox->setItemText(6, QCoreApplication::translate("CreateEditBlock", "Pink", nullptr));
        extraColorBox->setItemText(7, QCoreApplication::translate("CreateEditBlock", "Orange", nullptr));

        label_5->setText(QCoreApplication::translate("CreateEditBlock", "Memory Variable Name: ", nullptr));
        label_11->setText(QCoreApplication::translate("CreateEditBlock", "Block Metric", nullptr));
#if QT_CONFIG(tooltip)
        metricField->setToolTip(QCoreApplication::translate("CreateEditBlock", "<html><head/><body><p>set the cost for going over this block</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        permissiveCheck->setToolTip(QCoreApplication::translate("CreateEditBlock", "<html><head/><body><p>&quot;Is another train allowed to enter the block when it is already occupied&quot;</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        permissiveCheck->setText(QCoreApplication::translate("CreateEditBlock", "Permissive Working Allowed", nullptr));
        blockEditDone->setText(QCoreApplication::translate("CreateEditBlock", "Done", nullptr));
        blockEditCancel->setText(QCoreApplication::translate("CreateEditBlock", "Cancel", nullptr));
        senseBox->setItemText(0, QCoreApplication::translate("CreateEditBlock", "Active", nullptr));
        senseBox->setItemText(1, QCoreApplication::translate("CreateEditBlock", "Inactive", nullptr));

        menuWindow->setTitle(QCoreApplication::translate("CreateEditBlock", "Window", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("CreateEditBlock", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateEditBlock: public Ui_CreateEditBlock {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEEDITBLOCK_H
