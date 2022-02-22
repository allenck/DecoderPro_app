#ifndef LAYOUTBLOCKNEIGHBOURTABLEMODEL_H
#define LAYOUTBLOCKNEIGHBOURTABLEMODEL_H
#include "abstracttablemodel.h"
#include "propertychangelistener.h"

class Logger;
class PropertyChangeEvent;
class Manager;
class LayoutBlock;
class LayoutBlockNeighbourTableModel : public AbstractTableModel, public PropertyChangeListener
{
 Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
public:
 //explicit LayoutBlockNeighbourTableModel(QObject *parent = 0);

signals:

public slots:
private:
 enum COLUMNS
 {
  NEIGHBOURCOL = 0,
  DIRECTIONCOL = 1,
  MUTUALCOL = 2,
  RELATCOL = 3,
  METRICCOL = 4
 };
 LayoutBlock* lBlock;
 static /*final*/ int NUMCOL;// = 4 + 1;
 bool editable;// = false;
 /*private*/ LayoutBlockNeighbourTableModel(bool editable, LayoutBlock* lBlock, QObject *parent = 0);
 /*private*/ int rowCount(const QModelIndex &parent) const override;
 /*private*/ int columnCount(const QModelIndex &parent) const override;
 /*private*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const  override;
 /*private*/ QString getColumnClass(int col)  const override;
 /*private*/ Qt::ItemFlags flags(const QModelIndex &index) const  override;
 /*private*/ QVariant data(const QModelIndex &index, int role) const override;
 /*private*/ bool setData(const QModelIndex &index, const QVariant &value, int role) override;
 /*private*/ int getPreferredWidth(int column);
 /*private*/ void dispose();
 /*private*/ Manager* getManager();
 Logger* log;
 QObject* pself() override {return (QObject*)this;}

private slots:
 /*private*/ void propertyChange(PropertyChangeEvent* e) override;

protected:
 /*protected*/ bool matchPropertyName(PropertyChangeEvent* e);
 friend class LayoutBlockRouteTable;
};

#endif // LAYOUTBLOCKNEIGHBOURTABLEMODEL_H
