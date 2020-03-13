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
#include <namedbeancombobox.h>

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
    QWidget *toolBarWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_20;
    QHBoxLayout *horizontalLayout_21;
    QLabel *label_10;
    QLabel *xLabel;
    QLabel *label_11;
    QLabel *yLabel;
    QHBoxLayout *horizontalLayout_22;
    QLabel *turnoutNameLabel;
    NamedBeanComboBox *turnoutNameComboBox;
    QHBoxLayout *horizontalLayout_23;
    QLabel *extraTurnoutLabel;
    NamedBeanComboBox *extraTurnoutNameComboBox;
    QHBoxLayout *horizontalLayout_24;
    QHBoxLayout *horizontalLayout_25;
    QLabel *label_12;
    QCheckBox *turnoutRHButton;
    QCheckBox *turnoutLHButton;
    QCheckBox *turnoutWYEButton;
    QCheckBox *doubleXoverButton;
    QCheckBox *rhXoverButton;
    QCheckBox *lhXoverButton;
    QHBoxLayout *horizontalLayout_26;
    QCheckBox *layoutSingleSlipButton;
    QCheckBox *layoutDoubleSlipButton;
    QHBoxLayout *horizontalLayout_27;
    QLabel *label_13;
    QComboBox *rotationComboBox;
    QHBoxLayout *horizontalLayout_28;
    QHBoxLayout *horizontalLayout_29;
    QLabel *blockNameLabel;
    NamedBeanComboBox *blockIDComboBox;
    QCheckBox *highlightBlockCheckBox;
    QHBoxLayout *horizontalLayout_30;
    QLabel *blockSensorNameLabel;
    NamedBeanComboBox *blockSensorComboBox;
    QHBoxLayout *trackGroup2;
    QLabel *label_14;
    QCheckBox *trackButton;
    QCheckBox *levelXingButton;
    QHBoxLayout *trackSegmentPropertiesPanel;
    QCheckBox *chkDashed;
    QCheckBox *chkMainline;
    QHBoxLayout *horizontalLayout_31;
    QHBoxLayout *trackgroup1;
    QLabel *label_15;
    QCheckBox *chkEndBumper;
    QCheckBox *chkAnchorPoint;
    QCheckBox *edgeButton;
    QHBoxLayout *labelGroup1;
    QLabel *label_16;
    QCheckBox *textLabelButton;
    QLineEdit *textLabel;
    QHBoxLayout *horizontalLayout_32;
    QCheckBox *memoryButton;
    NamedBeanComboBox *textMemoryComboBox;
    QCheckBox *blockContentsButton;
    NamedBeanComboBox *blockContentsComboBox;
    QHBoxLayout *horizontalLayout_33;
    QHBoxLayout *horizontalLayout_34;
    QCheckBox *multiSensorButton;
    QPushButton *changeIconsButton;
    QHBoxLayout *horizontalLayout_35;
    QCheckBox *sensorButton;
    NamedBeanComboBox *sensorComboBox;
    QHBoxLayout *horizontalLayout_36;
    QCheckBox *signalButton;
    NamedBeanComboBox *signalHeadComboBox;
    QHBoxLayout *horizontalLayout_37;
    QCheckBox *signalMastButton;
    NamedBeanComboBox *signalMastComboBox;
    QCheckBox *iconLabelButton;
    QWidget *editPanel;
    QTextEdit *textEdit;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuOptions;
    QMenu *menuTools;
    QMenu *menuZoom;
    QMenu *menuMarker;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *LayoutEditor)
    {
        if (LayoutEditor->objectName().isEmpty())
            LayoutEditor->setObjectName(QLatin1String("LayoutEditor"));
        LayoutEditor->resize(1248, 426);
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
        toolBarWidget = new QWidget(centralWidget);
        toolBarWidget->setObjectName(QLatin1String("toolBarWidget"));
        verticalLayout_2 = new QVBoxLayout(toolBarWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QLatin1String("verticalLayout_2"));
        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setSpacing(6);
        horizontalLayout_20->setObjectName(QLatin1String("horizontalLayout_20"));
        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setSpacing(6);
        horizontalLayout_21->setObjectName(QLatin1String("horizontalLayout_21"));
        label_10 = new QLabel(toolBarWidget);
        label_10->setObjectName(QLatin1String("label_10"));

        horizontalLayout_21->addWidget(label_10);

        xLabel = new QLabel(toolBarWidget);
        xLabel->setObjectName(QLatin1String("xLabel"));

        horizontalLayout_21->addWidget(xLabel);

        label_11 = new QLabel(toolBarWidget);
        label_11->setObjectName(QLatin1String("label_11"));

        horizontalLayout_21->addWidget(label_11);

        yLabel = new QLabel(toolBarWidget);
        yLabel->setObjectName(QLatin1String("yLabel"));

        horizontalLayout_21->addWidget(yLabel);


        horizontalLayout_20->addLayout(horizontalLayout_21);

        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setSpacing(6);
        horizontalLayout_22->setObjectName(QLatin1String("horizontalLayout_22"));
        turnoutNameLabel = new QLabel(toolBarWidget);
        turnoutNameLabel->setObjectName(QLatin1String("turnoutNameLabel"));

        horizontalLayout_22->addWidget(turnoutNameLabel);

        turnoutNameComboBox = new NamedBeanComboBox(toolBarWidget);
        turnoutNameComboBox->setObjectName(QLatin1String("turnoutNameComboBox"));

        horizontalLayout_22->addWidget(turnoutNameComboBox);


        horizontalLayout_20->addLayout(horizontalLayout_22);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setSpacing(6);
        horizontalLayout_23->setObjectName(QLatin1String("horizontalLayout_23"));
        extraTurnoutLabel = new QLabel(toolBarWidget);
        extraTurnoutLabel->setObjectName(QLatin1String("extraTurnoutLabel"));

        horizontalLayout_23->addWidget(extraTurnoutLabel);

        extraTurnoutNameComboBox = new NamedBeanComboBox(toolBarWidget);
        extraTurnoutNameComboBox->setObjectName(QLatin1String("extraTurnoutNameComboBox"));

        horizontalLayout_23->addWidget(extraTurnoutNameComboBox);


        horizontalLayout_20->addLayout(horizontalLayout_23);

        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setSpacing(6);
        horizontalLayout_24->setObjectName(QLatin1String("horizontalLayout_24"));
        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setSpacing(6);
        horizontalLayout_25->setObjectName(QLatin1String("horizontalLayout_25"));
        label_12 = new QLabel(toolBarWidget);
        label_12->setObjectName(QLatin1String("label_12"));

        horizontalLayout_25->addWidget(label_12);

        turnoutRHButton = new QCheckBox(toolBarWidget);
        turnoutRHButton->setObjectName(QLatin1String("turnoutRHButton"));

        horizontalLayout_25->addWidget(turnoutRHButton);

        turnoutLHButton = new QCheckBox(toolBarWidget);
        turnoutLHButton->setObjectName(QLatin1String("turnoutLHButton"));

        horizontalLayout_25->addWidget(turnoutLHButton);

        turnoutWYEButton = new QCheckBox(toolBarWidget);
        turnoutWYEButton->setObjectName(QLatin1String("turnoutWYEButton"));

        horizontalLayout_25->addWidget(turnoutWYEButton);


        horizontalLayout_24->addLayout(horizontalLayout_25);

        doubleXoverButton = new QCheckBox(toolBarWidget);
        doubleXoverButton->setObjectName(QLatin1String("doubleXoverButton"));

        horizontalLayout_24->addWidget(doubleXoverButton);

        rhXoverButton = new QCheckBox(toolBarWidget);
        rhXoverButton->setObjectName(QLatin1String("rhXoverButton"));

        horizontalLayout_24->addWidget(rhXoverButton);

        lhXoverButton = new QCheckBox(toolBarWidget);
        lhXoverButton->setObjectName(QLatin1String("lhXoverButton"));

        horizontalLayout_24->addWidget(lhXoverButton);


        horizontalLayout_20->addLayout(horizontalLayout_24);

        horizontalLayout_26 = new QHBoxLayout();
        horizontalLayout_26->setSpacing(6);
        horizontalLayout_26->setObjectName(QLatin1String("horizontalLayout_26"));
        layoutSingleSlipButton = new QCheckBox(toolBarWidget);
        layoutSingleSlipButton->setObjectName(QLatin1String("layoutSingleSlipButton"));

        horizontalLayout_26->addWidget(layoutSingleSlipButton);

        layoutDoubleSlipButton = new QCheckBox(toolBarWidget);
        layoutDoubleSlipButton->setObjectName(QLatin1String("layoutDoubleSlipButton"));

        horizontalLayout_26->addWidget(layoutDoubleSlipButton);


        horizontalLayout_20->addLayout(horizontalLayout_26);

        horizontalLayout_27 = new QHBoxLayout();
        horizontalLayout_27->setSpacing(6);
        horizontalLayout_27->setObjectName(QLatin1String("horizontalLayout_27"));
        label_13 = new QLabel(toolBarWidget);
        label_13->setObjectName(QLatin1String("label_13"));

        horizontalLayout_27->addWidget(label_13);

        rotationComboBox = new QComboBox(toolBarWidget);
        rotationComboBox->setObjectName(QLatin1String("rotationComboBox"));

        horizontalLayout_27->addWidget(rotationComboBox);


        horizontalLayout_20->addLayout(horizontalLayout_27);


        verticalLayout_2->addLayout(horizontalLayout_20);

        horizontalLayout_28 = new QHBoxLayout();
        horizontalLayout_28->setSpacing(6);
        horizontalLayout_28->setObjectName(QLatin1String("horizontalLayout_28"));
        horizontalLayout_29 = new QHBoxLayout();
        horizontalLayout_29->setSpacing(6);
        horizontalLayout_29->setObjectName(QLatin1String("horizontalLayout_29"));
        blockNameLabel = new QLabel(toolBarWidget);
        blockNameLabel->setObjectName(QLatin1String("blockNameLabel"));

        horizontalLayout_29->addWidget(blockNameLabel);

        blockIDComboBox = new NamedBeanComboBox(toolBarWidget);
        blockIDComboBox->setObjectName(QLatin1String("blockIDComboBox"));

        horizontalLayout_29->addWidget(blockIDComboBox);

        highlightBlockCheckBox = new QCheckBox(toolBarWidget);
        highlightBlockCheckBox->setObjectName(QLatin1String("highlightBlockCheckBox"));

        horizontalLayout_29->addWidget(highlightBlockCheckBox);


        horizontalLayout_28->addLayout(horizontalLayout_29);

        horizontalLayout_30 = new QHBoxLayout();
        horizontalLayout_30->setSpacing(6);
        horizontalLayout_30->setObjectName(QLatin1String("horizontalLayout_30"));
        blockSensorNameLabel = new QLabel(toolBarWidget);
        blockSensorNameLabel->setObjectName(QLatin1String("blockSensorNameLabel"));

        horizontalLayout_30->addWidget(blockSensorNameLabel);

        blockSensorComboBox = new NamedBeanComboBox(toolBarWidget);
        blockSensorComboBox->setObjectName(QLatin1String("blockSensorComboBox"));

        horizontalLayout_30->addWidget(blockSensorComboBox);


        horizontalLayout_28->addLayout(horizontalLayout_30);

        trackGroup2 = new QHBoxLayout();
        trackGroup2->setSpacing(6);
        trackGroup2->setObjectName(QLatin1String("trackGroup2"));
        label_14 = new QLabel(toolBarWidget);
        label_14->setObjectName(QLatin1String("label_14"));

        trackGroup2->addWidget(label_14);

        trackButton = new QCheckBox(toolBarWidget);
        trackButton->setObjectName(QLatin1String("trackButton"));

        trackGroup2->addWidget(trackButton);

        levelXingButton = new QCheckBox(toolBarWidget);
        levelXingButton->setObjectName(QLatin1String("levelXingButton"));

        trackGroup2->addWidget(levelXingButton);


        horizontalLayout_28->addLayout(trackGroup2);

        trackSegmentPropertiesPanel = new QHBoxLayout();
        trackSegmentPropertiesPanel->setSpacing(6);
        trackSegmentPropertiesPanel->setObjectName(QLatin1String("trackSegmentPropertiesPanel"));
        chkDashed = new QCheckBox(toolBarWidget);
        chkDashed->setObjectName(QLatin1String("chkDashed"));

        trackSegmentPropertiesPanel->addWidget(chkDashed);

        chkMainline = new QCheckBox(toolBarWidget);
        chkMainline->setObjectName(QLatin1String("chkMainline"));

        trackSegmentPropertiesPanel->addWidget(chkMainline);


        horizontalLayout_28->addLayout(trackSegmentPropertiesPanel);


        verticalLayout_2->addLayout(horizontalLayout_28);

        horizontalLayout_31 = new QHBoxLayout();
        horizontalLayout_31->setSpacing(6);
        horizontalLayout_31->setObjectName(QLatin1String("horizontalLayout_31"));
        trackgroup1 = new QHBoxLayout();
        trackgroup1->setSpacing(6);
        trackgroup1->setObjectName(QLatin1String("trackgroup1"));
        label_15 = new QLabel(toolBarWidget);
        label_15->setObjectName(QLatin1String("label_15"));

        trackgroup1->addWidget(label_15);

        chkEndBumper = new QCheckBox(toolBarWidget);
        chkEndBumper->setObjectName(QLatin1String("chkEndBumper"));

        trackgroup1->addWidget(chkEndBumper);

        chkAnchorPoint = new QCheckBox(toolBarWidget);
        chkAnchorPoint->setObjectName(QLatin1String("chkAnchorPoint"));

        trackgroup1->addWidget(chkAnchorPoint);

        edgeButton = new QCheckBox(toolBarWidget);
        edgeButton->setObjectName(QLatin1String("edgeButton"));

        trackgroup1->addWidget(edgeButton);


        horizontalLayout_31->addLayout(trackgroup1);

        labelGroup1 = new QHBoxLayout();
        labelGroup1->setSpacing(6);
        labelGroup1->setObjectName(QLatin1String("labelGroup1"));
        label_16 = new QLabel(toolBarWidget);
        label_16->setObjectName(QLatin1String("label_16"));

        labelGroup1->addWidget(label_16);

        textLabelButton = new QCheckBox(toolBarWidget);
        textLabelButton->setObjectName(QLatin1String("textLabelButton"));

        labelGroup1->addWidget(textLabelButton);

        textLabel = new QLineEdit(toolBarWidget);
        textLabel->setObjectName(QLatin1String("textLabel"));

        labelGroup1->addWidget(textLabel);


        horizontalLayout_31->addLayout(labelGroup1);

        horizontalLayout_32 = new QHBoxLayout();
        horizontalLayout_32->setSpacing(6);
        horizontalLayout_32->setObjectName(QLatin1String("horizontalLayout_32"));
        memoryButton = new QCheckBox(toolBarWidget);
        memoryButton->setObjectName(QLatin1String("memoryButton"));

        horizontalLayout_32->addWidget(memoryButton);

        textMemoryComboBox = new NamedBeanComboBox(toolBarWidget);
        textMemoryComboBox->setObjectName(QLatin1String("textMemoryComboBox"));

        horizontalLayout_32->addWidget(textMemoryComboBox);


        horizontalLayout_31->addLayout(horizontalLayout_32);

        blockContentsButton = new QCheckBox(toolBarWidget);
        blockContentsButton->setObjectName(QLatin1String("blockContentsButton"));

        horizontalLayout_31->addWidget(blockContentsButton);

        blockContentsComboBox = new NamedBeanComboBox(toolBarWidget);
        blockContentsComboBox->setObjectName(QLatin1String("blockContentsComboBox"));

        horizontalLayout_31->addWidget(blockContentsComboBox);


        verticalLayout_2->addLayout(horizontalLayout_31);

        horizontalLayout_33 = new QHBoxLayout();
        horizontalLayout_33->setSpacing(6);
        horizontalLayout_33->setObjectName(QLatin1String("horizontalLayout_33"));
        horizontalLayout_34 = new QHBoxLayout();
        horizontalLayout_34->setSpacing(6);
        horizontalLayout_34->setObjectName(QLatin1String("horizontalLayout_34"));
        multiSensorButton = new QCheckBox(toolBarWidget);
        multiSensorButton->setObjectName(QLatin1String("multiSensorButton"));

        horizontalLayout_34->addWidget(multiSensorButton);

        changeIconsButton = new QPushButton(toolBarWidget);
        changeIconsButton->setObjectName(QLatin1String("changeIconsButton"));

        horizontalLayout_34->addWidget(changeIconsButton);


        horizontalLayout_33->addLayout(horizontalLayout_34);

        horizontalLayout_35 = new QHBoxLayout();
        horizontalLayout_35->setSpacing(6);
        horizontalLayout_35->setObjectName(QLatin1String("horizontalLayout_35"));
        sensorButton = new QCheckBox(toolBarWidget);
        sensorButton->setObjectName(QLatin1String("sensorButton"));

        horizontalLayout_35->addWidget(sensorButton);

        sensorComboBox = new NamedBeanComboBox(toolBarWidget);
        sensorComboBox->setObjectName(QLatin1String("sensorComboBox"));

        horizontalLayout_35->addWidget(sensorComboBox);


        horizontalLayout_33->addLayout(horizontalLayout_35);

        horizontalLayout_36 = new QHBoxLayout();
        horizontalLayout_36->setSpacing(6);
        horizontalLayout_36->setObjectName(QLatin1String("horizontalLayout_36"));
        signalButton = new QCheckBox(toolBarWidget);
        signalButton->setObjectName(QLatin1String("signalButton"));

        horizontalLayout_36->addWidget(signalButton);

        signalHeadComboBox = new NamedBeanComboBox(toolBarWidget);
        signalHeadComboBox->setObjectName(QLatin1String("signalHeadComboBox"));

        horizontalLayout_36->addWidget(signalHeadComboBox);


        horizontalLayout_33->addLayout(horizontalLayout_36);

        horizontalLayout_37 = new QHBoxLayout();
        horizontalLayout_37->setSpacing(6);
        horizontalLayout_37->setObjectName(QLatin1String("horizontalLayout_37"));
        signalMastButton = new QCheckBox(toolBarWidget);
        signalMastButton->setObjectName(QLatin1String("signalMastButton"));

        horizontalLayout_37->addWidget(signalMastButton);

        signalMastComboBox = new NamedBeanComboBox(toolBarWidget);
        signalMastComboBox->setObjectName(QLatin1String("signalMastComboBox"));

        horizontalLayout_37->addWidget(signalMastComboBox);


        horizontalLayout_33->addLayout(horizontalLayout_37);

        iconLabelButton = new QCheckBox(toolBarWidget);
        iconLabelButton->setObjectName(QLatin1String("iconLabelButton"));

        horizontalLayout_33->addWidget(iconLabelButton);


        verticalLayout_2->addLayout(horizontalLayout_33);


        verticalLayout->addWidget(toolBarWidget);

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
        menuBar->setGeometry(QRect(0, 0, 1248, 17));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QLatin1String("menuFile"));
        menuOptions = new QMenu(menuBar);
        menuOptions->setObjectName(QLatin1String("menuOptions"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QLatin1String("menuTools"));
        menuZoom = new QMenu(menuBar);
        menuZoom->setObjectName(QLatin1String("menuZoom"));
        menuMarker = new QMenu(menuBar);
        menuMarker->setObjectName(QLatin1String("menuMarker"));
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
        menuFile->addAction(actionSave_panels);
        menuFile->addAction(actionDelete_this_panel);
        menuFile->addAction(actionLoad_XML);
        menuFile->addAction(actionLoad_Other_XML);
        menuFile->addAction(actionSave);
        menuZoom->addSeparator();

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
        label_10->setText(QApplication::translate("LayoutEditor", "Location -x:  ", nullptr));
        xLabel->setText(QApplication::translate("LayoutEditor", "0000", nullptr));
        label_11->setText(QApplication::translate("LayoutEditor", "y:", nullptr));
        yLabel->setText(QApplication::translate("LayoutEditor", "0000", nullptr));
        turnoutNameLabel->setText(QApplication::translate("LayoutEditor", "Turnout: Name", nullptr));
        extraTurnoutLabel->setText(QApplication::translate("LayoutEditor", "Additional Name", nullptr));
        label_12->setText(QApplication::translate("LayoutEditor", "Type", nullptr));
        turnoutRHButton->setText(QApplication::translate("LayoutEditor", "RH", nullptr));
        turnoutLHButton->setText(QApplication::translate("LayoutEditor", "LH", nullptr));
        turnoutWYEButton->setText(QApplication::translate("LayoutEditor", "WYE", nullptr));
        doubleXoverButton->setText(QApplication::translate("LayoutEditor", "Double Xover", nullptr));
        rhXoverButton->setText(QApplication::translate("LayoutEditor", "RH Xover", nullptr));
        lhXoverButton->setText(QApplication::translate("LayoutEditor", "LH Xover", nullptr));
        layoutSingleSlipButton->setText(QApplication::translate("LayoutEditor", "Single Slip", nullptr));
        layoutDoubleSlipButton->setText(QApplication::translate("LayoutEditor", "DoubleSlip", nullptr));
        label_13->setText(QApplication::translate("LayoutEditor", "Rotation", nullptr));
        blockNameLabel->setText(QApplication::translate("LayoutEditor", "Block: Name", nullptr));
        highlightBlockCheckBox->setText(QApplication::translate("LayoutEditor", "Highlight Block", nullptr));
        blockSensorNameLabel->setText(QApplication::translate("LayoutEditor", "Sensor", nullptr));
        label_14->setText(QApplication::translate("LayoutEditor", "Track:", nullptr));
        trackButton->setText(QApplication::translate("LayoutEditor", "Track Segment", nullptr));
        levelXingButton->setText(QApplication::translate("LayoutEditor", "Level Crossing", nullptr));
        chkDashed->setText(QApplication::translate("LayoutEditor", "Dashed", nullptr));
        chkMainline->setText(QApplication::translate("LayoutEditor", "Mainline", nullptr));
        label_15->setText(QApplication::translate("LayoutEditor", "Track Nodes:", nullptr));
        chkEndBumper->setText(QApplication::translate("LayoutEditor", "End Bumper", nullptr));
        chkAnchorPoint->setText(QApplication::translate("LayoutEditor", "Anchor Point", nullptr));
#ifndef QT_NO_TOOLTIP
        edgeButton->setToolTip(QApplication::translate("LayoutEditor", "<html><head/><body><p>Select to add an edge connector track node when next clicking with shift down.</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        edgeButton->setText(QApplication::translate("LayoutEditor", "Edge Connector", nullptr));
        label_16->setText(QApplication::translate("LayoutEditor", "Label:", nullptr));
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
        menuTools->setTitle(QApplication::translate("LayoutEditor", "Tools", nullptr));
        menuZoom->setTitle(QApplication::translate("LayoutEditor", "Zoom", nullptr));
        menuMarker->setTitle(QApplication::translate("LayoutEditor", "Marker", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LayoutEditor: public Ui_LayoutEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAYOUTEDITOR_H
