#ifndef LAYOUTBLOCKTHROUGHPATHSTABLEMODEL_H
#define LAYOUTBLOCKTHROUGHPATHSTABLEMODEL_H
#include "abstracttablemodel.h"
#include "propertychangelistener.h"

class Logger;
class Manager;
class PropertyChangeEvent;
class LayoutBlock;
class LayoutBlockThroughPathsTableModel : public AbstractTableModel, public  PropertyChangeListener
{
 Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
public:
 //explicit LayoutBlockThroughPathsTableModel(QObject *parent = 0);
enum COLUMNS
{
 SOURCECOL = 0,
 DESTINATIONCOL = 1,
 ACTIVECOL = 2
};
/*public*/ LayoutBlockThroughPathsTableModel(bool editable, LayoutBlock* lBlock, QObject *parent = 0);
/*public*/ int rowCount(const QModelIndex &parent) const override;
/*public*/ int columnCount(const QModelIndex &parent) const override;
/*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
/*public*/ Qt::ItemFlags flags(const QModelIndex &index) const override;
/*public*/ QVariant data(const QModelIndex &index, int role) const override;
/*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role) override;
/*public*/ int getPreferredWidth(int column);
/*public*/ void dispose();
/*public*/ Manager* getManager();
QObject* self() override {return (QObject*)this;}

signals:

public slots:
/*public*/ void propertyChange(PropertyChangeEvent* e = 0) override;

private:
 LayoutBlock* lBlock;
 static /*final*/ int NUMCOL;// = 2 + 1;
 bool editable;// = false;
 Logger* log;
protected:
 /*protected*/ bool matchPropertyName(PropertyChangeEvent* e);

};

#endif // LAYOUTBLOCKTHROUGHPATHSTABLEMODEL_H
