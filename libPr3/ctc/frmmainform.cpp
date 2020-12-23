#include "frmmainform.h"
#include "instancemanager.h"
#include "ctcmanager.h"
#include "commonsubs.h"
#include <QAction>
#include "ctcfiles.h"
#include <QMenu>
#include "jlabel.h"
#include "jbutton.h"
#include "jlist.h"
#include "jcheckbox.h"
#include <QMenuBar>
#include "joptionpane.h"
#include "listselectionmodel.h"
#include "awtwindowproperties.h"
#include "frmswdi.h"
#include "checkjmriobject.h"
#include "defaultlistmodel.h"
#include <QBoxLayout>
#include "flowlayout.h"
#include <QScrollArea>
#include "frmcb.h"
#include "box.h"
#include "frmabout.h"
#include "frmguidesign.h"
#include "frmco.h"
#include "importexternaldata.h"
#include "createguiobjectsxmlfile.h"
#include "frmdebugging.h"
#include "frmdefaults.h"
#include <QItemSelection>
#include "frmsidi.h"
#include "frmswdl.h"
#include "frmco.h"
#include "frmtrl.h"
#include "frmsidl.h"
#include "frmil.h"
#include "frmfleeting.h"
#include "frmpatterns.h"
#include "frmtul.h"
#include "frmfixerrors.h"
#include "proxysensormanager.h"
#include "namedbeanhandlemanager.h"
#include "otherdata.h"

/**
 *
 * @author Gregory J. Bedlek Copyright (C) 2018, 2019
 */
///*public*/ class FrmMainForm extends JFrame {

