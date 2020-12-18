﻿#include "frmcb.h"
#include "ctcserialdata.h"
#include "programproperties.h"
#include "jcombobox.h"
#include "jformattedtextfield.h"
#include "checkjmriobject.h"
#include "codebuttonhandlerdataroutines.h"

/**
 *
 * @author Gregory J. Bedlek Copyright (C) 2018, 2019
 */
// /*public*/ class FrmCB extends JFrame {

    /**
     *
     */
    /*private*/ /*static*/ /*final*/ QString FrmCB::FORM_PROPERTIES = "DlgCB";  // NOI18N
    /*private*/ /*static*/ /*final*/ QString FrmCB::PREFIX = "_mOS";            // NOI18N

    /*private*/ void FrmCB::initOrig() {
        _mOSSectionOccupiedExternalSensorOrig = _mCodeButtonHandlerData->_mOSSectionOccupiedExternalSensor->getHandleName();
        _mOSSectionOccupiedExternalSensor2Orig = _mCodeButtonHandlerData->_mOSSectionOccupiedExternalSensor2->getHandleName();
        _mOSSectionSwitchSlavedToUniqueIDIndexOrig = _mOSSectionSwitchSlavedToUniqueID->getSelectedIndex();
        _mCodeButtonDelayTimeOrig = _mCodeButtonHandlerData->_mCodeButtonDelayTime;
    }
    /*private*/ bool FrmCB::dataChanged() {
        if (_mOSSectionOccupiedExternalSensorOrig != (_mOSSectionOccupiedExternalSensor->getSelectedItem())) return true;
        if (_mOSSectionOccupiedExternalSensor2Orig !=(_mOSSectionOccupiedExternalSensor2->getSelectedItem())) return true;
        if (_mOSSectionSwitchSlavedToUniqueIDIndexOrig != _mOSSectionSwitchSlavedToUniqueID->getSelectedIndex()) return true;
        if (CommonSubs::getIntFromJTextFieldNoThrow(_mCodeButtonDelayTime) != _mCodeButtonDelayTimeOrig) return true;
        return false;
    }

    /*public*/ FrmCB::FrmCB(   AwtWindowProperties* awtWindowProperties, CodeButtonHandlerData* codeButtonHandlerData, ProgramProperties* programProperties,
                    CTCSerialData* ctcSerialData, CheckJMRIObject* checkJMRIObject, QWidget* parent) : JFrame(parent){
        //super();
        initComponents();
        CommonSubs::addHelpMenu(this, "package.jmri.jmrit.ctc.CTC_frmCB", true);  // NOI18N
        _mAwtWindowProperties = awtWindowProperties;
        _mCodeButtonHandlerData = codeButtonHandlerData;
        _mProgramProperties = programProperties;
        _mCTCSerialData = ctcSerialData;
        _mCheckJMRIObject = checkJMRIObject;
        _mArrayListOfSelectableOSSectionUniqueIDs = CommonSubs::getArrayListOfSelectableOSSectionUniqueIDs(_mCTCSerialData->getCodeButtonHandlerDataArrayList());
        CommonSubs::populateJComboBoxWithBeans(_mCodeButtonInternalSensor, "Sensor", _mCodeButtonHandlerData->_mCodeButtonInternalSensor->getHandleName(), false);   // NOI18N
        CommonSubs::populateJComboBoxWithBeans(_mOSSectionOccupiedExternalSensor, "Sensor", _mCodeButtonHandlerData->_mOSSectionOccupiedExternalSensor->getHandleName(), true);   // NOI18N
        CommonSubs::populateJComboBoxWithBeans(_mOSSectionOccupiedExternalSensor2, "Sensor", _mCodeButtonHandlerData->_mOSSectionOccupiedExternalSensor2->getHandleName(), true);  // NOI18N
        CommonSubs::populateJComboBoxWithColumnDescriptionsAndSelectViaUniqueID(_mOSSectionSwitchSlavedToUniqueID, _mCTCSerialData, _mCodeButtonHandlerData->_mOSSectionSwitchSlavedToUniqueID);
        CommonSubs::setMillisecondsEdit(_mCodeButtonDelayTime);
        _mCodeButtonDelayTime->setText(QString::number(_mCodeButtonHandlerData->_mCodeButtonDelayTime));
        initOrig();
        _mAwtWindowProperties->setWindowState(this, FORM_PROPERTIES);
        //this.getRootPane().setDefaultButton(_mSaveAndClose);
        _mSaveAndClose->setDefault(true);
    }

    /*public*/ /*static*/ bool FrmCB::dialogCodeButtonHandlerDataValid(CheckJMRIObject* checkJMRIObject, CodeButtonHandlerData* codeButtonHandlerData) {
//  Checks:
        if(codeButtonHandlerData->_mOSSectionOccupiedExternalSensor == nullptr) return false;
        if (ProjectsCommonSubs::isNullOrEmptyString(codeButtonHandlerData->_mOSSectionOccupiedExternalSensor->getHandleName())) return false;
        return checkJMRIObject->validClassWithPrefix(PREFIX, VPtr<CodeButtonHandlerData>::asQVariant(codeButtonHandlerData));
    }

