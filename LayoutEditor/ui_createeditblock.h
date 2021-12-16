/********************************************************************************
** Form generated from reading UI file 'createeditblock.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
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
            CreateEditBlock->setObjectName(QLatin1String("CreateEditBlock"));
        CreateEditBlock->resize(357, 729);
        centralwidget = new QWidget(CreateEditBlock);
        centralwidget->setObjectName(QLatin1String("centralwidget"));
        formLayout = new QFormLayout(centralwidget);
        formLayout->setObjectName(QLatin1String("formLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QLatin1String("horizontalLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QLatin1String("label"));

        horizontalLayout->addWidget(label);

        blockNameLabel = new QLabel(centralwidget);
        blockNameLabel->setObjectName(QLatin1String("blockNameLabel"));

        horizontalLayout->addWidget(blockNameLabel);


        formLayout->setLayout(0, QFormLayout::LabelRole, horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QLatin1String("horizontalLayout_2"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QLatin1String("label_2"));

        horizontalLayout_2->addWidget(label_2);

        blockUseLabel = new QLabel(centralwidget);
        blockUseLabel->setObjectName(QLatin1String("blockUseLabel"));

        horizontalLayout_2->addWidget(blockUseLabel);


        formLayout->setLayout(1, QFormLayout::LabelRole, horizontalLayout_2);

        horizontalSpacer = new QSpacerItem(334, 15, QSizePolicy::Expanding, QSizePolicy::Minimum);

        formLayout->setItem(2, QFormLayout::SpanningRole, horizontalSpacer);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QLatin1String("horizontalLayout_3"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QLatin1String("label_3"));

        horizontalLayout_3->addWidget(label_3);

        sensorNameField = new QLineEdit(centralwidget);
        sensorNameField->setObjectName(QLatin1String("sensorNameField"));

        horizontalLayout_3->addWidget(sensorNameField);


        formLayout->setLayout(3, QFormLayout::SpanningRole, horizontalLayout_3);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QLatin1String("label_4"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_4);

        horizontalSpacer_2 = new QSpacerItem(334, 15, QSizePolicy::Expanding, QSizePolicy::Minimum);

        formLayout->setItem(6, QFormLayout::SpanningRole, horizontalSpacer_2);

        sensorDebounceGlobalCheck = new QCheckBox(centralwidget);
        sensorDebounceGlobalCheck->setObjectName(QLatin1String("sensorDebounceGlobalCheck"));

        formLayout->setWidget(7, QFormLayout::LabelRole, sensorDebounceGlobalCheck);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QLatin1String("horizontalLayout_4"));
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName(QLatin1String("label_9"));

        horizontalLayout_4->addWidget(label_9);

        sensorDebounceInactiveField = new QLineEdit(centralwidget);
        sensorDebounceInactiveField->setObjectName(QLatin1String("sensorDebounceInactiveField"));
        sensorDebounceInactiveField->setInputMethodHints(Qt::ImhDigitsOnly);
        sensorDebounceInactiveField->setMaxLength(4);

        horizontalLayout_4->addWidget(sensorDebounceInactiveField);


        formLayout->setLayout(8, QFormLayout::LabelRole, horizontalLayout_4);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QLatin1String("horizontalLayout_11"));
        label_10 = new QLabel(centralwidget);
        label_10->setObjectName(QLatin1String("label_10"));

        horizontalLayout_11->addWidget(label_10);

        sensorDebounceActiveField = new QLineEdit(centralwidget);
        sensorDebounceActiveField->setObjectName(QLatin1String("sensorDebounceActiveField"));
        sensorDebounceActiveField->setInputMethodHints(Qt::ImhDigitsOnly);
        sensorDebounceActiveField->setMaxLength(4);

        horizontalLayout_11->addWidget(sensorDebounceActiveField);


        formLayout->setLayout(9, QFormLayout::LabelRole, horizontalLayout_11);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QLatin1String("horizontalLayout_7"));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QLatin1String("label_6"));

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
        trackColorBox->setObjectName(QLatin1String("trackColorBox"));

        horizontalLayout_7->addWidget(trackColorBox);


        formLayout->setLayout(11, QFormLayout::SpanningRole, horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QLatin1String("horizontalLayout_8"));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QLatin1String("label_7"));

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
        occupiedColorBox->setObjectName(QLatin1String("occupiedColorBox"));

        horizontalLayout_8->addWidget(occupiedColorBox);


        formLayout->setLayout(12, QFormLayout::SpanningRole, horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QLatin1String("horizontalLayout_9"));
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QLatin1String("label_8"));

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
        extraColorBox->setObjectName(QLatin1String("extraColorBox"));

        horizontalLayout_9->addWidget(extraColorBox);


        formLayout->setLayout(13, QFormLayout::SpanningRole, horizontalLayout_9);

        horizontalSpacer_3 = new QSpacerItem(334, 16, QSizePolicy::Expanding, QSizePolicy::Minimum);

        formLayout->setItem(14, QFormLayout::SpanningRole, horizontalSpacer_3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QLatin1String("horizontalLayout_6"));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QLatin1String("label_5"));

        horizontalLayout_6->addWidget(label_5);

        memoryNameField = new QLineEdit(centralwidget);
        memoryNameField->setObjectName(QLatin1String("memoryNameField"));

        horizontalLayout_6->addWidget(memoryNameField);


        formLayout->setLayout(15, QFormLayout::SpanningRole, horizontalLayout_6);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QLatin1String("horizontalLayout_12"));
        label_11 = new QLabel(centralwidget);
        label_11->setObjectName(QLatin1String("label_11"));

        horizontalLayout_12->addWidget(label_11);

        metricField = new QLineEdit(centralwidget);
        metricField->setObjectName(QLatin1String("metricField"));
        metricField->setInputMethodHints(Qt::ImhDigitsOnly);
        metricField->setMaxLength(6);

        horizontalLayout_12->addWidget(metricField);


        formLayout->setLayout(16, QFormLayout::SpanningRole, horizontalLayout_12);

        horizontalSpacer_4 = new QSpacerItem(334, 15, QSizePolicy::Expanding, QSizePolicy::Minimum);

        formLayout->setItem(17, QFormLayout::SpanningRole, horizontalSpacer_4);

        permissiveCheck = new QCheckBox(centralwidget);
        permissiveCheck->setObjectName(QLatin1String("permissiveCheck"));

        formLayout->setWidget(18, QFormLayout::SpanningRole, permissiveCheck);

        horizontalSpacer_5 = new QSpacerItem(334, 16, QSizePolicy::Expanding, QSizePolicy::Minimum);

        formLayout->setItem(19, QFormLayout::SpanningRole, horizontalSpacer_5);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QLatin1String("horizontalLayout_5"));
        blockEditDone = new QPushButton(centralwidget);
        blockEditDone->setObjectName(QLatin1String("blockEditDone"));

        horizontalLayout_5->addWidget(blockEditDone);

        blockEditCancel = new QPushButton(centralwidget);
        blockEditCancel->setObjectName(QLatin1String("blockEditCancel"));

        horizontalLayout_5->addWidget(blockEditCancel);


        formLayout->setLayout(20, QFormLayout::SpanningRole, horizontalLayout_5);

        senseBox = new QComboBox(centralwidget);
        senseBox->addItem(QString());
        senseBox->addItem(QString());
        senseBox->setObjectName(QLatin1String("senseBox"));

        formLayout->setWidget(4, QFormLayout::FieldRole, senseBox);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        formLayout->setItem(10, QFormLayout::SpanningRole, horizontalSpacer_6);

        CreateEditBlock->setCentralWidget(centralwidget);
        menubar = new QMenuBar(CreateEditBlock);
        menubar->setObjectName(QLatin1String("menubar"));
        menubar->setGeometry(QRect(0, 0, 357, 25));
        menuWindow = new QMenu(menubar);
        menuWindow->setObjectName(QLatin1String("menuWindow"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QLatin1String("menuHelp"));
        CreateEditBlock->setMenuBar(menubar);
        statusbar = new QStatusBar(CreateEditBlock);
        statusbar->setObjectName(QLatin1String("statusbar"));
        CreateEditBlock->setStatusBar(statusbar);

        menubar->addAction(menuWindow->menuAction());
        menubar->addAction(menuHelp->menuAction());

        retranslateUi(CreateEditBlock);

        QMetaObject::connectSlotsByName(CreateEditBlock);
    } // setupUi

    void retranslateUi(QMainWindow *CreateEditBlock)
    {
        CreateEditBlock->setWindowTitle(QApplication::translate("CreateEditBlock", "MainWindow", nullptr));
        label->setText(QApplication::translate("CreateEditBlock", "Name:", nullptr));
        blockNameLabel->setText(QApplication::translate("CreateEditBlock", "Block x", nullptr));
        label_2->setText(QApplication::translate("CreateEditBlock", "Current use count : ", nullptr));
        blockUseLabel->setText(QApplication::translate("CreateEditBlock", "0", nullptr));
        label_3->setText(QApplication::translate("CreateEditBlock", "Occupancy Sensor:", nullptr));
#ifndef QT_NO_TOOLTIP
        sensorNameField->setToolTip(QApplication::translate("CreateEditBlock", "<html><head/><body><p>Enter a sensor number, System name or user name of a sensor. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        label_4->setText(QApplication::translate("CreateEditBlock", "Occupied sense:", nullptr));
        sensorDebounceGlobalCheck->setText(QApplication::translate("CreateEditBlock", "SensorDebounce", nullptr));
        label_9->setText(QApplication::translate("CreateEditBlock", "Inactive", nullptr));
        label_10->setText(QApplication::translate("CreateEditBlock", "Active", nullptr));
        label_6->setText(QApplication::translate("CreateEditBlock", "Track color:", nullptr));
        trackColorBox->setItemText(0, QApplication::translate("CreateEditBlock", "Black", nullptr));
        trackColorBox->setItemText(1, QApplication::translate("CreateEditBlock", "Dark Gray", nullptr));
        trackColorBox->setItemText(2, QApplication::translate("CreateEditBlock", "Gray", nullptr));
        trackColorBox->setItemText(3, QApplication::translate("CreateEditBlock", "Light Gray", nullptr));
        trackColorBox->setItemText(4, QApplication::translate("CreateEditBlock", "White", nullptr));
        trackColorBox->setItemText(5, QApplication::translate("CreateEditBlock", "Red", nullptr));
        trackColorBox->setItemText(6, QApplication::translate("CreateEditBlock", "Pink", nullptr));
        trackColorBox->setItemText(7, QApplication::translate("CreateEditBlock", "Orange", nullptr));

        label_7->setText(QApplication::translate("CreateEditBlock", "Occupied Track color:", nullptr));
        occupiedColorBox->setItemText(0, QApplication::translate("CreateEditBlock", "Black", nullptr));
        occupiedColorBox->setItemText(1, QApplication::translate("CreateEditBlock", "Dark Gray", nullptr));
        occupiedColorBox->setItemText(2, QApplication::translate("CreateEditBlock", "Gray", nullptr));
        occupiedColorBox->setItemText(3, QApplication::translate("CreateEditBlock", "Light Gray", nullptr));
        occupiedColorBox->setItemText(4, QApplication::translate("CreateEditBlock", "White", nullptr));
        occupiedColorBox->setItemText(5, QApplication::translate("CreateEditBlock", "Red", nullptr));
        occupiedColorBox->setItemText(6, QApplication::translate("CreateEditBlock", "Pink", nullptr));
        occupiedColorBox->setItemText(7, QApplication::translate("CreateEditBlock", "Orange", nullptr));

        label_8->setText(QApplication::translate("CreateEditBlock", "Alternate track color:", nullptr));
        extraColorBox->setItemText(0, QApplication::translate("CreateEditBlock", "Black", nullptr));
        extraColorBox->setItemText(1, QApplication::translate("CreateEditBlock", "Dark Gray", nullptr));
        extraColorBox->setItemText(2, QApplication::translate("CreateEditBlock", "Gray", nullptr));
        extraColorBox->setItemText(3, QApplication::translate("CreateEditBlock", "Light Gray", nullptr));
        extraColorBox->setItemText(4, QApplication::translate("CreateEditBlock", "White", nullptr));
        extraColorBox->setItemText(5, QApplication::translate("CreateEditBlock", "Red", nullptr));
        extraColorBox->setItemText(6, QApplication::translate("CreateEditBlock", "Pink", nullptr));
        extraColorBox->setItemText(7, QApplication::translate("CreateEditBlock", "Orange", nullptr));

        label_5->setText(QApplication::translate("CreateEditBlock", "Memory Variable Name: ", nullptr));
        label_11->setText(QApplication::translate("CreateEditBlock", "Block Metric", nullptr));
#ifndef QT_NO_TOOLTIP
        metricField->setToolTip(QApplication::translate("CreateEditBlock", "<html><head/><body><p>set the cost for going over this block</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        permissiveCheck->setToolTip(QApplication::translate("CreateEditBlock", "<html><head/><body><p>&quot;Is another train allowed to enter the block when it is already occupied&quot;</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        permissiveCheck->setText(QApplication::translate("CreateEditBlock", "Permissive Working Allowed", nullptr));
        blockEditDone->setText(QApplication::translate("CreateEditBlock", "Done", nullptr));
        blockEditCancel->setText(QApplication::translate("CreateEditBlock", "Cancel", nullptr));
        senseBox->setItemText(0, QApplication::translate("CreateEditBlock", "Active", nullptr));
        senseBox->setItemText(1, QApplication::translate("CreateEditBlock", "Inactive", nullptr));

        menuWindow->setTitle(QApplication::translate("CreateEditBlock", "Window", nullptr));
        menuHelp->setTitle(QApplication::translate("CreateEditBlock", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateEditBlock: public Ui_CreateEditBlock {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEEDITBLOCK_H
