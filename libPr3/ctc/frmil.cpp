#include "frmil.h"
#include "commonsubs.h"
#include "tablecolumnmodel.h"
#include <vptr.h>
#include "listselectionmodel.h"
#include "tablecolumn.h"
/**
 * @author Gregory J. Bedlek Copyright (C) 2018, 2019
 */
// /*public*/ class FrmIL extends JFrame {

/**
 * Creates new form DlgIL
 */
/*private*/ /*static*/ /*final*/ QString FrmIL::FORM_PROPERTIES = "DlgIL";  // NOI18N
/*private*/ /*static*/ /*final*/ QString FrmIL::PREFIX = "_mIL_";           // NOI18N
/*private*/ void FrmIL::initOrig(QList<QString> signalsArrayList) {
    _mSignalsArrayListOrig = QList<QString>();
    for (int index = 0; index < signalsArrayList.size(); index++) {
        _mSignalsArrayListOrig.append(signalsArrayList.at(index));
    }
}
/*private*/ bool FrmIL::dataChanged() {
    int tableLength = CommonSubs::compactDefaultTableModel(_mIL_TableOfExternalSignalNamesDefaultTableModel);
    if (tableLength != _mSignalsArrayListOrig.size()) return true;
    for (int index = 0; index < tableLength; index++) {
        if (_mSignalsArrayListOrig.at(index) !=(_mIL_TableOfExternalSignalNamesDefaultTableModel->getValueAt(index, 0))) return true;
    }
    return false;
}


/*public*/ FrmIL::FrmIL(AwtWindowProperties *awtWindowProperties,
                CodeButtonHandlerData* codeButtonHandlerData,
                CheckJMRIObject* checkJMRIObject,
                bool signalHeadSelected,
                CTCSerialData* ctcSerialData, QWidget* parent) : JFrame(parent){
    //super();
    initComponents();
    CommonSubs::addHelpMenu(this, "package.jmri.jmrit.ctc.CTC_frmIL", true);  // NOI18N
    _mAwtWindowProperties = awtWindowProperties;
    _mCodeButtonHandlerData = codeButtonHandlerData;
    _mCheckJMRIObject = checkJMRIObject;
    _mSignalHeadSelected = signalHeadSelected;
    _mCTCSerialData = ctcSerialData;
    _mIL_TableOfExternalSignalNamesDefaultTableModel = (DefaultTableModel*)_mIL_TableOfExternalSignalNames->getModel();
    QList<QString> signalsArrayList = ProjectsCommonSubs::getArrayListOfSignalNames(_mCodeButtonHandlerData->_mIL_Signals);
    loadUpSignalTable(signalsArrayList);
    initOrig(signalsArrayList);

    _mAwtWindowProperties->setWindowState(this, FORM_PROPERTIES);
    //this.getRootPane().setDefaultButton(_mSaveAndClose);
    _mSaveAndClose->setDefault(true);

    enableSignalListComboBox(_mIL_TableOfExternalSignalNames);
    bool anyAvailable = CommonSubs::populateJComboBoxWithColumnDescriptionsExceptOurs(_mOS_NumberEntry, _mCTCSerialData, _mCodeButtonHandlerData->_mUniqueID, _mUniqueIDS);
    BT_Replace->setEnabled(anyAvailable);
}

/*public*/ /*static*/ bool FrmIL::dialogCodeButtonHandlerDataValid(CheckJMRIObject* checkJMRIObject, CodeButtonHandlerData* codeButtonHandlerData) {
    if (!codeButtonHandlerData->_mIL_Enabled) return true; // Not enabled, can be no error!
//  Checks:
    if (codeButtonHandlerData->_mIL_Signals->isEmpty()) return false;
    for (QString signalName : ProjectsCommonSubs::getArrayListOfSignalNames(codeButtonHandlerData->_mIL_Signals)) {
        if (checkJMRIObject->checkSignal(signalName) == false) return false;
    }
    return checkJMRIObject->validClassWithPrefix(PREFIX, VPtr<CodeButtonHandlerData>::asQVariant(codeButtonHandlerData));
}

//  Validate all internal fields as much as possible:
/*private*/ QList<QString> FrmIL::formFieldsValid() {
    QList<QString> errors = QList<QString>();
//  Checks:
    if (CommonSubs::getCSVStringFromDefaultTableModel(_mIL_TableOfExternalSignalNamesDefaultTableModel).isEmpty()) {
        errors.append(tr("InfoDlgILNoEntriesIn") + " \"" + _mTableOfSignalNamesPrompt->text() + "\"");    // NOI18N
    }
    _mCheckJMRIObject->analyzeForm(PREFIX, this, errors);
    return errors;
}

