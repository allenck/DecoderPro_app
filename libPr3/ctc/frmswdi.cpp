#include "frmswdi.h"
#include "jcombobox.h"
#include "jcheckbox.h"
#include "commonsubs.h"
#include "awtwindowproperties.h"
#include "jformattedtextfield.h"
#include "swingconstants.h"
#include "checkjmriobject.h"
#include "vptr.h"


FrmSWDI::FrmSWDI(QWidget *parent)
{

}
/**
 *
 * @author Gregory J. Bedlek Copyright (C) 2018, 2019
 */
// /*public*/ class FrmSWDI extends JFrame {

    /*private*/ /*static*/ /*final*/ QString FrmSWDI::FORM_PROPERTIES = "DlgSWDI";    // NOI18N
    /*private*/ /*static*/ /*final*/ QString FrmSWDI::PREFIX = "_mSWDI_";             // NOI18N


    /*private*/ void FrmSWDI::initOrig() {
        _mSWDI_ExternalTurnoutOrig = _mCodeButtonHandlerData->_mSWDI_ExternalTurnout->getHandleName();
        _mSWDI_CodingTimeInMillisecondsOrig = _mCodeButtonHandlerData->_mSWDI_CodingTimeInMilliseconds;
        _mSWDI_FeedbackDifferentOrig = _mCodeButtonHandlerData->_mSWDI_FeedbackDifferent;
        _mSWDI_GUITurnoutTypeOrig = _mCodeButtonHandlerData->_mSWDI_GUITurnoutType;
        _mSWDI_GUITurnoutLeftHandOrig = _mCodeButtonHandlerData->_mSWDI_GUITurnoutLeftHand;
        _mSWDI_GUICrossoverLeftHandOrig = _mCodeButtonHandlerData->_mSWDI_GUICrossoverLeftHand;
    }
    /*private*/ bool FrmSWDI::dataChanged() {
        if (_mSWDI_ExternalTurnoutOrig != (_mSWDI_ExternalTurnout->getSelectedItem())) return true;
        if (CommonSubs::getIntFromJTextFieldNoThrow(_mSWDI_CodingTimeInMilliseconds) != _mSWDI_CodingTimeInMillisecondsOrig) return true;
        if (_mSWDI_FeedbackDifferentOrig != _mSWDI_FeedbackDifferent->isChecked()) return true;
        if (_mSWDI_GUITurnoutTypeOrig != CodeButtonHandlerData::TURNOUT_TYPE::getTurnoutType(_mSWDI_GUITurnoutType)) return true;
        if (_mSWDI_GUITurnoutLeftHandOrig != _mSWDI_GUITurnoutLeftHand->isChecked()) return true;
        if (_mSWDI_GUICrossoverLeftHandOrig != _mSWDI_GUICrossoverLeftHand->isChecked()) return true;
        return false;
    }

    /*public*/ FrmSWDI::FrmSWDI( AwtWindowProperties* awtWindowProperties, CodeButtonHandlerData* codeButtonHandlerData,
                    ProgramProperties* programProperties, CheckJMRIObject* checkJMRIObject, QWidget* parent) : JFrame(parent){
        //super();
        initComponents();
        CommonSubs::addHelpMenu(this, "package.jmri.jmrit.ctc.CTC_frmSWDI", true);  // NOI18N
        _mAwtWindowProperties = awtWindowProperties;
        _mCodeButtonHandlerData = codeButtonHandlerData;
        _mProgramProperties = programProperties;
        _mCheckJMRIObject = checkJMRIObject;
        CommonSubs::numberButtonGroup(_mSWDI_GUITurnoutType);
        CommonSubs::setButtonSelected(_mSWDI_GUITurnoutType, _mCodeButtonHandlerData->_mSWDI_GUITurnoutType.getInt());
        CommonSubs::setMillisecondsEdit(_mSWDI_CodingTimeInMilliseconds);
        CommonSubs::populateJComboBoxWithBeans(_mSWDI_NormalInternalSensor, "Sensor", _mCodeButtonHandlerData->_mSWDI_NormalInternalSensor->getHandleName(), false);   // NOI18N
        CommonSubs::populateJComboBoxWithBeans(_mSWDI_ReversedInternalSensor, "Sensor", _mCodeButtonHandlerData->_mSWDI_ReversedInternalSensor->getHandleName(), false);   // NOI18N
        CommonSubs::populateJComboBoxWithBeans(_mSWDI_ExternalTurnout, "Turnout", _mCodeButtonHandlerData->_mSWDI_ExternalTurnout->getHandleName(), true);
        _mSWDI_CodingTimeInMilliseconds->setText(QString::number(_mCodeButtonHandlerData->_mSWDI_CodingTimeInMilliseconds));
        _mSWDI_FeedbackDifferent->setChecked(_mCodeButtonHandlerData->_mSWDI_FeedbackDifferent);
        _mSWDI_GUITurnoutLeftHand->setChecked(_mCodeButtonHandlerData->_mSWDI_GUITurnoutLeftHand);
        _mSWDI_GUICrossoverLeftHand->setChecked(_mCodeButtonHandlerData->_mSWDI_GUICrossoverLeftHand);
        initOrig();
        _mAwtWindowProperties->setWindowState(this, FORM_PROPERTIES);
//        this.getRootPane()->setDefaultButton(_mSaveAndClose);
    }

    /*public*/ /*static*/ bool FrmSWDI::dialogCodeButtonHandlerDataValid(CheckJMRIObject* checkJMRIObject, CodeButtonHandlerData* codeButtonHandlerData) {
        if (!codeButtonHandlerData->_mSWDI_Enabled) return true; // Not enabled, can be no error!
//  Checks:
        if (ProjectsCommonSubs::isNullOrEmptyString(codeButtonHandlerData->_mSWDI_NormalInternalSensor->getHandleName())) return false;
        if (ProjectsCommonSubs::isNullOrEmptyString(codeButtonHandlerData->_mSWDI_ReversedInternalSensor->getHandleName())) return false;
        if (ProjectsCommonSubs::isNullOrEmptyString(codeButtonHandlerData->_mSWDI_ExternalTurnout->getHandleName())) return false;
        return checkJMRIObject->validClassWithPrefix(PREFIX, VPtr<CodeButtonHandlerData>::asQVariant( codeButtonHandlerData));
    }

