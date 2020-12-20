#ifndef FRMMAINFORM_H
#define FRMMAINFORM_H
#include "jframe.h"
#include "windowadapter.h"
#include "listselectionlistener.h"
#include "columns.h"
#include "ctcserialdata.h"
#include "codebuttonhandlerdataroutines.h"
#include "frmaddmodifyctccolumn.h"
#include "frmcb.h"

class QScrollArea;
class ListSelectionEvent;
class JButton;
class JLabel;
class JCheckBox;
class QMenu;
class CTCSerialData;
class Columns;
class DefaultListModel;
class ProgramProperties;
class AwtWindowProperties;
class CheckJMRIObject;
class JList;
class FrmMainForm : public JFrame
{
  Q_OBJECT
 public:
  FrmMainForm(QWidget* parent = nullptr);
  /*public*/ void shutdown();

 private:
  /*private*/ static /*final*/ QString FORM_PROPERTIES;// = "FrmMainForm";    // NOI18N
  // Variables declaration - do not modify
  /*private*/ JButton* _mButtonWriteXMLFiles;
  /*private*/ JLabel* _mCB_EditAlwaysEnabled;
  /*private*/ JCheckBox* _mCO_Enabled;
  /*private*/ QMenu* _mConfigure;
  /*private*/ QAction* _mDebugging;
  /*private*/ QAction* _mDefaults;
  /*private*/ QMenu* _mEdit;
  /*private*/ JButton* _mEdit_CB;
  /*private*/ JLabel* _mEdit_CB_Prompt;
  /*private*/ JButton* _mEdit_CO;
  /*private*/ JLabel* _mEdit_CO_Prompt;
  /*private*/ JButton* _mEdit_IL;
  /*private*/ JLabel* _mEdit_IL_Prompt;
  /*private*/ JButton* _mEdit_SIDI;
  /*private*/ JLabel* _mEdit_SIDI_Prompt;
  /*private*/ JButton* _mEdit_SIDL;
  /*private*/ JLabel* _mEdit_SIDL_Prompt;
  /*private*/ JButton* _mEdit_SWDI;
  /*private*/ JLabel* _mEdit_SWDI_Prompt;
  /*private*/ JButton* _mEdit_SWDL;
  /*private*/ JLabel* _mEdit_SWDL_Prompt;
  /*private*/ JButton* _mEdit_TRL;
  /*private*/ JLabel* _mEdit_TRL_Prompt;
  /*private*/ JButton* _mEdit_TUL;
  /*private*/ JLabel* _mEdit_TUL_Prompt;
  /*private*/ QMenu* _mFile;
  /*private*/ QAction* _mFixErrors;
  /*private*/ QAction* _mFleeting;
  /*private*/ QAction* _mGUIDesign;
  /*private*/ QMenu* _mHelp;
  /*private*/ QAction* _mHelpAbout;
  /*private*/ JCheckBox* _mIL_Enabled;
  /*private*/ QAction* _mImport;
  /*private*/ JButton* _mMoveDown;
  /*private*/ JButton* _mMoveUp;
  /*private*/ QAction* _mNew;
  /*private*/ QAction* _mPatterns;
  /*private*/ JList/*<String>*/* _mPresentlyDefinedColumns;
  /*private*/ JCheckBox* _mSIDI_Enabled;
  /*private*/ JCheckBox* _mSIDL_Enabled;
  /*private*/ JCheckBox* _mSWDI_Enabled;
  /*private*/ JCheckBox* _mSWDL_Enabled;
  /*private*/ JCheckBox* _mTRL_Enabled;
  /*private*/ JCheckBox* _mTUL_Enabled;
  /*private*/ JButton* addButton;
  /*private*/ JButton* changeNumbersButton;
  /*private*/ JButton* deleteButton;
  /*private*/ JLabel* jLabel1;
  /*private*/ QMenu* jMenu3;
  /*private*/ QMenuBar* jMenuBar1;
  /*private*/ QAction* jMenuItem1;
  ///*private*/ QScrollArea* jScrollPane1;
  // End of variables declaration
  /*private*/ CTCSerialData* _mCTCSerialData;
  /*private*/ Columns* _mColumns;
  /*private*/ DefaultListModel/*<String>*/* _mDefaultListModel;
  /*private*/ ProgramProperties* _mProgramProperties;
  /*private*/ AwtWindowProperties* _mAwtWindowProperties;
  /*private*/ CheckJMRIObject* _mCheckJMRIObject;

  /*private*/ bool _mAnySubFormOpen = false;   // For any BUT FrmTRL_Rules
  bool _mTRL_RulesFormOpen = false; // for ONLY FrmTRL_Rules

  /*private*/ void initComponents();
  /*private*/ void formWindowClosing(QCloseEvent* evt);
  /*private*/ bool validToExitAtThisTime(QString whatIsTriggeringSave);
  /*private*/ void setupEditor();

