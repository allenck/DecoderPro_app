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

class ConditionalNGTableModel;
class ConditionalNGDebugger;
class ConditionalNGEditor;
class LogixNGEditor : public QObject, public AbstractLogixNGEditor
{
  Q_OBJECT
  Q_INTERFACES(AbstractLogixNGEditor)
 public:
  LogixNGEditor(BeanTableFrame/*<LogixNG>*/* f, BeanTableDataModel/*<LogixNG>*/* m, QString sName, QObject* parent =nullptr);

 private:
  static Logger* log;
  BeanTableFrame/*<LogixNG>*/* beanTableFrame;
  BeanTableDataModel/*<LogixNG>*/* beanTableDataModel;

  LogixNG_Manager* _logixNG_Manager = nullptr;
  LogixNG* _curLogixNG = nullptr;

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
  /*private*/ ConditionalNG* _curConditionalNG = nullptr;
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

  // ------------ Methods for Edit LogixNG Pane ------------

  /**
   * Create and/or initialize the Edit LogixNG pane.
   */
//  void makeEditLogixNGWindow();
};

#endif // LOGIXNGEDITOR_H
