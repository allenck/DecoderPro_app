/********************************************************************************
** Form generated from reading UI file 'routetableaction.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROUTETABLEACTION_H
#define UI_ROUTETABLEACTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "jmribeancombobox.h"
#include "jtextfield.h"

QT_BEGIN_NAMESPACE

class Ui_addFrame
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_systemName;
    QLabel *label;
    JTextField *_systemName;
    QLabel *fixedSystemName;
    QCheckBox *_autoSystemName;
    QHBoxLayout *horizontalLayout_userName;
    QLabel *label_2;
    JTextField *_userName;
    QHBoxLayout *horizontalLayout_show;
    QLabel *label_3;
    QRadioButton *allButton;
    QRadioButton *includedButton;
    QLabel *label_4;
    QHBoxLayout *p2xt;
    QLabel *p2xtSpace;
    QVBoxLayout *verticalLayout;
    QLabel *label_9;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QTableView *routeTurnoutTable;
    QHBoxLayout *p2xs;
    QLabel *p2xsSpace;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QTableView *routeSensorTable;
    QHBoxLayout *horizontalLayout_sound_script;
    QLabel *label_15;
    QPushButton *setSound;
    JTextField *soundFile;
    QLabel *label_16;
    QPushButton *setScript;
    JTextField *scriptFile;
    QLabel *sensorThatActivates;
    QHBoxLayout *p31;
    JmriBeanComboBox *turnoutsAlignedSensor;
    QFrame *ps;
    QVBoxLayout *verticalLayout_3;
    QLabel *sensorsThatTrigger;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_19;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_8;
    QHBoxLayout *horizontalLayout_7;
    JmriBeanComboBox *sensor1;
    QComboBox *sensor1mode;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout_9;
    QHBoxLayout *horizontalLayout_11;
    JmriBeanComboBox *sensor2;
    QComboBox *sensor2mode;
    QFrame *frame_4;
    QHBoxLayout *horizontalLayout_12;
    QHBoxLayout *horizontalLayout_13;
    JmriBeanComboBox *sensor3;
    QComboBox *sensor3mode;
    QLabel *label_20;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_21;
    JmriBeanComboBox *cTurnout;
    QLabel *label_22;
    QComboBox *cTurnoutStateBox;
    QHBoxLayout *horizontalLayout;
    QLabel *label_23;
    JTextField *timeDelay;
    QFrame *frame;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_17;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_18;
    JmriBeanComboBox *cLockTurnout;
    QLabel *label_24;
    QComboBox *cLockTurnoutStateBox;
    QVBoxLayout *verticalLayout_5;
    QLabel *status1;
    QLabel *status2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *createButton;
    QPushButton *editButton;
    QPushButton *deleteButton;
    QPushButton *updateButton;
    QPushButton *cancelButton;
    QPushButton *exportBUtton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *addFrame)
    {
        if (addFrame->objectName().isEmpty())
            addFrame->setObjectName(QStringLiteral("addFrame"));
        addFrame->resize(617, 886);
        QFont font;
        font.setPointSize(9);
        addFrame->setFont(font);
        centralWidget = new QWidget(addFrame);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_6 = new QVBoxLayout(centralWidget);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        horizontalLayout_systemName = new QHBoxLayout();
        horizontalLayout_systemName->setObjectName(QStringLiteral("horizontalLayout_systemName"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_systemName->addWidget(label);

        _systemName = new JTextField(centralWidget);
        _systemName->setObjectName(QStringLiteral("_systemName"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(_systemName->sizePolicy().hasHeightForWidth());
        _systemName->setSizePolicy(sizePolicy);
        _systemName->setMaximumSize(QSize(80, 16777215));
        _systemName->setMaxLength(12);

        horizontalLayout_systemName->addWidget(_systemName);

        fixedSystemName = new QLabel(centralWidget);
        fixedSystemName->setObjectName(QStringLiteral("fixedSystemName"));

        horizontalLayout_systemName->addWidget(fixedSystemName);

        _autoSystemName = new QCheckBox(centralWidget);
        _autoSystemName->setObjectName(QStringLiteral("_autoSystemName"));

        horizontalLayout_systemName->addWidget(_autoSystemName);


        verticalLayout_6->addLayout(horizontalLayout_systemName);

        horizontalLayout_userName = new QHBoxLayout();
        horizontalLayout_userName->setObjectName(QStringLiteral("horizontalLayout_userName"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_userName->addWidget(label_2);

        _userName = new JTextField(centralWidget);
        _userName->setObjectName(QStringLiteral("_userName"));
        sizePolicy.setHeightForWidth(_userName->sizePolicy().hasHeightForWidth());
        _userName->setSizePolicy(sizePolicy);
        _userName->setMaximumSize(QSize(150, 16777215));
        _userName->setMaxLength(22);

        horizontalLayout_userName->addWidget(_userName);


        verticalLayout_6->addLayout(horizontalLayout_userName);

        horizontalLayout_show = new QHBoxLayout();
        horizontalLayout_show->setObjectName(QStringLiteral("horizontalLayout_show"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_show->addWidget(label_3);

        allButton = new QRadioButton(centralWidget);
        allButton->setObjectName(QStringLiteral("allButton"));

        horizontalLayout_show->addWidget(allButton);

        includedButton = new QRadioButton(centralWidget);
        includedButton->setObjectName(QStringLiteral("includedButton"));

        horizontalLayout_show->addWidget(includedButton);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_show->addWidget(label_4);


        verticalLayout_6->addLayout(horizontalLayout_show);

        p2xt = new QHBoxLayout();
        p2xt->setObjectName(QStringLiteral("p2xt"));
        p2xtSpace = new QLabel(centralWidget);
        p2xtSpace->setObjectName(QStringLiteral("p2xtSpace"));

        p2xt->addWidget(p2xtSpace);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));

        verticalLayout->addWidget(label_9);

        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout->addWidget(label_5);

        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout->addWidget(label_6);

        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        verticalLayout->addWidget(label_7);

        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setFont(font);

        verticalLayout->addWidget(label_8);


        p2xt->addLayout(verticalLayout);

        routeTurnoutTable = new QTableView(centralWidget);
        routeTurnoutTable->setObjectName(QStringLiteral("routeTurnoutTable"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(routeTurnoutTable->sizePolicy().hasHeightForWidth());
        routeTurnoutTable->setSizePolicy(sizePolicy1);

        p2xt->addWidget(routeTurnoutTable);


        verticalLayout_6->addLayout(p2xt);

        p2xs = new QHBoxLayout();
        p2xs->setObjectName(QStringLiteral("p2xs"));
        p2xsSpace = new QLabel(centralWidget);
        p2xsSpace->setObjectName(QStringLiteral("p2xsSpace"));

        p2xs->addWidget(p2xsSpace);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QStringLiteral("label_10"));

        verticalLayout_2->addWidget(label_10);

        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QStringLiteral("label_11"));

        verticalLayout_2->addWidget(label_11);

        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QStringLiteral("label_12"));

        verticalLayout_2->addWidget(label_12);

        label_13 = new QLabel(centralWidget);
        label_13->setObjectName(QStringLiteral("label_13"));

        verticalLayout_2->addWidget(label_13);

        label_14 = new QLabel(centralWidget);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setFont(font);

        verticalLayout_2->addWidget(label_14);


        p2xs->addLayout(verticalLayout_2);

        routeSensorTable = new QTableView(centralWidget);
        routeSensorTable->setObjectName(QStringLiteral("routeSensorTable"));
        sizePolicy1.setHeightForWidth(routeSensorTable->sizePolicy().hasHeightForWidth());
        routeSensorTable->setSizePolicy(sizePolicy1);

        p2xs->addWidget(routeSensorTable);


        verticalLayout_6->addLayout(p2xs);

        horizontalLayout_sound_script = new QHBoxLayout();
        horizontalLayout_sound_script->setObjectName(QStringLiteral("horizontalLayout_sound_script"));
        label_15 = new QLabel(centralWidget);
        label_15->setObjectName(QStringLiteral("label_15"));

        horizontalLayout_sound_script->addWidget(label_15);

        setSound = new QPushButton(centralWidget);
        setSound->setObjectName(QStringLiteral("setSound"));

        horizontalLayout_sound_script->addWidget(setSound);

        soundFile = new JTextField(centralWidget);
        soundFile->setObjectName(QStringLiteral("soundFile"));
        soundFile->setMaxLength(20);

        horizontalLayout_sound_script->addWidget(soundFile);

        label_16 = new QLabel(centralWidget);
        label_16->setObjectName(QStringLiteral("label_16"));

        horizontalLayout_sound_script->addWidget(label_16);

        setScript = new QPushButton(centralWidget);
        setScript->setObjectName(QStringLiteral("setScript"));

        horizontalLayout_sound_script->addWidget(setScript);

        scriptFile = new JTextField(centralWidget);
        scriptFile->setObjectName(QStringLiteral("scriptFile"));
        scriptFile->setMaxLength(20);

        horizontalLayout_sound_script->addWidget(scriptFile);


        verticalLayout_6->addLayout(horizontalLayout_sound_script);

        sensorThatActivates = new QLabel(centralWidget);
        sensorThatActivates->setObjectName(QStringLiteral("sensorThatActivates"));

        verticalLayout_6->addWidget(sensorThatActivates);

        p31 = new QHBoxLayout();
        p31->setObjectName(QStringLiteral("p31"));
        turnoutsAlignedSensor = new JmriBeanComboBox(centralWidget);
        turnoutsAlignedSensor->setObjectName(QStringLiteral("turnoutsAlignedSensor"));
        turnoutsAlignedSensor->setMaximumSize(QSize(100, 16777215));

        p31->addWidget(turnoutsAlignedSensor);


        verticalLayout_6->addLayout(p31);

        ps = new QFrame(centralWidget);
        ps->setObjectName(QStringLiteral("ps"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(ps->sizePolicy().hasHeightForWidth());
        ps->setSizePolicy(sizePolicy2);
        ps->setFrameShape(QFrame::Box);
        ps->setFrameShadow(QFrame::Raised);
        ps->setLineWidth(2);
        verticalLayout_3 = new QVBoxLayout(ps);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        sensorsThatTrigger = new QLabel(ps);
        sensorsThatTrigger->setObjectName(QStringLiteral("sensorsThatTrigger"));

        verticalLayout_3->addWidget(sensorsThatTrigger);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_19 = new QLabel(ps);
        label_19->setObjectName(QStringLiteral("label_19"));

        horizontalLayout_4->addWidget(label_19);

        frame_2 = new QFrame(ps);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_8 = new QHBoxLayout(frame_2);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        sensor1 = new JmriBeanComboBox(frame_2);
        sensor1->setObjectName(QStringLiteral("sensor1"));

        horizontalLayout_7->addWidget(sensor1);

        sensor1mode = new QComboBox(frame_2);
        sensor1mode->setObjectName(QStringLiteral("sensor1mode"));

        horizontalLayout_7->addWidget(sensor1mode);


        horizontalLayout_8->addLayout(horizontalLayout_7);


        horizontalLayout_4->addWidget(frame_2);

        frame_3 = new QFrame(ps);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        horizontalLayout_9 = new QHBoxLayout(frame_3);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        sensor2 = new JmriBeanComboBox(frame_3);
        sensor2->setObjectName(QStringLiteral("sensor2"));

        horizontalLayout_11->addWidget(sensor2);

        sensor2mode = new QComboBox(frame_3);
        sensor2mode->setObjectName(QStringLiteral("sensor2mode"));

        horizontalLayout_11->addWidget(sensor2mode);


        horizontalLayout_9->addLayout(horizontalLayout_11);


        horizontalLayout_4->addWidget(frame_3);

        frame_4 = new QFrame(ps);
        frame_4->setObjectName(QStringLiteral("frame_4"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        horizontalLayout_12 = new QHBoxLayout(frame_4);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        sensor3 = new JmriBeanComboBox(frame_4);
        sensor3->setObjectName(QStringLiteral("sensor3"));

        horizontalLayout_13->addWidget(sensor3);

        sensor3mode = new QComboBox(frame_4);
        sensor3mode->setObjectName(QStringLiteral("sensor3mode"));

        horizontalLayout_13->addWidget(sensor3mode);


        horizontalLayout_12->addLayout(horizontalLayout_13);


        horizontalLayout_4->addWidget(frame_4);


        verticalLayout_3->addLayout(horizontalLayout_4);

        label_20 = new QLabel(ps);
        label_20->setObjectName(QStringLiteral("label_20"));

        verticalLayout_3->addWidget(label_20);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_21 = new QLabel(ps);
        label_21->setObjectName(QStringLiteral("label_21"));

        horizontalLayout_10->addWidget(label_21);

        cTurnout = new JmriBeanComboBox(ps);
        cTurnout->setObjectName(QStringLiteral("cTurnout"));

        horizontalLayout_10->addWidget(cTurnout);

        label_22 = new QLabel(ps);
        label_22->setObjectName(QStringLiteral("label_22"));

        horizontalLayout_10->addWidget(label_22);

        cTurnoutStateBox = new QComboBox(ps);
        cTurnoutStateBox->setObjectName(QStringLiteral("cTurnoutStateBox"));

        horizontalLayout_10->addWidget(cTurnoutStateBox);


        verticalLayout_3->addLayout(horizontalLayout_10);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_23 = new QLabel(ps);
        label_23->setObjectName(QStringLiteral("label_23"));

        horizontalLayout->addWidget(label_23);

        timeDelay = new JTextField(ps);
        timeDelay->setObjectName(QStringLiteral("timeDelay"));
        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(timeDelay->sizePolicy().hasHeightForWidth());
        timeDelay->setSizePolicy(sizePolicy3);
        timeDelay->setMaximumSize(QSize(50, 16777215));
        timeDelay->setMaxLength(5);
        timeDelay->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(timeDelay);


        verticalLayout_3->addLayout(horizontalLayout);


        verticalLayout_6->addWidget(ps);

        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_4 = new QVBoxLayout(frame);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label_17 = new QLabel(frame);
        label_17->setObjectName(QStringLiteral("label_17"));

        verticalLayout_4->addWidget(label_17);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_18 = new QLabel(frame);
        label_18->setObjectName(QStringLiteral("label_18"));

        horizontalLayout_2->addWidget(label_18);

        cLockTurnout = new JmriBeanComboBox(frame);
        cLockTurnout->setObjectName(QStringLiteral("cLockTurnout"));

        horizontalLayout_2->addWidget(cLockTurnout);

        label_24 = new QLabel(frame);
        label_24->setObjectName(QStringLiteral("label_24"));

        horizontalLayout_2->addWidget(label_24);

        cLockTurnoutStateBox = new QComboBox(frame);
        cLockTurnoutStateBox->setObjectName(QStringLiteral("cLockTurnoutStateBox"));

        horizontalLayout_2->addWidget(cLockTurnoutStateBox);


        verticalLayout_4->addLayout(horizontalLayout_2);


        verticalLayout_6->addWidget(frame);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        status1 = new QLabel(centralWidget);
        status1->setObjectName(QStringLiteral("status1"));

        verticalLayout_5->addWidget(status1);

        status2 = new QLabel(centralWidget);
        status2->setObjectName(QStringLiteral("status2"));

        verticalLayout_5->addWidget(status2);


        verticalLayout_6->addLayout(verticalLayout_5);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        createButton = new QPushButton(centralWidget);
        createButton->setObjectName(QStringLiteral("createButton"));
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(createButton->sizePolicy().hasHeightForWidth());
        createButton->setSizePolicy(sizePolicy4);

        horizontalLayout_3->addWidget(createButton);

        editButton = new QPushButton(centralWidget);
        editButton->setObjectName(QStringLiteral("editButton"));
        sizePolicy4.setHeightForWidth(editButton->sizePolicy().hasHeightForWidth());
        editButton->setSizePolicy(sizePolicy4);

        horizontalLayout_3->addWidget(editButton);

        deleteButton = new QPushButton(centralWidget);
        deleteButton->setObjectName(QStringLiteral("deleteButton"));

        horizontalLayout_3->addWidget(deleteButton);

        updateButton = new QPushButton(centralWidget);
        updateButton->setObjectName(QStringLiteral("updateButton"));

        horizontalLayout_3->addWidget(updateButton);

        cancelButton = new QPushButton(centralWidget);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        horizontalLayout_3->addWidget(cancelButton);

        exportBUtton = new QPushButton(centralWidget);
        exportBUtton->setObjectName(QStringLiteral("exportBUtton"));

        horizontalLayout_3->addWidget(exportBUtton);


        verticalLayout_6->addLayout(horizontalLayout_3);

        addFrame->setCentralWidget(centralWidget);
        menubar = new QMenuBar(addFrame);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 617, 21));
        addFrame->setMenuBar(menubar);
        statusbar = new QStatusBar(addFrame);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        addFrame->setStatusBar(statusbar);

        retranslateUi(addFrame);

        QMetaObject::connectSlotsByName(addFrame);
    } // setupUi

    void retranslateUi(QMainWindow *addFrame)
    {
        addFrame->setWindowTitle(QApplication::translate("addFrame", "MainWindow", Q_NULLPTR));
        label->setText(QApplication::translate("addFrame", "Route SystemName:", Q_NULLPTR));
        _systemName->setText(QApplication::translate("addFrame", "xxxxxxxxxxxx", Q_NULLPTR));
        fixedSystemName->setText(QApplication::translate("addFrame", "TextLabel", Q_NULLPTR));
        _autoSystemName->setText(QApplication::translate("addFrame", "Automatically generate System Name", Q_NULLPTR));
        label_2->setText(QApplication::translate("addFrame", "Route User Name:", Q_NULLPTR));
        _userName->setText(QApplication::translate("addFrame", "xxxxxxxxxxxxxxxxxxxx", Q_NULLPTR));
        label_3->setText(QApplication::translate("addFrame", "Show", Q_NULLPTR));
        allButton->setText(QApplication::translate("addFrame", "All", Q_NULLPTR));
        includedButton->setText(QApplication::translate("addFrame", "Included", Q_NULLPTR));
        label_4->setText(QApplication::translate("addFrame", "Turnouts and Sensors", Q_NULLPTR));
        p2xtSpace->setText(QApplication::translate("addFrame", "TextLabel", Q_NULLPTR));
        label_9->setText(QString());
        label_5->setText(QApplication::translate("addFrame", "Please select", Q_NULLPTR));
        label_6->setText(QApplication::translate("addFrame", "Turnouts to", Q_NULLPTR));
        label_7->setText(QApplication::translate("addFrame", "be included ", Q_NULLPTR));
        label_8->setText(QApplication::translate("addFrame", "In this route", Q_NULLPTR));
        p2xsSpace->setText(QApplication::translate("addFrame", "TextLabel", Q_NULLPTR));
        label_10->setText(QString());
        label_11->setText(QApplication::translate("addFrame", "Please select", Q_NULLPTR));
        label_12->setText(QApplication::translate("addFrame", "Sensors to", Q_NULLPTR));
        label_13->setText(QApplication::translate("addFrame", "be included ", Q_NULLPTR));
        label_14->setText(QApplication::translate("addFrame", "In this route", Q_NULLPTR));
        label_15->setText(QApplication::translate("addFrame", "Play sound file :", Q_NULLPTR));
        setSound->setText(QApplication::translate("addFrame", "Set", Q_NULLPTR));
        label_16->setText(QApplication::translate("addFrame", "Run script:", Q_NULLPTR));
        setScript->setText(QApplication::translate("addFrame", "Set", Q_NULLPTR));
        sensorThatActivates->setText(QApplication::translate("addFrame", "Enter Sensor that Activates when Route Turnouts are correctly aligned (optional).", Q_NULLPTR));
        sensorsThatTrigger->setText(QApplication::translate("addFrame", "Enter Sensors that trigger this Route (optional)", Q_NULLPTR));
        label_19->setText(QApplication::translate("addFrame", "Sensors:", Q_NULLPTR));
        label_20->setText(QApplication::translate("addFrame", "Enter a Turnout that triggers this Route (optional).", Q_NULLPTR));
        label_21->setText(QApplication::translate("addFrame", "Turnout:", Q_NULLPTR));
        label_22->setText(QApplication::translate("addFrame", "Condition:", Q_NULLPTR));
        label_23->setText(QApplication::translate("addFrame", "Enter additional delay between Turnout Commands(optiona), added delay:", Q_NULLPTR));
        label_17->setText(QApplication::translate("addFrame", "Enter a Turnout that controls the lock for this Route (optional).", Q_NULLPTR));
        label_18->setText(QApplication::translate("addFrame", "Turnout:", Q_NULLPTR));
        label_24->setText(QApplication::translate("addFrame", "Conditon:", Q_NULLPTR));
        status1->setText(QApplication::translate("addFrame", "To change this Route, make changes above, then click 'Update Route'.", Q_NULLPTR));
        status2->setText(QApplication::translate("addFrame", "To leave Edit mode, without changing this Route, click 'Cancel',", Q_NULLPTR));
        createButton->setText(QApplication::translate("addFrame", "Add Route", Q_NULLPTR));
        editButton->setText(QApplication::translate("addFrame", "Edit Route", Q_NULLPTR));
        deleteButton->setText(QApplication::translate("addFrame", "Delete", Q_NULLPTR));
        updateButton->setText(QApplication::translate("addFrame", "Update", Q_NULLPTR));
        cancelButton->setText(QApplication::translate("addFrame", "Cancel", Q_NULLPTR));
        exportBUtton->setText(QApplication::translate("addFrame", "Export to Logix", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class addFrame: public Ui_addFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROUTETABLEACTION_H