//  Validate all internal fields as much as possible:
    /*private*/ QList<QString> FrmCB::formFieldsValid() {
        QList<QString> errors = QList<QString>();
//  Checks:
        CommonSubs::checkJComboBoxNotEmpty(_mOSSectionOccupiedExternalSensor, _mOSSectionOccupiedExternalSensorPrompt, errors);
        _mCheckJMRIObject->analyzeForm(PREFIX, this, errors);
        return errors;
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    // <editor-fold defaultstate="collapsed" desc="Generated Code">
    /*private*/ void FrmCB::initComponents() {

        _mCodeButtonInternalSensorPrompt = new JLabel();
        _mCodeButtonInternalSensor = new JComboBox();
        _mSaveAndClose = new JButton();
        jButton2 = new JButton();
        _mOSSectionOccupiedExternalSensorPrompt = new JLabel();
        _mOSSectionSwitchSlavedToUniqueID = new JComboBox();
        jLabel3 = new JLabel();
        jLabel4 = new JLabel();
        jLabel9 = new JLabel();
        _mCodeButtonDelayTime = new JFormattedTextField();
        jLabel5 = new JLabel();
        jLabel6 = new JLabel();
        jLabel7 = new JLabel();
        jLabel1 = new JLabel();
        _mOSSectionOccupiedExternalSensorPrompt1 = new JLabel();
        jLabel2 = new JLabel();
        jLabel8 = new JLabel();
        jLabel10 = new JLabel();
        _mOSSectionOccupiedExternalSensor = new JComboBox();
        _mOSSectionOccupiedExternalSensor2 = new JComboBox();

        setDefaultCloseOperation(JFrame::DO_NOTHING_ON_CLOSE);
        setTitle(tr("Edit Code Button"));
//        addWindowListener(new java.awt.event.WindowAdapter() {
//            @Override
//            /*public*/ void windowClosing(java.awt.event.WindowEvent evt) {
//                formWindowClosing(evt);
//            }
//        });
        addWindowListener(new FrmCB_windowListener(this));

        _mCodeButtonInternalSensorPrompt->setText(tr("Code Button sensor:"));

        //_mCodeButtonInternalSensor->setModel(new DefaultComboBoxModel<>(new String[] { "Item 1", "Item 2", "Item 3", "Item 4" }));
        _mCodeButtonInternalSensor->addItems({ "Item 1", "Item 2", "Item 3", "Item 4" });
        _mSaveAndClose->setText(tr("Save and Close"));
//        _mSaveAndClose.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
        connect(_mSaveAndClose, &JButton::clicked, [=]{
                _mSaveAndCloseActionPerformed(/*evt*/);
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

        _mOSSectionOccupiedExternalSensorPrompt->setText(tr("Primary O.S. section occupied sensor:"));

//        _mOSSectionSwitchSlavedToUniqueID.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
        connect(_mOSSectionSwitchSlavedToUniqueID, &JComboBox::currentIndexChanged, [=]{
                _mOSSectionSwitchSlavedToUniqueIDActionPerformed(/*evt*/);
//            }
        });

        jLabel3->setText(tr("Switch slaved to O.S. section #:"));

        jLabel4->setText(tr("Leave this blank if this is a normal O.S. section"));

        jLabel9->setText(tr("Selecting self forces blank!"));

//        _mCodeButtonDelayTime->setFormatterFactory(new DefaultFormatterFactory(new NumberFormatter(new DecimalFormat("#0"))));

        jLabel5->setText(tr("No Code Button delay (in milliseconds):"));

        jLabel6->setText(tr("Enter 0 for normal Code Button"));

        jLabel7->setText(tr("Enter >0 for tower O.S. section delay (no Code Button)"));

        jLabel1->setText(tr("Required"));

        _mOSSectionOccupiedExternalSensorPrompt1->setText(tr("Secondary O.S. section occupied sensor:"));

        jLabel2->setText(tr("Optional"));

        jLabel8->setText(tr("Locks everything"));

        jLabel10->setText(tr("Prevents turnout change, turnout lock"));

        //_mOSSectionOccupiedExternalSensor->setModel(new DefaultComboBoxModel<>(new String[] { "Item 1", "Item 2", "Item 3", "Item 4" }));
        _mOSSectionOccupiedExternalSensor->addItems({ "Item 1", "Item 2", "Item 3", "Item 4" });

        //_mOSSectionOccupiedExternalSensor2.setModel(new DefaultComboBoxModel<>(new String[] { "Item 1", "Item 2", "Item 3", "Item 4" }));
        _mOSSectionOccupiedExternalSensor2->addItems({ "Item 1", "Item 2", "Item 3", "Item 4" });
    #if 0
        GroupLayout layout = new GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addContainerGap()
                        .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                            .addGroup(layout.createSequentialGroup()
                                .addGap(5, 5, 5)
                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.TRAILING)
                                    .addComponent(_mOSSectionOccupiedExternalSensorPrompt1)
                                    .addComponent(_mOSSectionOccupiedExternalSensorPrompt)
                                    .addComponent(_mCodeButtonInternalSensorPrompt)
                                    .addComponent(jLabel8)
                                    .addComponent(jLabel10))
                                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                                    .addGroup(layout.createSequentialGroup()
                                        .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                                            .addComponent(_mCodeButtonInternalSensor, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                                            .addComponent(_mOSSectionOccupiedExternalSensor2, GroupLayout.PREFERRED_SIZE, 222, GroupLayout.PREFERRED_SIZE))
                                        .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                                        .addComponent(jLabel2))
                                    .addGroup(layout.createSequentialGroup()
                                        .addComponent(_mOSSectionOccupiedExternalSensor, GroupLayout.PREFERRED_SIZE, 222, GroupLayout.PREFERRED_SIZE)
                                        .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                                        .addComponent(jLabel1))))
                            .addGroup(layout.createSequentialGroup()
                                .addGap(21, 21, 21)
                                .addComponent(jLabel3)
                                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                                    .addComponent(jLabel4)
                                    .addGroup(layout.createSequentialGroup()
                                        .addComponent(_mOSSectionSwitchSlavedToUniqueID, GroupLayout.PREFERRED_SIZE, 126, GroupLayout.PREFERRED_SIZE)
                                        .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                                        .addComponent(jLabel9))))
                            .addGroup(layout.createSequentialGroup()
                                .addComponent(jLabel5)
                                .addGap(35, 35, 35)
                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                                    .addComponent(jLabel7)
                                    .addComponent(jLabel6)
                                    .addComponent(_mCodeButtonDelayTime, GroupLayout.PREFERRED_SIZE, 93, GroupLayout.PREFERRED_SIZE)))))
                    .addGroup(layout.createSequentialGroup()
                        .addGap(170, 170, 170)
                        .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                            .addComponent(_mSaveAndClose)
                            .addComponent(jButton2))))
                .addContainerGap(125, Short.MAX_VALUE))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                    .addComponent(_mCodeButtonInternalSensorPrompt)
                    .addComponent(_mCodeButtonInternalSensor, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                    .addComponent(_mOSSectionOccupiedExternalSensorPrompt)
                    .addComponent(jLabel1)
                    .addComponent(_mOSSectionOccupiedExternalSensor, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(jLabel8)
                .addGap(18, 18, 18)
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                    .addComponent(_mOSSectionOccupiedExternalSensorPrompt1)
                    .addComponent(jLabel2)
                    .addComponent(_mOSSectionOccupiedExternalSensor2, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jLabel10)
                .addGap(26, 26, 26)
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                    .addComponent(_mOSSectionSwitchSlavedToUniqueID, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                    .addComponent(jLabel3)
                    .addComponent(jLabel9))
                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jLabel4)
                .addGap(18, 18, 18)
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                    .addComponent(_mCodeButtonDelayTime, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                    .addComponent(jLabel5))
                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jLabel6)
                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jLabel7)
                .addGap(29, 29, 29)
                .addComponent(_mSaveAndClose)
                .addGap(18, 18, 18)
                .addComponent(jButton2)
                .addGap(19, 19, 19))
        );