//  Validate all internal fields as much as possible:
    /*private*/ QList<QString> FrmSWDI::formFieldsValid() {
        QList<QString> errors = QList<QString>();
//  Checks:
        CommonSubs::checkJComboBoxNotEmpty(_mSWDI_ExternalTurnout, _mSWDI_ActualTurnoutPrompt, errors);
        _mCheckJMRIObject->analyzeForm(PREFIX, this, errors);
        return errors;
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    // <editor-fold defaultstate="collapsed" desc="Generated Code">
    /*private*/ void FrmSWDI::initComponents() {

        _mSWDI_GUITurnoutType = new QButtonGroup(this);
        _mSaveAndClose = new JButton();
        _mSWDI_NormalInternalSensorPrompt = new JLabel();
        _mSWDI_NormalInternalSensor = new JComboBox();
        _mSWDI_ReversedInternalSensorPrompt = new JLabel();
        _mSWDI_ReversedInternalSensor = new JComboBox();
        _mSWDI_ActualTurnoutPrompt = new JLabel();
        _mSWDI_ExternalTurnout = new JComboBox();
        jLabel19 = new JLabel();
        _mSWDI_CodingTimeInMilliseconds = new JFormattedTextField();
        _mSWDI_FeedbackDifferent = new JCheckBox();
        jLabel2 = new JLabel();
        jButton2 = new JButton();
        jLabel3 = new JLabel();
        _mSWDI_GUITurnoutLeftHand = new JCheckBox();
        _mSWDI_GUICrossoverLeftHand = new JCheckBox();
        _mTurnout = new QRadioButton();
        _mCrossover = new QRadioButton();
        _mDoubleCrossover = new QRadioButton();

        setDefaultCloseOperation(JFrame::DO_NOTHING_ON_CLOSE);
        setTitle(tr("Edit switch direction indicators"));
//        addWindowListener(new java.awt.event.WindowAdapter() {
//            @Override
//            /*public*/ void windowClosing(java.awt.event.WindowEvent evt) {
//                formWindowClosing(evt);
//            }
//        });
        addWindowListener(new FrmSWDI_windowListener(this));
        _mSaveAndClose->setText(tr("Save and close"));
//        _mSaveAndClose.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
        connect(_mSaveAndClose, &JButton::clicked, [=]{
                _mSaveAndCloseActionPerformed(/*evt*/);
//            }
        });

        _mSWDI_NormalInternalSensorPrompt->setHorizontalAlignment(SwingConstants::RIGHT);
        _mSWDI_NormalInternalSensorPrompt->setText(tr("Normal indicator sensor:"));

        //_mSWDI_NormalInternalSensor->setModel(new DefaultComboBoxModel(new String[] { "Item 1", "Item 2", "Item 3", "Item 4" }));
        _mSWDI_NormalInternalSensor->addItems({ "Item 1", "Item 2", "Item 3", "Item 4" });
        _mSWDI_ReversedInternalSensorPrompt->setHorizontalAlignment(SwingConstants::RIGHT);
        _mSWDI_ReversedInternalSensorPrompt->setText(tr("Reverse indicator sensor:"));

        //_mSWDI_ReversedInternalSensor->setModel(new DefaultComboBoxModel<>(new String[] { "Item 1", "Item 2", "Item 3", "Item 4" }));
        _mSWDI_ReversedInternalSensor->addItems({ "Item 1", "Item 2", "Item 3", "Item 4" });

        _mSWDI_ActualTurnoutPrompt->setText(tr("Actual turnout:"));

        //_mSWDI_ExternalTurnout->setModel(new DefaultComboBoxModel<>(new String[] { "Item 1", "Item 2", "Item 3", "Item 4" }));
        _mSWDI_ExternalTurnout->addItems({ "Item 1", "Item 2", "Item 3", "Item 4" });

        jLabel19->setText(tr("Coding and response time milliseconds:"));

//        _mSWDI_CodingTimeInMilliseconds->setFormatterFactory(new DefaultFormatterFactory(new text.NumberFormatter(new java.text.DecimalFormat("#0"))));

        _mSWDI_FeedbackDifferent->setText(" ");

        jLabel2->setText(tr("Feedback different:"));

        jButton2->setText(tr("Reapply patterns - this form ONLY!"));
//        jButton2.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
        connect(jButton2, &JButton::clicked, [=]{
                jButton2ActionPerformed(/*evt*/);
//            }
        });

        jLabel3->setText(tr("Optional GUI parameters:"));

        _mSWDI_GUITurnoutLeftHand->setText(tr("Left hand turnout"));

        _mSWDI_GUICrossoverLeftHand->setText(tr("Other turnout also left handed"));

        _mSWDI_GUITurnoutType->addButton(_mTurnout);
        _mTurnout->setText(tr("Turnout"));
//        _mTurnout.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
        connect(_mTurnout, &QRadioButton::clicked, [=]{
                _mTurnoutActionPerformed(/*evt*/);
//            }
        });

        _mSWDI_GUITurnoutType->addButton(_mCrossover);
        _mCrossover->setText(tr("Crossover"));
//        _mCrossover.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
        connect(_mCrossover, &QRadioButton::clicked, [=]{
                _mCrossoverActionPerformed(/*evt*/);
//            }
        });

        _mSWDI_GUITurnoutType->addButton(_mDoubleCrossover);
        _mDoubleCrossover->setText(tr("Double crossover"));
//        _mDoubleCrossover.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
        connect(_mDoubleCrossover, &QRadioButton::clicked, [=] {
                _mDoubleCrossoverActionPerformed(/*evt*/);
//            }
        });
#if 0
        GroupLayout layout = new GroupLayout(getContentPane());
        getContentPane()->setLayout(layout);
        layout->setHorizontalGroup(
            layout.createParallelGroup(GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(GroupLayout.Alignment.TRAILING)
                            .addComponent(_mSWDI_ActualTurnoutPrompt)
                            .addComponent(jLabel19)
                            .addComponent(_mSWDI_ReversedInternalSensorPrompt, GroupLayout.PREFERRED_SIZE, 155, GroupLayout.PREFERRED_SIZE)
                            .addComponent(_mSWDI_NormalInternalSensorPrompt, GroupLayout.PREFERRED_SIZE, 155, GroupLayout.PREFERRED_SIZE)
                            .addComponent(jLabel2))
                        .addGap(12, 12, 12)
                        .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING, false)
                            .addComponent(_mSWDI_ReversedInternalSensor, 0, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addComponent(_mSWDI_NormalInternalSensor, 0, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addComponent(_mSWDI_CodingTimeInMilliseconds, GroupLayout.PREFERRED_SIZE, 63, GroupLayout.PREFERRED_SIZE)
                            .addComponent(_mSWDI_FeedbackDifferent)
                            .addComponent(_mSWDI_ExternalTurnout, 0, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)))
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(jLabel3)
                        .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                            .addComponent(jButton2)
                            .addGroup(layout.createSequentialGroup()
                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                                    .addComponent(_mCrossover)
                                    .addComponent(_mTurnout))
                                .addGap(41, 41, 41)
                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                                    .addComponent(_mSWDI_GUITurnoutLeftHand)
                                    .addComponent(_mSWDI_GUICrossoverLeftHand)))
                            .addComponent(_mDoubleCrossover)
                            .addGroup(layout.createSequentialGroup()
                                .addGap(43, 43, 43)
                                .addComponent(_mSaveAndClose)))))
                .addContainerGap(GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
        layout->setVerticalGroup(
            layout.createParallelGroup(GroupLayout.Alignment.LEADING)
            .addGroup(GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                    .addComponent(_mSWDI_NormalInternalSensorPrompt, GroupLayout.PREFERRED_SIZE, 12, GroupLayout.PREFERRED_SIZE)
                    .addComponent(_mSWDI_NormalInternalSensor, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                    .addComponent(_mSWDI_ReversedInternalSensorPrompt)
                    .addComponent(_mSWDI_ReversedInternalSensor, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                    .addComponent(_mSWDI_ActualTurnoutPrompt)
                    .addComponent(_mSWDI_ExternalTurnout, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                    .addComponent(_mSWDI_CodingTimeInMilliseconds, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                    .addComponent(jLabel19))
                .addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED)
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                    .addComponent(jLabel2)
                    .addComponent(_mSWDI_FeedbackDifferent))
                .addGap(22, 22, 22)
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                    .addComponent(jLabel3)
                    .addComponent(_mSWDI_GUITurnoutLeftHand)
                    .addComponent(_mTurnout))
                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                    .addComponent(_mCrossover)
                    .addComponent(_mSWDI_GUICrossoverLeftHand))
                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(_mDoubleCrossover)
                .addGap(18, 18, 18)
                .addComponent(_mSaveAndClose)
                .addGap(38, 38, 38)
                .addComponent(jButton2)
                .addContainerGap(GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
#else
        JPanel* contentPane = new JPanel();
        contentPane->setLayout(new QVBoxLayout());
        setCentralWidget(contentPane);

        JPanel* panel1 = new JPanel(new QHBoxLayout());
        ((QHBoxLayout*)panel1->layout())->addWidget(_mSWDI_NormalInternalSensorPrompt, 0, Qt::AlignRight);
        panel1->layout()->addWidget(_mSWDI_NormalInternalSensor);
        contentPane->layout()->addWidget(panel1);

        JPanel* panel2 = new JPanel(new QHBoxLayout());
        ((QHBoxLayout*)panel2->layout())->addWidget(_mSWDI_ReversedInternalSensorPrompt, 0, Qt::AlignRight);
        panel2->layout()->addWidget(_mSWDI_ReversedInternalSensor);
        contentPane->layout()->addWidget(panel2);

        JPanel* panel3 = new JPanel(new QHBoxLayout());
        ((QHBoxLayout*)panel3->layout())->addWidget(_mSWDI_ActualTurnoutPrompt, 0, Qt::AlignRight);
        panel3->layout()->addWidget(_mSWDI_ExternalTurnout);
        contentPane->layout()->addWidget(panel3);

        JPanel* panel4 = new JPanel(new QHBoxLayout());
        ((QHBoxLayout*)panel4->layout())->addWidget(jLabel19, 0, Qt::AlignRight);
        panel4->layout()->addWidget(_mSWDI_CodingTimeInMilliseconds);
        contentPane->layout()->addWidget(panel4);

        JPanel* panel5 = new JPanel(new QHBoxLayout());
        ((QHBoxLayout*)panel5->layout())->addWidget(jLabel2, 0, Qt::AlignRight);
        panel5->layout()->addWidget(_mSWDI_FeedbackDifferent);
        contentPane->layout()->addWidget(panel5);

        JPanel* panel6 = new JPanel(new QHBoxLayout());
        ((QHBoxLayout*)panel6->layout())->addWidget(jLabel3, 0, Qt::AlignRight);
        panel6->layout()->addWidget(_mTurnout);
        panel6->layout()->addWidget(_mSWDI_GUITurnoutLeftHand);
        contentPane->layout()->addWidget(panel6);

        JPanel* panel7 = new JPanel(new QHBoxLayout());
        ((QHBoxLayout*)panel7->layout())->addWidget(new JLabel(" "), 0, Qt::AlignRight);
        panel7->layout()->addWidget(_mCrossover);
        panel7->layout()->addWidget(_mSWDI_GUICrossoverLeftHand);
        contentPane->layout()->addWidget(panel7);

        JPanel* panel8 = new JPanel(new QHBoxLayout());
        ((QHBoxLayout*)panel8->layout())->addWidget(new JLabel(" "), 0, Qt::AlignRight);
        panel8->layout()->addWidget(_mDoubleCrossover);
        panel8->layout()->addWidget(new JLabel(" "));
        contentPane->layout()->addWidget(panel8);

        JPanel* panel9 = new JPanel(new FlowLayout());
        panel9->layout()->addWidget(_mSaveAndClose);
        panel9->layout()->addWidget(jButton2);
        contentPane->layout()->addWidget(panel9);

#endif
        pack();
    }// </editor-fold>

    /*private*/ void FrmSWDI::_mSaveAndCloseActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        if (CommonSubs::missingFieldsErrorDialogDisplayed(this, formFieldsValid(), false)) {
            return; // Do not allow exit or transfer of data.
        }

        _mCodeButtonHandlerData->_mSWDI_NormalInternalSensor = CommonSubs::getNBHSensor( _mSWDI_NormalInternalSensor->getSelectedItem(), false);
        _mCodeButtonHandlerData->_mSWDI_ReversedInternalSensor = CommonSubs::getNBHSensor( _mSWDI_ReversedInternalSensor->getSelectedItem(), false);

        NBHTurnout* newTurnout = CommonSubs::getNBHTurnout( _mSWDI_ExternalTurnout->getSelectedItem(), _mSWDI_FeedbackDifferent->isChecked());
        _mCodeButtonHandlerData->_mSWDI_ExternalTurnout = newTurnout;

        _mCodeButtonHandlerData->_mSWDI_CodingTimeInMilliseconds = CommonSubs::getIntFromJTextFieldNoThrow(_mSWDI_CodingTimeInMilliseconds);
        _mCodeButtonHandlerData->_mSWDI_FeedbackDifferent = _mSWDI_FeedbackDifferent->isChecked();
        _mCodeButtonHandlerData->_mSWDI_GUITurnoutType = CodeButtonHandlerData::TURNOUT_TYPE::getTurnoutType(_mSWDI_GUITurnoutType);
        _mCodeButtonHandlerData->_mSWDI_GUITurnoutLeftHand = _mSWDI_GUITurnoutLeftHand->isChecked();
        _mCodeButtonHandlerData->_mSWDI_GUICrossoverLeftHand = _mSWDI_GUICrossoverLeftHand->isChecked();
        _mClosedNormally = true;
        _mAwtWindowProperties->saveWindowState(this, FORM_PROPERTIES);
        dispose();
    }

    /*private*/ void FrmSWDI::formWindowClosing(QCloseEvent* evt) {
        _mAwtWindowProperties->saveWindowState(this, FORM_PROPERTIES);
        if (CommonSubs::allowClose(this, dataChanged())) dispose();
    }

    /*private*/ void FrmSWDI::jButton2ActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        CodeButtonHandlerData* temp = _mCodeButtonHandlerData;
        temp = CodeButtonHandlerDataRoutines::uECBHDWSD_SWDI(_mProgramProperties, temp);
        CommonSubs::populateJComboBoxWithBeans(_mSWDI_NormalInternalSensor, "Sensor", temp->_mSWDI_NormalInternalSensor->getHandleName(), false);   // NOI18N
        CommonSubs::populateJComboBoxWithBeans(_mSWDI_ReversedInternalSensor, "Sensor", temp->_mSWDI_ReversedInternalSensor->getHandleName(), false);   // NOI18N
    }

    /*private*/ void FrmSWDI::_mTurnoutActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        _mSWDI_GUITurnoutLeftHand->setEnabled(true);
        _mSWDI_GUICrossoverLeftHand->setEnabled(false);
    }

    /*private*/ void FrmSWDI::_mCrossoverActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        _mSWDI_GUITurnoutLeftHand->setEnabled(true);
        _mSWDI_GUICrossoverLeftHand->setEnabled(true);
    }

    /*private*/ void FrmSWDI::_mDoubleCrossoverActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        _mSWDI_GUITurnoutLeftHand->setEnabled(false);
        _mSWDI_GUICrossoverLeftHand->setEnabled(false);
    }


