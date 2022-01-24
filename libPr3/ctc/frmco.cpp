#include "frmco.h"
#include "commonsubs.h"
#include "listselectionmodel.h"
#include "joptionpane.h"
#include "callondata.h"
#include "blockmanager.h"
#include "instancemanager.h"
#include "codebuttonhandlerdataroutines.h"
#include "vptr.h"

/**
 *
 * @author Gregory J. Bedlek Copyright (C) 2018, 2019
 */
// /*public*/ class FrmCO extends JFrame {
    /**
     * Creates new form DlgCO
     */
    /*private*/ /*static*/ /*final*/ QString FrmCO::FORM_PROPERTIES = "DlgCO";  // NOI18N
    /*private*/ /*static*/ /*final*/ QString FrmCO::PREFIX = "_mCO_";           // NOI18N

    /*private*/ void FrmCO::initOrig() {
        int defaultListModelSize = _mDefaultListModel->size();
        for (int index = 0; index < defaultListModelSize; index++) {
            _mDefaultListModelOrig.append(VPtr<CallOnData>::asPtr(_mDefaultListModel->get(index)));
        }
    }
    /*private*/ bool FrmCO::dataChanged() {
        int defaultListModelSize = _mDefaultListModel->size();
        if (defaultListModelSize != _mDefaultListModelOrig.size()) return true;
        for (int index = 0; index < defaultListModelSize; index++) {
            if (VPtr<CallOnData>::asPtr(_mDefaultListModel->get(index)) != _mDefaultListModelOrig.at(index)) return true;
        }
        return false;
    }

    /*public*/ FrmCO::FrmCO(AwtWindowProperties* awtWindowProperties, CodeButtonHandlerData* codeButtonHandlerData, ProgramProperties* programProperties,
                    CTCSerialData* ctcSerialData, CheckJMRIObject *checkJMRIObject, bool signalHeadSelected, QWidget* parent) : JFrame(parent){
        //super();
        initComponents();
        CommonSubs::addHelpMenu(this, "package.jmri.jmrit.ctc.CTC_frmCO", true);  // NOI18N
//        _mSignalFacingDirection->setModel(new DefaultComboBoxModel<>(new String[] {  tr("InfoDlgCOLeftTraffic"),
//                                                                                                tr("InfoDlgCORightTraffic") }));
        _mSignalFacingDirection->addItems({tr("LEFTTRAFFIC"),tr("RIGHTTRAFFIC") });
//        _mSignalAspectToDisplay->setModel(new DefaultComboBoxModel<>(new String[] {  tr("SignalHeadStateDark"),
//                                                                                                tr("SignalHeadStateRed"),
//                                                                                                tr("SignalHeadStateYellow"),
//                                                                                                tr("SignalHeadStateGreen"),
//                                                                                                tr("SignalHeadStateFlashingRed"),
//                                                                                                tr("SignalHeadStateFlashingYellow"),
//                                                                                                tr("SignalHeadStateFlashingGreen"),
//                                                                                                tr("SignalHeadStateLunar"),
//                                                                                                tr("SignalHeadStateFlashingLunar") }));
       _mSignalAspectToDisplay->addItems({  tr("Dark"),tr("Red"),tr("Yellow"),tr("Green"),tr("FlashingRed"),tr("FlashingYellow"),tr("FlashingGreen"),tr("StateLunar"),
                                                                                                                                            tr("FlashingLunar") });
        _mAwtWindowProperties = awtWindowProperties;
        _mCodeButtonHandlerData = codeButtonHandlerData;
        _mProgramProperties = programProperties;
        _mCTCSerialData = ctcSerialData;
        _mCheckJMRIObject = checkJMRIObject;
        _mSignalHeadSelected = signalHeadSelected;
        CommonSubs::populateJComboBoxWithBeans(_mCO_CallOnToggleInternalSensor, "Sensor", _mCodeButtonHandlerData->_mCO_CallOnToggleInternalSensor->getHandleName(), false);   // NOI18N

        _mDefaultListModel = new DefaultListModel();
        _mGroupingsList->setModel(_mDefaultListModel);
//  Once you specify a model, then functions like JList->setListData may update the screen, but the model
//  DOES NOT SEE ANY OF THE DATA!  Therefore, I have to load the data via the model instead of directly:
        _mDefaultListModel->clear(); // Superflous but doesn't hurt in case GUI designer put something in there.....
        for (CallOnData* callOnData : *_mCodeButtonHandlerData->_mCO_GroupingsList) {
            _mDefaultListModel->addElement(VPtr<CallOnData>::asQVariant(callOnData));
        }
        initOrig();

        QList<QString> arrayListOfSelectableSwitchDirectionIndicators
          = CommonSubs::getArrayListOfSelectableSwitchDirectionIndicators(_mCTCSerialData->getCodeButtonHandlerDataArrayList());
        arrayListOfSelectableSwitchDirectionIndicators.insert(0, "");     // None is always available.
        QVector<QString> arrayOfSelectableSwitchDirectionIndicators = QVector<QString>(arrayListOfSelectableSwitchDirectionIndicators.size());
#if 0
        arrayOfSelectableSwitchDirectionIndicators = arrayListOfSelectableSwitchDirectionIndicators(arrayOfSelectableSwitchDirectionIndicators.toList());
#endif
        //  If I used "defaultComboBoxModel" in the calls below, that would cause ALL dropdowns to be tied together!  Changing one would change all!
//      DefaultComboBoxModel<String> defaultComboBoxModel = new DefaultComboBoxModel<>(arrayOfSelectableSwitchDirectionIndicators);
//  And there is NO copy constructor for "defaultComboBoxModel", ergo the hard way:
        //_mSwitchIndicator1->setModel(new DefaultComboBoxModel<>(arrayOfSelectableSwitchDirectionIndicators));
        _mSwitchIndicator1->addItems(arrayOfSelectableSwitchDirectionIndicators.toList());
//        _mSwitchIndicator2->setModel(new DefaultComboBoxModel<>(arrayOfSelectableSwitchDirectionIndicators));
        _mSwitchIndicator2->addItems(arrayOfSelectableSwitchDirectionIndicators.toList());
//        _mSwitchIndicator3->setModel(new DefaultComboBoxModel<>(arrayOfSelectableSwitchDirectionIndicators));
        _mSwitchIndicator3->addItems(arrayOfSelectableSwitchDirectionIndicators.toList());
//        _mSwitchIndicator4->setModel(new DefaultComboBoxModel<>(arrayOfSelectableSwitchDirectionIndicators));
        _mSwitchIndicator4->addItems(arrayOfSelectableSwitchDirectionIndicators.toList());
//        _mSwitchIndicator5->setModel(new DefaultComboBoxModel<>(arrayOfSelectableSwitchDirectionIndicators));
        _mSwitchIndicator5->addItems(arrayOfSelectableSwitchDirectionIndicators.toList());
//        _mSwitchIndicator6->setModel(new DefaultComboBoxModel<>(arrayOfSelectableSwitchDirectionIndicators));
        _mSwitchIndicator6->addItems(arrayOfSelectableSwitchDirectionIndicators.toList());

        _mAwtWindowProperties->setWindowState(this, FORM_PROPERTIES);
        enableTopPart(true);
        _mEditBelow->setEnabled(false);
        _mDelete->setEnabled(false);
    }

     /*public*/ /*static*/ bool FrmCO::dialogCodeButtonHandlerDataValid(CheckJMRIObject* checkJMRIObject, CodeButtonHandlerData* codeButtonHandlerData) {
         if (!codeButtonHandlerData->_mCO_Enabled) return true;  // Not enabled, can be no error!
 //  Checks:
         for (CallOnData* callOnDataRow : *codeButtonHandlerData->_mCO_GroupingsList) {
             if (!checkJMRIObject->validClass(VPtr<CallOnData>::asQVariant( callOnDataRow))) return false;
         }
         return checkJMRIObject->validClassWithPrefix(PREFIX, VPtr<CodeButtonHandlerData>::asQVariant(codeButtonHandlerData));
     }

