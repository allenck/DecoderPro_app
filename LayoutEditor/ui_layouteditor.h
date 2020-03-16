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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
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
        mainToolBar = new QToolBar(LayoutEditor);
        mainToolBar->setObjectName(QLatin1String("mainToolBar"));
        mainToolBar->setFont(font);
        LayoutEditor->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(LayoutEditor);
        statusBar->setObjectName(QLatin1String("statusBar"));
        LayoutEditor->setStatusBar(statusBar);

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
    } // retranslateUi

};

namespace Ui {
    class LayoutEditor: public Ui_LayoutEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAYOUTEDITOR_H
