/********************************************************************************
** Form generated from reading UI file 'layouteditor.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAYOUTEDITOR_H
#define UI_LAYOUTEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
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
            LayoutEditor->setObjectName(QLatin1String("LayoutEditor"));
        LayoutEditor->resize(1245, 426);
        QFont font;
        font.setPointSize(8);
        LayoutEditor->setFont(font);
        actionSave_panels = new QAction(LayoutEditor);
        actionSave_panels->setObjectName(QLatin1String("actionSave_panels"));
        actionDelete_this_panel = new QAction(LayoutEditor);
        actionDelete_this_panel->setObjectName(QLatin1String("actionDelete_this_panel"));
        actionEdit_mode = new QAction(LayoutEditor);
        actionEdit_mode->setObjectName(QLatin1String("actionEdit_mode"));
        actionEdit_mode->setCheckable(true);
        actionEdit_mode->setChecked(true);
        actionAllow_repositioning = new QAction(LayoutEditor);
        actionAllow_repositioning->setObjectName(QLatin1String("actionAllow_repositioning"));
        actionAllow_repositioning->setCheckable(true);
        actionAllow_layout_control = new QAction(LayoutEditor);
        actionAllow_layout_control->setObjectName(QLatin1String("actionAllow_layout_control"));
        actionAllow_layout_control->setCheckable(true);
        actionAllow_turnout_animation = new QAction(LayoutEditor);
        actionAllow_turnout_animation->setObjectName(QLatin1String("actionAllow_turnout_animation"));
        actionAllow_turnout_animation->setCheckable(true);
        actionShow_help_bar_in_edit_mode = new QAction(LayoutEditor);
        actionShow_help_bar_in_edit_mode->setObjectName(QLatin1String("actionShow_help_bar_in_edit_mode"));
        actionShow_help_bar_in_edit_mode->setCheckable(true);
        actionShow_grid_in_edit_mode = new QAction(LayoutEditor);
        actionShow_grid_in_edit_mode->setObjectName(QLatin1String("actionShow_grid_in_edit_mode"));
        actionShow_grid_in_edit_mode->setCheckable(true);
        actionSnap_to_grid_when_adding = new QAction(LayoutEditor);
        actionSnap_to_grid_when_adding->setObjectName(QLatin1String("actionSnap_to_grid_when_adding"));
        actionSnap_to_grid_when_adding->setCheckable(true);
        actionSnap_to_grid_when_moving = new QAction(LayoutEditor);
        actionSnap_to_grid_when_moving->setObjectName(QLatin1String("actionSnap_to_grid_when_moving"));
        actionSnap_to_grid_when_moving->setCheckable(true);
        actionBoth_scrollbars = new QAction(LayoutEditor);
        actionBoth_scrollbars->setObjectName(QLatin1String("actionBoth_scrollbars"));
        actionNo_scrollbars = new QAction(LayoutEditor);
        actionNo_scrollbars->setObjectName(QLatin1String("actionNo_scrollbars"));
        actionHorizontal_only = new QAction(LayoutEditor);
        actionHorizontal_only->setObjectName(QLatin1String("actionHorizontal_only"));
        actionVertical_only = new QAction(LayoutEditor);
        actionVertical_only->setObjectName(QLatin1String("actionVertical_only"));
        actionNever = new QAction(LayoutEditor);
        actionNever->setObjectName(QLatin1String("actionNever"));
        actionAlways = new QAction(LayoutEditor);
        actionAlways->setObjectName(QLatin1String("actionAlways"));
        actionIn_edit_mode_only = new QAction(LayoutEditor);
        actionIn_edit_mode_only->setObjectName(QLatin1String("actionIn_edit_mode_only"));
        actionNot_in_edit_mode_only = new QAction(LayoutEditor);
        actionNot_in_edit_mode_only->setObjectName(QLatin1String("actionNot_in_edit_mode_only"));
        actionShow_turnout_circles = new QAction(LayoutEditor);
        actionShow_turnout_circles->setObjectName(QLatin1String("actionShow_turnout_circles"));
        actionShow_turnout_circles->setCheckable(true);
        actionEnable_antialiasing_smoother_lines = new QAction(LayoutEditor);
        actionEnable_antialiasing_smoother_lines->setObjectName(QLatin1String("actionEnable_antialiasing_smoother_lines"));
        actionEnable_antialiasing_smoother_lines->setCheckable(true);
        actionNew_title = new QAction(LayoutEditor);
        actionNew_title->setObjectName(QLatin1String("actionNew_title"));
        actionNo_zoom = new QAction(LayoutEditor);
        actionNo_zoom->setObjectName(QLatin1String("actionNo_zoom"));
        actionNo_zoom->setCheckable(true);
        actionX_1_5 = new QAction(LayoutEditor);
        actionX_1_5->setObjectName(QLatin1String("actionX_1_5"));
        actionX_1_5->setCheckable(true);
        actionX_2_0 = new QAction(LayoutEditor);
        actionX_2_0->setObjectName(QLatin1String("actionX_2_0"));
        actionX_2_0->setCheckable(true);
        actionX_3_0 = new QAction(LayoutEditor);
        actionX_3_0->setObjectName(QLatin1String("actionX_3_0"));
        actionX_3_0->setCheckable(true);
        actionX_4_0 = new QAction(LayoutEditor);
        actionX_4_0->setObjectName(QLatin1String("actionX_4_0"));
        actionX_4_0->setCheckable(true);
        actionAdd_loco = new QAction(LayoutEditor);
        actionAdd_loco->setObjectName(QLatin1String("actionAdd_loco"));
        actionAdd_loco_from_roster = new QAction(LayoutEditor);
        actionAdd_loco_from_roster->setObjectName(QLatin1String("actionAdd_loco_from_roster"));
        actionRemove_markers = new QAction(LayoutEditor);
        actionRemove_markers->setObjectName(QLatin1String("actionRemove_markers"));
        actionEdit_track_width = new QAction(LayoutEditor);
        actionEdit_track_width->setObjectName(QLatin1String("actionEdit_track_width"));
        actionAdd_reporter_label = new QAction(LayoutEditor);
        actionAdd_reporter_label->setObjectName(QLatin1String("actionAdd_reporter_label"));
        actionPlaceholder = new QAction(LayoutEditor);
        actionPlaceholder->setObjectName(QLatin1String("actionPlaceholder"));
        actionPlaceholder_2 = new QAction(LayoutEditor);
        actionPlaceholder_2->setObjectName(QLatin1String("actionPlaceholder_2"));
        actionAdd_background_image_2 = new QAction(LayoutEditor);
        actionAdd_background_image_2->setObjectName(QLatin1String("actionAdd_background_image_2"));
        actionLoad_xl = new QAction(LayoutEditor);
        actionLoad_xl->setObjectName(QLatin1String("actionLoad_xl"));
        actionLoad_XML = new QAction(LayoutEditor);
        actionLoad_XML->setObjectName(QLatin1String("actionLoad_XML"));
        actionPlaceholder_3 = new QAction(LayoutEditor);
        actionPlaceholder_3->setObjectName(QLatin1String("actionPlaceholder_3"));
        actionPlaceholder_4 = new QAction(LayoutEditor);
        actionPlaceholder_4->setObjectName(QLatin1String("actionPlaceholder_4"));
        actionLoad_Other_Xml = new QAction(LayoutEditor);
        actionLoad_Other_Xml->setObjectName(QLatin1String("actionLoad_Other_Xml"));
        actionLoad_Other_XML = new QAction(LayoutEditor);
        actionLoad_Other_XML->setObjectName(QLatin1String("actionLoad_Other_XML"));
        actionSave = new QAction(LayoutEditor);
        actionSave->setObjectName(QLatin1String("actionSave"));
        actionSave->setEnabled(false);
        actionSave_as = new QAction(LayoutEditor);
        actionSave_as->setObjectName(QLatin1String("actionSave_as"));
        actionSave_as->setEnabled(true);
        actionScale_Translate_track_diagram = new QAction(LayoutEditor);
        actionScale_Translate_track_diagram->setObjectName(QLatin1String("actionScale_Translate_track_diagram"));
        actionTranslate_Selection = new QAction(LayoutEditor);
        actionTranslate_Selection->setObjectName(QLatin1String("actionTranslate_Selection"));
        actionUndo_Translate_Selection = new QAction(LayoutEditor);
        actionUndo_Translate_Selection->setObjectName(QLatin1String("actionUndo_Translate_Selection"));
        actionUse_Program_Default_Turnout_size = new QAction(LayoutEditor);
        actionUse_Program_Default_Turnout_size->setObjectName(QLatin1String("actionUse_Program_Default_Turnout_size"));
        actionSkip_unsignalled_Internal_Turnouts = new QAction(LayoutEditor);
        actionSkip_unsignalled_Internal_Turnouts->setObjectName(QLatin1String("actionSkip_unsignalled_Internal_Turnouts"));
        actionSkip_unsignalled_Internal_Turnouts->setCheckable(true);
        actionSet_Signals_at_Turnout = new QAction(LayoutEditor);
        actionSet_Signals_at_Turnout->setObjectName(QLatin1String("actionSet_Signals_at_Turnout"));
        actionSet_Signals_at_Block_Boundary = new QAction(LayoutEditor);
        actionSet_Signals_at_Block_Boundary->setObjectName(QLatin1String("actionSet_Signals_at_Block_Boundary"));
        actionSet_Signals_at_Crossover = new QAction(LayoutEditor);
        actionSet_Signals_at_Crossover->setObjectName(QLatin1String("actionSet_Signals_at_Crossover"));
        actionSet_Signals_at_Level_Crossing = new QAction(LayoutEditor);
        actionSet_Signals_at_Level_Crossing->setObjectName(QLatin1String("actionSet_Signals_at_Level_Crossing"));
        actionSet_Signals_at_Level_Crossing->setEnabled(true);
        actionSet_SIgnals_at_Throat_to_Throat_Turnouts = new QAction(LayoutEditor);
        actionSet_SIgnals_at_Throat_to_Throat_Turnouts->setObjectName(QLatin1String("actionSet_SIgnals_at_Throat_to_Throat_Turnouts"));
        actionSet_SIgnals_at_Throat_to_Throat_Turnouts->setEnabled(true);
        actionSet_Signals_at_Three_Way_Turnout = new QAction(LayoutEditor);
        actionSet_Signals_at_Three_Way_Turnout->setObjectName(QLatin1String("actionSet_Signals_at_Three_Way_Turnout"));
        actionSet_Signals_at_Three_Way_Turnout->setEnabled(true);
        actionSet_Signals_at_a_Slip = new QAction(LayoutEditor);
        actionSet_Signals_at_a_Slip->setObjectName(QLatin1String("actionSet_Signals_at_a_Slip"));
        actionSet_Signals_at_a_Slip->setEnabled(true);
        actionEntry_Exit = new QAction(LayoutEditor);
        actionEntry_Exit->setObjectName(QLatin1String("actionEntry_Exit"));
        actionEntry_Exit->setEnabled(true);
        actionAdd_Fast_Clock = new QAction(LayoutEditor);
        actionAdd_Fast_Clock->setObjectName(QLatin1String("actionAdd_Fast_Clock"));
        actionInit = new QAction(LayoutEditor);
        actionInit->setObjectName(QLatin1String("actionInit"));
        actionMoveLayout = new QAction(LayoutEditor);
        actionMoveLayout->setObjectName(QLatin1String("actionMoveLayout"));
        actionAdd_Turntable = new QAction(LayoutEditor);
        actionAdd_Turntable->setObjectName(QLatin1String("actionAdd_Turntable"));
        actionCalculate_bounds = new QAction(LayoutEditor);
        actionCalculate_bounds->setObjectName(QLatin1String("actionCalculate_bounds"));
        x = new QAction(LayoutEditor);
        x->setObjectName(QLatin1String("x"));
        y = new QAction(LayoutEditor);
        y->setObjectName(QLatin1String("y"));
        actionZoom_In = new QAction(LayoutEditor);
        actionZoom_In->setObjectName(QLatin1String("actionZoom_In"));
        actionZoom_Out = new QAction(LayoutEditor);
        actionZoom_Out->setObjectName(QLatin1String("actionZoom_Out"));
        actionZoom_to_fit = new QAction(LayoutEditor);
        actionZoom_to_fit->setObjectName(QLatin1String("actionZoom_to_fit"));
        centralWidget = new QWidget(LayoutEditor);
        centralWidget->setObjectName(QLatin1String("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QLatin1String("verticalLayout"));
        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setObjectName(QLatin1String("horizontalLayout_18"));
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QLatin1String("horizontalLayout_12"));
        label = new QLabel(centralWidget);
        label->setObjectName(QLatin1String("label"));

        horizontalLayout_12->addWidget(label);

        xLabel = new QLabel(centralWidget);
        xLabel->setObjectName(QLatin1String("xLabel"));

        horizontalLayout_12->addWidget(xLabel);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QLatin1String("label_2"));

        horizontalLayout_12->addWidget(label_2);

        yLabel = new QLabel(centralWidget);
        yLabel->setObjectName(QLatin1String("yLabel"));

        horizontalLayout_12->addWidget(yLabel);


        horizontalLayout_18->addLayout(horizontalLayout_12);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QLatin1String("horizontalLayout"));
        turnoutNameLabel = new QLabel(centralWidget);
        turnoutNameLabel->setObjectName(QLatin1String("turnoutNameLabel"));

        horizontalLayout->addWidget(turnoutNameLabel);

        turnoutNameComboBox = new JmriBeanComboBox(centralWidget);
        turnoutNameComboBox->setObjectName(QLatin1String("turnoutNameComboBox"));

        horizontalLayout->addWidget(turnoutNameComboBox);


        horizontalLayout_18->addLayout(horizontalLayout);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QLatin1String("horizontalLayout_13"));
        extraTurnoutLabel = new QLabel(centralWidget);
        extraTurnoutLabel->setObjectName(QLatin1String("extraTurnoutLabel"));

        horizontalLayout_13->addWidget(extraTurnoutLabel);

        extraTurnoutNameComboBox = new JmriBeanComboBox(centralWidget);
        extraTurnoutNameComboBox->setObjectName(QLatin1String("extraTurnoutNameComboBox"));

        horizontalLayout_13->addWidget(extraTurnoutNameComboBox);


        horizontalLayout_18->addLayout(horizontalLayout_13);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QLatin1String("horizontalLayout_15"));
        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QLatin1String("horizontalLayout_14"));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QLatin1String("label_4"));

        horizontalLayout_14->addWidget(label_4);

        turnoutRHButton = new QCheckBox(centralWidget);
        turnoutRHButton->setObjectName(QLatin1String("turnoutRHButton"));

        horizontalLayout_14->addWidget(turnoutRHButton);

        turnoutLHButton = new QCheckBox(centralWidget);
        turnoutLHButton->setObjectName(QLatin1String("turnoutLHButton"));

        horizontalLayout_14->addWidget(turnoutLHButton);

        turnoutWYEButton = new QCheckBox(centralWidget);
        turnoutWYEButton->setObjectName(QLatin1String("turnoutWYEButton"));

        horizontalLayout_14->addWidget(turnoutWYEButton);


        horizontalLayout_15->addLayout(horizontalLayout_14);

        doubleXoverButton = new QCheckBox(centralWidget);
        doubleXoverButton->setObjectName(QLatin1String("doubleXoverButton"));

        horizontalLayout_15->addWidget(doubleXoverButton);

        rhXoverButton = new QCheckBox(centralWidget);
        rhXoverButton->setObjectName(QLatin1String("rhXoverButton"));

        horizontalLayout_15->addWidget(rhXoverButton);

        lhXoverButton = new QCheckBox(centralWidget);
        lhXoverButton->setObjectName(QLatin1String("lhXoverButton"));

        horizontalLayout_15->addWidget(lhXoverButton);


        horizontalLayout_18->addLayout(horizontalLayout_15);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName(QLatin1String("horizontalLayout_16"));
        layoutSingleSlipButton = new QCheckBox(centralWidget);
        layoutSingleSlipButton->setObjectName(QLatin1String("layoutSingleSlipButton"));

        horizontalLayout_16->addWidget(layoutSingleSlipButton);

        layoutDoubleSlipButton = new QCheckBox(centralWidget);
        layoutDoubleSlipButton->setObjectName(QLatin1String("layoutDoubleSlipButton"));

        horizontalLayout_16->addWidget(layoutDoubleSlipButton);


        horizontalLayout_18->addLayout(horizontalLayout_16);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setObjectName(QLatin1String("horizontalLayout_17"));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QLatin1String("label_5"));

        horizontalLayout_17->addWidget(label_5);

        rotationComboBox = new QComboBox(centralWidget);
        rotationComboBox->setObjectName(QLatin1String("rotationComboBox"));

        horizontalLayout_17->addWidget(rotationComboBox);


        horizontalLayout_18->addLayout(horizontalLayout_17);


        verticalLayout->addLayout(horizontalLayout_18);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QLatin1String("horizontalLayout_11"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QLatin1String("horizontalLayout_2"));
        blockNameLabel = new QLabel(centralWidget);
        blockNameLabel->setObjectName(QLatin1String("blockNameLabel"));

        horizontalLayout_2->addWidget(blockNameLabel);

        blockIDComboBox = new JmriBeanComboBox(centralWidget);
        blockIDComboBox->setObjectName(QLatin1String("blockIDComboBox"));

        horizontalLayout_2->addWidget(blockIDComboBox);

        highlightBlockCheckBox = new QCheckBox(centralWidget);
        highlightBlockCheckBox->setObjectName(QLatin1String("highlightBlockCheckBox"));

        horizontalLayout_2->addWidget(highlightBlockCheckBox);


        horizontalLayout_11->addLayout(horizontalLayout_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QLatin1String("horizontalLayout_5"));
        blockSensorNameLabel = new QLabel(centralWidget);
        blockSensorNameLabel->setObjectName(QLatin1String("blockSensorNameLabel"));

        horizontalLayout_5->addWidget(blockSensorNameLabel);

        blockSensorComboBox = new JmriBeanComboBox(centralWidget);
        blockSensorComboBox->setObjectName(QLatin1String("blockSensorComboBox"));

        horizontalLayout_5->addWidget(blockSensorComboBox);


        horizontalLayout_11->addLayout(horizontalLayout_5);

        trackGroup2 = new QHBoxLayout();
        trackGroup2->setSpacing(6);
        trackGroup2->setObjectName(QLatin1String("trackGroup2"));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QLatin1String("label_8"));

        trackGroup2->addWidget(label_8);

        trackButton = new QCheckBox(centralWidget);
        trackButton->setObjectName(QLatin1String("trackButton"));

        trackGroup2->addWidget(trackButton);

        levelXingButton = new QCheckBox(centralWidget);
        levelXingButton->setObjectName(QLatin1String("levelXingButton"));

        trackGroup2->addWidget(levelXingButton);


        horizontalLayout_11->addLayout(trackGroup2);

        trackSegmentPropertiesPanel = new QHBoxLayout();
        trackSegmentPropertiesPanel->setSpacing(6);
        trackSegmentPropertiesPanel->setObjectName(QLatin1String("trackSegmentPropertiesPanel"));
        chkDashed = new QCheckBox(centralWidget);
        chkDashed->setObjectName(QLatin1String("chkDashed"));

        trackSegmentPropertiesPanel->addWidget(chkDashed);

        chkMainline = new QCheckBox(centralWidget);
        chkMainline->setObjectName(QLatin1String("chkMainline"));

        trackSegmentPropertiesPanel->addWidget(chkMainline);


        horizontalLayout_11->addLayout(trackSegmentPropertiesPanel);


        verticalLayout->addLayout(horizontalLayout_11);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QLatin1String("horizontalLayout_3"));
        trackgroup1 = new QHBoxLayout();
        trackgroup1->setSpacing(6);
        trackgroup1->setObjectName(QLatin1String("trackgroup1"));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QLatin1String("label_6"));

        trackgroup1->addWidget(label_6);

        chkEndBumper = new QCheckBox(centralWidget);
        chkEndBumper->setObjectName(QLatin1String("chkEndBumper"));

        trackgroup1->addWidget(chkEndBumper);

        chkAnchorPoint = new QCheckBox(centralWidget);
        chkAnchorPoint->setObjectName(QLatin1String("chkAnchorPoint"));

        trackgroup1->addWidget(chkAnchorPoint);

        edgeButton = new QCheckBox(centralWidget);
        edgeButton->setObjectName(QLatin1String("edgeButton"));

        trackgroup1->addWidget(edgeButton);


        horizontalLayout_3->addLayout(trackgroup1);

        labelGroup1 = new QHBoxLayout();
        labelGroup1->setSpacing(6);
        labelGroup1->setObjectName(QLatin1String("labelGroup1"));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QLatin1String("label_7"));

        labelGroup1->addWidget(label_7);

        textLabelButton = new QCheckBox(centralWidget);
        textLabelButton->setObjectName(QLatin1String("textLabelButton"));

        labelGroup1->addWidget(textLabelButton);

        textLabelTextField = new QLineEdit(centralWidget);
        textLabelTextField->setObjectName(QLatin1String("textLabelTextField"));

        labelGroup1->addWidget(textLabelTextField);


        horizontalLayout_3->addLayout(labelGroup1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QLatin1String("horizontalLayout_7"));
        memoryButton = new QCheckBox(centralWidget);
        memoryButton->setObjectName(QLatin1String("memoryButton"));

        horizontalLayout_7->addWidget(memoryButton);

        textMemoryComboBox = new JmriBeanComboBox(centralWidget);
        textMemoryComboBox->setObjectName(QLatin1String("textMemoryComboBox"));

        horizontalLayout_7->addWidget(textMemoryComboBox);


        horizontalLayout_3->addLayout(horizontalLayout_7);

        blockContentsButton = new QCheckBox(centralWidget);
        blockContentsButton->setObjectName(QLatin1String("blockContentsButton"));

        horizontalLayout_3->addWidget(blockContentsButton);

        blockContentsComboBox = new JmriBeanComboBox(centralWidget);
        blockContentsComboBox->setObjectName(QLatin1String("blockContentsComboBox"));

        horizontalLayout_3->addWidget(blockContentsComboBox);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QLatin1String("horizontalLayout_10"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QLatin1String("horizontalLayout_4"));
        multiSensorButton = new QCheckBox(centralWidget);
        multiSensorButton->setObjectName(QLatin1String("multiSensorButton"));

        horizontalLayout_4->addWidget(multiSensorButton);

        changeIconsButton = new QPushButton(centralWidget);
        changeIconsButton->setObjectName(QLatin1String("changeIconsButton"));

        horizontalLayout_4->addWidget(changeIconsButton);


        horizontalLayout_10->addLayout(horizontalLayout_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QLatin1String("horizontalLayout_6"));
        sensorButton = new QCheckBox(centralWidget);
        sensorButton->setObjectName(QLatin1String("sensorButton"));

        horizontalLayout_6->addWidget(sensorButton);

        sensorComboBox = new JmriBeanComboBox(centralWidget);
        sensorComboBox->setObjectName(QLatin1String("sensorComboBox"));

        horizontalLayout_6->addWidget(sensorComboBox);


        horizontalLayout_10->addLayout(horizontalLayout_6);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QLatin1String("horizontalLayout_8"));
        signalButton = new QCheckBox(centralWidget);
        signalButton->setObjectName(QLatin1String("signalButton"));

        horizontalLayout_8->addWidget(signalButton);

        signalHeadComboBox = new JmriBeanComboBox(centralWidget);
        signalHeadComboBox->setObjectName(QLatin1String("signalHeadComboBox"));

        horizontalLayout_8->addWidget(signalHeadComboBox);


        horizontalLayout_10->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QLatin1String("horizontalLayout_9"));
        signalMastButton = new QCheckBox(centralWidget);
        signalMastButton->setObjectName(QLatin1String("signalMastButton"));

        horizontalLayout_9->addWidget(signalMastButton);

        signalMastComboBox = new JmriBeanComboBox(centralWidget);
        signalMastComboBox->setObjectName(QLatin1String("signalMastComboBox"));

        horizontalLayout_9->addWidget(signalMastComboBox);


        horizontalLayout_10->addLayout(horizontalLayout_9);

        iconLabelButton = new QCheckBox(centralWidget);
        iconLabelButton->setObjectName(QLatin1String("iconLabelButton"));

        horizontalLayout_10->addWidget(iconLabelButton);


        verticalLayout->addLayout(horizontalLayout_10);

        editPanel = new QWidget(centralWidget);
        editPanel->setObjectName(QLatin1String("editPanel"));

        verticalLayout->addWidget(editPanel);

        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QLatin1String("textEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
        textEdit->setSizePolicy(sizePolicy);
        textEdit->setMaximumSize(QSize(16777215, 42));

        verticalLayout->addWidget(textEdit);

        LayoutEditor->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(LayoutEditor);
        menuBar->setObjectName(QLatin1String("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1245, 19));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QLatin1String("menuFile"));
        menuOptions = new QMenu(menuBar);
        menuOptions->setObjectName(QLatin1String("menuOptions"));
        menuShow_scrollbars = new QMenu(menuOptions);
        menuShow_scrollbars->setObjectName(QLatin1String("menuShow_scrollbars"));
        menuShow_icon_tooltips = new QMenu(menuOptions);
        menuShow_icon_tooltips->setObjectName(QLatin1String("menuShow_icon_tooltips"));
        menuSet_Background_color = new QMenu(menuOptions);
        menuSet_Background_color->setObjectName(QLatin1String("menuSet_Background_color"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QLatin1String("menuTools"));
        menuZoom = new QMenu(menuBar);
        menuZoom->setObjectName(QLatin1String("menuZoom"));
        menuMarker = new QMenu(menuBar);
        menuMarker->setObjectName(QLatin1String("menuMarker"));
        menuWindow = new QMenu(menuBar);
        menuWindow->setObjectName(QLatin1String("menuWindow"));
        LayoutEditor->setMenuBar(menuBar);
        mainToolBar = new QToolBar(LayoutEditor);
        mainToolBar->setObjectName(QLatin1String("mainToolBar"));
        mainToolBar->setFont(font);
        LayoutEditor->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(LayoutEditor);
        statusBar->setObjectName(QLatin1String("statusBar"));
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
        LayoutEditor->setWindowTitle(QApplication::translate("LayoutEditor", "MyLayoutEditor", nullptr));
        actionSave_panels->setText(QApplication::translate("LayoutEditor", "Save panels ...", nullptr));
        actionDelete_this_panel->setText(QApplication::translate("LayoutEditor", "Delete this panel ...", nullptr));
        actionEdit_mode->setText(QApplication::translate("LayoutEditor", "Edit mode", nullptr));
        actionAllow_repositioning->setText(QApplication::translate("LayoutEditor", "Allow repositioning", nullptr));
        actionAllow_layout_control->setText(QApplication::translate("LayoutEditor", "Allow layout control", nullptr));
        actionAllow_turnout_animation->setText(QApplication::translate("LayoutEditor", "Allow turnout animation", nullptr));
        actionShow_help_bar_in_edit_mode->setText(QApplication::translate("LayoutEditor", "Show help bar in edit mode", nullptr));
        actionShow_grid_in_edit_mode->setText(QApplication::translate("LayoutEditor", "Show grid in edit mode", nullptr));
        actionSnap_to_grid_when_adding->setText(QApplication::translate("LayoutEditor", "Snap to grid when adding", nullptr));
        actionSnap_to_grid_when_moving->setText(QApplication::translate("LayoutEditor", "Snap to grid when moving", nullptr));
        actionBoth_scrollbars->setText(QApplication::translate("LayoutEditor", "Both scrollbars", nullptr));
        actionNo_scrollbars->setText(QApplication::translate("LayoutEditor", "No scrollbars", nullptr));
        actionHorizontal_only->setText(QApplication::translate("LayoutEditor", "Horizontal only", nullptr));
        actionVertical_only->setText(QApplication::translate("LayoutEditor", "Vertical only", nullptr));
        actionNever->setText(QApplication::translate("LayoutEditor", "Never", nullptr));
        actionAlways->setText(QApplication::translate("LayoutEditor", "Always", nullptr));
        actionIn_edit_mode_only->setText(QApplication::translate("LayoutEditor", "In edit mode only", nullptr));
        actionNot_in_edit_mode_only->setText(QApplication::translate("LayoutEditor", "Not in edit mode only", nullptr));
        actionShow_turnout_circles->setText(QApplication::translate("LayoutEditor", "Show turnout circles", nullptr));
        actionEnable_antialiasing_smoother_lines->setText(QApplication::translate("LayoutEditor", "Enable antialiasing (smoother lines)", nullptr));
        actionNew_title->setText(QApplication::translate("LayoutEditor", "New title ...", nullptr));
        actionNo_zoom->setText(QApplication::translate("LayoutEditor", "No zoom", nullptr));
        actionX_1_5->setText(QApplication::translate("LayoutEditor", "x 1.5", nullptr));
        actionX_2_0->setText(QApplication::translate("LayoutEditor", "x 2.0", nullptr));
        actionX_3_0->setText(QApplication::translate("LayoutEditor", "x 3.0", nullptr));
        actionX_4_0->setText(QApplication::translate("LayoutEditor", "x 4.0", nullptr));
        actionAdd_loco->setText(QApplication::translate("LayoutEditor", "Add loco...", nullptr));
        actionAdd_loco_from_roster->setText(QApplication::translate("LayoutEditor", "Add loco from roster...", nullptr));
        actionRemove_markers->setText(QApplication::translate("LayoutEditor", "Remove markers", nullptr));
        actionEdit_track_width->setText(QApplication::translate("LayoutEditor", "Edit track width", nullptr));
        actionAdd_reporter_label->setText(QApplication::translate("LayoutEditor", "Add reporter label", nullptr));
        actionPlaceholder->setText(QApplication::translate("LayoutEditor", "placeholder", nullptr));
        actionPlaceholder_2->setText(QApplication::translate("LayoutEditor", "Placeholder", nullptr));
        actionAdd_background_image_2->setText(QApplication::translate("LayoutEditor", "Add background image", nullptr));
        actionLoad_xl->setText(QApplication::translate("LayoutEditor", "Load XML", nullptr));
        actionLoad_XML->setText(QApplication::translate("LayoutEditor", "Load XML", nullptr));
        actionPlaceholder_3->setText(QApplication::translate("LayoutEditor", "placeholder", nullptr));
        actionPlaceholder_4->setText(QApplication::translate("LayoutEditor", "placeholder", nullptr));
        actionLoad_Other_Xml->setText(QApplication::translate("LayoutEditor", "Load Other XML", nullptr));
        actionLoad_Other_XML->setText(QApplication::translate("LayoutEditor", "Load Other XML", nullptr));
        actionSave->setText(QApplication::translate("LayoutEditor", "Save", nullptr));
        actionSave_as->setText(QApplication::translate("LayoutEditor", "Save as...", nullptr));
        actionScale_Translate_track_diagram->setText(QApplication::translate("LayoutEditor", "Scale/Translate Track Diagram...", nullptr));
        actionTranslate_Selection->setText(QApplication::translate("LayoutEditor", "Translate Selection", nullptr));
        actionUndo_Translate_Selection->setText(QApplication::translate("LayoutEditor", "Undo Translate Selection", nullptr));
        actionUse_Program_Default_Turnout_size->setText(QApplication::translate("LayoutEditor", "Use Program Default Turnout size", nullptr));
        actionSkip_unsignalled_Internal_Turnouts->setText(QApplication::translate("LayoutEditor", "Skip Unsignalled Internal Turnouts", nullptr));
        actionSet_Signals_at_Turnout->setText(QApplication::translate("LayoutEditor", "Set Signals at Turnout...", nullptr));
        actionSet_Signals_at_Block_Boundary->setText(QApplication::translate("LayoutEditor", "Set Signals at Block Boundary...", nullptr));
        actionSet_Signals_at_Crossover->setText(QApplication::translate("LayoutEditor", "Set Signals at Crossover...", nullptr));
        actionSet_Signals_at_Level_Crossing->setText(QApplication::translate("LayoutEditor", "Set Signals at Level Crossing...", nullptr));
        actionSet_SIgnals_at_Throat_to_Throat_Turnouts->setText(QApplication::translate("LayoutEditor", "Set SIgnals at Throat to Throat Turnouts...", nullptr));
        actionSet_Signals_at_Three_Way_Turnout->setText(QApplication::translate("LayoutEditor", "Set Signals at 3-Way Turnout...", nullptr));
        actionSet_Signals_at_a_Slip->setText(QApplication::translate("LayoutEditor", "Set Signals at a Slip...", nullptr));
        actionEntry_Exit->setText(QApplication::translate("LayoutEditor", "Entry Exit...", nullptr));
        actionAdd_Fast_Clock->setText(QApplication::translate("LayoutEditor", "Add Fast Clock", nullptr));
        actionInit->setText(QApplication::translate("LayoutEditor", "Init", nullptr));
        actionMoveLayout->setText(QApplication::translate("LayoutEditor", "MoveLayout", nullptr));
        actionAdd_Turntable->setText(QApplication::translate("LayoutEditor", "Add Turntable", nullptr));
        actionCalculate_bounds->setText(QApplication::translate("LayoutEditor", "Calculate bounds", nullptr));
        x->setText(QApplication::translate("LayoutEditor", "Zoom In", nullptr));
        y->setText(QApplication::translate("LayoutEditor", "Zoom Out", nullptr));
        actionZoom_In->setText(QApplication::translate("LayoutEditor", "Zoom In", nullptr));
        actionZoom_Out->setText(QApplication::translate("LayoutEditor", "Zoom Out", nullptr));
        actionZoom_to_fit->setText(QApplication::translate("LayoutEditor", "Zoom to fit", nullptr));
        label->setText(QApplication::translate("LayoutEditor", "Location -x:  ", nullptr));
        xLabel->setText(QApplication::translate("LayoutEditor", "0000", nullptr));
        label_2->setText(QApplication::translate("LayoutEditor", "y:", nullptr));
        yLabel->setText(QApplication::translate("LayoutEditor", "0000", nullptr));
        turnoutNameLabel->setText(QApplication::translate("LayoutEditor", "Turnout: Name", nullptr));
        extraTurnoutLabel->setText(QApplication::translate("LayoutEditor", "Additional Name", nullptr));
        label_4->setText(QApplication::translate("LayoutEditor", "Type", nullptr));
        turnoutRHButton->setText(QApplication::translate("LayoutEditor", "RH", nullptr));
        turnoutLHButton->setText(QApplication::translate("LayoutEditor", "LH", nullptr));
        turnoutWYEButton->setText(QApplication::translate("LayoutEditor", "WYE", nullptr));
        doubleXoverButton->setText(QApplication::translate("LayoutEditor", "Double Xover", nullptr));
        rhXoverButton->setText(QApplication::translate("LayoutEditor", "RH Xover", nullptr));
        lhXoverButton->setText(QApplication::translate("LayoutEditor", "LH Xover", nullptr));
        layoutSingleSlipButton->setText(QApplication::translate("LayoutEditor", "Single Slip", nullptr));
        layoutDoubleSlipButton->setText(QApplication::translate("LayoutEditor", "DoubleSlip", nullptr));
        label_5->setText(QApplication::translate("LayoutEditor", "Rotation", nullptr));
        blockNameLabel->setText(QApplication::translate("LayoutEditor", "Block: Name", nullptr));
        highlightBlockCheckBox->setText(QApplication::translate("LayoutEditor", "Highlight Block", nullptr));
        blockSensorNameLabel->setText(QApplication::translate("LayoutEditor", "Sensor", nullptr));
        label_8->setText(QApplication::translate("LayoutEditor", "Track:", nullptr));
        trackButton->setText(QApplication::translate("LayoutEditor", "Track Segment", nullptr));
        levelXingButton->setText(QApplication::translate("LayoutEditor", "Level Crossing", nullptr));
        chkDashed->setText(QApplication::translate("LayoutEditor", "Dashed", nullptr));
        chkMainline->setText(QApplication::translate("LayoutEditor", "Mainline", nullptr));
        label_6->setText(QApplication::translate("LayoutEditor", "Track Nodes:", nullptr));
        chkEndBumper->setText(QApplication::translate("LayoutEditor", "End Bumper", nullptr));
        chkAnchorPoint->setText(QApplication::translate("LayoutEditor", "Anchor Point", nullptr));
#ifndef QT_NO_TOOLTIP
        edgeButton->setToolTip(QApplication::translate("LayoutEditor", "<html><head/><body><p>Select to add an edge connector track node when next clicking with shift down.</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        edgeButton->setText(QApplication::translate("LayoutEditor", "Edge Connector", nullptr));
        label_7->setText(QApplication::translate("LayoutEditor", "Label:", nullptr));
#ifndef QT_NO_TOOLTIP
        textLabelButton->setToolTip(QApplication::translate("LayoutEditor", "<html><head/><body><p>Select to add a label with the entered text when next clicking with shift down.</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        textLabelButton->setText(QApplication::translate("LayoutEditor", "Text Label", nullptr));
        memoryButton->setText(QApplication::translate("LayoutEditor", "Memory", nullptr));
        blockContentsButton->setText(QApplication::translate("LayoutEditor", "BlockContents", nullptr));
#ifndef QT_NO_TOOLTIP
        blockContentsComboBox->setToolTip(QApplication::translate("LayoutEditor", "<html><head/><body><p>Select to add a Block label when next clicking with shift down.</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        multiSensorButton->setText(QApplication::translate("LayoutEditor", "Multi-sensor", nullptr));
#ifndef QT_NO_TOOLTIP
        changeIconsButton->setToolTip(QApplication::translate("LayoutEditor", "<html><head/><body><p>Click to change icons used to represent sensors, signal head or label (whichever is checked at the right).</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        changeIconsButton->setText(QApplication::translate("LayoutEditor", "Change Icons...", nullptr));
        sensorButton->setText(QApplication::translate("LayoutEditor", "Sensor Icon", nullptr));
        signalButton->setText(QApplication::translate("LayoutEditor", "Signal Head Icon", nullptr));
        signalMastButton->setText(QApplication::translate("LayoutEditor", "SignalMast Icon", nullptr));
        iconLabelButton->setText(QApplication::translate("LayoutEditor", "Icon Label", nullptr));
        textEdit->setHtml(QApplication::translate("LayoutEditor", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt;\">To add an item check item type, enter needed data then with shift down, click on panel -except track segment. To add a track segment, with shift down, click mouse on one connection point and drag to another connection point. To move an item, drag it with the right mouse button. To show it's popup menu, right click on it. </span></p></body></html>", nullptr));
        menuFile->setTitle(QApplication::translate("LayoutEditor", "File", nullptr));
        menuOptions->setTitle(QApplication::translate("LayoutEditor", "Options", nullptr));
        menuShow_scrollbars->setTitle(QApplication::translate("LayoutEditor", "Show scrollbars", nullptr));
        menuShow_icon_tooltips->setTitle(QApplication::translate("LayoutEditor", "Show icon tooltips", nullptr));
        menuSet_Background_color->setTitle(QApplication::translate("LayoutEditor", "Set Background color", nullptr));
        menuTools->setTitle(QApplication::translate("LayoutEditor", "Tools", nullptr));
        menuZoom->setTitle(QApplication::translate("LayoutEditor", "Zoom", nullptr));
        menuMarker->setTitle(QApplication::translate("LayoutEditor", "Marker", nullptr));
        menuWindow->setTitle(QApplication::translate("LayoutEditor", "Window", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LayoutEditor: public Ui_LayoutEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAYOUTEDITOR_H
