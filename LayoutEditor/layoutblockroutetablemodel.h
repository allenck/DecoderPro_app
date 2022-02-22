#ifndef LAYOUTBLOCKROUTETABLEMODEL_H
#define LAYOUTBLOCKROUTETABLEMODEL_H

#include "abstracttablemodel.h"
#include "propertychangelistener.h"

class PropertyChangeEvent;
class Logger;
class Manager;
class LayoutBlock;
class LayoutBlockRouteTableModel : public AbstractTableModel, public PropertyChangeListener
{
 Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
public:
 //explicit LayoutBlockRouteTableModel(QObject *parent = 0);
enum COLUMNS
{
 DESTCOL = 0,
 NEXTHOPCOL = 1,
 HOPCOUNTCOL = 2,
 DIRECTIONCOL = 3,
 METRICCOL = 4,
 LENGTHCOL = 5,
 STATECOL = 6,
 VALIDCOL = 7

};
/*public*/ LayoutBlockRouteTableModel(bool editable, LayoutBlock* lBlock,QObject *parent = 0);
/*public*/ int rowCount(const QModelIndex &parent) const;
/*public*/ int columnCount(const QModelIndex &parent) const;
/*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
/*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
/*public*/ QVariant data(const QModelIndex &index, int role) const;
/*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
/*public*/ int getPreferredWidth(int column);
/*public*/ void dispose();
/*public*/ Manager* getManager();
QObject* pself() override {return (QObject*)this;}

signals:

public slots:
/*public*/ void propertyChange(PropertyChangeEvent* e) override;
private:
     LayoutBlock* lBlock;
     static /*final*/ int NUMCOL;// = 7 + 1;
     bool editable;// = false;
     Logger* log;
protected:
     /*protected*/ bool matchPropertyName(PropertyChangeEvent* e);

};

#endif // LAYOUTBLOCKROUTETABLEMODEL_H