#else
        JPanel* contentPane = new JPanel();
        QVBoxLayout* contentPaneLayout;
        contentPane->setLayout(contentPaneLayout = new QVBoxLayout());
        setCentralWidget(contentPane);

        JPanel* panel1 = new JPanel(new QHBoxLayout());
        ((QHBoxLayout*)panel1->layout())->addWidget(_mCodeButtonInternalSensorPrompt, 0, Qt::AlignRight);
        ((QHBoxLayout*)panel1->layout())->addWidget(_mCodeButtonInternalSensor, 0, Qt::AlignCenter);
        contentPaneLayout->addWidget(panel1, 0,  Qt::AlignHCenter);


        JPanel* panel2 = new JPanel(new QHBoxLayout());
        ((QHBoxLayout*)panel2->layout())->addWidget(_mOSSectionOccupiedExternalSensorPrompt, 0, Qt::AlignRight);
        ((QHBoxLayout*)panel2->layout())->addWidget(_mOSSectionOccupiedExternalSensor, 0, Qt::AlignLeft);
        ((QHBoxLayout*)panel2->layout())->addWidget(jLabel1);
        contentPaneLayout->addWidget(panel2, 0,  Qt::AlignHCenter);

        JPanel* panel3 = new JPanel(new QHBoxLayout());
        ((QHBoxLayout*)panel3->layout())->addWidget(new JLabel("    "));
        ((QHBoxLayout*)panel3->layout())->addWidget(jLabel8);
        contentPaneLayout->addWidget(panel3, 0,  Qt::AlignHCenter);

        JPanel* panel4 = new JPanel(new QHBoxLayout());
        ((QHBoxLayout*)panel4->layout())->addWidget(_mOSSectionOccupiedExternalSensorPrompt1, 0, Qt::AlignRight);
        ((QHBoxLayout*)panel4->layout())->addWidget(_mOSSectionOccupiedExternalSensor2, 0, Qt::AlignLeft);
        ((QHBoxLayout*)panel4->layout())->addWidget(jLabel2);
        contentPaneLayout->addWidget(panel4, 0,  Qt::AlignHCenter);

        JPanel* panel5 = new JPanel(new QHBoxLayout());
        ((QHBoxLayout*)panel5->layout())->addWidget(new JLabel("    "));
        ((QHBoxLayout*)panel5->layout())->addWidget(jLabel10);
        contentPaneLayout->addWidget(panel5, 0,  Qt::AlignHCenter);

        JPanel* panel6 = new JPanel(new QHBoxLayout());
        ((QHBoxLayout*)panel6->layout())->addWidget(jLabel3, 0, Qt::AlignRight);
        ((QHBoxLayout*)panel6->layout())->addWidget(_mOSSectionSwitchSlavedToUniqueID, 0, Qt::AlignLeft);
        ((QHBoxLayout*)panel6->layout())->addWidget(jLabel9);
        contentPaneLayout->addWidget(panel6, 0,  Qt::AlignHCenter);

        JPanel* panel7 = new JPanel(new QHBoxLayout());
        ((QHBoxLayout*)panel7->layout())->addWidget(new JLabel("    "));
        ((QHBoxLayout*)panel7->layout())->addWidget(jLabel4);
        contentPaneLayout->addWidget(panel7, 0,  Qt::AlignHCenter);

        JPanel* panel8 = new JPanel(new QHBoxLayout());
        JPanel* panel8a = new JPanel(new QVBoxLayout());
        panel8a->layout()->addWidget(_mCodeButtonDelayTime);
        panel8a->layout()->addWidget(jLabel6);
        panel8a->layout()->addWidget(jLabel7);
        panel8->layout()->addWidget(jLabel5);
        panel8->layout()->addWidget(panel8a);
        contentPaneLayout->addWidget(panel8, 0,  Qt::AlignHCenter);

        JPanel* panel9 = new JPanel(new QHBoxLayout());
        JPanel* panel9a = new JPanel(new QVBoxLayout());
        JPanel* panel9b = new JPanel(new FlowLayout());
        panel9b->layout()->addWidget(_mSaveAndClose);
        panel9a->layout()->addWidget(panel9b);
        panel9b = new JPanel(new FlowLayout());
        panel9b->layout()->addWidget(jButton2);
        panel9a->layout()->addWidget(panel9b);
        panel9->layout()->addWidget(panel9a);
        contentPaneLayout->addWidget(panel9);
