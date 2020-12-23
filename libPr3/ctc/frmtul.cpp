#include "frmtul.h"
#include "commonsubs.h"
#include "codebuttonhandlerdataroutines.h"
#include "instancemanager.h"
#include "turnoutmanager.h"

/**
 *
 * @author Gregory J. Bedlek Copyright (C) 2018, 2019
 *
 * 7/30/2020 Bug Fix (found by a user in the field, as reported to Dave Sand):
 * The user can in two different O.S. sections (or in the
 * same O.S. section) mention the same turnout multiple times.  Now, of course
 * this is illegal, however the program does NOT (at present) enforce this.
 * Then at run-time, this causes an "infinite loop" as each tries to fight
 * against the other(s), and eventually the stack overflows.
 * To Fix: At start of form, get a list of all other O.S. sections turnouts
 * that are mentioned, this is a "static" exclusion list for this time only
 * run" of this form.
 * In addition, when editing one of the lists, the other 3 lists selected
 * items also are excluded "dynamically".
 */
// /*public*/ class FrmTUL extends JFrame {

/**
 * Creates new form DlgTUL
 */
/*private*/ /*static*/ /*final*/ QString FrmTUL::FORM_PROPERTIES = "DlgTUL";     // NOI18N
/*private*/ /*static*/ /*final*/ QString FrmTUL::PREFIX = "_mTUL_";              // NOI18N


/*private*/ void FrmTUL::initOrig() {
    _mTUL_ExternalTurnoutOrig = _mCodeButtonHandlerData->_mTUL_ExternalTurnout->getHandleName();
    _mTUL_ExternalTurnoutFeedbackDifferentOrig = _mCodeButtonHandlerData->_mTUL_ExternalTurnoutFeedbackDifferent;
    _mTUL_NoDispatcherControlOfSwitchOrig = _mCodeButtonHandlerData->_mTUL_NoDispatcherControlOfSwitch;
    _mTUL_GUI_IconsEnabledOrig = _mCodeButtonHandlerData->_mTUL_GUI_IconsEnabled;
    _mTUL_ndcos_WhenLockedSwitchStateIsClosedOrig = _mCodeButtonHandlerData->_mTUL_ndcos_WhenLockedSwitchStateIsClosed;
    _mTUL_LockImplementationOrig = _mCodeButtonHandlerData->_mTUL_LockImplementation;
    _mTUL_AdditionalExternalTurnout1Orig = _mCodeButtonHandlerData->_mTUL_AdditionalExternalTurnout1->getHandleName();
    _mTUL_AdditionalExternalTurnout1FeedbackDifferentOrig = _mCodeButtonHandlerData->_mTUL_AdditionalExternalTurnout1FeedbackDifferent;
    _mTUL_AdditionalExternalTurnout2Orig = _mCodeButtonHandlerData->_mTUL_AdditionalExternalTurnout2->getHandleName();
    _mTUL_AdditionalExternalTurnout2FeedbackDifferentOrig = _mCodeButtonHandlerData->_mTUL_AdditionalExternalTurnout2FeedbackDifferent;
    _mTUL_AdditionalExternalTurnout3Orig = _mCodeButtonHandlerData->_mTUL_AdditionalExternalTurnout3->getHandleName();
    _mTUL_AdditionalExternalTurnout3FeedbackDifferentOrig = _mCodeButtonHandlerData->_mTUL_AdditionalExternalTurnout3FeedbackDifferent;
}

/*private*/ bool FrmTUL::dataChanged() {
    if (_mTUL_ExternalTurnoutOrig !=(_mTUL_ExternalTurnout->getSelectedItem())) return true;
    if (_mTUL_ExternalTurnoutFeedbackDifferentOrig != _mTUL_ExternalTurnoutFeedbackDifferent->isChecked()) return true;
    if (_mTUL_NoDispatcherControlOfSwitchOrig != _mTUL_NoDispatcherControlOfSwitch->isChecked()) return true;
    if (_mTUL_ndcos_WhenLockedSwitchStateIsClosedOrig != _mTUL_ndcos_WhenLockedSwitchStateIsClosed->isChecked()) return true;
    if (_mTUL_GUI_IconsEnabledOrig != _mTUL_GUI_IconsEnabled->isChecked()) return true;
    if (_mTUL_LockImplementationOrig != CodeButtonHandlerData::LOCK_IMPLEMENTATION::getLockImplementation(_mTUL_LockImplementation)) return true;
    if (_mTUL_AdditionalExternalTurnout1Orig !=(_mTUL_AdditionalExternalTurnout1->getSelectedItem())) return true;
    if (_mTUL_AdditionalExternalTurnout1FeedbackDifferentOrig != _mTUL_AdditionalExternalTurnout1FeedbackDifferent->isChecked()) return true;
    if (_mTUL_AdditionalExternalTurnout2Orig != (_mTUL_AdditionalExternalTurnout2->getSelectedItem())) return true;
    if (_mTUL_AdditionalExternalTurnout2FeedbackDifferentOrig != _mTUL_AdditionalExternalTurnout2FeedbackDifferent->isChecked()) return true;
    if (_mTUL_AdditionalExternalTurnout3Orig != (_mTUL_AdditionalExternalTurnout3->getSelectedItem())) return true;
    if (_mTUL_AdditionalExternalTurnout3FeedbackDifferentOrig != _mTUL_AdditionalExternalTurnout3FeedbackDifferent->isChecked()) return true;
    return false;
}