//  Validate all internal fields as much as possible:
    /*private*/ QList<QString> FrmCO::formFieldsValid() {
        QList<QString> errors = QList<QString>();
//  Checks:
        _mCheckJMRIObject->analyzeForm(PREFIX, this, errors);
        return errors;
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    // <editor-fold defaultstate="collapsed" desc="Generated Code">
    /*private*/ void FrmCO::initComponents() {

        _mSaveAndClose = new JButton();
        _mCO_CallOnToggleInternalSensorPrompt = new JLabel();
        _mCO_CallOnToggleInternalSensor = new JComboBox();
        _mGroupingsListPrompt = new JLabel();
        jLabel5 = new JLabel();
        jLabel6 = new JLabel();
        jLabel7 = new JLabel();
        jLabel8 = new JLabel();
        jLabel10 = new JLabel();
        jLabel11 = new JLabel();
        jLabel12 = new JLabel();
        jLabel13 = new JLabel();
        jLabel15 = new JLabel();
        _mSignalFacingDirection = new JComboBox();
        _mSignalAspectToDisplay = new JComboBox();
//        jScrollPane1 = new JScrollPane();
        _mGroupingsList = new JList();
        _mDelete = new JButton();
        _mEditBelow = new JButton();
        _mAddNew = new JButton();
        jLabel1 = new JLabel();
        jLabel3 = new JLabel();
        _mGroupingListAddReplace = new JButton();
        jButton2 = new JButton();
        _mCancel = new JButton();
        jLabel4 = new JLabel();
        jLabel16 = new JLabel();
        jLabel17 = new JLabel();
        jLabel9 = new JLabel();
        jLabel14 = new JLabel();
        _mSwitchIndicator1 = new JComboBox();
        _mSwitchIndicator2 = new JComboBox();
        _mSwitchIndicator3 = new JComboBox();
        _mSwitchIndicator4 = new JComboBox();
        _mSwitchIndicator6 = new JComboBox();
        _mSwitchIndicator5 = new JComboBox();
        _mExternalSignal = new JComboBox();
        _mCalledOnExternalSensor = new JComboBox();
        _mExternalBlock = new JComboBox();
        jLabel18 = new JLabel();

        setDefaultCloseOperation(JFrame::DO_NOTHING_ON_CLOSE);
        setTitle(tr("Edit Call-on"));
//        addWindowListener(new java.awt.event.WindowAdapter() {
//            @Override
//            /*public*/ void windowClosing(java.awt.event.WindowEvent evt) {
//                formWindowClosing(evt);
//            }
//        });
        addWindowListener(new FrmCO_windowListener(this));

        _mSaveAndClose->setText(tr("Save and Close"));
//        _mSaveAndClose.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
        connect(_mSaveAndClose, &JButton::clicked, [=]{
                _mSaveAndCloseActionPerformed(/*evt*/);
//            }
        });

        _mCO_CallOnToggleInternalSensorPrompt->setText(tr("Toggle sensor:"));

        //_mCO_CallOnToggleInternalSensor->setModel(new DefaultComboBoxModel<>(new String[] { "Item 1", "Item 2", "Item 3", "Item 4" }));
        _mCO_CallOnToggleInternalSensor->addItems({ "Item 1", "Item 2", "Item 3", "Item 4" });

        _mGroupingsListPrompt->setText(tr("Grouping list:"));

        jLabel5->setText(tr("Based upon Signal Type selected, various values are needed below and enabled for editing:"));

        jLabel6->setText(tr("Signal:"));

        jLabel7->setText(tr("Signal facing direction:"));

        jLabel8->setText(tr("Aspect:"));

        jLabel10->setText(tr("Called on sensor:"));

        jLabel11->setText(tr("A standard JMRI signal head or signal mast which will get the Call-on aspect."));

        jLabel12->setText(tr("LEFTTRAFFIC or RIGHTTRAFFIC"));

        jLabel13->setText(tr("For Signal Heads: Dark, Red, Yellow (Semaphores), Green, Flashing Red (Signals), Flashing Yellow, Flashing Green, Lunar, Flashing Lunar"));

        jLabel15->setText(tr("For Signal Heads: required JMRI Sensor for occupancy in the direction indicated (i.e. the sensor where the train is ultimately GOING) which MUST be occupied."));

        _mGroupingsList->setSelectionMode(/*ListSelectionModel::SINGLE_SELECTION*/QAbstractItemView::SingleSelection);
//        _mGroupingsList.addListSelectionListener(new event.ListSelectionListener() {
//            @Override
//            /*public*/ void valueChanged(event.ListSelectionEvent evt) {
//                _mGroupingsListValueChanged(evt);
//            }
//        });
        _mGroupingsList->addListSelectionListener(new FrmCO_listSelectionListener(this));
        //jScrollPane1->setViewportView(_mGroupingsList);

        _mDelete->setText(tr("Delete"));
//        _mDelete.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
        connect(_mDelete, &JButton::clicked, [=]{
                _mDeleteActionPerformed(/*evt*/);
//            }
        });

        _mEditBelow->setText(tr("Edit Below"));
//        _mEditBelow.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
        connect(_mEditBelow, &JButton::clicked, [=]{
                _mEditBelowActionPerformed(/*evt*/);
//            }
        });

        _mAddNew->setText(tr("Add New")
        );
//        _mAddNew.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
        connect(_mAddNew, &JButton::clicked, [=]{
                _mAddNewActionPerformed(/*evt*/);
//            }
        });

        jLabel1->setText(tr("Signal:"));

        jLabel3->setText(tr("Called on sensor:"));

        _mGroupingListAddReplace->setText("      ");
        _mGroupingListAddReplace->setEnabled(false);
//        _mGroupingListAddReplace.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
        connect(_mGroupingListAddReplace, &JButton::clicked, [=]{
                _mGroupingListAddReplaceActionPerformed(/*evt*/);
//            }
        });

        jButton2->setText(tr("Reapply patterns - this form ONLY!"));
//        jButton2.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
        connect(jButton2, &JButton::clicked, [=]{
                jButton2ActionPerformed(/*evt*/);
//            }
        });

        _mCancel->setText(tr("Cancel"));
//        _mCancel.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
        connect(_mCancel, &JButton::clicked, [=]{
                _mCancelActionPerformed(/*evt*/);
//            }
        });

        jLabel4->setText(tr("Block:"));

        jLabel16->setText(tr("Block:"));

        jLabel17->setText(tr("For Signal Masts: the \"Permissive\" aspect needs to be set in the specified block, and additionally the occupancy sensor associated with it MUST be occupied."));

        jLabel9->setText(tr("--------------------------------------- ROUTE ---------------------------------------"));

        jLabel14->setText(tr("Select up to 6 (all optional) switch direction indicators (when lit) to specify the route exactly:"));

//        _mSwitchIndicator1.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
        connect(_mSwitchIndicator1, &JComboBox::currentIndexChanged, [=]{
                _mSwitchIndicator1ActionPerformed(/*evt*/);
//            }
        });

        jLabel18->setText(tr("Aspect:"));
#if 0
        GroupLayout layout = new GroupLayout(getContentPane());
        getContentPane()->setLayout(layout);
        layout->setHorizontalGroup(
            layout.createParallelGroup(GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addGap(34, 34, 34)
                        .addGroup(layout.createParallelGroup(GroupLayout.Alignment.TRAILING)
                            .addComponent(jLabel7)
                            .addComponent(jLabel8)
                            .addComponent(jLabel6)
                            .addComponent(jLabel10)
                            .addComponent(jLabel16))
                        .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                            .addComponent(jLabel11)
                            .addComponent(jLabel12)
                            .addComponent(jLabel13)
                            .addComponent(jLabel15)
                            .addComponent(jLabel17)))
                    .addComponent(jLabel5)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(jButton2)
                        .addGap(252, 252, 252)
                        .addComponent(_mSaveAndClose))
                    .addGroup(layout.createParallelGroup(GroupLayout.Alignment.TRAILING, false)
                        .addGroup(GroupLayout.Alignment.LEADING, layout.createSequentialGroup()
                            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                                .addGroup(layout.createSequentialGroup()
                                    .addComponent(_mCO_CallOnToggleInternalSensorPrompt)
                                    .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                                    .addComponent(_mCO_CallOnToggleInternalSensor, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
                                .addComponent(_mGroupingsListPrompt, GroupLayout.Alignment.TRAILING))
                            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                            .addComponent(jScrollPane1)
                            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING, false)
                                .addComponent(_mEditBelow, GroupLayout.Alignment.TRAILING, GroupLayout.DEFAULT_SIZE, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                .addComponent(_mAddNew, GroupLayout.Alignment.TRAILING, GroupLayout.DEFAULT_SIZE, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                .addComponent(_mDelete, GroupLayout.Alignment.TRAILING, GroupLayout.DEFAULT_SIZE, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)))
                        .addGroup(GroupLayout.Alignment.LEADING, layout.createSequentialGroup()
                            .addGap(9, 9, 9)
                            .addComponent(jLabel1)
                            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                            .addComponent(_mExternalSignal, GroupLayout.PREFERRED_SIZE, 158, GroupLayout.PREFERRED_SIZE)
                            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                            .addComponent(_mSignalFacingDirection, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                            .addGap(14, 14, 14)
                            .addComponent(jLabel18)
                            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                            .addComponent(_mSignalAspectToDisplay, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                            .addGap(18, 18, 18)
                            .addComponent(jLabel3)
                            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                            .addComponent(_mCalledOnExternalSensor, GroupLayout.PREFERRED_SIZE, 165, GroupLayout.PREFERRED_SIZE)
                            .addGap(12, 12, 12))
                        .addGroup(GroupLayout.Alignment.LEADING, layout.createSequentialGroup()
                            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                                .addComponent(jLabel9)
                                .addComponent(jLabel14)
                                .addGroup(layout.createSequentialGroup()
                                    .addComponent(_mSwitchIndicator1, GroupLayout.PREFERRED_SIZE, 110, GroupLayout.PREFERRED_SIZE)
                                    .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                                    .addComponent(_mSwitchIndicator2, GroupLayout.PREFERRED_SIZE, 110, GroupLayout.PREFERRED_SIZE)
                                    .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                                    .addComponent(_mSwitchIndicator3, GroupLayout.PREFERRED_SIZE, 110, GroupLayout.PREFERRED_SIZE)
                                    .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                                    .addComponent(_mSwitchIndicator4, GroupLayout.PREFERRED_SIZE, 110, GroupLayout.PREFERRED_SIZE)
                                    .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                                    .addComponent(_mSwitchIndicator5, GroupLayout.PREFERRED_SIZE, 110, GroupLayout.PREFERRED_SIZE)
                                    .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                                    .addComponent(_mSwitchIndicator6, GroupLayout.PREFERRED_SIZE, 110, GroupLayout.PREFERRED_SIZE)))
                            .addGap(18, 18, 18)
                            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                                .addGroup(layout.createSequentialGroup()
                                    .addComponent(_mGroupingListAddReplace, GroupLayout.PREFERRED_SIZE, 340, GroupLayout.PREFERRED_SIZE)
                                    .addGap(0, 66, Short.MAX_VALUE))
                                .addGroup(layout.createSequentialGroup()
                                    .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                                        .addGroup(layout.createSequentialGroup()
                                            .addComponent(_mCancel)
                                            .addGap(0, 0, Short.MAX_VALUE))
                                        .addGroup(GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                                            .addGap(0, 0, Short.MAX_VALUE)
                                            .addComponent(jLabel4)))
                                    .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                                    .addComponent(_mExternalBlock, GroupLayout.PREFERRED_SIZE, 165, GroupLayout.PREFERRED_SIZE))))))
                .addContainerGap(GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
        layout->setVerticalGroup(
            layout.createParallelGroup(GroupLayout.Alignment.LEADING)
            .addGroup(GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(_mGroupingsListPrompt)
                        .addGap(45, 45, 45)
                        .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                            .addComponent(_mCO_CallOnToggleInternalSensorPrompt)
                            .addComponent(_mCO_CallOnToggleInternalSensor, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)))
                    .addComponent(jScrollPane1, GroupLayout.PREFERRED_SIZE, 117, GroupLayout.PREFERRED_SIZE)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(_mAddNew)
                        .addGap(18, 18, 18)
                        .addComponent(_mEditBelow)
                        .addGap(18, 18, 18)
                        .addComponent(_mDelete)))
                .addGap(18, 18, 18)
                .addComponent(jLabel5)
                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                    .addComponent(jLabel6)
                    .addComponent(jLabel11))
                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                    .addComponent(jLabel7)
                    .addComponent(jLabel12))
                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                    .addComponent(jLabel8)
                    .addComponent(jLabel13))
                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                    .addComponent(jLabel10)
                    .addComponent(jLabel15))
                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                    .addComponent(jLabel16)
                    .addComponent(jLabel17))
                .addGap(18, 18, 18)
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                    .addComponent(_mSignalFacingDirection, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                    .addComponent(_mSignalAspectToDisplay, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                    .addComponent(jLabel1)
                    .addComponent(jLabel3)
                    .addComponent(jLabel4)
                    .addComponent(_mExternalSignal, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                    .addComponent(_mCalledOnExternalSensor, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                    .addComponent(_mExternalBlock, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                    .addComponent(jLabel18))
                .addGap(18, 18, 18)
                .addComponent(jLabel9)
                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                    .addComponent(jLabel14)
                    .addComponent(_mCancel))
                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                    .addComponent(_mSwitchIndicator1, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                    .addComponent(_mSwitchIndicator2, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                    .addComponent(_mSwitchIndicator3, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                    .addComponent(_mSwitchIndicator4, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                    .addComponent(_mSwitchIndicator5, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                    .addComponent(_mSwitchIndicator6, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                    .addComponent(_mGroupingListAddReplace))
                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED, 8, Short.MAX_VALUE)
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                    .addComponent(_mSaveAndClose)
                    .addComponent(jButton2))
                .addGap(18, 18, 18))
        );
#else
    JPanel* contentPane = new JPanel();
    contentPane->setLayout(new QVBoxLayout());
    setCentralWidget(contentPane);

    QGridLayout* grid;
    JPanel* panel1 =  new JPanel(grid = new QGridLayout());
    grid->addWidget(_mGroupingsListPrompt, 0, 1, 1, 2, Qt::AlignLeft);
    grid->addWidget(_mGroupingsList, 0, 2, 1, -1);
    grid->addWidget(_mAddNew);

    grid->addWidget(_mCO_CallOnToggleInternalSensorPrompt, 2, 0);
    grid->addWidget(_mCO_CallOnToggleInternalSensor, 2, 1);
    grid->addWidget(_mEditBelow, 2, 3);

    grid->addWidget(_mDelete, 4, 3);
    contentPane->layout()->addWidget(panel1);

    JPanel* panel2 = new JPanel(grid = new QGridLayout());
    grid->addWidget(jLabel5, 0, 0, 1, 2);

    grid->addWidget(jLabel6, 1, 0, 1, 1, Qt::AlignRight); // Signal
    grid->addWidget(jLabel11, 1, 2);

    grid->addWidget(jLabel7, 2, 0, 1, 1, Qt::AlignRight); // Signal dacing direction
    grid->addWidget(jLabel12, 2, 2);

    grid->addWidget(jLabel8, 3, 0, 1, 1, Qt::AlignRight); // Aspect
    grid->addWidget(jLabel13, 3, 2);

    grid->addWidget(jLabel10, 4, 0, 1, 1, Qt::AlignRight); // called on sensor
    grid->addWidget(jLabel15, 4, 2);

    grid->addWidget(jLabel4, 5, 0, 1, 1, Qt::AlignRight); // Block
    grid->addWidget(jLabel17, 5, 2);
    contentPane->layout()->addWidget(panel2);

    JPanel* panel3 = new JPanel(new QHBoxLayout());
    panel3->layout()->addWidget(jLabel1);
    panel3->layout()->addWidget(_mExternalSignal);
    panel3->layout()->addWidget(_mSignalFacingDirection);
    panel3->layout()->addWidget(jLabel18);
    panel3->layout()->addWidget(_mSignalAspectToDisplay);
    panel3->layout()->addWidget(jLabel3);
    panel3->layout()->addWidget(_mCalledOnExternalSensor);
    panel3->layout()->addWidget(jLabel16);
    panel3->layout()->addWidget(_mExternalBlock);
    contentPane->layout()->addWidget(panel3);

    contentPane->layout()->addWidget(jLabel9);

    JPanel* panel4 = new JPanel(new QHBoxLayout());
    panel4->layout()->addWidget(jLabel14);
    panel4->layout()->addWidget(_mCancel);
    contentPane->layout()->addWidget(panel4);

    JPanel* panel5 = new JPanel(new QHBoxLayout());
    panel5->layout()->addWidget(_mSwitchIndicator1);
    panel5->layout()->addWidget(_mSwitchIndicator2);
    panel5->layout()->addWidget(_mSwitchIndicator3);
    panel5->layout()->addWidget(_mSwitchIndicator4);
    panel5->layout()->addWidget(_mSwitchIndicator5);
    panel5->layout()->addWidget(_mSwitchIndicator6);
    panel5->layout()->addWidget(_mGroupingListAddReplace);
    contentPane->layout()->addWidget(panel5);

    JPanel* panel6 = new JPanel(new FlowLayout());
    panel6->layout()->addWidget(_mSaveAndClose);
    panel6->layout()->addWidget(jButton2);
    contentPane->layout()->addWidget(panel6);

#endif

        pack();
    }// </editor-fold>

    /*private*/ void FrmCO::_mSaveAndCloseActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        if (CommonSubs::missingFieldsErrorDialogDisplayed(this, formFieldsValid(), false)) {
            return; // Do not allow exit or transfer of data.
        }

        _mCodeButtonHandlerData->_mCO_CallOnToggleInternalSensor = CommonSubs::getNBHSensor( _mCO_CallOnToggleInternalSensor->getSelectedItem(), false);

        int size = _mDefaultListModel->size();
        _mCodeButtonHandlerData->_mCO_GroupingsList->clear();
        for (int index = 0; index < size; index++) {
            CallOnData* thisEntry = VPtr<CallOnData>::asPtr(_mDefaultListModel->getElementAt(index));
            _mCodeButtonHandlerData->_mCO_GroupingsList->append(thisEntry);
        }
        _mClosedNormally = true;
        _mAwtWindowProperties->saveWindowState(this, FORM_PROPERTIES);
        dispose();
    }

    /*private*/ void FrmCO::_mAddNewActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        _mAddNewPressed = true;
        enableTopPart(false);
        _mGroupingsList->setEnabled(false);
        _mGroupingsList->clearSelection();
        _mSignalFacingDirection->setCurrentIndex(0);
        _mSignalAspectToDisplay->setCurrentIndex(4);    // Flashing Red.
        _mGroupingListAddReplace->setText(tr("TextDlgCOAddInstructions"));    // NOI18N
        _mGroupingListAddReplace->setEnabled(true);
        _mSwitchIndicator1->setCurrentIndex(0);
        _mSwitchIndicator2->setCurrentIndex(0);
        _mSwitchIndicator3->setCurrentIndex(0);
        _mSwitchIndicator4->setCurrentIndex(0);
        _mSwitchIndicator5->setCurrentIndex(0);
        _mSwitchIndicator6->setCurrentIndex(0);
//        _mExternalSignal->requestFocusInWindow();
        if (_mSignalHeadSelected) {
            CommonSubs::populateJComboBoxWithBeans(_mExternalSignal, "SignalHead", QString(), false);
            CommonSubs::populateJComboBoxWithBeans(_mCalledOnExternalSensor, "Sensor", QString(), false);
            CommonSubs::populateJComboBoxWithBeans(_mExternalBlock, "Block", QString(), true);
        } else {
            CommonSubs::populateJComboBoxWithBeans(_mExternalSignal, "SignalMast", QString(), false);
            CommonSubs::populateJComboBoxWithBeans(_mCalledOnExternalSensor, "Sensor", QString(), true);
            CommonSubs::populateJComboBoxWithBeans(_mExternalBlock, "Block", QString(), false);
        }
    }

    /*private*/ void FrmCO::_mEditBelowActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        _mAddNewPressed = false;
        int selectedIndex = _mGroupingsList->currentIndex().row();
        enableTopPart(false);
        _mGroupingsList->setEnabled(false);
        CallOnData* callOnData = VPtr<CallOnData>::asPtr(_mDefaultListModel->get(selectedIndex));
        _mSignalFacingDirection->setSelectedItem(callOnData->_mSignalFacingDirection);
        _mSignalAspectToDisplay->setSelectedItem(callOnData->_mSignalAspectToDisplay);
        _mGroupingListAddReplace->setText(tr("TextDlgCOUpdateInstructions")); // NOI18N
        _mGroupingListAddReplace->setEnabled(true);

        for (int i = 0; i < callOnData->_mSwitchIndicators->size(); i++) {
            if (i == 0) _mSwitchIndicator1->setSelectedItem(callOnData->_mSwitchIndicators->at(i)->getHandleName());
            if (i == 1) _mSwitchIndicator2->setSelectedItem(callOnData->_mSwitchIndicators->at(i)->getHandleName());
            if (i == 2) _mSwitchIndicator3->setSelectedItem(callOnData->_mSwitchIndicators->at(i)->getHandleName());
            if (i == 3) _mSwitchIndicator4->setSelectedItem(callOnData->_mSwitchIndicators->at(i)->getHandleName());
            if (i == 4) _mSwitchIndicator5->setSelectedItem(callOnData->_mSwitchIndicators->at(i)->getHandleName());
            if (i == 5) _mSwitchIndicator6->setSelectedItem(callOnData->_mSwitchIndicators->at(i)->getHandleName());
        }

//        _mExternalSignal->requestFocusInWindow();
        if (_mSignalHeadSelected) {
            CommonSubs::populateJComboBoxWithBeans(_mExternalSignal, "SignalHead", callOnData->_mExternalSignal->getHandleName(), false);
            CommonSubs::populateJComboBoxWithBeans(_mCalledOnExternalSensor, "Sensor", callOnData->_mCalledOnExternalSensor->getHandleName(), false);
            CommonSubs::populateJComboBoxWithBeans(_mExternalBlock, "Block", QString(), true);
        } else {
            CommonSubs::populateJComboBoxWithBeans(_mExternalSignal, "SignalMast", callOnData->_mExternalSignal->getHandleName(), false);
            CommonSubs::populateJComboBoxWithBeans(_mCalledOnExternalSensor, "Sensor", QString(), true);
            CommonSubs::populateJComboBoxWithBeans(_mExternalBlock, "Block", callOnData->_mExternalBlock->getName(), false);
        }
    }

    /*private*/ void FrmCO::_mDeleteActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        _mDefaultListModel->remove(_mGroupingsList->currentIndex().row());
        enableTopPart(true);
    }

    /*private*/ void FrmCO::_mGroupingListAddReplaceActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        if (ProjectsCommonSubs::isNullOrEmptyString( _mExternalSignal->getSelectedItem())) {
            JOptionPane::showMessageDialog(this, tr("Signal MUST have a value"),
                    tr("Error"), JOptionPane::ERROR_MESSAGE); // NOI18N
            return;
        }
        if (_mSignalHeadSelected) {
            if (ProjectsCommonSubs::isNullOrEmptyString( _mCalledOnExternalSensor->getSelectedItem())) {
                JOptionPane::showMessageDialog(this, tr("Called on sensor MUST have a value"),
                        tr("Error"), JOptionPane::ERROR_MESSAGE); // NOI18N
                return;
            }
        } else {
            if (ProjectsCommonSubs::isNullOrEmptyString( _mExternalBlock->getSelectedItem())) {
                JOptionPane::showMessageDialog(this, tr("Block MUST have a value"),
                        tr("Error"), JOptionPane::ERROR_MESSAGE); // NOI18N
                return;
            }
        }

        CallOnData* newCallOnData = new CallOnData();

        newCallOnData->_mExternalSignal = CommonSubs::getNBHSignal( _mExternalSignal->getSelectedItem());
        newCallOnData->_mSignalFacingDirection = (_mSignalFacingDirection->getSelectedItem() == QString() ? QString() : _mSignalFacingDirection->getSelectedItem()/*.toString()*/);
        newCallOnData->_mSignalAspectToDisplay = (_mSignalAspectToDisplay->getSelectedItem() == QString() ? QString() : _mSignalAspectToDisplay->getSelectedItem()/*.toString()*/);
        newCallOnData->_mCalledOnExternalSensor = CommonSubs::getNBHSensor( _mCalledOnExternalSensor->getSelectedItem(), false);
        if (newCallOnData->_mCalledOnExternalSensor != nullptr && !newCallOnData->_mCalledOnExternalSensor->valid()) newCallOnData->_mCalledOnExternalSensor = nullptr;

        NamedBeanHandle<Block*>* blockHandle = nullptr;
        QString blockName =  _mExternalBlock->getSelectedItem();
        Block* block = ((BlockManager*)InstanceManager::getDefault("BlockManager"))->getBlock(blockName);
        if (block != nullptr) {
            blockHandle = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(blockName, block);

            // Check for permissive setting
            if (!block->getPermissiveWorking()) {
                int response = JOptionPane::showConfirmDialog(this,
                        tr("The block table entry does not have Permissive enabled.\nSelect \"Yes\" to have it enabled for you."),
                        tr("Warning"),
                        JOptionPane::YES_NO_OPTION);
                if (response == 0) {
                    block->setPermissiveWorking(true);
                }
            }
        }
        newCallOnData->_mExternalBlock = blockHandle;

        QList<NBHSensor*>* indcators = new QList<NBHSensor*>();
        CommonSubs::addSensorToSensorList(indcators, _mSwitchIndicator1->getSelectedItem());
        CommonSubs::addSensorToSensorList(indcators, _mSwitchIndicator2->getSelectedItem());
        CommonSubs::addSensorToSensorList(indcators, _mSwitchIndicator3->getSelectedItem());
        CommonSubs::addSensorToSensorList(indcators, _mSwitchIndicator4->getSelectedItem());
        CommonSubs::addSensorToSensorList(indcators, _mSwitchIndicator5->getSelectedItem());
        CommonSubs::addSensorToSensorList(indcators, _mSwitchIndicator6->getSelectedItem());
        newCallOnData->_mSwitchIndicators = indcators;

        CheckJMRIObject::VerifyClassReturnValue* verifyClassReturnValue = _mCheckJMRIObject->verifyClass(VPtr<CallOnData>::asQVariant(newCallOnData));
        if (verifyClassReturnValue != nullptr) { // Error:
            JOptionPane::showMessageDialog(this, verifyClassReturnValue->toString(),
                    tr("Error"), JOptionPane::ERROR_MESSAGE);    // NOI18N
            return;
        }

        _mGroupingListAddReplace->setEnabled(false);
        enableTopPart(true);
        if (_mAddNewPressed) {
            _mDefaultListModel->addElement(VPtr<CallOnData>::asQVariant(newCallOnData));
        }
        else {
            _mDefaultListModel->set(_mGroupingsList->currentIndex().row(), VPtr<CallOnData>::asQVariant(newCallOnData));
        }
        _mGroupingsList->setEnabled(true);
    }

    /*private*/ void FrmCO::formWindowClosing(QCloseEvent* evt) {
        _mAwtWindowProperties->saveWindowState(this, FORM_PROPERTIES);
        if (CommonSubs::allowClose(this, dataChanged())) dispose();
    }

    /*private*/ void FrmCO::jButton2ActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        CodeButtonHandlerData* temp = _mCodeButtonHandlerData;
        temp = CodeButtonHandlerDataRoutines::uECBHDWSD_CallOn(_mProgramProperties, temp);
        CommonSubs::populateJComboBoxWithBeans(_mCO_CallOnToggleInternalSensor, "Sensor", temp->_mCO_CallOnToggleInternalSensor->getHandleName(), false);   // NOI18N
    }

    /*private*/ void FrmCO::_mGroupingsListValueChanged(ListSelectionEvent* evt) {
        if (_mGroupingsList->isSelectionEmpty()) {
            _mEditBelow->setEnabled(false);
            _mDelete->setEnabled(false);
        } else {
            _mEditBelow->setEnabled(true);
            _mDelete->setEnabled(true);
        }
    }

    /*private*/ void FrmCO::_mCancelActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        enableTopPart(true);
        _mGroupingsList->setEnabled(true);
    }

    /*private*/ void FrmCO::_mSwitchIndicator1ActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        // TODO add your handling code here:
    }

    /*private*/ void FrmCO::enableTopPart(bool enabled) {
        _mAddNew->setEnabled(enabled);
        _mSwitchIndicator1->setEnabled(!enabled);
        _mSwitchIndicator2->setEnabled(!enabled);
        _mSwitchIndicator3->setEnabled(!enabled);
        _mSwitchIndicator4->setEnabled(!enabled);
        _mSwitchIndicator5->setEnabled(!enabled);
        _mSwitchIndicator6->setEnabled(!enabled);

        _mExternalSignal->setEnabled(!enabled);
        _mSignalFacingDirection->setEnabled(!enabled);
        _mSignalAspectToDisplay->setEnabled(!enabled && _mSignalHeadSelected);
        _mCalledOnExternalSensor->setEnabled(!enabled && _mSignalHeadSelected);
        _mExternalBlock->setEnabled(!enabled && !_mSignalHeadSelected);

        _mGroupingListAddReplace->setEnabled(!enabled);
        _mCancel->setEnabled(!enabled);
        _mSaveAndClose->setEnabled(enabled);

        if (enabled) _mSaveAndClose->setDefault(true);//this.getRootPane()->setDefaultButton(_mSaveAndClose);
        else _mGroupingListAddReplace->setDefault(true);//this.getRootPane()->setDefaultButton(_mGroupingListAddReplace);
    }


//     /*private*/ static /*final*/ org.slf4j.Logger log = org.slf4j.LoggerFactory.getLogger(FrmCO.class);
