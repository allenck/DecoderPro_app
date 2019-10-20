#ifndef SPROGSLOTMONDATAMODEL_H
#define SPROGSLOTMONDATAMODEL_H
#include "abstracttablemodel.h"
#include "sprogsystemconnectionmemo.h"
class Logger;
namespace Sprog
{

 class SprogSlotMonDataModel : public AbstractTableModel
 {
  Q_OBJECT
 public:
  SprogSlotMonDataModel(int row, int column, SprogSystemConnectionMemo* memo, QObject* parent  = 0);
  enum COLUMNS
  {
   SLOTCOLUMN = 0,
   ADDRCOLUMN = 1,
   SPDCOLUMN = 2,
   STATCOLUMN = 3,  // status: free, common, etc
   DIRCOLUMN = 4,

   NUMCOLUMN = 5
  };
  /*public*/ int rowCount(const QModelIndex &parent) const;
  /*public*/ int columnCount(const QModelIndex &parent) const;
  /*public*/ QVariant data(const QModelIndex &index, int role) const;
  /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
  /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
  /*public*/ int getPreferredWidth(int col);
  /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
  /*public*/ void configureTable(JTable* slotTable);
  /*public*/ void showAllSlots(bool val);
  /*public*/ void dispose();
  /*public*/ int getRowCount() {return rowCount(QModelIndex());}
  /*public*/ int getColumnCount() {return columnCount(QModelIndex());}


 public slots:
  /*public*/ /*synchronized*/ void notifyChangedSlot(SprogSlot* s);

 private:
  /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger("SprogSlotMonDataModel");
  /*private*/ SprogSystemConnectionMemo* _memo;// = null;
   // methods for control of "all slots" vs "only active slots"
   /*private*/ bool _allSlots;// = true;

 protected:
  /*protected*/ int slotNum( int row) const;

 };
}
#endif // SPROGSLOTMONDATAMODEL_H
