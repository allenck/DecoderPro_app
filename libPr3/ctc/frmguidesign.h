#ifndef FRMGUIDESIGN_H
#define FRMGUIDESIGN_H
#include "jframe.h"
#include "otherdata.h"
#include "commonsubs.h"
#include "awtwindowproperties.h"
#include "jcheckbox.h"
#include "windowadapter.h"

class QRadioButton;
class FrmGUIDesign : public JFrame
{
  Q_OBJECT
 public:
  /*public*/ FrmGUIDesign(AwtWindowProperties* awtWindowProperties, OtherData* otherData, QWidget* parent = nullptr);


 private:
  // Variables declaration - do not modify
  /*private*/ QRadioButton* _mAllSignals;
  /*private*/ JCheckBox* _mGUIDesign_AnalogClockEtc;
  /*private*/ JCheckBox* _mGUIDesign_BuilderPlate;
  /*private*/ JCheckBox* _mGUIDesign_CTCDebugOnToggle;
  /*private*/ QButtonGroup* _mGUIDesign_CTCPanelType;
  /*private*/ JCheckBox* _mGUIDesign_CreateTrackPieces;
  /*private*/ JCheckBox* _mGUIDesign_FleetingToggleSwitch;
  /*private*/ JFormattedTextField* _mGUIDesign_NumberOfEmptyColumnsAtEnd;
  /*private*/ JCheckBox* _mGUIDesign_OSSectionUnknownInconsistentRedBlink;
  /*private*/ JCheckBox* _mGUIDesign_ReloadCTCSystemButton;
  /*private*/ QButtonGroup* _mGUIDesign_SignalsOnPanel;
  /*private*/ JCheckBox* _mGUIDesign_TurnoutsOnPanel;
  /*private*/ QButtonGroup* _mGUIDesign_VerticalSize;
  /*private*/ QRadioButton* _mGreenOffOnly;
  /*private*/ QRadioButton* _mNone;
  /*private*/ JButton* _mSaveAndClose;
  /*private*/ JLabel* jLabel1;
  /*private*/ JLabel* jLabel19;
  /*private*/ JLabel* jLabel2;
  /*private*/ JLabel* jLabel3;
  /*private*/ JLabel* jLabel4;
  /*private*/ JLabel* jLabel5;
  /*private*/ JLabel* jLabel6;
  /*private*/ QRadioButton* jRadioButton1;
  /*private*/ QRadioButton* jRadioButton2;
  /*private*/ QRadioButton* jRadioButton3;
  /*private*/ QRadioButton* jRadioButton4;
  /*private*/ QRadioButton* jRadioButton5;
  // End of variables declaration
  /*private*/ static /*final*/ QString FORM_PROPERTIES;// = "DlgGUIDesign";   // NOI18N
  /*private*/ /*final*/ AwtWindowProperties* _mAwtWindowProperties;
  /*private*/ /*final*/ OtherData* _mOtherData;
  /*private*/ bool _mClosedNormally = false;
  /*public*/ bool closedNormally() { return _mClosedNormally; }

  /*private*/ int _mGUIDesign_NumberOfEmptyColumnsAtEndOrig;
  /*private*/ OtherData::CTC_PANEL_TYPE   _mGUIDesign_CTCPanelTypeOrig;
  /*private*/ bool  _mGUIDesign_BuilderPlateOrig;
  /*private*/ OtherData::SIGNALS_ON_PANEL _mGUIDesign_SignalsOnPanelOrig;
  /*private*/ bool  _mGUIDesign_FleetingToggleSwitchOrig;
  /*private*/ bool  _mGUIDesign_AnalogClockEtcOrig;
  /*private*/ bool  _mGUIDesign_ReloadCTCSystemButtonOrig;
  /*private*/ bool  _mGUIDesign_CTCDebugOnToggleOrig;
  /*private*/ bool  _mGUIDesign_CreateTrackPiecesOrig;
  /*private*/ OtherData::VERTICAL_SIZE _mGUIDesign_VerticalSizeOrig;
  /*private*/ bool  _mGUIDesign_OSSectionUnknownInconsistentRedBlinkOrig;
  /*private*/ bool  _mGUIDesign_TurnoutsOnPanelOrig;
  /*private*/ void initOrig(OtherData* otherData);
  /*private*/ bool dataChanged();
  /*private*/ void initComponents();
  /*private*/ void formWindowClosing(QCloseEvent* evt);

 private slots:
  /*private*/ void _mSaveAndCloseActionPerformed(/*java.awt.event.ActionEvent evt*/);


  friend class FrmGUIDesign_windowListener;
};

class FrmGUIDesign_windowListener : public WindowAdapter
{
  Q_OBJECT
  FrmGUIDesign* dlg;
 public:
  FrmGUIDesign_windowListener(FrmGUIDesign* dlg) {this->dlg = dlg;}
  //@Override
  /*public*/ void windowClosing(QCloseEvent* evt) {
      dlg->formWindowClosing(evt);
  }
};

#endif // FRMGUIDESIGN_H
