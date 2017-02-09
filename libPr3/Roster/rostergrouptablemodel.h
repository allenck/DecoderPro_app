#ifndef ROSTERGROUPTABLEMODEL_H
#define ROSTERGROUPTABLEMODEL_H
#include "abstracttablemodel.h"

class RosterEntry;
class QTableView;
class Logger;
class RosterGroupTableModel : public AbstractTableModel
{
 Q_OBJECT
public:
 enum COLUMNS
 {
  IDCOL = 0,
  ROADNUMBERCOL = 1,
  ROADNAMECOL = 2,
  MFGCOL = 3,
  OWNERCOL = 4,
  ADDTOGROUPCOL = 5
 };

 explicit RosterGroupTableModel(QObject *parent = 0);
 static /*final*/ int NUMCOL;// = ADDTOGROUPCOL + 1;
 /*public*/ int rowCount(const QModelIndex &parent) const;
 /*public*/ int columnCount(const QModelIndex &parent) const;
 /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
 /*public*/ int getPreferredWidth(int col);
 /*public*/ bool isCellEditable(int row, int col);
 /*public*/ QVariant data(const QModelIndex &index, int role) const;
 /*public*/ void configureTable(QTableView* table);
 /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
 /*synchronized*/ /*public*/ void dispose();
 /*public*/ void setGroup(QString grp);
 /*public*/ void getGroupEnabled(RosterEntry* re);
 Qt::ItemFlags flags(const QModelIndex &index) const;

signals:

public slots:

private:
 QString group;// = "RosterGroup:";
 Logger* log;
};

#endif // ROSTERGROUPTABLEMODEL_H
