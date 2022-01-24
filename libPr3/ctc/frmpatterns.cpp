#include "frmpatterns.h"
#include "commonsubs.h"
#include "box.h"

/**
 *
 * @author Gregory J. Bedlek Copyright (C) 2018, 2019
 */
// /*public*/ class FrmPatterns extends JFrame {

/**
 * Creates new form dlgProperties
 */
/*private*/ /*static*/ /*final*/ QString FrmPatterns::FORM_PROPERTIES = "DlgPatterns";    // NOI18N

/*private*/ void FrmPatterns::initOrig(ProgramProperties* programProperties) {
    _mCodeButtonInternalSensorPatternOrig = programProperties->_mCodeButtonInternalSensorPattern;
    _mSIDI_LeftInternalSensorPatternOrig = programProperties->_mSIDI_LeftInternalSensorPattern;
    _mSIDI_NormalInternalSensorPatternOrig = programProperties->_mSIDI_NormalInternalSensorPattern;
    _mSIDI_RightInternalSensorPatternOrig = programProperties->_mSIDI_RightInternalSensorPattern;
    _mSIDL_LeftInternalSensorPatternOrig = programProperties->_mSIDL_LeftInternalSensorPattern;
    _mSIDL_NormalInternalSensorPatternOrig = programProperties->_mSIDL_NormalInternalSensorPattern;
    _mSIDL_RightInternalSensorPatternOrig = programProperties->_mSIDL_RightInternalSensorPattern;
    _mSWDI_NormalInternalSensorPatternOrig = programProperties->_mSWDI_NormalInternalSensorPattern;
    _mSWDI_ReversedInternalSensorPatternOrig = programProperties->_mSWDI_ReversedInternalSensorPattern;
    _mSWDL_InternalSensorPatternOrig = programProperties->_mSWDL_InternalSensorPattern;
    _mCO_CallOnToggleInternalSensorPatternOrig = programProperties->_mCO_CallOnToggleInternalSensorPattern;
    _mTUL_DispatcherInternalSensorLockTogglePatternOrig = programProperties->_mTUL_DispatcherInternalSensorLockTogglePattern;
    _mTUL_DispatcherInternalSensorUnlockedIndicatorPatternOrig = programProperties->_mTUL_DispatcherInternalSensorUnlockedIndicatorPattern;
}
/*private*/ bool FrmPatterns::dataChanged() {
    if (_mCodeButtonInternalSensorPatternOrig != (_mCodeButtonInternalSensorPattern->text())) return true;
    if (_mSIDI_LeftInternalSensorPatternOrig != (_mSIDI_LeftInternalSensorPattern->text())) return true;
    if (_mSIDI_NormalInternalSensorPatternOrig != (_mSIDI_NormalInternalSensorPattern->text())) return true;
    if (_mSIDI_RightInternalSensorPatternOrig != (_mSIDI_RightInternalSensorPattern->text())) return true;
    if (_mSIDL_LeftInternalSensorPatternOrig != (_mSIDL_LeftInternalSensorPattern->text())) return true;
    if (_mSIDL_NormalInternalSensorPatternOrig != (_mSIDL_NormalInternalSensorPattern->text())) return true;
    if (_mSIDL_RightInternalSensorPatternOrig != (_mSIDL_RightInternalSensorPattern->text())) return true;
    if (_mSWDI_NormalInternalSensorPatternOrig != (_mSWDI_NormalInternalSensorPattern->text())) return true;
    if (_mSWDI_ReversedInternalSensorPatternOrig != (_mSWDI_ReversedInternalSensorPattern->text())) return true;
    if (_mSWDL_InternalSensorPatternOrig !=(_mSWDL_InternalSensorPattern->text())) return true;
    if (_mCO_CallOnToggleInternalSensorPatternOrig != (_mCO_CallOnToggleInternalSensorPattern->text())) return true;
    if (_mTUL_DispatcherInternalSensorLockTogglePatternOrig != (_mTUL_DispatcherInternalSensorLockTogglePattern->text())) return true;
    if (_mTUL_DispatcherInternalSensorUnlockedIndicatorPatternOrig != (_mTUL_DispatcherInternalSensorUnlockedIndicatorPattern->text())) return true;
    return false;
}

