#include "frmsidi.h"
#include "commonsubs.h"
#include "tablecolumnmodel.h"
#include "codebuttonhandlerdataroutines.h"
#include "vptr.h"

/**
 *
 * @author Gregory J. Bedlek Copyright (C) 2018, 2019
 */
///*public*/ class FrmSIDI extends JFrame {

/**
 * Creates new form dlgSIDI
 */
/*private*/ /*static*/ /*final*/ QString FrmSIDI::FORM_PROPERTIES = "DlgSIDI";    // NOI18N
/*private*/ /*static*/ /*final*/ QString FrmSIDI::PREFIX = "_mSIDI_";             // NOI18N


/*private*/ void FrmSIDI::initOrig(QList<QString> signalArrayList1, QList<QString> signalArrayList2) {
    _mSIDI_CodingAndResponseTimeOrig = _mCodeButtonHandlerData->_mSIDI_CodingTimeInMilliseconds;
    _mSIDI_TimeLockingIntervalOrig = _mCodeButtonHandlerData->_mSIDI_TimeLockingTimeInMilliseconds;
    _mSIDI_TrafficDirectionOrig = _mCodeButtonHandlerData->_mSIDI_TrafficDirection;
    for (int index = 0; index < signalArrayList1.size(); index++) {
        _mLeftRightTrafficSignalsArrayListOrig.append(signalArrayList1.at(index));
    }
    for (int index = 0; index < signalArrayList2.size(); index++) {
        _mRightLeftTrafficSignalsArrayListOrig.append(signalArrayList2.at(index));
    }
}

/*private*/ bool FrmSIDI::dataChanged() {
    if (CommonSubs::getIntFromJTextFieldNoThrow(_mSIDI_CodingAndResponseTime) != _mSIDI_CodingAndResponseTimeOrig) return true;
    if (CommonSubs::getIntFromJTextFieldNoThrow(_mSIDI_TimeLockingInterval) != _mSIDI_TimeLockingIntervalOrig) return true;
    if (_mSIDI_TrafficDirectionOrig != _mSIDI_TrafficDirectionTemp) return true;

    int tableLength = CommonSubs::compactDefaultTableModel(_mSIDI_TableOfLeftToRightTrafficExternalSignalNamesDefaultTableModel);
    if (tableLength != _mLeftRightTrafficSignalsArrayListOrig.size()) return true;
    for (int index = 0; index < tableLength; index++) {
        if (_mLeftRightTrafficSignalsArrayListOrig.at(index) != (_mSIDI_TableOfLeftToRightTrafficExternalSignalNamesDefaultTableModel->getValueAt(index, 0))) return true;
    }
    tableLength = CommonSubs::compactDefaultTableModel(_mSIDI_TableOfRightToLeftTrafficExternalSignalNamesDefaultTableModel);
    if (tableLength != _mRightLeftTrafficSignalsArrayListOrig.size()) return true;
    for (int index = 0; index < tableLength; index++) {
        if (_mRightLeftTrafficSignalsArrayListOrig.at(index) !=(_mSIDI_TableOfRightToLeftTrafficExternalSignalNamesDefaultTableModel->getValueAt(index, 0))) return true;
    }
    return false;
}