 private slots:
  /*private*/ void addButtonActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void deleteButtonActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mPresentlyDefinedColumnsValueChanged(ListSelectionEvent* evt);
  /*private*/ void _mSIDI_EnabledActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mSIDL_EnabledActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mSWDI_EnabledActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mSWDL_EnabledActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mCO_EnabledActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mTUL_EnabledActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mIL_EnabledActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mEdit_SIDIActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mEdit_SIDLActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mEdit_SWDIActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mEdit_SWDLActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mEdit_COActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mEdit_TULActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mEdit_ILActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mTRL_EnabledActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mEdit_TRLActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mEdit_CBActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void changeNumbersButtonActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mButtonWriteXMLFilesActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mNewActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mImportActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mFleetingActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mPatternsActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mDefaultsActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mDebuggingActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mGUIDesignActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mMoveUpActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mMoveDownActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mFixErrorsActionPerformed(/*java.awt.event.ActionEvent evt*/);
  /*private*/ void _mHelpAboutActionPerformed(/*java.awt.event.ActionEvent evt*/);

 private slots:
  void selectionChanged(QModelIndex);

  friend class FrmMain_windowListener;
  friend class FrmMain_listSelectionListener;
  friend class FrmMain_dialogUpdateWindowListener;
  friend class FrmMain_dialogWindowListener;
  friend class FrmMain_FrmAddModifyCTCColumnWindowListener;
  friend class FrmTRL;
  friend class FrmTRL_Rules_windowListener;
  friend class FrmMain_FrmCBWindowListener;
};

class FrmMain_windowListener : public WindowAdapter
{
  Q_OBJECT
  FrmMainForm* form;
 public:
  FrmMain_windowListener(FrmMainForm* form) {this->form = form;}
  //@Override
  /*public*/ void windowClosing(QCloseEvent* evt) {
      form->formWindowClosing(evt);
  }
};

class FrmMain_listSelectionListener : public ListSelectionListener
{
  Q_OBJECT
  FrmMainForm* form;
 public:
  FrmMain_listSelectionListener(FrmMainForm* form) {this->form = form;}
  QObject* self() {return (QObject*)this;}
 public slots:
  //@Override
  /*public*/ void valueChanged(ListSelectionEvent* evt) {
      form->_mPresentlyDefinedColumnsValueChanged(evt);
  }
};

class FrmMain_dialogUpdateWindowListener : public WindowAdapter
{
  Q_OBJECT
  FrmMainForm* form;
  JFrame* dialog;
 public:
  FrmMain_dialogUpdateWindowListener(JFrame* dialog, FrmMainForm* form)
  {
   this->dialog = dialog;
   this->form = form;
  }
  //@Override
  void windowClosing(QCloseEvent* e){}
  /*public*/ void windowClosed(QCloseEvent* e) {
      if (dialog->closedNormally()) {
          form->_mColumns->updateFrame();
      }
      form->_mAnySubFormOpen = false;
  }

};
class FrmMain_dialogWindowListener : public WindowAdapter
{
  Q_OBJECT
  FrmMainForm* form;
  JFrame* dialog;
 public:
  FrmMain_dialogWindowListener(JFrame* dialog, FrmMainForm* form)
  {
   this->dialog = dialog;
   this->form = form;
  }
  //@Override
  void windowClosing(QCloseEvent* e){}
  /*public*/ void windowClosed(QCloseEvent* e) {
      form->_mAnySubFormOpen = false;
  }

};

class FrmMain_FrmAddModifyCTCColumnWindowListener : public WindowAdapter
{
  Q_OBJECT
  FrmMainForm* form;
  FrmAddModifyCTCColumn* dialog;
 public:
  FrmMain_FrmAddModifyCTCColumnWindowListener(FrmAddModifyCTCColumn* dialog, FrmMainForm* form)
  {
   this->dialog = dialog;
   this->form = form;
  }
  //@Override
  void windowClosing(QCloseEvent* e){}
  /*public*/ void windowClosed(QCloseEvent* e) {
      if (dialog->closedNormally()) {
          form->_mCTCSerialData->addCodeButtonHandlerData(CodeButtonHandlerDataRoutines::createNewCodeButtonHandlerData(form->_mCTCSerialData->getUniqueNumber(),
                 dialog->_mNewSwitchNumber, dialog->_mNewSignalEtcNumber, dialog->_mNewGUIColumnNumber, form->_mProgramProperties));
          form->_mColumns->updateFrame();
      }
      form->_mAnySubFormOpen = false;
  }

};

class FrmMain_FrmCBWindowListener : public WindowAdapter
{
  Q_OBJECT
  FrmMainForm* form;
  FrmCB* dialog;
 public:
  FrmMain_FrmCBWindowListener(FrmCB* dialog, FrmMainForm* form)
  {
   this->dialog = dialog;
   this->form = form;
  }
  //@Override
  void windowClosing(QCloseEvent* e){}
  /*public*/ void windowClosed(QCloseEvent* e) {
      if (dialog->closedNormally()) {
          form->_mColumns->updateFrame();
      }
      form->_mAnySubFormOpen = false;
  }
};

#endif // FRMMAINFORM_H
