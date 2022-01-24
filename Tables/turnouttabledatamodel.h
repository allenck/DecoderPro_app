#ifndef TURNOUTTABLEDATAMODEL_H
#define TURNOUTTABLEDATAMODEL_H

#include <beantabledatamodel.h>
#include "libtables_global.h"
#include <QStyledItemDelegate>
#include "jcombobox.h"
#include "jtable.h"
#include "namedbeancombobox.h"
#include "abstractturnoutmanager.h"
#include "abstractproxymanager.h"

class Sensor;
class TurnoutManager;
class Turnout;
class BufferedImage;
class TTComboBoxDelegate;
class TTEditDelegate;
class JActionEvent;
class TurnoutTableAction;
class LIBTABLESSHARED_EXPORT TurnoutTableDataModel : public BeanTableDataModel
{
 Q_OBJECT

 public:
    enum COLUMNS
    {
     INVERTCOL = BeanTableDataModel::NUMCOLUMN, // 5
     LOCKCOL = INVERTCOL+1,                     // 6
     EDITCOL = LOCKCOL+1,                       // 7
     KNOWNCOL = EDITCOL+1,                      // 8
     MODECOL = KNOWNCOL+1,                      // 9
     SENSOR1COL = MODECOL+1,                    // 10
     SENSOR2COL = SENSOR1COL+1,                 // 11
     OPSONOFFCOL = SENSOR2COL+1,                // 12
     OPSEDITCOL = OPSONOFFCOL+1,                // 13
     LOCKOPRCOL = OPSEDITCOL+1,                 // 14
     LOCKDECCOL = LOCKOPRCOL+1,                 // 15
     STRAIGHTCOL = LOCKDECCOL+1,                // 16
     DIVERGCOL = STRAIGHTCOL+1,                 // 17
     FORGETCOL = DIVERGCOL+1,                   // 18
     QUERYCOL = FORGETCOL+1                     // 19
    };

    TurnoutTableDataModel(QObject* parent = nullptr);
    /*public*/ TurnoutTableDataModel(Manager *mgr, QObject* parent = nullptr);
    /*public*/ int columnCount(const QModelIndex &parent) const override;
    /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    /*public*/ QString getColumnClass(int col) const override;
    /*public*/ int getPreferredWidth(int col) override;
    /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const override;
    /*public*/ QVariant data(const QModelIndex &index, int role) const override;
    /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    /*public*/ QString getValue(QString name) const override;
    /*public*/ TurnoutManager* getManager() override;
    /*public*/ Turnout *getBySystemName(QString name) const override;
    /*public*/ NamedBean* getByUserName(QString name) override;
    /*public*/ void clickOn(NamedBean* t) override;
    /*public*/ void configureTable(JTable* tbl) override;
    /*public*/ JTable* makeJTable(/*@Nonnull*/ QString name, /*@Nonnull*/ TableModel* model, /*@CheckForNull*/ RowSorter/*<? extends TableModel>*/* sorter) override;
    /*public*/ QString defaultThrownSpeedText;
    /*public*/ QString defaultClosedSpeedText;
    /*public*/ /*final*/ QVector<QString> speedListClosed = QVector<QString>();
    /*public*/ /*final*/ QVector<QString> speedListThrown = QVector<QString>();
    /*public*/ void showFeedbackChanged(bool visible, JTable* table );
    /*public*/ void showLockChanged(bool visible, JTable* table);
    /*public*/ void showTurnoutSpeedChanged(bool visible, JTable* table);
    /*public*/ void showStateForgetAndQueryChanged(bool visible, JTable* table);

 public slots:
    /*public*/ void comboBoxAction(JActionEvent* e = 0);
    /*public*/ void propertyChange(PropertyChangeEvent* e) override;

 private:
    void common();
    static Logger* log;
//    TTComboBoxDelegate* modeColDelegate = nullptr;
//    TTComboBoxDelegate* lockDecColDelegate = nullptr;
//    TTComboBoxDelegate* opsEditColDelegate = nullptr;
//    TTComboBoxDelegate* opsOnOffColDelegate = nullptr;
//    TTEditDelegate* sensorsColDelegate = nullptr;
//    /*private*/ JTable* makeJTable(TableModel* model);
    /*private*/ void initTable();
    QString closedText;
    QString thrownText;
    /*private*/ bool _graphicState;
    /*private*/ TurnoutManager* turnoutManager = nullptr;
    QString useBlockSpeed;
    QString bothText = "Both";
    QString cabOnlyText = "Cab only";
    QString pushbutText = "Pushbutton only";
    QString noneText = "None";
    void editButton(Turnout* t);
    /*private*/ void updateClosedList();
    /*private*/ void updateThrownList();
    JTable* table = nullptr;

 protected:
    /*protected*/ QString getMasterClassName() override;
    /*protected*/ QString getClassName();
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
    /*protected*/ void configValueColumn(JTable* table) override;
    QStringList getAutomationList(Turnout* t, QModelIndex &index);
    QStringList getDecoderList(Turnout* t, QModelIndex &);
    /*protected*/ void setColumnIdentities(JTable* table)override;
    /*protected*/ void editTurnoutOperation(Turnout* t, JComboBox* box);
    /*protected*/ JComboBox* makeAutomationBox(Turnout* t) const;
    /*protected*/ void setTurnoutOperation(Turnout* t, JComboBox* cb) const;
    /*protected*/ JButton* editButton();
    /*protected*/ /*final*/ void setManager(/*@Nonnull*/ Manager *manager)override;

 protected slots:

    friend class TTComboBoxDelegate;
};  // end of custom data model

class TTComboBoxDelegate : public QStyledItemDelegate
{
Q_OBJECT
public:
  TTComboBoxDelegate(bool editable = false, QObject *parent = 0);

  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
  void setEditorData(QWidget *editor, const QModelIndex &index) const;
  void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
  void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
  TurnoutTableAction* turnoutTableAction = nullptr;
  //mutable QStringList items;
  bool editable;
};


class TTJTable : public JTable{
  Q_OBJECT
  //TableModel* model;
 public:
  TTJTable(TableModel* model) : JTable(model){ }
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

class TTEditDelegate : public QStyledItemDelegate
{
Q_OBJECT
public:
  TTEditDelegate( );

  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
  void setEditorData(QWidget *editor, const QModelIndex &index) const;
  void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
  void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
  TurnoutTableAction* self;
};

#endif // TURNOUTTABLEDATAMODEL_H