/*public*/ FrmSIDI::FrmSIDI( AwtWindowProperties* awtWindowProperties, CodeButtonHandlerData* codeButtonHandlerData,
                ProgramProperties* programProperties, CheckJMRIObject* checkJMRIObject,
                bool signalHeadSelected, QWidget* parent) : JFrame(parent){
    //super();
    initComponents();
    CommonSubs::addHelpMenu(this, "package.jmri.jmrit.ctc.CTC_frmSIDI", true);  // NOI18N
    _mAwtWindowProperties = awtWindowProperties;
    _mCodeButtonHandlerData = codeButtonHandlerData;
    _mProgramProperties = programProperties;
    _mCheckJMRIObject = checkJMRIObject;
    _mSignalHeadSelected = signalHeadSelected;
    CommonSubs::setMillisecondsEdit(_mSIDI_CodingAndResponseTime);
    CommonSubs::setMillisecondsEdit(_mSIDI_TimeLockingInterval);
    CommonSubs::populateJComboBoxWithBeans(_mSIDI_LeftInternalSensor, "Sensor", _mCodeButtonHandlerData->_mSIDI_LeftInternalSensor->getHandleName(), false);   // NOI18N
    CommonSubs::populateJComboBoxWithBeans(_mSIDI_NormalInternalSensor, "Sensor", _mCodeButtonHandlerData->_mSIDI_NormalInternalSensor->getHandleName(), false);   // NOI18N
    CommonSubs::populateJComboBoxWithBeans(_mSIDI_RightInternalSensor, "Sensor", _mCodeButtonHandlerData->_mSIDI_RightInternalSensor->getHandleName(), false);   // NOI18N
    _mSIDI_CodingAndResponseTime->setText(QString::number(_mCodeButtonHandlerData->_mSIDI_CodingTimeInMilliseconds));
    _mSIDI_TimeLockingInterval->setText(QString::number(_mCodeButtonHandlerData->_mSIDI_TimeLockingTimeInMilliseconds));
    _mSIDI_TableOfLeftToRightTrafficExternalSignalNamesDefaultTableModel = (DefaultTableModel*)_mSIDI_TableOfLeftToRightTrafficExternalSignalNames->getModel();
    QList<QString> signalsArrayList1 = ProjectsCommonSubs::getArrayListOfSignalNames(_mCodeButtonHandlerData->_mSIDI_LeftRightTrafficSignals);
    int signalsArrayListSize1 = signalsArrayList1.size();
    if (signalsArrayListSize1 > _mSIDI_TableOfLeftToRightTrafficExternalSignalNames->getRowCount()) { // Has more than default (100 as of this writing) rows:
        _mSIDI_TableOfLeftToRightTrafficExternalSignalNamesDefaultTableModel->setRowCount(signalsArrayListSize1);
    }
    for (int index = 0; index < signalsArrayListSize1; index++) {
        _mSIDI_TableOfLeftToRightTrafficExternalSignalNamesDefaultTableModel->setValueAt(signalsArrayList1.at(index), index, 0);
    }
    _mSIDI_TableOfRightToLeftTrafficExternalSignalNamesDefaultTableModel = (DefaultTableModel*)_mSIDI_TableOfRightToLeftTrafficExternalSignalNames->getModel();
    QList<QString> signalsArrayList2 = ProjectsCommonSubs::getArrayListOfSignalNames(_mCodeButtonHandlerData->_mSIDI_RightLeftTrafficSignals);
    int signalsArrayListSize2 = signalsArrayList2.size();
    if (signalsArrayListSize2 > _mSIDI_TableOfRightToLeftTrafficExternalSignalNames->getRowCount()) { // Has more than default (100 as of this writing) rows:
        _mSIDI_TableOfRightToLeftTrafficExternalSignalNamesDefaultTableModel->setRowCount(signalsArrayListSize2);
    }
    for (int index = 0; index < signalsArrayListSize2; index++) {
        _mSIDI_TableOfRightToLeftTrafficExternalSignalNamesDefaultTableModel->setValueAt(signalsArrayList2.at(index), index, 0);
    }
    _mSIDI_TrafficDirectionTemp =_mCodeButtonHandlerData->_mSIDI_TrafficDirection;
    switch (_mSIDI_TrafficDirectionTemp) {
        default:
        case CodeButtonHandlerData::BOTH:
            _mSIDI_BothTrafficButton->setChecked(true);
            break;
        case CodeButtonHandlerData::LEFT:
            _mSIDI_LeftTrafficButton->setChecked(true);
            break;
        case CodeButtonHandlerData::RIGHT:
            _mSIDI_RightTrafficButton->setChecked(true);
            break;
    }

    initOrig(signalsArrayList1, signalsArrayList2);
    _mAwtWindowProperties->setWindowState(this, FORM_PROPERTIES);
    //this.getRootPane().setDefaultButton(_mSaveAndClose);
    _mSaveAndClose->setDefault(true);

    enableSignalListComboBox(_mSIDI_TableOfLeftToRightTrafficExternalSignalNames);
    enableSignalListComboBox(_mSIDI_TableOfRightToLeftTrafficExternalSignalNames);
}

/*public*/ /*static*/ bool FrmSIDI::dialogCodeButtonHandlerDataValid(CheckJMRIObject* checkJMRIObject, CodeButtonHandlerData* codeButtonHandlerData) {
    if (!codeButtonHandlerData->_mSIDI_Enabled) return true; // Not enabled, can be no error!
//  For interrelationship(s) checks:
    bool leftTrafficDirection = codeButtonHandlerData->_mSIDI_TrafficDirection != CodeButtonHandlerData::TRAFFIC_DIRECTION::RIGHT;
    bool rightTrafficDirection = codeButtonHandlerData->_mSIDI_TrafficDirection != CodeButtonHandlerData::TRAFFIC_DIRECTION::LEFT;

    bool entriesInLeftRightTrafficSignals = codeButtonHandlerData->_mSIDI_LeftRightTrafficSignals->size() != 0;
    bool entriesInRightLeftTrafficSignals = codeButtonHandlerData->_mSIDI_RightLeftTrafficSignals->size() != 0;

//  Checks:
    if (ProjectsCommonSubs::isNullOrEmptyString(codeButtonHandlerData->_mSIDI_NormalInternalSensor->getHandleName())) return false;
    if (leftTrafficDirection && !entriesInRightLeftTrafficSignals) return false;
    if (rightTrafficDirection && !entriesInLeftRightTrafficSignals) return false;
    if (!leftTrafficDirection && entriesInRightLeftTrafficSignals) return false;
    if (!rightTrafficDirection && entriesInLeftRightTrafficSignals) return false;
    for (QString signalName : ProjectsCommonSubs::getArrayListOfSignalNames(codeButtonHandlerData->_mSIDI_LeftRightTrafficSignals)) {
        if (checkJMRIObject->checkSignal(signalName) == false) return false;
    }
    for (QString signalName : ProjectsCommonSubs::getArrayListOfSignalNames(codeButtonHandlerData->_mSIDI_RightLeftTrafficSignals)) {
        if (checkJMRIObject->checkSignal(signalName) == false) return false;
    }
    return checkJMRIObject->validClassWithPrefix(PREFIX, VPtr<CodeButtonHandlerData>::asQVariant(codeButtonHandlerData));
}

