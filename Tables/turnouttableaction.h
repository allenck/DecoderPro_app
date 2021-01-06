#ifndef TURNOUTTABLEACTION_H
#define TURNOUTTABLEACTION_H
#include "abstracttableaction.h"
#include "../LayoutEditor/beantabledatamodel.h"
#include "actionlistener.h"
#include "jdialog.h"
#include "libtables_global.h"
#include <QHash>
#include "namedbeancombobox.h"

class Sensor;
class BufferedImage;
class TTAValidator;
class QSpinBox;
class JTable;
class TurnoutOperationConfig;
class TurnoutOperation;
class ItemListener;
class TTComboBoxDelegate;
class TTEditDelegate;
class Turnout;
class JActionEvent;
class JmriJFrame;
class QLabel;
class JTextField;
class JComboBox;
class UserPreferencesManager;
class TurnoutManager;
//class QTableView;
class LIBTABLESSHARED_EXPORT TurnoutTableAction : public AbstractTableAction
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit TurnoutTableAction(QObject *parent = 0);
    /*public*/ Q_INVOKABLE TurnoutTableAction(QString actionName, QObject *parent);
    ~TurnoutTableAction() {}
    Q_INVOKABLE TurnoutTableAction(const TurnoutTableAction& that) : AbstractTableAction(that.text(), that.parent()) {}
    /*public*/ void setManager(Manager* man);
    Q_INVOKABLE /*public*/ QString getClassDescription();
    static QString getName();
    /*public*/ static void updateAutomationBox(Turnout* t, /*QComboBox* cb*/QVector<QString> sl, QModelIndex index);
    /*public*/ void addToFrame(BeanTableFrame* f);
    /*public*/ void setMenuBar(BeanTableFrame* f);
    /*public*/ void addToPanel(AbstractTableTabAction* f);

signals:

public slots:
    void createPressed(ActionEvent* e = 0);
    void cancelPressed(ActionEvent* e = 0);
    void showFeedbackChanged();
    void showLockChanged();
    /*public*/ void showTurnoutSpeedChanged();
    void On_doAutomationBox_toggled(bool);
    /*public*/ void propertyChange(PropertyChangeEvent* e);

private:
    void common();
    QString closedText;
    QString thrownText;
    QString defaultThrownSpeedText;
    QString defaultClosedSpeedText;
    QString useBlockSpeed;// = "Use Block Speed";
    QString bothText;// = "Both";
    QString cabOnlyText;// = "Cab only";
    QString pushbutText;// = "Pushbutton only";
    QString noneText;// = "None";
    QStringList lockOperations;// = {bothText, cabOnlyText, pushbutText, noneText};
    /*private*/ QVector<QString> speedListClosed;// =  QVector<QString>();
    /*private*/ QVector<QString> speedListThrown;// =  QVector<QString>();
    /*private*/ bool noWarn;// = false;
    Q_INVOKABLE /*public*/ void setMessagePreferencesDetails();
    /*private*/ void updateClosedList();
    /*private*/ void updateThrownList();
    JmriJFrame* addFrame;// = NULL;
    JTextField* userNameTextField;// = new JTextField(40);
    JTextField* hardwareAddressTextField;// = new CheckedTextField(20);
    QLabel* statusBar;

    JComboBox* prefixBox;// = new QComboBox();
    JTextField* numberToAdd;// = new JTextField(5);
    QCheckBox* rangeBox;// = new QCheckBox("Add a range");
    QLabel* sysNameLabel;// = new JLabel("Hardware Address");
    QLabel* userNameLabel;// = new JLabel(tr("LabelUserName"));
    QString systemSelectionCombo;// = this.getClass().getName()+".SystemSelected";
    QPushButton* addButton;
    QString userNameError;// = this.getName()+".DuplicateUserName";
    UserPreferencesManager* pref;
    static Logger* log;
    void editButton(Turnout* t, QModelIndex index);
    QCheckBox* showFeedbackBox;// = new JCheckBox("Show feedback information");
    QCheckBox* showLockBox;// = new JCheckBox("Show lock information");
    QCheckBox* showTurnoutSpeedBox;// = new JCheckBox("Show Turnout Speed Details");
    QCheckBox* doAutomationBox;// = new JCheckBox("Automatic retry");
    void handleCreateException(QString sysName);
    TTAValidator* validator;
    QString connectionChoice;
    QString addEntryToolTip;

protected:
    /*protected*/ TurnoutManager* turnManager;// = InstanceManager::turnoutManagerInstance();
//    /*protected*/ QTableView* table;
    /*protected*/ QString getClassName();
    /*protected*/ void createModel();
    /*protected*/ void setTitle();
    /*protected*/ QString helpTarget();
//    /*protected*/ QPushButton* editButton();
    /*protected*/ void setTurnoutOperation(Turnout* t, /*QComboBox* cb*/QString val);
    /*protected*/ void editTurnoutOperation(Turnout* t, QString val);
    /*protected*/ void setDefaultSpeeds(JFrame* _who);
    // for icon state col
    /*protected*/ bool _graphicState = false; // updated from prefs
