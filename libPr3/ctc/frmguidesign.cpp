#include "frmguidesign.h"
#include "jformattedtextfield.h"
#include <QRadioButton>
/**
 *
 * @author Gregory J. Bedlek Copyright (C) 2018, 2019
 */
// /*public*/ class FrmGUIDesign extends JFrame {

/*
 * Creates new form dlgProperties
 */
/*private*/ /*static*/ /*final*/ QString FrmGUIDesign::FORM_PROPERTIES = "DlgGUIDesign";   // NOI18N

/*private*/ void FrmGUIDesign::initOrig(OtherData* otherData) {
    _mGUIDesign_NumberOfEmptyColumnsAtEndOrig = otherData->_mGUIDesign_NumberOfEmptyColumnsAtEnd;
    _mGUIDesign_CTCPanelTypeOrig = _mOtherData->_mGUIDesign_CTCPanelType;
    _mGUIDesign_BuilderPlateOrig = _mOtherData->_mGUIDesign_BuilderPlate;
    _mGUIDesign_SignalsOnPanelOrig = _mOtherData->_mGUIDesign_SignalsOnPanel;
    _mGUIDesign_FleetingToggleSwitchOrig = _mOtherData->_mGUIDesign_FleetingToggleSwitch;
    _mGUIDesign_AnalogClockEtcOrig = _mOtherData->_mGUIDesign_AnalogClockEtc;
    _mGUIDesign_ReloadCTCSystemButtonOrig = _mOtherData->_mGUIDesign_ReloadCTCSystemButton;
    _mGUIDesign_CTCDebugOnToggleOrig = _mOtherData->_mGUIDesign_CTCDebugOnToggle;
    _mGUIDesign_CreateTrackPiecesOrig = _mOtherData->_mGUIDesign_CreateTrackPieces;
    _mGUIDesign_VerticalSizeOrig = _mOtherData->_mGUIDesign_VerticalSize;
    _mGUIDesign_OSSectionUnknownInconsistentRedBlinkOrig = _mOtherData->_mGUIDesign_OSSectionUnknownInconsistentRedBlink;
    _mGUIDesign_TurnoutsOnPanelOrig = _mOtherData->_mGUIDesign_TurnoutsOnPanel;
}

/*private*/ bool FrmGUIDesign::dataChanged() {
    if (CommonSubs::getIntFromJTextFieldNoThrow(_mGUIDesign_NumberOfEmptyColumnsAtEnd) != _mGUIDesign_NumberOfEmptyColumnsAtEndOrig) return true;
    if (_mGUIDesign_CTCPanelTypeOrig != OtherData::CTC_PANEL_TYPE::getRadioGroupValue(ProjectsCommonSubs::getButtonSelectedInt(_mGUIDesign_CTCPanelType))) return true;
    if (_mGUIDesign_BuilderPlateOrig != _mGUIDesign_BuilderPlate->isChecked()) return true;
    if (_mGUIDesign_SignalsOnPanelOrig != OtherData::SIGNALS_ON_PANEL::getRadioGroupValue(ProjectsCommonSubs::getButtonSelectedInt(_mGUIDesign_SignalsOnPanel))) return true;
    if (_mGUIDesign_FleetingToggleSwitchOrig != _mGUIDesign_FleetingToggleSwitch->isChecked()) return true;
    if (_mGUIDesign_AnalogClockEtcOrig != _mGUIDesign_AnalogClockEtc->isChecked()) return true;
    if (_mGUIDesign_ReloadCTCSystemButtonOrig != _mGUIDesign_ReloadCTCSystemButton->isChecked()) return true;
    if (_mGUIDesign_CTCDebugOnToggleOrig != _mGUIDesign_CTCDebugOnToggle->isChecked()) return true;
    if (_mGUIDesign_CreateTrackPiecesOrig != _mGUIDesign_CreateTrackPieces->isChecked()) return true;
    if (_mGUIDesign_VerticalSizeOrig != OtherData::VERTICAL_SIZE::getRadioGroupValue(ProjectsCommonSubs::getButtonSelectedInt(_mGUIDesign_VerticalSize))) return true;
    if (_mGUIDesign_OSSectionUnknownInconsistentRedBlinkOrig != _mGUIDesign_OSSectionUnknownInconsistentRedBlink->isChecked()) return true;
    if (_mGUIDesign_TurnoutsOnPanelOrig != _mGUIDesign_TurnoutsOnPanel->isChecked()) return true;
    return false;
}