/*private*/ /*static*/ /*final*/ QString FrmMainForm::FORM_PROPERTIES = "FrmMainForm";    // NOI18N

    //@SuppressWarnings("LeakingThisInConstructor")   // NOI18N   Lazy, since this is NOT a multi-threaded program.
    /*public*/ FrmMainForm::FrmMainForm(QWidget *parent) {
        //super();
        InstanceManager::setDefault("FrmMainForm", this);
        CtcManager* ctcManager = (CtcManager*)InstanceManager::getDefault("CtcManager");
        _mProgramProperties = ctcManager->getProgramProperties();
        _mCTCSerialData = ctcManager->getCTCSerialData();
        initComponents();
        CommonSubs::addHelpMenu(this, "package.jmri.jmrit.ctc.CTC", true);  // NOI18N
        _mAwtWindowProperties = new AwtWindowProperties(this, "AwtWindowProperties.txt", FORM_PROPERTIES); // NOI18N
        _mCheckJMRIObject = new CheckJMRIObject();
        setupEditor();
        _mImport->setEnabled(CTCFiles::fileExists("CTCSystem.xml"));   // Disable import if there is no file

        // for testing
        CTCSerialData* cTCSerialData = ctcManager->getCTCSerialData();
        CodeButtonHandlerData* cbhd;
        OtherData* od = cTCSerialData->getOtherData();
        od->_mSignalSystemType = OtherData::SIGNAL_SYSTEM_TYPE::SIGNALHEAD;
        if(cTCSerialData->_mCodeButtonHandlerDataArrayList.isEmpty())
        {
         cTCSerialData->addCodeButtonHandlerData(cbhd = CodeButtonHandlerDataRoutines::createNewCodeButtonHandlerData(0, 1, 2, 2, _mProgramProperties));
         ctcManager->putNBHSignal("Left-U",  new NBHSignal("Left-U"));
         ctcManager->putNBHSignal("Left-L",  new NBHSignal("Left-L"));
         ctcManager->putNBHSignal("Left-M",  new NBHSignal("Left-M"));
         ctcManager->putNBHSignal("Left-S",  new NBHSignal("Left-S"));
         ctcManager->putNBHSignal("Right-M",  new NBHSignal("Right-M"));
         ctcManager->putNBHSignal("Right-S",  new NBHSignal("Right-S"));
         ctcManager->putNBHSignal("Right-U",  new NBHSignal("Right-U"));
         ctcManager->putNBHSignal("Right-L",  new NBHSignal("Right-L"));
         ctcManager->putNBHSignal("Stub-M",  new NBHSignal("Stub-M"));
         ctcManager->putNBHSignal("Stub-S",  new NBHSignal("Stub-S"));
         ctcManager->putNBHSignal("Stub-U",  new NBHSignal("Stub-U"));
         ctcManager->putNBHSignal("Stub-L",  new NBHSignal("Stub-L"));
         cbhd->_mSIDI_LeftRightTrafficSignals->append(ctcManager->getNBHSignal("Left-U"));
         cbhd->_mSIDI_LeftRightTrafficSignals->append(ctcManager->getNBHSignal("Left-L"));
         cbhd->_mSIDI_RightLeftTrafficSignals->append(ctcManager->getNBHSignal("Left-M"));
         cbhd->_mSIDI_RightLeftTrafficSignals->append(ctcManager->getNBHSignal("Left-S"));
         ProxySensorManager* sensorManager = (ProxySensorManager*)InstanceManager::sensorManagerInstance();
         QList<NamedBean*>* list = sensorManager->getNamedBeanList();
         NamedBeanHandleManager* namedBeanHandleManager = (NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager");
         foreach (NamedBean* b, *list) {
          Sensor* s = (Sensor*)b;
          NamedBeanHandle<NamedBean*>* nbh = new NamedBeanHandle<NamedBean*>(s->getSystemName(), b);
          ctcManager->putNBHSensor(s->getSystemName(), new NBHSensor(nbh));
         }
         //data->_mCodeButtonInternalSensor = new NBHSensor("CtcManagerXml", "create internal = ", "IS2:CB", "IS2:CB");
         //cTCSerialData->addCodeButtonHandlerData(new CodeButtonHandlerData(3, 3, 4,3 ));
         cTCSerialData->addCodeButtonHandlerData(CodeButtonHandlerDataRoutines::createNewCodeButtonHandlerData(3, 3, 4,3, _mProgramProperties));
         //cTCSerialData->addCodeButtonHandlerData(new CodeButtonHandlerData(1, 5, 6,4 ));
         cTCSerialData->addCodeButtonHandlerData(cbhd =CodeButtonHandlerDataRoutines::createNewCodeButtonHandlerData(1, 5, 6,4, _mProgramProperties));
         cbhd->_mSIDI_LeftRightTrafficSignals->append(ctcManager->getNBHSignal("Right-M"));
         cbhd->_mSIDI_LeftRightTrafficSignals->append(ctcManager->getNBHSignal("Right-S"));
         cbhd->_mSIDI_RightLeftTrafficSignals->append(ctcManager->getNBHSignal("Right-U"));
         cbhd->_mSIDI_RightLeftTrafficSignals->append(ctcManager->getNBHSignal("Right-L"));
         //cTCSerialData->addCodeButtonHandlerData(new CodeButtonHandlerData(2, 7, 8,5 ));
         cTCSerialData->addCodeButtonHandlerData(CodeButtonHandlerDataRoutines::createNewCodeButtonHandlerData(2, 7, 8,5 , _mProgramProperties));
        }
        _mColumns->updateFrame();
    }
#if 0
    /**
     * Create a platform specific accelerator key stroke
     * @param keycode The integer value for the key from KeyEvent
     * @return The key stroke with the platform's accelerator character
     */
    /*private*/ KeyStroke getAccelerator(int keycode) {
        int modifier = Toolkit.getDefaultToolkit().getMenuShortcutKeyMask();
        return KeyStroke.getKeyStroke(keycode, modifier);
    }
#endif
    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     * Note:  The form editor will set the method private.  It must be public.
     */
    // <editor-fold defaultstate="collapsed" desc="Generated Code">
    /*private*/ void FrmMainForm::initComponents() {

        jMenuItem1 = new QAction(this);
        jMenu3 = new QMenu();
        jLabel1 = new JLabel();
        //jScrollPane1 = new QScrollArea();
        _mPresentlyDefinedColumns = new JList();
        _mPresentlyDefinedColumns->setMinimumWidth(600);
        addButton = new JButton();
        deleteButton = new JButton();
        _mSIDI_Enabled = new JCheckBox();
        _mEdit_SIDI = new JButton();
        _mEdit_SIDI_Prompt = new JLabel();
        _mEdit_SIDL_Prompt = new JLabel();
        _mSIDL_Enabled = new JCheckBox();
        _mEdit_SIDL = new JButton();
        _mEdit_SWDI_Prompt = new JLabel();
        _mSWDI_Enabled = new JCheckBox();
        _mEdit_SWDI = new JButton();
        _mEdit_SWDL_Prompt = new JLabel();
        _mSWDL_Enabled = new JCheckBox();
        _mEdit_SWDL = new JButton();
        _mEdit_CO_Prompt = new JLabel();
        _mCO_Enabled = new JCheckBox();
        _mEdit_CO = new JButton();
        _mEdit_TUL_Prompt = new JLabel();
        _mTUL_Enabled = new JCheckBox();
        _mEdit_TUL = new JButton();
        _mEdit_IL_Prompt = new JLabel();
        _mIL_Enabled = new JCheckBox();
        _mEdit_IL = new JButton();
        _mEdit_TRL_Prompt = new JLabel();
        _mTRL_Enabled = new JCheckBox();
        _mEdit_TRL = new JButton();
        _mEdit_CB_Prompt = new JLabel();
        _mEdit_CB = new JButton();
        _mCB_EditAlwaysEnabled = new JLabel();
        changeNumbersButton = new JButton();
        _mButtonWriteXMLFiles = new JButton();
        _mMoveUp = new JButton();
        _mMoveDown = new JButton();
        jMenuBar1 = new QMenuBar();
        _mFile = new QMenu();
        _mNew = new QAction();
        _mImport = new QAction();
        _mEdit = new QMenu();
        _mFixErrors = new QAction(this);
        _mConfigure = new QMenu();
        _mDebugging = new QAction(this);
        _mDefaults = new QAction(this);
        _mFleeting = new QAction(this);
        _mPatterns = new QAction(this);
        _mGUIDesign = new QAction(this);
        _mHelp = new QMenu();
        _mHelpAbout = new QAction(this);

        jMenuItem1->setText("jMenuItem1");

        jMenu3->setTitle("jMenu3");

        setDefaultCloseOperation(JFrame::DO_NOTHING_ON_CLOSE);
        setLocation(QPoint(0, 0));
//        addWindowListener(new java.awt.event.WindowAdapter() {
//            @Override
//            /*public*/ void windowClosing(java.awt.event.WindowEvent evt) {
//                formWindowClosing(evt);
//            }
//        });
        addWindowListener(new FrmMain_windowListener(this));

        jLabel1->setText(tr("Presently defined CTC O.S. sections:"));

        _mPresentlyDefinedColumns->setSelectionMode(/*ListSelectionModel::SINGLE_SELECTION*/QAbstractItemView::SingleSelection);
//        _mPresentlyDefinedColumns.addListSelectionListener(new ListSelectionListener() {
//            @Override
//            /*public*/ void valueChanged(event.ListSelectionEvent evt) {
//                _mPresentlyDefinedColumnsValueChanged(evt);
//            }
//        });
        //_mPresentlyDefinedColumns->addListSelectionListener(new FrmMain_listSelectionListener(this));
        connect(_mPresentlyDefinedColumns, SIGNAL(clicked(QModelIndex)), this,SLOT(selectionChanged(QModelIndex)));

//        jScrollPane1->setViewportView(_mPresentlyDefinedColumns);

        addButton->setText(tr("Add"));
//        addButton.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
        connect(addButton, &JButton::clicked, [=]{
                addButtonActionPerformed(/*evt*/);
//            }
        });

        deleteButton->setText(tr("Delete"));
//        deleteButton.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
        connect(deleteButton, &JButton::clicked, [=]{
                deleteButtonActionPerformed(/*evt*/);
//            }
        });

        _mSIDI_Enabled->setText(tr("Enabled"));
//        _mSIDI_Enabled.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
        connect(_mSIDI_Enabled, &JCheckBox::clicked, [=]{
                _mSIDI_EnabledActionPerformed(/*evt*/);
//            }
        });

        _mEdit_SIDI->setText(tr("Edit"));
//        _mEdit_SIDI.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
        connect(_mEdit_SIDI, &JButton::clicked, [=]{
                _mEdit_SIDIActionPerformed(/*evt*/);
//            }
        });

        _mEdit_SIDI_Prompt->setText(tr("Signal direction indicators:"));

        _mEdit_SIDL_Prompt->setText(tr("Signal direction lever:"));

        _mSIDL_Enabled->setText(tr("Enabled"));
//        _mSIDL_Enabled.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
        connect(_mSIDL_Enabled, &JCheckBox::clicked, [=]{
                _mSIDL_EnabledActionPerformed(/*evt*/);
//            }
        });

        _mEdit_SIDL->setText(tr("Edit"));
//        _mEdit_SIDL.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
        connect(_mEdit_SIDL, &JButton::clicked, [=]{
                _mEdit_SIDLActionPerformed(/*evt*/);
//            }
        });

        _mEdit_SWDI_Prompt->setText(tr("Switch direction indicators:"));

        _mSWDI_Enabled->setText(tr("Enabled"));
//        _mSWDI_Enabled.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
        connect(_mSWDI_Enabled, &JCheckBox::clicked, [=]{
                _mSWDI_EnabledActionPerformed(/*evt*/);
//            }
        });

        _mEdit_SWDI->setText(tr("Edit"));
//        _mEdit_SWDI.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
        connect(_mEdit_SWDI, &JButton::clicked, [=]{
                _mEdit_SWDIActionPerformed(/*evt*/);
//            }
        });

        _mEdit_SWDL_Prompt->setText(tr("Switch direction lever:"));

        _mSWDL_Enabled->setText(tr("Enabled"));
//        _mSWDL_Enabled.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
        connect(_mSWDL_Enabled, &JCheckBox::clicked, [=]{
                _mSWDL_EnabledActionPerformed(/*evt*/);
//            }
        });

        _mEdit_SWDL->setText(tr("Edit"));
//        _mEdit_SWDL.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
        connect(_mEdit_SWDL, &JButton::clicked, [=]{
                _mEdit_SWDLActionPerformed(/*evt*/);
//            }
        });

        _mEdit_CO_Prompt->setText(tr("Call-on:"));

        _mCO_Enabled->setText(tr("Enabled"));
//        _mCO_Enabled.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
        connect(_mCO_Enabled, &JCheckBox::clicked, [=]{
                _mCO_EnabledActionPerformed(/*evt*/);
//            }
        });

        _mEdit_CO->setText(tr("Edit"));
//        _mEdit_CO.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
        connect(_mEdit_CO, &JButton::clicked, [=]{
                _mEdit_COActionPerformed(/*evt*/);
//            }
        });

        _mEdit_TUL_Prompt->setText(tr("Turnout locking:"));

        _mTUL_Enabled->setText(tr("Enabled"));
//        _mTUL_Enabled.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
        connect(_mTUL_Enabled, &JCheckBox::clicked, [=]{
                _mTUL_EnabledActionPerformed(/*evt*/);
//            }
        });

        _mEdit_TUL->setText(tr("Edit"));
//        _mEdit_TUL.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
        connect(_mEdit_TUL, &JButton::clicked, [=]{
                _mEdit_TULActionPerformed(/*evt*/);
//            }
        });

        _mEdit_IL_Prompt->setText(tr("Indication locking:"));

        _mIL_Enabled->setText(tr("Enabled"));
//        _mIL_Enabled.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
        connect(_mIL_Enabled, &JCheckBox::clicked, [=]{
                _mIL_EnabledActionPerformed(/*evt*/);
//            }
        });

        _mEdit_IL->setText(tr("Edit"));
//        _mEdit_IL.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
        connect(_mEdit_IL, &JButton::clicked, [=]{
                _mEdit_ILActionPerformed(/*evt*/);
//            }
        });

        _mEdit_TRL_Prompt->setText(tr("Traffic locking:"));

        _mTRL_Enabled->setText(tr("Enabled"));
//        _mTRL_Enabled.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
        connect(_mTRL_Enabled, &JCheckBox::clicked, [=]{
                _mTRL_EnabledActionPerformed(/*evt*/);
//            }
        });

        _mEdit_TRL->setText(tr("Edit"));
//        _mEdit_TRL.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
        connect(_mEdit_TRL, &JButton::clicked, [=]{
                _mEdit_TRLActionPerformed(/*evt*/);
//            }
        });

        _mEdit_CB_Prompt->setText(tr("Code Button:"));

        _mEdit_CB->setText(tr("Edit"));
//        _mEdit_CB.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
        connect(_mEdit_CB, &JButton::clicked, [=]{
                _mEdit_CBActionPerformed(/*evt*/);
//            }
        });

        _mCB_EditAlwaysEnabled->setText(tr("Always enabled"));

        changeNumbersButton->setText(tr("Change Switch and Signal etc. #'s"));
//        changeNumbersButton.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
        connect(changeNumbersButton, &JButton::clicked, [=]{
                changeNumbersButtonActionPerformed(/*evt*/);
//            }
        });

        _mButtonWriteXMLFiles->setText(tr("Write .xml file for JMRI GUI support"));
//        _mButtonWriteXMLFiles.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
        connect(_mButtonWriteXMLFiles, &JButton::clicked, [=]{
                _mButtonWriteXMLFilesActionPerformed(/*evt*/);
//            }
        });

        _mMoveUp->setText(tr("Move Up"));
//        _mMoveUp.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
        connect(_mMoveUp, &JButton::clicked, [=]{
                _mMoveUpActionPerformed(/*evt*/);
//            }
        });

        _mMoveDown->setText(tr("Move Down"));
//        _mMoveDown.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
        connect(_mMoveDown, &JButton::clicked, [=]{
                _mMoveDownActionPerformed(/*evt*/);
//            }
        });

        _mFile->setTitle(tr("File"));

//        _mNew->setAccelerator(getAccelerator(KeyEvent.VK_N));
        _mNew->setText(tr("New"));
//        _mNew.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
        connect(_mNew, &QAction::triggered, [=]{
                _mNewActionPerformed(/*evt*/);
//            }
        });
        _mFile->addAction(_mNew);

        _mImport->setText(tr("Import old configuration (CTCSystem.xml)"));
//        _mImport.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
        connect(_mImport, &QAction::triggered, [=]{
                _mImportActionPerformed(/*evt*/);
//            }
        });
        _mFile->addAction(_mImport);

        jMenuBar1->addMenu(_mFile);

        _mEdit->setTitle(tr("Edit"));

        _mFixErrors->setText(tr("Fix"));
//        _mFixErrors.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
        connect(_mFixErrors, &QAction::triggered, [=]{
                _mFixErrorsActionPerformed(/*evt*/);
//            }
        });
        _mEdit->addAction(_mFixErrors);

        jMenuBar1->addMenu(_mEdit);

        _mConfigure->setTitle(tr("Configure"));

        _mDebugging->setText(tr("Debugging"));
//        _mDebugging.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
        connect(_mDebugging, &QAction::triggered, [=]{
                _mDebuggingActionPerformed(/*evt*/);
//            }
        });
        _mConfigure->addAction(_mDebugging);

        _mDefaults->setText(tr("Defaults"));
//        _mDefaults.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
        connect(_mDefaults, &QAction::triggered, [=]{
                _mDefaultsActionPerformed(/*evt*/);
//            }
        });
        _mConfigure->addAction(_mDefaults);

        _mFleeting->setText(tr("Fleeting"));
//        _mFleeting.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
        connect(_mFleeting, &QAction::triggered, [=]{
                _mFleetingActionPerformed(/*evt*/);
//            }
        });
        _mConfigure->addAction(_mFleeting);

        _mPatterns->setText(tr("Patterns"));
//        _mPatterns.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
        connect(_mPatterns, &QAction::triggered, [=]{
                _mPatternsActionPerformed(/*evt*/);
//            }
        });
        _mConfigure->addAction(_mPatterns);

        _mGUIDesign->setText(tr("Design"));
//        _mGUIDesign.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
        connect(_mGUIDesign, &QAction::triggered, [=]{
                _mGUIDesignActionPerformed(/*evt*/);
//            }
        });
        _mConfigure->addAction(_mGUIDesign);

        jMenuBar1->addMenu(_mConfigure);

        _mHelp->setTitle(tr("About"));

        _mHelpAbout->setText(tr("About CTC"));
//        _mHelpAbout.addActionListener(new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
        connect(_mHelpAbout, &QAction::triggered, [=]{
                _mHelpAboutActionPerformed(/*evt*/);
//            }
        });
        _mHelp->addAction(_mHelpAbout);

        jMenuBar1->addMenu(_mHelp);

        setMenuBar(jMenuBar1);
#if 0
        GroupLayout layout = new GroupLayout(getContentPane());
        getContentPane()->setLayout(layout);
        layout->setHorizontalGroup(
            layout.createParallelGroup(GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                            .addGroup(layout.createSequentialGroup()
                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                                    .addComponent(_mEdit_CB_Prompt)
                                    .addComponent(_mEdit_CB)
                                    .addComponent(_mCB_EditAlwaysEnabled))
                                .addGap(27, 27, 27)
                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                                    .addComponent(_mEdit_SIDI_Prompt)
                                    .addComponent(_mSIDI_Enabled)
                                    .addComponent(_mEdit_SIDI)))
                            .addGroup(layout.createSequentialGroup()
                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                                    .addComponent(_mEdit_CO_Prompt)
                                    .addComponent(_mCO_Enabled)
                                    .addComponent(_mEdit_CO))
                                .addGap(43, 43, 43)
                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                                    .addComponent(_mEdit_TRL)
                                    .addComponent(_mTRL_Enabled)
                                    .addComponent(_mEdit_TRL_Prompt))))
                        .addGap(18, 18, 18)
                        .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                            .addComponent(_mEdit_SIDL_Prompt)
                            .addComponent(_mSIDL_Enabled)
                            .addComponent(_mEdit_SIDL)
                            .addComponent(_mEdit_TUL_Prompt)
                            .addComponent(_mTUL_Enabled)
                            .addComponent(_mEdit_TUL))
                        .addGap(18, 18, 18)
                        .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                            .addComponent(_mEdit_IL)
                            .addComponent(_mIL_Enabled)
                            .addComponent(_mEdit_IL_Prompt)
                            .addGroup(layout.createSequentialGroup()
                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                                    .addComponent(_mEdit_SWDI_Prompt)
                                    .addComponent(_mSWDI_Enabled)
                                    .addComponent(_mEdit_SWDI))
                                .addGap(18, 18, 18)
                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                                    .addComponent(_mEdit_SWDL)
                                    .addComponent(_mSWDL_Enabled)
                                    .addComponent(_mEdit_SWDL_Prompt))))
                        .addGap(0, 228, Short.MAX_VALUE))
                    .addGroup(GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                        .addComponent(jLabel1)
                        .addContainerGap(GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(jScrollPane1, GroupLayout.PREFERRED_SIZE, 662, GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                            .addGroup(layout.createSequentialGroup()
                                .addComponent(_mButtonWriteXMLFiles, GroupLayout.PREFERRED_SIZE, 291, GroupLayout.PREFERRED_SIZE)
                                .addContainerGap(12, Short.MAX_VALUE))
                            .addGroup(layout.createSequentialGroup()
                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                                    .addGroup(layout.createSequentialGroup()
                                        .addGap(4, 4, 4)
                                        .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING, false)
                                            .addComponent(addButton)
                                            .addComponent(deleteButton)))
                                    .addGroup(layout.createParallelGroup(GroupLayout.Alignment.TRAILING, false)
                                        .addComponent(_mMoveUp, GroupLayout.Alignment.LEADING, GroupLayout.DEFAULT_SIZE, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                        .addComponent(_mMoveDown, GroupLayout.Alignment.LEADING, GroupLayout.DEFAULT_SIZE, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                                    .addComponent(changeNumbersButton, GroupLayout.PREFERRED_SIZE, 291, GroupLayout.PREFERRED_SIZE))
                                .addGap(0, 0, Short.MAX_VALUE))))))
        );
        layout->setVerticalGroup(
            layout.createParallelGroup(GroupLayout.Alignment.LEADING)
            .addGroup(GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jLabel1)
                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                    .addComponent(jScrollPane1, GroupLayout.PREFERRED_SIZE, 334, GroupLayout.PREFERRED_SIZE)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(addButton)
                        .addGap(18, 18, 18)
                        .addComponent(deleteButton)
                        .addGap(18, 18, 18)
                        .addComponent(changeNumbersButton)
                        .addGap(18, 18, 18)
                        .addComponent(_mMoveUp)
                        .addGap(18, 18, 18)
                        .addComponent(_mMoveDown)
                        .addGap(18, 18, 18)
                        .addComponent(_mButtonWriteXMLFiles)))
                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                    .addComponent(_mEdit_CB_Prompt)
                    .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                        .addComponent(_mEdit_SIDI_Prompt)
                        .addComponent(_mEdit_SIDL_Prompt)
                        .addComponent(_mEdit_SWDI_Prompt)
                        .addComponent(_mEdit_SWDL_Prompt)))
                .addGap(3, 3, 3)
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                    .addComponent(_mSIDI_Enabled)
                    .addComponent(_mSIDL_Enabled)
                    .addComponent(_mSWDI_Enabled)
                    .addComponent(_mSWDL_Enabled)
                    .addComponent(_mCB_EditAlwaysEnabled))
                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                    .addComponent(_mEdit_SIDI)
                    .addComponent(_mEdit_SIDL)
                    .addComponent(_mEdit_SWDI)
                    .addComponent(_mEdit_SWDL)
                    .addComponent(_mEdit_CB))
                .addGap(18, 18, 18)
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                    .addComponent(_mEdit_CO_Prompt)
                    .addComponent(_mEdit_TRL_Prompt)
                    .addComponent(_mEdit_TUL_Prompt)
                    .addComponent(_mEdit_IL_Prompt))
                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                    .addComponent(_mCO_Enabled)
                    .addComponent(_mTRL_Enabled)
                    .addComponent(_mTUL_Enabled)
                    .addComponent(_mIL_Enabled))
                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                    .addComponent(_mEdit_CO)
                    .addComponent(_mEdit_TRL)
                    .addComponent(_mEdit_TUL)
                    .addComponent(_mEdit_IL))
                .addContainerGap(20, Short.MAX_VALUE))
        );