/**
 * Add a signal head/mast combo box as the default cell editor.
 * @param table The signal table to be modified.
 */
/*public*/ void FrmIL::enableSignalListComboBox(JTable* table) {
    // Create the signals combo box
    JComboBox/*<String>*/*comboBox = new JComboBox();
    // Since IL does not have a signal type field, use the SIDI signal type
    if (_mSignalHeadSelected) {
        CommonSubs::populateJComboBoxWithBeans(comboBox, "SignalHead", QString(), true);
    } else {
        CommonSubs::populateJComboBoxWithBeans(comboBox, "SignalMast", QString(), true);
    }

    // Update the signal list cell editor
    table->setSelectionMode(ListSelectionModel::SINGLE_SELECTION);
    //table->getColumnModel()->getColumn(0).setCellEditor(new DefaultCellEditor(comboBox));
}

/*private*/ void FrmIL::loadUpSignalTable(QList<QString> signalsArrayList) {
    int signalsArrayLength = signalsArrayList.size();
    if (signalsArrayLength > _mIL_TableOfExternalSignalNames->getRowCount()) { // Has more than default (100 as of this writing) rows:
        _mIL_TableOfExternalSignalNamesDefaultTableModel->setRowCount(signalsArrayLength);
    }
    for (int index = 0; index < signalsArrayLength; index++) {
        _mIL_TableOfExternalSignalNamesDefaultTableModel->setValueAt(signalsArrayList.at(index), index, 0);
    }
}

/**
 * This method is called from within the constructor to initialize the form.
 * WARNING: Do NOT modify this code. The content of this method is always
 * regenerated by the Form Editor.
 */
//@SuppressWarnings("unchecked")  // NOI18N
// <editor-fold defaultstate="collapsed" desc="Generated Code">
/*private*/ void FrmIL::initComponents() {

    _mSaveAndClose = new JButton();
//    jScrollPane1 = new JScrollPane();
    _mIL_TableOfExternalSignalNames = new JTable();
    jButton1 = new JButton();
    jLabel4 = new JLabel();
    jLabel1 = new JLabel();
    jLabel5 = new JLabel();
    jLabel6 = new JLabel();
    _mTableOfSignalNamesPrompt = new JLabel();
    jLabel2 = new JLabel();
    _mOS_NumberEntry = new JComboBox();
    BT_Replace = new JButton();

    setDefaultCloseOperation(JFrame::DO_NOTHING_ON_CLOSE);
    setTitle(tr("Edit indication locking"));
//    addWindowListener(new java.awt.event.WindowAdapter() {
//        @Override
//        /*public*/ void windowClosing(java.awt.event.WindowEvent evt) {
//            formWindowClosing(evt);
//        }
//    });
    addWindowListener(new FrmIL_windowListener(this));

    _mSaveAndClose->setText(tr("Save and close"));
//    _mSaveAndClose.addActionListener(new java.awt.event.ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
    connect(_mSaveAndClose, &JButton::clicked, [=]{
            _mSaveAndCloseActionPerformed(/*evt*/);
//        }
    });
#if 0
    _mIL_TableOfExternalSignalNames->setModel(new table->DefaultTableModel(
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
    _mIL_TableOfExternalSignalNames->setModel(new DefaultTableModel(100, 1));
#endif
    _mIL_TableOfExternalSignalNames->setRowHeight(18);
//    jScrollPane1.setViewportView(_mIL_TableOfExternalSignalNames);

    jButton1->setText(tr("Compact"));
//    jButton1.addActionListener(new java.awt.event.ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
    connect(jButton1, &JButton::clicked, [=]{
            jButton1ActionPerformed(/*evt*/);
//        }
    });

    jLabel4->setText(tr("To remove signal(s), just blank out the line(s), then press:"));

    jLabel1->setText(tr("If ANY of these signals are NON RED,"));

    jLabel5->setText(tr("then this O.S. section is considered \"indication\" locked."));

    jLabel6->setText(tr("<- Compact is automatically done"));

    _mTableOfSignalNamesPrompt->setText(tr("Signal names:"));

    jLabel2->setText(tr("Completely replace this set with this O.S. sections set:"));

    BT_Replace->setText(tr("Replace"));
//    BT_Replace.addActionListener(new java.awt.event.ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
    connect(BT_Replace, &JButton::clicked, [=]{
            BT_ReplaceActionPerformed(/*evt*/);
//        }
    });
#if 0
    GroupLayout layout = new GroupLayout(getContentPane());
    getContentPane().setLayout(layout);
    layout.setHorizontalGroup(
        layout.createParallelGroup(GroupLayout.Alignment.LEADING)
        .addGroup(layout.createSequentialGroup()
            .addContainerGap()
            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                .addComponent(jScrollPane1, GroupLayout.PREFERRED_SIZE, 140, GroupLayout.PREFERRED_SIZE)
                .addComponent(_mTableOfSignalNamesPrompt))
            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                .addComponent(jLabel1)
                .addComponent(jLabel5)
                .addComponent(jButton1)
                .addComponent(jLabel4)
                .addGroup(layout.createSequentialGroup()
                    .addComponent(_mSaveAndClose)
                    .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                    .addComponent(jLabel6))
                .addComponent(jLabel2)
                .addGroup(layout.createSequentialGroup()
                    .addComponent(_mOS_NumberEntry, GroupLayout.PREFERRED_SIZE, 80, GroupLayout.PREFERRED_SIZE)
                    .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                    .addComponent(BT_Replace)))
            .addContainerGap(169, Short.MAX_VALUE))
    );
    layout.setVerticalGroup(
        layout.createParallelGroup(GroupLayout.Alignment.LEADING)
        .addGroup(layout.createSequentialGroup()
            .addContainerGap()
            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                .addComponent(jLabel1)
                .addComponent(_mTableOfSignalNamesPrompt, GroupLayout.Alignment.TRAILING))
            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                .addGroup(layout.createSequentialGroup()
                    .addComponent(jLabel5)
                    .addGap(47, 47, 47)
                    .addComponent(jLabel4)
                    .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                    .addComponent(jButton1)
                    .addGap(18, 18, 18)
                    .addComponent(jLabel2)
                    .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                    .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                        .addComponent(_mOS_NumberEntry, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                        .addComponent(BT_Replace))
                    .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED, 155, Short.MAX_VALUE)
                    .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                        .addComponent(_mSaveAndClose)
                        .addComponent(jLabel6)))
                .addComponent(jScrollPane1, GroupLayout.PREFERRED_SIZE, 0, Short.MAX_VALUE))
            .addContainerGap())
    );
