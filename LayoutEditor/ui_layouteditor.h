/********************************************************************************
** Form generated from reading UI file 'layouteditor.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAYOUTEDITOR_H
#define UI_LAYOUTEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <jmribeancombobox.h>

QT_BEGIN_NAMESPACE

class Ui_LayoutEditor
{
public:
    QAction *actionSave_panels;
    QAction *actionDelete_this_panel;
    QAction *actionEdit_mode;
    QAction *actionAllow_repositioning;
    QAction *actionAllow_layout_control;
    QAction *actionAllow_turnout_animation;
    QAction *actionShow_help_bar_in_edit_mode;
    QAction *actionShow_grid_in_edit_mode;
    QAction *actionSnap_to_grid_when_adding;
    QAction *actionSnap_to_grid_when_moving;
    QAction *actionBoth_scrollbars;
    QAction *actionNo_scrollbars;
    QAction *actionHorizontal_only;
    QAction *actionVertical_only;
    QAction *actionNever;
    QAction *actionAlways;
    QAction *actionIn_edit_mode_only;
    QAction *actionNot_in_edit_mode_only;
    QAction *actionShow_turnout_circles;
    QAction *actionEnable_antialiasing_smoother_lines;
    QAction *actionNew_title;
    QAction *actionNo_zoom;
    QAction *actionX_1_5;
    QAction *actionX_2_0;
    QAction *actionX_3_0;
    QAction *actionX_4_0;
    QAction *actionAdd_loco;
    QAction *actionAdd_loco_from_roster;
    QAction *actionRemove_markers;
    QAction *actionEdit_track_width;
    QAction *actionAdd_reporter_label;
    QAction *actionPlaceholder;
    QAction *actionPlaceholder_2;
    QAction *actionAdd_background_image_2;
    QAction *actionLoad_xl;
    QAction *actionLoad_XML;
    QAction *actionPlaceholder_3;
    QAction *actionPlaceholder_4;
    QAction *actionLoad_Other_Xml;
    QAction *actionLoad_Other_XML;
    QAction *actionSave;
    QAction *actionSave_as;
    QAction *actionScale_Translate_track_diagram;
    QAction *actionTranslate_Selection;
    QAction *actionUndo_Translate_Selection;
    QAction *actionUse_Program_Default_Turnout_size;
    QAction *actionSkip_unsignalled_Internal_Turnouts;
    QAction *actionSet_Signals_at_Turnout;
    QAction *actionSet_Signals_at_Block_Boundary;
    QAction *actionSet_Signals_at_Crossover;
    QAction *actionSet_Signals_at_Level_Crossing;
    QAction *actionSet_SIgnals_at_Throat_to_Throat_Turnouts;
    QAction *actionSet_Signals_at_Three_Way_Turnout;
    QAction *actionSet_Signals_at_a_Slip;
    QAction *actionEntry_Exit;
    QAction *actionAdd_Fast_Clock;
    QAction *actionInit;
    QAction *actionMoveLayout;
    QAction *actionAdd_Turntable;
    QAction *actionCalculate_bounds;
    QAction *x;
    QAction *y;
    QAction *actionZoom_In;
    QAction *actionZoom_Out;
    QAction *actionZoom_to_fit;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_18;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label;
    QLabel *xLabel;
    QLabel *label_2;
    QLabel *yLabel;
    QHBoxLayout *horizontalLayout;
    QLabel *turnoutNameLabel;
    JmriBeanComboBox *turnoutNameComboBox;
    QHBoxLayout *horizontalLayout_13;
    QLabel *extraTurnoutLabel;
    JmriBeanComboBox *extraTurnoutNameComboBox;
    QHBoxLayout *horizontalLayout_15;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_4;
    QCheckBox *turnoutRHButton;
    QCheckBox *turnoutLHButton;
    QCheckBox *turnoutWYEButton;
    QCheckBox *doubleXoverButton;
    QCheckBox *rhXoverButton;
    QCheckBox *lhXoverButton;
    QHBoxLayout *horizontalLayout_16;
    QCheckBox *layoutSingleSlipButton;
    QCheckBox *layoutDoubleSlipButton;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_5;
    QComboBox *rotationComboBox;
    QHBoxLayout *horizontalLayout_11;
    QHBoxLayout *horizontalLayout_2;
    QLabel *blockNameLabel;
    JmriBeanComboBox *blockIDComboBox;
    QCheckBox *highlightBlockCheckBox;
    QHBoxLayout *horizontalLayout_5;
    QLabel *blockSensorNameLabel;
    JmriBeanComboBox *blockSensorComboBox;
    QHBoxLayout *trackGroup2;
    QLabel *label_8;
    QCheckBox *trackButton;
    QCheckBox *levelXingButton;
    QHBoxLayout *trackSegmentPropertiesPanel;
    QCheckBox *chkDashed;
    QCheckBox *chkMainline;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *trackgroup1;
    QLabel *label_6;
    QCheckBox *chkEndBumper;
    QCheckBox *chkAnchorPoint;
    QCheckBox *edgeButton;
    QHBoxLayout *labelGroup1;
    QLabel *label_7;
    QCheckBox *textLabelButton;
    QLineEdit *textLabelTextField;
    QHBoxLayout *horizontalLayout_7;
    QCheckBox *memoryButton;
    JmriBeanComboBox *textMemoryComboBox;
    QCheckBox *blockContentsButton;
    JmriBeanComboBox *blockContentsComboBox;
    QHBoxLayout *horizontalLayout_10;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *multiSensorButton;
    QPushButton *changeIconsButton;
    QHBoxLayout *horizontalLayout_6;
    QCheckBox *sensorButton;
    JmriBeanComboBox *sensorComboBox;
    QHBoxLayout *horizontalLayout_8;
    QCheckBox *signalButton;
    JmriBeanComboBox *signalHeadComboBox;
    QHBoxLayout *horizontalLayout_9;
    QCheckBox *signalMastButton;
    JmriBeanComboBox *signalMastComboBox;
    QCheckBox *iconLabelButton;
    QWidget *editPanel;
    QTextEdit *textEdit;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuOptions;
    QMenu *menuShow_scrollbars;
    QMenu *menuShow_icon_tooltips;
    QMenu *menuSet_Background_color;
    QMenu *menuTools;
    QMenu *menuZoom;
    QMenu *menuMarker;
    QMenu *menuWindow;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *LayoutEditor)
    {
        if (LayoutEditor->objectName().isEmpty())
            LayoutEditor->setObjectName(QStringLiteral("LayoutEditor"));
        LayoutEditor->resize(1245, 426);
        QFont font;
        font.setPointSize(8);
        LayoutEditor->setFont(font);
        actionSave_panels = new QAction(LayoutEditor);
        actionSave_panels->setObjectName(QStringLiteral("actionSave_panels"));
        actionDelete_this_panel = new QAction(LayoutEditor);
        actionDelete_this_panel->setObjectName(QStringLiteral("actionDelete_this_panel"));
        actionEdit_mode = new QAction(LayoutEditor);
        actionEdit_mode->setObjectName(QStringLiteral("actionEdit_mode"));
        actionEdit_mode->setCheckable(true);
        actionEdit_mode->setChecked(true);
        actionAllow_repositioning = new QAction(LayoutEditor);
        actionAllow_repositioning->setObjectName(QStringLiteral("actionAllow_repositioning"));
        actionAllow_repositioning->setCheckable(true);
        actionAllow_layout_control = new QAction(LayoutEditor);
        actionAllow_layout_control->setObjectName(QStringLiteral("actionAllow_layout_control"));
        actionAllow_layout_control->setCheckable(true);
        actionAllow_turnout_animation = new QAction(LayoutEditor);
        actionAllow_turnout_animation->setObjectName(QStringLiteral("actionAllow_turnout_animation"));
        actionAllow_turnout_animation->setCheckable(true);
        actionShow_help_bar_in_edit_mode = new QAction(LayoutEditor);
        actionShow_help_bar_in_edit_mode->setObjectName(QStringLiteral("actionShow_help_bar_in_edit_mode"));
        actionShow_help_bar_in_edit_mode->setCheckable(true);
        actionShow_grid_in_edit_mode = new QAction(LayoutEditor);
        actionShow_grid_in_edit_mode->setObjectName(QStringLiteral("actionShow_grid_in_edit_mode"));
        actionShow_grid_in_edit_mode->setCheckable(true);
        actionSnap_to_grid_when_adding = new QAction(LayoutEditor);
        actionSnap_to_grid_when_adding->setObjectName(QStringLiteral("actionSnap_to_grid_when_adding"));
        actionSnap_to_grid_when_adding->setCheckable(true);
        actionSnap_to_grid_when_moving = new QAction(LayoutEditor);
        actionSnap_to_grid_when_moving->setObjectName(QStringLiteral("actionSnap_to_grid_when_moving"));
        actionSnap_to_grid_when_moving->setCheckable(true);
        actionBoth_scrollbars = new QAction(LayoutEditor);
        actionBoth_scrollbars->setObjectName(QStringLiteral("actionBoth_scrollbars"));
        actionNo_scrollbars = new QAction(LayoutEditor);
        actionNo_scrollbars->setObjectName(QStringLiteral("actionNo_scrollbars"));
        actionHorizontal_only = new QAction(LayoutEditor);
        actionHorizontal_only->setObjectName(QStringLiteral("actionHorizontal_only"));
        actionVertical_only = new QAction(LayoutEditor);
        actionVertical_only->setObjectName(QStringLiteral("actionVertical_only"));
        actionNever = new QAction(LayoutEditor);
        actionNever->setObjectName(QStringLiteral("actionNever"));
        actionAlways = new QAction(LayoutEditor);
        actionAlways->setObjectName(QStringLiteral("actionAlways"));
        actionIn_edit_mode_only = new QAction(LayoutEditor);
        actionIn_edit_mode_only->setObjectName(QStringLiteral("actionIn_edit_mode_only"));
        actionNot_in_edit_mode_only = new QAction(LayoutEditor);
        actionNot_in_edit_mode_only->setObjectName(QStringLiteral("actionNot_in_edit_mode_only"));
        actionShow_turnout_circles = new QAction(LayoutEditor);
        actionShow_turnout_circles->setObjectName(QStringLiteral("actionShow_turnout_circles"));
        actionShow_turnout_circles->setCheckable(true);
        actionEnable_antialiasing_smoother_lines = new QAction(LayoutEditor);
        actionEnable_antialiasing_smoother_lines->setObjectName(QStringLiteral("actionEnable_antialiasing_smoother_lines"));
        actionEnable_antialiasing_smoother_lines->setCheckable(true);
        actionNew_title = new QAction(LayoutEditor);
        actionNew_title->setObjectName(QStringLiteral("actionNew_title"));
        actionNo_zoom = new QAction(LayoutEditor);
        actionNo_zoom->setObjectName(QStringLiteral("actionNo_zoom"));
        actionNo_zoom->setCheckable(true);
        actionX_1_5 = new QAction(LayoutEditor);
        actionX_1_5->setObjectName(QStringLiteral("actionX_1_5"));
        actionX_1_5->setCheckable(true);
        actionX_2_0 = new QAction(LayoutEditor);
        actionX_2_0->setObjectName(QStringLiteral("actionX_2_0"));
        actionX_2_0->setCheckable(true);
        actionX_3_0 = new QAction(LayoutEditor);
        actionX_3_0->setObjectName(QStringLiteral("actionX_3_0"));
        actionX_3_0->setCheckable(true);
        actionX_4_0 = new QAction(LayoutEditor);
        actionX_4_0->setObjectName(QStringLiteral("actionX_4_0"));
        actionX_4_0->setCheckable(true);
        actionAdd_loco = new QAction(LayoutEditor);
        actionAdd_loco->setObjectName(QStringLiteral("actionAdd_loco"));
        actionAdd_loco_from_roster = new QAction(LayoutEditor);
        actionAdd_loco_from_roster->setObjectName(QStringLiteral("actionAdd_loco_from_roster"));
        actionRemove_markers = new QAction(LayoutEditor);
        actionRemove_markers->setObjectName(QStringLiteral("actionRemove_markers"));
        actionEdit_track_width = new QAction(LayoutEditor);
        actionEdit_track_width->setObjectName(QStringLiteral("actionEdit_track_width"));
        actionAdd_reporter_label = new QAction(LayoutEditor);
        actionAdd_reporter_label->setObjectName(QStringLiteral("actionAdd_reporter_label"));
        actionPlaceholder = new QAction(LayoutEditor);
        actionPlaceholder->setObjectName(QStringLiteral("actionPlaceholder"));
        actionPlaceholder_2 = new QAction(LayoutEditor);
        actionPlaceholder_2->setObjectName(QStringLiteral("actionPlaceholder_2"));
        actionAdd_background_image_2 = new QAction(LayoutEditor);
        actionAdd_background_image_2->setObjectName(QStringLiteral("actionAdd_background_image_2"));
        actionLoad_xl = new QAction(LayoutEditor);
        actionLoad_xl->setObjectName(QStringLiteral("actionLoad_xl"));
        actionLoad_XML = new QAction(LayoutEditor);
        actionLoad_XML->setObjectName(QStringLiteral("actionLoad_XML"));
        actionPlaceholder_3 = new QAction(LayoutEditor);
        actionPlaceholder_3->setObjectName(QStringLiteral("actionPlaceholder_3"));
        actionPlaceholder_4 = new QAction(LayoutEditor);
        actionPlaceholder_4->setObjectName(QStringLiteral("actionPlaceholder_4"));
        actionLoad_Other_Xml = new QAction(LayoutEditor);
        actionLoad_Other_Xml->setObjectName(QStringLiteral("actionLoad_Other_Xml"));
        actionLoad_Other_XML = new QAction(LayoutEditor);
        actionLoad_Other_XML->setObjectName(QStringLiteral("actionLoad_Other_XML"));
        actionSave = new QAction(LayoutEditor);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionSave->setEnabled(false);
        actionSave_as = new QAction(LayoutEditor);
        actionSave_as->setObjectName(QStringLiteral("actionSave_as"));
        actionSave_as->setEnabled(true);
        actionScale_Translate_track_diagram = new QAction(LayoutEditor);
        actionScale_Translate_track_diagram->setObjectName(QStringLiteral("actionScale_Translate_track_diagram"));
        actionTranslate_Selection = new QAction(LayoutEditor);
        actionTranslate_Selection->setObjectName(QStringLiteral("actionTranslate_Selection"));
        actionUndo_Translate_Selection = new QAction(LayoutEditor);
        actionUndo_Translate_Selection->setObjectName(QStringLiteral("actionUndo_Translate_Selection"));
        actionUse_Program_Default_Turnout_size = new QAction(LayoutEditor);
        actionUse_Program_Default_Turnout_size->setObjectName(QStringLiteral("actionUse_Program_Default_Turnout_size"));
        actionSkip_unsignalled_Internal_Turnouts = new QAction(LayoutEditor);
        actionSkip_unsignalled_Internal_Turnouts->setObjectName(QStringLiteral("actionSkip_unsignalled_Internal_Turnouts"));
        actionSkip_unsignalled_Internal_Turnouts->setCheckable(true);
        actionSet_Signals_at_Turnout = new QAction(LayoutEditor);
        actionSet_Signals_at_Turnout->setObjectName(QStringLiteral("actionSet_Signals_at_Turnout"));
        actionSet_Signals_at_Block_Boundary = new QAction(LayoutEditor);
        actionSet_Signals_at_Block_Boundary->setObjectName(QStringLiteral("actionSet_Signals_at_Block_Boundary"));
        actionSet_Signals_at_Crossover = new QAction(LayoutEditor);
        actionSet_Signals_at_Crossover->setObjectName(QStringLiteral("actionSet_Signals_at_Crossover"));
        actionSet_Signals_at_Level_Crossing = new QAction(LayoutEditor);
        actionSet_Signals_at_Level_Crossing->setObjectName(QStringLiteral("actionSet_Signals_at_Level_Crossing"));
        actionSet_Signals_at_Level_Crossing->setEnabled(true);
        actionSet_SIgnals_at_Throat_to_Throat_Turnouts = new QAction(LayoutEditor);
        actionSet_SIgnals_at_Throat_to_Throat_Turnouts->setObjectName(QStringLiteral("actionSet_SIgnals_at_Throat_to_Throat_Turnouts"));
        actionSet_SIgnals_at_Throat_to_Throat_Turnouts->setEnabled(true);
        actionSet_Signals_at_Three_Way_Turnout = new QAction(LayoutEditor);
        actionSet_Signals_at_Three_Way_Turnout->setObjectName(QStringLiteral("actionSet_Signals_at_Three_Way_Turnout"));
        actionSet_Signals_at_Three_Way_Turnout->setEnabled(true);
        actionSet_Signals_at_a_Slip = new QAction(LayoutEditor);
        actionSet_Signals_at_a_Slip->setObjectName(QStringLiteral("actionSet_Signals_at_a_Slip"));
        actionSet_Signals_at_a_Slip->setEnabled(true);
        actionEntry_Exit = new QAction(LayoutEditor);
        actionEntry_Exit->setObjectName(QStringLiteral("actionEntry_Exit"));
        actionEntry_Exit->setEnabled(true);
        actionAdd_Fast_Clock = new QAction(LayoutEditor);
        actionAdd_Fast_Clock->setObjectName(QStringLiteral("actionAdd_Fast_Clock"));
        actionInit = new QAction(LayoutEditor);
        actionInit->setObjectName(QStringLiteral("actionInit"));
        actionMoveLayout = new QAction(LayoutEditor);
        actionMoveLayout->setObjectName(QStringLiteral("actionMoveLayout"));
        actionAdd_Turntable = new QAction(LayoutEditor);
        actionAdd_Turntable->setObjectName(QStringLiteral("actionAdd_Turntable"));
        actionCalculate_bounds = new QAction(LayoutEditor);
        actionCalculate_bounds->setObjectName(QStringLiteral("actionCalculate_bounds"));
        x = new QAction(LayoutEditor);
        x->setObjectName(QStringLiteral("x"));
        y = new QAction(LayoutEditor);
        y->setObjectName(QStringLiteral("y"));
        actionZoom_In = new QAction(LayoutEditor);
        actionZoom_In->setObjectName(QStringLiteral("actionZoom_In"));
        actionZoom_Out = new QAction(LayoutEditor);
        actionZoom_Out->setObjectName(QStringLiteral("actionZoom_Out"));
        actionZoom_to_fit = new QAction(LayoutEditor);
        actionZoom_to_fit->setObjectName(QStringLiteral("actionZoom_to_fit"));
        centralWidget = new QWidget(LayoutEditor);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setObjectName(QStringLiteral("horizontalLayout_18"));
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_12->addWidget(label);

        xLabel = new QLabel(centralWidget);
        xLabel->setObjectName(QStringLiteral("xLabel"));

        horizontalLayout_12->addWidget(xLabel);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_12->addWidget(label_2);

        yLabel = new QLabel(centralWidget);
        yLabel->setObjectName(QStringLiteral("yLabel"));

        horizontalLayout_12->addWidget(yLabel);


        horizontalLayout_18->addLayout(horizontalLayout_12);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        turnoutNameLabel = new QLabel(centralWidget);
        turnoutNameLabel->setObjectName(QStringLiteral("turnoutNameLabel"));

        horizontalLayout->addWidget(turnoutNameLabel);

        turnoutNameComboBox = new JmriBeanComboBox(centralWidget);
        turnoutNameComboBox->setObjectName(QStringLiteral("turnoutNameComboBox"));

        horizontalLayout->addWidget(turnoutNameComboBox);


        horizontalLayout_18->addLayout(horizontalLayout);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        extraTurnoutLabel = new QLabel(centralWidget);
        extraTurnoutLabel->setObjectName(QStringLiteral("extraTurnoutLabel"));

        horizontalLayout_13->addWidget(extraTurnoutLabel);

        extraTurnoutNameComboBox = new JmriBeanComboBox(centralWidget);
        extraTurnoutNameComboBox->setObjectName(QStringLiteral("extraTurnoutNameComboBox"));

        horizontalLayout_13->addWidget(extraTurnoutNameComboBox);


        horizontalLayout_18->addLayout(horizontalLayout_13);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_14->addWidget(label_4);

        turnoutRHButton = new QCheckBox(centralWidget);
        turnoutRHButton->setObjectName(QStringLiteral("turnoutRHButton"));

        horizontalLayout_14->addWidget(turnoutRHButton);

        turnoutLHButton = new QCheckBox(centralWidget);
        turnoutLHButton->setObjectName(QStringLiteral("turnoutLHButton"));

        horizontalLayout_14->addWidget(turnoutLHButton);

        turnoutWYEButton = new QCheckBox(centralWidget);
        turnoutWYEButton->setObjectName(QStringLiteral("turnoutWYEButton"));

        horizontalLayout_14->addWidget(turnoutWYEButton);


        horizontalLayout_15->addLayout(horizontalLayout_14);

        doubleXoverButton = new QCheckBox(centralWidget);
        doubleXoverButton->setObjectName(QStringLiteral("doubleXoverButton"));

        horizontalLayout_15->addWidget(doubleXoverButton);

        rhXoverButton = new QCheckBox(centralWidget);
        rhXoverButton->setObjectName(QStringLiteral("rhXoverButton"));

        horizontalLayout_15->addWidget(rhXoverButton);

        lhXoverButton = new QCheckBox(centralWidget);
        lhXoverButton->setObjectName(QStringLiteral("lhXoverButton"));

        horizontalLayout_15->addWidget(lhXoverButton);


        horizontalLayout_18->addLayout(horizontalLayout_15);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        layoutSingleSlipButton = new QCheckBox(centralWidget);
        layoutSingleSlipButton->setObjectName(QStringLiteral("layoutSingleSlipButton"));

        horizontalLayout_16->addWidget(layoutSingleSlipButton);

        layoutDoubleSlipButton = new QCheckBox(centralWidget);
        layoutDoubleSlipButton->setObjectName(QStringLiteral("layoutDoubleSlipButton"));

        horizontalLayout_16->addWidget(layoutDoubleSlipButton);


        horizontalLayout_18->addLayout(horizontalLayout_16);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_17->addWidget(label_5);

        rotationComboBox = new QComboBox(centralWidget);
        rotationComboBox->setObjectName(QStringLiteral("rotationComboBox"));

        horizontalLayout_17->addWidget(rotationComboBox);


        horizontalLayout_18->addLayout(horizontalLayout_17);


        verticalLayout->addLayout(horizontalLayout_18);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        blockNameLabel = new QLabel(centralWidget);
        blockNameLabel->setObjectName(QStringLiteral("blockNameLabel"));

        horizontalLayout_2->addWidget(blockNameLabel);

        blockIDComboBox = new JmriBeanComboBox(centralWidget);
        blockIDComboBox->setObjectName(QStringLiteral("blockIDComboBox"));

        horizontalLayout_2->addWidget(blockIDComboBox);

        highlightBlockCheckBox = new QCheckBox(centralWidget);
        highlightBlockCheckBox->setObjectName(QStringLiteral("highlightBlockCheckBox"));

        horizontalLayout_2->addWidget(highlightBlockCheckBox);


        horizontalLayout_11->addLayout(horizontalLayout_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        blockSensorNameLabel = new QLabel(centralWidget);
        blockSensorNameLabel->setObjectName(QStringLiteral("blockSensorNameLabel"));

        horizontalLayout_5->addWidget(blockSensorNameLabel);

        blockSensorComboBox = new JmriBeanComboBox(centralWidget);
        blockSensorComboBox->setObjectName(QStringLiteral("blockSensorComboBox"));

        horizontalLayout_5->addWidget(blockSensorComboBox);


        horizontalLayout_11->addLayout(horizontalLayout_5);

        trackGroup2 = new QHBoxLayout();
        trackGroup2->setSpacing(6);
        trackGroup2->setObjectName(QStringLiteral("trackGroup2"));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));

        trackGroup2->addWidget(label_8);

        trackButton = new QCheckBox(centralWidget);
        trackButton->setObjectName(QStringLiteral("trackButton"));

        trackGroup2->addWidget(trackButton);

        levelXingButton = new QCheckBox(centralWidget);
        levelXingButton->setObjectName(QStringLiteral("levelXingButton"));

        trackGroup2->addWidget(levelXingButton);


        horizontalLayout_11->addLayout(trackGroup2);

        trackSegmentPropertiesPanel = new QHBoxLayout();
        trackSegmentPropertiesPanel->setSpacing(6);
        trackSegmentPropertiesPanel->setObjectName(QStringLiteral("trackSegmentPropertiesPanel"));
        chkDashed = new QCheckBox(centralWidget);
        chkDashed->setObjectName(QStringLiteral("chkDashed"));

        trackSegmentPropertiesPanel->addWidget(chkDashed);

        chkMainline = new QCheckBox(centralWidget);
        chkMainline->setObjectName(QStringLiteral("chkMainline"));

        trackSegmentPropertiesPanel->addWidget(chkMainline);


        horizontalLayout_11->addLayout(trackSegmentPropertiesPanel);


        verticalLayout->addLayout(horizontalLayout_11);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        trackgroup1 = new QHBoxLayout();
        trackgroup1->setSpacing(6);
        trackgroup1->setObjectName(QStringLiteral("trackgroup1"));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        trackgroup1->addWidget(label_6);

        chkEndBumper = new QCheckBox(centralWidget);
        chkEndBumper->setObjectName(QStringLiteral("chkEndBumper"));

        trackgroup1->addWidget(chkEndBumper);

        chkAnchorPoint = new QCheckBox(centralWidget);
        chkAnchorPoint->setObjectName(QStringLiteral("chkAnchorPoint"));

        trackgroup1->addWidget(chkAnchorPoint);

        edgeButton = new QCheckBox(centralWidget);
        edgeButton->setObjectName(QStringLiteral("edgeButton"));

        trackgroup1->addWidget(edgeButton);


        horizontalLayout_3->addLayout(trackgroup1);

        labelGroup1 = new QHBoxLayout();
        labelGroup1->setSpacing(6);
        labelGroup1->setObjectName(QStringLiteral("labelGroup1"));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        labelGroup1->addWidget(label_7);

        textLabelButton = new QCheckBox(centralWidget);
        textLabelButton->setObjectName(QStringLiteral("textLabelButton"));

        labelGroup1->addWidget(textLabelButton);

        textLabelTextField = new QLineEdit(centralWidget);
        textLabelTextField->setObjectName(QStringLiteral("textLabelTextField"));

        labelGroup1->addWidget(textLabelTextField);


        horizontalLayout_3->addLayout(labelGroup1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        memoryButton = new QCheckBox(centralWidget);
        memoryButton->setObjectName(QStringLiteral("memoryButton"));

        horizontalLayout_7->addWidget(memoryButton);

        textMemoryComboBox = new JmriBeanComboBox(centralWidget);
        textMemoryComboBox->setObjectName(QStringLiteral("textMemoryComboBox"));

        horizontalLayout_7->addWidget(textMemoryComboBox);


        horizontalLayout_3->addLayout(horizontalLayout_7);

        blockContentsButton = new QCheckBox(centralWidget);
        blockContentsButton->setObjectName(QStringLiteral("blockContentsButton"));

        horizontalLayout_3->addWidget(blockContentsButton);

        blockContentsComboBox = new JmriBeanComboBox(centralWidget);
        blockContentsComboBox->setObjectName(QStringLiteral("blockContentsComboBox"));

        horizontalLayout_3->addWidget(blockContentsComboBox);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        multiSensorButton = new QCheckBox(centralWidget);
        multiSensorButton->setObjectName(QStringLiteral("multiSensorButton"));

        horizontalLayout_4->addWidget(multiSensorButton);

        changeIconsButton = new QPushButton(centralWidget);
        changeIconsButton->setObjectName(QStringLiteral("changeIconsButton"));

        horizontalLayout_4->addWidget(changeIconsButton);


        horizontalLayout_10->addLayout(horizontalLayout_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        sensorButton = new QCheckBox(centralWidget);
        sensorButton->setObjectName(QStringLiteral("sensorButton"));

        horizontalLayout_6->addWidget(sensorButton);

        sensorComboBox = new JmriBeanComboBox(centralWidget);
        sensorComboBox->setObjectName(QStringLiteral("sensorComboBox"));

        horizontalLayout_6->addWidget(sensorComboBox);


        horizontalLayout_10->addLayout(horizontalLayout_6);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        signalButton = new QCheckBox(centralWidget);
        signalButton->setObjectName(QStringLiteral("signalButton"));

        horizontalLayout_8->addWidget(signalButton);

        signalHeadComboBox = new JmriBeanComboBox(centralWidget);
        signalHeadComboBox->setObjectName(QStringLiteral("signalHeadComboBox"));

        horizontalLayout_8->addWidget(signalHeadComboBox);


        horizontalLayout_10->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        signalMastButton = new QCheckBox(centralWidget);
        signalMastButton->setObjectName(QStringLiteral("signalMastButton"));

        horizontalLayout_9->addWidget(signalMastButton);

        signalMastComboBox = new JmriBeanComboBox(centralWidget);
        signalMastComboBox->setObjectName(QStringLiteral("signalMastComboBox"));

        horizontalLayout_9->addWidget(signalMastComboBox);


        horizontalLayout_10->addLayout(horizontalLayout_9);

        iconLabelButton = new QCheckBox(centralWidget);
        iconLabelButton->setObjectName(QStringLiteral("iconLabelButton"));

        horizontalLayout_10->addWidget(iconLabelButton);


        verticalLayout->addLayout(horizontalLayout_10);

        editPanel = new QWidget(centralWidget);
        editPanel->setObjectName(QStringLiteral("editPanel"));

        verticalLayout->addWidget(editPanel);

        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
        textEdit->setSizePolicy(sizePolicy);
        textEdit->setMaximumSize(QSize(16777215, 42));

        verticalLayout->addWidget(textEdit);

        LayoutEditor->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(LayoutEditor);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1245, 19));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuOptions = new QMenu(menuBar);
        menuOptions->setObjectName(QStringLiteral("menuOptions"));
        menuShow_scrollbars = new QMenu(menuOptions);
        menuShow_scrollbars->setObjectName(QStringLiteral("menuShow_scrollbars"));
        menuShow_icon_tooltips = new QMenu(menuOptions);
        menuShow_icon_tooltips->setObjectName(QStringLiteral("menuShow_icon_tooltips"));
        menuSet_Background_color = new QMenu(menuOptions);
        menuSet_Background_color->setObjectName(QStringLiteral("menuSet_Background_color"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QStringLiteral("menuTools"));
        menuZoom = new QMenu(menuBar);
        menuZoom->setObjectName(QStringLiteral("menuZoom"));
        menuMarker = new QMenu(menuBar);
        menuMarker->setObjectName(QStringLiteral("menuMarker"));
        menuWindow = new QMenu(menuBar);
        menuWindow->setObjectName(QStringLiteral("menuWindow"));
        LayoutEditor->setMenuBar(menuBar);
        mainToolBar = new QToolBar(LayoutEditor);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setFont(font);
        LayoutEditor->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(LayoutEditor);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        LayoutEditor->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuOptions->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menuZoom->menuAction());
        menuBar->addAction(menuMarker->menuAction());
        menuBar->addAction(menuWindow->menuAction());
        menuFile->addAction(actionSave_panels);
        menuFile->addAction(actionDelete_this_panel);
        menuFile->addAction(actionLoad_XML);
        menuFile->addAction(actionLoad_Other_XML);
        menuFile->addAction(actionSave);
        menuOptions->addAction(actionEdit_mode);
        menuOptions->addAction(actionAllow_repositioning);
        menuOptions->addAction(actionAllow_layout_control);
        menuOptions->addAction(actionAllow_turnout_animation);
        menuOptions->addAction(actionShow_help_bar_in_edit_mode);
        menuOptions->addAction(actionShow_grid_in_edit_mode);
        menuOptions->addAction(actionSnap_to_grid_when_adding);
        menuOptions->addAction(actionSnap_to_grid_when_moving);
        menuOptions->addAction(menuShow_scrollbars->menuAction());
        menuOptions->addAction(menuShow_icon_tooltips->menuAction());
        menuOptions->addAction(actionEnable_antialiasing_smoother_lines);
        menuOptions->addSeparator();
        menuOptions->addAction(actionNew_title);
        menuOptions->addAction(actionAdd_background_image_2);
        menuOptions->addAction(menuSet_Background_color->menuAction());
        menuOptions->addAction(actionAdd_Fast_Clock);
        menuOptions->addAction(actionAdd_Turntable);
        menuOptions->addAction(actionAdd_reporter_label);
        menuOptions->addAction(actionEdit_track_width);
        menuOptions->addAction(actionMoveLayout);
        menuOptions->addAction(actionCalculate_bounds);
        menuShow_scrollbars->addAction(actionBoth_scrollbars);
        menuShow_scrollbars->addAction(actionNo_scrollbars);
        menuShow_scrollbars->addAction(actionHorizontal_only);
        menuShow_scrollbars->addAction(actionVertical_only);
        menuShow_icon_tooltips->addAction(actionNever);
        menuShow_icon_tooltips->addAction(actionAlways);
        menuShow_icon_tooltips->addAction(actionIn_edit_mode_only);
        menuShow_icon_tooltips->addAction(actionNot_in_edit_mode_only);
        menuTools->addAction(actionScale_Translate_track_diagram);
        menuTools->addAction(actionTranslate_Selection);
        menuTools->addAction(actionUndo_Translate_Selection);
        menuTools->addAction(actionUse_Program_Default_Turnout_size);
        menuTools->addSeparator();
        menuTools->addAction(actionSkip_unsignalled_Internal_Turnouts);
        menuTools->addAction(actionSet_Signals_at_Turnout);
        menuTools->addAction(actionSet_Signals_at_Block_Boundary);
        menuTools->addAction(actionSet_Signals_at_Crossover);
        menuTools->addAction(actionSet_Signals_at_Level_Crossing);
        menuTools->addAction(actionSet_SIgnals_at_Throat_to_Throat_Turnouts);
        menuTools->addAction(actionSet_Signals_at_Three_Way_Turnout);
        menuTools->addAction(actionSet_Signals_at_a_Slip);
        menuTools->addAction(actionEntry_Exit);
        menuZoom->addAction(actionNo_zoom);
        menuZoom->addAction(actionX_1_5);
        menuZoom->addAction(actionX_2_0);
        menuZoom->addAction(actionX_3_0);
        menuZoom->addAction(actionX_4_0);
        menuZoom->addSeparator();
        menuZoom->addAction(actionZoom_In);
        menuZoom->addAction(actionZoom_Out);
        menuZoom->addAction(actionZoom_to_fit);
        menuMarker->addAction(actionAdd_loco);
        menuMarker->addAction(actionAdd_loco_from_roster);
        menuMarker->addAction(actionRemove_markers);

        retranslateUi(LayoutEditor);

        QMetaObject::connectSlotsByName(LayoutEditor);
    } // setupUi

    void retranslateUi(QMainWindow *LayoutEditor)
    {
        LayoutEditor->setWindowTitle(QApplication::translate("LayoutEditor", "MyLayoutEditor", Q_NULLPTR));
        actionSave_panels->setText(QApplication::translate("LayoutEditor", "Save panels ...", Q_NULLPTR));
        actionDelete_this_panel->setText(QApplication::translate("LayoutEditor", "Delete this panel ...", Q_NULLPTR));
        actionEdit_mode->setText(QApplication::translate("LayoutEditor", "Edit mode", Q_NULLPTR));
        actionAllow_repositioning->setText(QApplication::translate("LayoutEditor", "Allow repositioning", Q_NULLPTR));
        actionAllow_layout_control->setText(QApplication::translate("LayoutEditor", "Allow layout control", Q_NULLPTR));
        actionAllow_turnout_animation->setText(QApplication::translate("LayoutEditor", "Allow turnout animation", Q_NULLPTR));
        actionShow_help_bar_in_edit_mode->setText(QApplication::translate("LayoutEditor", "Show help bar in edit mode", Q_NULLPTR));
        actionShow_grid_in_edit_mode->setText(QApplication::translate("LayoutEditor", "Show grid in edit mode", Q_NULLPTR));
        actionSnap_to_grid_when_adding->setText(QApplication::translate("LayoutEditor", "Snap to grid when adding", Q_NULLPTR));
        actionSnap_to_grid_when_moving->setText(QApplication::translate("LayoutEditor", "Snap to grid when moving", Q_NULLPTR));
        actionBoth_scrollbars->setText(QApplication::translate("LayoutEditor", "Both scrollbars", Q_NULLPTR));
        actionNo_scrollbars->setText(QApplication::translate("LayoutEditor", "No scrollbars", Q_NULLPTR));
        actionHorizontal_only->setText(QApplication::translate("LayoutEditor", "Horizontal only", Q_NULLPTR));
        actionVertical_only->setText(QApplication::translate("LayoutEditor", "Vertical only", Q_NULLPTR));
        actionNever->setText(QApplication::translate("LayoutEditor", "Never", Q_NULLPTR));
        actionAlways->setText(QApplication::translate("LayoutEditor", "Always", Q_NULLPTR));
        actionIn_edit_mode_only->setText(QApplication::translate("LayoutEditor", "In edit mode only", Q_NULLPTR));
        actionNot_in_edit_mode_only->setText(QApplication::translate("LayoutEditor", "Not in edit mode only", Q_NULLPTR));
        actionShow_turnout_circles->setText(QApplication::translate("LayoutEditor", "Show turnout circles", Q_NULLPTR));
        actionEnable_antialiasing_smoother_lines->setText(QApplication::translate("LayoutEditor", "Enable antialiasing (smoother lines)", Q_NULLPTR));
        actionNew_title->setText(QApplication::translate("LayoutEditor", "New title ...", Q_NULLPTR));
        actionNo_zoom->setText(QApplication::translate("LayoutEditor", "No zoom", Q_NULLPTR));
        actionX_1_5->setText(QApplication::translate("LayoutEditor", "x 1.5", Q_NULLPTR));
        actionX_2_0->setText(QApplication::translate("LayoutEditor", "x 2.0", Q_NULLPTR));
        actionX_3_0->setText(QApplication::translate("LayoutEditor", "x 3.0", Q_NULLPTR));
        actionX_4_0->setText(QApplication::translate("LayoutEditor", "x 4.0", Q_NULLPTR));
        actionAdd_loco->setText(QApplication::translate("LayoutEditor", "Add loco...", Q_NULLPTR));
        actionAdd_loco_from_roster->setText(QApplication::translate("LayoutEditor", "Add loco from roster...", Q_NULLPTR));
        actionRemove_markers->setText(QApplication::translate("LayoutEditor", "Remove markers", Q_NULLPTR));
        actionEdit_track_width->setText(QApplication::translate("LayoutEditor", "Edit track width", Q_NULLPTR));
        actionAdd_reporter_label->setText(QApplication::translate("LayoutEditor", "Add reporter label", Q_NULLPTR));
        actionPlaceholder->setText(QApplication::translate("LayoutEditor", "placeholder", Q_NULLPTR));
        actionPlaceholder_2->setText(QApplication::translate("LayoutEditor", "Placeholder", Q_NULLPTR));
        actionAdd_background_image_2->setText(QApplication::translate("LayoutEditor", "Add background image", Q_NULLPTR));
        actionLoad_xl->setText(QApplication::translate("LayoutEditor", "Load XML", Q_NULLPTR));
        actionLoad_XML->setText(QApplication::translate("LayoutEditor", "Load XML", Q_NULLPTR));
        actionPlaceholder_3->setText(QApplication::translate("LayoutEditor", "placeholder", Q_NULLPTR));
        actionPlaceholder_4->setText(QApplication::translate("LayoutEditor", "placeholder", Q_NULLPTR));
        actionLoad_Other_Xml->setText(QApplication::translate("LayoutEditor", "Load Other XML", Q_NULLPTR));
        actionLoad_Other_XML->setText(QApplication::translate("LayoutEditor", "Load Other XML", Q_NULLPTR));
        actionSave->setText(QApplication::translate("LayoutEditor", "Save", Q_NULLPTR));
        actionSave_as->setText(QApplication::translate("LayoutEditor", "Save as...", Q_NULLPTR));
        actionScale_Translate_track_diagram->setText(QApplication::translate("LayoutEditor", "Scale/Translate Track Diagram...", Q_NULLPTR));
        actionTranslate_Selection->setText(QApplication::translate("LayoutEditor", "Translate Selection", Q_NULLPTR));
        actionUndo_Translate_Selection->setText(QApplication::translate("LayoutEditor", "Undo Translate Selection", Q_NULLPTR));
        actionUse_Program_Default_Turnout_size->setText(QApplication::translate("LayoutEditor", "Use Program Default Turnout size", Q_NULLPTR));
        actionSkip_unsignalled_Internal_Turnouts->setText(QApplication::translate("LayoutEditor", "Skip Unsignalled Internal Turnouts", Q_NULLPTR));
        actionSet_Signals_at_Turnout->setText(QApplication::translate("LayoutEditor", "Set Signals at Turnout...", Q_NULLPTR));
        actionSet_Signals_at_Block_Boundary->setText(QApplication::translate("LayoutEditor", "Set Signals at Block Boundary...", Q_NULLPTR));
        actionSet_Signals_at_Crossover->setText(QApplication::translate("LayoutEditor", "Set Signals at Crossover...", Q_NULLPTR));
        actionSet_Signals_at_Level_Crossing->setText(QApplication::translate("LayoutEditor", "Set Signals at Level Crossing...", Q_NULLPTR));
        actionSet_SIgnals_at_Throat_to_Throat_Turnouts->setText(QApplication::translate("LayoutEditor", "Set SIgnals at Throat to Throat Turnouts...", Q_NULLPTR));
        actionSet_Signals_at_Three_Way_Turnout->setText(QApplication::translate("LayoutEditor", "Set Signals at 3-Way Turnout...", Q_NULLPTR));
        actionSet_Signals_at_a_Slip->setText(QApplication::translate("LayoutEditor", "Set Signals at a Slip...", Q_NULLPTR));
        actionEntry_Exit->setText(QApplication::translate("LayoutEditor", "Entry Exit...", Q_NULLPTR));
        actionAdd_Fast_Clock->setText(QApplication::translate("LayoutEditor", "Add Fast Clock", Q_NULLPTR));
        actionInit->setText(QApplication::translate("LayoutEditor", "Init", Q_NULLPTR));
        actionMoveLayout->setText(QApplication::translate("LayoutEditor", "MoveLayout", Q_NULLPTR));
        actionAdd_Turntable->setText(QApplication::translate("LayoutEditor", "Add Turntable", Q_NULLPTR));
        actionCalculate_bounds->setText(QApplication::translate("LayoutEditor", "Calculate bounds", Q_NULLPTR));
        x->setText(QApplication::translate("LayoutEditor", "Zoom In", Q_NULLPTR));
        y->setText(QApplication::translate("LayoutEditor", "Zoom Out", Q_NULLPTR));
        actionZoom_In->setText(QApplication::translate("LayoutEditor", "Zoom In", Q_NULLPTR));
        actionZoom_Out->setText(QApplication::translate("LayoutEditor", "Zoom Out", Q_NULLPTR));
        actionZoom_to_fit->setText(QApplication::translate("LayoutEditor", "Zoom to fit", Q_NULLPTR));
        label->setText(QApplication::translate("LayoutEditor", "Location -x:  ", Q_NULLPTR));
        xLabel->setText(QApplication::translate("LayoutEditor", "0000", Q_NULLPTR));
        label_2->setText(QApplication::translate("LayoutEditor", "y:", Q_NULLPTR));
        yLabel->setText(QApplication::translate("LayoutEditor", "0000", Q_NULLPTR));
        turnoutNameLabel->setText(QApplication::translate("LayoutEditor", "Turnout: Name", Q_NULLPTR));
        extraTurnoutLabel->setText(QApplication::translate("LayoutEditor", "Additional Name", Q_NULLPTR));
        label_4->setText(QApplication::translate("LayoutEditor", "Type", Q_NULLPTR));
        turnoutRHButton->setText(QApplication::translate("LayoutEditor", "RH", Q_NULLPTR));
        turnoutLHButton->setText(QApplication::translate("LayoutEditor", "LH", Q_NULLPTR));
        turnoutWYEButton->setText(QApplication::translate("LayoutEditor", "WYE", Q_NULLPTR));
        doubleXoverButton->setText(QApplication::translate("LayoutEditor", "Double Xover", Q_NULLPTR));
        rhXoverButton->setText(QApplication::translate("LayoutEditor", "RH Xover", Q_NULLPTR));
        lhXoverButton->setText(QApplication::translate("LayoutEditor", "LH Xover", Q_NULLPTR));
        layoutSingleSlipButton->setText(QApplication::translate("LayoutEditor", "Single Slip", Q_NULLPTR));
        layoutDoubleSlipButton->setText(QApplication::translate("LayoutEditor", "DoubleSlip", Q_NULLPTR));
        label_5->setText(QApplication::translate("LayoutEditor", "Rotation", Q_NULLPTR));
        blockNameLabel->setText(QApplication::translate("LayoutEditor", "Block: Name", Q_NULLPTR));
        highlightBlockCheckBox->setText(QApplication::translate("LayoutEditor", "Highlight Block", Q_NULLPTR));
        blockSensorNameLabel->setText(QApplication::translate("LayoutEditor", "Sensor", Q_NULLPTR));
        label_8->setText(QApplication::translate("LayoutEditor", "Track:", Q_NULLPTR));
        trackButton->setText(QApplication::translate("LayoutEditor", "Track Segment", Q_NULLPTR));
        levelXingButton->setText(QApplication::translate("LayoutEditor", "Level Crossing", Q_NULLPTR));
        chkDashed->setText(QApplication::translate("LayoutEditor", "Dashed", Q_NULLPTR));
        chkMainline->setText(QApplication::translate("LayoutEditor", "Mainline", Q_NULLPTR));
        label_6->setText(QApplication::translate("LayoutEditor", "Track Nodes:", Q_NULLPTR));
        chkEndBumper->setText(QApplication::translate("LayoutEditor", "End Bumper", Q_NULLPTR));
        chkAnchorPoint->setText(QApplication::translate("LayoutEditor", "Anchor Point", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        edgeButton->setToolTip(QApplication::translate("LayoutEditor", "<html><head/><body><p>Select to add an edge connector track node when next clicking with shift down.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        edgeButton->setText(QApplication::translate("LayoutEditor", "Edge Connector", Q_NULLPTR));
        label_7->setText(QApplication::translate("LayoutEditor", "Label:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        textLabelButton->setToolTip(QApplication::translate("LayoutEditor", "<html><head/><body><p>Select to add a label with the entered text when next clicking with shift down.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        textLabelButton->setText(QApplication::translate("LayoutEditor", "Text Label", Q_NULLPTR));
        memoryButton->setText(QApplication::translate("LayoutEditor", "Memory", Q_NULLPTR));
        blockContentsButton->setText(QApplication::translate("LayoutEditor", "BlockContents", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        blockContentsComboBox->setToolTip(QApplication::translate("LayoutEditor", "<html><head/><body><p>Select to add a Block label when next clicking with shift down.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        multiSensorButton->setText(QApplication::translate("LayoutEditor", "Multi-sensor", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        changeIconsButton->setToolTip(QApplication::translate("LayoutEditor", "<html><head/><body><p>Click to change icons used to represent sensors, signal head or label (whichever is checked at the right).</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        changeIconsButton->setText(QApplication::translate("LayoutEditor", "Change Icons...", Q_NULLPTR));
        sensorButton->setText(QApplication::translate("LayoutEditor", "Sensor Icon", Q_NULLPTR));
        signalButton->setText(QApplication::translate("LayoutEditor", "Signal Head Icon", Q_NULLPTR));
        signalMastButton->setText(QApplication::translate("LayoutEditor", "SignalMast Icon", Q_NULLPTR));
        iconLabelButton->setText(QApplication::translate("LayoutEditor", "Icon Label", Q_NULLPTR));
        textEdit->setHtml(QApplication::translate("LayoutEditor", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt;\">To add an item check item type, enter needed data then with shift down, click on panel -except track segment. To add a track segment, with shift down, click mouse on one connection point and drag to another connection point. To move an item, drag it with the right mouse button. To show it's popup menu, right click on it. </span></p></body></html>", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("LayoutEditor", "File", Q_NULLPTR));
        menuOptions->setTitle(QApplication::translate("LayoutEditor", "Options", Q_NULLPTR));
        menuShow_scrollbars->setTitle(QApplication::translate("LayoutEditor", "Show scrollbars", Q_NULLPTR));
        menuShow_icon_tooltips->setTitle(QApplication::translate("LayoutEditor", "Show icon tooltips", Q_NULLPTR));
        menuSet_Background_color->setTitle(QApplication::translate("LayoutEditor", "Set Background color", Q_NULLPTR));
        menuTools->setTitle(QApplication::translate("LayoutEditor", "Tools", Q_NULLPTR));
        menuZoom->setTitle(QApplication::translate("LayoutEditor", "Zoom", Q_NULLPTR));
        menuMarker->setTitle(QApplication::translate("LayoutEditor", "Marker", Q_NULLPTR));
        menuWindow->setTitle(QApplication::translate("LayoutEditor", "Window", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LayoutEditor: public Ui_LayoutEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAYOUTEDITOR_H