protected slots:
    /*protected*/ void addPressed(ActionEvent* e = 0);
    /*protected*/ /*QComboBox**/QVector<QString> makeAutomationBox(Turnout* t, QModelIndex index);
    /*private*/ void canAddRange(ActionEvent* e = 0);
 friend class CBActionListener;
 friend class RangeListener;
 friend class OkListener;
 friend class TurnoutTableDataModel;
 friend class ItemListener2;
 friend class TTAValidator;
 friend class TTComboBoxDelegate;
};
Q_DECLARE_METATYPE(TurnoutTableAction)
//class CBActionListener : public ActionListener
//{
// Q_OBJECT
// TurnoutTableAction* self;
// QComboBox* cb;
// Turnout* myTurnout ;
//public:
// CBActionListener(QComboBox* cb, Turnout* myTurnout, TurnoutTableAction* self);
//public slots:
// void actionPerformed(ActionEvent *e = 0);
//};
class OkListener : public ActionListener
{
    Q_OBJECT
    TurnoutTableAction* self;
public:
    OkListener(TurnoutTableAction* self);
public slots:
    void actionPerformed(JActionEvent *e = 0);
};

class ToCancelActionListener : public ActionListener
{
    Q_OBJECT
    TurnoutTableAction* self;
public:
    ToCancelActionListener(TurnoutTableAction* self);
public slots:
    void actionPerformed(JActionEvent *e = 0);
};

class RangeListener : public ActionListener
{
    Q_OBJECT
    TurnoutTableAction* self;
public:
    RangeListener(TurnoutTableAction* self);
public slots:
    void actionPerformed(JActionEvent *e = 0);
};

class LIBTABLESSHARED_EXPORT TurnoutTableDataModel : public BeanTableDataModel
{
 Q_OBJECT
    TurnoutTableAction* turnoutTableAction;

 public:
    enum COLUMNS
    {
     INVERTCOL = BeanTableDataModel::NUMCOLUMN,
     LOCKCOL = INVERTCOL+1,
     EDITCOL = LOCKCOL+1,
     KNOWNCOL = EDITCOL+1,
     MODECOL = KNOWNCOL+1,
     SENSOR1COL = MODECOL+1,
     SENSOR2COL = SENSOR1COL+1,
     OPSONOFFCOL = SENSOR2COL+1,
     OPSEDITCOL = OPSONOFFCOL+1,
     LOCKOPRCOL = OPSEDITCOL+1,
     LOCKDECCOL = LOCKOPRCOL+1,
     STRAIGHTCOL = LOCKDECCOL+1,
     DIVERGCOL = STRAIGHTCOL+1,
     FORGETCOL = DIVERGCOL+1,
     QUERYCOL = FORGETCOL+1
    };

    TurnoutTableDataModel(TurnoutTableAction* turnoutTableAction);
    /*public*/ int columnCount(const QModelIndex &parent) const override;
    /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    /*public*/ QString getColumnClass(int col) override;
    /*public*/ int getPreferredWidth(int col) override;
    /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const override;
    /*public*/ QVariant data(const QModelIndex &index, int role) const override;
    /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    /*public*/ QString getValue(QString name) const override;
    /*public*/ Manager* getManager() override;
    /*public*/ NamedBean* getBySystemName(QString name) const override;
    /*public*/ NamedBean* getByUserName(QString name) override;
    /*public*/ void clickOn(NamedBean* t) override;
    /*public*/ void configureTable(JTable* tbl) override;
    /*public*/ JTable* makeJTable(/*@Nonnull*/ QString name, /*@Nonnull*/ TableModel* model, /*@CheckForNull*/ RowSorter/*<? extends TableModel>*/* sorter);
public slots:
    /*public*/ void comboBoxAction(JActionEvent* e = 0);
    /*public*/ void propertyChange(PropertyChangeEvent* e) override;

 private:
    Logger* log;
    TTComboBoxDelegate* modeColDelegate = nullptr;
    TTComboBoxDelegate* lockDecColDelegate = nullptr;
    TTComboBoxDelegate* opsEditColDelegate = nullptr;
    TTComboBoxDelegate* opsOnOffColDelegate = nullptr;
    TTEditDelegate* sensorsColDelegate = nullptr;
    /*private*/ JTable* makeJTable(TableModel* model);