#else
        JPanel* contentPane = new JPanel();
        QVBoxLayout* contentPaneLayout = new QVBoxLayout(contentPane);
        setCentralWidget(contentPane);
        JPanel* panel1 =new JPanel();
        panel1->setLayout(new QHBoxLayout());
        panel1->layout()->addWidget(jLabel1);
        //panel1->layout()->addWidget(jLabel1); JMRI Validation
        //panel1->layout()->addWidget(jLabel1); Enabled/disabled
        contentPaneLayout->addWidget(panel1);

        JPanel* panel2 = new JPanel();
        panel2->setLayout(new QHBoxLayout());
//        QSize s = _mPresentlyDefinedColumns->sizeHint();
//        QSizePolicy sizePolicy =  QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
//        _mPresentlyDefinedColumns->setSizePolicy(sizePolicy);
//        _mPresentlyDefinedColumns->resize(662, s.height());
        _mPresentlyDefinedColumns->setMaximumWidth(662);
        ((QHBoxLayout*)panel2->layout())->addWidget(_mPresentlyDefinedColumns,1, Qt::AlignLeft);

        JPanel* panel3 = new JPanel();
        panel3->setLayout(new QVBoxLayout);
        panel3->layout()->addWidget(addButton);
        panel3->layout()->addWidget(deleteButton);

        JPanel* panel4 = new JPanel();
        panel4->setLayout(new QVBoxLayout);
        panel4->layout()->addWidget(changeNumbersButton);
        panel4->layout()->addWidget(_mMoveUp);
        panel4->layout()->addWidget(_mMoveDown);
        panel4->layout()->addWidget(Box::createVerticalStrut(24));
        panel4->layout()->addWidget(_mButtonWriteXMLFiles);

        JPanel* panel5 = new JPanel();
        panel5->setLayout(new QVBoxLayout);
        panel5->layout()->addWidget(panel3);
        panel5->layout()->addWidget(panel4);
        ((QHBoxLayout*)panel2->layout())->addWidget(panel5,0,Qt::AlignRight);
        contentPane->layout()->addWidget(panel2);

        JPanel* panel6 = new JPanel();
        panel6->setLayout(new QHBoxLayout());

        JPanel* panel6a = new JPanel();
        panel6a->setLayout(new QVBoxLayout());
        panel6a->layout()->addWidget(_mEdit_CB_Prompt);
        panel6a->layout()->addWidget(_mCB_EditAlwaysEnabled);
        panel6a->layout()->addWidget(_mEdit_CB);
        panel6->layout()->addWidget(panel6a);

        JPanel* panel6b = new JPanel();
        panel6b->setLayout(new QVBoxLayout);
        panel6b->layout()->addWidget(_mEdit_SIDI_Prompt);
        panel6b->layout()->addWidget(_mSIDI_Enabled);
        panel6b->layout()->addWidget(_mEdit_SIDI);
        panel6->layout()->addWidget(panel6b);

        JPanel* panel6c = new JPanel();
        panel6c->setLayout(new QVBoxLayout);
        panel6c->layout()->addWidget(_mEdit_SIDL_Prompt);
        panel6c->layout()->addWidget(_mSIDL_Enabled);
        panel6c->layout()->addWidget(_mEdit_SIDL);
        panel6->layout()->addWidget(panel6c);

        JPanel* panel6d = new JPanel();
        panel6d->setLayout(new QVBoxLayout);
        panel6d->layout()->addWidget(_mEdit_SWDI_Prompt);
        panel6d->layout()->addWidget(_mSWDI_Enabled);
        panel6d->layout()->addWidget(_mEdit_SWDI);
        panel6->layout()->addWidget(panel6d);

        JPanel* panel6e = new JPanel();
        panel6e->setLayout(new QVBoxLayout);
        panel6e->layout()->addWidget(_mEdit_SWDL_Prompt);
        panel6e->layout()->addWidget(_mSWDL_Enabled);
        panel6e->layout()->addWidget(_mEdit_SWDL);
        panel6->layout()->addWidget(panel6e);
        contentPaneLayout->addWidget(panel6);

        JPanel* panel7 = new JPanel();
        panel7->setLayout(new QHBoxLayout());

        JPanel* panel7a = new JPanel();
        panel7a->setLayout(new QVBoxLayout());
        panel7a->layout()->addWidget(_mEdit_CO_Prompt);
        panel7a->layout()->addWidget(_mCO_Enabled);
        panel7a->layout()->addWidget(_mEdit_CO);
        panel7->layout()->addWidget(panel7a);

        JPanel* panel7b = new JPanel();
        panel7b->setLayout(new QVBoxLayout());
        panel7b->layout()->addWidget(_mEdit_TRL_Prompt);
        panel7b->layout()->addWidget(_mTRL_Enabled);
        panel7b->layout()->addWidget(_mEdit_TRL);
        panel7->layout()->addWidget(panel7b);

        JPanel* panel7c = new JPanel();
        panel7c->setLayout(new QVBoxLayout());
        panel7c->layout()->addWidget(_mEdit_TUL_Prompt);
        panel7c->layout()->addWidget(_mTUL_Enabled);
        panel7c->layout()->addWidget(_mEdit_TUL);
        panel7->layout()->addWidget(panel7c);

        JPanel* panel7d = new JPanel();
        panel7d->setLayout(new QVBoxLayout());
        panel7d->layout()->addWidget(_mEdit_IL_Prompt);
        panel7d->layout()->addWidget(_mIL_Enabled);
        panel7d->layout()->addWidget(_mEdit_IL);
        panel7->layout()->addWidget(panel7d);

        panel7->layout()->addWidget(Box::createHorizontalStrut(50));
        contentPaneLayout->addWidget(panel7);

