#ifndef BLOCKPORTALTABLEMODEL_H
#define BLOCKPORTALTABLEMODEL_H
#include "abstracttablemodel.h"
#include "propertychangelistener.h"

class Logger;
class PropertyChangeEvent;
class OBlockTableModel;
class BlockPortalTableModel : public AbstractTableModel, public PropertyChangeListener
{
 Q_OBJECT
    Q_INTERFACES(PropertyChangeListener)
public:
 //explicit BlockPortalTableModel(QObject *parent = 0);
 enum COLUMNS
 {
   BLOCK_NAME_COLUMN = 0,
   PORTAL_NAME_COLUMN = 1,
   OPPOSING_BLOCK_NAME = 2,
   NUMCOLS = 3
 };
 /*public*/ BlockPortalTableModel(OBlockTableModel* oBlockModel);
 /*public*/ int columnCount(const QModelIndex &parent) const override;
 /*public*/ int rowCount(const QModelIndex &parent) const override;
 /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
 /*public*/ QVariant data(const QModelIndex &index, int role) const override;
 /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role) override;
 /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const override;
 /*public*/ int getPreferredWidth(int col) ;
 /*public*/ QString getColumnClass(int col);
 QObject* pself() override {return (QObject*)this;}

signals:

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* e) override;

private:
 OBlockTableModel* _oBlockModel;
 static Logger* log;
};

#endif // BLOCKPORTALTABLEMODEL_H