 protected:
    /*protected*/ QString getMasterClassName() override;
    /*protected*/ QString getBeanType() override;
    /*protected*/ bool matchPropertyName(PropertyChangeEvent* e) override;
    /*protected*/ QString rootPath = "resources/icons/misc/switchboard/"; // also used in display.switchboardEditor
    /*protected*/ char beanTypeChar;// = 'S'; // for Sensor
    /*protected*/ QString onIconPath;// = rootPath + beanTypeChar + "-on-s.png";
    /*protected*/ QString offIconPath;// = rootPath + beanTypeChar + "-off-s.png";
    /*protected*/ BufferedImage* onImage;
    /*protected*/ BufferedImage* offImage;
    /*protected*/ QPixmap onIcon;
    /*protected*/ QPixmap offIcon;
    /*protected*/ int iconHeight = -1;
    /*protected*/ void loadIcons();
    /*protected*/ void configValueColumn(JTable* table);

 protected slots:

};  // end of custom data model

class TTComboBoxDelegate : public QItemDelegate
{
Q_OBJECT

public:
  TTComboBoxDelegate(QStringList items,  TurnoutTableAction* turnoutTableAction, bool editable = false, QObject *parent = 0);

  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
  void setEditorData(QWidget *editor, const QModelIndex &index) const;
  void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
  //void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
  void setItems(QStringList, QString);

private:
  TurnoutTableAction* turnoutTableAction;
  mutable QStringList items;
  bool editable;
};

class TTEditDelegate : public QItemDelegate
{
Q_OBJECT
public:
  TTEditDelegate( TurnoutTableAction* self);

  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
  void setEditorData(QWidget *editor, const QModelIndex &index) const;
  void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
  //void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
  TurnoutTableAction* self;
};

class ItemListener1 : public ActionListener
{
 Q_OBJECT
 JmriJFrame* F;
public:
 ItemListener1(JmriJFrame* F);
public slots:
 void actionPerformed(JActionEvent *e = 0);
};
class ItemListener2 : public ActionListener
{
 Q_OBJECT
 JmriJFrame* F;
 TurnoutTableAction* self;
public:
 ItemListener2(JmriJFrame* F, TurnoutTableAction* self);
public slots:
 void actionPerformed(JActionEvent *e = 0);
};

/*protected*/ /*static*/ class TurnoutOperationEditor : public JDialog
{
 Q_OBJECT
    /**
     *
     */
//    /*private*/ static /*final*/ long serialVersionUID = 3523604197678096714L;
    TurnoutOperationConfig* config;
    TurnoutOperation* myOp;
    Turnout* myTurnout;
 public:
    TurnoutOperationEditor(TurnoutTableAction* tta, JFrame* parent, TurnoutOperation* op, Turnout* t, /*QComboBox* box*/ QString val);
public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* evt);
    void On_nameButton_clicked();
    void On_okButton_clicked();
    void On_cancelButton_clicked();
private:
    /*private*/ void setTitle();
};
class TTAValidator : public QValidator
{
 Q_OBJECT
 TurnoutTableAction* act;
 JTextField* fld;
 bool allow0Length = false; // for Add new bean item, a value that is zero-length is considered invalid.
 QString prefix;// = ConnectionNameFromSystemName::getPrefixFromName(rta->connectionChoice);
 QColor mark;// = ColorUtil::stringToColor("orange");

public:
 TTAValidator(JTextField* fld, TurnoutTableAction* act);
 QValidator::State validate(QString &, int &) const;
 void setPrefix(QString);
 //void fixup(QString &input) const;

public slots:
 void prefixBoxChanged(QString);
};

class TTJTable : public JTable{
  Q_OBJECT
  //TableModel* model;
 public:
  TTJTable(TableModel* model) : JTable(model){}
  //@Override
  /*public*/ QAbstractItemDelegate *getCellRenderer(int row, int column);
  //@Override
  /*public*/ QAbstractItemDelegate* getCellEditor(int row, int column);
  TableCellRenderer* getRenderer(int row, int column);
  TableCellEditor* getEditor(int row, int column);
 protected:
  /*protected*/ void loadRenderEditMaps(QHash<Turnout *, TableCellRenderer *> *r, QHash<Turnout *, TableCellEditor *> *e,
          Turnout* t, Sensor* s) ;
private:
  QHash<Turnout*, TableCellRenderer*>* rendererMapSensor1 = new QHash<Turnout*, TableCellRenderer*>();
  QHash<Turnout*, TableCellEditor*>* editorMapSensor1 = new QHash<Turnout*, TableCellEditor*>();

  QHash<Turnout*, TableCellRenderer*>* rendererMapSensor2 = new QHash<Turnout*, TableCellRenderer*>();
  QHash<Turnout*, TableCellEditor*>* editorMapSensor2 = new QHash<Turnout*, TableCellEditor*>();
};

class BeanBoxRenderer : public JComboBoxEditor
{
  Q_OBJECT
 public:
  BeanBoxRenderer(NamedBeanComboBox* beanBox)
  {
   setValues(beanBox->itemList());
  }
};


class BeanComboBoxEditor : public JComboBoxEditor
{
  Q_OBJECT
 public:
  BeanComboBoxEditor(NamedBeanComboBox* beanBox)
  {
   setValues(beanBox->itemList());
  }
};
#endif // TURNOUTTABLEACTION_H
