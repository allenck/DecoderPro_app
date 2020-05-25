#include "timetableframe.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "borderfactory.h"
#include "box.h"
#include "borderlayout.h"
#include <QSplitter>
#include "userpreferencesmanager.h"
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include "colorselectionmodel.h"
#include "spinnernumbermodel.h"
#include "gridbaglayout.h"
#include "layout.h"
#include "ttschedule.h"
#include "tttrain.h"
#include "colorutil.h"
#include "joptionpane.h"
#include "timetablexml.h"
#include "fileutil.h"
#include "jfilechooser.h"
#include "splitbuttoncolorchooserpanel.h"
#include "vptr.h"
#include "timetableprintgraph.h"
#include "scale.h"
#include "timetableimport.h"
#include <QTime>
#include "timetabledisplaygraph.h"

namespace TimeTable
{

/**
 * Create and maintain timetables.
 * <p>
 * A timetable describes the layout and trains along with the times that each train should be at specified locations.
 *
 *   Logical Schema
 * Layout
 *    Train Types
 *    Segments
 *        Stations
 *    Schedules
 *        Trains
 *           Stops
 *
 * @author Dave Sand Copyright (c) 2018
 */
// /*public*/ class TimeTableFrame extends jmri.util.JmriJFrame {

    /*public*/ /*static*/ /*final*/ QString TimeTableFrame::EMPTY_GRID = "EmptyGrid";

    /*public*/ TimeTableFrame::TimeTableFrame(QWidget *parent) : JmriJFrame(parent){
    }

    /*public*/ TimeTableFrame::TimeTableFrame(QString tt, QWidget *parent) : JmriJFrame(tt, true,true){
        //super(true, true);
        setTitle(tr("Timetable"));  // NOI18N
        InstanceManager::setDefault("TimeTableFrame", this);
        _dataMgr = TimeTableDataManager::getDataManager();
        detailChangeEvent = new TTFChangeListener(this);
        detailFocusEvent = new TTFFocusListener(this);
        stopStationItemEvent = new StopStationItemEventListener(this);
        layoutScaleItemEvent = new LayoutScaleItemEventListener(this);

        buildComponents();
        createFrame();
        createMenu();
        setEditMode(false);
        setShowReminder(false);

    }


    // ------------ Create Panel and components ------------

    /**
     * Create the main Timetable Window
     * The left side contains the timetable tree.
     * The right side contains the current edit grid.
     */
    /*private*/ void TimeTableFrame::createFrame() {
        QWidget* contentPane = new QWidget();
        //BorderLayout* contentPaneLayout = new BorderLayout();
        QVBoxLayout* contentPaneLayout = new QVBoxLayout();
        contentPane->setLayout(contentPaneLayout);
        setCentralWidget(contentPane);

        // ------------ Body - tree (left side) ------------
        JTree* treeContent = buildTree();
        //JScrollPane treeScroll = new JScrollPane(treeContent);

        // ------------ Body - detail (right side) ------------
        JPanel* detailPane = new JPanel();
        detailPane->setBorder(BorderFactory::createMatteBorder(0, 2, 0, 0, Qt::darkGray));
        detailPane->setLayout(new QVBoxLayout());//detailPane, Boxlayout->Y_AXIS));

        // ------------ Edit Detail Panel ------------
        makeDetailGrid(EMPTY_GRID);  // NOI18N

        JPanel* panel = new JPanel();
        panel->setLayout(new QHBoxLayout());//panel, Boxlayout->X_AXIS));

        _cancelAction = new QPushButton(tr("Cancel"));  // NOI18N
        _cancelAction->setToolTip(tr("HintCancelClose without saving the add/edit changesButton"));  // NOI18N
        panel->layout()->addWidget(_cancelAction);
        //_cancelAction.addActionListener((ActionEvent e) -> cancelPressed());
        connect(_cancelAction, &QPushButton::clicked, [=]{cancelPressed();});
        panel->layout()->addWidget(Box::createHorizontalStrut(10));

        _updateAction = new QPushButton(tr("Update"));  // NOI18N
        _updateAction->setToolTip(tr("Update/Save the changes"));  // NOI18N
        panel->layout()->addWidget(_updateAction);
        //_updateAction.addActionListener((ActionEvent e) -> updatePressed());
        connect(_updateAction, &QPushButton::clicked, [=]{updatePressed();});
        _detailFooter->layout()->addWidget(panel);

//        JPanel* detailEdit = new JPanel(new BorderLayout());
//        ((BorderLayout*)detailEdit->layout())->addWidget(_detailGrid, BorderLayout::North);
//        ((BorderLayout*)detailEdit->layout())->addWidget(_detailFooter, BorderLayout::South);
                JPanel* detailEdit = new JPanel(new QVBoxLayout());
                ((QVBoxLayout*)detailEdit->layout())->addWidget(_detailGrid, 1, Qt::AlignTop);
                ((QVBoxLayout*)detailEdit->layout())->addWidget(_detailFooter, 0, Qt::AlignBottom);
        detailPane->layout()->addWidget(detailEdit);

        //JSplitPane bodyPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT, treeScroll, detailPane);
        QSplitter* bodyPane = new QSplitter(Qt::Horizontal);
        bodyPane->addWidget(treeContent);
        bodyPane->addWidget(detailPane);
//        bodyPane->setDividerSize(10);
//        bodyPane->setResizeWeight(.35);
//        bodyPane->setOneTouchExpandable(true);
        //contentPaneLayout->addWidget(bodyPane, BorderLayout::Center);
        contentPaneLayout->addWidget(bodyPane, 1, Qt::AlignVCenter);

        // ------------ Footer ------------
//        JPanel* footer = new JPanel(new BorderLayout());
        JPanel* footer = new JPanel(new QHBoxLayout());
        _leftButtonBar = new JPanel(new FlowLayout());

        // ------------ Add Button ------------
        _addButton = new QPushButton(tr("New Layout"));    // NOI18N
        _addButton->setToolTip(tr("Add a new item"));       // NOI18N
//        _addButton->addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e) {
        connect(_addButton, &QPushButton::clicked, [=]{
                addPressed();
//            }
        });
        _addButtonPanel = new JPanel(new FlowLayout());
        _addButtonPanel->layout()->addWidget(_addButton);
        _leftButtonBar->layout()->addWidget(_addButtonPanel);

        // ------------ Delete Button ------------
        _deleteButton = new QPushButton(tr("Delete Layout")); // NOI18N
        _deleteButton->setToolTip(tr("Delete the selected item"));    // NOI18N
//        _deleteButton->addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e) {
        connect(_deleteButton, &QPushButton::clicked, [=]{
                deletePressed();
//            }
        });
        _deleteButtonPanel = new JPanel(new FlowLayout());
        _deleteButtonPanel->layout()->addWidget(_deleteButton);
        _deleteButtonPanel->setVisible(false);
        _leftButtonBar->layout()->addWidget(_deleteButtonPanel);

        // ------------ Move Buttons ------------
        JLabel* moveLabel = new JLabel(tr("Move"));      // NOI18N

        QPushButton* upButton = new QPushButton(tr("Up"));      // NOI18N
        upButton->setToolTip(tr("Move the selected item up one row"));         // NOI18N
        QPushButton* downButton = new QPushButton(tr("Down"));  // NOI18N
        downButton->setToolTip(tr("Move the selected item down one row"));     // NOI18N

//        upButton.addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e) {
        connect(upButton, &QPushButton::clicked, [=]{
                downButton->setEnabled(false);
                upButton->setEnabled(false);
                upPressed();
//            }
        });

//        downButton.addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e) {
        connect(downButton, &QPushButton::clicked, [=]{
                upButton->setEnabled(false);
                downButton->setEnabled(false);
                downPressed();
//            }
        });

        _moveButtonPanel = new JPanel(new FlowLayout());
        _moveButtonPanel->layout()->addWidget(moveLabel);
        _moveButtonPanel->layout()->addWidget(upButton);
        _moveButtonPanel->layout()->addWidget(new JLabel("|"));
        _moveButtonPanel->layout()->addWidget(downButton);
        _moveButtonPanel->setVisible(false);
        _leftButtonBar->layout()->addWidget(_moveButtonPanel);

        // ------------ Graph Buttons ------------
        JLabel*  graphLabel = new JLabel(tr("Graph"));      // NOI18N

        _displayButton = new QPushButton(tr("Display"));  // NOI18N
        _displayButton->setToolTip(tr("Display the train graph for this segment"));     // NOI18N
//        _displayButton.addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e) {
        connect(_displayButton, &QPushButton::clicked, [=]{
                graphPressed("Display");  // NOI18N
//            }
        });

        _printButton = new QPushButton(tr("Print"));  // NOI18N
        _printButton->setToolTip(tr("HintPrintButton"));     // NOI18N
//        _printButton.addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e) {
        connect(_printButton, &QPushButton::clicked, [=]{
                graphPressed("Print");  // NOI18N
//            }
        });

        _graphButtonPanel = new JPanel(new FlowLayout());
        _graphButtonPanel->layout()->addWidget(graphLabel);
        _graphButtonPanel->layout()->addWidget(_displayButton);
        _graphButtonPanel->layout()->addWidget(new JLabel("|"));
        _graphButtonPanel->layout()->addWidget(_printButton);
        _leftButtonBar->layout()->addWidget(_graphButtonPanel);

//        ((BorderLayout*)footer->layout())->addWidget(_leftButtonBar, BorderLayout::West);
        ((QHBoxLayout*)footer->layout())->addWidget(_leftButtonBar, 0, Qt::AlignLeft);

        JPanel* rightButtonBar = new JPanel(new FlowLayout());

        // ------------ Save Button ------------
        _saveButton = new QPushButton(tr("Save"));  // NOI18N
        _saveButton->setToolTip(tr("Save the timetables"));     // NOI18N
//        _saveButton.addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e) {
        connect(_saveButton, &QPushButton::clicked, [=]{
                savePressed();
//            }
        });
        JPanel* saveButtonPanel = new JPanel(new FlowLayout());
        saveButtonPanel->layout()->addWidget(_saveButton);
        rightButtonBar->layout()->addWidget(saveButtonPanel);

        // ------------ Done Button ------------
        QPushButton* doneButton = new QPushButton(tr("Done"));  // NOI18N
        doneButton->setToolTip(tr("Close the timetables window"));     // NOI18N
//        doneButton.addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e) {
        connect(doneButton, &QPushButton::clicked, [=]{
                donePressed();
//            }
        });
        JPanel* doneButtonPanel = new JPanel(new FlowLayout());
        doneButtonPanel->layout()->addWidget(doneButton);
        rightButtonBar->layout()->addWidget(doneButtonPanel);

//        ((BorderLayout*)footer->layout())->addWidget(rightButtonBar, BorderLayout::East);
        ((QHBoxLayout*)footer->layout())->addWidget(rightButtonBar, 0, Qt::AlignRight);
//        contentPaneLayout->addWidget(footer, BorderLayout::South);
        contentPaneLayout->addWidget(footer, 0, Qt::AlignBottom);
//        contentPane->setLayout(contentPaneLayout);
//        setCentralWidget(contentPane);

//        addWindowListener(new java.awt.event.WindowAdapter() {
//            @Override
//            /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//                donePressed();
//            }
//        });
        addWindowListener(new TTFWindowListener(this));
        setDefaultCloseOperation(JFrame::DO_NOTHING_ON_CLOSE);

        pack();
        _addButtonPanel->setVisible(false);
        _deleteButtonPanel->setVisible(false);
        _graphButtonPanel->setVisible(false);
    }

    /**
     * Create a Options/Tools menu.
     * - Option: Show train times on the graph.
     * - Option: Enable two page graph printing.
     * - Tool: Import a SchedGen data file.
     * - Tool: Import a CSV data file.
     * - Tool: Export a CSV data file.
     * Include the standard Windows and Help menu bar items.
     */
    void TimeTableFrame::createMenu() {
        _showTrainTimes = ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->
                getSimplePreferenceState("jmri.jmrit.timetable:TrainTimes");      // NOI18N

        QAction* trainTime = new QAction(tr("Display train times"),this);  // NOI18N
        trainTime->setCheckable(true);
        trainTime->setChecked(_showTrainTimes);
        //trainTime.addActionListener((ActionEvent event) -> {
        connect(trainTime, &QAction::triggered, [=]{
            _showTrainTimes = trainTime->isChecked();
            ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->
                    setSimplePreferenceState("jmri.jmrit.timetable:TrainTimes", _showTrainTimes);  // NOI18N
        });

        _twoPage = ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->
                getSimplePreferenceState("jmri.jmrit.timetable:TwoPage");      // NOI18N

        QAction* twoPage = new QAction(tr("Print train graph using two pages"),this);  // NOI18N
        twoPage->setCheckable(true);
        twoPage->setChecked(_twoPage);
//        twoPage.addActionListener((ActionEvent event) -> {
        connect(twoPage, &QAction::triggered, [=]{
            _twoPage = twoPage->isChecked();
            ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->
                    setSimplePreferenceState("jmri.jmrit.timetable:TwoPage", _twoPage);  // NOI18N
        });

        QAction* impsgn = new QAction(tr("Import SGN file..."),this);  // NOI18N
        //impsgn.addActionListener((ActionEvent event) -> importPressed());
        connect(impsgn, &QAction::triggered, [=]{importPressed();});

        QAction* impcsv = new QAction(tr("Import CSV file..."),this);  // NOI18N
        //impcsv.addActionListener((ActionEvent event) -> importCsvPressed());
        connect(impcsv, &QAction::triggered, [=]{importCsvPressed();});

        QAction* impopr = new QAction(tr("Import from OperationsPro..."),this);  // NOI18N
        //impopr.addActionListener((ActionEvent event) -> importFromOperationsPressed());
        connect(impsgn, &QAction::triggered, [=]{importFromOperationsPressed();});

        QAction* expcsv = new QAction(tr("Export CSV file..."));  // NOI18N
        //expcsv.addActionListener((ActionEvent event) -> exportCsvPressed());
        connect(impsgn, &QAction::triggered, [=]{exportCsvPressed();});

        QMenu* ttMenu = new QMenu(tr("Timetable"));  // NOI18N
        ttMenu->addAction(trainTime);
        ttMenu->addSeparator();
        ttMenu->addAction(twoPage);
        ttMenu->addSeparator();
        ttMenu->addAction(impsgn);
        ttMenu->addAction(impcsv);
        ttMenu->addAction(impopr);
        ttMenu->addAction(expcsv);

        QMenuBar* menuBar = new QMenuBar();
        menuBar->addMenu(ttMenu);
        setMenuBar(menuBar);

        //setup Help menu
        addHelpMenu("html.tools.TimeTable", true);  // NOI18N
    }

