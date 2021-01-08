#ifndef OBLOCKTABLEMODEL_H
#define OBLOCKTABLEMODEL_H
#include "beantabledatamodel.h"
#include "jtable.h"
#include "jcombobox.h"

class OBlock;
class TableFrames;
class OBlockManager;
class DecimalFormat;
class OBlockTableModel : public BeanTableDataModel
{
 Q_OBJECT
public:
// explicit OBlockTableModel(QObject *parent = 0);
 /*public*/ OBlockTableModel(TableFrames* parent);
 /*public*/ Manager* getManager() override;
 /*public*/ NamedBean* getBySystemName(QString name) const override;
 /*public*/ NamedBean* getByUserName(QString name) override;
 /*public*/ void clickOn(NamedBean* t) override;
 /*public*/ QString getValue(QString name) const override;
 /*public*/ int columnCount(const QModelIndex &parent) const override;
 /*public*/ int rowCount(const QModelIndex &parent) const override;
 /*public*/ QVariant data(const QModelIndex &index, int role) const override;
 /*public*/ static int numberOfLeadingZeros(int i);
 /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
 /*public*/ QString getColumnClass(int col) const override;
 /*public*/ int getPreferredWidth(int col) override;
 /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const override;
 /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role) override;
 enum COLOUMNS
 {
  SYSNAMECOL = 0,
  USERNAMECOL = 1,
  COMMENTCOL = 2,
  STATECOL = 3,
  SENSORCOL = 4,
  EDIT_COL = 5,			// Path button
  DELETE_COL = 6,
  LENGTHCOL = 7,
  UNITSCOL = 8,
  REPORTERCOL = 9,
  REPORT_CURRENTCOL = 10,
  PERMISSIONCOL = 11,
  SPEEDCOL = 12,
  WARRANTCOL=13,
  ERR_SENSORCOL = 14,
  CURVECOL = 15,
  NUMCOLS = 16
 };

 static /*public*/ /*final*/ QString noneText;// = AbstractTableAction.rb.getString("BlockNone");
 static /*public*/ /*final*/ QString gradualText;// = AbstractTableAction.rb.getString("BlockGradual");
 static /*public*/ /*final*/ QString tightText;// = AbstractTableAction.rb.getString("BlockTight");
 static /*public*/ /*final*/ QString severeText;// = AbstractTableAction.rb.getString("BlockSevere");
 static /*final*/ QStringList curveOptions;// = {noneText, gradualText, tightText, severeText};
 static JComboBox/*<String>*/* getCurveEditorBox(int row);
 /*public*/ void configCurveColumn(JTable* table);
 static JComboBox* getSpeedEditorBox(int row);
 /*public*/ void configSpeedColumn(JTable* table);

 signals:

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* e) override;

private:
 Logger* log;


 static QString ZEROS;// = "00000000";

 DecimalFormat* twoDigit;// = new java.text.DecimalFormat("0.00");

 OBlockManager* _manager;
 /*private*/ /*final*/ QStringList tempRow;// = new String[NUMCOLS];
 /*private*/ float _tempLen;// = 0.0f;      // mm for length col of tempRow
 TableFrames* _parent;
 bool _tabbed = false;
 void addHeaderListener(JTable* table);
 void initTempRow();
 /*private*/ static bool sensorExists(QString name);
 bool noWarnDelete;// = false;
 void deleteBean(OBlock* bean);

protected:
 /*protected*/ QString getBeanType() override;
 /*protected*/ QString getMasterClassName() override;
 /*protected*/ QList<NamedBean*> getBeanList();
 static /*protected*/ QString getValue(int state);

 friend class JInternalFrame;
 friend class TableFrames;
 friend class BlockPortalTableModel;
 friend class OBlockTablePanel;
};

class OBSComboBoxDelegate : public QItemDelegate
{
Q_OBJECT
public:
  OBSComboBoxDelegate(QAbstractTableModel* model, QStringList items, QObject *parent = 0);

  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
  void setEditorData(QWidget *editor, const QModelIndex &index) const;
  void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
  //void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
  QAbstractTableModel* model;
  QStringList items;
};
#endif // OBLOCKTABLEMODEL_H