/*public*/ FrmPatterns::FrmPatterns(AwtWindowProperties* awtWindowProperties, ProgramProperties* programProperties, QWidget* parent) {
    //super();
    initComponents();
     CommonSubs::addHelpMenu(this, "package.jmri.jmrit.ctc.CTC_menuCfgPat", true);  // NOI18N
    _mAwtWindowProperties = awtWindowProperties;
    _mProgramProperties = programProperties;

    _mCodeButtonInternalSensorPattern->setText(programProperties->_mCodeButtonInternalSensorPattern);
    _mSIDI_LeftInternalSensorPattern->setText(programProperties->_mSIDI_LeftInternalSensorPattern);
    _mSIDI_NormalInternalSensorPattern->setText(programProperties->_mSIDI_NormalInternalSensorPattern);
    _mSIDI_RightInternalSensorPattern->setText(programProperties->_mSIDI_RightInternalSensorPattern);
    _mSIDL_LeftInternalSensorPattern->setText(programProperties->_mSIDL_LeftInternalSensorPattern);
    _mSIDL_NormalInternalSensorPattern->setText(programProperties->_mSIDL_NormalInternalSensorPattern);
    _mSIDL_RightInternalSensorPattern->setText(programProperties->_mSIDL_RightInternalSensorPattern);
    _mSWDI_NormalInternalSensorPattern->setText(programProperties->_mSWDI_NormalInternalSensorPattern);
    _mSWDI_ReversedInternalSensorPattern->setText(programProperties->_mSWDI_ReversedInternalSensorPattern);
    _mSWDL_InternalSensorPattern->setText(programProperties->_mSWDL_InternalSensorPattern);
    _mCO_CallOnToggleInternalSensorPattern->setText(programProperties->_mCO_CallOnToggleInternalSensorPattern);
    _mTUL_DispatcherInternalSensorLockTogglePattern->setText(programProperties->_mTUL_DispatcherInternalSensorLockTogglePattern);
    _mTUL_DispatcherInternalSensorUnlockedIndicatorPattern->setText(programProperties->_mTUL_DispatcherInternalSensorUnlockedIndicatorPattern);
    initOrig(programProperties);
    _mAwtWindowProperties->setWindowState(this, FORM_PROPERTIES);
    //this.getRootPane()->setDefaultButton(_mSaveAndClose);
    _mSaveAndClose->setDefault(true);
}

/**
 * This method is called from within the constructor to initialize the form.
 * WARNING: Do NOT modify this code. The content of this method is always
 * regenerated by the Form Editor.
 */
