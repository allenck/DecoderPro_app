#ifndef FRMCB_H
#define FRMCB_H

#include <QObject>
#include "jframe.h"
#include "awtwindowproperties.h"
#include "codebuttonhandlerdata.h"
#include "programproperties.h"
#include "commonsubs.h"
#include "windowadapter.h"
#include "vptr.h"

class CheckJMRIObject;
class CTCSerialData;
class FrmCB : public JFrame
{
  Q_OBJECT
 public:
  /*public*/ FrmCB(AwtWindowProperties* awtWindowProperties, CodeButtonHandlerData* codeButtonHandlerData, ProgramProperties* programProperties,
                  CTCSerialData* ctcSerialData, CheckJMRIObject *checkJMRIObject, QWidget* parent= nullptr);
  /*public*/ static bool dialogCodeButtonHandlerDataValid(CheckJMRIObject* checkJMRIObject, CodeButtonHandlerData* codeButtonHandlerData);
  /*public*/ bool closedNormally() { return _mClosedNormally; }


 private:
  // Variables declaration - do not modify
  /*private*/ JFormattedTextField* _mCodeButtonDelayTime;
  /*private*/ JComboBox/*<String>*/* _mCodeButtonInternalSensor;
  /*private*/ JLabel* _mCodeButtonInternalSensorPrompt;
  /*private*/ JComboBox/*<String>*/* _mOSSectionOccupiedExternalSensor;
  /*private*/ JComboBox/*<String>*/* _mOSSectionOccupiedExternalSensor2;
  /*private*/ JLabel* _mOSSectionOccupiedExternalSensorPrompt;
  /*private*/ JLabel* _mOSSectionOccupiedExternalSensorPrompt1;
  /*private*/ JComboBox/*<String>*/* _mOSSectionSwitchSlavedToUniqueID;
  /*private*/ JButton* _mSaveAndClose;
  /*private*/ JButton* jButton2;
  /*private*/ JLabel* jLabel1;
  /*private*/ JLabel* jLabel10;
  /*private*/ JLabel* jLabel2;
  /*private*/ JLabel* jLabel3;
  /*private*/ JLabel* jLabel4;
  /*private*/ JLabel* jLabel5;
  /*private*/ JLabel* jLabel6;
  /*private*/ JLabel* jLabel7;
  /*private*/ JLabel* jLabel8;
  /*private*/ JLabel* jLabel9;
  // End of variables declaration

  /*private*/ static /*final*/ QString FORM_PROPERTIES;// = "DlgCB";  // NOI18N
  /*private*/ static /*final*/ QString PREFIX;// = "_mOS";            // NOI18N
  /*private*/ /*final*/ AwtWindowProperties* _mAwtWindowProperties;
  /*private*/ bool _mClosedNormally = false;
  /*private*/ /*final*/ CodeButtonHandlerData* _mCodeButtonHandlerData;
  /*private*/ /*final*/ ProgramProperties* _mProgramProperties;
  /*private*/ /*final*/ CTCSerialData* _mCTCSerialData;
  /*private*/ /*final*/ CheckJMRIObject* _mCheckJMRIObject;
  /*private*/ /*final*/ QList<int> _mArrayListOfSelectableOSSectionUniqueIDs;

  /*private*/ QString _mOSSectionOccupiedExternalSensorOrig;
  /*private*/ QString _mOSSectionOccupiedExternalSensor2Orig;
  /*private*/ int _mOSSectionSwitchSlavedToUniqueIDIndexOrig;
  /*private*/ int _mCodeButtonDelayTimeOrig;
  /*private*/ void initOrig();
  /*private*/ bool dataChanged();
  /*private*/ QList<QString> formFieldsValid();
  /*private*/ void initComponents();
  /*private*/ void formWindowClosing(QCloseEvent* evt);

 private slots:
  /*private*/ void _mSaveAndCloseActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void jButton2ActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mOSSectionSwitchSlavedToUniqueIDActionPerformed(/*java.awt.event.ActionEvent evt*/);

  friend class FrmCB_windowListener;
  friend class FrmMainForm;
};

class FrmCB_windowListener : public WindowAdapter
{
  Q_OBJECT
  FrmCB* dlg;
 public:
  FrmCB_windowListener(FrmCB* dlg) {this->dlg = dlg;}
  //@Override
  /*public*/ void windowClosing(QCloseEvent* evt) {
      dlg->formWindowClosing(evt);
  }
};

#endif // FRMCB_H