/*public*/ FrmGUIDesign::FrmGUIDesign(AwtWindowProperties* awtWindowProperties, OtherData* otherData, QWidget* parent)
 : JFrame(parent)
{
    //super();
    initComponents();
    CommonSubs::addHelpMenu(this, "package.jmri.jmrit.ctc.CTC_menuCfgGui", true);  // NOI18N
    _mAwtWindowProperties = awtWindowProperties;
    _mOtherData = otherData;

    _mGUIDesign_NumberOfEmptyColumnsAtEnd->setText(QString::number(_mOtherData->_mGUIDesign_NumberOfEmptyColumnsAtEnd));
    CommonSubs::numberButtonGroup(_mGUIDesign_CTCPanelType);
    CommonSubs::setButtonSelected(_mGUIDesign_CTCPanelType, _mOtherData->_mGUIDesign_CTCPanelType.getRadioGroupValue());
    _mGUIDesign_BuilderPlate->setChecked(otherData->_mGUIDesign_BuilderPlate);
    CommonSubs::numberButtonGroup(_mGUIDesign_SignalsOnPanel);
    CommonSubs::setButtonSelected(_mGUIDesign_SignalsOnPanel, _mOtherData->_mGUIDesign_SignalsOnPanel.getRadioGroupValue());
    _mGUIDesign_FleetingToggleSwitch->setChecked(otherData->_mGUIDesign_FleetingToggleSwitch);
    _mGUIDesign_AnalogClockEtc->setChecked(otherData->_mGUIDesign_AnalogClockEtc);
    _mGUIDesign_ReloadCTCSystemButton->setChecked(otherData->_mGUIDesign_ReloadCTCSystemButton);
    _mGUIDesign_CTCDebugOnToggle->setChecked(otherData->_mGUIDesign_CTCDebugOnToggle);
    _mGUIDesign_CreateTrackPieces->setChecked(otherData->_mGUIDesign_CreateTrackPieces);
    CommonSubs::numberButtonGroup(_mGUIDesign_VerticalSize);
    CommonSubs::setButtonSelected(_mGUIDesign_VerticalSize, _mOtherData->_mGUIDesign_VerticalSize.getRadioGroupValue());
    _mGUIDesign_OSSectionUnknownInconsistentRedBlink->setChecked(otherData->_mGUIDesign_OSSectionUnknownInconsistentRedBlink);
    _mGUIDesign_TurnoutsOnPanel->setChecked(otherData->_mGUIDesign_TurnoutsOnPanel);
    initOrig(otherData);
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
/*private*/ void FrmGUIDesign::initComponents() {

    _mGUIDesign_CTCPanelType = new QButtonGroup();
    _mGUIDesign_SignalsOnPanel = new QButtonGroup();
    _mGUIDesign_VerticalSize = new QButtonGroup();
    _mGUIDesign_NumberOfEmptyColumnsAtEnd = new JFormattedTextField();
    jLabel19 = new JLabel();
    _mSaveAndClose = new JButton();
    _mAllSignals = new QRadioButton();
    _mGreenOffOnly = new QRadioButton();
    jLabel1 = new JLabel();
    _mNone = new QRadioButton();
    jRadioButton1 = new QRadioButton();
    jRadioButton2 = new QRadioButton();
    jLabel2 = new JLabel();
    jLabel3 = new JLabel();
    _mGUIDesign_BuilderPlate = new JCheckBox();
    _mGUIDesign_ReloadCTCSystemButton = new JCheckBox();
    _mGUIDesign_CTCDebugOnToggle = new JCheckBox();
    _mGUIDesign_FleetingToggleSwitch = new JCheckBox();
    _mGUIDesign_AnalogClockEtc = new JCheckBox();
    _mGUIDesign_CreateTrackPieces = new JCheckBox();
    jRadioButton3 = new QRadioButton();
    jRadioButton4 = new QRadioButton();
    jRadioButton5 = new QRadioButton();
    jLabel4 = new JLabel();
    _mGUIDesign_OSSectionUnknownInconsistentRedBlink = new JCheckBox();
    jLabel5 = new JLabel();
    jLabel6 = new JLabel();
    _mGUIDesign_TurnoutsOnPanel = new JCheckBox();

    setDefaultCloseOperation(JFrame::DO_NOTHING_ON_CLOSE);
    setTitle(tr("CTC GUI Design"));
//    addWindowListener(new java.awt.event.WindowAdapter() {
//        @Override
//        /*public*/ void windowClosing(java.awt.event.WindowEvent evt) {
//            formWindowClosing(evt);
//        }
//    });
    addWindowListener(new FrmGUIDesign_windowListener(this));

    //_mGUIDesign_NumberOfEmptyColumnsAtEnd->setFormatterFactory(new DefaultFormatterFactory(new NumberFormatter(new DecimalFormat("#0"))));
    _mGUIDesign_NumberOfEmptyColumnsAtEnd->setValidator(new QIntValidator());

    jLabel19->setText(tr("Extra blank columns after last defined column to create:"));

    _mSaveAndClose->setText(tr("Save and Close"));
//    _mSaveAndClose.addActionListener(new java.awt.event.ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(/*java.awt.event.ActionEvent evt*/ {
    connect(_mSaveAndClose, &JButton::clicked, [=]{
            _mSaveAndCloseActionPerformed(/*evt*/);
//        }
    });

    _mGUIDesign_SignalsOnPanel->addButton(_mAllSignals);
    _mAllSignals->setText(tr("All O.S. section signals"));

    _mGUIDesign_SignalsOnPanel->addButton(_mGreenOffOnly);
    _mGreenOffOnly->setText(tr("Green/off only (Future feature)"));
    _mGreenOffOnly->setEnabled(false);

    jLabel1->setText(tr("Prototype selections:"));

    _mGUIDesign_SignalsOnPanel->addButton(_mNone);
    _mNone->setText(tr("None"));

    _mGUIDesign_CTCPanelType->addButton(jRadioButton1);
    jRadioButton1->setText(tr("USS"));

    _mGUIDesign_CTCPanelType->addButton(jRadioButton2);
    jRadioButton2->setText(tr("Other (Future)"));
    jRadioButton2->setEnabled(false);

    jLabel2->setText(tr("Type of CTC panel:"));

    jLabel3->setText(tr("Signals on panel:"));

    _mGUIDesign_BuilderPlate->setText(tr("Builder Plate"));

    _mGUIDesign_ReloadCTCSystemButton->setText(tr("Reload CTC system button"));

    _mGUIDesign_CTCDebugOnToggle->setText(tr("CTC Debug on toggle"));

    _mGUIDesign_FleetingToggleSwitch->setText(tr("Fleeting toggle switch (only if fleeting configured)"));

    _mGUIDesign_AnalogClockEtc->setText(tr("Analog clock and clock on toggle"));

    _mGUIDesign_CreateTrackPieces->setText(tr("Create variety of track pieces"));
    _mGUIDesign_CreateTrackPieces->setEnabled(false);

    _mGUIDesign_VerticalSize->addButton(jRadioButton3);
    jRadioButton3->setText(tr("718 pixels"));

    _mGUIDesign_VerticalSize->addButton(jRadioButton4);
    jRadioButton4->setText(tr("850 pixels"));

    jRadioButton5->setText(tr("900 pixels"));
    _mGUIDesign_VerticalSize->addButton(jRadioButton5);

    jLabel4->setText(tr("Vertical size:"));

    _mGUIDesign_OSSectionUnknownInconsistentRedBlink->setText(tr("O.S. Occupancy sensor blinks red"));

    jLabel5->setText(tr("when unknown or inconsistent"));

    jLabel6->setText(tr("Turnouts on panel:"));

    _mGUIDesign_TurnoutsOnPanel->setText(tr("Generate"));
#if 0
    GroupLayout layout = new GroupLayout(getContentPane());
    getContentPane()->setLayout(layout);
    layout->setHorizontalGroup(
        layout.createParallelGroup(GroupLayout.Alignment.LEADING)
        .addGroup(layout.createSequentialGroup()
            .addGap(138, 138, 138)
            .addComponent(_mSaveAndClose)
            .addGap(0, 0, Short.MAX_VALUE))
        .addGroup(layout.createSequentialGroup()
            .addGap(20, 20, 20)
            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                .addGroup(layout.createSequentialGroup()
                    .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                        .addComponent(_mGUIDesign_FleetingToggleSwitch)
                        .addComponent(_mGUIDesign_AnalogClockEtc)
                        .addGroup(layout.createSequentialGroup()
                            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING, false)
                                .addGroup(layout.createSequentialGroup()
                                    .addComponent(jLabel2)
                                    .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                                    .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                                        .addComponent(jRadioButton2)
                                        .addGroup(layout.createSequentialGroup()
                                            .addComponent(jRadioButton1)
                                            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                            .addComponent(jLabel4))))
                                .addComponent(jLabel19))
                            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                                .addComponent(_mGUIDesign_NumberOfEmptyColumnsAtEnd, GroupLayout.PREFERRED_SIZE, 50, GroupLayout.PREFERRED_SIZE)
                                .addComponent(jRadioButton3)
                                .addComponent(jRadioButton4)
                                .addComponent(jRadioButton5)
                                .addComponent(_mGUIDesign_BuilderPlate)))
                        .addGroup(layout.createSequentialGroup()
                            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                                .addComponent(_mGUIDesign_ReloadCTCSystemButton)
                                .addComponent(_mGUIDesign_CreateTrackPieces))
                            .addGap(18, 18, 18)
                            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                                .addComponent(_mGUIDesign_CTCDebugOnToggle)
                                .addComponent(_mGUIDesign_OSSectionUnknownInconsistentRedBlink)
                                .addGroup(layout.createSequentialGroup()
                                    .addGap(21, 21, 21)
                                    .addComponent(jLabel5)))))
                    .addGap(0, 99, Short.MAX_VALUE))
                .addGroup(layout.createSequentialGroup()
                    .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                        .addGroup(layout.createSequentialGroup()
                            .addGap(10, 10, 10)
                            .addComponent(jLabel3))
                        .addComponent(jLabel6, GroupLayout.Alignment.TRAILING))
                    .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                    .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                        .addComponent(_mGreenOffOnly)
                        .addComponent(_mNone)
                        .addComponent(_mAllSignals)
                        .addComponent(jLabel1)
                        .addComponent(_mGUIDesign_TurnoutsOnPanel))
                    .addContainerGap(GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))))
    );
    layout->setVerticalGroup(
        layout.createParallelGroup(GroupLayout.Alignment.LEADING)
        .addGroup(layout.createSequentialGroup()
            .addContainerGap()
            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                .addComponent(_mGUIDesign_NumberOfEmptyColumnsAtEnd, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                .addComponent(jLabel19))
            .addGap(18, 18, 18)
            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                .addComponent(jRadioButton1)
                .addComponent(jLabel2)
                .addComponent(jRadioButton3)
                .addComponent(jLabel4))
            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                .addComponent(jRadioButton2)
                .addComponent(jRadioButton4))
            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
            .addComponent(jRadioButton5)
            .addGap(20, 20, 20)
            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                .addComponent(_mAllSignals)
                .addComponent(jLabel3)
                .addComponent(_mGUIDesign_BuilderPlate))
            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
            .addComponent(jLabel1)
            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
            .addComponent(_mGreenOffOnly)
            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
            .addComponent(_mNone)
            .addGap(18, 18, 18)
            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                .addComponent(_mGUIDesign_TurnoutsOnPanel)
                .addComponent(jLabel6))
            .addGap(34, 34, 34)
            .addComponent(_mGUIDesign_FleetingToggleSwitch)
            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
            .addComponent(_mGUIDesign_AnalogClockEtc)
            .addGap(18, 18, 18)
            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                .addComponent(_mGUIDesign_ReloadCTCSystemButton, GroupLayout.PREFERRED_SIZE, 23, GroupLayout.PREFERRED_SIZE)
                .addComponent(_mGUIDesign_CTCDebugOnToggle))
            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                .addComponent(_mGUIDesign_CreateTrackPieces)
                .addComponent(_mGUIDesign_OSSectionUnknownInconsistentRedBlink))
            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
            .addComponent(jLabel5)
            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED, 14, Short.MAX_VALUE)
            .addComponent(_mSaveAndClose)
            .addGap(19, 19, 19))
    );