/*public*/ FrmTUL::FrmTUL(AwtWindowProperties* awtWindowProperties,
                CTCSerialData* ctcSerialData,
                CodeButtonHandlerData *codeButtonHandlerData,
                ProgramProperties* programProperties, CheckJMRIObject* checkJMRIObject, QWidget* parent) : JFrame(parent) {
    //super();
    initComponents();
    CommonSubs::addHelpMenu(this, "package.jmri.jmrit.ctc.CTC_frmTUL", true);  // NOI18N
    _mAwtWindowProperties = awtWindowProperties;
    _mCTCSerialData = ctcSerialData;
    _mCodeButtonHandlerData = codeButtonHandlerData;
    _mProgramProperties = programProperties;
    _mCheckJMRIObject = checkJMRIObject;
    CommonSubs::numberButtonGroup(_mTUL_LockImplementation);
    CommonSubs::setButtonSelected(_mTUL_LockImplementation, _mCodeButtonHandlerData->_mTUL_LockImplementation.getInt());
    CommonSubs::populateJComboBoxWithBeans(_mTUL_DispatcherInternalSensorLockToggle, "Sensor", _mCodeButtonHandlerData->_mTUL_DispatcherInternalSensorLockToggle->getHandleName(), false);   // NOI18N
    CommonSubs::populateJComboBoxWithBeans(_mTUL_DispatcherInternalSensorUnlockedIndicator, "Sensor", _mCodeButtonHandlerData->_mTUL_DispatcherInternalSensorUnlockedIndicator->getHandleName(), false);   // NOI18N
    _mTUL_ExternalTurnoutFeedbackDifferent->setChecked(_mCodeButtonHandlerData->_mTUL_ExternalTurnoutFeedbackDifferent);
    _mTUL_GUI_IconsEnabled->setChecked(_mCodeButtonHandlerData->_mTUL_GUI_IconsEnabled);
    _mTUL_NoDispatcherControlOfSwitch->setChecked(_mCodeButtonHandlerData->_mTUL_NoDispatcherControlOfSwitch);
    _mTUL_ndcos_WhenLockedSwitchStateIsClosed->setChecked(_mCodeButtonHandlerData->_mTUL_ndcos_WhenLockedSwitchStateIsClosed);
    _mTUL_NoDispatcherControlOfSwitchActionPerformed(/*null*/);     // Enable/Disable _mTUL_ndcos_WhenLockedSwitchStateIsClosed

    // The CTCv1 import process can create empty NBHSensors.
    if (!_mCodeButtonHandlerData->_mTUL_DispatcherInternalSensorLockToggle->valid()) {
        // Use reapply patterns to fix the sensors
        jButton2ActionPerformed(/*null*/);
    }

    _mTUL_AdditionalExternalTurnout1FeedbackDifferent->setChecked(_mCodeButtonHandlerData->_mTUL_AdditionalExternalTurnout1FeedbackDifferent);
    _mTUL_AdditionalExternalTurnout2FeedbackDifferent->setChecked(_mCodeButtonHandlerData->_mTUL_AdditionalExternalTurnout2FeedbackDifferent);
    _mTUL_AdditionalExternalTurnout3FeedbackDifferent->setChecked(_mCodeButtonHandlerData->_mTUL_AdditionalExternalTurnout3FeedbackDifferent);
    _mCurrentExternalTurnout = _mCodeButtonHandlerData->_mTUL_ExternalTurnout->getHandleName();
    _mCurrentAdditionalTurnout1 = _mCodeButtonHandlerData->_mTUL_AdditionalExternalTurnout1->getHandleName();
    _mCurrentAdditionalTurnout2 = _mCodeButtonHandlerData->_mTUL_AdditionalExternalTurnout2->getHandleName();
    _mCurrentAdditionalTurnout3 = _mCodeButtonHandlerData->_mTUL_AdditionalExternalTurnout3->getHandleName();
    initOrig();
    initializeAll4LockedTurnoutJComboBoxesAndSupportingData();
    _mAwtWindowProperties->setWindowState(this, FORM_PROPERTIES);
    //this.getRootPane()->setDefaultButton(_mSaveAndClose);
    _mSaveAndClose->setDefault(true);
}