#else
    JPanel* contentPane = new JPanel();
    QGridLayout* grid;
    contentPane->setLayout(grid = new QGridLayout());
    setCentralWidget(contentPane);

    grid->addWidget(_mTableOfSignalNamesPrompt, 0, 0, 1, 1);
    grid->addWidget(jLabel1, 0, 1, 1, 3); // "If ANY of these signals are NON RED,"

    grid->addWidget(_mIL_TableOfExternalSignalNames, 1, 0, 18, 1);
    grid->addWidget(jLabel5, 1, 1, 1, 3);

    grid->addWidget(jLabel4, 4, 1, 1, 3);
    grid->addWidget(jButton1, 5, 1);

    grid->addWidget(jLabel2, 6, 1, 1, 3);
    grid->addWidget(_mOS_NumberEntry, 7, 1);
    grid->addWidget(BT_Replace, 7, 2);

    grid->addWidget(_mSaveAndClose, 14, 1);
    grid->addWidget(jLabel6, 14, 2);
#endif
    pack();
}// </editor-fold>

/*private*/ void FrmIL::_mSaveAndCloseActionPerformed(/*java.awt.event.ActionEvent evt*/) {
    if (CommonSubs::missingFieldsErrorDialogDisplayed(this, formFieldsValid(), false)) {
        return; // Do not allow exit or transfer of data.
    }
    _mCodeButtonHandlerData->_mIL_Signals = ProjectsCommonSubs::getArrayListOfSignals(
            CommonSubs::getStringArrayFromDefaultTableModel(
            _mIL_TableOfExternalSignalNamesDefaultTableModel));
    _mClosedNormally = true;
    _mAwtWindowProperties->saveWindowState(this, FORM_PROPERTIES);
    dispose();
}

/*private*/ void FrmIL::formWindowClosing(QCloseEvent* evt) {
    _mAwtWindowProperties->saveWindowState(this, FORM_PROPERTIES);
    if (CommonSubs::allowClose(this, dataChanged())) dispose();
}

/*private*/ void FrmIL::jButton1ActionPerformed(/*java.awt.event.ActionEvent evt*/) {
    CommonSubs::compactDefaultTableModel(_mIL_TableOfExternalSignalNamesDefaultTableModel);
}

/*private*/ void FrmIL::BT_ReplaceActionPerformed(/*java.awt.event.ActionEvent evt*/) {
    int index = _mOS_NumberEntry->getSelectedIndex();
    if (index != -1) { // Safety:
        CodeButtonHandlerData* otherCodeButtonHandlerData = _mCTCSerialData->getCodeButtonHandlerDataViaUniqueID(_mUniqueIDS->at(index));
        loadUpSignalTable(ProjectsCommonSubs::getArrayListOfSignalNames(otherCodeButtonHandlerData->_mIL_Signals));
    }
}