//  Validate all internal fields as much as possible:
/*private*/ QList<QString> FrmSIDI::formFieldsValid() {
    QList<QString> errors = QList<QString>();
//  For interrelationship(s) checks:

    bool leftTrafficDirection = _mSIDI_TrafficDirectionTemp != CodeButtonHandlerData::TRAFFIC_DIRECTION::RIGHT;
    bool rightTrafficDirection = _mSIDI_TrafficDirectionTemp != CodeButtonHandlerData::TRAFFIC_DIRECTION::LEFT;

    // Convert the 100 row lists into occupied signal entries.
    bool entriesInLeftRightTrafficSignals =
            ProjectsCommonSubs::getArrayListOfSignals(
                CommonSubs::getStringArrayFromDefaultTableModel(_mSIDI_TableOfLeftToRightTrafficExternalSignalNamesDefaultTableModel)
                )->size() != 0;
    bool entriesInRightLeftTrafficSignals =
            ProjectsCommonSubs::getArrayListOfSignals(
                CommonSubs::getStringArrayFromDefaultTableModel(_mSIDI_TableOfRightToLeftTrafficExternalSignalNamesDefaultTableModel)
                )->size() != 0;

//  Checks:

    if (leftTrafficDirection && !entriesInRightLeftTrafficSignals) errors.append(tr("The %1 or Both button is active but the \"%2\" is empty.").arg(tr("Left")).arg(_mTableOfRightToLeftTrafficSignalNamesPrompt->text()));    // NOI18N
    if (rightTrafficDirection && !entriesInLeftRightTrafficSignals) errors.append(tr("The %1 or Both button is active but the \"%2\" is empty.").arg(tr("Right")).arg(_mTableOfLeftToRightTrafficSignalNamesPrompt->text()));

    if (!leftTrafficDirection && entriesInRightLeftTrafficSignals) errors.append(tr("The %1  button is active but the \"%2\" has entries.").arg(tr("Left")).arg(_mTableOfRightToLeftTrafficSignalNamesPrompt->text()));    // NOI18N
    if (!rightTrafficDirection && entriesInLeftRightTrafficSignals) errors.append(tr("The %1  button is active but the \"%2\" has entries.").arg(tr("Right")).arg(_mTableOfLeftToRightTrafficSignalNamesPrompt->text()));

    _mCheckJMRIObject->analyzeForm(PREFIX, this, errors);
    return errors;
}

/**
 * Add a signal head/mast combo box as the default cell editor.
 * @param table The signal table to be modified.
 */
/*public*/ void FrmSIDI::enableSignalListComboBox(JTable* table) {
    // Create the signals combo box
    JComboBox* comboBox = new JComboBox();
    if (_mSignalHeadSelected) {
        CommonSubs::populateJComboBoxWithBeans(comboBox, "SignalHead", QString(), true);
    } else {
        CommonSubs::populateJComboBoxWithBeans(comboBox, "SignalMast", QString(), true);
    }

    // Update the signal list cell editor
#if 0 // TODO
    table->setSelectionMode(ListSelectionModel::SINGLE_SELECTION);
    table->getColumnModel()->getColumn(0).setCellEditor(new DefaultCellEditor(comboBox));
#endif
}

/**
 * This method is called from within the constructor to initialize the form.
 * WARNING: Do NOT modify this code. The content of this method is always
 * regenerated by the Form Editor.
 */