#else
    JPanel* contentPane = new JPanel();
    QGridLayout* grid;
    contentPane->setLayout(grid = new QGridLayout());
    setCentralWidget(contentPane);

    JPanel* panel1 = new JPanel(new QHBoxLayout());
    panel1->layout()->addWidget(jLabel19);
    panel1->layout()->addWidget(_mGUIDesign_NumberOfEmptyColumnsAtEnd);
    grid->addWidget(panel1, 0,0);

    grid->addWidget(jLabel2, 2, 0, 1,1, Qt::AlignRight);
    grid->addWidget(jRadioButton1, 2, 1);
    grid->addWidget(jLabel4, 2, 2, 1, 1);
    grid->addWidget(jRadioButton3, 2, 4); //718

    grid->addWidget(jRadioButton2, 3, 1);
    grid->addWidget(jRadioButton4, 3, 4);

    grid->addWidget(jRadioButton5, 4, 4);

    grid->addWidget(jLabel3, 6, 0, 1, 1, Qt::AlignRight); // "Signals on panel:"
    grid->addWidget(_mAllSignals, 6, 1);
    grid->addWidget(_mGUIDesign_BuilderPlate, 6, 4);

    grid->addWidget(jLabel1, 7, 1, 1,1, Qt::AlignLeft); // "Prototype selections:"

    grid->addWidget(_mGreenOffOnly, 8, 1);

    grid->addWidget(_mNone, 9, 1);

    grid->addWidget(jLabel6, 11, 0, 1.1, Qt::AlignRight);
    grid->addWidget(_mGUIDesign_TurnoutsOnPanel, 11,1);

    grid->addWidget(_mGUIDesign_FleetingToggleSwitch, 14, 0);
    grid->addWidget(_mGUIDesign_AnalogClockEtc, 15, 0);

    grid->addWidget(_mGUIDesign_ReloadCTCSystemButton, 17, 0);
    grid->addWidget(_mGUIDesign_CTCDebugOnToggle, 17,2);

    grid->addWidget(_mGUIDesign_CreateTrackPieces, 18,0);
    grid->addWidget(_mGUIDesign_OSSectionUnknownInconsistentRedBlink, 18, 2);
    grid->addWidget(jLabel5, 19, 2);

    grid->addWidget(_mSaveAndClose, 20, 2);
