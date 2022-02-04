#ifndef ABSTRACTLOGIXNGTABLEACTION_H
#define ABSTRACTLOGIXNGTABLEACTION_H

#include <abstracttableaction.h>
#include "jtextarea.h"
#include "namedbean.h"
#include "abstractlogixngeditor.h"
#include "beantabledatamodel.h"
#include "pickframe.h"
#include "base.h"
#include "jtextfield.h"
#include "jcheckbox.h"
#include "jlabel.h"
#include "joptionpane.h"
#include "runnable.h"
#include "instancemanager.h"
#include "userpreferencesmanager.h"

class AbstractLogixNGTableAction : public AbstractTableAction
{
  Q_OBJECT
 public:
  explicit AbstractLogixNGTableAction(QString s,QObject *parent);
  /*public*/  void setMenuBar(BeanTableFrame* f);
  /*public*/  void setMessagePreferencesDetails()override;
  /*public*/  QString getClassDescription()override;

 private:
  static Logger* log;
  // Browser Options
  static /*final*/ QString PRINT_LINE_NUMBERS_OPTION;// = "jmri.jmrit.logixng.PrintLineNumbers";
  static /*final*/ QString PRINT_ERROR_HANDLING_OPTION;// = "jmri.jmrit.logixng.ErrorHandling";
  static /*final*/ QString PRINT_NOT_CONNECTED_OPTION;// = "jmri.jmrit.logixng.NotConnectedSockets";
  static /*final*/ QString PRINT_LOCAL_VARIABLES_OPTION;// = "jmri.jmrit.logixng.LocalVariables";
  JTextArea* _textContent;
  /*private*/ void openPickListTable();
  bool _showReminder = false;
  PickFrame* _pickTables;
  int conditionalRowNumber = 0;
  // Add E Variables
  JmriJFrame* addLogixNGFrame = nullptr;
  JTextField* _systemName = new JTextField(20);
  JTextField* _addUserName = new JTextField(20);
  JCheckBox* _autoSystemName = new JCheckBox(tr("Automatically generate System Name"));   // NOI18N
  JLabel* _sysNameLabel = new JLabel(tr("LogixNG") + " " + tr("SystemName") + ":");  // NOI18N
  JLabel* _userNameLabel = new JLabel(tr("BeanNameLogixNG") + " " + tr("ColumnUserName") + ":");   // NOI18N
  QString systemNameAuto = QString("jmri.jmrit.beantable.AbstractLogixNGTableAction") + ".AutoSystemName";       // NOI18N
  JButton* create =nullptr;

  // Edit E Variables
  /*private*/ bool _inEditMode = false;
  /*private*/ bool _inCopyMode = false;
  void autoSystemName();
  QString _logixNGSysName;
  bool checkLogixNGUserName(QString uName);
  bool checkLogixNGSysName();
  bool checkFlags(QString sName);
  void handleCreateException(QString sysName);
  void editPressed(QString sName);
  void showSaveReminder();
  void deletePressed(QString sName);
  void browserPressed(QString sName);
  void getPrintTreeSettings();
  void updateBrowserText();
  void makeBrowserWindow();
  void saveBrowserPressed();

 private slots:
  void cancelAddPressed(JActionEvent* e = nullptr);
  void copyPressed(QString sName);
  void copyLogixNGPressed(JActionEvent* e=0);
  void createPressed(JActionEvent* e=nullptr);

 protected:
  /*protected*/ /*abstract*/virtual AbstractLogixNGEditor/*<E>*/* getEditor(BeanTableFrame/*<E>*/* f, BeanTableDataModel/*<E>*/* m, QString sName)=0;
  /*protected*/ AbstractLogixNGEditor/*<E>*/* _editor = nullptr;

  //@Nonnull
  //@Override
  /*protected*/ /*abstract*/ Manager/*<E>*/* getManager()override =0;
  /*protected*/ /*abstract*/ virtual void enableAll(bool enable)=0;
  /*protected*/ /*abstract*/ virtual void setEnabled(NamedBean* bean, bool enable)=0;
  /*protected*/ /*abstract*/ virtual bool isEnabled(NamedBean* bean)=0;
  /*protected*/ /*abstract*/ virtual NamedBean* createBean(QString userName)=0;
  /*protected*/ /*abstract*/ virtual NamedBean* createBean(QString systemName, QString userName)=0;
  /*protected*/ /*abstract*/ virtual void deleteBean(NamedBean* bean)=0;
  /*protected*/ bool browseMonoSpace() { return false; }
  /*protected*/ /*abstract*/ virtual QString getBeanText(NamedBean* bean)=0;
  /*protected*/ /*abstract*/ virtual QString getAddTitleKey()=0;
  /*protected*/ /*abstract*/ virtual QString getCreateButtonHintKey()=0;
  /*protected*/ /*abstract*/ virtual void getListenerRefsIncludingChildren(NamedBean* t, QList<QString> list)=0;
  /*protected*/ /*abstract*/ virtual bool hasChildren(NamedBean* t)=0;
  /*protected*/ void createModel()override;
  /*protected*/ void setTitle()override;
  /*protected*/ QString helpTarget()override;
  /*protected*/ NamedBean* _curNamedBean = nullptr;
  /*protected*/ /*final*/ Base::PrintTreeSettings* _printTreeSettings = new  Base::PrintTreeSettings();
  /*protected*/ /*abstract*/virtual JPanel* makeAddFrame(QString titleId, QString startMessageId)=0;
  /*protected*/ QString getClassName()override;
  /*protected*/ JPanel* getSettingsPanel();