#endif
        pack();
    }// </editor-fold>

    /*public*/ void FrmMainForm::shutdown() {
        InstanceManager::reset("FrmMainForm");
        dispose();
    }

    /*private*/ void FrmMainForm::addButtonActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        if (_mAnySubFormOpen) return;
        _mAnySubFormOpen = true;
//  Pre-scan and find the highest switch number used so far, and highest column number:
        int highestSwitchNumber = _mCTCSerialData->findHighestSwitchNumberUsedSoFar();
        int highestColumnNumber = _mCTCSerialData->findHighestColumnNumberUsedSoFar();

        FrmAddModifyCTCColumn* dialog = new FrmAddModifyCTCColumn(_mAwtWindowProperties, _mColumns, false, highestSwitchNumber + 2, highestColumnNumber + 1, false);
//        dialog.addWindowListener(new WindowAdapter() {
//            @Override
//            /*public*/ void windowClosed(WindowEvent e) {
//                if (dialog.closedNormally()) {
//                    _mCTCSerialData->addCodeButtonHandlerData(CodeButtonHandlerDataRoutines.createNewCodeButtonHandlerData(_mCTCSerialData->getUniqueNumber(), dialog._mNewSwitchNumber, dialog._mNewSignalEtcNumber, dialog._mNewGUIColumnNumber, _mProgramProperties));
//                    _mColumns.updateFrame();
//                }
//                _mAnySubFormOpen = false;
//            }
//        });
        dialog->addWindowListener(new FrmMain_FrmAddModifyCTCColumnWindowListener(dialog, this));

        dialog->setVisible(true);  // MUST BE AFTER "addWindowListener"!  BUG IN AWT/SWING!
    }

    /*private*/ void FrmMainForm::deleteButtonActionPerformed(/*java.awt.event.ActionEvent evt*/) {

        if ((_mPresentlyDefinedColumns->getSelectedValue().toString()).contains(Columns::REFERENCES_PRESENT_INDICATOR)) {
            JOptionPane::showMessageDialog(this, tr("References exist, remove those first before delete allowed."));   // NOI18N
            return; // Do nothing!
        }

        int selectedIndex = _mPresentlyDefinedColumns->getSelectedIndex();
        if (selectedIndex != -1) { // Safety:
            _mCTCSerialData->removeCodeButtonHandlerData(selectedIndex);
            _mColumns->updateFrame();
        }
    }

    /*private*/ void FrmMainForm::formWindowClosing(QCloseEvent* evt) {
        if (!validToExitAtThisTime(tr("FrmMainFormExitError1"))) return; // NOI18N
        _mAwtWindowProperties->saveWindowStateAndClose(this, FORM_PROPERTIES);
        shutdown();
    }

    /*private*/ bool FrmMainForm::validToExitAtThisTime(QString whatIsTriggeringSave) {
        if (_mColumns->anyErrorsPresent()) {
            JOptionPane::showMessageDialog(this,
                    tr("FrmMainFormValidError1") + whatIsTriggeringSave + tr("s not allowed until you fix all errors.\nYou can try Edit > Fix Error(s)... first."),
                    tr("FrmMainFormValidError3"),
                    JOptionPane::ERROR_MESSAGE);   // NOI18N
            return false;
        }
        return true;
    }

    /*private*/ void FrmMainForm::_mPresentlyDefinedColumnsValueChanged(ListSelectionEvent* evt) {
        if (!evt->getValueIsAdjusting()) { // returns false is FINAL in chain.
            int selectedIndex = _mPresentlyDefinedColumns->getSelectedIndex();
//  I guess at some level this makes sense:
//  It seems that "_mDefaultListModel.clear();" and "_mDefaultListModel.addElement..." BOTH
//  causes this routine to be called repeatedly with a -1 each time for selectedIndex.  In fact, for EACH
//  "_mDefaultListModel.addElement..." it calls us with -1.  Go figure!  Why -1 in that case?
//  Isn't one being added that makes sense at a value >= 0?  Then why call us at all?  Sigh......
//  I'm used to other languages (C, C++, C#) that don't do this.
            _mColumns->setEntrySelected(selectedIndex);
        }
    }

    /*private*/ void FrmMainForm::_mSIDI_EnabledActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        _mColumns->sidi_EnabledClicked(_mSIDI_Enabled->isChecked());
    }

    /*private*/ void FrmMainForm::_mSIDL_EnabledActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        _mColumns->sidl_EnabledClicked(_mSIDL_Enabled->isChecked());
    }

    /*private*/ void FrmMainForm::_mSWDI_EnabledActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        _mColumns->swdi_EnabledClicked(_mSWDI_Enabled->isChecked());
    }

    /*private*/ void FrmMainForm::_mSWDL_EnabledActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        _mColumns->swdl_EnabledClicked(_mSWDL_Enabled->isChecked());
    }

    /*private*/ void FrmMainForm::_mCO_EnabledActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        _mColumns->co_EnabledClicked(_mCO_Enabled->isChecked());
    }

    /*private*/ void FrmMainForm::_mTUL_EnabledActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        _mColumns->tul_EnabledClicked(_mTUL_Enabled->isChecked());
    }

    /*private*/ void FrmMainForm::_mIL_EnabledActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        _mColumns->il_EnabledClicked(_mIL_Enabled->isChecked());
    }

    /*private*/ void FrmMainForm::_mEdit_SIDIActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        if (_mAnySubFormOpen) return;
        _mAnySubFormOpen = true;

        FrmSIDI* dialog = new FrmSIDI(    _mAwtWindowProperties, _mColumns->getSelectedCodeButtonHandlerData(), _mProgramProperties, _mCheckJMRIObject,
                                         _mCTCSerialData->getOtherData()->_mSignalSystemType == OtherData::SIGNAL_SYSTEM_TYPE::SIGNALHEAD);
