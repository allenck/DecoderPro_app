#ifndef PATHTURNOUTTABLEMODEL_H
#define PATHTURNOUTTABLEMODEL_H
#include "abstracttablemodel.h"
#include <QStringList>

class QPushButton;
class Logger;
class OPath;
class PropertyChangeEvent;
class QSignalMapper;
class JTable;
class PathTurnoutTableModel : public AbstractTableModel
{
 Q_OBJECT
public:
 explicit PathTurnoutTableModel(QObject *parent = 0);
 /*public*/ PathTurnoutTableModel(OPath* path, QObject *parent = 0);
 enum COLUMNS
 {
 TURNOUT_NAME_COL = 0,
 SETTINGCOLUMN = 1,
 DELETE_COL = 2,
 NUMCOLS = 3
};
 /*public*/ void removeListener() ;
 /*public*/ void init();
 /*public*/ int columnCount(const QModelIndex &parent) const;
 /*public*/ int rowCount(const QModelIndex &parent) const;
 /*public*/QVariant headerData(int section, Qt::Orientation orientation, int role) const;
 /*public*/ QVariant data(const QModelIndex &index, int role) const;
 /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
 /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
 /*public*/ int getPreferredWidth(int col);
 /*public*/ QString getColumnClass(int col);

signals:

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* e);

  private:
  QList<int> buttonMap;
  void setPersistentButtons();
  JTable* table;
  void fireTableRowsUpdated(int, int);
  void fireTableDataChanged();
  static /*final*/ QString closed;// = InstanceManager.turnoutManagerInstance().getClosedText();
  static /*final*/ QString thrown;// = InstanceManager.turnoutManagerInstance().getThrownText();

  static /*final*/ QStringList turnoutStates;// = {closed, thrown};//, unknown, inconsistent};
  /*private*/ QStringList tempRow;// = new String[NUMCOLS];
  /*private*/ OPath* _path;
  void common();
  void initTempRow();
  Logger* log;
  void dispose();

 protected:
  /*protected*/ void setColumnToHoldButton(JTable* table, int column, QPushButton* /*sample*/);
  /*protected*/ void configTurnoutStateColumn(JTable* table);

 friend class TableFrames;
 friend class BPEFCloseListener;
 friend class BlockPathEditFrame;

};
#endif // PATHTURNOUTTABLEMODEL_H
