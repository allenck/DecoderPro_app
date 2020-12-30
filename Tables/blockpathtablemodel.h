#ifndef BLOCKPATHTABLEMODEL_H
#define BLOCKPATHTABLEMODEL_H
#include "abstracttablemodel.h"
#include <QStringList>

class QPushButton;
class JTable;
class QSignalMapper;
class Logger;
class PropertyChangeEvent;
class OPath;
class DecimalFormat;
class OBlock;
class TableFrames;
class BlockPathTableModel : public AbstractTableModel
{
 Q_OBJECT
public:
 explicit BlockPathTableModel(QObject *parent = 0);
 enum COLUMNS
 {
  FROM_PORTAL_COLUMN = 0,
  NAME_COLUMN = 1,
  TO_PORTAL_COLUMN = 2,
  LENGTHCOL = 3,
  UNITSCOL = 4,
  EDIT_COL = 5,
  DELETE_COL = 6,
  NUMCOLS = 7
 };
 /*public*/ BlockPathTableModel(OBlock* block, TableFrames* _parent, QObject *parent = 0);
 /*public*/ void init();
 /*public*/ void removeListener();
 /*public*/ int columnCount(const QModelIndex &parent) const;
 /*public*/ int rowCount(const QModelIndex &parent) const;
 /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;QVariant data(const QModelIndex &index, int role) const;
 /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
 /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
 /*public*/ int getPreferredWidth(int col);
signals:

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* e) ;
private:
 Logger* log;
 void common();
 /*private*/ QStringList tempRow;// = new String[NUMCOLS];

 /*private*/ TableFrames* _parent;
 /*private*/ OBlock* _block;
 /*private*/ QList<bool> _units;      // gimmick to toggle units of length col for each path
 /*private*/ float _tempLen;

 DecimalFormat* twoDigit;// = new DecimalFormat("0.00");
 void initTempRow();
 bool deletePath(OPath* path);
 QList<int> buttonMap;
 void setPersistentButtons();
 JTable* table;
 void fireTableRowsUpdated(int, int);
 void fireTableDataChanged();
private slots:
 void OnButtonClicked(QObject*);

protected:
 /*protected*/ OBlock* getBlock();
 /*protected*/ void setColumnToHoldButton(JTable* table, int column, QPushButton* /*sample*/ = NULL);

 friend class TableFrames;
 friend class BlockPathEditFrame;
};

#endif // BLOCKPATHTABLEMODEL_H
