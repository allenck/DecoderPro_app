#ifndef LOGIXNGEDITOR_H
#define LOGIXNGEDITOR_H
#include "beantableframe.h"
#include "abstractlogixngeditor.h"
#include "beantabledatamodel.h"
#include "logixng_manager.h"
//#include "conditionalng_editor.h"
//#include "conditionalngdebugger.h"
#include "jcheckbox.h"
#include "jlabel.h"
#include "jtextfield.h"
#include <QRadioButton>
#include "propertychangelistener.h"
#include "windowadapter.h"
#include "conditionalngeditor.h"
#include "conditionalngdebugger.h"
#include "defaultlogixng.h"

class LogixNGEventListenerImpl;
class ConditionalNGTableModel;
class ConditionalNGDebugger;
class ConditionalNGEditor;
/**
 * Create a custom listener event.
 */
/*public*/  /*interface*/class  LogixNGEventListener : public EventListener {

  Q_INTERFACES(EventListener)
 public:
    virtual void logixNGEventOccurred()=0;
};
Q_DECLARE_INTERFACE(LogixNGEventListener, "LogixNGEventListener")

class LogixNGEditor : public QObject, public AbstractLogixNGEditor
{
  Q_OBJECT
  Q_INTERFACES(AbstractLogixNGEditor)
 public:
  LogixNGEditor(BeanTableFrame/*<LogixNG>*/* f, BeanTableDataModel/*<LogixNG>*/* m, QString sName, QObject* parent =nullptr);
  /*public*/  void bringToFront();
  /*public*/  void addEditorEventListener(EditorEventListener* listener);
  /*public*/  void removeEditorEventListener(EditorEventListener* listener);

 public slots:
  void reorderPressed(JActionEvent* e = 0);
  void executePressed(JActionEvent* e = 0);
  void donePressed(JActionEvent* e = 0);
  void deletePressed();
  void newConditionalNGPressed(JActionEvent* e = 0);

 private:
  static Logger* log;
  BeanTableFrame/*<LogixNG>*/* beanTableFrame;
  BeanTableDataModel/*<LogixNG>*/* beanTableDataModel;

  LogixNG_Manager* _logixNG_Manager = nullptr;
  DefaultLogixNG* _curLogixNG = nullptr;

  ConditionalNGEditor* _treeEdit = nullptr;
  ConditionalNGDebugger* _debugger = nullptr;

  int _numConditionalNGs = 0;
  bool _inEditMode = false;

  bool _showReminder = false;
  bool _suppressReminder = false;
  bool _suppressIndirectRef = false;

  /*private*/ /*final*/ JCheckBox* _autoSystemName = new JCheckBox(tr("Automatically generate System Name"));   // NOI18N
  /*private*/ /*final*/ JLabel* _sysNameLabel = new JLabel(tr("SystemName") + ":");  // NOI18N
  /*private*/ /*final*/ JLabel* _userNameLabel = new JLabel(tr("UserName") + ":");   // NOI18N
  /*private*/ /*final*/ QString systemNameAuto = QString("jmri.jmrit.logixng.tools.swing.LogixNGEditor.AutoSystemName");         // NOI18N
  /*private*/ /*final*/ JTextField* _systemName = new JTextField(20);
  /*private*/ /*final*/ JTextField* _addUserName = new JTextField(20);
  // ------------ LogixNG Variables ------------
  JmriJFrame* _editLogixNGFrame = nullptr;
  JTextField* editUserName = new JTextField(20);
  JLabel* status = new JLabel(" ");

  // ------------ ConditionalNG Variables ------------
  /*private*/ ConditionalNGTableModel* _conditionalNGTableModel = nullptr;
  /*private*/ JCheckBox* _showStartupThreadsCheckBox = nullptr;
  /*private*/ DefaultConditionalNG* _curConditionalNG = nullptr;
  int _conditionalRowNumber = 0;
  bool _inReorderMode = false;
  bool _inActReorder = false;
  bool _inVarReorder = false;
  int _nextInOrder = 0;

  // ------------ Select LogixNG/ConditionalNG Variables ------------
  JPanel* _selectLogixNGPanel = nullptr;
  JPanel* _selectConditionalNGPanel = nullptr;
//    /*private*/ JComboBox<String> _selectLogixNGComboBox = new JComboBox<>();
//    /*private*/ JComboBox<String> _selectConditionalNGComboBox = new JComboBox<>();
  QMap<QString, QString> _selectLogixNGMap = QMap<QString, QString>(); // TreeMap
  QList<QString> _selectConditionalNGList = QList<QString>();