// <editor-fold defaultstate="collapsed" desc="Generated Code">
/*private*/ void FrmPatterns::initComponents() {

    _mCodeButtonInternalSensorPattern = new JTextField();
    jLabel1 = new JLabel();
    _mSIDI_LeftInternalSensorPattern = new JTextField();
    _mSIDI_NormalInternalSensorPattern = new JTextField();
    _mSIDI_RightInternalSensorPattern = new JTextField();
    jLabel5 = new JLabel();
    jLabel6 = new JLabel();
    jLabel7 = new JLabel();
    _mSWDI_NormalInternalSensorPattern = new JTextField();
    _mSWDI_ReversedInternalSensorPattern = new JTextField();
    jLabel13 = new JLabel();
    jLabel14 = new JLabel();
    _mSIDL_LeftInternalSensorPattern = new JTextField();
    _mSIDL_NormalInternalSensorPattern = new JTextField();
    _mSIDL_RightInternalSensorPattern = new JTextField();
    jLabel9 = new JLabel();
    jLabel10 = new JLabel();
    jLabel11 = new JLabel();
    _mSWDL_InternalSensorPattern = new JTextField();
    jLabel16 = new JLabel();
    _mCO_CallOnToggleInternalSensorPattern = new JTextField();
    jLabel28 = new JLabel();
    _mSaveAndClose = new JButton();
    jLabel3 = new JLabel();
    jLabel4 = new JLabel();
    jLabel12 = new JLabel();
    jLabel8 = new JLabel();
    jLabel15 = new JLabel();
    jLabel20 = new JLabel();
    jLabel30 = new JLabel();
    jLabel31 = new JLabel();
    _mTUL_DispatcherInternalSensorLockTogglePattern = new JTextField();
    jLabel32 = new JLabel();
    _mTUL_DispatcherInternalSensorUnlockedIndicatorPattern = new JTextField();

    setDefaultCloseOperation(JFrame::DO_NOTHING_ON_CLOSE);
    setTitle(tr("CTC Patterns"));
//    addWindowListener(new java.awt.event.WindowAdapter() {
//        @Override
//        /*public*/ void windowClosing(java.awt.event.WindowEvent evt) {
//            formWindowClosing(evt);
//        }
//    });
    addWindowListener(new FrmPatterns_windowListener(this));
    jLabel1->setHorizontalAlignment(Qt::AlignRight);
    jLabel1->setText(tr("Code Button sensor:"));
    jLabel1->setHorizontalTextPosition(Qt::AlignRight);

    jLabel5->setHorizontalAlignment(Qt::AlignRight);
    jLabel5->setText(tr("Left indicator sensor:"));

    jLabel6->setHorizontalAlignment(Qt::AlignRight);
    jLabel6->setText(tr("Normal indicator sensor:"));

    jLabel7->setHorizontalAlignment(Qt::AlignRight);
    jLabel7->setText(tr("Right indicator sensor:"));

    jLabel13->setHorizontalAlignment(Qt::AlignRight);
    jLabel13->setText(tr("Normal indicator sensor:"));

    jLabel14->setHorizontalAlignment(Qt::AlignRight);
    jLabel14->setText(tr("Reverse indicator sensor:"));

    jLabel9->setHorizontalAlignment(Qt::AlignRight);
    jLabel9->setText(tr("Left lever sensor:"));

    jLabel10->setHorizontalAlignment(Qt::AlignRight);
    jLabel10->setText(tr("Normal lever sensor:"));

    jLabel11->setHorizontalAlignment(Qt::AlignRight);
    jLabel11->setText(tr("Right lever sensor:"));

    jLabel16->setText(tr("Lever sensor:"));

    jLabel28->setText(tr("Toggle sensor:"));

    _mSaveAndClose->setText(tr("Save and Close"));
//    _mSaveAndClose.addActionListener(new java.awt.event.ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/) {
    connect(_mSaveAndClose, &JButton::clicked, [=]{
            _mSaveAndCloseActionPerformed(/*evt*/);
//        }
    });

    jLabel3->setText(tr("General patterns:"));

    jLabel4->setText(tr("Signal direction indicators patterns:"));

    jLabel12->setText(tr("Switch direction indicators patterns:"));

    jLabel8->setText(tr("Signal direction levers patterns:"));

    jLabel15->setHorizontalAlignment(Qt::AlignRight);
    jLabel15->setText(tr("Switch direction levers patterns:"));

    jLabel20->setText(tr("Call-on patterns:"));

    jLabel30->setText(tr("Turnout lock patterns:"));

    jLabel31->setText(tr("Lock toggle sensor:"));

    jLabel32->setText(tr("Unlocked indicator sensor:"));
#if 0
    GroupLayout layout = new GroupLayout(getContentPane());
    getContentPane()->setLayout(layout);
    layout->setHorizontalGroup(
        layout.createParallelGroup(GroupLayout.Alignment.LEADING)
        .addGroup(layout.createSequentialGroup()
            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                .addGroup(layout.createSequentialGroup()
                    .addGap(27, 27, 27)
                    .addGroup(layout.createParallelGroup(GroupLayout.Alignment.TRAILING)
                        .addComponent(jLabel5)
                        .addComponent(jLabel1)
                        .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING, false)
                            .addComponent(jLabel7, GroupLayout.Alignment.TRAILING, GroupLayout.DEFAULT_SIZE, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addComponent(jLabel6, GroupLayout.Alignment.TRAILING, GroupLayout.DEFAULT_SIZE, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                        .addComponent(jLabel10)
                        .addComponent(jLabel11)
                        .addComponent(jLabel8)
                        .addComponent(jLabel9)
                        .addComponent(jLabel4)))
                .addGroup(layout.createSequentialGroup()
                    .addContainerGap()
                    .addGroup(layout.createParallelGroup(GroupLayout.Alignment.TRAILING)
                        .addComponent(jLabel32)
                        .addComponent(jLabel31)
                        .addComponent(jLabel30))))
            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                .addGroup(GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                    .addGroup(layout.createParallelGroup(GroupLayout.Alignment.TRAILING)
                        .addGroup(layout.createSequentialGroup()
                            .addComponent(_mSIDI_NormalInternalSensorPattern, GroupLayout.PREFERRED_SIZE, 93, GroupLayout.PREFERRED_SIZE)
                            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.TRAILING)
                                .addGroup(layout.createSequentialGroup()
                                    .addComponent(jLabel16)
                                    .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                                    .addComponent(_mSWDL_InternalSensorPattern, GroupLayout.PREFERRED_SIZE, 105, GroupLayout.PREFERRED_SIZE))
                                .addGroup(layout.createSequentialGroup()
                                    .addComponent(jLabel14)
                                    .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                                    .addComponent(_mSWDI_ReversedInternalSensorPattern, GroupLayout.PREFERRED_SIZE, 85, GroupLayout.PREFERRED_SIZE))
                                .addGroup(layout.createSequentialGroup()
                                    .addGroup(layout.createParallelGroup(GroupLayout.Alignment.TRAILING)
                                        .addComponent(jLabel20)
                                        .addComponent(jLabel28))
                                    .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                                    .addComponent(_mCO_CallOnToggleInternalSensorPattern, GroupLayout.PREFERRED_SIZE, 105, GroupLayout.PREFERRED_SIZE))))
                        .addGroup(layout.createSequentialGroup()
                            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.TRAILING)
                                .addGroup(layout.createSequentialGroup()
                                    .addGap(0, 0, Short.MAX_VALUE)
                                    .addComponent(jLabel12))
                                .addGroup(layout.createSequentialGroup()
                                    .addComponent(_mSIDI_LeftInternalSensorPattern, GroupLayout.PREFERRED_SIZE, 93, GroupLayout.PREFERRED_SIZE)
                                    .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                    .addComponent(jLabel13)))
                            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                            .addComponent(_mSWDI_NormalInternalSensorPattern, GroupLayout.PREFERRED_SIZE, 85, GroupLayout.PREFERRED_SIZE))
                        .addGroup(layout.createSequentialGroup()
                            .addGap(0, 0, Short.MAX_VALUE)
                            .addComponent(jLabel15, GroupLayout.PREFERRED_SIZE, 195, GroupLayout.PREFERRED_SIZE)
                            .addGap(109, 109, 109))
                        .addGroup(GroupLayout.Alignment.LEADING, layout.createSequentialGroup()
                            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.TRAILING)
                                .addComponent(_mSIDL_RightInternalSensorPattern, GroupLayout.Alignment.LEADING, GroupLayout.PREFERRED_SIZE, 93, GroupLayout.PREFERRED_SIZE)
                                .addComponent(_mSIDI_RightInternalSensorPattern, GroupLayout.Alignment.LEADING, GroupLayout.PREFERRED_SIZE, 93, GroupLayout.PREFERRED_SIZE)
                                .addComponent(_mSIDL_NormalInternalSensorPattern, GroupLayout.Alignment.LEADING, GroupLayout.PREFERRED_SIZE, 93, GroupLayout.PREFERRED_SIZE)
                                .addComponent(_mCodeButtonInternalSensorPattern, GroupLayout.Alignment.LEADING, GroupLayout.PREFERRED_SIZE, 57, GroupLayout.PREFERRED_SIZE)
                                .addGroup(GroupLayout.Alignment.LEADING, layout.createSequentialGroup()
                                    .addGap(65, 65, 65)
                                    .addComponent(_mSaveAndClose)))
                            .addGap(0, 0, Short.MAX_VALUE)))
                    .addContainerGap())
                .addGroup(layout.createSequentialGroup()
                    .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING, false)
                        .addComponent(_mSIDL_LeftInternalSensorPattern, GroupLayout.PREFERRED_SIZE, 93, GroupLayout.PREFERRED_SIZE)
                        .addComponent(_mTUL_DispatcherInternalSensorLockTogglePattern, GroupLayout.DEFAULT_SIZE, 184, Short.MAX_VALUE)
                        .addComponent(_mTUL_DispatcherInternalSensorUnlockedIndicatorPattern))
                    .addGap(0, 0, Short.MAX_VALUE))))
        .addGroup(layout.createSequentialGroup()
            .addGap(260, 260, 260)
            .addComponent(jLabel3)
            .addGap(0, 334, Short.MAX_VALUE))
    );
    layout->setVerticalGroup(
        layout.createParallelGroup(GroupLayout.Alignment.LEADING)
        .addGroup(layout.createSequentialGroup()
            .addContainerGap()
            .addComponent(jLabel3)
            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                .addComponent(_mCodeButtonInternalSensorPattern, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                .addComponent(jLabel1))
            .addGap(18, 18, 18)
            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                .addComponent(jLabel4)
                .addComponent(jLabel12))
            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                .addComponent(_mSIDI_LeftInternalSensorPattern, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                .addComponent(jLabel5)
                .addComponent(_mSWDI_NormalInternalSensorPattern, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                .addComponent(jLabel13))
            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                .addComponent(_mSIDI_NormalInternalSensorPattern, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                .addComponent(jLabel6)
                .addComponent(_mSWDI_ReversedInternalSensorPattern, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                .addComponent(jLabel14))
            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                .addComponent(_mSIDI_RightInternalSensorPattern, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                .addComponent(jLabel7))
            .addGap(18, 18, 18)
            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                .addComponent(jLabel15)
                .addComponent(jLabel8, GroupLayout.PREFERRED_SIZE, 14, GroupLayout.PREFERRED_SIZE))
            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                .addComponent(_mSIDL_LeftInternalSensorPattern, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                .addComponent(jLabel9)
                .addComponent(_mSWDL_InternalSensorPattern, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                .addComponent(jLabel16))
            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                .addComponent(_mSIDL_NormalInternalSensorPattern, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                .addComponent(jLabel10))
            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                .addGroup(layout.createSequentialGroup()
                    .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                    .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                        .addComponent(_mSIDL_RightInternalSensorPattern, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                        .addComponent(jLabel11))
                    .addGap(28, 28, 28)
                    .addComponent(jLabel30))
                .addGroup(layout.createSequentialGroup()
                    .addGap(5, 5, 5)
                    .addComponent(jLabel20, GroupLayout.PREFERRED_SIZE, 12, GroupLayout.PREFERRED_SIZE)
                    .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                    .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                        .addComponent(jLabel28)
                        .addComponent(_mCO_CallOnToggleInternalSensorPattern, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))))
            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                .addComponent(jLabel31)
                .addComponent(_mTUL_DispatcherInternalSensorLockTogglePattern, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
            .addGap(3, 3, 3)
            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                .addComponent(_mTUL_DispatcherInternalSensorUnlockedIndicatorPattern, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                .addComponent(jLabel32))
            .addGap(18, 18, 18)
            .addComponent(_mSaveAndClose)
            .addContainerGap(GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
    );
#else
    JPanel* contentPane = new JPanel();
    //QVBoxLayout* contentPaneLayout;
    QGridLayout* grid;
    int rowSpan = 1;
    //contentPane->setLayout(contentPaneLayout = new QVBoxLayout());
    contentPane->setLayout(grid = new QGridLayout());
    setCentralWidget(contentPane);

//    JPanel* panel1 = new JPanel(new QHBoxLayout());
//    ((QHBoxLayout*)panel1->layout())->addWidget(jLabel3, 0, Qt::AlignHCenter); // "General patterns:"
//    contentPane->layout()->addWidget(panel1);
    grid->addWidget(jLabel3,0,0,rowSpan,8, Qt::AlignHCenter);

    //contentPane->layout()->addWidget(new JLabel(" "));

//    JPanel* panel2 = new JPanel(new QHBoxLayout());
//    ((QHBoxLayout*)panel2->layout())->addWidget(jLabel1, 0, Qt::AlignRight); // "Code Button sensor:"
//    ((QHBoxLayout*)panel2->layout())->addWidget(_mCodeButtonInternalSensorPattern, 0, Qt::AlignLeft);
//    contentPane->layout()->addWidget(panel2);
    grid->addWidget(jLabel1, 1, 0, rowSpan, 2, Qt::AlignRight);
    grid->addWidget(_mCodeButtonInternalSensorPattern, 1, 2);

//    JPanel* panel3 = new JPanel(new QHBoxLayout());
//    ((QHBoxLayout*)panel3->layout())->addWidget(jLabel4, 0, Qt::AlignLeft);  //"Signal direction indicators patterns:"
//    ((QHBoxLayout*)panel3->layout())->addWidget(jLabel12, 0, Qt::AlignLeft); //"Switch direction indicators patterns:"
//    contentPane->layout()->addWidget(panel3);
    grid->addWidget(jLabel4, 3, 0, rowSpan, 2, Qt::AlignRight);
    grid->addWidget(jLabel12, 3, 3, rowSpan, 2, Qt::AlignLeft);

//    JPanel* panel4 = new JPanel(new QHBoxLayout());
//    JPanel* panel4l = new JPanel(new QHBoxLayout());
//    JPanel* panel4r = new JPanel(new QHBoxLayout());
//    ((QHBoxLayout*)panel4l->layout())->addWidget(jLabel5, 0, Qt::AlignRight); // "Left indicator sensor:"
//    ((QHBoxLayout*)panel4l->layout())->addWidget(_mSIDI_LeftInternalSensorPattern, 0, Qt::AlignRight);
//    panel4->layout()->addWidget(panel4l);
//    ((QHBoxLayout*)panel4r->layout())->addWidget(jLabel13, 0, Qt::AlignRight); // "Normal indicator sensor:"
//    ((QHBoxLayout*)panel4r->layout())->addWidget(_mSWDI_NormalInternalSensorPattern, 0, Qt::AlignRight);
//    panel4->layout()->addWidget(panel4r);
//    contentPaneLayout->addWidget(panel4);
    grid->addWidget(jLabel5, 4, 0, rowSpan,2, Qt::AlignRight);
    grid->addWidget(_mSIDI_LeftInternalSensorPattern, 4, 2);
    grid->addWidget(jLabel13, 4,3,rowSpan,2, Qt::AlignRight);
    grid->addWidget(_mSWDI_NormalInternalSensorPattern, 4, 5);

//    JPanel* panel5 = new JPanel(new QHBoxLayout());
//    JPanel* panel5l = new JPanel(new QHBoxLayout());
//    JPanel* panel5r = new JPanel(new QHBoxLayout());
//    ((QHBoxLayout*)panel5l->layout())->addWidget(jLabel6, 0, Qt::AlignRight); // "Normal indicator sensor:"
//    ((QHBoxLayout*)panel5l->layout())->addWidget(_mSIDI_NormalInternalSensorPattern, 0, Qt::AlignRight);
//    panel5->layout()->addWidget(panel5l);
//    ((QHBoxLayout*)panel5r->layout())->addWidget(jLabel14, 0, Qt::AlignRight); // "Reverse indicator sensor:"
//    ((QHBoxLayout*)panel5r->layout())->addWidget(_mSWDI_ReversedInternalSensorPattern, 0, Qt::AlignRight);
//    panel5->layout()->addWidget(panel5r);
//    contentPaneLayout->addWidget(panel5);
    grid->addWidget(jLabel6, 5, 0, rowSpan,2, Qt::AlignRight);
    grid->addWidget(_mSIDI_NormalInternalSensorPattern, 5, 2);
    grid->addWidget(jLabel14, 5,3,rowSpan,2, Qt::AlignRight);
    grid->addWidget(_mSWDI_ReversedInternalSensorPattern, 5, 5);


//    JPanel* panel6 = new JPanel(new QHBoxLayout());
//    JPanel* panel6l = new JPanel(new QHBoxLayout());
//    JPanel* panel6r = new JPanel(new QHBoxLayout());
//    ((QHBoxLayout*)panel6l->layout())->addWidget(jLabel7, 0, Qt::AlignRight); // "Right indicator sensor:"
//    ((QHBoxLayout*)panel6l->layout())->addWidget(_mSIDI_RightInternalSensorPattern, 0, Qt::AlignRight);
//    panel6->layout()->addWidget(panel6l);
//    panel6->layout()->addWidget(panel6r);
//    contentPaneLayout->addWidget(panel6);
    grid->addWidget(jLabel7, 6, 0, rowSpan,2, Qt::AlignRight);
    grid->addWidget(_mSIDI_RightInternalSensorPattern, 6, 2);

//    contentPane->layout()->addWidget(new JLabel(" "));

//    JPanel* panel7 = new JPanel(new QHBoxLayout());
//    ((QHBoxLayout*)panel7->layout())->addWidget(jLabel8, 0, Qt::AlignRight);  // "Signal direction levers patterns:"
//    ((QHBoxLayout*)panel7->layout())->addWidget(jLabel15);// Switch direction levers patterns:"
//    contentPane->layout()->addWidget(panel7);
    grid->addWidget(jLabel8, 7, 0, rowSpan, 2, Qt::AlignRight);
    grid->addWidget(jLabel15, 7, 3, rowSpan, 2, Qt::AlignLeft);

//    JPanel* panel8 = new JPanel(new QHBoxLayout());
//    JPanel* panel8l = new JPanel(new QHBoxLayout());
//    JPanel* panel8r = new JPanel(new QHBoxLayout());
//    ((QHBoxLayout*)panel8l->layout())->addWidget(jLabel9, 0, Qt::AlignRight); // "Left lever sensor:"
//    ((QHBoxLayout*)panel8l->layout())->addWidget(_mSIDL_LeftInternalSensorPattern, 0, Qt::AlignRight);
//     panel8->layout()->addWidget(panel8l);
//    ((QHBoxLayout*)panel8r->layout())->addWidget(jLabel16, 0, Qt::AlignRight); // "Lever sensor:"
//    ((QHBoxLayout*)panel8r->layout())->addWidget(_mSWDL_InternalSensorPattern, 0, Qt::AlignRight);
//    panel8->layout()->addWidget(panel8r);
//    contentPaneLayout->addWidget(panel8);
    grid->addWidget(jLabel9, 8, 0, rowSpan, 2, Qt::AlignRight);
    grid->addWidget(_mSIDL_LeftInternalSensorPattern, 8, 2);
    grid->addWidget(jLabel16, 8, 3, rowSpan, 2, Qt::AlignRight);
    grid->addWidget(_mSWDL_InternalSensorPattern, 8, 5, rowSpan, 2);

//    JPanel* panel9 = new JPanel(new QHBoxLayout());
//    JPanel* panel9l = new JPanel(new QHBoxLayout());
//    JPanel* panel9r = new JPanel(new QHBoxLayout());
//    ((QHBoxLayout*)panel9l->layout())->addWidget(jLabel10, 0, Qt::AlignRight); // "Normal lever sensor:"
//    ((QHBoxLayout*)panel9l->layout())->addWidget(_mSIDL_NormalInternalSensorPattern, 0, Qt::AlignRight);
//    panel9->layout()->addWidget(panel9l);
//    panel9->layout()->addWidget(panel9r);
//    contentPaneLayout->addWidget(panel9);
    grid->addWidget(jLabel10, 9, 0, rowSpan, 2, Qt::AlignRight);
    grid->addWidget(_mSIDL_NormalInternalSensorPattern, 9, 2, rowSpan, 1);


//    JPanel* panel10 = new JPanel(new QHBoxLayout());
//    JPanel* panel10l = new JPanel(new QHBoxLayout());
//    JPanel* panel10r = new JPanel(new QHBoxLayout());
//    ((QHBoxLayout*)panel10l->layout())->addWidget(jLabel11, 0, Qt::AlignRight); // "Right lever sensor:"
//    ((QHBoxLayout*)panel10l->layout())->addWidget(_mSIDL_RightInternalSensorPattern, 0, Qt::AlignRight);
//     panel10->layout()->addWidget(panel10l);
//    ((QHBoxLayout*)panel10r->layout())->addWidget(jLabel20, 0, Qt::AlignRight); // "Call-on patterns:"
//    ((QHBoxLayout*)panel10r->layout())->addWidget(new JLabel(" ")); //
//    panel10->layout()->addWidget(panel10r);
//    contentPaneLayout->addWidget(panel10);
    grid->addWidget(jLabel11, 10, 0, rowSpan, 2, Qt::AlignRight);
    grid->addWidget(_mSIDL_RightInternalSensorPattern, 10, 2, rowSpan, 1, Qt::AlignRight);
    grid->addWidget(jLabel20, 10, 3, rowSpan, 2, Qt::AlignRight);


//    JPanel* panel11 = new JPanel(new QHBoxLayout());
//    JPanel* panel11l = new JPanel(new QHBoxLayout());
//    panel11l->layout()->addWidget(Box::createHorizontalStrut(150));
//    panel11->layout()->addWidget(panel11l);
//    JPanel* panel11r = new JPanel(new QHBoxLayout());
//    ((QHBoxLayout*)panel11r->layout())->addWidget(jLabel28);       // "Toggle sensor:"
//    ((QHBoxLayout*)panel11r->layout())->addWidget(_mCO_CallOnToggleInternalSensorPattern);
//    panel11->layout()->addWidget(panel11r);
//    contentPaneLayout->addWidget(panel11);
    grid->addWidget(jLabel28, 11, 4, rowSpan,1,Qt::AlignRight);
    grid->addWidget(_mCO_CallOnToggleInternalSensorPattern, 11, 5);

//    JPanel* panel12 = new JPanel(new QHBoxLayout());
//    JPanel* panel12a = new JPanel(new QHBoxLayout());
//    ((QHBoxLayout*)panel12a->layout())->addWidget(jLabel30, 0, Qt::AlignLeft); // "Turnout lock patterns:"
//    ((QHBoxLayout*)panel12a->layout())->addWidget(new JLabel(" "), 0, Qt::AlignRight);
//    panel12->layout()->addWidget(panel12a);
//    contentPaneLayout->addWidget(panel12);
    grid->addWidget(jLabel30, 12, 1, rowSpan, 1, Qt::AlignRight);

//    JPanel* panel13 = new JPanel(new QHBoxLayout());
//    JPanel* panel13a = new JPanel(new QHBoxLayout());
//    ((QHBoxLayout*)panel13a->layout())->addWidget(jLabel31, 0, Qt::AlignLeft); // Lock toggle sensor:"
//    ((QHBoxLayout*)panel13a->layout())->addWidget(_mTUL_DispatcherInternalSensorLockTogglePattern, 0, Qt::AlignLeft);
//    panel13->layout()->addWidget(panel13a);
//    contentPaneLayout->addWidget(panel13);
    grid->addWidget(jLabel31, 13, 1, rowSpan,1, Qt::AlignRight);
    grid->addWidget(_mTUL_DispatcherInternalSensorLockTogglePattern, 13, 2, rowSpan, 2);

//    JPanel* panel114 = new JPanel(new QHBoxLayout());
//    JPanel* panel114a = new JPanel(new QHBoxLayout());
//    ((QHBoxLayout*)panel114a->layout())->addWidget(jLabel32, 0, Qt::AlignLeft); // "Unlocked indicator sensor:"
//    ((QHBoxLayout*)panel114a->layout())->addWidget(_mTUL_DispatcherInternalSensorUnlockedIndicatorPattern, 0, Qt::AlignLeft);
//    panel114->layout()->addWidget(panel114a);
//    contentPaneLayout->addWidget(panel114);
    grid->addWidget(jLabel32, 14, 1, rowSpan,1, Qt::AlignRight);
    grid->addWidget(_mTUL_DispatcherInternalSensorUnlockedIndicatorPattern, 14, 2, rowSpan, 2);

//    JPanel* panel15 = new JPanel(new QVBoxLayout());
//    JPanel* panel15a = new JPanel(new FlowLayout());
//    panel15a->layout()->addWidget(_mSaveAndClose);
//    panel15->layout()->addWidget(panel15a);
//    contentPaneLayout->addWidget(panel15);
    grid->addWidget(_mSaveAndClose, 16, 2, rowSpan, 1);

#endif
    pack();
}// </editor-fold>

/*private*/ void FrmPatterns::formWindowClosing(QCloseEvent* evt) {
    _mAwtWindowProperties->saveWindowState(this, FORM_PROPERTIES);
    if ( CommonSubs::allowClose(this, dataChanged())) dispose();
}

/*private*/ void FrmPatterns::_mSaveAndCloseActionPerformed(/*java.awt.event.ActionEvent evt*/) {
    _mProgramProperties->_mCodeButtonInternalSensorPattern = _mCodeButtonInternalSensorPattern->text();
    _mProgramProperties->_mSIDI_LeftInternalSensorPattern = _mSIDI_LeftInternalSensorPattern->text();
    _mProgramProperties->_mSIDI_NormalInternalSensorPattern = _mSIDI_NormalInternalSensorPattern->text();
    _mProgramProperties->_mSIDI_RightInternalSensorPattern = _mSIDI_RightInternalSensorPattern->text();
    _mProgramProperties->_mSIDL_LeftInternalSensorPattern = _mSIDL_LeftInternalSensorPattern->text();
    _mProgramProperties->_mSIDL_NormalInternalSensorPattern = _mSIDL_NormalInternalSensorPattern->text();
    _mProgramProperties->_mSIDL_RightInternalSensorPattern = _mSIDL_RightInternalSensorPattern->text();
    _mProgramProperties->_mSWDI_NormalInternalSensorPattern = _mSWDI_NormalInternalSensorPattern->text();
    _mProgramProperties->_mSWDI_ReversedInternalSensorPattern = _mSWDI_ReversedInternalSensorPattern->text();
    _mProgramProperties->_mSWDL_InternalSensorPattern = _mSWDL_InternalSensorPattern->text();
    _mProgramProperties->_mCO_CallOnToggleInternalSensorPattern = _mCO_CallOnToggleInternalSensorPattern->text();
    _mProgramProperties->_mTUL_DispatcherInternalSensorLockTogglePattern = _mTUL_DispatcherInternalSensorLockTogglePattern->text();
    _mProgramProperties->_mTUL_DispatcherInternalSensorUnlockedIndicatorPattern = _mTUL_DispatcherInternalSensorUnlockedIndicatorPattern->text();
    _mClosedNormally = true;
    _mAwtWindowProperties->saveWindowState(this, FORM_PROPERTIES);
    dispose();
}

