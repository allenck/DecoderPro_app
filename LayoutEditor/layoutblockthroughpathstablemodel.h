#ifndef LAYOUTBLOCKTHROUGHPATHSTABLEMODEL_H
#define LAYOUTBLOCKTHROUGHPATHSTABLEMODEL_H
#include "abstracttablemodel.h"

class Logger;
class Manager;
class PropertyChangeEvent;
class LayoutBlock;
class LayoutBlockThroughPathsTableModel : public AbstractTableModel
{
 Q_OBJECT
public:
 //explicit LayoutBlockThroughPathsTableModel(QObject *parent = 0);
enum COLUMNS
{
 SOURCECOL = 0,
 DESTINATIONCOL = 1,
 ACTIVECOL = 2
};
/*public*/ LayoutBlockThroughPathsTableModel(bool editable, LayoutBlock* lBlock, QObject *parent = 0);
/*public*/ int rowCount(const QModelIndex &parent) const;
/*public*/ int columnCount(const QModelIndex &parent) const;
/*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
/*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
/*public*/ QVariant data(const QModelIndex &index, int role) const;
/*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
/*public*/ int getPreferredWidth(int column);
/*public*/ void dispose();
/*public*/ Manager* getManager();

signals:

public slots:
/*public*/ void propertyChange(PropertyChangeEvent* e = 0);

private:
 LayoutBlock* lBlock;
 static /*final*/ int NUMCOL;// = 2 + 1;
 bool editable;// = false;
 Logger* log;
protected:
 /*protected*/ bool matchPropertyName(PropertyChangeEvent* e);

};

#endif // LAYOUTBLOCKTHROUGHPATHSTABLEMODEL_H