//        dialog.addWindowListener(new WindowAdapter() {
//            @Override
//            /*public*/ void windowClosed(WindowEvent e) {
//                if (dialog.closedNormally()) {
//                    _mColumns.updateFrame();
//                }
//                _mAnySubFormOpen = false;
//            }
//        });
        dialog->addWindowListener(new FrmMain_dialogUpdateWindowListener(dialog, this));
        dialog->setVisible(true);
    }

    /*private*/ void FrmMainForm::_mEdit_SIDLActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        if (_mAnySubFormOpen) return;
        _mAnySubFormOpen = true;

        FrmSIDL* dialog = new FrmSIDL(_mAwtWindowProperties, _mColumns->getSelectedCodeButtonHandlerData(), _mProgramProperties, _mCheckJMRIObject);
//        dialog.addWindowListener(new WindowAdapter() {
//            @Override
//            /*public*/ void windowClosed(WindowEvent e) {
//                if (dialog.closedNormally()) {
//                    _mColumns.updateFrame();
//                }
//                _mAnySubFormOpen = false;
//            }
//        });
        dialog->addWindowListener(new FrmMain_dialogUpdateWindowListener(dialog, this));
        dialog->setVisible(true);  // MUST BE AFTER "addWindowListener"!  BUG IN AWT/SWING!
    }

    void FrmMainForm::selectionChanged(QModelIndex curr)
    {
     _mColumns->setEntrySelected(curr.row());
    }

    /*private*/ void FrmMainForm::_mEdit_SWDIActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        if (_mAnySubFormOpen) return;
        _mAnySubFormOpen = true;
        FrmSWDI* dialog = new FrmSWDI(_mAwtWindowProperties, _mColumns->getSelectedCodeButtonHandlerData(), _mProgramProperties, _mCheckJMRIObject);

