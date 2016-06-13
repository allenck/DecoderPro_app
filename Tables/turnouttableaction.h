#ifndef TURNOUTTABLEACTION_H
#define TURNOUTTABLEACTION_H
#include "abstracttableaction.h"
#include "../LayoutEditor/beantabledatamodel.h"
#include "actionlistener.h"
#include "jdialog.h"
#include "libtables_global.h"

class JTable;
class TurnoutOperationConfig;
class TurnoutOperation;
class ItemListener;
class TTComboBoxDelegate;
class Turnout;
class ActionEvent;
class JmriJFrame;
class QLabel;
class JTextField;
class QComboBox;
class UserPreferencesManager;
class TurnoutManager;
//class QTableView;
class LIBTABLESSHARED_EXPORT TurnoutTableAction : public AbstractTableAction
{
    Q_OBJECT
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
     DIVERGCOL = STRAIGHTCOL+1
    };

    explicit TurnoutTableAction(QObject *parent = 0);
    /*public*/ TurnoutTableAction(QString actionName, QObject *parent);
    ~TurnoutTableAction() {}
    TurnoutTableAction(const TurnoutTableAction& that) : AbstractTableAction(that.text(), that.parent()) {}
    /*public*/ void setManager(Manager* man);
    /*public*/ QString getClassDescription();
    static QString getName();
    /*public*/ static void updateAutomationBox(Turnout* t, /*QComboBox* cb*/QStringList* sl);
    /*public*/ void addToFrame(BeanTableFrame* f);
    /*public*/ void setMenuBar(BeanTableFrame* f);
    /*public*/ void addToPanel(AbstractTableTabAction* f);

signals:

public slots:
    void okPressed(ActionEvent* e = 0);
    void showFeedbackChanged();
    void showLockChanged();
    /*public*/ void showTurnoutSpeedChanged();
    void On_doAutomationBox_toggled(bool);
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
    /*public*/ void setMessagePreferencesDetails();
    /*private*/ void updateClosedList();
    /*private*/ void updateThrownList();
    JmriJFrame* addFrame;// = NULL;
    JTextField* sysName;// = new JTextField(40);
    JTextField* userName;// = new JTextField(40);
    QComboBox* prefixBox;// = new QComboBox();
    JTextField* numberToAdd;// = new JTextField(5);
    QCheckBox* range;// = new QCheckBox("Add a range");
    QLabel* sysNameLabel;// = new JLabel("Hardware Address");
    QLabel* userNameLabel;// = new JLabel(tr("LabelUserName"));
    QString systemSelectionCombo;// = this.getClass().getName()+".SystemSelected";
    QString userNameError;// = this.getName()+".DuplicateUserName";
    UserPreferencesManager* p;
    Logger* log;
    void editButton(Turnout* t);
    QCheckBox* showFeedbackBox;// = new JCheckBox("Show feedback information");
    QCheckBox* showLockBox;// = new JCheckBox("Show lock information");
    QCheckBox* showTurnoutSpeedBox;// = new JCheckBox("Show Turnout Speed Details");
    QCheckBox* doAutomationBox;// = new JCheckBox("Automatic retry");
    void handleCreateException(QString sysName);

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

protected slots:
    /*protected*/ void addPressed(ActionEvent* e = 0);
    /*protected*/ /*QComboBox**/QStringList* makeAutomationBox(Turnout* t);
    /*private*/ void canAddRange(ActionEvent* e = 0);
 friend class CBActionListener;
 friend class RangeListener;
 friend class OkListener;
 friend class TurnoutTableDataModel;
 friend class ItemListener2;
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
    void actionPerformed(ActionEvent *e = 0);
};
class RangeListener : public ActionListener
{
    Q_OBJECT
    TurnoutTableAction* self;
public:
    RangeListener(TurnoutTableAction* self);
public slots:
    void actionPerformed(ActionEvent *e = 0);
};
class LIBTABLESSHARED_EXPORT TurnoutTableDataModel : public BeanTableDataModel
{
 Q_OBJECT
    TurnoutTableAction* self;
    JTable* table;

 public:
    TurnoutTableDataModel(TurnoutTableAction* self);
    /*public*/ int columnCount(const QModelIndex &parent) const;
    /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    /*public*/ int getPreferredWidth(int col);
    /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
    /*public*/ QVariant data(const QModelIndex &index, int role) const;
    /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
    /*public*/ QString getValue(QString name) const;
    /*public*/ Manager* getManager();
    /*public*/ NamedBean* getBySystemName(QString name) const;
    /*public*/ NamedBean* getByUserName(QString name);
    /*public*/ void clickOn(NamedBean* t);
    /*public*/ void configureTable(JTable* tbl);
    /*public*/ JTable* makeJTable(/*TableSorter srtr*/);
public slots:
    /*public*/ void comboBoxAction(ActionEvent* e = 0);
    /*public*/ void propertyChange(PropertyChangeEvent* e);

 private:
    Logger* log;
    TTComboBoxDelegate* modeColDelegate;
    TTComboBoxDelegate* lockDecColDelegate;
    TTComboBoxDelegate* opsEditColDelegate;
    TTComboBoxDelegate* opsOnOffColDelegate;
 protected:
    /*protected*/ QString getMasterClassName();
    /*protected*/ QString getBeanType();
    /*protected*/ bool matchPropertyName(PropertyChangeEvent* e);
 protected slots:

};  // end of custom data model
//};
class TTComboBoxDelegate : public QItemDelegate
{
Q_OBJECT
public:
  TTComboBoxDelegate(QStringList items,  TurnoutTableAction* self, bool editable = false, QObject *parent = 0);

  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
  void setEditorData(QWidget *editor, const QModelIndex &index) const;
  void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
  //void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
  void setItems(QStringList, QString);

private:
  TurnoutTableAction* self;
  QStringList items;
  bool editable;
};
class ItemListener1 : public ActionListener
{
 Q_OBJECT
 JmriJFrame* F;
public:
 ItemListener1(JmriJFrame* F);
public slots:
 void actionPerformed(ActionEvent *e = 0);
};
class ItemListener2 : public ActionListener
{
 Q_OBJECT
 JmriJFrame* F;
 TurnoutTableAction* self;
public:
 ItemListener2(JmriJFrame* F, TurnoutTableAction* self);
public slots:
 void actionPerformed(ActionEvent *e = 0);
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

#endif // TURNOUTTABLEACTION_H