  // ------------ Edit ConditionalNG Variables ------------
  bool _inEditConditionalNGMode = false;
  JmriJFrame* _editConditionalNGFrame = nullptr;
  QRadioButton* _triggerOnChangeButton;

  /**
   * This contains a list of commands to be processed by the listener
   * recipient.
   */
  /*private*/ QMap<QString, QString> logixNG_Data = QMap<QString, QString>();

  // ------------ Methods for Edit LogixNG Pane ------------

  /**
   * Create and/or initialize the Edit LogixNG pane.
   */
  void makeEditLogixNGWindow();
  void showSaveReminder();
  void swapConditionalNG(int row);
  void finishDone();
  /*private*/ bool showAddLogixNGFrame();
  void autoSystemName();
  void makeEditConditionalNGWindow();
  void makeDebugConditionalNGWindow();
  void editConditionalNGPressed(int rx);
  void debugConditionalNGPressed(int rx);
  /*private*/ bool checkEditConditionalNG();
  bool checkConditionalNGUserName(QString uName, LogixNG* logixNG);
  bool checkConditionalNGSystemName(QString sName);
  /*private*/ void changeUserName(QVariant value, int row);
  /*private*/ void fireEditorEvent();

  /**
   * Maintain a list of listeners -- normally only one.
   */
  QList<EditorEventListener*> listenerList = QList<EditorEventListener*>();
 protected:
  /*protected*/ QString getClassName();

  friend class ConditionalNGTableModel;
  friend class LogixNGEditor_windowListener;
  friend class LogixNGEditor_DeleteBeanWorker;
  friend class LogixNGEventListenerImpl;
  friend class LogixNG_DebuggerEventListenerImpl;
  friend class AbstractLogixNGTableAction;
};

/*public*/  /*final*/ class ConditionalNGTableModel : public AbstractTableModel,
         public PropertyChangeListener {
  Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
  LogixNGEditor* editor;
 public:
  enum COLUMNS
  {
   SNAME_COLUMN = 0,
   UNAME_COLUMN = SNAME_COLUMN + 1,
   THREAD_COLUMN = UNAME_COLUMN + 1,
   BUTTON_COLUMN = THREAD_COLUMN + 1,
   BUTTON_DEBUG_COLUMN = BUTTON_COLUMN + 1,
   BUTTON_DELETE_COLUMN = BUTTON_DEBUG_COLUMN + 1,
   BUTTON_EDIT_THREADS_COLUMN = BUTTON_DELETE_COLUMN + 1,
   NUM_COLUMNS = BUTTON_EDIT_THREADS_COLUMN + 1
  };
  ConditionalNGTableModel(QObject* parent = nullptr);
  /*public*/  void setShowStartupThreads(bool showStartupThreads);
  /*public*/  /*Class<?>*/QString getColumnClass(int c) const override;
  /*public*/  int columnCount(const QModelIndex &parent) const override;
  /*public*/  int rowCount(const QModelIndex &parent) const override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;
  bool setData(const QModelIndex &index, const QVariant &value, int role) override;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
  QVariant data(const QModelIndex &index, int role) const override;
  /*public*/  int getPreferredWidth(int col);

  QObject* pself() override {return (QObject*)this;}
 public slots:
  /*public*/  void propertyChange(PropertyChangeEvent* e)override;

 private:
  /*private*/ bool _showStartupThreads;
  /*synchronized*/ void updateConditionalNGListeners();
  bool matchPropertyName(PropertyChangeEvent* e);
  /*private*/ void buttomColumnClicked(int row, int col);
  /*private*/ void buttomDebugClicked(int row, int col);
  /*private*/ void deleteConditionalNG(int row);
  /*private*/ void changeUserName(QVariant value, int row);
  void messageDuplicateConditionalNGUserName(QString svName);


};

class LogixNGEditor_windowListener : public WindowAdapter
{
  Q_OBJECT
  LogixNGEditor* editor;
 public:
  LogixNGEditor_windowListener(LogixNGEditor* editor) {this->editor = editor;}
  /*public*/  void windowClosing(QCloseEvent* e) {
      if (editor->_inEditMode) {
          editor->donePressed(/*null*/);
      } else {
          editor->finishDone();
      }
  }};
class LogixNGEditor_dialog_windowListener : public WindowAdapter
{
  Q_OBJECT
  LogixNGEditor* editor;
 public:
  LogixNGEditor_dialog_windowListener(LogixNGEditor* editor) {this->editor = editor;}
};

