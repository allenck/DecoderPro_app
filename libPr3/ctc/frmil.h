#ifndef FRMIL_H
#define FRMIL_H
#include "jframe.h"
#include "jbutton.h"
#include "jlabel.h"
#include "jcombobox.h"
#include "jtable.h"
#include "awtwindowproperties.h"
#include "checkjmriobject.h"
#include "codebuttonhandlerdata.h"
#include "ctcserialdata.h"
#include "defaulttablemodel.h"
#include "windowadapter.h"

class FrmIL : public JFrame
{
  Q_OBJECT
 public:
  /*public*/ FrmIL(AwtWindowProperties* awtWindowProperties,
                  CodeButtonHandlerData *codeButtonHandlerData,
                  CheckJMRIObject *checkJMRIObject,
                  bool signalHeadSelected,
                  CTCSerialData *ctcSerialData, QWidget* parent = nullptr);
  /*public*/ void enableSignalListComboBox(JTable* table);

  /*public*/ bool closedNormally() { return _mClosedNormally; }

 private:
  // Variables declaration - do not modify
  /*private*/ JButton* BT_Replace;
  /*private*/ JTable* _mIL_TableOfExternalSignalNames;
  /*private*/ JComboBox/*<String>*/*_mOS_NumberEntry;
  /*private*/ JButton* _mSaveAndClose;
  /*private*/ JLabel* _mTableOfSignalNamesPrompt;
  /*private*/ JButton* jButton1;
  /*private*/ JLabel* jLabel1;
  /*private*/ JLabel* jLabel2;
  /*private*/ JLabel* jLabel4;
  /*private*/ JLabel* jLabel5;
  /*private*/ JLabel* jLabel6;
  ///*private*/ JScrollPane jScrollPane1;
  // End of variables declaration
  /*private*/ static /*final*/ QString FORM_PROPERTIES;// = "DlgIL";  // NOI18N
  /*private*/ static /*final*/ QString PREFIX ;//= "_mIL_";           // NOI18N
  /*private*/ /*final*/ AwtWindowProperties* _mAwtWindowProperties;
  /*private*/ bool _mClosedNormally = false;
  /*private*/ /*final*/ CodeButtonHandlerData* _mCodeButtonHandlerData;
  /*private*/ /*final*/ CheckJMRIObject* _mCheckJMRIObject;
  /*private*/ /*final*/ bool _mSignalHeadSelected;
  /*private*/ /*final*/ CTCSerialData* _mCTCSerialData;
  /*private*/ /*final*/QList<int>* _mUniqueIDS = new QList<int>();

  /*private*/ QList<QString> _mSignalsArrayListOrig;
  /*private*/ void initOrig(QList<QString> signalsArrayList);
  /*private*/ bool dataChanged();
  /*private*/ /*final*/ DefaultTableModel* _mIL_TableOfExternalSignalNamesDefaultTableModel;
  /*public*/ static bool dialogCodeButtonHandlerDataValid(CheckJMRIObject* checkJMRIObject, CodeButtonHandlerData* codeButtonHandlerData);
  /*private*/ void loadUpSignalTable(QList<QString> signalsArrayList);
  /*private*/ void initComponents();
  /*private*/ void formWindowClosing(QCloseEvent* evt);
  /*private*/ QList<QString> formFieldsValid();

 private slots:
  /*private*/ void _mSaveAndCloseActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void jButton1ActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void BT_ReplaceActionPerformed(/*java.awt.event.ActionEvent evt*/);


  friend class FrmIL_windowListener;
  friend class Columns;
};


class FrmIL_windowListener : public WindowAdapter
{
  Q_OBJECT
  FrmIL* dlg;
 public:
  FrmIL_windowListener(FrmIL* dlg) {this->dlg = dlg;}
  //@Override
  /*public*/ void windowClosing(QCloseEvent* evt) {
      dlg->formWindowClosing(evt);
  }
};

class TableOfExternalSignalNames : public DefaultTableModel
{
  Q_OBJECT
  FrmIL* dlg;
 public:
  TableOfExternalSignalNames();
};
#endif // FRMIL_H
