#ifndef BLOCKPORTALTABLEMODEL_H
#define BLOCKPORTALTABLEMODEL_H
#include "abstracttablemodel.h"

class Logger;
class PropertyChangeEvent;
class OBlockTableModel;
class BlockPortalTableModel : public AbstractTableModel
{
 Q_OBJECT
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
 /*public*/ int columnCount(const QModelIndex &parent) const;
 /*public*/ int rowCount(const QModelIndex &parent) const;
 /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
 /*public*/ QVariant data(const QModelIndex &index, int role) const;
 /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
 /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
 /*public*/ int getPreferredWidth(int col) ;
 /*public*/ QString getColumnClass(int col);

signals:

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* e);

private:
 OBlockTableModel* _oBlockModel;
 static Logger* log;
};

#endif // BLOCKPORTALTABLEMODEL_H