//@SuppressWarnings("unchecked")  // NOI18N
// <editor-fold defaultstate="collapsed" desc="Generated Code">
/*private*/ void FrmSIDI::initComponents() {

    _mSIDI_TrafficDirection = new QButtonGroup(this);
    panelLeftColumn = new JPanel();
    _mSIDI_LeftInternalSensorPrompt = new JLabel();
    _mSIDI_LeftInternalSensor = new JComboBox();
    _mSIDI_NormalInternalSensorPrompt = new JLabel();
    _mSIDI_NormalInternalSensor = new JComboBox();
    _mSIDI_RightInternalSensorPrompt = new JLabel();
    _mSIDI_RightInternalSensor = new JComboBox();
    _mSIDI_LableCodeTimeLabel = new JLabel();
    _mSIDI_CodingAndResponseTime = new JFormattedTextField();
    _mSIDI_LockTimeLabel = new JLabel();
    _mSIDI_TimeLockingInterval = new JFormattedTextField();
    _mSIDI_TrafficDirectionGroupPanel = new JPanel();
    jLabel1 = new JLabel();
    _mSIDI_LeftTrafficButton = new QRadioButton();
    _mSIDI_BothTrafficButton = new QRadioButton();
    _mSIDI_RightTrafficButton = new QRadioButton();
    _mSIDI_SaveCloseLabel = new JLabel();
    _mSaveAndClose = new JButton();
    _mSIDI_CompactListsButton = new JButton();
    _mSIDI_CompactListsLabel = new JLabel();
    _mSIDI_ReapplyPatterns = new JButton();
    _mSIDI_LeftRightSignals = new JPanel();
    _mTableOfLeftToRightTrafficSignalNamesPrompt = new JLabel();
    //jScrollPane1 = new JScrollPane();
    _mSIDI_TableOfLeftToRightTrafficExternalSignalNames = new JTable();
    _mSIDI_RightLeftSignals = new JPanel();
    _mTableOfRightToLeftTrafficSignalNamesPrompt = new JLabel();
    //jScrollPane2 = new JScrollPane();
    _mSIDI_TableOfRightToLeftTrafficExternalSignalNames = new JTable();

    setDefaultCloseOperation(JFrame::DO_NOTHING_ON_CLOSE);
    setTitle(tr("Edit signal direction indicators"));
//    addWindowListener(new java.awt.event.WindowAdapter() {
//        @Override
//        /*public*/ void windowClosing(java.awt.event.WindowEvent evt) {
//            formWindowClosing(evt);
//        }
//    });
    addWindowListener(new FrmSIDI_windowListener(this));

    _mSIDI_LeftInternalSensorPrompt->setHorizontalAlignment(/*SwingConstants.RIGHT*/Qt::AlignRight);
    _mSIDI_LeftInternalSensorPrompt->setText(tr("Left indicator sensor:"));

    //_mSIDI_LeftInternalSensor->setModel(new DefaultComboBoxModel<>(new String[] { "Item 1", "Item 2", "Item 3", "Item 4" }));
    _mSIDI_LeftInternalSensor->addItems({ "Item 1", "Item 2", "Item 3", "Item 4" });
    _mSIDI_NormalInternalSensorPrompt->setHorizontalAlignment(/*SwingConstants.RIGHT*/Qt::AlignRight);
    _mSIDI_NormalInternalSensorPrompt->setText(tr("Normal indicator sensor:"));

    //_mSIDI_NormalInternalSensor.setModel(new DefaultComboBoxModel<>(new String[] { "Item 1", "Item 2", "Item 3", "Item 4" }));
    _mSIDI_NormalInternalSensor->addItems({ "Item 1", "Item 2", "Item 3", "Item 4" });
    _mSIDI_RightInternalSensorPrompt->setHorizontalAlignment(/*SwingConstants.RIGHT*/Qt::AlignRight);
    _mSIDI_RightInternalSensorPrompt->setText(tr("Right indicator sensor:"));

    //_mSIDI_RightInternalSensor.setModel(new DefaultComboBoxModel<>(new String[] { "Item 1", "Item 2", "Item 3", "Item 4" }));
    _mSIDI_RightInternalSensor->addItems({ "Item 1", "Item 2", "Item 3", "Item 4" });

    _mSIDI_LableCodeTimeLabel->setText(tr("Coding and response time milliseconds:"));

    //_mSIDI_CodingAndResponseTime.setFormatterFactory(new text.DefaultFormatterFactory(new text.NumberFormatter(new java.text.DecimalFormat("#0"))));
    _mSIDI_CodingAndResponseTime->setValidator(new QIntValidator(0,1));
    _mSIDI_LockTimeLabel->setText(tr("Time locking interval milliseconds:"));

    //_mSIDI_TimeLockingInterval.setFormatterFactory(new text.DefaultFormatterFactory(new text.NumberFormatter(new java.text.DecimalFormat("#0"))));
    _mSIDI_TimeLockingInterval->setValidator(new QIntValidator(0,1));

//    jLabel1.setHorizontalAlignment(SwingConstants.CENTER);
    jLabel1->setText(tr("Traffic Direction"));
    jLabel1->setToolTip("");
//    jLabel1.setHorizontalTextPosition(SwingConstants.CENTER);

    _mSIDI_TrafficDirection->addButton(_mSIDI_LeftTrafficButton);
    _mSIDI_LeftTrafficButton->setText(tr("Left"));
//    _mSIDI_LeftTrafficButton.addActionListener(new java.awt.event.ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
    connect(_mSIDI_LeftTrafficButton, &QRadioButton::clicked, [=]{
            _mSIDI_LeftTrafficButtonActionPerformed(/*evt*/);
//        }
    });

    _mSIDI_TrafficDirection->addButton(_mSIDI_BothTrafficButton);
    _mSIDI_BothTrafficButton->setText(tr("Both"));
//    _mSIDI_BothTrafficButton.addActionListener(new java.awt.event.ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
    connect(_mSIDI_BothTrafficButton, &QRadioButton::clicked, [=]{
            _mSIDI_BothTrafficButtonActionPerformed(/*evt*/);
//        }
    });

    _mSIDI_TrafficDirection->addButton(_mSIDI_RightTrafficButton);
    _mSIDI_RightTrafficButton->setText(tr("Right"));
//    _mSIDI_RightTrafficButton.addActionListener(new java.awt.event.ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
    connect(_mSIDI_RightTrafficButton, &QRadioButton::clicked, [=]{
            _mSIDI_RightTrafficButtonActionPerformed(/*evt*/);
//        }
    });
#if 0
    GroupLayout _mSIDI_TrafficDirectionGroupPanelLayout = new GroupLayout(_mSIDI_TrafficDirectionGroupPanel);
    _mSIDI_TrafficDirectionGroupPanel.setLayout(_mSIDI_TrafficDirectionGroupPanelLayout);
    _mSIDI_TrafficDirectionGroupPanelLayout.setHorizontalGroup(
        _mSIDI_TrafficDirectionGroupPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING)
        .addGroup(_mSIDI_TrafficDirectionGroupPanelLayout.createSequentialGroup()
            .addContainerGap()
            .addComponent(_mSIDI_LeftTrafficButton)
            .addGap(18, 18, 18)
            .addComponent(_mSIDI_BothTrafficButton)
            .addGap(18, 18, 18)
            .addComponent(_mSIDI_RightTrafficButton)
            .addContainerGap(GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        .addGroup(GroupLayout.Alignment.TRAILING, _mSIDI_TrafficDirectionGroupPanelLayout.createSequentialGroup()
            .addContainerGap(GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
            .addComponent(jLabel1)
            .addGap(58, 58, 58))
    );
    _mSIDI_TrafficDirectionGroupPanelLayout.setVerticalGroup(
        _mSIDI_TrafficDirectionGroupPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING)
        .addGroup(_mSIDI_TrafficDirectionGroupPanelLayout.createSequentialGroup()
            .addContainerGap(GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
            .addComponent(jLabel1)
            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
            .addGroup(_mSIDI_TrafficDirectionGroupPanelLayout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                .addComponent(_mSIDI_LeftTrafficButton)
                .addComponent(_mSIDI_BothTrafficButton)
                .addComponent(_mSIDI_RightTrafficButton)))
    );
#else
//    JPanel* contentPane = new JPanel();
//    QVBoxLayout* contentPaneLayout;
//    contentPane->setLayout(contentPaneLayout = new QVBoxLayout());
//    setCentralWidget(contentPane);


#endif
    _mSIDI_SaveCloseLabel->setText(tr("<- Compact is automatically done"));

    _mSaveAndClose->setText(tr("Save and Close"));
//    _mSaveAndClose.addActionListener(new java.awt.event.ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
    connect(_mSaveAndClose, &JButton::clicked, [=]{
            _mSaveAndCloseActionPerformed(/*evt*/);
//        }
    });
#if 0
    GroupLayout panelLeftColumnLayout = new GroupLayout(panelLeftColumn);
    panelLeftColumn.setLayout(panelLeftColumnLayout);
    panelLeftColumnLayout.setHorizontalGroup(
        panelLeftColumnLayout.createParallelGroup(GroupLayout.Alignment.LEADING)
        .addGroup(GroupLayout.Alignment.TRAILING, panelLeftColumnLayout.createSequentialGroup()
            .addContainerGap(28, Short.MAX_VALUE)
            .addGroup(panelLeftColumnLayout.createParallelGroup(GroupLayout.Alignment.LEADING)
                .addComponent(_mSIDI_TrafficDirectionGroupPanel, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                .addGroup(panelLeftColumnLayout.createSequentialGroup()
                    .addComponent(_mSaveAndClose)
                    .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                    .addComponent(_mSIDI_SaveCloseLabel))
                .addGroup(panelLeftColumnLayout.createSequentialGroup()
                    .addGroup(panelLeftColumnLayout.createParallelGroup(GroupLayout.Alignment.TRAILING)
                        .addComponent(_mSIDI_LockTimeLabel)
                        .addComponent(_mSIDI_LableCodeTimeLabel)
                        .addComponent(_mSIDI_NormalInternalSensorPrompt)
                        .addComponent(_mSIDI_LeftInternalSensorPrompt)
                        .addComponent(_mSIDI_RightInternalSensorPrompt))
                    .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                    .addGroup(panelLeftColumnLayout.createParallelGroup(GroupLayout.Alignment.LEADING)
                        .addComponent(_mSIDI_RightInternalSensor, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                        .addComponent(_mSIDI_NormalInternalSensor, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                        .addComponent(_mSIDI_LeftInternalSensor, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                        .addComponent(_mSIDI_CodingAndResponseTime, GroupLayout.PREFERRED_SIZE, 63, GroupLayout.PREFERRED_SIZE)
                        .addComponent(_mSIDI_TimeLockingInterval, GroupLayout.PREFERRED_SIZE, 63, GroupLayout.PREFERRED_SIZE))))
            .addGap(24, 24, 24))
    );
    panelLeftColumnLayout.setVerticalGroup(
        panelLeftColumnLayout.createParallelGroup(GroupLayout.Alignment.LEADING)
        .addGroup(panelLeftColumnLayout.createSequentialGroup()
            .addGap(6, 6, 6)
            .addGroup(panelLeftColumnLayout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                .addComponent(_mSIDI_LeftInternalSensorPrompt)
                .addComponent(_mSIDI_LeftInternalSensor, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
            .addGroup(panelLeftColumnLayout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                .addComponent(_mSIDI_NormalInternalSensorPrompt)
                .addComponent(_mSIDI_NormalInternalSensor, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
            .addGroup(panelLeftColumnLayout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                .addComponent(_mSIDI_RightInternalSensorPrompt)
                .addComponent(_mSIDI_RightInternalSensor, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
            .addGroup(panelLeftColumnLayout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                .addComponent(_mSIDI_LableCodeTimeLabel)
                .addComponent(_mSIDI_CodingAndResponseTime, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
            .addGroup(panelLeftColumnLayout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                .addComponent(_mSIDI_LockTimeLabel)
                .addComponent(_mSIDI_TimeLockingInterval, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
            .addGap(38, 38, 38)
            .addComponent(_mSIDI_TrafficDirectionGroupPanel, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
            .addGap(36, 36, 36)
            .addGroup(panelLeftColumnLayout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                .addComponent(_mSaveAndClose)
                .addComponent(_mSIDI_SaveCloseLabel))
            .addContainerGap(98, Short.MAX_VALUE))
    );
#else
    JPanel* contentPane = new JPanel();
    QGridLayout* grid;
    contentPane->setLayout(grid = new QGridLayout());
    setCentralWidget(contentPane);

    grid->addWidget(_mSIDI_LeftInternalSensorPrompt, 0, 0, 1, 1, Qt::AlignLeft);
    grid->addWidget(_mSIDI_LeftInternalSensor, 0, 1);
    grid->addWidget(_mTableOfLeftToRightTrafficSignalNamesPrompt, 0, 2);
    grid->addWidget(_mTableOfRightToLeftTrafficSignalNamesPrompt, 0, 3);

    grid->addWidget(_mSIDI_NormalInternalSensorPrompt, 1, 0, 1, 1, Qt::AlignLeft);
    grid->addWidget(_mSIDI_NormalInternalSensor, 1,1);
    grid->addWidget(_mSIDI_TableOfLeftToRightTrafficExternalSignalNames, 1, 2, 18, 1);
    grid->addWidget(_mSIDI_TableOfRightToLeftTrafficExternalSignalNames, 1, 3, 18, 1);

    grid->addWidget(_mSIDI_NormalInternalSensorPrompt, 2, 0, 1, 1, Qt::AlignRight);
    grid->addWidget(_mSIDI_NormalInternalSensor, 2,1);

    grid->addWidget(_mSIDI_LableCodeTimeLabel, 3,0, 1,1, Qt::AlignRight);
    grid->addWidget(_mSIDI_CodingAndResponseTime, 3, 1);

    grid->addWidget(_mSIDI_LockTimeLabel, 4, 0, 1, 1, Qt::AlignRight);
    grid->addWidget(_mSIDI_TimeLockingInterval, 4,1);

    grid->addWidget(_mSaveAndClose, 16, 0);
    grid->addWidget(_mSIDI_SaveCloseLabel, 16, 1,1, Qt::AlignLeft);

    grid->addWidget(_mSIDI_CompactListsLabel, 20, 2, 1, 2, Qt::AlignHCenter);

    grid->addWidget(_mSIDI_ReapplyPatterns, 21, 0);
    grid->addWidget(_mSIDI_CompactListsButton, 21,3);

#endif
    _mSIDI_CompactListsButton->setText(tr("Compact both lists"));
//    _mSIDI_CompactListsButton.addActionListener(new java.awt.event.ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
    connect(_mSIDI_CompactListsButton, &JButton::clicked, [=]{
            _mSIDI_CompactListsButtonActionPerformed(/*evt*/);
//        }
    });

    _mSIDI_CompactListsLabel->setText(tr("To remove signal(s), just blank out the line(s), then press:"));

    _mSIDI_ReapplyPatterns->setText(tr("Reapply patterns - this form ONLY!"));
//    _mSIDI_ReapplyPatterns.addActionListener(new java.awt.event.ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
    connect(_mSIDI_ReapplyPatterns, &JButton::clicked, [=]{
            _mSIDI_ReapplyPatternsActionPerformed(/*evt*/);
//        }
    });

    _mTableOfLeftToRightTrafficSignalNamesPrompt->setText(tr("Left to right traffic signal list:"));
#if 0
    _mSIDI_TableOfLeftToRightTrafficExternalSignalNames.setModel(new table.DefaultTableModel(
        new Object [][] {
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null}
        },
        new String [] {
            ""
        }
    ) {
        Class[] types = new Class [] {
            java.lang.String.class
        };

        @Override
        /*public*/ Class getColumnClass(int columnIndex) {
            return types [columnIndex];
        }
    });
#else
    _mSIDI_TableOfLeftToRightTrafficExternalSignalNames->setModel(new DefaultTableModel(100, 1));
#endif
    _mSIDI_TableOfLeftToRightTrafficExternalSignalNames->setRowHeight(18);
//    jScrollPane1.setViewportView(_mSIDI_TableOfLeftToRightTrafficExternalSignalNames);
#if 0
    GroupLayout _mSIDI_LeftRightSignalsLayout = new GroupLayout(_mSIDI_LeftRightSignals);
    _mSIDI_LeftRightSignals.setLayout(_mSIDI_LeftRightSignalsLayout);
    _mSIDI_LeftRightSignalsLayout.setHorizontalGroup(
        _mSIDI_LeftRightSignalsLayout.createParallelGroup(GroupLayout.Alignment.LEADING)
        .addGroup(_mSIDI_LeftRightSignalsLayout.createSequentialGroup()
            .addContainerGap()
            .addGroup(_mSIDI_LeftRightSignalsLayout.createParallelGroup(GroupLayout.Alignment.LEADING)
                .addComponent(jScrollPane1, GroupLayout.PREFERRED_SIZE, 0, Short.MAX_VALUE)
                .addComponent(_mTableOfLeftToRightTrafficSignalNamesPrompt))
            .addContainerGap())
    );
    _mSIDI_LeftRightSignalsLayout.setVerticalGroup(
        _mSIDI_LeftRightSignalsLayout.createParallelGroup(GroupLayout.Alignment.LEADING)
        .addGroup(_mSIDI_LeftRightSignalsLayout.createSequentialGroup()
            .addContainerGap()
            .addComponent(_mTableOfLeftToRightTrafficSignalNamesPrompt)
            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
            .addComponent(jScrollPane1, GroupLayout.PREFERRED_SIZE, 363, GroupLayout.PREFERRED_SIZE)
            .addContainerGap(18, Short.MAX_VALUE))
    );
#else
#endif

    _mTableOfRightToLeftTrafficSignalNamesPrompt->setText(tr("Right to left traffic signal list:"));
#if 0
    _mSIDI_TableOfRightToLeftTrafficExternalSignalNames.setModel(new table.DefaultTableModel(
        new Object [][] {
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null},
            {null}
        },
        new String [] {
            ""
        }
    ) {
        Class[] types = new Class [] {
            java.lang.String.class
        };

        @Override
        /*public*/ Class getColumnClass(int columnIndex) {
            return types [columnIndex];
        }
    });
#else
    _mSIDI_TableOfRightToLeftTrafficExternalSignalNames->setModel(new DefaultTableModel(100, 1));
#endif
    _mSIDI_TableOfRightToLeftTrafficExternalSignalNames->setRowHeight(18);
//    jScrollPane2.setViewportView(_mSIDI_TableOfRightToLeftTrafficExternalSignalNames);
#if 0
    GroupLayout _mSIDI_RightLeftSignalsLayout = new GroupLayout(_mSIDI_RightLeftSignals);
    _mSIDI_RightLeftSignals.setLayout(_mSIDI_RightLeftSignalsLayout);
    _mSIDI_RightLeftSignalsLayout.setHorizontalGroup(
        _mSIDI_RightLeftSignalsLayout.createParallelGroup(GroupLayout.Alignment.LEADING)
        .addGroup(_mSIDI_RightLeftSignalsLayout.createSequentialGroup()
            .addContainerGap()
            .addGroup(_mSIDI_RightLeftSignalsLayout.createParallelGroup(GroupLayout.Alignment.LEADING)
                .addComponent(_mTableOfRightToLeftTrafficSignalNamesPrompt)
                .addComponent(jScrollPane2, GroupLayout.PREFERRED_SIZE, 0, Short.MAX_VALUE))
            .addContainerGap())
    );
    _mSIDI_RightLeftSignalsLayout.setVerticalGroup(
        _mSIDI_RightLeftSignalsLayout.createParallelGroup(GroupLayout.Alignment.LEADING)
        .addGroup(_mSIDI_RightLeftSignalsLayout.createSequentialGroup()
            .addContainerGap()
            .addComponent(_mTableOfRightToLeftTrafficSignalNamesPrompt)
            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
            .addComponent(jScrollPane2, GroupLayout.PREFERRED_SIZE, 363, GroupLayout.PREFERRED_SIZE)
            .addContainerGap(18, Short.MAX_VALUE))
    );

    GroupLayout layout = new GroupLayout(getContentPane());
    getContentPane().setLayout(layout);
    layout.setHorizontalGroup(
        layout.createParallelGroup(GroupLayout.Alignment.LEADING)
        .addGroup(layout.createSequentialGroup()
            .addContainerGap()
            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                .addGroup(layout.createSequentialGroup()
                    .addGap(6, 6, 6)
                    .addComponent(_mSIDI_ReapplyPatterns)
                    .addGap(39, 39, 39)
                    .addComponent(_mSIDI_CompactListsLabel)
                    .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                    .addComponent(_mSIDI_CompactListsButton)
                    .addContainerGap(GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addGroup(layout.createSequentialGroup()
                    .addComponent(panelLeftColumn, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                    .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                    .addComponent(_mSIDI_LeftRightSignals, GroupLayout.DEFAULT_SIZE, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addGap(18, 18, 18)
                    .addComponent(_mSIDI_RightLeftSignals, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                    .addGap(17, 17, 17))))
    );
    layout.setVerticalGroup(
        layout.createParallelGroup(GroupLayout.Alignment.LEADING)
        .addGroup(layout.createSequentialGroup()
            .addContainerGap()
            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                .addGroup(layout.createSequentialGroup()
                    .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                        .addComponent(panelLeftColumn, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                        .addComponent(_mSIDI_RightLeftSignals, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
                    .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                    .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                        .addComponent(_mSIDI_ReapplyPatterns)
                        .addComponent(_mSIDI_CompactListsLabel)
                        .addComponent(_mSIDI_CompactListsButton))
                    .addGap(0, 0, Short.MAX_VALUE))
                .addGroup(layout.createSequentialGroup()
                    .addComponent(_mSIDI_LeftRightSignals, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                    .addContainerGap(GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))))
    );
#else

#endif
    pack();
}// </editor-fold>

/*private*/ void FrmSIDI::_mSaveAndCloseActionPerformed(/*java.awt.event.ActionEvent evt*/) {
    if (CommonSubs::missingFieldsErrorDialogDisplayed(this, formFieldsValid(), false)) {
        return; // Do not allow exit or transfer of data.
    }

    _mCodeButtonHandlerData->_mSIDI_LeftInternalSensor = CommonSubs::getNBHSensor( _mSIDI_LeftInternalSensor->getSelectedItem(), false);
    _mCodeButtonHandlerData->_mSIDI_NormalInternalSensor = CommonSubs::getNBHSensor( _mSIDI_NormalInternalSensor->getSelectedItem(), false);
    _mCodeButtonHandlerData->_mSIDI_RightInternalSensor = CommonSubs::getNBHSensor( _mSIDI_RightInternalSensor->getSelectedItem(), false);

    _mCodeButtonHandlerData->_mSIDI_CodingTimeInMilliseconds = CommonSubs::getIntFromJTextFieldNoThrow(_mSIDI_CodingAndResponseTime);
    _mCodeButtonHandlerData->_mSIDI_TimeLockingTimeInMilliseconds = CommonSubs::getIntFromJTextFieldNoThrow(_mSIDI_TimeLockingInterval);
    _mCodeButtonHandlerData->_mSIDI_TrafficDirection = _mSIDI_TrafficDirectionTemp;

    _mCodeButtonHandlerData->_mSIDI_LeftRightTrafficSignals = ProjectsCommonSubs::getArrayListOfSignals(CommonSubs::getStringArrayFromDefaultTableModel(_mSIDI_TableOfLeftToRightTrafficExternalSignalNamesDefaultTableModel));
    _mCodeButtonHandlerData->_mSIDI_RightLeftTrafficSignals = ProjectsCommonSubs::getArrayListOfSignals(CommonSubs::getStringArrayFromDefaultTableModel(_mSIDI_TableOfRightToLeftTrafficExternalSignalNamesDefaultTableModel));
    _mClosedNormally = true;
    _mAwtWindowProperties->saveWindowState(this, FORM_PROPERTIES);
    dispose();
}

/*private*/ void FrmSIDI::formWindowClosing(QCloseEvent* evt) {
    _mAwtWindowProperties->saveWindowState(this, FORM_PROPERTIES);
    if (CommonSubs::allowClose(this, dataChanged())) dispose();
}

/*private*/ void FrmSIDI::_mSIDI_CompactListsButtonActionPerformed(/*java.awt.event.ActionEvent evt*/) {
    CommonSubs::compactDefaultTableModel(_mSIDI_TableOfLeftToRightTrafficExternalSignalNamesDefaultTableModel);
    CommonSubs::compactDefaultTableModel(_mSIDI_TableOfRightToLeftTrafficExternalSignalNamesDefaultTableModel);
}

/*private*/ void FrmSIDI::_mSIDI_ReapplyPatternsActionPerformed(/*java.awt.event.ActionEvent evt*/) {
    CodeButtonHandlerData* temp = _mCodeButtonHandlerData;
    temp = CodeButtonHandlerDataRoutines::uECBHDWSD_SIDI(_mProgramProperties, temp);
    CommonSubs::populateJComboBoxWithBeans(_mSIDI_LeftInternalSensor, "Sensor", temp->_mSIDI_LeftInternalSensor->getHandleName(), false);   // NOI18N
    CommonSubs::populateJComboBoxWithBeans(_mSIDI_NormalInternalSensor, "Sensor", temp->_mSIDI_NormalInternalSensor->getHandleName(), false);   // NOI18N
    CommonSubs::populateJComboBoxWithBeans(_mSIDI_RightInternalSensor, "Sensor", temp->_mSIDI_RightInternalSensor->getHandleName(), false);   // NOI18N
}

/*private*/ void FrmSIDI::_mSIDI_LeftTrafficButtonActionPerformed(/*java.awt.event.ActionEvent evt*/) {
    _mSIDI_TrafficDirectionTemp = CodeButtonHandlerData::TRAFFIC_DIRECTION::LEFT;

    _mSIDI_TableOfLeftToRightTrafficExternalSignalNames->setEnabled(false);
    _mSIDI_TableOfRightToLeftTrafficExternalSignalNames->setEnabled(true);

    _mTableOfLeftToRightTrafficSignalNamesPrompt->setEnabled(false);
    _mTableOfRightToLeftTrafficSignalNamesPrompt->setEnabled(true);
}

/*private*/ void FrmSIDI::_mSIDI_BothTrafficButtonActionPerformed(/*java.awt.event.ActionEvent evt*/) {
    _mSIDI_TrafficDirectionTemp = CodeButtonHandlerData::TRAFFIC_DIRECTION::BOTH;

    _mSIDI_TableOfLeftToRightTrafficExternalSignalNames->setEnabled(true);
    _mSIDI_TableOfRightToLeftTrafficExternalSignalNames->setEnabled(true);

    _mTableOfLeftToRightTrafficSignalNamesPrompt->setEnabled(true);
    _mTableOfRightToLeftTrafficSignalNamesPrompt->setEnabled(true);
}

/*private*/ void FrmSIDI::_mSIDI_RightTrafficButtonActionPerformed(/*java.awt.event.ActionEvent evt*/) {
    _mSIDI_TrafficDirectionTemp = CodeButtonHandlerData::TRAFFIC_DIRECTION::RIGHT;

    _mSIDI_TableOfRightToLeftTrafficExternalSignalNames->setEnabled(false);
    _mSIDI_TableOfLeftToRightTrafficExternalSignalNames->setEnabled(true);

    _mTableOfRightToLeftTrafficSignalNamesPrompt->setEnabled(false);
    _mTableOfLeftToRightTrafficSignalNamesPrompt->setEnabled(true);
}