 protected slots:
  /*protected*/ void addPressed(JActionEvent* e=0)override;

  friend class LNGBeanTableDataModel;
  friend class ALNGRunnable;
  friend class LogixNGTableTableAction;
  friend class LogixNGTableAction;
  friend class LNGTE_windowListener;;
};

class LNGBeanTableDataModel : public BeanTableDataModel
{
  Q_OBJECT
  AbstractLogixNGTableAction* act;
 public:
  LNGBeanTableDataModel(AbstractLogixNGTableAction* act) {this->act = act;}
  // overlay the state column with the edit column
  static /*public*/  /*final*/ int ENABLECOL;// = VALUECOL;
  static /*public*/  /*final*/ int EDITCOL;// = DELETECOL;

  //@Override
  /*public*/  QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
  /*public*/  QString getColumnClass(int col) const override;
  /*public*/  int getPreferredWidth(int col)override ;
  /*public*/  Qt::ItemFlags flags(const QModelIndex &index) const override;
  /*public*/  QVariant data(const QModelIndex &index, int role) const override;
  /*public*/  bool setData(const QModelIndex &index, const QVariant &value, int role);
  /*public*/  Manager/*<E>*/* getManager()override;
  /*public*/  NamedBean* getBySystemName(QString name)const override;
  /*public*/  NamedBean* getByUserName(QString name)override;
  /*public*/  void configureTable(JTable* table)override;
;
  /*public*/  void clickOn(NamedBean* t)override;
  /*public*/  QString getValue(QString s)override;
  protected:
  /*protected*/ QString enabledString = tr("Enabled");  // NOI18N
  /*protected*/ QString getBeanType() override ;
  /*protected*/ void doDelete(NamedBean* bean)override;
  /*protected*/ bool matchPropertyName(PropertyChangeEvent* e)override;
  /*protected*/ QString getMasterClassName()override;
  /*protected*/ void configDeleteColumn(JTable* table)override;

};
class ALNGRunnable : public Runnable
{
  Q_OBJECT
  AbstractLogixNGTableAction* act;
 public:
  ALNGRunnable(AbstractLogixNGTableAction* act) {this->act = act;}
  //@Override
  /*public*/  void run() {
      JOptionPane::showMessageDialog(nullptr, "Copy is not implemented yet.", "Error", JOptionPane::ERROR_MESSAGE);

      // This may or may not work. It's not tested yet.
      // Disable for now.
      if (1==0) {
          JPanel* panel5 = act->makeAddFrame("TitleCopyLogixNG", "Copy");    // NOI18N
          // Create bean
          JButton* create = new JButton(tr("Copy"));  // NOI18N
          panel5->layout()->addWidget(create);
          connect(create, &JButton::clicked, [=] {
              JOptionPane::showMessageDialog(nullptr, "Copy is not implemented yet.", "Error", JOptionPane::ERROR_MESSAGE);
//                    copyLogixNGPressed(e);
          });
          act->addLogixNGFrame->pack();
          act->addLogixNGFrame->setVisible(true);
          act->_autoSystemName->setSelected(false);
          UserPreferencesManager* prefMgr =(UserPreferencesManager*)InstanceManager::getOptionalDefault("UserPreferencesManager");
          if(prefMgr) {
              act->_autoSystemName->setSelected(prefMgr->getCheckboxPreferenceState(act->systemNameAuto, true));
          }//);
      }
      act->_inCopyMode = false;
  }
};
#if 0
class ALNGEventListener : public QObject, public EventListener
{
  Q_OBJECT
  Q_INTERFACES(EVentListener)
  AbstractLogixNGTableAction* act;
 public:
  ALNGEventListener(AbstractLogixNGTableAction* act) {this->act = act;}
  QString lgxName = sName;
  data.forEach((key, value) -> {
      if (key.equals("Finish")) {                  // NOI18N
          _editor = null;
          _inEditMode = false;
          f.setVisible(true);
      } else if (key.equals("Delete")) {           // NOI18N
          _inEditMode = false;
          deletePressed(value);
      } else if (key.equals("chgUname")) {         // NOI18N
          E x = getManager().getBySystemName(lgxName);
          if (x == null) {
              log.error("Found no logixNG for name {} when changing user name (2)", lgxName);
              return;
          }
          x.setUserName(value);
          m.fireTableDataChanged();
      }
  });
};
#endif

#endif // ABSTRACTLOGIXNGTABLEACTION_H