    /**
     * Initialize components.
     * Add Focus and Change listeners to activate edit mode.
     * Create the color selector for train types.
     */
    void TimeTableFrame::buildComponents() {
        // Layout
        _editLayoutName = new JTextField(20);
        _editLayoutName,setObjectName("_editLayoutName");
        _editScale = new JComboBox();
        _editScale->setObjectName("_editScale");
        _editScale->addItemListener(layoutScaleItemEvent);
        _editFastClock = new JTextField(5);
        _editFastClock->setObjectName("_editFastClock");
        _editThrottles = new JTextField(5);
        _editThrottles->setObjectName("_editThrottles");
        _editMetric = new JCheckBox();
        _editMetric->setObjectName("_editMetric");
        _showScaleMK = new JLabel();

        _editLayoutName->addFocusListener(detailFocusEvent);
        _editScale->addFocusListener(detailFocusEvent);
        _editFastClock->addFocusListener(detailFocusEvent);
        _editThrottles->addFocusListener(detailFocusEvent);
#if 1
        _editMetric->addChangeListener(detailChangeEvent);
#endif
        // TrainType
        _editTrainTypeName = new JTextField(20);
        _editTrainTypeName->setObjectName("_editTrainTypeName");
        _editTrainTypeColor = new JColorChooser(Qt::black);
        _editTrainTypeColor->setPreviewPanel(new JPanel()); // remove the preview panel
        QVector<AbstractColorChooserPanel*> editTypeColorPanels = {new SplitButtonColorChooserPanel()};
        _editTrainTypeColor->setChooserPanels(&editTypeColorPanels);

        _editTrainTypeName->addFocusListener(detailFocusEvent);
        _editTrainTypeColor->getSelectionModel()->addChangeListener(detailChangeEvent);

        // Segment
        _editSegmentName = new JTextField(20);
        _editSegmentName->setObjectName("_editSegmentName");

//        _editSegmentName->addFocusListener(detailFocusEvent);

        // Station
        _editStationName = new JTextField(20);
        _editStationName->setObjectName("_editStationName");
        _editDistance = new JTextField(5);
        _editDoubleTrack = new JCheckBox();
        _editSidings = new JSpinner(new SpinnerNumberModel(0, 0, QVariant(), 1));
        _editStaging = new JSpinner(new SpinnerNumberModel(0, 0, QVariant(), 1));

        _editStationName->addFocusListener(detailFocusEvent);
        _editDistance->addFocusListener(detailFocusEvent);
#if 1
        _editDoubleTrack->addChangeListener(detailChangeEvent);
#endif
        _editSidings->addChangeListener(detailChangeEvent);
        _editStaging->addChangeListener(detailChangeEvent);

        // Schedule
        _editScheduleName = new JTextField(20);
        _editScheduleName->setObjectName("_editScheduleName");
        _editEffDate = new JTextField(10);
        _editStartHour = new JSpinner(new SpinnerNumberModel(0, 0, 23, 1));
        _editDuration = new JSpinner(new SpinnerNumberModel(24, 1, 24, 1));

        _editScheduleName->addFocusListener(detailFocusEvent);
        _editEffDate->addFocusListener(detailFocusEvent);
        _editStartHour->addChangeListener(detailChangeEvent);
        _editDuration->addChangeListener(detailChangeEvent);

        // Train
        _editTrainName = new JTextField(10);
        _editTrainDesc = new JTextField(20);
        _editTrainType = new JComboBox();
        _editDefaultSpeed = new JTextField(5);
        _editTrainStartTime = new JTextField(5);
        _editThrottle = new JSpinner(new SpinnerNumberModel(0, 0, QVariant(), 1));
        _editTrainNotes = new JTextArea(4, 30);
        _showRouteDuration = new JLabel();

        _editTrainName->addFocusListener(detailFocusEvent);
        _editTrainDesc->addFocusListener(detailFocusEvent);
        _editTrainType->addFocusListener(detailFocusEvent);
        _editDefaultSpeed->addFocusListener(detailFocusEvent);
        _editTrainStartTime->addFocusListener(detailFocusEvent);
        _editThrottle->addChangeListener(detailChangeEvent);
#if 1
        _editTrainNotes->addFocusListener(detailFocusEvent);
#endif
        // Stop
        _showStopSeq = new JLabel();
        _editStopStation = new JComboBox();
        _editStopDuration = new JTextField(5);
        _editNextSpeed = new JTextField(5);
        _editStagingTrack = new JSpinner(new SpinnerNumberModel(0, 0, QVariant(), 1));
        _editStopNotes = new JTextArea(4, 30);
        _showArriveTime = new JLabel();
        _showDepartTime = new JLabel();

        _editStopStation->addFocusListener(detailFocusEvent);
#if 1
        _editStopStation->addItemListener(stopStationItemEvent);
#endif
        _editStopDuration->addFocusListener(detailFocusEvent);
        _editNextSpeed->addFocusListener(detailFocusEvent);
        _editStagingTrack->addChangeListener(detailChangeEvent);
#if 1
        _editStopNotes->addFocusListener(detailFocusEvent);
#endif
    }

