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
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *xLabel;
    QLabel *label_2;
    QLineEdit *yLabel;
    QLabel *label_3;
    QLineEdit *edTurnoutName;
    QLabel *label_11;
    QLineEdit *edExtraName;
    QLabel *label_4;
    QCheckBox *chkRH;
    QCheckBox *chkLH;
    QCheckBox *chkWYE;
    QCheckBox *chkDoubleXover;
    QCheckBox *chkRHXover;
    QCheckBox *chkLHXover;
    QCheckBox *chkSingleSlip;
    QCheckBox *chkDoubleSlip;
    QLabel *label_5;
    QLineEdit *edRotation;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_6;
    QLineEdit *edBlockName;
    QLabel *label_7;
    QLineEdit *edOccupancySensor;
    QLabel *label_8;
    QCheckBox *chkLevelCrossing;
    QCheckBox *chkTrackSegment;
    QCheckBox *chkDashed;
    QCheckBox *chkMainline;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_9;
    QCheckBox *chkEndBumper;
    QCheckBox *chkAnchorPoint;
    QLabel *label_10;
    QCheckBox *chkTextLabel;
    QLineEdit *edTextLabel;
    QCheckBox *chkMemoryLabel;
    QLineEdit *edMemoryLabel;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *chkMultisensor;
    QPushButton *btnChange;
    QCheckBox *chkSensorIcon;
    QLineEdit *edSensorIcon;
    QCheckBox *chkSignalHeadIcon;
    QLineEdit *edSignalHeadIcon;
    QCheckBox *chkSignalMastIcon;
    QLineEdit *edSignalMastIcon;
    QCheckBox *chkIconLabel;
    QWidget *editPanel;
    QTextEdit *textEdit;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuOptions;
    QMenu *menuShow_scrollbars;
    QMenu *menuShow_icon_tooltips;
    QMenu *menuSet_Background_color;
    QMenu *menuSet_default_track_color;
    QMenu *menuSet_default_text_color;
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
        LayoutEditor->resize(1240, 426);
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
        actionSave->setEnabled(true);
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
        centralWidget = new QWidget(LayoutEditor);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        xLabel = new QLineEdit(centralWidget);
        xLabel->setObjectName(QStringLiteral("xLabel"));
        xLabel->setMinimumSize(QSize(0, 0));
        xLabel->setMaximumSize(QSize(50, 16777215));
        xLabel->setMaxLength(5);
        xLabel->setReadOnly(true);

        horizontalLayout->addWidget(xLabel);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        yLabel = new QLineEdit(centralWidget);
        yLabel->setObjectName(QStringLiteral("yLabel"));
        yLabel->setMaximumSize(QSize(50, 16777215));
        yLabel->setMaxLength(5);
        yLabel->setReadOnly(true);

        horizontalLayout->addWidget(yLabel);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);

        edTurnoutName = new QLineEdit(centralWidget);
        edTurnoutName->setObjectName(QStringLiteral("edTurnoutName"));

        horizontalLayout->addWidget(edTurnoutName);

        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QStringLiteral("label_11"));

        horizontalLayout->addWidget(label_11);

        edExtraName = new QLineEdit(centralWidget);
        edExtraName->setObjectName(QStringLiteral("edExtraName"));
        QFont font1;
        font1.setPointSize(11);
        edExtraName->setFont(font1);

        horizontalLayout->addWidget(edExtraName);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout->addWidget(label_4);

        chkRH = new QCheckBox(centralWidget);
        chkRH->setObjectName(QStringLiteral("chkRH"));

        horizontalLayout->addWidget(chkRH);

        chkLH = new QCheckBox(centralWidget);
        chkLH->setObjectName(QStringLiteral("chkLH"));

        horizontalLayout->addWidget(chkLH);

        chkWYE = new QCheckBox(centralWidget);
        chkWYE->setObjectName(QStringLiteral("chkWYE"));

        horizontalLayout->addWidget(chkWYE);

        chkDoubleXover = new QCheckBox(centralWidget);
        chkDoubleXover->setObjectName(QStringLiteral("chkDoubleXover"));

        horizontalLayout->addWidget(chkDoubleXover);

        chkRHXover = new QCheckBox(centralWidget);
        chkRHXover->setObjectName(QStringLiteral("chkRHXover"));

        horizontalLayout->addWidget(chkRHXover);

        chkLHXover = new QCheckBox(centralWidget);
        chkLHXover->setObjectName(QStringLiteral("chkLHXover"));

        horizontalLayout->addWidget(chkLHXover);

        chkSingleSlip = new QCheckBox(centralWidget);
        chkSingleSlip->setObjectName(QStringLiteral("chkSingleSlip"));

        horizontalLayout->addWidget(chkSingleSlip);

        chkDoubleSlip = new QCheckBox(centralWidget);
        chkDoubleSlip->setObjectName(QStringLiteral("chkDoubleSlip"));

        horizontalLayout->addWidget(chkDoubleSlip);

        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout->addWidget(label_5);

        edRotation = new QLineEdit(centralWidget);
        edRotation->setObjectName(QStringLiteral("edRotation"));
        edRotation->setInputMethodHints(Qt::ImhFormattedNumbersOnly);

        horizontalLayout->addWidget(edRotation);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_2->addWidget(label_6);

        edBlockName = new QLineEdit(centralWidget);
        edBlockName->setObjectName(QStringLiteral("edBlockName"));

        horizontalLayout_2->addWidget(edBlockName);

        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_2->addWidget(label_7);

        edOccupancySensor = new QLineEdit(centralWidget);
        edOccupancySensor->setObjectName(QStringLiteral("edOccupancySensor"));

        horizontalLayout_2->addWidget(edOccupancySensor);

        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_2->addWidget(label_8);

        chkLevelCrossing = new QCheckBox(centralWidget);
        chkLevelCrossing->setObjectName(QStringLiteral("chkLevelCrossing"));

        horizontalLayout_2->addWidget(chkLevelCrossing);

        chkTrackSegment = new QCheckBox(centralWidget);
        chkTrackSegment->setObjectName(QStringLiteral("chkTrackSegment"));

        horizontalLayout_2->addWidget(chkTrackSegment);

        chkDashed = new QCheckBox(centralWidget);
        chkDashed->setObjectName(QStringLiteral("chkDashed"));

        horizontalLayout_2->addWidget(chkDashed);

        chkMainline = new QCheckBox(centralWidget);
        chkMainline->setObjectName(QStringLiteral("chkMainline"));

        horizontalLayout_2->addWidget(chkMainline);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(2);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_3->addWidget(label_9);

        chkEndBumper = new QCheckBox(centralWidget);
        chkEndBumper->setObjectName(QStringLiteral("chkEndBumper"));

        horizontalLayout_3->addWidget(chkEndBumper);

        chkAnchorPoint = new QCheckBox(centralWidget);
        chkAnchorPoint->setObjectName(QStringLiteral("chkAnchorPoint"));

        horizontalLayout_3->addWidget(chkAnchorPoint);

        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_3->addWidget(label_10);

        chkTextLabel = new QCheckBox(centralWidget);
        chkTextLabel->setObjectName(QStringLiteral("chkTextLabel"));

        horizontalLayout_3->addWidget(chkTextLabel);

        edTextLabel = new QLineEdit(centralWidget);
        edTextLabel->setObjectName(QStringLiteral("edTextLabel"));

        horizontalLayout_3->addWidget(edTextLabel);

        chkMemoryLabel = new QCheckBox(centralWidget);
        chkMemoryLabel->setObjectName(QStringLiteral("chkMemoryLabel"));

        horizontalLayout_3->addWidget(chkMemoryLabel);

        edMemoryLabel = new QLineEdit(centralWidget);
        edMemoryLabel->setObjectName(QStringLiteral("edMemoryLabel"));

        horizontalLayout_3->addWidget(edMemoryLabel);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(2);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        chkMultisensor = new QCheckBox(centralWidget);
        chkMultisensor->setObjectName(QStringLiteral("chkMultisensor"));

        horizontalLayout_4->addWidget(chkMultisensor);

        btnChange = new QPushButton(centralWidget);
        btnChange->setObjectName(QStringLiteral("btnChange"));

        horizontalLayout_4->addWidget(btnChange);

        chkSensorIcon = new QCheckBox(centralWidget);
        chkSensorIcon->setObjectName(QStringLiteral("chkSensorIcon"));

        horizontalLayout_4->addWidget(chkSensorIcon);

        edSensorIcon = new QLineEdit(centralWidget);
        edSensorIcon->setObjectName(QStringLiteral("edSensorIcon"));

        horizontalLayout_4->addWidget(edSensorIcon);

        chkSignalHeadIcon = new QCheckBox(centralWidget);
        chkSignalHeadIcon->setObjectName(QStringLiteral("chkSignalHeadIcon"));

        horizontalLayout_4->addWidget(chkSignalHeadIcon);

        edSignalHeadIcon = new QLineEdit(centralWidget);
        edSignalHeadIcon->setObjectName(QStringLiteral("edSignalHeadIcon"));

        horizontalLayout_4->addWidget(edSignalHeadIcon);

        chkSignalMastIcon = new QCheckBox(centralWidget);
        chkSignalMastIcon->setObjectName(QStringLiteral("chkSignalMastIcon"));

        horizontalLayout_4->addWidget(chkSignalMastIcon);

        edSignalMastIcon = new QLineEdit(centralWidget);
        edSignalMastIcon->setObjectName(QStringLiteral("edSignalMastIcon"));

        horizontalLayout_4->addWidget(edSignalMastIcon);

        chkIconLabel = new QCheckBox(centralWidget);
        chkIconLabel->setObjectName(QStringLiteral("chkIconLabel"));

        horizontalLayout_4->addWidget(chkIconLabel);


        verticalLayout->addLayout(horizontalLayout_4);

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
        menuBar->setGeometry(QRect(0, 0, 1240, 19));
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
        menuSet_default_track_color = new QMenu(menuOptions);
        menuSet_default_track_color->setObjectName(QStringLiteral("menuSet_default_track_color"));
        menuSet_default_text_color = new QMenu(menuOptions);
        menuSet_default_text_color->setObjectName(QStringLiteral("menuSet_default_text_color"));
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
        menuFile->addAction(actionSave_as);
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
        menuOptions->addAction(menuSet_default_track_color->menuAction());
        menuOptions->addAction(menuSet_default_text_color->menuAction());
        menuOptions->addAction(actionMoveLayout);
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
        label->setText(QApplication::translate("LayoutEditor", "Location -x: ", Q_NULLPTR));
        label_2->setText(QApplication::translate("LayoutEditor", "y:", Q_NULLPTR));
        label_3->setText(QApplication::translate("LayoutEditor", "Turnout: Name", Q_NULLPTR));
        label_11->setText(QApplication::translate("LayoutEditor", "Additional Name", Q_NULLPTR));
        label_4->setText(QApplication::translate("LayoutEditor", "Type", Q_NULLPTR));
        chkRH->setText(QApplication::translate("LayoutEditor", "RH", Q_NULLPTR));
        chkLH->setText(QApplication::translate("LayoutEditor", "LH", Q_NULLPTR));
        chkWYE->setText(QApplication::translate("LayoutEditor", "WYE", Q_NULLPTR));
        chkDoubleXover->setText(QApplication::translate("LayoutEditor", "Double Xover", Q_NULLPTR));
        chkRHXover->setText(QApplication::translate("LayoutEditor", "RH Xover", Q_NULLPTR));
        chkLHXover->setText(QApplication::translate("LayoutEditor", "LH Xover", Q_NULLPTR));
        chkSingleSlip->setText(QApplication::translate("LayoutEditor", "Single Slip", Q_NULLPTR));
        chkDoubleSlip->setText(QApplication::translate("LayoutEditor", "DoubleSlip", Q_NULLPTR));
        label_5->setText(QApplication::translate("LayoutEditor", "Rotation", Q_NULLPTR));
        label_6->setText(QApplication::translate("LayoutEditor", "Block: Name", Q_NULLPTR));
        label_7->setText(QApplication::translate("LayoutEditor", "Occupancy Sensor", Q_NULLPTR));
        label_8->setText(QApplication::translate("LayoutEditor", "Track:", Q_NULLPTR));
        chkLevelCrossing->setText(QApplication::translate("LayoutEditor", "Level Crossing", Q_NULLPTR));
        chkTrackSegment->setText(QApplication::translate("LayoutEditor", "Track Segment", Q_NULLPTR));
        chkDashed->setText(QApplication::translate("LayoutEditor", "Dashed", Q_NULLPTR));
        chkMainline->setText(QApplication::translate("LayoutEditor", "Mainline", Q_NULLPTR));
        label_9->setText(QApplication::translate("LayoutEditor", "Track Nodes:", Q_NULLPTR));
        chkEndBumper->setText(QApplication::translate("LayoutEditor", "End Bumper", Q_NULLPTR));
        chkAnchorPoint->setText(QApplication::translate("LayoutEditor", "Anchor Point", Q_NULLPTR));
        label_10->setText(QApplication::translate("LayoutEditor", "Labels: ", Q_NULLPTR));
        chkTextLabel->setText(QApplication::translate("LayoutEditor", "Text Label", Q_NULLPTR));
        chkMemoryLabel->setText(QApplication::translate("LayoutEditor", "Memory Label", Q_NULLPTR));
        chkMultisensor->setText(QApplication::translate("LayoutEditor", "Multi-sensor", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        btnChange->setToolTip(QApplication::translate("LayoutEditor", "<html><head/><body><p>Click to change icons used to represent sensors, signal head or label (whichever is checked at the right).</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        btnChange->setText(QApplication::translate("LayoutEditor", "Change Icons...", Q_NULLPTR));
        chkSensorIcon->setText(QApplication::translate("LayoutEditor", "Sensor Icon", Q_NULLPTR));
        chkSignalHeadIcon->setText(QApplication::translate("LayoutEditor", "Signal Head Icon", Q_NULLPTR));
        chkSignalMastIcon->setText(QApplication::translate("LayoutEditor", "SignalMast Icon", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        edSignalMastIcon->setToolTip(QApplication::translate("LayoutEditor", "<html><head/><body><p>Select to add a signal mast icon when next clicking with shift down.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        chkIconLabel->setText(QApplication::translate("LayoutEditor", "Icon Label", Q_NULLPTR));
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
        menuSet_default_track_color->setTitle(QApplication::translate("LayoutEditor", "Set default track color", Q_NULLPTR));
        menuSet_default_text_color->setTitle(QApplication::translate("LayoutEditor", "Set default text color", Q_NULLPTR));
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