#endif
        pack();
    }// </editor-fold>

    /*private*/ void FrmCB::_mSaveAndCloseActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        if (CommonSubs::missingFieldsErrorDialogDisplayed(this, formFieldsValid(), false)) {
            return; // Do not allow exit or transfer of data.
        }

        _mCodeButtonHandlerData->_mCodeButtonInternalSensor = CommonSubs::getNBHSensor(_mCodeButtonInternalSensor->getSelectedItem(), false);

        NBHSensor* newSensor = CommonSubs::getNBHSensor(_mOSSectionOccupiedExternalSensor->getSelectedItem(), false);
        if (newSensor != nullptr) _mCodeButtonHandlerData->_mOSSectionOccupiedExternalSensor = newSensor;

        newSensor = CommonSubs::getNBHSensor(_mOSSectionOccupiedExternalSensor2->getSelectedItem(), false);
        if (newSensor != nullptr) _mCodeButtonHandlerData->_mOSSectionOccupiedExternalSensor2 = newSensor;

        int selectedIndex = _mOSSectionSwitchSlavedToUniqueID->getSelectedIndex();
        if (selectedIndex > 0) { // None and skip blank entry
            _mCodeButtonHandlerData->_mOSSectionSwitchSlavedToUniqueID = _mArrayListOfSelectableOSSectionUniqueIDs.value(selectedIndex - 1);  // Correct for blank entry
        } else if (selectedIndex == 0) { // Blank entry:
            _mCodeButtonHandlerData->_mOSSectionSwitchSlavedToUniqueID = CodeButtonHandlerData::SWITCH_NOT_SLAVED;
        }
        _mCodeButtonHandlerData->_mCodeButtonDelayTime = CommonSubs::getIntFromJTextFieldNoThrow(_mCodeButtonDelayTime);
        _mClosedNormally = true;
        _mAwtWindowProperties->saveWindowState(this, FORM_PROPERTIES);
        dispose();
    }

    /*private*/ void FrmCB::formWindowClosing(QCloseEvent* evt) {
        _mAwtWindowProperties->saveWindowState(this, FORM_PROPERTIES);
        if (CommonSubs::allowClose(this, dataChanged())) dispose();
    }

    /*private*/ void FrmCB::jButton2ActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        CodeButtonHandlerData* temp = _mCodeButtonHandlerData;
        temp = CodeButtonHandlerDataRoutines::uECBHDWSD_CodeButton(_mProgramProperties, temp);
        CommonSubs::populateJComboBoxWithBeans(_mCodeButtonInternalSensor, "Sensor", temp->_mCodeButtonInternalSensor->getHandleName(), false);   // NOI18N
    }

    /*private*/ void FrmCB::_mOSSectionSwitchSlavedToUniqueIDActionPerformed(/*java.awt.event.ActionEvent evt*/) {
//  Verify user didn't select "self", since I don't want to screw up array indexes by eliminating it:
        int selectedIndex = _mOSSectionSwitchSlavedToUniqueID->getSelectedIndex();
        if (selectedIndex > 0) { // None and skip blank entry
            int osSectionSelectedUniqueID = _mArrayListOfSelectableOSSectionUniqueIDs.at(selectedIndex - 1);  // Correct for blank entry
            if (osSectionSelectedUniqueID == _mCodeButtonHandlerData->_mUniqueID) {
                _mOSSectionSwitchSlavedToUniqueID->setCurrentIndex(0); // Back to blank!
            }
        }
    }