    /**
     * Enable edit mode.  Used for JTextFields and JComboBoxs.
     */
//    /*transient*/ FocusListener* detailFocusEvent = new TTFFocusListener(this);
//{
//        @Override
//        /*public*/ void focusGained(FocusEvent e) {
//            if (!_editActive) {
//                setEditMode(true);
//            }
//        }

//        @Override
//        /*public*/ void focusLost(FocusEvent e) {
//        }
//    };

//    /**
//     * Enable edit mode.  Used for JCheckBoxs, JSpinners and JColorChoosers.
//     */
//    /*transient*/ ChangeListener* detailChangeEvent = new TTFChangeListener(this);
//    {
//        @Override
//        /*public*/ void stateChanged(ChangeEvent e) {
//            if (!_editActive) {
//                setEditMode(true);
//            }
//        }
//    };
#if 1
//    /**
//     * Change the max spinner value based on the station data.
//     * The number of staging tracks varies depending on the selected station->
//     */
//    /*transient*/ ItemListener* stopStationItemEvent = new StopStationItemEventListener(this);
//{
//        @Override
//        /*public*/ void itemStateChanged(ItemEvent e) {
//            if (e.getStateChange() == ItemEvent.SELECTED) {
//                TimeTableDataManager::SegmentStation segmentStation = (TimeTableDataManager::SegmentStation) e.getItem();
//                int stagingTracks = _dataMgr->getStation(segmentstation->getStationId()).getStaging();
//                Stop stop = _dataMgr->getStop(_curNodeId);
//                if (stop->getStagingTrack() <= stagingTracks) {
//                    _editStagingTrack.setModel(new SpinnerNumberModel(stop->getStagingTrack(), 0, stagingTracks, 1));
//                }
//            }
//        }
//    };

//    /**
//     * If the custom scale item is selected provide a dialog to set the scale ratio
//     */
//    /*transient*/ ItemListener* layoutScaleItemEvent = new LayoutScaleItemEventListener(this);
//{
//        @Override
//        /*public*/ void itemStateChanged(ItemEvent e) {
//            if (e.getStateChange() == ItemEvent.SELECTED) {
//                if (_editScale.hasFocus()) {
//                    Scale scale = (Scale) _editScale.getSelectedItem();
//                    if (scale.getScaleName() == ("CUSTOM")) {  // NOI18N
//                        String ans = JOptionPane::showInputDialog(
//                                tr("ScaleRatioChange"),  // NOI18N
//                                scale.getScaleRatio()
//                                );
//                        if (ans != null) {
//                            try {
//                                double newRatio = Double.parseDouble(ans);
//                                scale.setScaleRatio(newRatio);
//                            } catch (java.lang.IllegalArgumentException
//                                    | java.beans.PropertyVetoException ex) {
//                                log->warn("Unable to change custom ratio: {}", ex.getMessage());  // NOI18N
//                                JOptionPane::showMessageDialog(null,
//                                        tr("NumberFormatError", ans, "Custom ratio"),  // NOI18N
//                                        tr("Warning"),  // NOI18N
//                                        JOptionPane::WARNING_MESSAGE);
//                                Layout layout = _dataMgr->getLayout(_curNodeId);
//                                _editScale->setCheckedItem(layout->getScale());
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    };
#endif
    // ------------ Create GridBag panels ------------

    /**
     * Build new GridBag content. The grid panel is hidden, emptied, re-built and
     * made visible.
     *
     * @param gridType The type of grid to create
     */
    void TimeTableFrame::makeDetailGrid(QString gridType) {
     if(!_detailGrid->layout())
      _detailGrid->setLayout(new QVBoxLayout());
        _detailGrid->setVisible(false);
        //_detailGrid.removeAll();
//        QWidgetList l = _detailGrid->findChildren<QWidget*>();
//        foreach(QWidget* w, l)
//        {
//         _detailGrid->layout()->removeWidget(w);
//         delete w;
//        }
        QLayoutItem* item;
        while ( ( item = _detailGrid->layout()->takeAt( 0 ) ) != NULL )
        {
         _detailGrid->layout()->removeWidget( item->widget());
          item->widget()->setHidden(true);
        }
        _detailFooter->setVisible(true);

        _gridPanel = new JPanel(new GridBagLayout());
        GridBagConstraints* c =  new GridBagConstraints();
        c->gridwidth = 1;
        c->gridheight = 1;
        c->ipadx = 5;

        if(gridType == EMPTY_GRID)
        {
         makeEmptyGrid(c);
         _detailFooter->setVisible(false);
         _gridPanel->setObjectName("emptyGrid");
        }
        else if(gridType == "Layout") {
         makeLayoutGrid(c);
         _gridPanel->setObjectName("layoutGrid");
        }
        else if(gridType == "TrainType")
        {
         makeTrainTypeGrid(c);
         _gridPanel->setObjectName("trainTypeGrid");
        }
        else if(gridType == "Segment") {
          makeSegmentGrid(c);
          _gridPanel->setObjectName("SegmentGrid");
        }
        else if(gridType ==  "Station") {
                makeStationGrid(c);
                _gridPanel->setObjectName("stationGrid");
        }
        else if(gridType == "Schedule") {
         makeScheduleGrid(c);
         _gridPanel->setObjectName("ScheduleGrid");
        }
        else if(gridType ==  "Train") {
                makeTrainGrid(c);
                _gridPanel->setObjectName("trainGrid");
        }
        else if(gridType ==  "Stop") {
                makeStopGrid(c);
                _gridPanel->setObjectName("stopGrid");
        }
        else {
         log->warn(tr("Invalid grid type: '%1'").arg(gridType));  // NOI18N
         makeEmptyGrid(c);
         _gridPanel->setObjectName("emptyGid");
        }

        _detailGrid->layout()->addWidget(_gridPanel);
        _detailGrid->setVisible(true);
    }

    /**
     * This grid is used when there are no edit grids required.
     *
     * @param c The constraints object used for the grid construction
     */
    void TimeTableFrame::makeEmptyGrid(GridBagConstraints* c) {
        // Variable type box
        c->gridy = 0;
        c->gridx = 0;
        c->anchor = GridBagConstraints::CENTER;
        JLabel*  rowLabel = new JLabel("This page is intentionally blank");  // NOI18N
        rowLabel->setObjectName("rowLabel");
        ((GridBagLayout*)_gridPanel->layout())->addWidget(rowLabel, *c);
    }

    /**
     * This grid is used to edit Layout data.
     *
     * @param c The constraints object used for the grid construction
     */
    void TimeTableFrame::makeLayoutGrid(GridBagConstraints *c) {
        makeGridLabel(0, tr("Layout Name:"), tr("The layout name"), c);  // NOI18N
        ((GridBagLayout*)_gridPanel->layout())->addWidget(_editLayoutName, *c);

        makeGridLabel(1, tr("Scale:"), tr("The layout scale as defined in Preferences -> Warrants"), c);  // NOI18N
        ((GridBagLayout*)_gridPanel->layout())->addWidget(_editScale, *c);

        makeGridLabel(2, tr("Fast Clock:"), tr("The fast clock speed"), c);  // NOI18N
        ((GridBagLayout*)_gridPanel->layout())->addWidget(_editFastClock, *c);

        makeGridLabel(3, tr("Throttles:"), tr("The number of throttles"), c);  // NOI18N
        ((GridBagLayout*)_gridPanel->layout())->addWidget(_editThrottles, *c);

        makeGridLabel(4, tr("Use Metric Units:"), tr("Checked if distances are metric based"), c);  // NOI18N
        ((GridBagLayout*)_gridPanel->layout())->addWidget(_editMetric, *c);

        makeGridLabel(5, tr("Scale Mile/Km:"), tr("The length of a scale mile in feet or a scale kilometer in meters"), c);  // NOI18N
        ((GridBagLayout*)_gridPanel->layout())->addWidget(_showScaleMK, *c);
    }

    /**
     * This grid is used to edit the Train Type data.
     *
     * @param c The constraints object used for the grid construction
     */
    void TimeTableFrame::makeTrainTypeGrid(GridBagConstraints *c) {
        makeGridLabel(0, tr("Type Name:"), tr("The type name"), c);  // NOI18N
        ((GridBagLayout*)_gridPanel->layout())->addWidget(_editTrainTypeName, *c);

        makeGridLabel(1, tr("Color:"), tr("The type color"), c);  // NOI18N
        ((GridBagLayout*)_gridPanel->layout())->addWidget(_editTrainTypeColor, *c);
    }

    /**
     * This grid is used to edit the Segment data.
     *
     * @param c The constraints object used for the grid construction
     */
    void TimeTableFrame::makeSegmentGrid(GridBagConstraints *c) {
        makeGridLabel(0, tr("Segment Name:"), tr("The segment name"), c);  // NOI18N
        ((GridBagLayout*)_gridPanel->layout())->addWidget(_editSegmentName, *c);
    }

    /**
     * This grid is used to edit the Station data.
     *
     * @param c The constraints object used for the grid construction
     */
    void TimeTableFrame::makeStationGrid(GridBagConstraints *c) {
        makeGridLabel(0, tr("Station Name:"), tr("The station Name"), c);  // NOI18N
        ((GridBagLayout*)_gridPanel->layout())->addWidget(_editStationName, *c);

        makeGridLabel(1, tr("Distance:"), tr("The distance from the beginning of the segment"), c);  // NOI18N
        ((GridBagLayout*)_gridPanel->layout())->addWidget(_editDistance, *c);

        makeGridLabel(2, tr("Double Track:"), tr("s this area double tracked?"), c);  // NOI18N
        ((GridBagLayout*)_gridPanel->layout())->addWidget(_editDoubleTrack, *c);

        makeGridLabel(3, tr("Sidings:"), tr("The number of sidings.  The default is zero."), c);  // NOI18N
        ((GridBagLayout*)_gridPanel->layout())->addWidget(_editSidings, *c);

        makeGridLabel(4, tr("Staging:"), tr("The number of staging tracks.  The default is zero."), c);  // NOI18N
        ((GridBagLayout*)_gridPanel->layout())->addWidget(_editStaging, *c);
    }

    /**
     * This grid is used to edit the Schedule data.
     *
     * @param c The constraints object used for the grid construction
     */
    void TimeTableFrame::makeScheduleGrid(GridBagConstraints *c) {
        makeGridLabel(0, "Schedule Name:", "The schedule name which normally printed on the timetable.", c);  // NOI18N
        ((GridBagLayout*)_gridPanel->layout())->addWidget(_editScheduleName, *c);

        makeGridLabel(1, "Effective Date:", "The date when the schedule becomes effective.", c);  // NOI18N
        ((GridBagLayout*)_gridPanel->layout())->addWidget(_editEffDate, *c);

        makeGridLabel(2, "Start Hour (hh):", "The starting hour for the schedule, values are 0 - 23.  Default is 0 (midnight)", c);  // NOI18N
        ((GridBagLayout*)_gridPanel->layout())->addWidget(_editStartHour, *c);

        makeGridLabel(3, "Duration (hh):", "The duration of the schedule in hours, values are 1 to 24.  Default is 24.", c);  // NOI18N
        ((GridBagLayout*)_gridPanel->layout())->addWidget(_editDuration, *c);
    }

    /**
     * This grid is used to edit the Train data.
     *
     * @param c The constraints object used for the grid construction
     */
    void TimeTableFrame::makeTrainGrid(GridBagConstraints *c) {
        makeGridLabel(0, "Train Name:", "The train name or symbol.", c);  // NOI18N
        ((GridBagLayout*)_gridPanel->layout())->addWidget(_editTrainName, *c);

        makeGridLabel(1, "Description:", "A description of the train.", c);  // NOI18N
        ((GridBagLayout*)_gridPanel->layout())->addWidget(_editTrainDesc, *c);

        makeGridLabel(2, "Type:", "The assigned train type.", c);  // NOI18N
        ((GridBagLayout*)_gridPanel->layout())->addWidget(_editTrainType, *c);

        makeGridLabel(3, "Default Speed:", "The speed to be used when a stop does not specify a new speed.", c);  // NOI18N
        ((GridBagLayout*)_gridPanel->layout())->addWidget(_editDefaultSpeed, *c);

        makeGridLabel(4, "Start Time (hh:mm):", "The start time for the train, hh:mm.", c);  // NOI18N
        ((GridBagLayout*)_gridPanel->layout())->addWidget(_editTrainStartTime, *c);

        makeGridLabel(5, "Throttle:", "The assigned throttle, if any.", c);  // NOI18N
        ((GridBagLayout*)_gridPanel->layout())->addWidget(_editThrottle, *c);

        makeGridLabel(6, "Route Duration (hh:mm):", "The calculated duration for the train.", c);  // NOI18N
        ((GridBagLayout*)_gridPanel->layout())->addWidget(_showRouteDuration, *c);

        makeGridLabel(7, "Notes:", "Detail instructions for the train.", c);  // NOI18N
        ((GridBagLayout*)_gridPanel->layout())->addWidget(_editTrainNotes, *c);
    }

    /**
     * This grid is used to edit the Stop data.
     *
     * @param c The constraints object used for the grid construction
     */
    void TimeTableFrame::makeStopGrid(GridBagConstraints *c) {
        makeGridLabel(0, "Sequence:", "The assigned sequence number, used to sort the stops.", c);  // NOI18N
        ((GridBagLayout*)_gridPanel->layout())->addWidget(_showStopSeq, *c);

        makeGridLabel(1, "Station:", "The station name.", c);  // NOI18N
        ((GridBagLayout*)_gridPanel->layout())->addWidget(_editStopStation, *c);

        makeGridLabel(2, "Duration (min):", "The duration of the stop or zero.", c);  // NOI18N
        ((GridBagLayout*)_gridPanel->layout())->addWidget(_editStopDuration, *c);

        makeGridLabel(3, "Next Speed:", "The speed to the next station.  Zero indicates use the default train speed.", c);  // NOI18N
        ((GridBagLayout*)_gridPanel->layout())->addWidget(_editNextSpeed, *c);

        makeGridLabel(4, "Staging Track:", "The assigned staging track.", c);  // NOI18N
        ((GridBagLayout*)_gridPanel->layout())->addWidget(_editStagingTrack, *c);

        makeGridLabel(5, "Arrival Time (hh:mm):", "The calculated arrival time.", c);  // NOI18N
        ((GridBagLayout*)_gridPanel->layout())->addWidget(_showArriveTime, *c);

        makeGridLabel(6, "Departure Time (hh:mm):", "The calculated departure time.", c);  // NOI18N
        ((GridBagLayout*)_gridPanel->layout())->addWidget(_showDepartTime, *c);

        makeGridLabel(7, "Notes:", "Detail instructions for this stop.", c);  // NOI18N
        ((GridBagLayout*)_gridPanel->layout())->addWidget(_editStopNotes, *c);
    }

    /**
     * Create the label portion of a grid row.
     * @param row The grid row number.
     * @param label The bundle key for the label text.
     * @param hint The bundle key for the label tool tip.
     * @param c The grid bag contraints object.
     */
    void TimeTableFrame::makeGridLabel(int row, QString label, QString hint, GridBagConstraints* c) {
        c->gridy = row;
        c->gridx = 0;
        c->anchor = GridBagConstraints::EAST;
        JLabel*  rowLabel = new JLabel(/*tr*/(label));
        rowLabel->setToolTip(/*tr*/(hint));
        ((GridBagLayout*)_gridPanel->layout())->addWidget(rowLabel, *c);
        c->gridx = 1;
        c->anchor = GridBagConstraints::WEST;
    }

    // ------------ Process button bar and tree events ------------

    /**
     * Add new items.
     */
    void TimeTableFrame::addPressed() {
        if(_curNodeType == "Layout"){
                addLayout();
         }
         else if(_curNodeType == "TrainTypes") {
                addTrainType();
        }
        else if(_curNodeType == "Segments") {
                addSegment();
        }
        else if(_curNodeType == "Segment"){
                addStation();
        }
        else if(_curNodeType == "Schedules") {
                addSchedule();
        }
        else if(_curNodeType == "Schedule") {
                addTrain();
        }
        else if(_curNodeType == "Train"){
                addStop();
        }
        else{
         log->error(tr("Add called for unsupported node type: '%1'").arg(_curNodeType));  // NOI18N
        }
    }

    /**
     * Create a new Layout object with default values.
     * Add the layout node and the TrainTypes, Segments and Schedules collection nodes.
     */
    void TimeTableFrame::addLayout() {
        Layout* newLayout = new Layout();
        setShowReminder(true);

        // Build tree components
        _curNode  = new TimeTableTreeNode(newLayout->getLayoutName(), "Layout", newLayout->getLayoutId(), 0);    // NOI18N
        _timetableRoot->add(_curNode);
        _leafNode = new TimeTableTreeNode(buildNodeText("TrainTypes", nullptr, 0), "TrainTypes", 0, 0);    // NOI18N
        _curNode->add(_leafNode);
        _leafNode = new TimeTableTreeNode(buildNodeText("Segments", nullptr, 0), "Segments", 0, 0);    // NOI18N
        _curNode->add(_leafNode);
        _leafNode = new TimeTableTreeNode(buildNodeText("Schedules", nullptr, 0), "Schedules", 0, 0);    // NOI18N
        _curNode->add(_leafNode);
        _timetableModel->nodeStructureChanged(_timetableRoot);

        // Switch to new node
        QVector<TreeNode*>* v = _curNode->getPath();
        QVector<QObject*>* ov = new QVector<QObject*>();
        foreach(TreeNode* n, *v)
         ov->append((QObject*)n);
        _timetableTree->setSelectionPath(new TreePath(/*_curNode->getPath()*/ov));
    }

    /**
     * Create a new Train Type object.
     * The default color is black.
     */
    void TimeTableFrame::addTrainType() {
        TimeTableTreeNode* layoutNode = (TimeTableTreeNode*) _curNode->getParent();
        int layoutId = layoutNode->getId();
        TrainType* newType = new TrainType(layoutId);
        setShowReminder(true);

        // Build tree components
        _leafNode = new TimeTableTreeNode(newType->getTypeName(), "TrainType", newType->getTypeId(), 0);    // NOI18N
        _curNode->add(_leafNode);
        _timetableModel->nodeStructureChanged(_curNode);

        // Switch to new node
        //_timetableTree->setSelectionPath(new TreePath(_leafNode->getPath()));
        QVector<TreeNode*>* v = _leafNode->getPath();
        QVector<QObject*>* ov = new QVector<QObject*>();
        foreach(TreeNode* n, *v)
         ov->append((QObject*)n);
        _timetableTree->setSelectionPath(new TreePath(ov));
    }

    /**
     * Create a new Segment object with default values.
     */
    void TimeTableFrame::addSegment() {
        TimeTableTreeNode* layoutNode = (TimeTableTreeNode*) _curNode->getParent();
        int layoutId = layoutNode->getId();
        Segment* newSegment = new Segment(layoutId);
        setShowReminder(true);

        // Build tree components
        _leafNode = new TimeTableTreeNode(newSegment->getSegmentName(), "Segment", newSegment->getSegmentId(), 0);    // NOI18N
        _curNode->add(_leafNode);
        _timetableModel->nodeStructureChanged(_curNode);

        // Switch to new node
        //_timetableTree->setSelectionPath(new TreePath(_leafNode->getPath()));
        QVector<TreeNode*>* v = _leafNode->getPath();
        QVector<QObject*>* ov = new QVector<QObject*>();
        foreach(TreeNode* n, *v)
         ov->append((QObject*)n);
        _timetableTree->setSelectionPath(new TreePath(ov));
    }

    /**
     * Create a new Station object with default values.
     */
    void TimeTableFrame::addStation() {
        Station* newStation = new Station(_curNodeId);
        setShowReminder(true);

        // Build tree components
        _leafNode = new TimeTableTreeNode(newStation->getStationName(), "Station", newStation->getStationId(), 0);    // NOI18N
        _curNode->add(_leafNode);
        _timetableModel->nodeStructureChanged(_curNode);

        // Switch to new node
        //_timetableTree->setSelectionPath(new TreePath(_leafNode->getPath()));
        QVector<TreeNode*>* v = _leafNode->getPath();
        QVector<QObject*>* ov = new QVector<QObject*>();
        foreach(TreeNode* n, *v)
         ov->append((QObject*)n);
        _timetableTree->setSelectionPath(new TreePath(ov));
    }

    /**
     * Create a new Schedule object with default values.
     */
    void TimeTableFrame::addSchedule() {
        TimeTableTreeNode* layoutNode = (TimeTableTreeNode*) _curNode->getParent();
        int layoutId = layoutNode->getId();
        TimeTable::TTSchedule* newSchedule = new TimeTable::TTSchedule(layoutId);
        setShowReminder(true);

        // Build tree components
        _leafNode = new TimeTableTreeNode(newSchedule->getScheduleName(), "Schedule", newSchedule->getScheduleId(), 0);    // NOI18N
        _curNode->add(_leafNode);
        _timetableModel->nodeStructureChanged(_curNode);

        // Switch to new node
        //_timetableTree->setSelectionPath(new TreePath(_leafNode->getPath()));
        QVector<TreeNode*>* v = _leafNode->getPath();
        QVector<QObject*>* ov = new QVector<QObject*>();
        foreach(TreeNode* n, *v)
         ov->append((QObject*)n);
        _timetableTree->setSelectionPath(new TreePath(ov));
    }

    void TimeTableFrame::addTrain() {
        TTTrain* newTrain = new TTTrain(_curNodeId);
        setShowReminder(true);

        // Build tree components
        _leafNode = new TimeTableTreeNode(newTrain->getTrainName(), "Train", newTrain->getTrainId(), 0);    // NOI18N
        _curNode->add(_leafNode);
        _timetableModel->nodeStructureChanged(_curNode);

        // Switch to new node
        //_timetableTree->setSelectionPath(new TreePath(_leafNode->getPath()));
        QVector<TreeNode*>* v = _leafNode->getPath();
        QVector<QObject*>* ov = new QVector<QObject*>();
        foreach(TreeNode* n, *v)
         ov->append((QObject*)n);
        _timetableTree->setSelectionPath(new TreePath(ov));
    }

    void TimeTableFrame::addStop() {
        int newSeq = _dataMgr->getStops(_curNodeId, 0, false).size();
        Stop* newStop = new Stop(_curNodeId, newSeq + 1);
        setShowReminder(true);

        // Build tree components
        _leafNode = new TimeTableTreeNode(QString::number(newSeq + 1), "Stop", newStop->getStopId(), newSeq + 1);    // NOI18N
        _curNode->add(_leafNode);
        _timetableModel->nodeStructureChanged(_curNode);

        // Switch to new node
        //_timetableTree->setSelectionPath(new TreePath(_leafNode->getPath()));
        QVector<TreeNode*>* v = _leafNode->getPath();
        QVector<QObject*>* ov = new QVector<QObject*>();
        foreach(TreeNode* n, *v)
         ov->append((QObject*)n);
        _timetableTree->setSelectionPath(new TreePath(ov));
    }

    /**
     * Set up the edit environment for the selected node Called from
     * {@link #treeRowSelected}. This takes the place of an actual button.
     */
    void TimeTableFrame::editPressed() {
        if(_curNodeType== "Layout") {
                editLayout();
                makeDetailGrid("Layout");  // NOI18N
        }
        else if(_curNodeType== "TrainType") {
                editTrainType();
                makeDetailGrid("TrainType");  // NOI18N
        }
        else if(_curNodeType== "Segment") {
                editSegment();
                makeDetailGrid("Segment");  // NOI18N
        }
        else if(_curNodeType== "Station") {
                editStation();
                makeDetailGrid("Station");  // NOI18N
        }
        else if(_curNodeType=="Schedule") {
                editSchedule();
                makeDetailGrid("Schedule");  // NOI18N
        }
        else if(_curNodeType== "Train") {
                editTrain();
                makeDetailGrid("Train");  // NOI18N
        }
        else if(_curNodeType== "Stop") {
                editStop();
                makeDetailGrid("Stop");  // NOI18N
         }
        else {
                log->error(tr("Edit called for unsupported node type: '%1'").arg(_curNodeType));  // NOI18N
        }
        setEditMode(false);
    }

    /*
     * Set Layout edit variables and labels
     */
    void TimeTableFrame::editLayout() {
        Layout* layout = _dataMgr->getLayout(_curNodeId);
        _editLayoutName->setText(layout->getLayoutName());
        _editFastClock->setText(QString::number(layout->getFastClock()));
        _editThrottles->setText(QString::number(layout->getThrottles()));
        _editMetric->setChecked(layout->getMetric());
        QString unitMeasure = (layout->getMetric())
                ? tr("meters") // NOI18N
                : tr("feet"); // NOI18N
        _showScaleMK->setText(tr("%1 %2").arg(layout->getScaleMK(),0,'g',2).arg(unitMeasure)); // NOI18N

        _editScale->clear();
        for (Scale* scale : ScaleManager::getScales()) {
            _editScale->addItem(scale->getScaleName(), VPtr<Scale>::asQVariant(scale));
        }
//        jmri.util.swing.JComboBoxUtil.setupComboBoxMaxRows(_editScale);
        //_editScale->setCheckedItem(layout->getScale());
        _editScale->findText(layout->getScale()->getScaleName());
    }

    /*
     * Set TrainType edit variables and labels
     */
    void TimeTableFrame::editTrainType() {
        TrainType* type = _dataMgr->getTrainType(_curNodeId);
        _editTrainTypeName->setText(type->getTypeName());
        _editTrainTypeColor->setColor(QColor(type->getTypeColor()));
    }

    /*
     * Set Segment edit variables and labels
     */
    void TimeTableFrame::editSegment() {
        Segment* segment = _dataMgr->getSegment(_curNodeId);
        _editSegmentName->setText(segment->getSegmentName());
    }

    /*
     * Set Station edit variables and labels
     */
    void TimeTableFrame::editStation() {
        Station* station = _dataMgr->getStation(_curNodeId);
        _editStationName->setText(station->getStationName());
        _editDistance->setText(QString::number(station->getDistance()));
        _editDoubleTrack->setChecked(station->getDoubleTrack());
        _editSidings->setValue(station->getSidings());
        _editStaging->setValue(station->getStaging());
    }

    /*
     * Set Schedule edit variables and labels
     */
    void TimeTableFrame::editSchedule() {
        TimeTable::TTSchedule* schedule = _dataMgr->getSchedule(_curNodeId);
        _editScheduleName->setText(schedule->getScheduleName());
        _editEffDate->setText(schedule->getEffDate());
        _editStartHour->setValue(schedule->getStartHour());
        _editDuration->setValue(schedule->getDuration());
    }

    /*
     * Set Train edit variables and labels
     */
    void TimeTableFrame::editTrain() {
        TTTrain* train = _dataMgr->getTrain(_curNodeId);
        int layoutId = _dataMgr->getSchedule(train->getScheduleId())->getLayoutId();

        _editTrainName->setText(train->getTrainName());
        _editTrainDesc->setText(train->getTrainDesc());
        _editDefaultSpeed->setText(QString::number(train->getDefaultSpeed()));
        _editTrainStartTime->setText(QString::asprintf("%02d:%02d",  // NOI18N
                train->getStartTime() / 60,
                train->getStartTime() % 60));
        _editThrottle->setModel(new SpinnerNumberModel(train->getThrottle(), 0, _dataMgr->getLayout(layoutId)->getThrottles(), 1));
        _editTrainNotes->setText(train->getTrainNotes());
        _showRouteDuration->setText(QString::asprintf("%02d:%02d",  // NOI18N
                train->getRouteDuration() / 60,
                train->getRouteDuration() % 60));

        _editTrainType->clear();
        for (TrainType* type : _dataMgr->getTrainTypes(layoutId, true)) {
            _editTrainType->addItem(type->getTypeName(), VPtr<TrainType>::asQVariant(type));
        }
//        jmri.util.swing.JComboBoxUtil.setupComboBoxMaxRows(_editTrainType);
        if (train->getTypeId() > 0) {
            //_editTrainType->setCheckedItem(_dataMgr->getTrainType(train->getTypeId()));
         _editTrainType->findText(_dataMgr->getTrainType(train->getTypeId())->getTypeName());
        }
    }

    /*
     * Set Stop edit variables and labels
     * The station combo box uses a data manager internal class to present
     * both the segment name and the station name.  This is needed since a station
     * can be in multiple segments.
     */
    void TimeTableFrame::editStop() {
        Stop* stop = _dataMgr->getStop(_curNodeId);
        Layout* layout = _dataMgr->getLayoutForStop(_curNodeId);

        _showStopSeq->setText(QString::number(stop->getSeq()));
        _editStopDuration->setText(QString::number(stop->getDuration()));
        _editNextSpeed->setText(QString::number(stop->getNextSpeed()));
        _editStopNotes->setText(stop->getStopNotes());
        _showArriveTime->setText(QString::asprintf("%02d:%02d",  // NOI18N
                stop->getArriveTime() / 60,
                stop->getArriveTime() % 60));
        _showDepartTime->setText(QString::asprintf("%02d:%02d",  // NOI18N
                stop->getDepartTime() / 60,
                stop->getDepartTime() % 60));

        _editStopStation->clear();
        for (SegmentStation* segmentStation : _dataMgr->getSegmentStations(layout->getLayoutId())) {
            _editStopStation->addItem(segmentStation->toString(), VPtr<SegmentStation>::asQVariant(segmentStation));
            if (stop->getStationId() == segmentStation->getStationId()) {
                // This also triggers stopStationItemEvent which will set _editStagingTrack
               // _editStopStation->->setCheckedItem(segmentStation);
             _editStopStation->findText(segmentStation->toString());
            }
        }
//        jmri.util.swing.JComboBoxUtil.setupComboBoxMaxRows(_editStopStation);
        setMoveButtons();
    }

    /**
     * Apply the updates to the current node.
     */
    void TimeTableFrame::updatePressed() {
        if(_curNodeType == "Layout") {
                updateLayout();
        }
        else if(_curNodeType == "TrainType") {
                updateTrainType();
        }
        else if(_curNodeType == "Segment") {
                updateSegment();
        }
        else if(_curNodeType == "Station") {
                updateStation();
        }
        else if(_curNodeType == "Schedule") {
                updateSchedule();
        }
        else if(_curNodeType == "Train") {
                updateTrain();
        }
        else if(_curNodeType == "Stop") {
                updateStop();
        }
        else
        {
                log->warn("Invalid update button press");  // NOI18N
        }
        setEditMode(false);
        _timetableTree->setSelectionPath(_curTreePath);
//        _timetableTree->grabFocus();
        editPressed();
    }

    /**
     * Update the layout information.
     * If the fast clock or metric values change, a recalc will be required.
     * The throttles value cannot be less than the highest throttle assigned to a train->
     */
    void TimeTableFrame::updateLayout() {
        Layout* layout = _dataMgr->getLayout(_curNodeId);

        // Pre-validate and convert inputs
        QString newName = _editLayoutName->text().trimmed();
        Scale* newScale = (Scale*) VPtr<Scale>::asPtr(_editScale->currentData());
        int newFastClock = parseNumber(_editFastClock, "fast clock");  // NOI18N
        if (newFastClock < 1) {
            newFastClock = layout->getFastClock();
        }
        int newThrottles = parseNumber(_editThrottles, "throttles");  // NOI18N
        if (newThrottles < 0) {
            newThrottles = layout->getThrottles();
        }
        bool newMetric =_editMetric->isChecked();

        bool update = false;
        QStringList exceptionList = QStringList();

        // Perform updates
        if (layout->getLayoutName() != (newName)) {
            layout->setLayoutName(newName);
            _curNode->setText(newName);
            _timetableModel->nodeChanged(_curNode);
            update = true;
        }

        if (layout->getScale() != (newScale)) {
            try {
                layout->setScale(newScale);
                update = true;
            } catch (IllegalArgumentException ex) {
                exceptionList.append(ex.getMessage());
            }
        }

        if (layout->getFastClock() != newFastClock) {
            try {
                layout->setFastClock(newFastClock);
                update = true;
            } catch (IllegalArgumentException ex) {
                exceptionList.append(ex.getMessage());
            }
        }

        if (layout->getMetric() != newMetric) {
            try {
                layout->setMetric(newMetric);
                update = true;
            } catch (IllegalArgumentException ex) {
                exceptionList.append(ex.getMessage());
            }
        }

        if (layout->getThrottles() != newThrottles) {
            try {
                layout->setThrottles(newThrottles);
                update = true;
            } catch (IllegalArgumentException ex) {
                exceptionList.append(ex.getMessage());
            }
        }

        if (update) {
            setShowReminder(true);
        }

        // Display exceptions if necessary
        if (!exceptionList.isEmpty()) {
            QString msg = tr("--- Layout Update Errors ---\n");  // NOI18N
            for (QString keyWord : exceptionList) {
                if (keyWord.startsWith(TimeTableDataManager::TIME_OUT_OF_RANGE)) {
                     QStringList comps = keyWord.split("~");

                    msg.append(tr("- Time outside of range for stop seq %1, train %2").arg(comps[1]).arg(comps[2]));
                } else if (keyWord.startsWith(TimeTableDataManager::SCALE_NF)) {
                     QStringList scaleMsg = keyWord.split("~");
                    msg.append(tr("- Scale %1 is not available.").arg(scaleMsg[1]));
                } else {
                    msg.append(QString::asprintf("%n%s", (keyWord)));
                    if (keyWord == (TimeTableDataManager::THROTTLES_IN_USE)) {
                        // Add the affected trains
                        for (TTSchedule* schedule : _dataMgr->getSchedules(_curNodeId, true)) {
                            for (TTTrain* train : _dataMgr->getTrains(schedule->getScheduleId(), 0, true)) {
                                if (train->getThrottle() > newThrottles) {
                                    msg.append(QString::asprintf("%n      %s [ %d ]", train->getTrainName(), train->getThrottle()));
                                }
                            }
                        }
                    }
                }
            }
            JOptionPane::showMessageDialog(nullptr,
                    msg,
                    tr("Warning"),  // NOI18N
                    JOptionPane::WARNING_MESSAGE);
        }
    }

    /**
     * Update the train type information.
     */
    void TimeTableFrame::updateTrainType() {
        TrainType* type = _dataMgr->getTrainType(_curNodeId);

        QString newName = _editTrainTypeName->text().trimmed();
        QColor newColor = _editTrainTypeColor->getColor();
        QString newColorHex = ColorUtil::colorToHexString(newColor);

        bool update = false;

        if (type->getTypeName() != (newName)) {
            type->setTypeName(newName);
            _curNode->setText(newName);
            update = true;
        }
        if (type->getTypeColor() != (newColorHex)) {
            type->setTypeColor(newColorHex);
            update = true;
        }
        _timetableModel->nodeChanged(_curNode);

        if (update) {
            setShowReminder(true);
        }
    }

    /**
     * Update the segment information.
     */
    void TimeTableFrame::updateSegment() {
        QString newName = _editSegmentName->text().trimmed();

        Segment* segment = _dataMgr->getSegment(_curNodeId);
        if (segment->getSegmentName() != (newName)) {
            segment->setSegmentName(newName);
            _curNode->setText(newName);
            setShowReminder(true);
        }
        _timetableModel->nodeChanged(_curNode);
    }

    /**
     * Update the station information.
     * The staging track value cannot be less than any train references.
     */
    void TimeTableFrame::updateStation() {
        Station* station = _dataMgr->getStation(_curNodeId);

        // Pre-validate and convert inputs
        QString newName = _editStationName->text().trimmed();
        double newDistance;
        bool bok;
            newDistance = (_editDistance->text().toDouble(&bok));
        if(!bok) {
            log->warn(tr("'%1' is not a valid number for %2").arg(_editDistance->text()).arg("station distance"));  // NOI18N
            JOptionPane::showMessageDialog(nullptr,
                    tr("\"%1\" is not a valid number for %2").arg(_editDistance->text()).arg("station distance"),  // NOI18N
                    tr("Error"),  // NOI18N
                    JOptionPane::WARNING_MESSAGE);
            newDistance = station->getDistance();
        }
        bool newDoubleTrack =_editDoubleTrack->isChecked();
        int newSidings = (int) _editSidings->value();
        int newStaging = (int) _editStaging->value();

        bool update = false;
        QList<QString> exceptionList = QList<QString>();

        // Perform updates
        if (station->getStationName() != (newName)) {
            station->setStationName(newName);
            _curNode->setText(newName);
            _timetableModel->nodeChanged(_curNode);
            update = true;
        }

        if (newDistance < 0.0) {
            newDistance = station->getDistance();
        }
        if (qAbs(station->getDistance() - newDistance) > .01 ) {
            try {
                station->setDistance(newDistance);
                update = true;
            } catch (IllegalArgumentException ex) {
                exceptionList.append(ex.getMessage());
            }
        }

        if (station->getDoubleTrack() != newDoubleTrack) {
            station->setDoubleTrack(newDoubleTrack);
            update = true;
        }

        if (station->getSidings() != newSidings) {
            station->setSidings(newSidings);
            update = true;
        }

        if (station->getStaging() != newStaging) {
            try {
                station->setStaging(newStaging);
                update = true;
            } catch (IllegalArgumentException ex) {
                exceptionList.append(ex.getMessage());
            }
        }

        if (update) {
            setShowReminder(true);
        }

        // Display exceptions if necessary
        if (!exceptionList.isEmpty()) {
            QString msg = tr("--- Station Update Errors ---\n");  // NOI18N
            for (QString keyWord : exceptionList) {
                if (keyWord.startsWith(TimeTableDataManager::TIME_OUT_OF_RANGE)) {
                    QStringList comps = keyWord.split("~");
#if 0
                    msg.append(tr(comps[0], comps[1], comps[2]));
                } else {
                    msg.append(QString::sprintf("%n%s", tr(keyWord)));
                    if (keyWord == (TimeTableDataManager::STAGING_IN_USE)) {
                        // Add the affected stops
                        for (Stop* stop : _dataMgr->getStops(0, _curNodeId, false)) {
                            if (stop->getStagingTrack() > newStaging) {
                                TimeTable::Train train = _dataMgr->getTrain(stop->getTrainId());
                                msg.append(QString::sprintf("%n      %s, %d", train->getTrainName(), stop->getSeq()));
                            }
                        }
                    }
#endif
                }
            }
            JOptionPane::showMessageDialog(nullptr,
                    msg,
                    tr("Warning"),  // NOI18N
                    JOptionPane::WARNING_MESSAGE);
        }
    }

    /**
     * Update the schedule information.
     * Changes to the schedule times cannot make a train start time or
     * a stop's arrival or departure times invalid.
     */
    void TimeTableFrame::updateSchedule() {
        TimeTable::TTSchedule* schedule = _dataMgr->getSchedule(_curNodeId);

        // Pre-validate and convert inputs
        QString newName = _editScheduleName->text().trimmed();
        QString newEffDate = _editEffDate->text().trimmed();
        int newStartHour = (int) _editStartHour->getValue();
        if (newStartHour < 0 || newStartHour > 23) {
            newStartHour = schedule->getStartHour();
        }
        int newDuration = (int) _editDuration->getValue();
        if (newDuration < 1 || newDuration > 24) {
            newDuration = schedule->getDuration();
        }

        bool update = false;
        QList<QString> exceptionList = QList<QString>();

        // Perform updates
        if (schedule->getScheduleName() != (newName)) {
            schedule->setScheduleName(newName);
            update = true;
        }

        if (schedule->getEffDate() != (newEffDate)) {
            schedule->setEffDate(newEffDate);
            update = true;
        }

        if (update) {
            _curNode->setText(buildNodeText("Schedule", schedule, 0));  // NOI18N
            _timetableModel->nodeChanged(_curNode);
        }

        if (schedule->getStartHour() != newStartHour) {
            try {
                schedule->setStartHour(newStartHour);
                update = true;
            } catch (IllegalArgumentException ex) {
                exceptionList.append(ex.getMessage());
            }
        }

        if (schedule->getDuration() != newDuration) {
            try {
                schedule->setDuration(newDuration);
                update = true;
            } catch (IllegalArgumentException ex) {
                exceptionList.append(ex.getMessage());
            }
        }

        if (update) {
            setShowReminder(true);
        }

        // Display exceptions if necessary
        if (!exceptionList.isEmpty()) {
            QString msg = tr("--- Schedule Update Errors ---\n");  // NOI18N
            for (QString keyWord : exceptionList) {
                if (keyWord.startsWith(TimeTableDataManager::TIME_OUT_OF_RANGE)) {
                     QStringList comps = keyWord.split("~");
#if 0
                    msg.append(tr(comps[0], comps[1], comps[2]));
                } else {
                    msg.append(QString::asprintf("%n%s", tr(keyWord)));
#endif
                }
            }
            JOptionPane::showMessageDialog(nullptr,
                    msg,
                    tr("Warning"),  // NOI18N
                    JOptionPane::WARNING_MESSAGE);
        }
    }

    /**
     * Update the train information.
     * The train start time has to have a h:mm format and cannot fall outside
     * of the schedules times.
     */
    void TimeTableFrame::updateTrain() {
        TTTrain* train = _dataMgr->getTrain(_curNodeId);
        QList<QString> exceptionList = QList<QString>();

        // Pre-validate and convert inputs
        QString newName = _editTrainName->text().trimmed();
        QString newDesc = _editTrainDesc->text().trimmed();
        int newType =  VPtr<TrainType>::asPtr(_editTrainType->currentData())->getTypeId();
        int newSpeed = parseNumber(_editDefaultSpeed, "default train speed");  // NOI18N
        if (newSpeed < 0) {
            newSpeed = train->getDefaultSpeed();
        }
#if 0
        LocalTime newTime;
        int newStart;
        try {
            newTime = LocalTime.parse(_editTrainStartTime->text().trimmed(), DateTimeFormatter.ofPattern("H:mm"));  // NOI18N
            newStart = newTime.getHour() * 60 + newTime.getMinute();
        } catch (DateTimeParseException ex) {
            exceptionList.add(TimeTableDataManager::START_TIME_FORMAT + "~" + ex.getParsedString());
            newStart = train->getStartTime();
        }
#else
        int newStart;
        QTime newTime = QTime::fromString(_editTrainStartTime->text().trimmed(), "H:mm");
        if(!newTime.isValid())
        {
         exceptionList.append(TimeTableDataManager::START_TIME_FORMAT + "~" + /*ex.getParsedString()*/_editTrainStartTime->text().trimmed());
         newStart = train->getStartTime();
        }
        else
        {
         newStart = newTime.hour() * 60 + newTime.minute();
        }
#endif
        int newThrottle = (int) _editThrottle->getValue();
        QString newNotes = _editTrainNotes->toHtml();

        bool update = false;

        // Perform updates
        if (train->getTrainName() != (newName)) {
            train->setTrainName(newName);
            update = true;
        }

        if (train->getTrainDesc() != (newDesc)) {
            train->setTrainDesc(newDesc);
            update = true;
        }

        if (update) {
            _curNode->setText(buildNodeText("Train", train, 0));  // NOI18N
            _timetableModel->nodeChanged(_curNode);
        }

        if (train->getTypeId() != newType) {
            train->setTypeId(newType);
            update = true;
        }

        if (train->getDefaultSpeed() != newSpeed) {
            try {
                train->setDefaultSpeed(newSpeed);
                update = true;
            } catch (IllegalArgumentException ex) {
                exceptionList.append(ex.getMessage());
            }
        }
#if 1
        if (train->getStartTime() != newStart) {
            try {
                train->setStartTime(newStart);
                update = true;
            } catch (IllegalArgumentException ex) {
                exceptionList.append(ex.getMessage());
            }
        }
#endif
        if (train->getThrottle() != newThrottle) {
            try {
                train->setThrottle(newThrottle);
                update = true;
            } catch (IllegalArgumentException ex) {
                exceptionList.append(ex.getMessage());
            }
        }

        if (train->getTrainNotes() != (newNotes)) {
            train->setTrainNotes(newNotes);
            update = true;
        }

        if (update) {
            setShowReminder(true);
        }

        // Display exceptions if necessary
        if (!exceptionList.isEmpty()) {
            QString msg = tr("--- Train Update Errors ---\n");  // NOI18N
            for (QString keyWord : exceptionList) {
                log->info(tr("kw = %1").arg(keyWord));
                if (keyWord.startsWith(TimeTableDataManager::TIME_OUT_OF_RANGE)) {
                     QStringList comps = keyWord.split("~");
#if 0
                    msg.append(tr(comps[0], comps[1], comps[2]));
                } else if (keyWord.startsWith(TimeTableDataManager::START_TIME_FORMAT)) {
                     QStringList timeMsg = keyWord.split("~");
                    msg.append(tr(timeMsg[0], timeMsg[1]));
                } else if (keyWord.startsWith(TimeTableDataManager::START_TIME_RANGE)) {
                     QStringList schedMsg = keyWord.split("~");
                    msg.append(tr(schedMsg[0], schedMsg[1], schedMsg[2]));
                } else {
                    msg.append(QString::asprintf("%n%s", tr(keyWord)));
#endif
                }
            }
            JOptionPane::showMessageDialog(nullptr,
                    msg,
                    tr("Warning"),  // NOI18N
                    JOptionPane::WARNING_MESSAGE);
        }
    }

    /**
     * Update the stop information.
     */
    void TimeTableFrame::updateStop() {
        Stop* stop = _dataMgr->getStop(_curNodeId);

        // Pre-validate and convert inputs
        SegmentStation* stopSegmentStation =
                VPtr<SegmentStation>::asPtr(_editStopStation->currentData());
        int newStation = stopSegmentStation->getStationId();
        int newDuration = parseNumber(_editStopDuration, "stop duration");  // NOI18N
        if (newDuration < 0) {
            newDuration = stop->getDuration();
        }
        int newSpeed = parseNumber(_editNextSpeed, "next speed");  // NOI18N
        if (newSpeed < 0) {
            newSpeed = stop->getNextSpeed();
        }
        int newStagingTrack = (int) _editStagingTrack->getValue();
        QString newNotes = _editStopNotes->toHtml();

        bool update = false;
        QList<QString> exceptionList = QList<QString>();

        // Perform updates
        if (stop->getStationId() != newStation) {
            stop->setStationId(newStation);
            _curNode->setText(buildNodeText("Stop", stop, 0));  // NOI18N
            _timetableModel->nodeChanged(_curNode);
            update = true;
        }

        if (stop->getDuration() != newDuration) {
            try {
                stop->setDuration(newDuration);
                update = true;
            } catch (IllegalArgumentException ex) {
                exceptionList.append(ex.getMessage());
            }
        }

        if (stop->getNextSpeed() != newSpeed) {
            try {
                stop->setNextSpeed(newSpeed);
                update = true;
            } catch (IllegalArgumentException ex) {
                exceptionList.append(ex.getMessage());
            }
        }

        if (stop->getStagingTrack() != newStagingTrack) {
            try {
                stop->setStagingTrack(newStagingTrack);
                update = true;
            } catch (IllegalArgumentException ex) {
                exceptionList.append(ex.getMessage());
            }
        }

        if (stop->getStopNotes() != (newNotes)) {
            stop->setStopNotes(newNotes);
            update = true;
        }

        if (update) {
            setShowReminder(true);
        }

        // Display exceptions if necessary
        if (!exceptionList.isEmpty()) {
            QString msg = tr("--- Stop Update Errors ---\n");  // NOI18N
            for (QString keyWord : exceptionList) {
                if (keyWord.startsWith(TimeTableDataManager::TIME_OUT_OF_RANGE)) {
                     QStringList comps = keyWord.split("~");
#if 0
                    msg.append(tr(comps[0], comps[1], comps[2]));
                } else {
                    msg.append(QString::asprintf("%n%s", tr(keyWord)));
#endif
                }
            }
            JOptionPane::showMessageDialog(nullptr,
                    msg,
                    tr("Warning"),  // NOI18N
                    JOptionPane::WARNING_MESSAGE);
        }
    }

    /**
     * Convert text input to an integer.
     * @param textField JTextField containing the probable integer.
     * @param fieldName The name of the field for the dialog.
     * @return the valid number or -1 for an invalid input.
     */
    int TimeTableFrame::parseNumber(JTextField* textField, QString fieldName) {
        QString text = textField->text().trimmed();
        bool bok;
            return (text).toInt(&bok);
        if(!bok) {
            log->warn(tr("'%1' is not a valid number for %1").arg(text).arg(fieldName));  // NOI18N
            JOptionPane::showMessageDialog(nullptr,
                    tr("\"%1\" is not a valid number for %2").arg(text).arg(fieldName),  // NOI18N
                    tr("Warning"),  // NOI18N
                    JOptionPane::WARNING_MESSAGE);
            return -1;
        }
    }

    /**
     * Process the node delete request.
     */
    void TimeTableFrame::deletePressed() {
        if(_curNodeType == "Layout") {
                deleteLayout();
        }
        else if(_curNodeType == "TrainType") {
                deleteTrainType();
        }
        else if(_curNodeType == "Segment") {
                deleteSegment();
        }
        else if(_curNodeType == "Station") {
                deleteStation();
        }
        else if(_curNodeType == "Schedule") {
                deleteSchedule();
        }
        else if(_curNodeType == "Train") {
                deleteTrain();
        }
        else if(_curNodeType == "Stop"){
                deleteStop();  // NOI18N
        }
        else {
                log->error(tr("Delete called for unsupported node type: '%1").arg(_curNodeType));  // NOI18N
        }
    }

    /**
     * After confirmation, perform a cascade delete of the layout and its components.
     */
    void TimeTableFrame::deleteLayout() {
        QVariantList options = {tr("No"), tr("Yes")};  // NOI18N
        int selectedOption = JOptionPane::showOptionDialog( nullptr,
                tr("Delete the Layout and ALL of its components?"), // NOI18N
                tr("Question"),   // NOI18N
                JOptionPane::YES_NO_OPTION,
                JOptionPane::QUESTION_MESSAGE,
                QIcon(), options, options[0]);
        if (selectedOption == 0) {
            return;
        }

        // Delete the components
        for (TTSchedule* schedule : _dataMgr->getSchedules(_curNodeId, false)) {
            for (TTTrain* train : _dataMgr->getTrains(schedule->getScheduleId(), 0, false)) {
                for (Stop* stop : _dataMgr->getStops(train->getTrainId(), 0, false)) {
                    _dataMgr->deleteStop(stop->getStopId());
                }
                _dataMgr->deleteTrain(train->getTrainId());
            }
            _dataMgr->deleteSchedule(schedule->getScheduleId());
        }

        for (Segment* segment : _dataMgr->getSegments(_curNodeId, false)) {
            for (Station* station : _dataMgr->getStations(segment->getSegmentId(), false)) {
                _dataMgr->deleteStation(station->getStationId());
            }
            _dataMgr->deleteSegment(segment->getSegmentId());
        }

        for (TrainType* type : _dataMgr->getTrainTypes(_curNodeId, false)) {
            _dataMgr->deleteTrainType(type->getTypeId());
        }

        // delete the Layout
        _dataMgr->deleteLayout(_curNodeId);
        setShowReminder(true);

        // Update the tree
//         TreePath parentPath = _curTreePath.getParentPath();
        TreeNode* parentNode = _curNode->getParent();
        _curNode->removeFromParent();
        _curNode  =  nullptr;
        _timetableModel->nodeStructureChanged(parentNode);
//         _timetableTree->setSelectionPath(parentPath);
    }

    /**
     * Delete a train type after checking for usage.
     */
    void TimeTableFrame::deleteTrainType() {
        // Check train references
        QStringList typeReference = QStringList();
        for (TTTrain* train : _dataMgr->getTrains(0, _curNodeId, true)) {
            typeReference.append(train->getTrainName());
        }
        if (!typeReference.isEmpty()) {
            QString msg = tr("%1 cannot be deleted.\nIt is being used by the following items:").arg(_curNodeType);  // NOI18N
            for (QString trainName : typeReference) {
                msg.append("\n    " + trainName);  // NOI18N
            }
            JOptionPane::showMessageDialog( nullptr,
                    msg,
                    tr("Warning"),  // NOI18N
                    JOptionPane::WARNING_MESSAGE);
            return;
        }
        _dataMgr->deleteTrainType(_curNodeId);
        setShowReminder(true);

        // Update the tree
        TreePath* parentPath = _curTreePath->getParentPath();
        TimeTableTreeNode* parentNode = (TimeTableTreeNode*) _curNode->getParent();
        parentNode->remove(_curNode);
        _timetableModel->nodeStructureChanged(parentNode);
        _curNode  =  nullptr;
        _timetableTree->setSelectionPath(parentPath);
    }

    /**
     * Delete a Segment.
     * If the segment contains inactive stations, provide the option to perform
     * a cascade delete.
     */
    void TimeTableFrame::deleteSegment() {
        QList<Station*> stationList = QList<Station*>(_dataMgr->getStations(_curNodeId, true));
        if (!stationList.isEmpty()) {
            // The segment still has stations.  See if any are still used by Stops
            QList<Station*> activeList = QList<Station*>();
            for (Station* checkActive : stationList) {
                QList<Stop*> stopList =QList<Stop*>(_dataMgr->getStops(0, checkActive->getStationId(), true));
                if (!stopList.isEmpty()) {
                    activeList.append(checkActive);
                }
            }
            if (!activeList.isEmpty()) {
                // Cannot delete the Segment
                QString msg = tr("%1 cannot be deleted.\nIt is being used by the following items:").arg(_curNodeType);  // NOI18N
                for (Station* activeStation : activeList) {
                    msg.append("\n    " + activeStation->getStationName());  // NOI18N
                }
                JOptionPane::showMessageDialog( nullptr,
                        msg,
                        tr("Warning"),  // NOI18N
                        JOptionPane::WARNING_MESSAGE);
                return;
            }
            // Present the option to delete the stations and the segment
             QVariantList options = {tr("No"), tr("Yes")};  // NOI18N
            int selectedOption = JOptionPane::showOptionDialog( nullptr,
                    tr("There are inactive Stations assigned.\nDelete the stations and the segment?"), // NOI18N
                    tr("Question"),   // NOI18N
                    JOptionPane::YES_NO_OPTION,
                    JOptionPane::QUESTION_MESSAGE,
                    QIcon(), options, options[0]);
            if (selectedOption == 0) {
                return;
            }
            for (Station* delStation : stationList) {
                _dataMgr->deleteStation(delStation->getStationId());
            }
        }
        // delete the segment
        _dataMgr->deleteSegment(_curNodeId);
        setShowReminder(true);

        // Update the tree
        TreePath* parentPath = _curTreePath->getParentPath();
        TimeTableTreeNode* parentNode = (TimeTableTreeNode*) _curNode->getParent();
        _curNode->removeFromParent();
        _curNode  =  nullptr;
        _timetableModel->nodeStructureChanged(parentNode);
        _timetableTree->setSelectionPath(parentPath);
    }

    /**
     * Delete a Station after checking for usage.
     */
    void TimeTableFrame::deleteStation() {
        // Check stop references
        QList<QString> stopReference = QList<QString>();
        for (Stop* stop : _dataMgr->getStops(0, _curNodeId, true)) {
            TTTrain* train = _dataMgr->getTrain(stop->getTrainId());
            QString trainSeq = QString::asprintf("%s : %d", train->getTrainName(), stop->getSeq());  // NOI18N
            stopReference.append(trainSeq);
        }
        if (!stopReference.isEmpty()) {
            QString msg = tr("%1 cannot be deleted.\nIt is being used by the following items:").arg(_curNodeType);  // NOI18N
            for (QString stopTrainSeq : stopReference) {
                msg.append("\n    " + stopTrainSeq);  // NOI18N
            }
            JOptionPane::showMessageDialog( nullptr,
                    msg,
                    tr("Warning"),  // NOI18N
                    JOptionPane::WARNING_MESSAGE);
            return;
        }
        _dataMgr->deleteStation(_curNodeId);
        setShowReminder(true);

        // Update the tree
        TreePath* parentPath = _curTreePath->getParentPath();
        TimeTableTreeNode* parentNode = (TimeTableTreeNode*) _curNode->getParent();
        parentNode->remove(_curNode);
        _timetableModel->nodeStructureChanged(parentNode);
        _curNode  =  nullptr;
        _timetableTree->setSelectionPath(parentPath);
    }

    /**
     * Delete a schedule->
     * If the schedule contains trains, provide the option to perform
     * a cascade delete of trains and their stops.
     */
    void TimeTableFrame::deleteSchedule() {
        QList<TTTrain*> trainList = QList<TTTrain*>(_dataMgr->getTrains(_curNodeId, 0, true));
        if (!trainList.isEmpty()) {
            // The schedule still has trains.
            // Present the option to delete the stops, trains and the schedule
             QVariantList options = {tr("No"), tr("Yes")};  // NOI18N
            int selectedOption = JOptionPane::showOptionDialog( nullptr,
                    tr("There are Trains assigned.\nDelete the trains, stops and the schedule?"), // NOI18N
                    tr("Question"),   // NOI18N
                    JOptionPane::YES_NO_OPTION,
                    JOptionPane::QUESTION_MESSAGE,
                     QIcon(), options, options[0]);
            if (selectedOption == 0) {
                return;
            }
            for (TTTrain* train : trainList) {
                for (Stop* stop : _dataMgr->getStops(train->getTrainId(), 0, false)) {
                    _dataMgr->deleteStop(stop->getStopId());
                }
                _dataMgr->deleteTrain(train->getTrainId());
            }
        }
        // delete the schedule
        _dataMgr->deleteSchedule(_curNodeId);
        setShowReminder(true);

        // Update the tree
        TreePath* parentPath = _curTreePath->getParentPath();
        TimeTableTreeNode* parentNode = (TimeTableTreeNode*) _curNode->getParent();
        _curNode->removeFromParent();
        _curNode  = nullptr;
        _timetableModel->nodeStructureChanged(parentNode);
        _timetableTree->setSelectionPath(parentPath);
    }

    /**
     * Delete a train->
     * If the train contains stops, provide the option to perform
     * a cascade delete of the stops.
     */
    void TimeTableFrame::deleteTrain() {
        QList<Stop*> stopList = QList<Stop*>(_dataMgr->getStops(_curNodeId, 0, true));
        if (!stopList.isEmpty()) {
            // The trains still has stops.
            // Present the option to delete the stops and the train
             QVariantList options = {tr("No"), tr("Yes")};  // NOI18N
            int selectedOption = JOptionPane::showOptionDialog( nullptr,
                    tr("There are Stops assigned.\nDelete the stops and the train?"), // NOI18N
                    tr("Question"),   // NOI18N
                    JOptionPane::YES_NO_OPTION,
                    JOptionPane::QUESTION_MESSAGE,
                    QIcon(), options, options[0]);
            if (selectedOption == 0) {
                return;
            }
            for (Stop* stop : stopList) {
                _dataMgr->deleteStop(stop->getStopId());
            }
        }
        // delete the train
        _dataMgr->deleteTrain(_curNodeId);
        setShowReminder(true);

        // Update the tree
        TreePath* parentPath = _curTreePath->getParentPath();
        TimeTableTreeNode* parentNode = (TimeTableTreeNode*) _curNode->getParent();
        _curNode->removeFromParent();
        _curNode  = nullptr;
        _timetableModel->nodeStructureChanged(parentNode);
        _timetableTree->setSelectionPath(parentPath);
    }

    /**
     * Delete a stop->
     */
    void TimeTableFrame::deleteStop() {
        // delete the stop
        _dataMgr->deleteStop(_curNodeId);
        setShowReminder(true);

        // Update the tree
        TreePath* parentPath = _curTreePath->getParentPath();
        TimeTableTreeNode* parentNode = (TimeTableTreeNode*) _curNode->getParent();
        _curNode->removeFromParent();
        _curNode  = nullptr;
        _timetableModel->nodeStructureChanged(parentNode);
        _timetableTree->setSelectionPath(parentPath);
    }

    /**
     * Cancel the current node edit.
     */
    void TimeTableFrame::cancelPressed() {
        setEditMode(false);
        _timetableTree->setSelectionPath(_curTreePath);
//        _timetableTree->grabFocus();
    }

    /**
     * Move a Stop row up 1 row.
     */
    void TimeTableFrame::upPressed() {
        setShowReminder(true);

        DefaultMutableTreeNode* prevNode = _curNode->getPreviousSibling();
        if (!(qobject_cast<TimeTableTreeNode*>(prevNode))) {
            log->warn("At first node, cannot move up");  // NOI18N
            return;
        }
        int prevStopId = ((TimeTableTreeNode*) prevNode)->getId();
        Stop* prevStop = _dataMgr->getStop(prevStopId);
        prevStop->setSeq(prevStop->getSeq() + 1);
        Stop* currStop = _dataMgr->getStop(_curNodeId);
        currStop->setSeq(currStop->getSeq() - 1);
        moveTreeNode("Up");     // NOI18N
    }

    /**
     * Move a Stop row down 1 row.
     */
    void TimeTableFrame::downPressed() {
        setShowReminder(true);

        DefaultMutableTreeNode* nextNode = _curNode->getNextSibling();
        if (!(qobject_cast<TimeTableTreeNode*>(nextNode ))) {
            log->warn("At last node, cannot move down");  // NOI18N
            return;
        }
        int nextStopId = ((TimeTableTreeNode*) nextNode)->getId();
        Stop* nextStop = _dataMgr->getStop(nextStopId);
        nextStop->setSeq(nextStop->getSeq() - 1);
        Stop* currStop = _dataMgr->getStop(_curNodeId);
        currStop->setSeq(currStop->getSeq() + 1);
        moveTreeNode("Down");     // NOI18N
    }

    /**
     * Move a tree node in response to a up or down request.
     *
     * @param direction The direction of movement, Up or Down
     */
    void TimeTableFrame::moveTreeNode(QString direction) {
        // Update the node
        if (direction == ("Up")) {    // NOI18N
            _curNodeRow -= 1;
        } else {
            _curNodeRow += 1;
        }
        _curNode->setRow(_curNodeRow);
        _timetableModel->nodeChanged(_curNode);

        // Update the sibling
        DefaultMutableTreeNode* siblingNode;
        TimeTableTreeNode* tempNode;
        if (direction == ("Up")) {    // NOI18N
            siblingNode = _curNode->getPreviousSibling();
            if (qobject_cast<TimeTableTreeNode*>(siblingNode)) {
                tempNode = (TimeTableTreeNode*) siblingNode;
                tempNode->setRow(tempNode->getRow() + 1);
            }
        } else {
            siblingNode = _curNode->getNextSibling();
            if (qobject_cast<TimeTableTreeNode*>(siblingNode)) {
                tempNode = (TimeTableTreeNode*) siblingNode;
                tempNode->setRow(tempNode->getRow() - 1);
            }
        }
        _timetableModel->nodeChanged(siblingNode);

        // Update the tree
        TimeTableTreeNode* parentNode = (TimeTableTreeNode*) _curNode->getParent();
        parentNode->insert(_curNode, _curNodeRow - 1);
        _timetableModel->nodeStructureChanged(parentNode);
        //_timetableTree->setSelectionPath(new TreePath(_curNode->getPath()));
        QVector<TreeNode*>* v = _curNode->getPath();
        QVector<QObject*>* ov = new QVector<QObject*>();
        foreach(TreeNode* n, *v)
         ov->append((QObject*)n);
        _timetableTree->setSelectionPath(new TreePath(ov));
        setMoveButtons();

        // Update times
        _dataMgr->calculateTrain(_dataMgr->getStop(_curNodeId)->getTrainId(), true);
    }

    /**
     * Enable/Disable the Up and Down buttons based on the postion in the list.
     */
    void TimeTableFrame::setMoveButtons() {
        if (_curNode  == nullptr) {
            return;
        }

        QWidgetList compList = _moveButtonPanel->findChildren<QWidget*>();
        QPushButton* up = (QPushButton*) compList[1];
        QPushButton* down = (QPushButton*) compList[3];

        up->setEnabled(true);
        down->setEnabled(true);

        int rows = _curNode->getSiblingCount();
        if (_curNodeRow < 2) {
            up->setEnabled(false);
        }
        if (_curNodeRow > rows - 1) {
            down->setEnabled(false);
        }

        // Disable move buttons during Variable or Action add or edit processing, or nothing selected
        if (_editActive) {
            up->setEnabled(false);
            down->setEnabled(false);
        }

        _moveButtonPanel->setVisible(true);
    }

    void TimeTableFrame::graphPressed(QString graphType)
    {
     // select a schedule if necessary
     Segment* segment = _dataMgr->getSegment(_curNodeId);
     Layout* layout = _dataMgr->getLayout(segment->getLayoutId());
     int scheduleId;
     QList<TTSchedule*> schedules = _dataMgr->getSchedules(layout->getLayoutId(), true);

     if (schedules.size() == 0) {
         log->warn("no schedule");  // NOI18N
         return;
     }
     else
     {
      scheduleId = schedules.at(0)->getScheduleId();
      if (schedules.size() > 1)
      {
       // do selection dialog
       //QVector<TTSchedule*> schedArr = QVector<TTSchedule*>(schedules.size());
       QVariantList schedArr = QVariantList();
       //schedArr = schedules.toArray(schedArr);
       foreach(TTSchedule* s, schedules)
         schedArr.append(s->getScheduleName());
       QString schedSelected = JOptionPane::showInputDialog(
                nullptr,
               tr("Select the Schedule to be used for the graph."),  // NOI18N
               tr("Question"),  // NOI18N
               JOptionPane::QUESTION_MESSAGE,
               QIcon(),
               schedArr,
               schedArr[0]
       ).toString();
       if (schedSelected.isEmpty()) {
           log->warn("Schedule not selected, graph request cancelled");  // NOI18N
           return;
       }
       //scheduleId = schedSelected->getScheduleId();
       foreach (TTSchedule* s, schedules)
       {
        if(s->getScheduleName() == schedSelected)
        {
         scheduleId = s->getScheduleId();
         break;
        }
       }
      }
     }

     if (graphType == ("Display"))
     {
      TimeTableDisplayGraph* graph = new TimeTableDisplayGraph(_curNodeId, scheduleId, _showTrainTimes);

      JmriJFrame* f = new JmriJFrameX(tr("Timetable Graph"), true, true);  // NOI18N
      f->setMinimumSize(QSize(600, 300));
      f->getContentPane(true)->layout()->addWidget(graph);
      f->pack();
      f->addHelpMenu("html.tools.TimeTable", true);  // NOI18N
      f->setVisible(true);
     }

     if (graphType == ("Print")) {
         TimeTablePrintGraph* print = new TimeTablePrintGraph(_curNodeId, scheduleId, _showTrainTimes, _twoPage);
         print->printGraph();
     }
    }

    void TimeTableFrame::importPressed() {
        fileChooser = XmlFile::userFileChooser("SchedGen File", "sgn");  // NOI18N
        int retVal = fileChooser->showOpenDialog(nullptr);
        if (retVal == JFileChooser::APPROVE_OPTION) {
            File* file = fileChooser->getSelectedFile();
            try {
                (new TimeTableImport())->importSgn(_dataMgr, file);
            } catch (IOException ex) {
                log->error("Import exception: {}", ex);  // NOI18N
                JOptionPane::showMessageDialog(nullptr,
                        tr("The %1 import has failed.\nCheck the JMRI System Console for details."
                           ).arg("SGN"),  // NOI18N
                        tr("Error"),  // NOI18N
                        JOptionPane::ERROR_MESSAGE);
                return;
            }
            savePressed();
            JOptionPane::showMessageDialog(nullptr,
                    tr("The changes have been saved.\nClose and re-open the Timetable to refresh.", "SGN"),  // NOI18N
                    tr("Message"),  // NOI18N
                    JOptionPane::INFORMATION_MESSAGE);
        }
    }

    void TimeTableFrame::importCsvPressed() {
        fileChooser = new JFileChooser(FileUtil::getUserFilesPath());
        fileChooser->setFileFilter("Import File (*csv");//new FileNameExtensionFilter("Import File", "csv"));
        int retVal = fileChooser->showOpenDialog(nullptr);
        if (retVal == JFileChooser::APPROVE_OPTION) {
            File* file = fileChooser->getSelectedFile();
            completeImport(file);
        }
    }

    void TimeTableFrame::completeImport(File* file) {
    #if 0
        try {
            feedbackList = new TimeTableCsvImport().importCsv(file);
        } catch (IOException ex) {
            log->error("Import exception: {}", ex); // NOI18N
            JOptionPane::showMessageDialog(null,
                    tr("ImportCsvFailed", "CVS"), // NOI18N
                    tr("Error"), // NOI18N
                    JOptionPane::ERROR_MESSAGE);
            return;
        }
        if (feedbackList.size() > 0) {
            QString msg = tr("--- CSV Import Errors ---\n"); // NOI18N
            for (String feedback : feedbackList) {
                msg.append(feedback + "\n");
            }
            JOptionPane::showMessageDialog(null,
                    msg,
                    tr("Error"), // NOI18N
                    JOptionPane::ERROR_MESSAGE);
            return;
        }
        savePressed();
        JOptionPane::showMessageDialog(null,
                tr("ImportCompleted", "CSV"), // NOI18N
                tr("MessageTitle"), // NOI18N
                JOptionPane::INFORMATION_MESSAGE);
    #endif
    }

    void TimeTableFrame::importFromOperationsPressed() {
    #if 0
        ExportTimetable ex = new ExportTimetable();
        new ExportTimetable().writeOperationsTimetableFile();
        completeImport(ex.getExportFile());
    #endif
    }

    void TimeTableFrame::exportCsvPressed() {
    #if 0
        // Select layout
        QList<Layout*> layouts = _dataMgr->getLayouts(true);
        if (layouts.size() == 0) {
            JOptionPane::showMessageDialog(nullptr,
                    tr("No layouts have been defined."),  // NOI18N
                    tr("Error"),  // NOI18N
                    JOptionPane::ERROR_MESSAGE);
            return;
        }
        int layoutId = layouts.get(0).getLayoutId();
        if (layouts.size() > 1) {
            Layout* layout = (Layout*) JOptionPane::showInputDialog(
                    nullptr,
                    tr("ExportSelectLayout"),  // NOI18N
                    tr("QuestionTitle"),  // NOI18N
                    JOptionPane::PLAIN_MESSAGE,
                    QIcon()),
                    layouts.toArray(),
                    nullptr);
            if (layout == nullptr) return;
            layoutId = layout->getLayoutId();
        }

        // Select segment
        List<Segment> segments = _dataMgr->getSegments(layoutId, true);
        if (segments.size() == 0) {
            JOptionPane::showMessageDialog(null,
                    tr("ExportSegmentError"),  // NOI18N
                    tr("Error"),  // NOI18N
                    JOptionPane::ERROR_MESSAGE);
            return;
        }
        int segmentId = segments.get(0).getSegmentId();
        if (segments.size() > 1) {
            Segment segment = (Segment) JOptionPane::showInputDialog(
                    null,
                    tr("ExportSelectSegment"),  // NOI18N
                    tr("QuestionTitle"),  // NOI18N
                    JOptionPane::PLAIN_MESSAGE,
                    null,
                    segments.toArray(),
                    null);
            if (segment == null) return;
            segmentId = segment.getSegmentId();
        }

        // Select schedule
        List<Schedule> schedules = _dataMgr->getSchedules(layoutId, true);
        if (schedules.size() == 0) {
            JOptionPane::showMessageDialog(null,
                    tr("ExportScheduleError"),  // NOI18N
                    tr("Error"),  // NOI18N
                    JOptionPane::ERROR_MESSAGE);
            return;
        }
        int scheduleId = schedules.get(0).getScheduleId();
        if (schedules.size() > 1) {
            Schedule schedule = (Schedule) JOptionPane::showInputDialog(
                    null,
                    tr("ExportSelectSchedule"),  // NOI18N
                    tr("QuestionTitle"),  // NOI18N
                    JOptionPane::PLAIN_MESSAGE,
                    null,
                    schedules.toArray(),
                    null);
            if (schedule == null) return;
            scheduleId = schedule->getScheduleId();
        }

        fileChooser = new JFileChooser(jmri.util.FileUtil.getUserFilesPath());
        fileChooser.setFileFilter(new FileNameExtensionFilter("Export as CSV File", "csv"));  // NOI18N
        int retVal = fileChooser.showSaveDialog(null);
        if (retVal == JFileChooser.APPROVE_OPTION) {
            File file = fileChooser.getSelectedFile();
            String fileName = file.getAbsolutePath();
            String fileNameLC = fileName.toLowerCase();
            if (!fileNameLC.endsWith(".csv")) {  // NOI18N
                fileName = fileName + ".csv";  // NOI18N
                file = new File(fileName);
            }
            if (file.exists()) {
                if (JOptionPane::showConfirmDialog(null,
                        tr("FileOverwriteWarning", file.getName()),  // NOI18N
                        tr("QuestionTitle"),  // NOI18N
                        JOptionPane::OK_CANCEL_OPTION,
                        JOptionPane::QUESTION_MESSAGE) != JOptionPane::OK_OPTION) {
                    return;
                }
            }


            bool hasErrors;
            try {
                hasErrors = new TimeTableCsvExport().exportCsv(file, layoutId, segmentId, scheduleId);
            } catch (IOException ex) {
                log->error("Export exception: {}", ex);  // NOI18N
                JOptionPane::showMessageDialog(null,
                        tr("ExportFailed"),  // NOI18N
                        tr("Error"),  // NOI18N
                        JOptionPane::ERROR_MESSAGE);
                return;
            }

            if (hasErrors) {
                JOptionPane::showMessageDialog(null,
                        tr("ExportFailed"),  // NOI18N
                        tr("Error"),  // NOI18N
                        JOptionPane::ERROR_MESSAGE);
            } else {
                JOptionPane::showMessageDialog(null,
                        tr("ExportCompleted", file),  // NOI18N
                        tr("MessageTitle"),  // NOI18N
                        JOptionPane::INFORMATION_MESSAGE);
            }
        }
    #endif
    }

    /**
     * Save the current set of timetable data.
     */
    void TimeTableFrame::savePressed() {
        TimeTableXml::doStore();
        setShowReminder(false);
    }

    /**
     * Check for pending updates and close if none or approved.
     */
    void TimeTableFrame::donePressed() {
        if (_isDirty) {
            QVariantList options = {tr("No"),  tr("Yes")};  // NOI18N
            int selectedOption = JOptionPane::showOptionDialog(nullptr,
                    tr("Timetable changes have not been saved.\nDiscard changes and exit?"), // NOI18N
                    tr("Warning"),   // NOI18N
                    JOptionPane::YES_NO_OPTION,
                    JOptionPane::WARNING_MESSAGE,
                    QIcon(), options, options[0]);
            if (selectedOption == 0) {
                return;
            }
        }
        InstanceManager::reset("TimeTableFrame");
        dispose();
    }

    // ------------  Tree Content and Navigation ------------

    /**
     * Create the TimeTable tree structure.
     *
     * @return _timetableTree The tree ddefinition with its content
     */
    JTree* TimeTableFrame::buildTree() {
        _timetableRoot = new DefaultMutableTreeNode("Root Node");      // NOI18N
        _timetableModel = new DefaultTreeModel(_timetableRoot);
        _timetableTree = new JTree(_timetableModel);

        createTimeTableContent();

        // build the tree GUI
        _timetableTree->expandPath(new TreePath(_timetableRoot));
        _timetableTree->setRootVisible(false);
        _timetableTree->setShowsRootHandles(true);
        _timetableTree->setScrollsOnExpand(true);
        _timetableTree->setExpandsSelectedPaths(true);
        _timetableTree->getSelectionModel()->setSelectionMode(TreeSelectionModel::SINGLE_TREE_SELECTION);

        // tree listeners
        _timetableTree->addTreeSelectionListener(_timetableListener = new TTFTreeSelectionListener(this));
//        {
//            @Override
//            /*public*/ void valueChanged(TreeSelectionEvent e) {
//                if (_editActive) {
//                    if (e.getNewLeadSelectionPath() != _curTreePath) {
//                        _timetableTree->setSelectionPath(e.getOldLeadSelectionPath());
//                        showNodeEditMessage();
//                    }
//                    return;
//                }

//                _curTreePath = _timetableTree->getSelectionPath();
//                if (_curTreePath != null) {
//                    Object chkLast = _curTreePath.getLastPathComponent();
//                    if (chkLast instanceof TimeTableTreeNode) {
//                        treeRowSelected((TimeTableTreeNode*) chkLast);
//                    }
//                }
//            }
//        });

        //addLayout();
        return _timetableTree;
    }

    /**
     * Create the tree content.
     * Level 1 -- Layouts
     * Level 2 -- Train Type, Segment and Schedule Containers
     * Level 3 -- Train Types, Segments, Schedules
     * Level 4 -- Stations, Trains
     * Level 5 -- Stops
     */
    void TimeTableFrame::createTimeTableContent()
    {
     for (Layout* l : _dataMgr->getLayouts(true))
     {
      _layoutNode = new TimeTableTreeNode(l->getLayoutName(), "Layout", l->getLayoutId(), 0);    // NOI18N
      _timetableRoot->add(_layoutNode);

      _typeHead = new TimeTableTreeNode(buildNodeText("TrainTypes", nullptr, 0), "TrainTypes", 0, 0);    // NOI18N
      _layoutNode->add(_typeHead);
      for (TrainType* y : _dataMgr->getTrainTypes(l->getLayoutId(), true))
      {
       _typeNode = new TimeTableTreeNode(y->getTypeName(), "TrainType", y->getTypeId(), 0);    // NOI18N
       _typeHead->add(_typeNode);
      }

      _segmentHead = new TimeTableTreeNode(buildNodeText("Segments", nullptr, 0), "Segments", 0, 0);    // NOI18N
      _layoutNode->add(_segmentHead);
      for (Segment* sg : _dataMgr->getSegments(l->getLayoutId(), true))
      {
       _segmentNode = new TimeTableTreeNode(sg->getSegmentName(), "Segment", sg->getSegmentId(), 0);    // NOI18N
       _segmentHead->add(_segmentNode);
       for (Station* st : _dataMgr->getStations(sg->getSegmentId(), true)) {
           _leafNode = new TimeTableTreeNode(st->getStationName(), "Station", st->getStationId(), 0);    // NOI18N
           _segmentNode->add(_leafNode);
       }
      }

      _scheduleHead = new TimeTableTreeNode(buildNodeText("Schedules", nullptr, 0), "Schedules", 0, 0);    // NOI18N
      _layoutNode->add(_scheduleHead);
      for (TTSchedule* c : _dataMgr->getSchedules(l->getLayoutId(), true))
      {
       _scheduleNode = new TimeTableTreeNode(buildNodeText("Schedule", c, 0), "Schedule", c->getScheduleId(), 0);    // NOI18N
       _scheduleHead->add(_scheduleNode);
       for (TTTrain* tr : _dataMgr->getTrains(c->getScheduleId(), 0, true))
       {
        _trainNode = new TimeTableTreeNode(buildNodeText("Train", tr, 0), "Train", tr->getTrainId(), 0);    // NOI18N
        _scheduleNode->add(_trainNode);
        for (Stop* sp : _dataMgr->getStops(tr->getTrainId(), 0, true)) {
            _leafNode = new TimeTableTreeNode(buildNodeText("Stop", sp, 0), "Stop", sp->getStopId(), sp->getSeq());    // NOI18N
            _trainNode->add(_leafNode);
        }
       }
      }
     }
    }

    /**
     * Create the localized node text display strings based on node type.
     *
     * @param nodeType  The type of the node
     * @param component The object or child object
     * @param idx       Optional index value
     * @return nodeText containing the text to display on the node
     */
    QString TimeTableFrame::buildNodeText(QString nodeType, QObject* component, int idx) {
        if(nodeType=="TrainTypes")
                return tr("Train Types");
        else if(nodeType==    "Segments")
                return tr("Segments");
        else if(nodeType== "Schedules")
                return tr("Schedules");
        else if(nodeType== "Schedule")
        {
         TTSchedule* schedule = (TimeTable::TTSchedule*) component;
         return tr("%1   Effective Date: %2").arg(schedule->getScheduleName()).arg(schedule->getEffDate());
        }
        else if(nodeType== "Train")
        {
          TTTrain* train = (TTTrain*) component;
          return tr("%1 -- %2").arg(train->getTrainName()).arg(train->getTrainDesc());
        }
        else if(nodeType== "Stop")
        {
          Stop* stop = (Stop*) component;
          int stationId = stop->getStationId();
          return tr("%1 -- %2").arg(stop->getSeq()).arg(_dataMgr->getStation(stationId)->getStationName());
        }
        else
        {
         return "None";
        }
    }

    /**
     * Change the button row based on the currently selected node type. Invoke
     * edit where appropriate.
     *
     * @param selectedNode The node object
     */
    void TimeTableFrame::treeRowSelected(TimeTableTreeNode* selectedNode)
    {
        // Set the current node variables
        _curNode  = selectedNode;
        _curNodeId = selectedNode->getId();
        _curNodeType = selectedNode->getType();
        _curNodeText = selectedNode->getText();
        _curNodeRow = selectedNode->getRow();

        // Reset button bar
        _addButtonPanel->setVisible(false);
        _deleteButtonPanel->setVisible(false);
        _moveButtonPanel->setVisible(false);
        _graphButtonPanel->setVisible(false);

        if(_curNodeType=="Layout")
        {
         _addButton->setText(tr("New Layout"));  // NOI18N
         _addButtonPanel->setVisible(true);
         _deleteButton->setText(tr("Delete Layout"));  // NOI18N
         _deleteButtonPanel->setVisible(true);
         editPressed();
        }
        else if(_curNodeType== "TrainTypes") {
         _addButton->setText(tr("Add Train Type"));  // NOI18N
         _addButtonPanel->setVisible(true);
         makeDetailGrid(EMPTY_GRID);  // NOI18N
        }
        else if(_curNodeType== "TrainType") {
          _deleteButton->setText(tr("Delete Train Type"));  // NOI18N
          _deleteButtonPanel->setVisible(true);
          editPressed();
        }
        else if(_curNodeType== "Segments") {
         _addButton->setText(tr("Add Segment"));  // NOI18N
         _addButtonPanel->setVisible(true);
         makeDetailGrid(EMPTY_GRID);  // NOI18N
        }
        else if(_curNodeType== "Segment") {
         _addButton->setText(tr("Add Station"));  // NOI18N
         _addButtonPanel->setVisible(true);
         _deleteButton->setText(tr("Delete Segment"));  // NOI18N
         _deleteButtonPanel->setVisible(true);
         _graphButtonPanel->setVisible(true);
         editPressed();
        }
        else if(_curNodeType== "Station") {
         _deleteButton->setText(tr("Delete Station"));  // NOI18N
         _deleteButtonPanel->setVisible(true);
         editPressed();
        }
        else if(_curNodeType== "Schedules") {
          _addButton->setText(tr("Add Schedule"));  // NOI18N
          _addButtonPanel->setVisible(true);
          makeDetailGrid(EMPTY_GRID);  // NOI18N
        }
        else if(_curNodeType=="Schedule") {
         _addButton->setText(tr("Add Train"));  // NOI18N
         _addButtonPanel->setVisible(true);
         _deleteButton->setText(tr("Delete Schedule"));  // NOI18N
         _deleteButtonPanel->setVisible(true);
         editPressed();
        }
        else if(_curNodeType== "Train") {
         _addButton->setText(tr("Add Stop"));  // NOI18N
         _addButtonPanel->setVisible(true);
         _deleteButton->setText(tr("Delete Train"));  // NOI18N
         _deleteButtonPanel->setVisible(true);
         editPressed();
        }
        else if(_curNodeType=="Stop") {
         _deleteButton->setText(tr("Delete Stop"));  // NOI18N
         _deleteButtonPanel->setVisible(true);
         editPressed();
        }
        else
        {
         log->warn("Should not be here");  // NOI18N
        }
    }

    /**
     * Display reminder to save.
     */
    void TimeTableFrame::showNodeEditMessage() {
        if (InstanceManager::getNullableDefault("UserPreferencesManager") != nullptr) {
            ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->
                    showInfoMessage(tr("Active Node Edit"), // NOI18N
            tr("Another node cannot be selected while editing a node. Select Cancel or Update to complete the edit."), // NOI18N
            getClassName(),
            "SkipTimeTableEditMessage"); // NOI18N
        }
    }

    /**
     * Set/clear dirty flag and save button
     * @param dirty True if changes have been made that are not saved.
     */
    /*public*/ void TimeTableFrame::setShowReminder(bool dirty) {
        _isDirty = dirty;
        _saveButton->setEnabled(dirty);
    }

    /**
     * Enable/disable buttons based on edit state.
     * The edit state controls the ability to select tree nodes.
     *
     * @param active True to make edit active, false to make edit inactive
     */
    void TimeTableFrame::setEditMode(bool active) {
        _editActive = active;
        _cancelAction->setEnabled(active);
        _updateAction->setEnabled(active);
        _addButton->setEnabled(!active);
        _deleteButton->setEnabled(!active);
        if (_curNodeType != nullptr && _curNodeType == ("Stop")) {  // NOI18N
            setMoveButtons();
        }
    }
#if 0
    /**
     * Timetable Tree Node Definition.
     */
    static class TimeTableTreeNode extends DefaultMutableTreeNode {

        private String ttText;
        private String ttType;
        private int ttId;
        private int ttRow;

        /*public*/ TimeTableTreeNode(String nameText, String type, int sysId, int row) {
            this.ttText = nameText;
            this.ttType = type;
            this.ttId = sysId;
            this.ttRow = row;
        }

        /*public*/ String getType() {
            return ttType;
        }

        /*public*/ int getId() {
            return ttId;
        }

        /*public*/ void setId(int newId) {
            ttId = newId;
        }

        /*public*/ int getRow() {
            return ttRow;
        }

        /*public*/ void setRow(int newRow) {
            ttRow = newRow;
        }

        /*public*/ String getText() {
            return ttText;
        }

        /*public*/ void setText(String newText) {
            ttText = newText;
        }

        @Override
        /*public*/ String toString() {
            return ttText;
        }
    }
#endif
    /*protected*/ QString TimeTableFrame::getClassName() {
        return "jmri.jmrit.timetable.swing.TimeTableFrame";
    }

    /*private*/ /*static*/ /*final*/ Logger* TimeTableFrame::log = LoggerFactory::getLogger("TimeTableFrame");
}
