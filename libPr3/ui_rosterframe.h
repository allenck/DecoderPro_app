/********************************************************************************
** Form generated from reading UI file 'rosterframe.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROSTERFRAME_H
#define UI_ROSTERFRAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
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
#include <QtWidgets/QTableWidget>
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
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QSplitter *splitter;
    QTableWidget *tableWidget;
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
    QLabel *lblImage;
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
            RosterFrame->setObjectName(QStringLiteral("RosterFrame"));
        RosterFrame->resize(800, 600);
        QFont font;
        font.setPointSize(8);
        RosterFrame->setFont(font);
        actionNew_Roster_Window = new QAction(RosterFrame);
        actionNew_Roster_Window->setObjectName(QStringLiteral("actionNew_Roster_Window"));
        actionClose_Window = new QAction(RosterFrame);
        actionClose_Window->setObjectName(QStringLiteral("actionClose_Window"));
        actionProgram = new QAction(RosterFrame);
        actionProgram->setObjectName(QStringLiteral("actionProgram"));
        actionLabels_and_Media = new QAction(RosterFrame);
        actionLabels_and_Media->setObjectName(QStringLiteral("actionLabels_and_Media"));
        actionNew_Throttle = new QAction(RosterFrame);
        actionNew_Throttle->setObjectName(QStringLiteral("actionNew_Throttle"));
        actionHide_Show_Summary_Panel = new QAction(RosterFrame);
        actionHide_Show_Summary_Panel->setObjectName(QStringLiteral("actionHide_Show_Summary_Panel"));
        actionHide_Show_Roster_Image = new QAction(RosterFrame);
        actionHide_Show_Roster_Image->setObjectName(QStringLiteral("actionHide_Show_Roster_Image"));
        actionProgramming_Track = new QAction(RosterFrame);
        actionProgramming_Track->setObjectName(QStringLiteral("actionProgramming_Track"));
        actionProgramming_Track->setCheckable(true);
        actionProgramming_On_Main = new QAction(RosterFrame);
        actionProgramming_On_Main->setObjectName(QStringLiteral("actionProgramming_On_Main"));
        actionProgramming_On_Main->setCheckable(true);
        actionEdit_Only = new QAction(RosterFrame);
        actionEdit_Only->setObjectName(QStringLiteral("actionEdit_Only"));
        actionEdit_Only->setCheckable(true);
        actionEdit_Only->setChecked(true);
        actionDuplicate_Loco = new QAction(RosterFrame);
        actionDuplicate_Loco->setObjectName(QStringLiteral("actionDuplicate_Loco"));
        actionDelete_Loco = new QAction(RosterFrame);
        actionDelete_Loco->setObjectName(QStringLiteral("actionDelete_Loco"));
        actionPreferences = new QAction(RosterFrame);
        actionPreferences->setObjectName(QStringLiteral("actionPreferences"));
        centralwidget = new QWidget(RosterFrame);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Vertical);
        tableWidget = new QTableWidget(splitter);
        if (tableWidget->columnCount() < 20)
            tableWidget->setColumnCount(20);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setColumnCount(20);
        splitter->addWidget(tableWidget);
        tableWidget->horizontalHeader()->setStretchLastSection(true);

        verticalLayout->addWidget(splitter);


        verticalLayout_2->addLayout(verticalLayout);

        summaryPanel = new QWidget(centralwidget);
        summaryPanel->setObjectName(QStringLiteral("summaryPanel"));
        gridLayout_4 = new QGridLayout(summaryPanel);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        service = new QRadioButton(summaryPanel);
        service->setObjectName(QStringLiteral("service"));

        verticalLayout_5->addWidget(service);

        ops = new QRadioButton(summaryPanel);
        ops->setObjectName(QStringLiteral("ops"));

        verticalLayout_5->addWidget(ops);

        edit = new QRadioButton(summaryPanel);
        edit->setObjectName(QStringLiteral("edit"));
        edit->setChecked(true);

        verticalLayout_5->addWidget(edit);


        gridLayout_4->addLayout(verticalLayout_5, 0, 2, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        btnThrottle = new QPushButton(summaryPanel);
        btnThrottle->setObjectName(QStringLiteral("btnThrottle"));

        gridLayout->addWidget(btnThrottle, 1, 1, 1, 1);

        btnLabelsMedia = new QPushButton(summaryPanel);
        btnLabelsMedia->setObjectName(QStringLiteral("btnLabelsMedia"));

        gridLayout->addWidget(btnLabelsMedia, 1, 0, 1, 1);

        btnProgram = new QPushButton(summaryPanel);
        btnProgram->setObjectName(QStringLiteral("btnProgram"));

        gridLayout->addWidget(btnProgram, 0, 0, 1, 2);


        gridLayout_4->addLayout(gridLayout, 1, 2, 1, 1);

        lblImage = new QLabel(summaryPanel);
        lblImage->setObjectName(QStringLiteral("lblImage"));

        gridLayout_4->addWidget(lblImage, 0, 0, 3, 1);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        label_11 = new QLabel(summaryPanel);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setMinimumSize(QSize(109, 0));
        label_11->setMaximumSize(QSize(16777215, 16777215));
        label_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(0, QFormLayout::LabelRole, label_11);

        lblID = new QLabel(summaryPanel);
        lblID->setObjectName(QStringLiteral("lblID"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lblID);

        label_12 = new QLabel(summaryPanel);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setMinimumSize(QSize(109, 0));
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(1, QFormLayout::LabelRole, label_12);

        lblRoadName = new QLabel(summaryPanel);
        lblRoadName->setObjectName(QStringLiteral("lblRoadName"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lblRoadName);

        label_13 = new QLabel(summaryPanel);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setMinimumSize(QSize(109, 0));
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(2, QFormLayout::LabelRole, label_13);

        lblRoadNumber = new QLabel(summaryPanel);
        lblRoadNumber->setObjectName(QStringLiteral("lblRoadNumber"));

        formLayout->setWidget(2, QFormLayout::FieldRole, lblRoadNumber);

        label_14 = new QLabel(summaryPanel);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setMinimumSize(QSize(109, 0));
        label_14->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(3, QFormLayout::LabelRole, label_14);

        lblManufacturer = new QLabel(summaryPanel);
        lblManufacturer->setObjectName(QStringLiteral("lblManufacturer"));

        formLayout->setWidget(3, QFormLayout::FieldRole, lblManufacturer);

        label_15 = new QLabel(summaryPanel);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setMinimumSize(QSize(111, 0));
        label_15->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(4, QFormLayout::LabelRole, label_15);

        lblOwner = new QLabel(summaryPanel);
        lblOwner->setObjectName(QStringLiteral("lblOwner"));

        formLayout->setWidget(4, QFormLayout::FieldRole, lblOwner);

        label_16 = new QLabel(summaryPanel);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setMinimumSize(QSize(109, 0));
        label_16->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(5, QFormLayout::LabelRole, label_16);

        lblModel = new QLabel(summaryPanel);
        lblModel->setObjectName(QStringLiteral("lblModel"));

        formLayout->setWidget(5, QFormLayout::FieldRole, lblModel);

        label_17 = new QLabel(summaryPanel);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setMinimumSize(QSize(109, 0));
        label_17->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(6, QFormLayout::LabelRole, label_17);

        lblDCCAddress = new QLabel(summaryPanel);
        lblDCCAddress->setObjectName(QStringLiteral("lblDCCAddress"));

        formLayout->setWidget(6, QFormLayout::FieldRole, lblDCCAddress);

        label_18 = new QLabel(summaryPanel);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setMinimumSize(QSize(109, 0));
        label_18->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(7, QFormLayout::LabelRole, label_18);

        lblDecoderFamily = new QLabel(summaryPanel);
        lblDecoderFamily->setObjectName(QStringLiteral("lblDecoderFamily"));

        formLayout->setWidget(7, QFormLayout::FieldRole, lblDecoderFamily);

        label_19 = new QLabel(summaryPanel);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setMinimumSize(QSize(109, 0));
        label_19->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(8, QFormLayout::LabelRole, label_19);

        lblDecoderModel = new QLabel(summaryPanel);
        lblDecoderModel->setObjectName(QStringLiteral("lblDecoderModel"));

        formLayout->setWidget(8, QFormLayout::FieldRole, lblDecoderModel);

        label_20 = new QLabel(summaryPanel);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setMinimumSize(QSize(109, 0));
        label_20->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(9, QFormLayout::LabelRole, label_20);

        lblFileName = new QLabel(summaryPanel);
        lblFileName->setObjectName(QStringLiteral("lblFileName"));

        formLayout->setWidget(9, QFormLayout::FieldRole, lblFileName);


        gridLayout_4->addLayout(formLayout, 0, 1, 3, 1);


        verticalLayout_2->addWidget(summaryPanel);

        RosterFrame->setCentralWidget(centralwidget);
        menubar = new QMenuBar(RosterFrame);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuSettings = new QMenu(menubar);
        menuSettings->setObjectName(QStringLiteral("menuSettings"));
        menuProgramming = new QMenu(menuSettings);
        menuProgramming->setObjectName(QStringLiteral("menuProgramming"));
        menuActions = new QMenu(menubar);
        menuActions->setObjectName(QStringLiteral("menuActions"));
        menuLocoNet = new QMenu(menubar);
        menuLocoNet->setObjectName(QStringLiteral("menuLocoNet"));
        RosterFrame->setMenuBar(menubar);
        statusBar = new QStatusBar(RosterFrame);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        RosterFrame->setStatusBar(statusBar);
        toolBar = new QToolBar(RosterFrame);
        toolBar->setObjectName(QStringLiteral("toolBar"));
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
        RosterFrame->setWindowTitle(QApplication::translate("RosterFrame", "Roster: All Entries", 0));
        actionNew_Roster_Window->setText(QApplication::translate("RosterFrame", "New Roster Window", 0));
        actionClose_Window->setText(QApplication::translate("RosterFrame", "Close Window", 0));
        actionProgram->setText(QApplication::translate("RosterFrame", "Program", 0));
        actionLabels_and_Media->setText(QApplication::translate("RosterFrame", "Labels && Media", 0));
        actionNew_Throttle->setText(QApplication::translate("RosterFrame", "New Throttle", 0));
        actionHide_Show_Summary_Panel->setText(QApplication::translate("RosterFrame", "Hide/Show Summary Panel", 0));
        actionHide_Show_Roster_Image->setText(QApplication::translate("RosterFrame", "Hide/Show Roster Image", 0));
        actionProgramming_Track->setText(QApplication::translate("RosterFrame", "Programming Track", 0));
        actionProgramming_On_Main->setText(QApplication::translate("RosterFrame", "Programming On Main", 0));
        actionEdit_Only->setText(QApplication::translate("RosterFrame", "Edit Only", 0));
        actionDuplicate_Loco->setText(QApplication::translate("RosterFrame", "Duplicate Loco", 0));
        actionDelete_Loco->setText(QApplication::translate("RosterFrame", "Delete Loco", 0));
        actionPreferences->setText(QApplication::translate("RosterFrame", "Preferences", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("RosterFrame", "ID", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("RosterFrame", "DCC Address", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("RosterFrame", "Icon", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("RosterFrame", "Decoder Model", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("RosterFrame", "Road Name", 0));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("RosterFrame", "Road Number", 0));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("RosterFrame", "Manufacturer", 0));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QApplication::translate("RosterFrame", "Model", 0));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QApplication::translate("RosterFrame", "Owner", 0));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QApplication::translate("RosterFrame", "Date Modified", 0));
        service->setText(QApplication::translate("RosterFrame", "Programming Track", 0));
        ops->setText(QApplication::translate("RosterFrame", "Programming on Main", 0));
        edit->setText(QApplication::translate("RosterFrame", "Edit Only", 0));
        btnThrottle->setText(QApplication::translate("RosterFrame", "Throttle", 0));
        btnLabelsMedia->setText(QApplication::translate("RosterFrame", "Labels & Media", 0));
        btnProgram->setText(QApplication::translate("RosterFrame", "Program", 0));
        lblImage->setText(QApplication::translate("RosterFrame", "Roster Image", 0));
        label_11->setText(QApplication::translate("RosterFrame", "ID:", 0));
        lblID->setText(QApplication::translate("RosterFrame", "TextLabel", 0));
        label_12->setText(QApplication::translate("RosterFrame", "Road Name:", 0));
        lblRoadName->setText(QApplication::translate("RosterFrame", "TextLabel", 0));
        label_13->setText(QApplication::translate("RosterFrame", "Road Number:", 0));
        lblRoadNumber->setText(QApplication::translate("RosterFrame", "TextLabel", 0));
        label_14->setText(QApplication::translate("RosterFrame", "Manufacturer:", 0));
        lblManufacturer->setText(QApplication::translate("RosterFrame", "TextLabel", 0));
        label_15->setText(QApplication::translate("RosterFrame", "Owner:", 0));
        lblOwner->setText(QApplication::translate("RosterFrame", "TextLabel", 0));
        label_16->setText(QApplication::translate("RosterFrame", "Model:", 0));
        lblModel->setText(QApplication::translate("RosterFrame", "TextLabel", 0));
        label_17->setText(QApplication::translate("RosterFrame", "DCC Address:", 0));
        lblDCCAddress->setText(QApplication::translate("RosterFrame", "TextLabel", 0));
        label_18->setText(QApplication::translate("RosterFrame", "Decoder Family:", 0));
        lblDecoderFamily->setText(QApplication::translate("RosterFrame", "TextLabel", 0));
        label_19->setText(QApplication::translate("RosterFrame", "Decoder Model:", 0));
        lblDecoderModel->setText(QApplication::translate("RosterFrame", "TextLabel", 0));
        label_20->setText(QApplication::translate("RosterFrame", "File Name:", 0));
        lblFileName->setText(QApplication::translate("RosterFrame", "TextLabel", 0));
        menuFile->setTitle(QApplication::translate("RosterFrame", "File", 0));
        menuEdit->setTitle(QApplication::translate("RosterFrame", "Edit", 0));
        menuSettings->setTitle(QApplication::translate("RosterFrame", "Settings", 0));
        menuProgramming->setTitle(QApplication::translate("RosterFrame", "Programming", 0));
        menuActions->setTitle(QApplication::translate("RosterFrame", "Actions", 0));
        menuLocoNet->setTitle(QApplication::translate("RosterFrame", "LocoNet", 0));
        toolBar->setWindowTitle(QApplication::translate("RosterFrame", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class RosterFrame: public Ui_RosterFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROSTERFRAME_H