#endif
    pack();
}// </editor-fold>

/*private*/ void FrmGUIDesign::formWindowClosing(QCloseEvent* evt) {
    _mAwtWindowProperties->saveWindowState(this, FORM_PROPERTIES);
    if (CommonSubs::allowClose(this, dataChanged())) dispose();
}

/*private*/ void FrmGUIDesign::_mSaveAndCloseActionPerformed(/*java.awt.event.ActionEvent evt*/) {
    _mOtherData->_mGUIDesign_NumberOfEmptyColumnsAtEnd = _mGUIDesign_NumberOfEmptyColumnsAtEnd->text().toInt();
    _mOtherData->_mGUIDesign_CTCPanelType = OtherData::CTC_PANEL_TYPE::getRadioGroupValue(ProjectsCommonSubs::getButtonSelectedInt(_mGUIDesign_CTCPanelType));
    _mOtherData->_mGUIDesign_BuilderPlate = _mGUIDesign_BuilderPlate->isChecked();
    _mOtherData->_mGUIDesign_SignalsOnPanel = OtherData::SIGNALS_ON_PANEL::getRadioGroupValue(ProjectsCommonSubs::getButtonSelectedInt(_mGUIDesign_SignalsOnPanel));
    _mOtherData->_mGUIDesign_FleetingToggleSwitch = _mGUIDesign_FleetingToggleSwitch->isChecked();
    _mOtherData->_mGUIDesign_AnalogClockEtc = _mGUIDesign_AnalogClockEtc->isChecked();
    _mOtherData->_mGUIDesign_ReloadCTCSystemButton = _mGUIDesign_ReloadCTCSystemButton->isChecked();
    _mOtherData->_mGUIDesign_CTCDebugOnToggle = _mGUIDesign_CTCDebugOnToggle->isChecked();
    _mOtherData->_mGUIDesign_CreateTrackPieces = _mGUIDesign_CreateTrackPieces->isChecked();
    _mOtherData->_mGUIDesign_VerticalSize = OtherData::VERTICAL_SIZE::getRadioGroupValue(ProjectsCommonSubs::getButtonSelectedInt(_mGUIDesign_VerticalSize));
    _mOtherData->_mGUIDesign_OSSectionUnknownInconsistentRedBlink = _mGUIDesign_OSSectionUnknownInconsistentRedBlink->isChecked();
    _mOtherData->_mGUIDesign_TurnoutsOnPanel = _mGUIDesign_TurnoutsOnPanel->isChecked();
    _mClosedNormally = true;
    _mAwtWindowProperties->saveWindowState(this, FORM_PROPERTIES);
    dispose();
}