// This class is copied from BeanTableDataModel
/*private*/ class LogixNGEditor_DeleteBeanWorker : public QObject//extends SwingWorker<Void, Void>
{
 Q_OBJECT
  LogixNGEditor* editor;
    /*private*/ /*final*/ ConditionalNG* _conditionalNG;
    /*private*/ /*final*/ int _row;
    bool _hasDeleted = false;
public:
    /*public*/  LogixNGEditor_DeleteBeanWorker(ConditionalNG* conditionalNG, int row, LogixNGEditor* editor);
    /*public*/  int getDisplayDeleteMsg();
    /*public*/  void setDisplayDeleteMsg(int boo);
    /*public*/  void doDelete();
    /*public*/  void doInBackground();
    void execute() {} //temp
    void get() {}
 protected:
    /*protected*/ void done() ;
};

/*private*/ class LogixNGEventListenerImpl :  public QObject, public ConditionalNGEditor::ConditionalNGEventListener , public PropertyChangeListener {

  Q_OBJECT
  Q_INTERFACES( PropertyChangeListener )
    /*private*/ /*final*/ LogixNGEditor* _logixNGEditor;
public:
    /*public*/  LogixNGEventListenerImpl(LogixNGEditor* logixNGEditor) {
        this->_logixNGEditor = logixNGEditor;
    }
  QObject* self() override {return (QObject*)this;}
  QObject* pself() override {return (QObject*)this;}

    //@Override
    /*public*/  void conditionalNGEventOccurred() override{
        QString lgxName =_logixNGEditor-> _curLogixNG->getSystemName();
       //_logixNGEditor-> _treeEdit->logixNGData.forEach((key, value) ->
        QMapIterator<QString, QString> iter(_logixNGEditor->_treeEdit->logixNGData);
        while(iter.hasNext())
       {
         iter.next();
         QString key = iter.key();
         QString value = iter.value();
            if (key == ("Finish")) {                  // NOI18N
                _logixNGEditor->_treeEdit = nullptr;
                _logixNGEditor->_inEditConditionalNGMode = false;
                _logixNGEditor->bringToFront();
            } else if (key == ("Delete")) {           // NOI18N
                _logixNGEditor->deletePressed();
            } else if (key == ("chgUname")) {         // NOI18N
                LogixNG* x = (LogixNG*)_logixNGEditor->_logixNG_Manager->getBySystemName(lgxName)->self();
                if (x == nullptr) {
                    _logixNGEditor->log->error(tr("Found no logixNG for name %1 when changing user name (2)").arg(lgxName));
                    return;
                }
                x->NamedBean::setUserName(value);
                _logixNGEditor->beanTableDataModel->fireTableDataChanged();
            }
        }//);
    }
};

/*private*/ class LogixNG_DebuggerEventListenerImpl
        : public QObject, public ConditionalNGDebugger::ConditionalNGEventListener {
  Q_OBJECT
  Q_INTERFACES( ConditionalNGDebugger::ConditionalNGEventListener)
    /*private*/ /*final*/ LogixNGEditor* _logixNGEditor;
public:
    /*public*/  LogixNG_DebuggerEventListenerImpl(LogixNGEditor* logixNGEditor) {
        this->_logixNGEditor = logixNGEditor;
    }
  QObject* self() override {return (QObject*)this;}
  //QObject* pself() override {return (QObject*)this;}

    //@Override
    /*public*/  void conditionalNGEventOccurred() override{
        QString lgxName = _logixNGEditor->_curLogixNG->getSystemName();
        //_debugger.logixNGData.forEach((key, value) -> {
        QMapIterator<QString, QString> iter(_logixNGEditor->_debugger->logixNGData);
        while (iter.hasNext()) {
         iter.next();
         QString key = iter.key();
         QString value = iter.value();

            if (key == ("Finish")) {                  // NOI18N
                _logixNGEditor->_debugger = nullptr;
                _logixNGEditor->_inEditConditionalNGMode = false;
                _logixNGEditor->bringToFront();
            } else if (key == ("Delete")) {           // NOI18N
                _logixNGEditor->deletePressed();
            } else if (key == ("chgUname")) {         // NOI18N
                LogixNG* x = (LogixNG*)_logixNGEditor->_logixNG_Manager->getBySystemName(lgxName)->self();
                if (x == nullptr) {
                    _logixNGEditor->log->error(tr("Found no logixNG for name %1 when changing user name (2)").arg(lgxName));
                    return;
                }
                x->NamedBean::setUserName(value);
                _logixNGEditor->beanTableDataModel->fireTableDataChanged();
            }
        }//);
    }
};

#endif // LOGIXNGEDITOR_H