//        dialog.addWindowListener(new WindowAdapter() {
//            @Override
//            /*public*/ void windowClosed(WindowEvent e) {
//                if (dialog.closedNormally()) {
//                    _mColumns.updateFrame();
//                }
//                _mAnySubFormOpen = false;
//            }
//        });

        dialog->addWindowListener(new FrmMain_dialogUpdateWindowListener(dialog, this));
        dialog->setVisible(true);  // MUST BE AFTER "addWindowListener"!  BUG IN AWT/SWING!
    }

    /*private*/ void FrmMainForm::_mEdit_SWDLActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        if (_mAnySubFormOpen) return;
        _mAnySubFormOpen = true;

        FrmSWDL* dialog = new FrmSWDL(_mAwtWindowProperties, _mColumns->getSelectedCodeButtonHandlerData(), _mProgramProperties, _mCheckJMRIObject);
//        dialog.addWindowListener(new WindowAdapter() {
//            @Override
//            /*public*/ void windowClosed(WindowEvent e) {
//                if (dialog.closedNormally()) {
//                    _mColumns.updateFrame();
//                }
//                _mAnySubFormOpen = false;
//            }
//        });
        dialog->addWindowListener(new FrmMain_dialogUpdateWindowListener(dialog, this));
        dialog->setVisible(true);  // MUST BE AFTER "addWindowListener"!  BUG IN AWT/SWING!
    }

    /*private*/ void FrmMainForm::_mEdit_COActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        if (_mAnySubFormOpen) return;
        _mAnySubFormOpen = true;

        FrmCO* dialog = new FrmCO(   _mAwtWindowProperties, _mColumns->getSelectedCodeButtonHandlerData(),
                                    _mProgramProperties, _mCTCSerialData, _mCheckJMRIObject,
                                     _mCTCSerialData->getOtherData()->_mSignalSystemType == OtherData::SIGNAL_SYSTEM_TYPE::SIGNALHEAD);
