#ifndef FRMSIDI_H
#define FRMSIDI_H
#include "jframe.h"
#include <QRadioButton>
#include "jformattedtextfield.h"
#include "jlabel.h"
#include "jcombobox.h"
#include "jbutton.h"
#include "jtable.h"
#include "awtwindowproperties.h"
#include "codebuttonhandlerdata.h"
#include "programproperties.h"
#include "checkjmriobject.h"
#include "defaulttablemodel.h"
#include "windowadapter.h"

class FrmSIDI : public JFrame
{
  Q_OBJECT
 public:
  /*public*/ FrmSIDI( AwtWindowProperties* awtWindowProperties, CodeButtonHandlerData* codeButtonHandlerData,
                  ProgramProperties* programProperties, CheckJMRIObject* checkJMRIObject,
                  bool signalHeadSelected, QWidget* parent = nullptr);

  /*public*/ bool closedNormally() { return _mClosedNormally; }
  /*public*/ static bool dialogCodeButtonHandlerDataValid(CheckJMRIObject* checkJMRIObject, CodeButtonHandlerData* codeButtonHandlerData);
  /*public*/ void enableSignalListComboBox(JTable* table);

 private:
  // Variables declaration - do not modify
  /*private*/ QRadioButton* _mSIDI_BothTrafficButton;
  /*private*/ JFormattedTextField* _mSIDI_CodingAndResponseTime;
  /*private*/ JButton* _mSIDI_CompactListsButton;
  /*private*/ JLabel* _mSIDI_CompactListsLabel;
  /*private*/ JLabel* _mSIDI_LableCodeTimeLabel;
  /*private*/ JComboBox* _mSIDI_LeftInternalSensor;
  /*private*/ JLabel* _mSIDI_LeftInternalSensorPrompt;
  /*private*/ JPanel* _mSIDI_LeftRightSignals;
  /*private*/ QRadioButton* _mSIDI_LeftTrafficButton;
  /*private*/ JLabel* _mSIDI_LockTimeLabel;
  /*private*/ JComboBox* _mSIDI_NormalInternalSensor;
  /*private*/ JLabel* _mSIDI_NormalInternalSensorPrompt;
  /*private*/ JButton* _mSIDI_ReapplyPatterns;
  /*private*/ JComboBox* _mSIDI_RightInternalSensor;
  /*private*/ JLabel* _mSIDI_RightInternalSensorPrompt;
  /*private*/ JPanel* _mSIDI_RightLeftSignals;
  /*private*/ QRadioButton* _mSIDI_RightTrafficButton;
  /*private*/ JLabel* _mSIDI_SaveCloseLabel;
  /*private*/ JTable* _mSIDI_TableOfLeftToRightTrafficExternalSignalNames;
  /*private*/ JTable* _mSIDI_TableOfRightToLeftTrafficExternalSignalNames;
  /*private*/ JFormattedTextField* _mSIDI_TimeLockingInterval;
  /*private*/ QButtonGroup* _mSIDI_TrafficDirection;
  /*private*/ JPanel* _mSIDI_TrafficDirectionGroupPanel;
  /*private*/ JButton* _mSaveAndClose;
  /*private*/ JLabel* _mTableOfLeftToRightTrafficSignalNamesPrompt;
  /*private*/ JLabel* _mTableOfRightToLeftTrafficSignalNamesPrompt;
  /*private*/ JLabel* jLabel1;
//    /*private*/ JScrollPane jScrollPane1;
//    /*private*/ JScrollPane jScrollPane2;
  /*private*/ JPanel* panelLeftColumn;
  // End of variables declaration
  /*private*/ static /*final*/ QString FORM_PROPERTIES;// = "DlgSIDI";    // NOI18N
  /*private*/ static /*final*/ QString PREFIX;// = "_mSIDI_";             // NOI18N
  /*private*/ /*final*/ AwtWindowProperties* _mAwtWindowProperties;
  /*private*/ bool _mClosedNormally = false;
  /*private*/ /*final*/ CodeButtonHandlerData* _mCodeButtonHandlerData;
  /*private*/ /*final*/ ProgramProperties* _mProgramProperties;
  /*private*/ /*final*/ CheckJMRIObject* _mCheckJMRIObject;
  /*private*/ /*final*/ bool _mSignalHeadSelected;
  /*private*/ CodeButtonHandlerData::TRAFFIC_DIRECTION _mSIDI_TrafficDirectionTemp;

  /*private*/ int _mSIDI_CodingAndResponseTimeOrig;
  /*private*/ int _mSIDI_TimeLockingIntervalOrig;
  /*private*/ CodeButtonHandlerData::TRAFFIC_DIRECTION _mSIDI_TrafficDirectionOrig;
  /*private*/ QList<QString> _mLeftRightTrafficSignalsArrayListOrig = QList<QString>();
  /*private*/ QList<QString> _mRightLeftTrafficSignalsArrayListOrig = QList<QString>();
  /*private*/ /*final*/ DefaultTableModel* _mSIDI_TableOfLeftToRightTrafficExternalSignalNamesDefaultTableModel;
  /*private*/ /*final*/ DefaultTableModel* _mSIDI_TableOfRightToLeftTrafficExternalSignalNamesDefaultTableModel;
  /*private*/ void initOrig(QList<QString> signalArrayList1, QList<QString> signalArrayList2);
  /*private*/ bool dataChanged();
  /*private*/ void initComponents();
  /*private*/ void formWindowClosing(QCloseEvent* evt);
  /*private*/ QList<QString> formFieldsValid();

 private slots:
  /*private*/ void _mSaveAndCloseActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mSIDI_CompactListsButtonActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mSIDI_ReapplyPatternsActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mSIDI_LeftTrafficButtonActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mSIDI_BothTrafficButtonActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mSIDI_RightTrafficButtonActionPerformed(/*java.awt.event.ActionEvent evt*/);


  friend class FrmSIDI_windowListener;
};

class FrmSIDI_windowListener : public WindowAdapter
{
  Q_OBJECT
  FrmSIDI* dlg;
 public:
  FrmSIDI_windowListener(FrmSIDI* dlg) {this->dlg = dlg;}
  //@Override
  /*public*/ void windowClosing(QCloseEvent* evt) {
      dlg->formWindowClosing(evt);
  }
};

#endif // FRMSIDI_H