/*public*/ /*static*/ bool FrmTUL::dialogCodeButtonHandlerDataValid(CheckJMRIObject* checkJMRIObject, CodeButtonHandlerData* codeButtonHandlerData) {
    if (!codeButtonHandlerData->_mTUL_Enabled) return true; // Not enabled, can be no error!
//  Checks:
    if (ProjectsCommonSubs::isNullOrEmptyString(codeButtonHandlerData->_mTUL_ExternalTurnout->getHandleName())) return false;
    return checkJMRIObject->validClassWithPrefix(PREFIX, VPtr<CodeButtonHandlerData>::asQVariant( codeButtonHandlerData));
}

//  Validate all internal fields as much as possible:
/*private*/ QList<QString> FrmTUL::formFieldsValid() {
    QList<QString> errors = QList<QString>();
//  Checks:
    CommonSubs::checkJComboBoxNotEmpty(_mTUL_ExternalTurnout, _mTUL_ActualTurnoutPrompt, errors);
    _mCheckJMRIObject->analyzeForm(PREFIX, this, errors);
    return errors;
}

/**
 * This method is called from within the constructor to initialize the form.
 * WARNING: Do NOT modify this code. The content of this method is always
 * regenerated by the Form Editor.
 */
// <editor-fold defaultstate="collapsed" desc="Generated Code">
/*private*/ void FrmTUL::initComponents() {

    _mTUL_LockImplementation = new QButtonGroup(this);
    _mSaveAndClose = new JButton();
    jLabel2 = new JLabel();
    _mTUL_DispatcherInternalSensorLockToggle = new JComboBox();
    _mTUL_ExternalTurnoutFeedbackDifferent = new JCheckBox();
    jLabel4 = new JLabel();
    _mTUL_ActualTurnoutPrompt = new JLabel();
    jLabel6 = new JLabel();
    _mTUL_DispatcherInternalSensorUnlockedIndicator = new JComboBox();
    _mTUL_NoDispatcherControlOfSwitch = new JCheckBox();
    jLabel7 = new JLabel();
    _mTUL_GUI_IconsEnabled = new JCheckBox();
    _mLabelDlgTULGUIEnable = new JLabel();
    jButton2 = new JButton();
    jRadioButton1 = new QRadioButton();
    jLabel1 = new JLabel();
    jRadioButton2 = new QRadioButton();
    jLabel11 = new JLabel();
    _mTUL_AdditionalExternalTurnout1FeedbackDifferent = new JCheckBox();
    _mTUL_AdditionalExternalTurnout2FeedbackDifferent = new JCheckBox();
    _mTUL_AdditionalExternalTurnout3FeedbackDifferent = new JCheckBox();
    _mTUL_ExternalTurnout = new JComboBox();
    _mTUL_AdditionalExternalTurnout1 = new JComboBox();
    _mTUL_AdditionalExternalTurnout2 = new JComboBox();
    _mTUL_AdditionalExternalTurnout3 = new JComboBox();
    _mLabelDlgTULClosed = new JLabel();
    _mTUL_ndcos_WhenLockedSwitchStateIsClosed = new JCheckBox();

    setDefaultCloseOperation(JFrame::DO_NOTHING_ON_CLOSE);
    setTitle(tr("Edit turnout locking"));
//    addWindowListener(new java.awt.event.WindowAdapter() {
//        @Override
//        /*public*/ void windowClosing(java.awt.event.WindowEvent evt) {
//            formWindowClosing(evt);
//        }
//    });
    addWindowListener(new FrmTUL_windowListener(this));

    _mSaveAndClose->setText(tr("Save and Close"));
//    _mSaveAndClose.addActionListener(new java.awt.event.ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
    connect(_mSaveAndClose, &JButton::clicked, [=]{
            _mSaveAndCloseActionPerformed(/*evt*/);
//        }
    });

    jLabel2->setHorizontalAlignment(Qt::AlignRight);
    jLabel2->setText(tr("Dispatcher sensor lock toggle:"));

    //_mTUL_DispatcherInternalSensorLockToggle->setModel(new DefaultComboBoxModel<>(new String[] { "Item 1", "Item 2", "Item 3", "Item 4" }));
    _mTUL_DispatcherInternalSensorLockToggle->addItems({ "Item 1", "Item 2", "Item 3", "Item 4" });

    _mTUL_ExternalTurnoutFeedbackDifferent->setText(" ");

    jLabel4->setText(tr("Feedbacks different"));

    _mTUL_ActualTurnoutPrompt->setHorizontalAlignment(Qt::AlignRight);
    _mTUL_ActualTurnoutPrompt->setText(tr("Actual turnout (required):"));

    jLabel6->setHorizontalAlignment(Qt::AlignRight);
    jLabel6->setText(tr("Dispatcher sensor unlocked indicator:"));

    //_mTUL_DispatcherInternalSensorUnlockedIndicator->setModel(new DefaultComboBoxModel<>(new String[] ));
    _mTUL_DispatcherInternalSensorUnlockedIndicator->clear();

    _mTUL_NoDispatcherControlOfSwitch->setText(" ");
    _mTUL_NoDispatcherControlOfSwitch->setToolTip(tr("<html>Control locking for turnout<br>outside of any O.S.section</html>"));
//    _mTUL_NoDispatcherControlOfSwitch.addActionListener(new java.awt.event.ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
    connect(_mTUL_NoDispatcherControlOfSwitch, &JCheckBox::clicked, [=]{
            _mTUL_NoDispatcherControlOfSwitchActionPerformed(/*evt*/);
//        }
    });

    jLabel7->setHorizontalAlignment(Qt::AlignRight);
    jLabel7->setText(tr("No Dispatcher control of switch:"));

    _mTUL_GUI_IconsEnabled->setText(" ");
    _mTUL_GUI_IconsEnabled->setToolTip(tr("<html>If checked, the GUI icons will be included when writing the xml panel file.<br>If unchecked, the dispatcher will not be able to unlock the turnout.</html>"));

    _mLabelDlgTULGUIEnable->setHorizontalAlignment(Qt::AlignRight);
    _mLabelDlgTULGUIEnable->setText(tr("Enable the GUI Icons:"));

    jButton2->setText(tr("Reapply patterns - this form ONLY!"));
//    jButton2.addActionListener(new java.awt.event.ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
    connect(jButton2, &JButton::clicked, [=]{
            jButton2ActionPerformed(/*evt*/);
//        }
    });

    _mTUL_LockImplementation->addButton(jRadioButton1);
    jRadioButton1->setText(tr("Greg's"));

    jLabel1->setHorizontalAlignment(Qt::AlignRight);
    jLabel1->setText(tr("Lock implementation:"));

    _mTUL_LockImplementation->addButton(jRadioButton2);
    jRadioButton2->setText(tr("Other (unsupported)"));
    jRadioButton2->setEnabled(false);

    jLabel11->setHorizontalAlignment(Qt::AlignRight);
    jLabel11->setText(tr("LabelDlgOptional additional turnout(s):TULToOpt"));

    _mTUL_AdditionalExternalTurnout1FeedbackDifferent->setText(" ");

    _mTUL_AdditionalExternalTurnout2FeedbackDifferent->setText(" ");

    _mTUL_AdditionalExternalTurnout3FeedbackDifferent->setText(" ");

//    _mTUL_ExternalTurnout.addActionListener(new java.awt.event.ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
    connect(_mTUL_ExternalTurnout, &JComboBox::currentIndexChanged, [=]{
            _mTUL_ExternalTurnoutActionPerformed(/*evt*/);
//        }
    });

//    _mTUL_AdditionalExternalTurnout1.addActionListener(new java.awt.event.ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
    connect(_mTUL_AdditionalExternalTurnout1, &JComboBox::currentIndexChanged, [=]{
            _mTUL_AdditionalExternalTurnout1ActionPerformed(/*evt*/);
//        }
    });

//    _mTUL_AdditionalExternalTurnout2.addActionListener(new java.awt.event.ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
    connect(_mTUL_AdditionalExternalTurnout2, &JComboBox::currentIndexChanged, [=]{
            _mTUL_AdditionalExternalTurnout2ActionPerformed(/*evt*/);
//        }
    });

//    _mTUL_AdditionalExternalTurnout3.addActionListener(new java.awt.event.ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
    connect(_mTUL_AdditionalExternalTurnout3, &JComboBox::currentIndexChanged, [=]{
            _mTUL_AdditionalExternalTurnout3ActionPerformed(/*evt*/);
//        }
    });

    _mLabelDlgTULClosed->setHorizontalAlignment(Qt::AlignRight);
    _mLabelDlgTULClosed->setText(tr("When locked, switch state is \"Closed\":"));

    _mTUL_ndcos_WhenLockedSwitchStateIsClosed->setText(" ");
    _mTUL_ndcos_WhenLockedSwitchStateIsClosed->setToolTip(tr("When enabled, the turnout will be set to Closed when locking."));
#if 0
    GroupLayout layout = new GroupLayout(getContentPane());
    getContentPane()->setLayout(layout);
    layout->setHorizontalGroup(
        layout.createParallelGroup(GroupLayout.Alignment.LEADING)
        .addGroup(layout.createSequentialGroup()
            .addGap(71, 71, 71)
            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.TRAILING)
                .addComponent(->at)
                .addComponent(jLabel1)
                .addComponent(jLabel11)
                .addComponent(_mTUL_ActualTurnoutPrompt)
                .addComponent(jLabel2)
                .addComponent(jButton2)
                .addComponent(jLabel7)
                .addComponent(_mLabelDlgTULGUIEnable))
            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                .addGroup(layout.createSequentialGroup()
                    .addGroup(layout.createParallelGroup(GroupLayout.Alignment.TRAILING, false)
                        .addComponent(_mTUL_AdditionalExternalTurnout3, 0, 133, Short.MAX_VALUE)
                        .addComponent(_mTUL_AdditionalExternalTurnout2, 0, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addComponent(_mTUL_AdditionalExternalTurnout1, 0, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addComponent(_mTUL_ExternalTurnout, 0, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                    .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                    .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                        .addGroup(layout.createSequentialGroup()
                            .addComponent(_mTUL_ExternalTurnoutFeedbackDifferent)
                            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                            .addComponent(jLabel4))
                        .addComponent(_mTUL_AdditionalExternalTurnout1FeedbackDifferent)
                        .addComponent(_mTUL_AdditionalExternalTurnout2FeedbackDifferent)
                        .addComponent(_mTUL_AdditionalExternalTurnout3FeedbackDifferent)))
                .addComponent(_mTUL_DispatcherInternalSensorLockToggle, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                .addComponent(_mTUL_DispatcherInternalSensorUnlockedIndicator, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                .addGroup(layout.createSequentialGroup()
                    .addGap(57, 57, 57)
                    .addComponent(_mSaveAndClose))
                .addGroup(layout.createSequentialGroup()
                    .addComponent(_mTUL_NoDispatcherControlOfSwitch)
                    .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                    .addComponent(_mLabelDlgTULClosed)
                    .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                    .addComponent(_mTUL_ndcos_WhenLockedSwitchStateIsClosed))
                .addComponent(_mTUL_GUI_IconsEnabled)
                .addGroup(layout.createSequentialGroup()
                    .addComponent(jRadioButton1)
                    .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                    .addComponent(jRadioButton2)))
            .addContainerGap(GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
    );
    layout->setVerticalGroup(
        layout.createParallelGroup(GroupLayout.Alignment.LEADING)
        .addGroup(GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
            .addContainerGap()
            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                .addComponent(jLabel2)
                .addComponent(_mTUL_DispatcherInternalSensorLockToggle, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
            .addGap(7, 7, 7)
            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                .addComponent(_mTUL_ActualTurnoutPrompt)
                .addComponent(_mTUL_ExternalTurnoutFeedbackDifferent)
                .addComponent(jLabel4)
                .addComponent(_mTUL_ExternalTurnout, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                .addComponent(jLabel11)
                .addComponent(_mTUL_AdditionalExternalTurnout1FeedbackDifferent)
                .addComponent(_mTUL_AdditionalExternalTurnout1, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                .addComponent(_mTUL_AdditionalExternalTurnout2FeedbackDifferent)
                .addComponent(_mTUL_AdditionalExternalTurnout2, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                .addComponent(_mTUL_AdditionalExternalTurnout3FeedbackDifferent)
                .addComponent(_mTUL_AdditionalExternalTurnout3, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
            .addGap(6, 6, 6)
            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                .addComponent(->at)
                .addComponent(_mTUL_DispatcherInternalSensorUnlockedIndicator, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
            .addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                .addComponent(_mTUL_GUI_IconsEnabled)
                .addComponent(_mLabelDlgTULGUIEnable))
            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                .addComponent(jLabel7)
                .addComponent(_mTUL_NoDispatcherControlOfSwitch)
                .addComponent(_mLabelDlgTULClosed)
                .addComponent(_mTUL_ndcos_WhenLockedSwitchStateIsClosed))
            .addGap(18, 18, 18)
            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                .addComponent(jLabel1)
                .addComponent(jRadioButton1)
                .addComponent(jRadioButton2))
            .addGap(18, 18, Short.MAX_VALUE)
            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                .addComponent(_mSaveAndClose)
                .addComponent(jButton2))
            .addContainerGap(GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
    );
#else
    JPanel* contentPane = new JPanel();
    QGridLayout* grid;
    contentPane->setLayout(grid = new QGridLayout());
    setCentralWidget(contentPane);

    grid->addWidget(jLabel2, 0, 0, 1, 1, Qt::AlignRight);
    grid->addWidget(_mTUL_DispatcherInternalSensorLockToggle, 0, 1, 1, 3, Qt::AlignLeft);

    grid->addWidget(_mTUL_ActualTurnoutPrompt, 1, 0, 1,1, Qt::AlignRight);
    grid->addWidget(_mTUL_ExternalTurnout, 1, 1, 1, 2);
    grid->addWidget(_mTUL_ExternalTurnoutFeedbackDifferent, 1, 3);
    grid->addWidget(jLabel4, 1, 4, 1, 2);   // "Feedbacks different"

    grid->addWidget(jLabel11, 2, 0);
    grid->addWidget(_mTUL_AdditionalExternalTurnout1, 2, 2, 1, 2);
    grid->addWidget(_mTUL_AdditionalExternalTurnout1FeedbackDifferent, 2, 3);

    //grid->addWidget(jButton2, 3, 0, 1, 1, Qt::AlignRight);
    grid->addWidget(_mTUL_AdditionalExternalTurnout2, 3, 2, 1, 2);
    grid->addWidget(_mTUL_AdditionalExternalTurnout2FeedbackDifferent, 3, 3);

    grid->addWidget(_mTUL_AdditionalExternalTurnout3, 4, 2, 1, 2);
    grid->addWidget(_mTUL_AdditionalExternalTurnout3FeedbackDifferent, 4, 3);

    grid->addWidget(jLabel6, 5, 0, 1,1, Qt::AlignRight);
    grid->addWidget(_mTUL_DispatcherInternalSensorUnlockedIndicator, 5, 1, 1, 3);

    grid->addWidget(_mTUL_NoDispatcherControlOfSwitch, 7, 1);
    grid->addWidget(jLabel7, 7,0, 1,2, Qt::AlignRight);
    grid->addWidget(new JLabel(tr("If this is checked, then ...")), 7, 2, 1, 2);

    grid->addWidget(_mLabelDlgTULClosed, 8, 0, 1, 1, Qt::AlignRight);
    grid->addWidget(_mTUL_ndcos_WhenLockedSwitchStateIsClosed, 8, 1);
    grid->addWidget(new JLabel(tr("<- this is important to configure properly")), 8, 2, 1, 3);

    grid->addWidget(jLabel1, 9, 0, 1, 1, Qt::AlignRight);
    JPanel* panel9 = new JPanel(new QHBoxLayout());
    panel9->layout()->addWidget(jRadioButton1);
    panel9->layout()->addWidget(jRadioButton2);
    grid->addWidget(panel9, 9, 2, 1, 3);

    grid->addWidget(_mSaveAndClose, 11, 2, 1, 2, Qt::AlignHCenter);
    grid->addWidget(jButton2, 12, 1, 1, 2);

#endif
    pack();
}// </editor-fold>

/*private*/ void FrmTUL::_mSaveAndCloseActionPerformed(/*java.awt.event.ActionEvent evt*/) {
    if (CommonSubs::missingFieldsErrorDialogDisplayed(this, formFieldsValid(), false)) {
        return; // Do not allow exit or transfer of data.
    }

    _mCodeButtonHandlerData->_mTUL_DispatcherInternalSensorLockToggle = CommonSubs::getNBHSensor( _mTUL_DispatcherInternalSensorLockToggle->getSelectedItem(), false);
    _mCodeButtonHandlerData->_mTUL_DispatcherInternalSensorUnlockedIndicator = CommonSubs::getNBHSensor( _mTUL_DispatcherInternalSensorUnlockedIndicator->getSelectedItem(), false);

    // External turnout
    NBHTurnout* newTurnout = CommonSubs::getNBHTurnout(_mCurrentExternalTurnout, _mTUL_ExternalTurnoutFeedbackDifferent->isChecked());
    _mCodeButtonHandlerData->_mTUL_ExternalTurnout = newTurnout;
    _mCodeButtonHandlerData->_mTUL_ExternalTurnoutFeedbackDifferent = _mTUL_ExternalTurnoutFeedbackDifferent->isChecked();

    // Additional turnout 1
    newTurnout = CommonSubs::getNBHTurnout(_mCurrentAdditionalTurnout1, _mTUL_AdditionalExternalTurnout1FeedbackDifferent->isChecked());
    _mCodeButtonHandlerData->_mTUL_AdditionalExternalTurnout1 = newTurnout;
    _mCodeButtonHandlerData->_mTUL_AdditionalExternalTurnout1FeedbackDifferent = _mTUL_AdditionalExternalTurnout1FeedbackDifferent->isChecked();

    // Additional turnout 2
    newTurnout = CommonSubs::getNBHTurnout(_mCurrentAdditionalTurnout2, _mTUL_AdditionalExternalTurnout2FeedbackDifferent->isChecked());
    _mCodeButtonHandlerData->_mTUL_AdditionalExternalTurnout2 = newTurnout;
    _mCodeButtonHandlerData->_mTUL_AdditionalExternalTurnout2FeedbackDifferent = _mTUL_AdditionalExternalTurnout2FeedbackDifferent->isChecked();

    // Additional turnout 3
    newTurnout = CommonSubs::getNBHTurnout(_mCurrentAdditionalTurnout3, _mTUL_AdditionalExternalTurnout3FeedbackDifferent->isChecked());
    _mCodeButtonHandlerData->_mTUL_AdditionalExternalTurnout3 = newTurnout;
    _mCodeButtonHandlerData->_mTUL_AdditionalExternalTurnout3FeedbackDifferent = _mTUL_AdditionalExternalTurnout3FeedbackDifferent->isChecked();

    // Other fields
    _mCodeButtonHandlerData->_mTUL_GUI_IconsEnabled = _mTUL_GUI_IconsEnabled->isChecked();
    _mCodeButtonHandlerData->_mTUL_NoDispatcherControlOfSwitch = _mTUL_NoDispatcherControlOfSwitch->isChecked();
    _mCodeButtonHandlerData->_mTUL_ndcos_WhenLockedSwitchStateIsClosed = _mTUL_ndcos_WhenLockedSwitchStateIsClosed->isChecked();
    _mCodeButtonHandlerData->_mTUL_LockImplementation = CodeButtonHandlerData::LOCK_IMPLEMENTATION::getLockImplementation(_mTUL_LockImplementation);

    _mClosedNormally = true;
    _mAwtWindowProperties->saveWindowState(this, FORM_PROPERTIES);
    dispose();
}

/*private*/ void FrmTUL::formWindowClosing(QCloseEvent* evt) {
    _mAwtWindowProperties->saveWindowState(this, FORM_PROPERTIES);
    if (CommonSubs::allowClose(this, dataChanged())) dispose();
}

/*private*/ void FrmTUL::jButton2ActionPerformed(/*java.awt.event.ActionEvent evt*/) {
    CodeButtonHandlerData* temp = _mCodeButtonHandlerData;
    temp = CodeButtonHandlerDataRoutines::uECBHDWSD_TUL(_mProgramProperties, temp);
    CommonSubs::populateJComboBoxWithBeans(_mTUL_DispatcherInternalSensorLockToggle, "Sensor", temp->_mTUL_DispatcherInternalSensorLockToggle->getHandleName(), false);   // NOI18N
    CommonSubs::populateJComboBoxWithBeans(_mTUL_DispatcherInternalSensorUnlockedIndicator, "Sensor", temp->_mTUL_DispatcherInternalSensorUnlockedIndicator->getHandleName(), false);   // NOI18N
}

/*private*/ void FrmTUL::_mTUL_ExternalTurnoutActionPerformed(/*java.awt.event.ActionEvent evt*/) {
    _mCurrentExternalTurnout =  _mTUL_ExternalTurnout->getSelectedItem();
    initializeAll4LockedTurnoutJComboBoxesAndSupportingData();
}

/*private*/ void FrmTUL::_mTUL_AdditionalExternalTurnout1ActionPerformed(/*java.awt.event.ActionEvent evt*/) {
    _mCurrentAdditionalTurnout1 =  _mTUL_AdditionalExternalTurnout1->getSelectedItem();
    initializeAll4LockedTurnoutJComboBoxesAndSupportingData();
}

/*private*/ void FrmTUL::_mTUL_AdditionalExternalTurnout2ActionPerformed(/*java.awt.event.ActionEvent evt*/) {
    _mCurrentAdditionalTurnout2 =  _mTUL_AdditionalExternalTurnout2->getSelectedItem();
    initializeAll4LockedTurnoutJComboBoxesAndSupportingData();
}

/*private*/ void FrmTUL::_mTUL_AdditionalExternalTurnout3ActionPerformed(/*java.awt.event.ActionEvent evt*/) {
    _mCurrentAdditionalTurnout3 =  _mTUL_AdditionalExternalTurnout3->getSelectedItem();
    initializeAll4LockedTurnoutJComboBoxesAndSupportingData();
}

/*private*/ void FrmTUL::_mTUL_NoDispatcherControlOfSwitchActionPerformed(/*java.awt.event.ActionEvent evt*/) {
    // enable/disable _mTUL_ndcos_WhenLockedSwitchStateIsClosed based on NDCOS selection
    bool ndcpos = _mTUL_NoDispatcherControlOfSwitch->isChecked();
    _mTUL_ndcos_WhenLockedSwitchStateIsClosed->setEnabled(ndcpos);
    _mLabelDlgTULClosed->setEnabled(ndcpos);
}

/*private*/ void FrmTUL::initializeAll4LockedTurnoutJComboBoxesAndSupportingData() {
    if (_mIgnoreActionEvent) return;    // Process ONLY when the user selectes an item in the combo box (even if the same one), otherwise forget it.

    // Turnouts used in other columns
    QSet<QString> hashSetOfExistingLockedTurnoutsExcludingThisOne = _mCTCSerialData->getHashSetOfAllLockedTurnoutsExcludingPassedOne(_mCodeButtonHandlerData); // Once initialized, fixed!

    // All turnouts minus those used in other columns
//    InstanceManager::getDefault("TurnoutManager").getNamedBeanSet().forEach((t) -> { _mStartingHashSetOfTurnouts.add(t.getDisplayName()); });
    foreach(NamedBean* nb, ((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->getNamedBeanSet())
    _mStartingHashSetOfTurnouts.insert(((Turnout*)nb)->getDisplayName());
     //_mStartingHashSetOfTurnouts.remove(hashSetOfExistingLockedTurnoutsExcludingThisOne);
    foreach(QString s, _mStartingHashSetOfTurnouts){
     if(!hashSetOfExistingLockedTurnoutsExcludingThisOne.contains(s))
      _mStartingHashSetOfTurnouts.remove(s);
    }

    // Retain the selected turnout.  The list can changed based on selections and which combo box.
    _mArrayListOfThisRecordsUsedLockedTurnouts.clear();
    _mArrayListOfThisRecordsUsedLockedTurnouts.append(_mCurrentExternalTurnout);
    _mArrayListOfThisRecordsUsedLockedTurnouts.append(_mCurrentAdditionalTurnout1);
    _mArrayListOfThisRecordsUsedLockedTurnouts.append(_mCurrentAdditionalTurnout2);
    _mArrayListOfThisRecordsUsedLockedTurnouts.append(_mCurrentAdditionalTurnout3);

    // Update the combo boxes
    update1LockedTurnoutJComboBox(_mTUL_ExternalTurnout, 0, _mCurrentExternalTurnout);
    update1LockedTurnoutJComboBox(_mTUL_AdditionalExternalTurnout1, 1, _mCurrentAdditionalTurnout1);
    update1LockedTurnoutJComboBox(_mTUL_AdditionalExternalTurnout2, 2, _mCurrentAdditionalTurnout2);
    update1LockedTurnoutJComboBox(_mTUL_AdditionalExternalTurnout3, 3, _mCurrentAdditionalTurnout3);
}

/*private*/ void FrmTUL::update1LockedTurnoutJComboBox(JComboBox/*<String>*/*jComboBox, int index, QString currentSelection) {
    QSet<QString> ultimateHashSet = QSet<QString>(_mStartingHashSetOfTurnouts);   // Make a deep copy.
    //ultimateHashSet.removeAll(returnHashSetSubset(index));
#if 0
    foreach(QString s, ultimateHashSet){
     if(s != returnHashSetSubset.val(index))
      ultimateHashSet.remove(s);
    }
#endif
    populateJComboBox(jComboBox, ultimateHashSet, currentSelection);
}

/**
 * Just returns a sub-set of _mArrayListOfThisRecordsUsedLockedTurnouts excluding
 * any blank entries, and the one index passed.
 *
 * @param indexToLeaveOff The JComboBox "field" we will be editing: 0 = _mTUL_ExternalTurnout, 1 = _mTUL_AdditionalExternalTurnout1, 2 = _mTUL_AdditionalExternalTurnout2, 3 = _mTUL_AdditionalExternalTurnout3
 * @return The requested subset of _mArrayListOfThisRecordsUsedLockedTurnouts
 */
/*private*/ QSet<QString> FrmTUL::returnHashSetSubset(int indexToLeaveOff) {
    QSet<QString> returnValue = QSet<QString>();
    for (int index = 0; index < _mArrayListOfThisRecordsUsedLockedTurnouts.size(); index++) {

        QString recordUsed = _mArrayListOfThisRecordsUsedLockedTurnouts.at(index);
        bool recordValid = (recordUsed.isNull() || recordUsed.isEmpty()) ? false : true;
        if (index != indexToLeaveOff && recordValid) {
            returnValue.insert(recordUsed);
        }
    }
    return returnValue;
}

/**
 *
 * This is a DIRECT plagiarization of Dave Sands CommonSubs::populateJComboBoxWithBeans, repurposed to support
 * what is needed specifically by Turnout Locking.
 * It does not have the flexibility of the original routine, since thats not needed.
 * (see "_mIgnoreActionEvent", since I don't know of another way to do it).
 *
 * Populate a combo box with bean names using getDisplayName().
 * <p>
 * If a panel xml file has not been loaded, the combo box will behave as a
 * text field (editable), otherwise it will behave as standard combo box (not editable).
 * @param jComboBox The string based combo box to be populated.
 * @param populateWith A hash set that needs to be sorted first, to populate the drop down list with.
 * @param currentSelection The current item to be selected, none if null.
 */
/*public*/ void FrmTUL::populateJComboBox(JComboBox/*<String>*/*jComboBox, QSet<QString> populateWith, QString currentSelection) {
    _mIgnoreActionEvent = true;
    jComboBox->clear();
    jComboBox->setEditable(false);
    QList<QString> list = QList<QString>(populateWith.toList());
//    list.sort(new AlphanumComparator());
    //list.forEach((item) ->
    foreach(QString item, list)
    {
        jComboBox->addItem(item);
    }//);
//    JComboBoxUtil::setupComboBoxMaxRows(jComboBox);
//    jComboBox->setCheckedItem(currentSelection);
    jComboBox->insertItem(0,"");
//    if (currentSelection == nullptr || currentSelection.isEmpty()) {
//        jComboBox->setCheckedIndex(0);
//    }
    _mIgnoreActionEvent = false;
}