//        dialog.addWindowListener(new WindowAdapter() {
//            @Override
//            /*public*/ void windowClosed(WindowEvent e) {
//                if (dialog.closedNormally()) {
//                    _mColumns.updateFrame();
//                }
//                _mAnySubFormOpen = false;
//            }
//        });
        dialog->addWindowListener(new FrmMain_dialogUpdateWindowListener(dialog, this));
        dialog->setVisible(true);  // MUST BE AFTER "addWindowListener"!  BUG IN AWT/SWING!
    }

    /*private*/ void FrmMainForm::_mEdit_TULActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        if (_mAnySubFormOpen) return;
        _mAnySubFormOpen = true;
#if 1
        FrmTUL* dialog = new FrmTUL(_mAwtWindowProperties, _mCTCSerialData, _mColumns->getSelectedCodeButtonHandlerData(), _mProgramProperties, _mCheckJMRIObject);
//        dialog.addWindowListener(new WindowAdapter() {
//            @Override
//            /*public*/ void windowClosed(WindowEvent e) {
//                if (dialog.closedNormally()) {
//                    _mColumns.updateFrame();
//                }
//                _mAnySubFormOpen = false;
//            }
//        });
        dialog->addWindowListener(new FrmMain_dialogUpdateWindowListener(dialog, this));
        dialog->setVisible(true);  // MUST BE AFTER "addWindowListener"!  BUG IN AWT/SWING!
#endif
    }

    /*private*/ void FrmMainForm::_mEdit_ILActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        if (_mAnySubFormOpen) return;
        _mAnySubFormOpen = true;
#if 1
        FrmIL* dialog = new FrmIL(   _mAwtWindowProperties, _mColumns->getSelectedCodeButtonHandlerData(), _mCheckJMRIObject,
                                    _mCTCSerialData->getOtherData()->_mSignalSystemType == OtherData::SIGNAL_SYSTEM_TYPE::SIGNALHEAD,
                                    _mCTCSerialData);
//        dialog.addWindowListener(new WindowAdapter() {
//            @Override
//            /*public*/ void windowClosed(WindowEvent e) {
//                if (dialog.closedNormally()) {
//                    _mColumns.updateFrame();
//                }
//                _mAnySubFormOpen = false;
//            }
//        });
        dialog->addWindowListener(new FrmMain_dialogUpdateWindowListener(dialog, this));
        dialog->setVisible(true);  // MUST BE AFTER "addWindowListener"!  BUG IN AWT/SWING!
#endif
    }

    /*private*/ void FrmMainForm::_mTRL_EnabledActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        _mColumns->trl_EnabledClicked(_mTRL_Enabled->isChecked());
    }

    /*private*/ void FrmMainForm::_mEdit_TRLActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        if (_mAnySubFormOpen) return;
        _mAnySubFormOpen = true;
        CodeButtonHandlerData* codeButtonHandlerDataSelected = _mColumns->getSelectedCodeButtonHandlerData();

        FrmTRL* dialog = new FrmTRL( _mAwtWindowProperties, codeButtonHandlerDataSelected,
                                    _mCTCSerialData, _mCheckJMRIObject);
//        dialog.addWindowListener(new WindowAdapter() {
//            @Override
//            /*public*/ void windowClosed(WindowEvent e) {
//                if (dialog.closedNormally()) {
//                    _mColumns.updateFrame();
//                }
//                _mAnySubFormOpen = false;
//            }
//        });
        dialog->addWindowListener(new FrmMain_dialogUpdateWindowListener(dialog, this));
        dialog->setVisible(true);  // MUST BE AFTER "addWindowListener"!  BUG IN AWT/SWING!
    }

    /*private*/ void FrmMainForm::_mEdit_CBActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        if (_mAnySubFormOpen) return;
        _mAnySubFormOpen = true;
        FrmCB* dialog = new FrmCB(   _mAwtWindowProperties, _mColumns->getSelectedCodeButtonHandlerData(),
                                    _mProgramProperties, _mCTCSerialData, _mCheckJMRIObject);
//        dialog.addWindowListener(new WindowAdapter() {
//            @Override
//            /*public*/ void windowClosed(WindowEvent e) {
//                if (dialog.closedNormally()) {
//                    _mColumns.updateFrame();
//                }
//                _mAnySubFormOpen = false;
//            }
//        });
        dialog->addWindowListener(new FrmMain_dialogUpdateWindowListener(dialog, this));
        dialog->setVisible(true);  // MUST BE AFTER "addWindowListener"!  BUG IN AWT/SWING!
    }

    /*private*/ void FrmMainForm::changeNumbersButtonActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        if (_mAnySubFormOpen) return;
        _mAnySubFormOpen = true;
        CodeButtonHandlerData* temp = _mColumns->getSelectedCodeButtonHandlerData();
#if 1
        FrmAddModifyCTCColumn* dialog = new FrmAddModifyCTCColumn(_mAwtWindowProperties, _mColumns, true, temp->_mSwitchNumber, temp->_mGUIColumnNumber, temp->_mGUIGeneratedAtLeastOnceAlready);
//        dialog.addWindowListener(new WindowAdapter() {
//            @Override
//            /*public*/ void windowClosed(WindowEvent e) {
//                if (dialog.closedNormally()) {
//                    _mCTCSerialData->updateSwitchAndSignalEtcNumbersEverywhere(_mColumns.getEntrySelectedIndex(), dialog._mNewSwitchNumber, dialog._mNewSignalEtcNumber, dialog._mNewGUIColumnNumber, dialog._mNewGUIGeneratedAtLeastOnceAlready);

//                    CodeButtonHandlerData codeButtonHandlerData = _mCTCSerialData->getCodeButtonHandlerData(_mColumns.getEntrySelectedIndex());
//                    CodeButtonHandlerDataRoutines.updateExistingCodeButtonHandlerDataWithSubstitutedData(_mProgramProperties, codeButtonHandlerData);

//                    _mColumns.updateFrame();
//                }
//                _mAnySubFormOpen = false;
//            }
//        });
        dialog->addWindowListener(new FrmMain_FrmAddModifyCTCColumnWindowListener(dialog, this));
        dialog->setVisible(true);    // MUST BE AFTER "addWindowListener"!  BUG IN AWT/SWING!
