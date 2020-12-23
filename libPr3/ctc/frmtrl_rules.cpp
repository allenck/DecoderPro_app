#include "frmtrl_rules.h"
#include "codebuttonhandlerdata.h"
#include "awtwindowproperties.h"
#include "checkjmriobject.h"
#include "commonsubs.h"
#include "jcombobox.h"
#include "jlist.h"
#include "defaultlistmodel.h"
#include "jlabel.h"
#include "vptr.h"
#include "defaultcomboboxmodel.h"
#include "ctcserialdata.h"
#include "checkjmriobject.h"
#include "joptionpane.h"
#include "jpanel.h"
#include <QBoxLayout>


/**
 * Maintain the set of traffic locking rules.  There is an east set and a west set
 * in CodeButtonHandlerData.
 * <p>
 * When the form is invoked, trafficLockingRules points to either the east set or the west set.
 * The contents of the set is then loaded into _mTrafficLockingModel for display by JList.
 * When changes are made, the related entries in the model are updated.
 * <p>
 * When the save and close button is pressed, the model contents replace the contents of
 * the related traffic locking rules ArrayList in the current CodeButtonHandlerData object.
 *
 * @author Gregory J. Bedlek Copyright (C) 2018, 2019
 */
///*public*/ class FrmTRL_Rules extends JFrame {
/*private*/ /*static*/ /*final*/ QString FrmTRL_Rules::FORM_PROPERTIES;// = "DlgTRL_Rules";   // NOI18N

    /**
     * Creates new form DlgTRL_Rules
     */

    /*private*/ void FrmTRL_Rules::initOrig() {
        for (int index = 0; index < _mTrafficLockingModel->size(); index++) {
            _mTrafficLockingRulesOrig->append(VPtr<TrafficLockingData>::asPtr(_mTrafficLockingModel->get(index)));
        }
    }

    /*private*/ bool FrmTRL_Rules::dataChanged() {
        int ruleListSize = _mTrafficLockingModel->size();
        if (ruleListSize != _mTrafficLockingRulesOrig->size()) return true;
        for (int index = 0; index < ruleListSize; index++) {
            if (VPtr<TrafficLockingData>::asPtr( _mTrafficLockingModel->get(index)) != (_mTrafficLockingRulesOrig->at(index))) return true;
        }
        return false;
    }

    /*public*/ FrmTRL_Rules::FrmTRL_Rules(AwtWindowProperties* awtWindowProperties, CodeButtonHandlerData* codeButtonHandlerData,
                        bool isLeftTraffic,
                        CTCSerialData* ctcSerialData, CheckJMRIObject* checkJMRIObject, QWidget *parent) : JFrame(parent) {
        //super();
        initComponents();
        CommonSubs::addHelpMenu(this, "package.jmri.jmrit.ctc.CTC_frmTRL", true);  // NOI18N
        _mAwtWindowProperties = awtWindowProperties;
        _mCodeButtonHandlerData = codeButtonHandlerData;
        _mIsLeftTraffic = isLeftTraffic;
        _mCTCSerialData = ctcSerialData;
        _mCheckJMRIObject = checkJMRIObject;
        _mArrayListOfSelectableOSSectionUniqueIDs = CommonSubs::getArrayListOfSelectableOSSectionUniqueIDs(_mCTCSerialData->getCodeButtonHandlerDataArrayList());
        QString identifier = codeButtonHandlerData->myShortStringNoComma();

        QList<TrafficLockingData*>* trafficLockingRules;
        if (isLeftTraffic) {
            this->setTitle(tr("Edit Left traffic locking rules for") + " " + identifier);    // NOI18N
            _mRulesInfo->setText(tr("If ANY of these rules are true, then the Left Traffic Direction Lever is allowed to be coded."));             // NOI18N
            trafficLockingRules = _mCodeButtonHandlerData->_mTRL_LeftTrafficLockingRules;
        } else {
            this->setTitle(tr("Edit Right traffic locking rules for") + " " + identifier);   // NOI18N
            _mRulesInfo->setText(tr("If ANY of these rules are true, then the Right Traffic Direction Lever is allowed to be coded."));            // NOI18N
            trafficLockingRules = _mCodeButtonHandlerData->_mTRL_RightTrafficLockingRules;
        }
        _mTrafficLockingModel = new DefaultListModel();
        _mTRL_TrafficLockingRules->setModel(_mTrafficLockingModel);
        //trafficLockingRules.forEach(rule ->
        foreach(TrafficLockingData*rule, *trafficLockingRules)
        {
            _mTrafficLockingModel->addElement(VPtr<TrafficLockingData>::asQVariant( rule));
        }//);
        int ruleNumber = 1;
        for (int index = 0; index < _mTrafficLockingModel->size(); index++) {
            _mTrafficLockingModel->set(index, VPtr<TrafficLockingData>::asQVariant(renumberRule(VPtr<TrafficLockingData>::asPtr(_mTrafficLockingModel->get(index)), ruleNumber++)));
        }
        initOrig();
        _mAwtWindowProperties->setWindowState(this, FORM_PROPERTIES);
        CommonSubs::populateJComboBoxWithBeans(_mOccupancyExternalSensor1, "Sensor", "", true);
        CommonSubs::populateJComboBoxWithBeans(_mOccupancyExternalSensor2, "Sensor", "", true);
        CommonSubs::populateJComboBoxWithBeans(_mOccupancyExternalSensor3, "Sensor", "", true);
        CommonSubs::populateJComboBoxWithBeans(_mOccupancyExternalSensor4, "Sensor", "", true);
        CommonSubs::populateJComboBoxWithBeans(_mOccupancyExternalSensor5, "Sensor", "", true);
        CommonSubs::populateJComboBoxWithBeans(_mOccupancyExternalSensor6, "Sensor", "", true);
        CommonSubs::populateJComboBoxWithBeans(_mOccupancyExternalSensor7, "Sensor", "", true);
        CommonSubs::populateJComboBoxWithBeans(_mOccupancyExternalSensor8, "Sensor", "", true);
        CommonSubs::populateJComboBoxWithBeans(_mOccupancyExternalSensor9, "Sensor", "", true);
        CommonSubs::populateJComboBoxWithBeans(_mOptionalExternalSensor1, "Sensor", "", true);
        CommonSubs::populateJComboBoxWithBeans(_mOptionalExternalSensor2, "Sensor", "", true);
        CommonSubs::populateJComboBoxWithColumnDescriptions(_mOS_NumberEntry1, _mCTCSerialData);
        CommonSubs::populateJComboBoxWithColumnDescriptions(_mOS_NumberEntry2, _mCTCSerialData);
        CommonSubs::populateJComboBoxWithColumnDescriptions(_mOS_NumberEntry3, _mCTCSerialData);
        CommonSubs::populateJComboBoxWithColumnDescriptions(_mOS_NumberEntry4, _mCTCSerialData);
        CommonSubs::populateJComboBoxWithColumnDescriptions(_mOS_NumberEntry5, _mCTCSerialData);
        QVector<QString> normalAndReverse = QVector<QString> { tr("Normal"), tr("Reverse") }; // NOI18N
        //_mSwitchAlignment1->setModel(new DefaultComboBoxModel/*<>*/(normalAndReverse));
        _mSwitchAlignment1->addItems(normalAndReverse.toList());
//        _mSwitchAlignment2->setModel(new DefaultComboBoxModel/*<>*/(normalAndReverse));
        _mSwitchAlignment2->addItems(normalAndReverse.toList());
//        _mSwitchAlignment3->setModel(new DefaultComboBoxModel/*<>*/(normalAndReverse));
        _mSwitchAlignment3->addItems(normalAndReverse.toList());
//        _mSwitchAlignment4->setModel(new DefaultComboBoxModel/*<>*/(normalAndReverse));
        _mSwitchAlignment4->addItems(normalAndReverse.toList());
//        _mSwitchAlignment5->setModel(new DefaultComboBoxModel/*<>*/(normalAndReverse));
        _mSwitchAlignment5->addItems(normalAndReverse.toList());
        enableTopPart(true);
        _mEditBelow->setEnabled(false);
        _mDelete->setEnabled(false);
        _mDupToEnd->setEnabled(false);
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    // <editor-fold defaultstate="collapsed" desc="Generated Code">
    /*private*/ void FrmTRL_Rules::initComponents() {

        _mSaveAndClose = new JButton();
        jLabel2 = new JLabel();
        jScrollPane1 = new QScrollArea();
        _mTRL_TrafficLockingRules = new JList/*<>*/();
        _mAddNew = new JButton();
        _mEditBelow = new JButton();
        _mDelete = new JButton();
        _mGroupingListAddReplace = new JButton();
        jLabel1 = new JLabel();
        jLabel8 = new JLabel();
        jLabel7 = new JLabel();
        _mRulesInfo = new JLabel();
        _mCancel = new JButton();
        jLabel4 = new JLabel();
        jLabel10 = new JLabel();
        _mRuleEnabled = new JCheckBox();
        _mEnableALLRules = new JButton();
        _mDisableALLRules = new JButton();
        _mOS_NumberEntry1 = new JComboBox/*<>*/();
        _mOS_NumberEntry2 = new JComboBox/*<>*/();
        _mOS_NumberEntry3 = new JComboBox/*<>*/();
        _mOS_NumberEntry4 = new JComboBox/*<>*/();
        _mOS_NumberEntry5 = new JComboBox/*<>*/();
        _mSwitchAlignment1 = new JComboBox/*<>*/();
        _mSwitchAlignment2 = new JComboBox/*<>*/();
        _mSwitchAlignment3 = new JComboBox/*<>*/();
        _mSwitchAlignment4 = new JComboBox/*<>*/();
        _mSwitchAlignment5 = new JComboBox/*<>*/();
        jLabel5 = new JLabel();
        _mOccupancyExternalSensor1 = new JComboBox/*<>*/();
        _mOccupancyExternalSensor2 = new JComboBox/*<>*/();
        _mOccupancyExternalSensor3 = new JComboBox/*<>*/();
        _mOccupancyExternalSensor4 = new JComboBox/*<>*/();
        _mOccupancyExternalSensor5 = new JComboBox/*<>*/();
        _mOccupancyExternalSensor6 = new JComboBox/*<>*/();
        _mOccupancyExternalSensor7 = new JComboBox/*<>*/();
        _mOccupancyExternalSensor8 = new JComboBox/*<>*/();
        _mOccupancyExternalSensor9 = new JComboBox/*<>*/();
        _mOptionalExternalSensor1 = new JComboBox/*<>*/();
        _mOptionalExternalSensor2 = new JComboBox/*<>*/();
        _mDupToEnd = new JButton();
        _mDestinationSignalOrCommentPrompt = new JLabel();
        _mDestinationSignalOrComment = new JTextField();

        setDefaultCloseOperation(JFrame::DO_NOTHING_ON_CLOSE);
        setTitle(tr("[code]"));
//        addWindowListener(new java.awt.event.WindowAdapter() {
//            @Override
//            /*public*/ void windowClosing(java.awt.event.WindowEvent evt) {
//                formWindowClosing(evt);
//            }
//        });
        addWindowListener(new FTR_WindowListener(this));

        _mSaveAndClose->setText(tr("Save and close"));
//        _mSaveAndClose.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent evt) {
        connect(_mSaveAndClose, &JButton::clicked, [=] {
                _mSaveAndCloseActionPerformed(/*evt*/);
//            }
        });

        jLabel2->setText(tr("Rules:"));

//        _mTRL_TrafficLockingRules.addListSelectionListener(new event.ListSelectionListener() {
//            @Override
//            /*public*/ void valueChanged(event.ListSelectionEvent evt) {
//                _mTRL_TrafficLockingRulesValueChanged(evt);
//            }
//        });
        _mTRL_TrafficLockingRules->addListSelectionListener(new FTR_ListSelectionListener(this));

//        jScrollPane1->setViewportView(_mTRL_TrafficLockingRules);

        _mAddNew->setText(tr("Add New"));
//        _mAddNew.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent evt) {
        connect(_mAddNew, &JButton::clicked, [=]{
                _mAddNewActionPerformed(/*evt*/);
//            }
        });

        _mEditBelow->setText(tr("Edit Below"));
//        _mEditBelow.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent evt) {
        connect(_mEditBelow, &JButton::clicked, [=]{
                _mEditBelowActionPerformed(/*evt*/);
//            }
        });

        _mDelete->setText(tr("Delete"));
//        _mDelete.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent evt) {
        connect(_mDelete, &JButton::clicked, [=]{
                _mDeleteActionPerformed(/*evt*/);
//            }
        });

        _mGroupingListAddReplace->setText(tr("[code]"));
        _mGroupingListAddReplace->setEnabled(false);
//        _mGroupingListAddReplace.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent evt) {
        connect(_mGroupingListAddReplace, &JButton::clicked, [=]{
                _mGroupingListAddReplaceActionPerformed(/*evt*/);
//            }
        });

        jLabel1->setText(tr("---------------------------------------- ROUTE ----------------------------------------"));

        jLabel8->setText(tr("Select up to 5 O.S. section(s) to specify the route exactly.  Below each are switch alignments (for those specified):"));

        jLabel7->setText(tr("--------- Optional sensors that must be ACTIVE to be valid ---------"));

        _mRulesInfo->setText(tr("If ANY of these rules are true, then the ? Traffic Direction Lever is allowed to be \"coded\"."));

        _mCancel->setText(tr("Cancel"));
//        _mCancel.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent evt) {
        connect(_mCancel, &JButton::clicked, [=]{
                _mCancelActionPerformed(/*evt*/);
//            }
        });

        jLabel4->setText(tr("Having NO rules (or no rules enabled) ALWAYS allows"));

        jLabel10->setText(tr("this direction.  For example: Where you go into staging and there is no O.S. section set controlling entry/exit from the staging area."));

        _mRuleEnabled->setText(tr("This rule ENABLED"));

        _mEnableALLRules->setText(tr("Enable ALL rules"));
//        _mEnableALLRules.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent evt) {
        connect(_mEnableALLRules, &JButton::clicked, [=]{
                _mEnableALLRulesActionPerformed(/*evt*/);
//            }
        });

        _mDisableALLRules->setText(tr("Disable ALL rules"));
//        _mDisableALLRules.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent evt) {
        connect(_mDisableALLRules, &JButton::clicked, [=]{
                _mDisableALLRulesActionPerformed(/*evt*/);
//            }
        });

        jLabel5->setText(tr("Occupancy sensors not reserved by other routes for the route specified to be allowed."));

        _mDupToEnd->setText(tr("Dup (to end)"));
//        _mDupToEnd.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent evt) {
        connect(_mDupToEnd, &JButton::clicked, [=]{
                _mDupToEndActionPerformed(/*evt*/);
//            }
        });

        _mDestinationSignalOrCommentPrompt->setText(tr("Dest Signal / Comment:")
        );
#if 0
        GroupLayout layout = new GroupLayout(getContentPane());
        getContentPane()->setLayout(layout);
        layout->setHorizontalGroup(
            layout.createParallelGroup(GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jLabel2)
                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addGap(3, 3, 3)
                        .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING, false)
                            .addComponent(jLabel8)
                            .addComponent(jLabel7)
                            .addComponent(jLabel1)
                            .addComponent(jLabel5)
                            .addGroup(layout.createSequentialGroup()
                                .addComponent(_mSwitchAlignment1, GroupLayout.PREFERRED_SIZE, 126, GroupLayout.PREFERRED_SIZE)
                                .addGap(18, 18, 18)
                                .addComponent(_mSwitchAlignment2, GroupLayout.PREFERRED_SIZE, 126, GroupLayout.PREFERRED_SIZE)
                                .addGap(18, 18, 18)
                                .addComponent(_mSwitchAlignment3, GroupLayout.PREFERRED_SIZE, 126, GroupLayout.PREFERRED_SIZE)
                                .addGap(18, 18, 18)
                                .addComponent(_mSwitchAlignment4, GroupLayout.PREFERRED_SIZE, 126, GroupLayout.PREFERRED_SIZE)
                                .addGap(18, 18, 18)
                                .addComponent(_mSwitchAlignment5, GroupLayout.PREFERRED_SIZE, 126, GroupLayout.PREFERRED_SIZE))
                            .addGroup(layout.createSequentialGroup()
                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING, false)
                                    .addComponent(_mOccupancyExternalSensor1, 0, 280, Short.MAX_VALUE)
                                    .addComponent(_mOccupancyExternalSensor4, 0, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                    .addComponent(_mOccupancyExternalSensor7, 0, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                                .addGap(18, 18, 18)
                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING, false)
                                    .addComponent(_mOccupancyExternalSensor2, 0, 280, Short.MAX_VALUE)
                                    .addComponent(_mOccupancyExternalSensor5, 0, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                    .addComponent(_mOccupancyExternalSensor8, 0, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                                .addGap(18, 18, 18)
                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING, false)
                                    .addComponent(_mOccupancyExternalSensor3, 0, 280, Short.MAX_VALUE)
                                    .addComponent(_mOccupancyExternalSensor6, 0, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                    .addComponent(_mOccupancyExternalSensor9, 0, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)))
                            .addGroup(layout.createSequentialGroup()
                                .addComponent(_mOptionalExternalSensor1, GroupLayout.PREFERRED_SIZE, 224, GroupLayout.PREFERRED_SIZE)
                                .addGap(18, 18, 18)
                                .addComponent(_mOptionalExternalSensor2, GroupLayout.PREFERRED_SIZE, 219, GroupLayout.PREFERRED_SIZE)
                                .addGap(36, 36, 36)
                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                                    .addComponent(_mSaveAndClose)
                                    .addGroup(layout.createSequentialGroup()
                                        .addComponent(_mGroupingListAddReplace, GroupLayout.PREFERRED_SIZE, 312, GroupLayout.PREFERRED_SIZE)
                                        .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                                        .addComponent(_mCancel))))
                            .addGroup(layout.createSequentialGroup()
                                .addComponent(_mOS_NumberEntry1, GroupLayout.PREFERRED_SIZE, 126, GroupLayout.PREFERRED_SIZE)
                                .addGap(18, 18, 18)
                                .addComponent(_mOS_NumberEntry2, GroupLayout.PREFERRED_SIZE, 126, GroupLayout.PREFERRED_SIZE)
                                .addGap(18, 18, 18)
                                .addComponent(_mOS_NumberEntry3, GroupLayout.PREFERRED_SIZE, 126, GroupLayout.PREFERRED_SIZE)
                                .addGap(18, 18, 18)
                                .addComponent(_mOS_NumberEntry4, GroupLayout.PREFERRED_SIZE, 126, GroupLayout.PREFERRED_SIZE)
                                .addGap(18, 18, 18)
                                .addComponent(_mOS_NumberEntry5, GroupLayout.PREFERRED_SIZE, 126, GroupLayout.PREFERRED_SIZE))))
                    .addComponent(jLabel10)
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                            .addComponent(jScrollPane1, GroupLayout.PREFERRED_SIZE, 786, GroupLayout.PREFERRED_SIZE)
                            .addGroup(layout.createSequentialGroup()
                                .addComponent(_mRuleEnabled)
                                .addGap(18, 18, 18)
                                .addComponent(_mEnableALLRules, GroupLayout.PREFERRED_SIZE, 133, GroupLayout.PREFERRED_SIZE)
                                .addGap(18, 18, 18)
                                .addComponent(_mDisableALLRules, GroupLayout.PREFERRED_SIZE, 143, GroupLayout.PREFERRED_SIZE)
                                .addGap(18, 18, 18)
                                .addComponent(_mDestinationSignalOrCommentPrompt)
                                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(_mDestinationSignalOrComment, GroupLayout.PREFERRED_SIZE, 113, GroupLayout.PREFERRED_SIZE))
                            .addGroup(layout.createSequentialGroup()
                                .addComponent(_mRulesInfo)
                                .addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED)
                                .addComponent(jLabel4)))
                        .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING, false)
                            .addComponent(_mEditBelow, GroupLayout.DEFAULT_SIZE, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addComponent(_mAddNew, GroupLayout.DEFAULT_SIZE, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addComponent(_mDelete, GroupLayout.DEFAULT_SIZE, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addComponent(_mDupToEnd))))
                .addContainerGap(GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
        layout->setVerticalGroup(
            layout.createParallelGroup(GroupLayout.Alignment.LEADING)
            .addGroup(GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addGap(18, 18, 18)
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                    .addComponent(jLabel2)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(_mAddNew)
                        .addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED)
                        .addComponent(_mEditBelow)
                        .addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED)
                        .addComponent(_mDelete)
                        .addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED)
                        .addComponent(_mDupToEnd))
                    .addComponent(jScrollPane1, GroupLayout.PREFERRED_SIZE, 139, GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                    .addComponent(_mRulesInfo)
                    .addComponent(jLabel4))
                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jLabel10)
                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                    .addComponent(_mRuleEnabled)
                    .addComponent(_mEnableALLRules)
                    .addComponent(_mDisableALLRules)
                    .addComponent(_mDestinationSignalOrCommentPrompt)
                    .addComponent(_mDestinationSignalOrComment, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
                .addGap(18, 18, Short.MAX_VALUE)
                .addComponent(jLabel1)
                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jLabel8)
                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                    .addComponent(_mOS_NumberEntry1, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                    .addComponent(_mOS_NumberEntry2, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                    .addComponent(_mOS_NumberEntry3, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                    .addComponent(_mOS_NumberEntry4, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                    .addComponent(_mOS_NumberEntry5, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                    .addComponent(_mSwitchAlignment1, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                    .addComponent(_mSwitchAlignment2, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                    .addComponent(_mSwitchAlignment3, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                    .addComponent(_mSwitchAlignment4, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                    .addComponent(_mSwitchAlignment5, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
                .addGap(18, 18, Short.MAX_VALUE)
                .addComponent(jLabel5)
                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                    .addComponent(_mOccupancyExternalSensor1, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                    .addComponent(_mOccupancyExternalSensor2, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                    .addComponent(_mOccupancyExternalSensor3, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                    .addComponent(_mOccupancyExternalSensor4, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                    .addComponent(_mOccupancyExternalSensor5, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                    .addComponent(_mOccupancyExternalSensor6, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                    .addComponent(_mOccupancyExternalSensor7, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                    .addComponent(_mOccupancyExternalSensor8, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                    .addComponent(_mOccupancyExternalSensor9, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
                .addGap(18, 18, 18)
                .addComponent(jLabel7)
                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                    .addComponent(_mGroupingListAddReplace)
                    .addComponent(_mCancel)
                    .addComponent(_mOptionalExternalSensor1, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                    .addComponent(_mOptionalExternalSensor2, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(_mSaveAndClose)
                .addGap(13, 13, 13))
        );
#else
        QVBoxLayout* contentPaneLayout;
        if(getContentPane()->layout() == nullptr)
         getContentPane()->setLayout(contentPaneLayout = new QVBoxLayout());
        JPanel* panel1 = new JPanel();
        panel1->setLayout(new QHBoxLayout());
        panel1->layout()->addWidget(jLabel2);
        contentPaneLayout->addWidget(panel1);
        JPanel* panel2 = new JPanel();
        panel2->setLayout(new QVBoxLayout);
        JPanel* panel2a = new JPanel();
        panel2a->setLayout(new QHBoxLayout());
        panel2a->layout()->addWidget(jLabel8);
        panel2a->layout()->addWidget(_mSwitchAlignment1);
        panel2a->layout()->addWidget(_mSwitchAlignment2);
        panel2a->layout()->addWidget(_mSwitchAlignment3);
        panel2a->layout()->addWidget(_mSwitchAlignment4);
        panel2a->layout()->addWidget(_mSwitchAlignment5);
        panel2->layout()->addWidget(panel2a);
        JPanel* panel2b = new JPanel();
        panel2b->setLayout(new QHBoxLayout());
        panel2b->layout()->addWidget(jLabel7);
        panel2b->layout()->addWidget(_mOccupancyExternalSensor1);
        panel2b->layout()->addWidget(_mOccupancyExternalSensor4);
        panel2b->layout()->addWidget(_mOccupancyExternalSensor7);
        panel2->layout()->addWidget(panel2b);
        JPanel* panel2c = new JPanel();
        panel2c->setLayout(new QHBoxLayout());
        panel2c->layout()->addWidget(jLabel1);
        panel2b->layout()->addWidget(_mOccupancyExternalSensor2);
        panel2b->layout()->addWidget(_mOccupancyExternalSensor5);
        panel2b->layout()->addWidget(_mOccupancyExternalSensor8);
        panel2->layout()->addWidget(panel2c);
        JPanel* panel2d = new JPanel();
        panel2d->setLayout(new QHBoxLayout());
        panel2d->layout()->addWidget(jLabel5);
        panel2b->layout()->addWidget(_mOccupancyExternalSensor3);
        panel2b->layout()->addWidget(_mOccupancyExternalSensor6);
        panel2b->layout()->addWidget(_mOccupancyExternalSensor9);
        panel2->layout()->addWidget(panel2d);
        contentPaneLayout->addWidget(panel2);
        JPanel* panel3 = new JPanel();
        panel3->layout()->addWidget(_mOptionalExternalSensor1);
        panel3->layout()->addWidget(_mOptionalExternalSensor2);
        JPanel* panel3a = new JPanel();
        panel3a->layout()->addWidget(_mSaveAndClose);
        JPanel* panel3a1 = new JPanel();
        panel3a1->layout()->addWidget(_mGroupingListAddReplace);
        panel3a1->layout()->addWidget(_mCancel);
        panel3a->layout()->addWidget(panel3a);
        panel3->layout()->addWidget(panel3a);
        JPanel* panel3b = new JPanel();
        panel3b->layout()->addWidget(_mOS_NumberEntry1);
        panel3b->layout()->addWidget(_mOS_NumberEntry2);
        panel3b->layout()->addWidget(_mOS_NumberEntry3);
        panel3b->layout()->addWidget(_mOS_NumberEntry4);
        panel3b->layout()->addWidget(_mOS_NumberEntry5);
        panel3->layout()->addWidget(panel3b);
        contentPaneLayout->addWidget(panel3);
        contentPaneLayout->addWidget(jLabel10);
        JPanel* panel4 = new JPanel();
        panel4->setLayout(new QVBoxLayout());
        QScrollArea* scrollArea = new QScrollArea();
        JPanel* panel5 = new JPanel();
        panel5->setLayout(new QHBoxLayout());
        JPanel* panel5a = new JPanel();
        panel5a->layout()->addWidget(_mRuleEnabled);
        panel5a->layout()->addWidget(_mEnableALLRules);
        panel5a->layout()->addWidget(_mDisableALLRules);
        panel5a->layout()->addWidget(_mDestinationSignalOrCommentPrompt);
        panel5a->layout()->addWidget(_mDestinationSignalOrComment);
        panel5->layout()->addWidget(panel5a);
        JPanel* panel5b = new JPanel();
        panel5b->layout()->addWidget(_mRulesInfo);
        panel5b->layout()->addWidget(jLabel4);
        panel5->layout()->addWidget(panel5b);
        scrollArea->setWidget(panel5);
        panel4->layout()->addWidget(scrollArea);
        contentPaneLayout->addWidget(panel4);
        JPanel* panel6 = new JPanel();
        panel6->layout()->addWidget(_mEditBelow);
        panel6->layout()->addWidget(_mAddNew);
        panel6->layout()->addWidget(_mDelete);
        panel6->layout()->addWidget(_mDupToEnd);
#endif
        pack();
    }// </editor-fold>

    /*private*/ void FrmTRL_Rules::_mSaveAndCloseActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        QList<TrafficLockingData*>* trafficLockingRules;
        if (_mIsLeftTraffic) {
            trafficLockingRules = _mCodeButtonHandlerData->_mTRL_LeftTrafficLockingRules;
        } else {
            trafficLockingRules = _mCodeButtonHandlerData->_mTRL_RightTrafficLockingRules;
        }

        int size = _mTrafficLockingModel->getSize();
        trafficLockingRules->clear();
        for (int index = 0; index < size; index++) {
            trafficLockingRules->append(VPtr<TrafficLockingData>::asPtr( _mTrafficLockingModel->getElementAt(index)));
        }
        _mClosedNormally = true;
        _mAwtWindowProperties->saveWindowState(this, FORM_PROPERTIES);
        dispose();
    }

    /*private*/ void FrmTRL_Rules::formWindowClosing(/*java.awt.event.WindowEvent evt*/) {
        _mAwtWindowProperties->saveWindowState(this, FORM_PROPERTIES);
        if (CommonSubs::allowClose(this, dataChanged())) dispose();
    }

    /*private*/ void FrmTRL_Rules::_mTRL_TrafficLockingRulesValueChanged(ListSelectionEvent* evt) {
        if (_mTRL_TrafficLockingRules->isSelectionEmpty()) {
            _mEditBelow->setEnabled(false);
            _mDelete->setEnabled(false);
            _mDupToEnd->setEnabled(false);
        } else {
            _mEditBelow->setEnabled(true);
            _mDelete->setEnabled(true);
            _mDupToEnd->setEnabled(true);
        }
    }

    /*private*/ void FrmTRL_Rules::_mAddNewActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        _mAddNewPressed = true;
        enableTopPart(false);
        _mTRL_TrafficLockingRules->setEnabled(false);
        _mTRL_TrafficLockingRules->clearSelection();
        CommonSubs::populateJComboBoxWithBeans(_mOccupancyExternalSensor1, "Sensor", "", true);
        CommonSubs::populateJComboBoxWithBeans(_mOccupancyExternalSensor2, "Sensor", "", true);
        CommonSubs::populateJComboBoxWithBeans(_mOccupancyExternalSensor3, "Sensor", "", true);
        CommonSubs::populateJComboBoxWithBeans(_mOccupancyExternalSensor4, "Sensor", "", true);
        CommonSubs::populateJComboBoxWithBeans(_mOccupancyExternalSensor5, "Sensor", "", true);
        CommonSubs::populateJComboBoxWithBeans(_mOccupancyExternalSensor6, "Sensor", "", true);
        CommonSubs::populateJComboBoxWithBeans(_mOccupancyExternalSensor7, "Sensor", "", true);
        CommonSubs::populateJComboBoxWithBeans(_mOccupancyExternalSensor8, "Sensor", "", true);
        CommonSubs::populateJComboBoxWithBeans(_mOccupancyExternalSensor9, "Sensor", "", true);
        CommonSubs::populateJComboBoxWithBeans(_mOptionalExternalSensor1, "Sensor", "", true);
        CommonSubs::populateJComboBoxWithBeans(_mOptionalExternalSensor2, "Sensor", "", true);
        _mOS_NumberEntry1->setCurrentIndex(0);
        _mOS_NumberEntry2->setCurrentIndex(0);
        _mOS_NumberEntry3->setCurrentIndex(0);
        _mOS_NumberEntry4->setCurrentIndex(0);
        _mOS_NumberEntry5->setCurrentIndex(0);
        _mSwitchAlignment1->setCurrentIndex(0);
        _mSwitchAlignment2->setCurrentIndex(0);
        _mSwitchAlignment3->setCurrentIndex(0);
        _mSwitchAlignment4->setCurrentIndex(0);
        _mSwitchAlignment5->setCurrentIndex(0);
        _mGroupingListAddReplace->setText(tr("Add this to the end of Rules list above"));  // NOI18N
        _mGroupingListAddReplace->setEnabled(true);
        _mRuleEnabled->setChecked(true);
        _mDestinationSignalOrComment->setText("");
//        _mOS_NumberEntry1->requestFocusInWindow();
    }

    /*private*/ void FrmTRL_Rules::_mEditBelowActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        _mAddNewPressed = false;
        int selectedIndex = _mTRL_TrafficLockingRules->getSelectedIndex();
        enableTopPart(false);
        _mTRL_TrafficLockingRules->setEnabled(false);

        TrafficLockingData* trafficLockingData = VPtr<TrafficLockingData>::asPtr( _mTrafficLockingModel->get(selectedIndex));

        QList<NBHSensor*>* occupancySensors = trafficLockingData->getOccupancySensors();
        QList<NBHSensor*>* optionalSensors = trafficLockingData->getOptionalSensors();
        QList<int>* ids = trafficLockingData->getUniqueIDs();
        QList<QString> alignments = trafficLockingData->getAlignments();

        CommonSubs::populateJComboBoxWithBeans(_mOccupancyExternalSensor1, "Sensor", occupancySensors->at(0)->getHandleName(), true);
        CommonSubs::populateJComboBoxWithBeans(_mOccupancyExternalSensor2, "Sensor", occupancySensors->at(1)->getHandleName(), true);
        CommonSubs::populateJComboBoxWithBeans(_mOccupancyExternalSensor3, "Sensor", occupancySensors->at(2)->getHandleName(), true);
        CommonSubs::populateJComboBoxWithBeans(_mOccupancyExternalSensor4, "Sensor", occupancySensors->at(3)->getHandleName(), true);
        CommonSubs::populateJComboBoxWithBeans(_mOccupancyExternalSensor5, "Sensor", occupancySensors->at(4)->getHandleName(), true);
        CommonSubs::populateJComboBoxWithBeans(_mOccupancyExternalSensor6, "Sensor", occupancySensors->at(5)->getHandleName(), true);
        CommonSubs::populateJComboBoxWithBeans(_mOccupancyExternalSensor7, "Sensor", occupancySensors->at(6)->getHandleName(), true);
        CommonSubs::populateJComboBoxWithBeans(_mOccupancyExternalSensor8, "Sensor", occupancySensors->at(7)->getHandleName(), true);
        CommonSubs::populateJComboBoxWithBeans(_mOccupancyExternalSensor9, "Sensor", occupancySensors->at(8)->getHandleName(), true);

        CommonSubs::populateJComboBoxWithBeans(_mOptionalExternalSensor1, "Sensor", optionalSensors->at(0)->getHandleName(), true);
        CommonSubs::populateJComboBoxWithBeans(_mOptionalExternalSensor2, "Sensor", optionalSensors->at(1)->getHandleName(), true);

        CommonSubs::setSelectedIndexOfJComboBoxViaUniqueID(_mOS_NumberEntry1, _mCTCSerialData, ids->at(0));
        CommonSubs::setSelectedIndexOfJComboBoxViaUniqueID(_mOS_NumberEntry2, _mCTCSerialData, ids->at(1));
        CommonSubs::setSelectedIndexOfJComboBoxViaUniqueID(_mOS_NumberEntry3, _mCTCSerialData, ids->at(2));
        CommonSubs::setSelectedIndexOfJComboBoxViaUniqueID(_mOS_NumberEntry4, _mCTCSerialData, ids->at(3));
        CommonSubs::setSelectedIndexOfJComboBoxViaUniqueID(_mOS_NumberEntry5, _mCTCSerialData, ids->at(4));

        _mSwitchAlignment1->setSelectedItem(alignments.at(0));
        _mSwitchAlignment2->setSelectedItem(alignments.at(1));
        _mSwitchAlignment3->setSelectedItem(alignments.at(2));
        _mSwitchAlignment4->setSelectedItem(alignments.at(3));
        _mSwitchAlignment5->setSelectedItem(alignments.at(4));
        _mGroupingListAddReplace->setText(tr("Update selected item in the Rules list above"));       // NOI18N
        _mGroupingListAddReplace->setEnabled(true);
        _mRuleEnabled->setChecked(trafficLockingData->_mRuleEnabled != (tr("Disabled")));  // NOI18N  Default if invalid is ENABLED
        _mDestinationSignalOrComment->setText(trafficLockingData->_mDestinationSignalOrComment);
//        _mOS_NumberEntry1.requestFocusInWindow();
    }

    /*private*/ void FrmTRL_Rules::_mDeleteActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        _mTrafficLockingModel->remove(_mTRL_TrafficLockingRules->getSelectedIndex());
        for (int index = 0; index < _mTrafficLockingModel->size(); index++) {
            _mTrafficLockingModel->set(index, VPtr<TrafficLockingData>::asQVariant( renumberRule(VPtr<TrafficLockingData>::asPtr(_mTrafficLockingModel->get(index)), index + 1)));
        }
        enableTopPart(true);
    }

    /*private*/ void FrmTRL_Rules::_mGroupingListAddReplaceActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        TrafficLockingData* trafficLockingData = new TrafficLockingData();
        trafficLockingData->_mRuleEnabled = _mRuleEnabled->isChecked() ? tr("Enabled") : tr("Disabled");  // NOI18N
        trafficLockingData->_mDestinationSignalOrComment = _mDestinationSignalOrComment->text();

        QList<NBHSensor*>* occupancySensors = new QList<NBHSensor*>();
        CommonSubs::addSensorToSensorList(occupancySensors, /*(String)*/_mOccupancyExternalSensor1->getSelectedItem());
        CommonSubs::addSensorToSensorList(occupancySensors, /*(String)*/_mOccupancyExternalSensor2->getSelectedItem());
        CommonSubs::addSensorToSensorList(occupancySensors, /*(String)*/_mOccupancyExternalSensor3->getSelectedItem());
        CommonSubs::addSensorToSensorList(occupancySensors, /*(String)*/_mOccupancyExternalSensor4->getSelectedItem());
        CommonSubs::addSensorToSensorList(occupancySensors, /*(String)*/_mOccupancyExternalSensor5->getSelectedItem());
        CommonSubs::addSensorToSensorList(occupancySensors, /*(String)*/_mOccupancyExternalSensor6->getSelectedItem());
        CommonSubs::addSensorToSensorList(occupancySensors, /*(String)*/_mOccupancyExternalSensor7->getSelectedItem());
        CommonSubs::addSensorToSensorList(occupancySensors, /*(String)*/_mOccupancyExternalSensor8->getSelectedItem());
        CommonSubs::addSensorToSensorList(occupancySensors, /*(String)*/_mOccupancyExternalSensor9->getSelectedItem());
        trafficLockingData->_mOccupancyExternalSensors = occupancySensors;

        QList<NBHSensor*>* optionalSensors = new QList<NBHSensor*>();
        CommonSubs::addSensorToSensorList(optionalSensors, /*(String)*/_mOptionalExternalSensor1->getSelectedItem());
        CommonSubs::addSensorToSensorList(optionalSensors, /*(String)*/_mOptionalExternalSensor2->getSelectedItem());
        trafficLockingData->_mOptionalExternalSensors = optionalSensors;

        TrafficLockingData::TRLSwitch* trlSwitch;
        QList<TrafficLockingData::TRLSwitch*>* switchAlignments = new QList<TrafficLockingData::TRLSwitch*>();
        trlSwitch = getSwitchAllignment(_mOS_NumberEntry1, _mSwitchAlignment1);
        if (trlSwitch != nullptr) switchAlignments->append(trlSwitch);
        trlSwitch = getSwitchAllignment(_mOS_NumberEntry2, _mSwitchAlignment2);
        if (trlSwitch != nullptr) switchAlignments->append(trlSwitch);
        trlSwitch = getSwitchAllignment(_mOS_NumberEntry3, _mSwitchAlignment3);
        if (trlSwitch != nullptr) switchAlignments->append(trlSwitch);
        trlSwitch = getSwitchAllignment(_mOS_NumberEntry4, _mSwitchAlignment4);
        if (trlSwitch != nullptr) switchAlignments->append(trlSwitch);
        trlSwitch = getSwitchAllignment(_mOS_NumberEntry5, _mSwitchAlignment5);
        if (trlSwitch != nullptr) switchAlignments->append(trlSwitch);
        trafficLockingData->_mSwitchAlignments = switchAlignments;

        CheckJMRIObject::VerifyClassReturnValue* verifyClassReturnValue = _mCheckJMRIObject->verifyClass(VPtr<TrafficLockingData>::asQVariant(trafficLockingData));
        if (verifyClassReturnValue != nullptr) { // Error:
            JOptionPane::showMessageDialog(this, verifyClassReturnValue->toString(),
                    tr("Error"), JOptionPane::ERROR_MESSAGE);  // NOI18N
            return;
        }

        _mGroupingListAddReplace->setEnabled(false);
        enableTopPart(true);
        if (_mAddNewPressed) {
            trafficLockingData->_mUserRuleNumber = getRuleNumberString(_mTrafficLockingModel->size() + 1);
//            _mTrafficLockingModel->addElement(VPtr<TrafficLockingData>::asQVariant(trafficLockingData));
        }
        else {
            int selectedIndex = _mTRL_TrafficLockingRules->currentIndex().row();
            trafficLockingData->_mUserRuleNumber = getRuleNumberString(selectedIndex + 1);
            _mTrafficLockingModel->set(selectedIndex, VPtr<TrafficLockingData>::asQVariant( trafficLockingData));
        }
        _mTRL_TrafficLockingRules->setEnabled(true);
    }

    /*private*/ void FrmTRL_Rules::_mCancelActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        enableTopPart(true);
        _mTRL_TrafficLockingRules->setEnabled(true);
    }

    /*private*/ void FrmTRL_Rules::_mEnableALLRulesActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        for (int index = 0; index < _mTrafficLockingModel->getSize(); index++) {
            TrafficLockingData* trafficLockingData = VPtr<TrafficLockingData>::asPtr(_mTrafficLockingModel->get(index));
            trafficLockingData->_mRuleEnabled = tr("Enabled");   // NOI18N
            _mTrafficLockingModel->set(index, VPtr<TrafficLockingData>::asQVariant(trafficLockingData));
        }
    }

    /*private*/ void FrmTRL_Rules::_mDisableALLRulesActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        for (int index = 0; index < _mTrafficLockingModel->getSize(); index++) {
            TrafficLockingData* trafficLockingData = VPtr<TrafficLockingData>::asPtr(_mTrafficLockingModel->get(index));
            trafficLockingData->_mRuleEnabled = tr("Disabled");  // NOI18N
            _mTrafficLockingModel->set(index, VPtr<TrafficLockingData>::asQVariant(trafficLockingData));
        }
    }

    /*private*/ void FrmTRL_Rules::_mDupToEndActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        TrafficLockingData* trafficLockingData = VPtr<TrafficLockingData>::asPtr(_mTrafficLockingModel->get(_mTRL_TrafficLockingRules->getSelectedIndex()));
        trafficLockingData->_mUserRuleNumber = getRuleNumberString(_mTrafficLockingModel->size() + 1);
        _mTrafficLockingModel->addElement(VPtr<TrafficLockingData>::asQVariant(trafficLockingData));
    }

    /*private*/ TrafficLockingData* FrmTRL_Rules::renumberRule(TrafficLockingData* rule, int number) {
        rule->_mUserRuleNumber = getRuleNumberString(number);
        return rule;
    }

    /*public*/ /*static*/ QString FrmTRL_Rules::getRuleNumberString(int ruleNumber) { return " " + tr("Rule #:") + QString::number(ruleNumber); }   // NOI18N

    /*public*/ /*static*/ QString FrmTRL_Rules::getRuleEnabledString() { return tr("Enabled"); }

    /*public*/ TrafficLockingData::TRLSwitch* FrmTRL_Rules::getSwitchAllignment(JComboBox* userText, JComboBox* alignment) {
        TrafficLockingData::TRLSwitch* trlSwitch = nullptr;
        int osNumberSelectedIndex = userText->getSelectedIndex();
        if (osNumberSelectedIndex > 0) {
            trlSwitch = new TrafficLockingData::TRLSwitch(
                    /*(String)*/userText->getSelectedItem(),
                    /*(String)*/alignment->getSelectedItem(),
                    _mArrayListOfSelectableOSSectionUniqueIDs.at(osNumberSelectedIndex - 1));
        }
        return trlSwitch;
    }

    /*private*/ void FrmTRL_Rules::enableTopPart(bool enabled) {
        _mAddNew->setEnabled(enabled);
        _mDestinationSignalOrComment->setEnabled(!enabled);
        _mOccupancyExternalSensor1->setEnabled(!enabled);
        _mOccupancyExternalSensor2->setEnabled(!enabled);
        _mOccupancyExternalSensor3->setEnabled(!enabled);
        _mOccupancyExternalSensor4->setEnabled(!enabled);
        _mOccupancyExternalSensor5->setEnabled(!enabled);
        _mOccupancyExternalSensor6->setEnabled(!enabled);
        _mOccupancyExternalSensor7->setEnabled(!enabled);
        _mOccupancyExternalSensor8->setEnabled(!enabled);
        _mOccupancyExternalSensor9->setEnabled(!enabled);
        _mOptionalExternalSensor1->setEnabled(!enabled);
        _mOptionalExternalSensor2->setEnabled(!enabled);
        _mOS_NumberEntry1->setEnabled(!enabled);
        _mOS_NumberEntry2->setEnabled(!enabled);
        _mOS_NumberEntry3->setEnabled(!enabled);
        _mOS_NumberEntry4->setEnabled(!enabled);
        _mOS_NumberEntry5->setEnabled(!enabled);
        _mRuleEnabled->setEnabled(!enabled);
        _mSwitchAlignment1->setEnabled(!enabled);
        _mSwitchAlignment2->setEnabled(!enabled);
        _mSwitchAlignment3->setEnabled(!enabled);
        _mSwitchAlignment4->setEnabled(!enabled);
        _mSwitchAlignment5->setEnabled(!enabled);
        _mGroupingListAddReplace->setEnabled(!enabled);
        _mCancel->setEnabled(!enabled);
        _mSaveAndClose->setEnabled(enabled);

//        if (enabled) this.getRootPane()->setDefaultButton(_mSaveAndClose);
//        else this.getRootPane()->setDefaultButton(_mGroupingListAddReplace);
    }

