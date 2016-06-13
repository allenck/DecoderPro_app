/********************************************************************************
** Form generated from reading UI file 'mylayouteditor.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYLAYOUTEDITOR_H
#define UI_MYLAYOUTEDITOR_H

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

class Ui_MyLayoutEditor
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

    void setupUi(QMainWindow *MyLayoutEditor)
    {
        if (MyLayoutEditor->objectName().isEmpty())
            MyLayoutEditor->setObjectName(QStringLiteral("MyLayoutEditor"));
        MyLayoutEditor->resize(1240, 426);
        QFont font;
        font.setPointSize(8);
        MyLayoutEditor->setFont(font);
        actionSave_panels = new QAction(MyLayoutEditor);
        actionSave_panels->setObjectName(QStringLiteral("actionSave_panels"));
        actionDelete_this_panel = new QAction(MyLayoutEditor);
        actionDelete_this_panel->setObjectName(QStringLiteral("actionDelete_this_panel"));
        actionEdit_mode = new QAction(MyLayoutEditor);
        actionEdit_mode->setObjectName(QStringLiteral("actionEdit_mode"));
        actionEdit_mode->setCheckable(true);
        actionEdit_mode->setChecked(true);
        actionAllow_repositioning = new QAction(MyLayoutEditor);
        actionAllow_repositioning->setObjectName(QStringLiteral("actionAllow_repositioning"));
        actionAllow_repositioning->setCheckable(true);
        actionAllow_layout_control = new QAction(MyLayoutEditor);
        actionAllow_layout_control->setObjectName(QStringLiteral("actionAllow_layout_control"));
        actionAllow_layout_control->setCheckable(true);
        actionAllow_turnout_animation = new QAction(MyLayoutEditor);
        actionAllow_turnout_animation->setObjectName(QStringLiteral("actionAllow_turnout_animation"));
        actionAllow_turnout_animation->setCheckable(true);
        actionShow_help_bar_in_edit_mode = new QAction(MyLayoutEditor);
        actionShow_help_bar_in_edit_mode->setObjectName(QStringLiteral("actionShow_help_bar_in_edit_mode"));
        actionShow_help_bar_in_edit_mode->setCheckable(true);
        actionShow_grid_in_edit_mode = new QAction(MyLayoutEditor);
        actionShow_grid_in_edit_mode->setObjectName(QStringLiteral("actionShow_grid_in_edit_mode"));
        actionShow_grid_in_edit_mode->setCheckable(true);
        actionSnap_to_grid_when_adding = new QAction(MyLayoutEditor);
        actionSnap_to_grid_when_adding->setObjectName(QStringLiteral("actionSnap_to_grid_when_adding"));
        actionSnap_to_grid_when_adding->setCheckable(true);
        actionSnap_to_grid_when_moving = new QAction(MyLayoutEditor);
        actionSnap_to_grid_when_moving->setObjectName(QStringLiteral("actionSnap_to_grid_when_moving"));
        actionSnap_to_grid_when_moving->setCheckable(true);
        actionBoth_scrollbars = new QAction(MyLayoutEditor);
        actionBoth_scrollbars->setObjectName(QStringLiteral("actionBoth_scrollbars"));
        actionNo_scrollbars = new QAction(MyLayoutEditor);
        actionNo_scrollbars->setObjectName(QStringLiteral("actionNo_scrollbars"));
        actionHorizontal_only = new QAction(MyLayoutEditor);
        actionHorizontal_only->setObjectName(QStringLiteral("actionHorizontal_only"));
        actionVertical_only = new QAction(MyLayoutEditor);
        actionVertical_only->setObjectName(QStringLiteral("actionVertical_only"));
        actionNever = new QAction(MyLayoutEditor);
        actionNever->setObjectName(QStringLiteral("actionNever"));
        actionAlways = new QAction(MyLayoutEditor);
        actionAlways->setObjectName(QStringLiteral("actionAlways"));
        actionIn_edit_mode_only = new QAction(MyLayoutEditor);
        actionIn_edit_mode_only->setObjectName(QStringLiteral("actionIn_edit_mode_only"));
        actionNot_in_edit_mode_only = new QAction(MyLayoutEditor);
        actionNot_in_edit_mode_only->setObjectName(QStringLiteral("actionNot_in_edit_mode_only"));
        actionShow_turnout_circles = new QAction(MyLayoutEditor);
        actionShow_turnout_circles->setObjectName(QStringLiteral("actionShow_turnout_circles"));
        actionShow_turnout_circles->setCheckable(true);
        actionEnable_antialiasing_smoother_lines = new QAction(MyLayoutEditor);
        actionEnable_antialiasing_smoother_lines->setObjectName(QStringLiteral("actionEnable_antialiasing_smoother_lines"));
        actionEnable_antialiasing_smoother_lines->setCheckable(true);
        actionNew_title = new QAction(MyLayoutEditor);
        actionNew_title->setObjectName(QStringLiteral("actionNew_title"));
        actionNo_zoom = new QAction(MyLayoutEditor);
        actionNo_zoom->setObjectName(QStringLiteral("actionNo_zoom"));
        actionNo_zoom->setCheckable(true);
        actionX_1_5 = new QAction(MyLayoutEditor);
        actionX_1_5->setObjectName(QStringLiteral("actionX_1_5"));
        actionX_1_5->setCheckable(true);
        actionX_2_0 = new QAction(MyLayoutEditor);
        actionX_2_0->setObjectName(QStringLiteral("actionX_2_0"));
        actionX_2_0->setCheckable(true);
        actionX_3_0 = new QAction(MyLayoutEditor);
        actionX_3_0->setObjectName(QStringLiteral("actionX_3_0"));
        actionX_3_0->setCheckable(true);
        actionX_4_0 = new QAction(MyLayoutEditor);
        actionX_4_0->setObjectName(QStringLiteral("actionX_4_0"));
        actionX_4_0->setCheckable(true);
        actionAdd_loco = new QAction(MyLayoutEditor);
        actionAdd_loco->setObjectName(QStringLiteral("actionAdd_loco"));
        actionAdd_loco_from_roster = new QAction(MyLayoutEditor);
        actionAdd_loco_from_roster->setObjectName(QStringLiteral("actionAdd_loco_from_roster"));
        actionRemove_markers = new QAction(MyLayoutEditor);
        actionRemove_markers->setObjectName(QStringLiteral("actionRemove_markers"));
        actionEdit_track_width = new QAction(MyLayoutEditor);
        actionEdit_track_width->setObjectName(QStringLiteral("actionEdit_track_width"));
        actionAdd_reporter_label = new QAction(MyLayoutEditor);
        actionAdd_reporter_label->setObjectName(QStringLiteral("actionAdd_reporter_label"));
        actionPlaceholder = new QAction(MyLayoutEditor);
        actionPlaceholder->setObjectName(QStringLiteral("actionPlaceholder"));
        actionPlaceholder_2 = new QAction(MyLayoutEditor);
        actionPlaceholder_2->setObjectName(QStringLiteral("actionPlaceholder_2"));
        actionAdd_background_image_2 = new QAction(MyLayoutEditor);
        actionAdd_background_image_2->setObjectName(QStringLiteral("actionAdd_background_image_2"));
        actionLoad_xl = new QAction(MyLayoutEditor);
        actionLoad_xl->setObjectName(QStringLiteral("actionLoad_xl"));
        actionLoad_XML = new QAction(MyLayoutEditor);
        actionLoad_XML->setObjectName(QStringLiteral("actionLoad_XML"));
        actionPlaceholder_3 = new QAction(MyLayoutEditor);
        actionPlaceholder_3->setObjectName(QStringLiteral("actionPlaceholder_3"));
        actionPlaceholder_4 = new QAction(MyLayoutEditor);
        actionPlaceholder_4->setObjectName(QStringLiteral("actionPlaceholder_4"));
        actionLoad_Other_Xml = new QAction(MyLayoutEditor);
        actionLoad_Other_Xml->setObjectName(QStringLiteral("actionLoad_Other_Xml"));
        actionLoad_Other_XML = new QAction(MyLayoutEditor);
        actionLoad_Other_XML->setObjectName(QStringLiteral("actionLoad_Other_XML"));
        actionSave = new QAction(MyLayoutEditor);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionSave->setEnabled(true);
        actionSave_as = new QAction(MyLayoutEditor);
        actionSave_as->setObjectName(QStringLiteral("actionSave_as"));
        actionSave_as->setEnabled(true);
        actionScale_Translate_track_diagram = new QAction(MyLayoutEditor);
        actionScale_Translate_track_diagram->setObjectName(QStringLiteral("actionScale_Translate_track_diagram"));
        actionTranslate_Selection = new QAction(MyLayoutEditor);
        actionTranslate_Selection->setObjectName(QStringLiteral("actionTranslate_Selection"));
        actionUndo_Translate_Selection = new QAction(MyLayoutEditor);
        actionUndo_Translate_Selection->setObjectName(QStringLiteral("actionUndo_Translate_Selection"));
        actionUse_Program_Default_Turnout_size = new QAction(MyLayoutEditor);
        actionUse_Program_Default_Turnout_size->setObjectName(QStringLiteral("actionUse_Program_Default_Turnout_size"));
        actionSkip_unsignalled_Internal_Turnouts = new QAction(MyLayoutEditor);
        actionSkip_unsignalled_Internal_Turnouts->setObjectName(QStringLiteral("actionSkip_unsignalled_Internal_Turnouts"));
        actionSkip_unsignalled_Internal_Turnouts->setCheckable(true);
        actionSet_Signals_at_Turnout = new QAction(MyLayoutEditor);
        actionSet_Signals_at_Turnout->setObjectName(QStringLiteral("actionSet_Signals_at_Turnout"));
        actionSet_Signals_at_Block_Boundary = new QAction(MyLayoutEditor);
        actionSet_Signals_at_Block_Boundary->setObjectName(QStringLiteral("actionSet_Signals_at_Block_Boundary"));
        actionSet_Signals_at_Crossover = new QAction(MyLayoutEditor);
        actionSet_Signals_at_Crossover->setObjectName(QStringLiteral("actionSet_Signals_at_Crossover"));
        actionSet_Signals_at_Level_Crossing = new QAction(MyLayoutEditor);
        actionSet_Signals_at_Level_Crossing->setObjectName(QStringLiteral("actionSet_Signals_at_Level_Crossing"));
        actionSet_Signals_at_Level_Crossing->setEnabled(true);
        actionSet_SIgnals_at_Throat_to_Throat_Turnouts = new QAction(MyLayoutEditor);
        actionSet_SIgnals_at_Throat_to_Throat_Turnouts->setObjectName(QStringLiteral("actionSet_SIgnals_at_Throat_to_Throat_Turnouts"));
        actionSet_SIgnals_at_Throat_to_Throat_Turnouts->setEnabled(true);
        actionSet_Signals_at_Three_Way_Turnout = new QAction(MyLayoutEditor);
        actionSet_Signals_at_Three_Way_Turnout->setObjectName(QStringLiteral("actionSet_Signals_at_Three_Way_Turnout"));
        actionSet_Signals_at_Three_Way_Turnout->setEnabled(false);
        actionSet_Signals_at_a_Slip = new QAction(MyLayoutEditor);
        actionSet_Signals_at_a_Slip->setObjectName(QStringLiteral("actionSet_Signals_at_a_Slip"));
        actionSet_Signals_at_a_Slip->setEnabled(true);
        actionEntry_Exit = new QAction(MyLayoutEditor);
        actionEntry_Exit->setObjectName(QStringLiteral("actionEntry_Exit"));
        actionEntry_Exit->setEnabled(true);
        actionAdd_Fast_Clock = new QAction(MyLayoutEditor);
        actionAdd_Fast_Clock->setObjectName(QStringLiteral("actionAdd_Fast_Clock"));
        actionInit = new QAction(MyLayoutEditor);
        actionInit->setObjectName(QStringLiteral("actionInit"));
        actionMoveLayout = new QAction(MyLayoutEditor);
        actionMoveLayout->setObjectName(QStringLiteral("actionMoveLayout"));
        actionAdd_Turntable = new QAction(MyLayoutEditor);
        actionAdd_Turntable->setObjectName(QStringLiteral("actionAdd_Turntable"));
        centralWidget = new QWidget(MyLayoutEditor);
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

        MyLayoutEditor->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MyLayoutEditor);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1240, 22));
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
        MyLayoutEditor->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MyLayoutEditor);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setFont(font);
        MyLayoutEditor->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MyLayoutEditor);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MyLayoutEditor->setStatusBar(statusBar);

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
        menuOptions->addAction(actionShow_turnout_circles);
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

        retranslateUi(MyLayoutEditor);

        QMetaObject::connectSlotsByName(MyLayoutEditor);
    } // setupUi

    void retranslateUi(QMainWindow *MyLayoutEditor)
    {
        MyLayoutEditor->setWindowTitle(QApplication::translate("MyLayoutEditor", "MyLayoutEditor", 0));
        actionSave_panels->setText(QApplication::translate("MyLayoutEditor", "Save panels ...", 0));
        actionDelete_this_panel->setText(QApplication::translate("MyLayoutEditor", "Delete this panel ...", 0));
        actionEdit_mode->setText(QApplication::translate("MyLayoutEditor", "Edit mode", 0));
        actionAllow_repositioning->setText(QApplication::translate("MyLayoutEditor", "Allow repositioning", 0));
        actionAllow_layout_control->setText(QApplication::translate("MyLayoutEditor", "Allow layout control", 0));
        actionAllow_turnout_animation->setText(QApplication::translate("MyLayoutEditor", "Allow turnout animation", 0));
        actionShow_help_bar_in_edit_mode->setText(QApplication::translate("MyLayoutEditor", "Show help bar in edit mode", 0));
        actionShow_grid_in_edit_mode->setText(QApplication::translate("MyLayoutEditor", "Show grid in edit mode", 0));
        actionSnap_to_grid_when_adding->setText(QApplication::translate("MyLayoutEditor", "Snap to grid when adding", 0));
        actionSnap_to_grid_when_moving->setText(QApplication::translate("MyLayoutEditor", "Snap to grid when moving", 0));
        actionBoth_scrollbars->setText(QApplication::translate("MyLayoutEditor", "Both scrollbars", 0));
        actionNo_scrollbars->setText(QApplication::translate("MyLayoutEditor", "No scrollbars", 0));
        actionHorizontal_only->setText(QApplication::translate("MyLayoutEditor", "Horizontal only", 0));
        actionVertical_only->setText(QApplication::translate("MyLayoutEditor", "Vertical only", 0));
        actionNever->setText(QApplication::translate("MyLayoutEditor", "Never", 0));
        actionAlways->setText(QApplication::translate("MyLayoutEditor", "Always", 0));
        actionIn_edit_mode_only->setText(QApplication::translate("MyLayoutEditor", "In edit mode only", 0));
        actionNot_in_edit_mode_only->setText(QApplication::translate("MyLayoutEditor", "Not in edit mode only", 0));
        actionShow_turnout_circles->setText(QApplication::translate("MyLayoutEditor", "Show turnout circles", 0));
        actionEnable_antialiasing_smoother_lines->setText(QApplication::translate("MyLayoutEditor", "Enable antialiasing (smoother lines)", 0));
        actionNew_title->setText(QApplication::translate("MyLayoutEditor", "New title ...", 0));
        actionNo_zoom->setText(QApplication::translate("MyLayoutEditor", "No zoom", 0));
        actionX_1_5->setText(QApplication::translate("MyLayoutEditor", "x 1.5", 0));
        actionX_2_0->setText(QApplication::translate("MyLayoutEditor", "x 2.0", 0));
        actionX_3_0->setText(QApplication::translate("MyLayoutEditor", "x 3.0", 0));
        actionX_4_0->setText(QApplication::translate("MyLayoutEditor", "x 4.0", 0));
        actionAdd_loco->setText(QApplication::translate("MyLayoutEditor", "Add loco...", 0));
        actionAdd_loco_from_roster->setText(QApplication::translate("MyLayoutEditor", "Add loco from roster...", 0));
        actionRemove_markers->setText(QApplication::translate("MyLayoutEditor", "Remove markers", 0));
        actionEdit_track_width->setText(QApplication::translate("MyLayoutEditor", "Edit track width", 0));
        actionAdd_reporter_label->setText(QApplication::translate("MyLayoutEditor", "Add reporter label", 0));
        actionPlaceholder->setText(QApplication::translate("MyLayoutEditor", "placeholder", 0));
        actionPlaceholder_2->setText(QApplication::translate("MyLayoutEditor", "Placeholder", 0));
        actionAdd_background_image_2->setText(QApplication::translate("MyLayoutEditor", "Add background image", 0));
        actionLoad_xl->setText(QApplication::translate("MyLayoutEditor", "Load XML", 0));
        actionLoad_XML->setText(QApplication::translate("MyLayoutEditor", "Load XML", 0));
        actionPlaceholder_3->setText(QApplication::translate("MyLayoutEditor", "placeholder", 0));
        actionPlaceholder_4->setText(QApplication::translate("MyLayoutEditor", "placeholder", 0));
        actionLoad_Other_Xml->setText(QApplication::translate("MyLayoutEditor", "Load Other XML", 0));
        actionLoad_Other_XML->setText(QApplication::translate("MyLayoutEditor", "Load Other XML", 0));
        actionSave->setText(QApplication::translate("MyLayoutEditor", "Save", 0));
        actionSave_as->setText(QApplication::translate("MyLayoutEditor", "Save as...", 0));
        actionScale_Translate_track_diagram->setText(QApplication::translate("MyLayoutEditor", "Scale/Translate Track Diagram...", 0));
        actionTranslate_Selection->setText(QApplication::translate("MyLayoutEditor", "Translate Selection", 0));
        actionUndo_Translate_Selection->setText(QApplication::translate("MyLayoutEditor", "Undo Translate Selection", 0));
        actionUse_Program_Default_Turnout_size->setText(QApplication::translate("MyLayoutEditor", "Use Program Default Turnout size", 0));
        actionSkip_unsignalled_Internal_Turnouts->setText(QApplication::translate("MyLayoutEditor", "Skip Unsignalled Internal Turnouts", 0));
        actionSet_Signals_at_Turnout->setText(QApplication::translate("MyLayoutEditor", "Set Signals at Turnout...", 0));
        actionSet_Signals_at_Block_Boundary->setText(QApplication::translate("MyLayoutEditor", "Set Signals at Block Boundary...", 0));
        actionSet_Signals_at_Crossover->setText(QApplication::translate("MyLayoutEditor", "Set Signals at Crossover...", 0));
        actionSet_Signals_at_Level_Crossing->setText(QApplication::translate("MyLayoutEditor", "Set Signals at Level Crossing...", 0));
        actionSet_SIgnals_at_Throat_to_Throat_Turnouts->setText(QApplication::translate("MyLayoutEditor", "Set SIgnals at Throat to Throat Turnouts...", 0));
        actionSet_Signals_at_Three_Way_Turnout->setText(QApplication::translate("MyLayoutEditor", "Set Signals at 3-Way Turnout...", 0));
        actionSet_Signals_at_a_Slip->setText(QApplication::translate("MyLayoutEditor", "Set Signals at a Slip...", 0));
        actionEntry_Exit->setText(QApplication::translate("MyLayoutEditor", "Entry Exit...", 0));
        actionAdd_Fast_Clock->setText(QApplication::translate("MyLayoutEditor", "Add Fast Clock", 0));
        actionInit->setText(QApplication::translate("MyLayoutEditor", "Init", 0));
        actionMoveLayout->setText(QApplication::translate("MyLayoutEditor", "MoveLayout", 0));
        actionAdd_Turntable->setText(QApplication::translate("MyLayoutEditor", "Add Turntable", 0));
        label->setText(QApplication::translate("MyLayoutEditor", "Location -x: ", 0));
        label_2->setText(QApplication::translate("MyLayoutEditor", "y:", 0));
        label_3->setText(QApplication::translate("MyLayoutEditor", "Turnout: Name", 0));
        label_11->setText(QApplication::translate("MyLayoutEditor", "Additional Name", 0));
        label_4->setText(QApplication::translate("MyLayoutEditor", "Type", 0));
        chkRH->setText(QApplication::translate("MyLayoutEditor", "RH", 0));
        chkLH->setText(QApplication::translate("MyLayoutEditor", "LH", 0));
        chkWYE->setText(QApplication::translate("MyLayoutEditor", "WYE", 0));
        chkDoubleXover->setText(QApplication::translate("MyLayoutEditor", "Double Xover", 0));
        chkRHXover->setText(QApplication::translate("MyLayoutEditor", "RH Xover", 0));
        chkLHXover->setText(QApplication::translate("MyLayoutEditor", "LH Xover", 0));
        chkSingleSlip->setText(QApplication::translate("MyLayoutEditor", "Single Slip", 0));
        chkDoubleSlip->setText(QApplication::translate("MyLayoutEditor", "DoubleSlip", 0));
        label_5->setText(QApplication::translate("MyLayoutEditor", "Rotation", 0));
        label_6->setText(QApplication::translate("MyLayoutEditor", "Block: Name", 0));
        label_7->setText(QApplication::translate("MyLayoutEditor", "Occupancy Sensor", 0));
        label_8->setText(QApplication::translate("MyLayoutEditor", "Track:", 0));
        chkLevelCrossing->setText(QApplication::translate("MyLayoutEditor", "Level Crossing", 0));
        chkTrackSegment->setText(QApplication::translate("MyLayoutEditor", "Track Segment", 0));
        chkDashed->setText(QApplication::translate("MyLayoutEditor", "Dashed", 0));
        chkMainline->setText(QApplication::translate("MyLayoutEditor", "Mainline", 0));
        label_9->setText(QApplication::translate("MyLayoutEditor", "Track Nodes:", 0));
        chkEndBumper->setText(QApplication::translate("MyLayoutEditor", "End Bumper", 0));
        chkAnchorPoint->setText(QApplication::translate("MyLayoutEditor", "Anchor Point", 0));
        label_10->setText(QApplication::translate("MyLayoutEditor", "Labels: ", 0));
        chkTextLabel->setText(QApplication::translate("MyLayoutEditor", "Text Label", 0));
        chkMemoryLabel->setText(QApplication::translate("MyLayoutEditor", "Memory Label", 0));
        chkMultisensor->setText(QApplication::translate("MyLayoutEditor", "Multi-sensor", 0));
#ifndef QT_NO_TOOLTIP
        btnChange->setToolTip(QApplication::translate("MyLayoutEditor", "<html><head/><body><p>Click to change icons used to represent sensors, signal head or label (whichever is checked at the right).</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        btnChange->setText(QApplication::translate("MyLayoutEditor", "Change Icons...", 0));
        chkSensorIcon->setText(QApplication::translate("MyLayoutEditor", "Sensor Icon", 0));
        chkSignalHeadIcon->setText(QApplication::translate("MyLayoutEditor", "Signal Head Icon", 0));
        chkSignalMastIcon->setText(QApplication::translate("MyLayoutEditor", "SignalMast Icon", 0));
#ifndef QT_NO_TOOLTIP
        edSignalMastIcon->setToolTip(QApplication::translate("MyLayoutEditor", "<html><head/><body><p>Select to add a signal mast icon when next clicking with shift down.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        chkIconLabel->setText(QApplication::translate("MyLayoutEditor", "Icon Label", 0));
        textEdit->setHtml(QApplication::translate("MyLayoutEditor", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt;\">To add an item check item type, enter needed data then with shift down, click on panel -except track segment. To add a track segment, with shift down, click mouse on one connection point and drag to another connection point. To move an item, drag it with the right mouse button. To show it's popup menu, right click on it. </span></p></body></html>", 0));
        menuFile->setTitle(QApplication::translate("MyLayoutEditor", "File", 0));
        menuOptions->setTitle(QApplication::translate("MyLayoutEditor", "Options", 0));
        menuShow_scrollbars->setTitle(QApplication::translate("MyLayoutEditor", "Show scrollbars", 0));
        menuShow_icon_tooltips->setTitle(QApplication::translate("MyLayoutEditor", "Show icon tooltips", 0));
        menuSet_Background_color->setTitle(QApplication::translate("MyLayoutEditor", "Set Background color", 0));
        menuSet_default_track_color->setTitle(QApplication::translate("MyLayoutEditor", "Set default track color", 0));
        menuSet_default_text_color->setTitle(QApplication::translate("MyLayoutEditor", "Set default text color", 0));
        menuTools->setTitle(QApplication::translate("MyLayoutEditor", "Tools", 0));
        menuZoom->setTitle(QApplication::translate("MyLayoutEditor", "Zoom", 0));
        menuMarker->setTitle(QApplication::translate("MyLayoutEditor", "Marker", 0));
        menuWindow->setTitle(QApplication::translate("MyLayoutEditor", "Window", 0));
    } // retranslateUi

};

namespace Ui {
    class MyLayoutEditor: public Ui_MyLayoutEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYLAYOUTEDITOR_H
