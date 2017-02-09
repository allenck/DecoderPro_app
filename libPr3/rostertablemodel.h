#ifndef ROSTERTABLEMODEL_H
#define ROSTERTABLEMODEL_H
#include "defaulttablemodel.h"

class Logger;
class ImageIcon;
class RosterEntry;
class RosterIconFactory;
class XTableColumnModel;
class PropertyChangeEvent;
class RosterTableModel : public DefaultTableModel
{
 Q_OBJECT
public:
 RosterTableModel(QObject* parent = 0);
 enum COLUMNS
 {
  IDCOL = 0,
  ADDRESSCOL = 1,
  ICONCOL = 2,
  DECODERCOL = 3,
  ROADNAMECOL = 4,
  ROADNUMBERCOL = 5,
  MFGCOL = 6,
  MODELCOL = 7,
  OWNERCOL = 8,
  DATEUPDATECOL = 9,
  PROTOCOL = 10
 };
 /*public*/ RosterTableModel(bool editable, QObject* parent = 0);
 /*public*/ int rowCount(const QModelIndex &parent) const;

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* e);
 /*public*/ void addColumn(QVariant c);
 /*public*/ int columnCount(const QModelIndex &parent) const;
 /*public*/ void setColumnModel(XTableColumnModel* tcm);
 /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
 /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
 /*public*/ QVariant data(const QModelIndex &index, int role) const;
 /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
 /*public*/ int getPreferredWidth(int column);
 /*public*/ /*final*/ void setRosterGroup(QString rosterGroup);
 /*public*/ /*final*/ QString getRosterGroup();
 /*public*/ void dispose();

private:
 int NUMCOL; // = PROTOCOL + 1;
 /*private*/ QString rosterGroup;// = null;
 bool editable;// = false;
 void common();
 XTableColumnModel* _tcm;// = null;
 RosterIconFactory* iconFactory;// = null;
 ImageIcon* getIcon(RosterEntry* re) ;
 Logger* log;
 friend class ImageDelegate;
};

#endif // ROSTERTABLEMODEL_H
