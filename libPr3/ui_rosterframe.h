/********************************************************************************
** Form generated from reading UI file 'rosterframe.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROSTERFRAME_H
#define UI_ROSTERFRAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RosterFrame
{
public:
    QAction *actionNew_Roster_Window;
    QAction *actionClose_Window;
    QAction *actionProgram;
    QAction *actionLabels_and_Media;
    QAction *actionNew_Throttle;
    QAction *actionHide_Show_Summary_Panel;
    QAction *actionHide_Show_Roster_Image;
    QAction *actionProgramming_Track;
    QAction *actionProgramming_On_Main;
    QAction *actionEdit_Only;
    QAction *actionDuplicate_Loco;
    QAction *actionDelete_Loco;
    QAction *actionPreferences;
    QWidget *centralwidget;
    QGridLayout *gridLayout_3;
    QSplitter *splitter;
    QSplitter *splitter_2;
    QWidget *groupsPlaceholder;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QTableView *rtable;
    QWidget *summaryPanel;
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout_5;
    QRadioButton *service;
    QRadioButton *ops;
    QRadioButton *edit;
    QGridLayout *gridLayout;
    QPushButton *btnThrottle;
    QPushButton *btnLabelsMedia;
    QPushButton *btnProgram;
    QLabel *locoImage;
    QFormLayout *formLayout;
    QLabel *label_11;
    QLabel *lblID;
    QLabel *label_12;
    QLabel *lblRoadName;
    QLabel *label_13;
    QLabel *lblRoadNumber;
    QLabel *label_14;
    QLabel *lblManufacturer;
    QLabel *label_15;
    QLabel *lblOwner;
    QLabel *label_16;
    QLabel *lblModel;
    QLabel *label_17;
    QLabel *lblDCCAddress;
    QLabel *label_18;
    QLabel *lblDecoderFamily;
    QLabel *label_19;
    QLabel *lblDecoderModel;
    QLabel *label_20;
    QLabel *lblFileName;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuSettings;
    QMenu *menuProgramming;
    QMenu *menuActions;
    QMenu *menuLocoNet;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *RosterFrame)
    {
        if (RosterFrame->objectName().isEmpty())
            RosterFrame->setObjectName(QLatin1String("RosterFrame"));
        RosterFrame->resize(800, 600);
        QFont font;
        font.setPointSize(8);
        RosterFrame->setFont(font);
        actionNew_Roster_Window = new QAction(RosterFrame);
        actionNew_Roster_Window->setObjectName(QLatin1String("actionNew_Roster_Window"));
        actionClose_Window = new QAction(RosterFrame);
        actionClose_Window->setObjectName(QLatin1String("actionClose_Window"));
        actionProgram = new QAction(RosterFrame);
        actionProgram->setObjectName(QLatin1String("actionProgram"));
        actionLabels_and_Media = new QAction(RosterFrame);
        actionLabels_and_Media->setObjectName(QLatin1String("actionLabels_and_Media"));
        actionNew_Throttle = new QAction(RosterFrame);
        actionNew_Throttle->setObjectName(QLatin1String("actionNew_Throttle"));
        actionHide_Show_Summary_Panel = new QAction(RosterFrame);
        actionHide_Show_Summary_Panel->setObjectName(QLatin1String("actionHide_Show_Summary_Panel"));
        actionHide_Show_Roster_Image = new QAction(RosterFrame);
        actionHide_Show_Roster_Image->setObjectName(QLatin1String("actionHide_Show_Roster_Image"));
        actionProgramming_Track = new QAction(RosterFrame);
        actionProgramming_Track->setObjectName(QLatin1String("actionProgramming_Track"));
        actionProgramming_Track->setCheckable(true);
        actionProgramming_On_Main = new QAction(RosterFrame);
        actionProgramming_On_Main->setObjectName(QLatin1String("actionProgramming_On_Main"));
        actionProgramming_On_Main->setCheckable(true);
        actionEdit_Only = new QAction(RosterFrame);
        actionEdit_Only->setObjectName(QLatin1String("actionEdit_Only"));
        actionEdit_Only->setCheckable(true);
        actionEdit_Only->setChecked(true);
        actionDuplicate_Loco = new QAction(RosterFrame);
        actionDuplicate_Loco->setObjectName(QLatin1String("actionDuplicate_Loco"));
        actionDelete_Loco = new QAction(RosterFrame);
        actionDelete_Loco->setObjectName(QLatin1String("actionDelete_Loco"));
        actionPreferences = new QAction(RosterFrame);
        actionPreferences->setObjectName(QLatin1String("actionPreferences"));
        centralwidget = new QWidget(RosterFrame);
        centralwidget->setObjectName(QLatin1String("centralwidget"));
        gridLayout_3 = new QGridLayout(centralwidget);
        gridLayout_3->setObjectName(QLatin1String("gridLayout_3"));
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QLatin1String("splitter"));
        splitter->setOrientation(Qt::Vertical);
        splitter_2 = new QSplitter(splitter);
        splitter_2->setObjectName(QLatin1String("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        groupsPlaceholder = new QWidget(splitter_2);
        groupsPlaceholder->setObjectName(QLatin1String("groupsPlaceholder"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupsPlaceholder->sizePolicy().hasHeightForWidth());
        groupsPlaceholder->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(groupsPlaceholder);
        verticalLayout_2->setObjectName(QLatin1String("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QLatin1String("verticalLayout"));

        verticalLayout_2->addLayout(verticalLayout);

        splitter_2->addWidget(groupsPlaceholder);
        rtable = new QTableView(splitter_2);
        rtable->setObjectName(QLatin1String("rtable"));
        splitter_2->addWidget(rtable);
        splitter->addWidget(splitter_2);
        summaryPanel = new QWidget(splitter);
        summaryPanel->setObjectName(QLatin1String("summaryPanel"));
        gridLayout_4 = new QGridLayout(summaryPanel);
        gridLayout_4->setObjectName(QLatin1String("gridLayout_4"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QLatin1String("verticalLayout_5"));
        service = new QRadioButton(summaryPanel);
        service->setObjectName(QLatin1String("service"));

        verticalLayout_5->addWidget(service);

        ops = new QRadioButton(summaryPanel);
        ops->setObjectName(QLatin1String("ops"));

        verticalLayout_5->addWidget(ops);

        edit = new QRadioButton(summaryPanel);
        edit->setObjectName(QLatin1String("edit"));
        edit->setChecked(true);

        verticalLayout_5->addWidget(edit);


        gridLayout_4->addLayout(verticalLayout_5, 0, 2, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QLatin1String("gridLayout"));
        btnThrottle = new QPushButton(summaryPanel);
        btnThrottle->setObjectName(QLatin1String("btnThrottle"));

        gridLayout->addWidget(btnThrottle, 1, 1, 1, 1);

        btnLabelsMedia = new QPushButton(summaryPanel);
        btnLabelsMedia->setObjectName(QLatin1String("btnLabelsMedia"));

        gridLayout->addWidget(btnLabelsMedia, 1, 0, 1, 1);

        btnProgram = new QPushButton(summaryPanel);
        btnProgram->setObjectName(QLatin1String("btnProgram"));

        gridLayout->addWidget(btnProgram, 0, 0, 1, 2);


        gridLayout_4->addLayout(gridLayout, 1, 2, 1, 1);

        locoImage = new QLabel(summaryPanel);
        locoImage->setObjectName(QLatin1String("locoImage"));

        gridLayout_4->addWidget(locoImage, 0, 0, 3, 1);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QLatin1String("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        label_11 = new QLabel(summaryPanel);
        label_11->setObjectName(QLatin1String("label_11"));
        label_11->setMinimumSize(QSize(109, 0));
        label_11->setMaximumSize(QSize(16777215, 16777215));
        label_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(0, QFormLayout::LabelRole, label_11);

        lblID = new QLabel(summaryPanel);
        lblID->setObjectName(QLatin1String("lblID"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lblID);

        label_12 = new QLabel(summaryPanel);
        label_12->setObjectName(QLatin1String("label_12"));
        label_12->setMinimumSize(QSize(109, 0));
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(1, QFormLayout::LabelRole, label_12);

        lblRoadName = new QLabel(summaryPanel);
        lblRoadName->setObjectName(QLatin1String("lblRoadName"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lblRoadName);

        label_13 = new QLabel(summaryPanel);
        label_13->setObjectName(QLatin1String("label_13"));
        label_13->setMinimumSize(QSize(109, 0));
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(2, QFormLayout::LabelRole, label_13);

        lblRoadNumber = new QLabel(summaryPanel);
        lblRoadNumber->setObjectName(QLatin1String("lblRoadNumber"));

        formLayout->setWidget(2, QFormLayout::FieldRole, lblRoadNumber);

        label_14 = new QLabel(summaryPanel);
        label_14->setObjectName(QLatin1String("label_14"));
        label_14->setMinimumSize(QSize(109, 0));
        label_14->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(3, QFormLayout::LabelRole, label_14);

        lblManufacturer = new QLabel(summaryPanel);
        lblManufacturer->setObjectName(QLatin1String("lblManufacturer"));

        formLayout->setWidget(3, QFormLayout::FieldRole, lblManufacturer);

        label_15 = new QLabel(summaryPanel);
        label_15->setObjectName(QLatin1String("label_15"));
        label_15->setMinimumSize(QSize(111, 0));
        label_15->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(4, QFormLayout::LabelRole, label_15);

        lblOwner = new QLabel(summaryPanel);
        lblOwner->setObjectName(QLatin1String("lblOwner"));

        formLayout->setWidget(4, QFormLayout::FieldRole, lblOwner);

        label_16 = new QLabel(summaryPanel);
        label_16->setObjectName(QLatin1String("label_16"));
        label_16->setMinimumSize(QSize(109, 0));
        label_16->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(5, QFormLayout::LabelRole, label_16);

        lblModel = new QLabel(summaryPanel);
        lblModel->setObjectName(QLatin1String("lblModel"));

        formLayout->setWidget(5, QFormLayout::FieldRole, lblModel);

        label_17 = new QLabel(summaryPanel);
        label_17->setObjectName(QLatin1String("label_17"));
        label_17->setMinimumSize(QSize(109, 0));
        label_17->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(6, QFormLayout::LabelRole, label_17);

        lblDCCAddress = new QLabel(summaryPanel);
        lblDCCAddress->setObjectName(QLatin1String("lblDCCAddress"));

        formLayout->setWidget(6, QFormLayout::FieldRole, lblDCCAddress);

        label_18 = new QLabel(summaryPanel);
        label_18->setObjectName(QLatin1String("label_18"));
        label_18->setMinimumSize(QSize(109, 0));
        label_18->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(7, QFormLayout::LabelRole, label_18);

        lblDecoderFamily = new QLabel(summaryPanel);
        lblDecoderFamily->setObjectName(QLatin1String("lblDecoderFamily"));

        formLayout->setWidget(7, QFormLayout::FieldRole, lblDecoderFamily);

        label_19 = new QLabel(summaryPanel);
        label_19->setObjectName(QLatin1String("label_19"));
        label_19->setMinimumSize(QSize(109, 0));
        label_19->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(8, QFormLayout::LabelRole, label_19);

        lblDecoderModel = new QLabel(summaryPanel);
        lblDecoderModel->setObjectName(QLatin1String("lblDecoderModel"));

        formLayout->setWidget(8, QFormLayout::FieldRole, lblDecoderModel);

        label_20 = new QLabel(summaryPanel);
        label_20->setObjectName(QLatin1String("label_20"));
        label_20->setMinimumSize(QSize(109, 0));
        label_20->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(9, QFormLayout::LabelRole, label_20);

        lblFileName = new QLabel(summaryPanel);
        lblFileName->setObjectName(QLatin1String("lblFileName"));

        formLayout->setWidget(9, QFormLayout::FieldRole, lblFileName);


        gridLayout_4->addLayout(formLayout, 0, 1, 3, 1);

        splitter->addWidget(summaryPanel);

        gridLayout_3->addWidget(splitter, 0, 0, 1, 1);

        RosterFrame->setCentralWidget(centralwidget);
        menubar = new QMenuBar(RosterFrame);
        menubar->setObjectName(QLatin1String("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QLatin1String("menuFile"));
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName(QLatin1String("menuEdit"));
        menuSettings = new QMenu(menubar);
        menuSettings->setObjectName(QLatin1String("menuSettings"));
        menuProgramming = new QMenu(menuSettings);
        menuProgramming->setObjectName(QLatin1String("menuProgramming"));
        menuActions = new QMenu(menubar);
        menuActions->setObjectName(QLatin1String("menuActions"));
        menuLocoNet = new QMenu(menubar);
        menuLocoNet->setObjectName(QLatin1String("menuLocoNet"));
        RosterFrame->setMenuBar(menubar);
        statusBar = new QStatusBar(RosterFrame);
        statusBar->setObjectName(QLatin1String("statusBar"));
        RosterFrame->setStatusBar(statusBar);
        toolBar = new QToolBar(RosterFrame);
        toolBar->setObjectName(QLatin1String("toolBar"));
        RosterFrame->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuSettings->menuAction());
        menubar->addAction(menuActions->menuAction());
        menubar->addAction(menuLocoNet->menuAction());
        menuFile->addAction(actionNew_Roster_Window);
        menuFile->addSeparator();
        menuFile->addAction(actionClose_Window);
        menuEdit->addAction(actionDuplicate_Loco);
        menuEdit->addAction(actionDelete_Loco);
        menuEdit->addSeparator();
        menuEdit->addAction(actionPreferences);
        menuSettings->addAction(actionHide_Show_Summary_Panel);
        menuSettings->addAction(actionHide_Show_Roster_Image);
        menuSettings->addSeparator();
        menuSettings->addAction(menuProgramming->menuAction());
        menuProgramming->addSeparator();
        menuProgramming->addAction(actionProgramming_Track);
        menuProgramming->addAction(actionProgramming_On_Main);
        menuProgramming->addAction(actionEdit_Only);
        menuActions->addAction(actionProgram);
        menuActions->addAction(actionLabels_and_Media);
        menuActions->addAction(actionNew_Throttle);

        retranslateUi(RosterFrame);

        QMetaObject::connectSlotsByName(RosterFrame);
    } // setupUi

    void retranslateUi(QMainWindow *RosterFrame)
    {
        RosterFrame->setWindowTitle(QApplication::translate("RosterFrame", "Roster: All Entries", nullptr));
        actionNew_Roster_Window->setText(QApplication::translate("RosterFrame", "New Roster Window", nullptr));
        actionClose_Window->setText(QApplication::translate("RosterFrame", "Close Window", nullptr));
        actionProgram->setText(QApplication::translate("RosterFrame", "Program", nullptr));
        actionLabels_and_Media->setText(QApplication::translate("RosterFrame", "Labels && Media", nullptr));
        actionNew_Throttle->setText(QApplication::translate("RosterFrame", "New Throttle", nullptr));
        actionHide_Show_Summary_Panel->setText(QApplication::translate("RosterFrame", "Hide/Show Summary Panel", nullptr));
        actionHide_Show_Roster_Image->setText(QApplication::translate("RosterFrame", "Hide/Show Roster Image", nullptr));
        actionProgramming_Track->setText(QApplication::translate("RosterFrame", "Programming Track", nullptr));
        actionProgramming_On_Main->setText(QApplication::translate("RosterFrame", "Programming On Main", nullptr));
        actionEdit_Only->setText(QApplication::translate("RosterFrame", "Edit Only", nullptr));
        actionDuplicate_Loco->setText(QApplication::translate("RosterFrame", "Duplicate Loco", nullptr));
        actionDelete_Loco->setText(QApplication::translate("RosterFrame", "Delete Loco", nullptr));
        actionPreferences->setText(QApplication::translate("RosterFrame", "Preferences", nullptr));
        service->setText(QApplication::translate("RosterFrame", "Programming Track", nullptr));
        ops->setText(QApplication::translate("RosterFrame", "Programming on Main", nullptr));
        edit->setText(QApplication::translate("RosterFrame", "Edit Only", nullptr));
        btnThrottle->setText(QApplication::translate("RosterFrame", "Throttle", nullptr));
        btnLabelsMedia->setText(QApplication::translate("RosterFrame", "Labels & Media", nullptr));
        btnProgram->setText(QApplication::translate("RosterFrame", "Program", nullptr));
        locoImage->setText(QApplication::translate("RosterFrame", "Roster Image", nullptr));
        label_11->setText(QApplication::translate("RosterFrame", "ID:", nullptr));
        lblID->setText(QApplication::translate("RosterFrame", "TextLabel", nullptr));
        label_12->setText(QApplication::translate("RosterFrame", "Road Name:", nullptr));
        lblRoadName->setText(QApplication::translate("RosterFrame", "TextLabel", nullptr));
        label_13->setText(QApplication::translate("RosterFrame", "Road Number:", nullptr));
        lblRoadNumber->setText(QApplication::translate("RosterFrame", "TextLabel", nullptr));
        label_14->setText(QApplication::translate("RosterFrame", "Manufacturer:", nullptr));
        lblManufacturer->setText(QApplication::translate("RosterFrame", "TextLabel", nullptr));
        label_15->setText(QApplication::translate("RosterFrame", "Owner:", nullptr));
        lblOwner->setText(QApplication::translate("RosterFrame", "TextLabel", nullptr));
        label_16->setText(QApplication::translate("RosterFrame", "Model:", nullptr));
        lblModel->setText(QApplication::translate("RosterFrame", "TextLabel", nullptr));
        label_17->setText(QApplication::translate("RosterFrame", "DCC Address:", nullptr));
        lblDCCAddress->setText(QApplication::translate("RosterFrame", "TextLabel", nullptr));
        label_18->setText(QApplication::translate("RosterFrame", "Decoder Family:", nullptr));
        lblDecoderFamily->setText(QApplication::translate("RosterFrame", "TextLabel", nullptr));
        label_19->setText(QApplication::translate("RosterFrame", "Decoder Model:", nullptr));
        lblDecoderModel->setText(QApplication::translate("RosterFrame", "TextLabel", nullptr));
        label_20->setText(QApplication::translate("RosterFrame", "File Name:", nullptr));
        lblFileName->setText(QApplication::translate("RosterFrame", "TextLabel", nullptr));
        menuFile->setTitle(QApplication::translate("RosterFrame", "File", nullptr));
        menuEdit->setTitle(QApplication::translate("RosterFrame", "Edit", nullptr));
        menuSettings->setTitle(QApplication::translate("RosterFrame", "Settings", nullptr));
        menuProgramming->setTitle(QApplication::translate("RosterFrame", "Programming", nullptr));
        menuActions->setTitle(QApplication::translate("RosterFrame", "Actions", nullptr));
        menuLocoNet->setTitle(QApplication::translate("RosterFrame", "LocoNet", nullptr));
        toolBar->setWindowTitle(QApplication::translate("RosterFrame", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RosterFrame: public Ui_RosterFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROSTERFRAME_H
