#ifndef TABLEEDITOR_H
#define TABLEEDITOR_H

#include "abstractlogixngeditor.h"
#include "beantabledatamodel.h"
#include "namedtablemanager.h"
#include "defaultsymboltable.h"
#include "abstractlistmodel.h"
#include "jcheckbox.h"
#include "jlabel.h"
#include "jtextfield.h"
#include "defaultsymboltable.h"
#include "namedbeancombobox.h"
#include "jmrijframe.h"
#include "namedtable.h"
#include "tablemodel.h"
#include "jbutton.h"
#include "jlist.h"
#include "abstractnamedtable.h"

class TableTableModel;
class TableEditor : public QObject, public AbstractLogixNGEditor
{
  Q_OBJECT
  Q_INTERFACES(AbstractLogixNGEditor)
 public:
  TableEditor(BeanTableDataModel/*<NamedTable>*/* m, QString sName, QObject* parent = nullptr);
  /*public*/ void bringToFront()override;
  /*public*/ void addEditorEventListener(EditorEventListener* listener)override;
  /*public*/ void removeEditorEventListener(EditorEventListener* listener);

 private:
  /*private*/ NamedTableManager* _tableManager = nullptr;
  /*private*/ AbstractNamedTable* _curTable = nullptr;
  /*private*/ bool _inEditMode = false;
  /*private*/ bool _showReminder = false;
  /*private*/ /*final*/ SymbolTable* symbolTable = new DefaultSymbolTable();
  /*private*/ /*final*/ JCheckBox* _autoSystemName = new JCheckBox(tr("AutoSysName"));   // NOI18N
  /*private*/ /*final*/ JLabel* _sysNameLabel = new JLabel(tr("SystemName") + ":");  // NOI18N
  /*private*/ /*final*/ JLabel* _userNameLabel = new JLabel(tr("UserName") + ":");   // NOI18N
  /*private*/ /*final*/ QString systemNameAuto = QString("jmri.jmrit.logixng.tools.TableEditor") + ".AutoSystemName";         // NOI18N
  /*private*/ /*final*/ JTextField* _systemName = new JTextField(20);
  /*private*/ /*final*/ JTextField* _addUserName = new JTextField(20);

  /*private*/ NamedBeanComboBox/*<NamedTable>*/* _nameComboBox = nullptr;

  // ------------ NamedTable Variables ------------
  /*private*/ JmriJFrame* _editLogixNGFrame = nullptr;
  /*private*/ /*final*/ JTextField* editUserName = new JTextField(20);
  /*private*/ /*final*/ JTextField* editCsvTableName = new JTextField(40);
//    private JLabel status = new JLabel(" ");
  // ------------ ConditionalNG Variables ------------
  /*private*/ TableTableModel* tableTableModel = nullptr;
//    private ConditionalNG _curConditionalNG = null;
//    private int _conditionalRowNumber = 0;
//    private boolean _inReorderMode = false;
//    private boolean _inActReorder = false;
//    private boolean _inVarReorder = false;
//    private int _nextInOrder = 0;

  // ------------ Select NamedTable/ConditionalNG Variables ------------
//    private JPanel _selectLogixNGPanel = null;
//    private JPanel _selectConditionalNGPanel = null;
//    private JComboBox<String> _selectLogixNGComboBox = new JComboBox<>();
//    private JComboBox<String> _selectConditionalNGComboBox = new JComboBox<>();
//    private TreeMap<String, String> _selectLogixNGMap = new TreeMap<>();
//    private ArrayList<String> _selectConditionalNGList = new ArrayList<>();

  // ------------ Edit ConditionalNG Variables ------------
//    private boolean _inEditConditionalNGMode = false;
//    private JmriJFrame _editConditionalNGFrame = null;
//    private JTextField _conditionalUserName = new JTextField(22);
//    private JRadioButton _triggerOnChangeButton;};

  // ------------ Methods for Edit NamedTable Pane ------------
  /*private*/ JButton* createFileChooser();
  /*private*/ void makeEditTableWindow();
  void showSaveReminder();
  void finishDone();
  void deletePressed();
  /*private*/ void fireEditorEvent();
  static Logger* log;
  /**
   * Maintain a list of listeners -- normally only one.
   */
  QList<EditorEventListener*> listenerList = QList<EditorEventListener*>();

  /**
   * This contains a list of commands to be processed by the listener
   * recipient.
   */
  /*private*/ /*final*/ QMap<QString, QString> tableData = QMap<QString, QString>();

 private slots:
  /*private*/ void okPressed(JActionEvent* e=0);
 protected:
  QString getClassName();

  friend class TEListSelectionListener;
  friend class TableTableModel;
  friend class RowHeaderListModel;
};

/*public*/ /*final*/ class TableTableModel : public AbstractTableModel {
 Q_OBJECT
  TableEditor* editor;
 public:
  TableTableModel(TableEditor* editor) {this->editor = editor;}
    //@Override
  QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
//  Qt::ItemFlags flags(const QModelIndex &index) const override;
//  bool setData(const QModelIndex &index, const QVariant &value, int role) override;
  int rowCount(const QModelIndex &parent) const override;
  int columnCount(const QModelIndex &parent) const override;
  QVariant data(const QModelIndex &index, int role) const override;
  /*public*/ QVariant getElementAt(int index);

 private:

};

/*private*/ class RowHeaderListModel : public AbstractListModel/*<Object>*/ {
  Q_OBJECT
TableEditor* editor;
 public:
  RowHeaderListModel(TableEditor* editor) {this->editor = editor;}
  /*public*/ int getSize() const override;
  /*public*/ QVariant getElementAt(int index)const override;
  /*public*/ int rowCount(const QModelIndex &parent) const {return getSize();}
  /*public*/ QVariant data(const QModelIndex &index, int role) const {
   //return getElementAt(index.row());
  }

};

/*private*/ /*static*/ /*final*/ class RowHeaderRenderer :  public JLabel //implements ListCellRenderer<Object>
{
  Q_OBJECT
 public:
  RowHeaderRenderer(JTable *table);
  /*public*/ QWidget* getListCellRendererComponent(JList* list, QVariant value,
          int index, bool isSelected, bool cellHasFocus) ;
};

class TEListSelectionListener : public QObject, public ListSelectionListener
{
  Q_OBJECT
 TableEditor* editor;
 JTable* _tableTable;
 JLabel* cellRefByIndexLabel;  // NOI18N
 JTextField* cellRefByIndex;  // NOI18N
 JButton* cellRefByIndexButton;
 JButton* cellRefByHeaderButton;
 JTextField* cellRefByHeader;
 JLabel* cellRefByHeaderLabel;
 public:
 TEListSelectionListener(JTable* _tableTable,
                         JLabel* cellRefByIndexLabel,
                         JTextField* cellRefByIndex,
                         JButton* cellRefByIndexButton,
                         JButton* cellRefByHeaderButton,
                         JLabel* cellRefByHeaderLabel,
                         JTextField* cellRefByHeader,
                         TableEditor* editor)
 {
  this->_tableTable = _tableTable;
  this->cellRefByIndexLabel = cellRefByIndexLabel;
  this->cellRefByIndex = cellRefByIndex;
  this->cellRefByIndexButton = cellRefByIndexButton;
  this->cellRefByHeaderButton =cellRefByHeaderButton;
  this->cellRefByHeaderLabel = cellRefByHeaderLabel;
  this->cellRefByHeader = cellRefByHeader;
  this->editor = editor;
 }
 /*public*/ void valueChanged(ListSelectionEvent* /*e*/);
 QObject* self() override{return (QObject*)this;}
};

#endif // TABLEEDITOR_H