#endif
    }

    /*private*/ void FrmMainForm::_mButtonWriteXMLFilesActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        CreateGUIObjectsXMLFile::writeGUIObjects();
        _mColumns->updateFrame();
    }

    /*private*/ void FrmMainForm::setupEditor() {
        setTitle(tr("CTC Editor"));     // NOI18N
        _mDefaultListModel = new DefaultListModel();
        _mPresentlyDefinedColumns->setModel(_mDefaultListModel);
        _mColumns = new Columns(_mCTCSerialData, _mCheckJMRIObject, _mDefaultListModel,
                                deleteButton, changeNumbersButton,
                                _mMoveUp, _mMoveDown,
                                _mEdit_CB_Prompt, _mCB_EditAlwaysEnabled, _mEdit_CB,
                                _mEdit_SIDI_Prompt, _mSIDI_Enabled, _mEdit_SIDI,
                                _mEdit_SIDL_Prompt, _mSIDL_Enabled, _mEdit_SIDL,
                                _mEdit_SWDI_Prompt, _mSWDI_Enabled, _mEdit_SWDI,
                                _mEdit_SWDL_Prompt, _mSWDL_Enabled, _mEdit_SWDL,
                                _mEdit_CO_Prompt, _mCO_Enabled, _mEdit_CO,
                                _mEdit_TRL_Prompt, _mTRL_Enabled, _mEdit_TRL,
                                _mEdit_TUL_Prompt, _mTUL_Enabled, _mEdit_TUL,
                                _mEdit_IL_Prompt, _mIL_Enabled, _mEdit_IL);
    }

    /*private*/ void FrmMainForm::_mNewActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        int response = JOptionPane::showConfirmDialog(this,
                tr("NewConfigWarning"),
                tr("NewConfigTitle"),
                JOptionPane::YES_NO_OPTION);
        if (response == 1) return;

        CtcManager* ctcManager = (CtcManager*)InstanceManager::getDefault("CtcManager");
        _mProgramProperties = ctcManager->newProgramProperties();
        _mCTCSerialData = ctcManager->newCTCSerialData();
        setupEditor();
    }

    /*private*/ void FrmMainForm::_mImportActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        int response = JOptionPane::showConfirmDialog(this,
                tr("The existing configuration, if any, will be replaced by the imported configuration.  Continue?"),
                tr("Start Import"),
                JOptionPane::YES_NO_OPTION);
        if (response == 1) return;

        CtcManager* ctcManager = (CtcManager*)InstanceManager::getDefault("CtcManager");
        _mProgramProperties = ctcManager->newProgramProperties();
        _mCTCSerialData = ctcManager->newCTCSerialData();
        ImportExternalData::loadExternalData();
        _mImport->setEnabled(CTCFiles::fileExists("CTCSystem.xml"));   // Disable import if there is no file
        setupEditor();
    }

    /*private*/ void FrmMainForm::_mFleetingActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        if (_mAnySubFormOpen) return;
        _mAnySubFormOpen = true;
#if 1
        FrmFleeting* dialog = new FrmFleeting(_mAwtWindowProperties,  _mCTCSerialData->getOtherData());
        dialog->setVisible(true);
//        dialog.addWindowListener(new WindowAdapter() {
//            @Override
//            /*public*/ void windowClosed(WindowEvent e) {
//                _mAnySubFormOpen = false;
//            }
//        });
        dialog->addWindowListener(new FrmMain_dialogWindowListener(dialog, this));
#endif
    }

    /*private*/ void FrmMainForm::_mPatternsActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        if (_mAnySubFormOpen) return;
        _mAnySubFormOpen = true;
#if 1
        FrmPatterns* dialog = new FrmPatterns(_mAwtWindowProperties, _mProgramProperties);
        dialog->setVisible(true);
//        dialog.addWindowListener(new WindowAdapter() {
//            @Override
//            /*public*/ void windowClosed(WindowEvent e) {
//                _mAnySubFormOpen = false;
//            }
//        });
        dialog->addWindowListener(new FrmMain_dialogWindowListener(dialog, this));
#endif
    }

    /*private*/ void FrmMainForm::_mDefaultsActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        if (_mAnySubFormOpen) return;
        _mAnySubFormOpen = true;
        FrmDefaults* dialog = new FrmDefaults(_mAwtWindowProperties, _mProgramProperties,  _mCTCSerialData->getOtherData());
        dialog->setVisible(true);
//        dialog.addWindowListener(new WindowAdapter() {
//            @Override
//            /*public*/ void windowClosed(WindowEvent e) {
//                _mAnySubFormOpen = false;
//            }
//        });
        dialog->addWindowListener(new FrmMain_dialogWindowListener(dialog, this));
    }

    /*private*/ void FrmMainForm::_mDebuggingActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        if (_mAnySubFormOpen) return;
        _mAnySubFormOpen = true;
        FrmDebugging* dialog = new FrmDebugging(_mAwtWindowProperties,  _mCTCSerialData->getOtherData());
        dialog->setVisible(true);
//        dialog.addWindowListener(new WindowAdapter() {
//            @Override
//            /*public*/ void windowClosed(WindowEvent e) {
//                _mAnySubFormOpen = false;
//            }
//        });
        dialog->addWindowListener(new FrmMain_dialogWindowListener(dialog, this));
    }

    /*private*/ void FrmMainForm::_mGUIDesignActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        if (_mAnySubFormOpen) return;
        _mAnySubFormOpen = true;
        FrmGUIDesign* dialog = new FrmGUIDesign(_mAwtWindowProperties,  _mCTCSerialData->getOtherData());
        dialog->setVisible(true);
//        dialog.addWindowListener(new WindowAdapter() {
//            @Override
//            /*public*/ void windowClosed(WindowEvent e) {
//                _mAnySubFormOpen = false;
//            }
//        });
        dialog->addWindowListener(new FrmMain_dialogWindowListener(dialog, this));
    }

    /*private*/ void FrmMainForm::_mMoveUpActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        int selectedIndex = _mPresentlyDefinedColumns->getSelectedIndex();
        if (selectedIndex != -1) { // Safety:
            _mCTCSerialData->moveUp(selectedIndex);
            _mColumns->updateFrame();
            if (selectedIndex > 0) selectedIndex--;
            _mPresentlyDefinedColumns->setSelectedIndex(selectedIndex);
        }
    }

    /*private*/ void FrmMainForm::_mMoveDownActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        int selectedIndex = _mPresentlyDefinedColumns->getSelectedIndex();
        if (selectedIndex != -1) { // Safety:
            _mCTCSerialData->moveDown(selectedIndex);
            _mColumns->updateFrame();
            if (selectedIndex != _mCTCSerialData->getCodeButtonHandlerDataSize() - 1) selectedIndex++;
            _mPresentlyDefinedColumns->setSelectedIndex(selectedIndex);
        }
    }

    /*private*/ void FrmMainForm::_mFixErrorsActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        if (_mAnySubFormOpen) return;
        _mAnySubFormOpen = true;

        FrmFixErrors* dialog = new FrmFixErrors(_mAwtWindowProperties, _mColumns);
        dialog->setVisible(true);
//        dialog.addWindowListener(new WindowAdapter() {
//            @Override
//            /*public*/ void windowClosed(WindowEvent e) {
//                _mAnySubFormOpen = false;
//            }
//        });
        dialog->addWindowListener(new FrmMain_dialogWindowListener(dialog,this));
    }

    /*private*/ void FrmMainForm::_mHelpAboutActionPerformed(/*java.awt.event.ActionEvent evt*/) {
        if (_mAnySubFormOpen) return;
        _mAnySubFormOpen = true;

        FrmAbout* dialog = new FrmAbout(_mAwtWindowProperties);
        dialog->setVisible(true);
//        dialog.addWindowListener(new WindowAdapter() {
//            @Override
//            /*public*/ void windowClosed(WindowEvent e) {
//                _mAnySubFormOpen = false;
//            }
//        });
        dialog->addWindowListener(new FrmMain_dialogWindowListener(dialog, this));
    }

