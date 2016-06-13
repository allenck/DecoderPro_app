#ifndef SLOTMONDATAMODEL_H
#define SLOTMONDATAMODEL_H

#include "abstracttablemodel.h"
#include "logger.h"
#include "runnable.h"
#include "libtables_global.h"

class LocoNetSlot;
class JTable;
class LocoNetSystemConnectionMemo;
class LIBTABLESSHARED_EXPORT SlotMonDataModel : public AbstractTableModel
{
    Q_OBJECT
public:
    //explicit SlotMonDataModel(QObject *parent = 0);
    SlotMonDataModel(int row, int column, LocoNetSystemConnectionMemo* memo, QObject *parent = 0);

enum COLUMNS
{
 SLOTCOLUMN = 0,
 ESTOPCOLUMN = 1,
 ADDRCOLUMN = 2,
 SPDCOLUMN  = 3,
 TYPECOLUMN = 4,
 STATCOLUMN = 5,  // status: free, common, etc
 DISPCOLUMN = 6,  // originally "dispatch" button, now "free"
 CONSCOLUMN = 7,  // consist state
 THROTCOLUMN = 8,
 DIRCOLUMN  = 9,
 F0COLUMN   = 10,
 F1COLUMN   = 11,
 F2COLUMN   = 12,
 F3COLUMN   = 13,
 F4COLUMN   = 14,
 F5COLUMN   = 15,
 F6COLUMN   = 16,
 F7COLUMN   = 17,
 F8COLUMN   = 18,

 NUMCOLUMN = 19
};
/*public*/ int rowCount(const QModelIndex &parent) const;
/*public*/ int columnCount(const QModelIndex &parent) const;
/*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
/*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
/*public*/ QVariant data(const QModelIndex &index, int role) const;
/*public*/ int getPreferredWidth(int col);
/*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
/*public*/ void configureTable(JTable* slotTable);
void setColumnToHoldButton(JTable* slotTable, int column);
/*public*/ void showAllSlots(bool val);
/*public*/ void showSystemSlots(bool val);
/*public*/ void dispose();

signals:

public slots:
/*public*/ /*synchronized*/ void notifyChangedSlot(LocoNetSlot* s);
/*public*/ void estopAll();
/*public*/ void clearAllSlots();

private:
LocoNetSystemConnectionMemo* memo;
Logger * log;
 /*static*/ class Notify : public Runnable
 {
  /*private*/ int _row;
  AbstractTableModel* _model;
 public:
    /*public*/ Notify(int row, AbstractTableModel* model);
    /*public*/ void run();
 };
/*private*/ bool _allSlots;// = true;
/*private*/ bool _systemSlots;// = true;
protected:
/*protected*/ int slotNum(int row) const;

};

#endif // SLOTMONDATAMODEL_H
