#ifndef PORTALTABLEMODEL_H
#define PORTALTABLEMODEL_H
#include "beantabledatamodel.h"

class Portal;
class TableFrames;
class PortalManager;
class PortalTableModel : public BeanTableDataModel
{
 Q_OBJECT
public:
 explicit PortalTableModel(TableFrames* _parent, QObject *parent = 0);
 /*public*/ void init();
 /*public*/ Manager* getManager() ;
 /*public*/ NamedBean* getBySystemName(QString name) const ;
 /*public*/ NamedBean* getByUserName(QString name) const;
 /*protected*/ QString getBeanType();
 /*public*/ QString getValue(QString name);
 /*public*/ void clickOn(NamedBean* t) ;
 /*public*/ int columnCount(const QModelIndex &parent) const;
 /*public*/ int rowCount(const QModelIndex &parent) const;
 /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
 /*public*/ QVariant data(const QModelIndex &index, int role) const;
 /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
 /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
 /*public*/ QString getColumnClass(int col);
 /*public*/ int getPreferredWidth(int col);
 enum COLUMNS
 {
  FROM_BLOCK_COLUMN = 0,
  NAME_COLUMN = 1,
  TO_BLOCK_COLUMN = 2,
  DELETE_COL = 3,
  EDIT_COL = 4,
  NUMCOLS = 4
 };// reports + 1 for EDIT column if _tabbed

signals:

public slots:
private:
 ///*private*/ static final long serialVersionUID = -4467086483594717590L;

 PortalManager* _manager;
 /*private*/ QVector<QString> tempRow = QVector<QString>(NUMCOLS);
 /*private*/ /*final*/ bool _tabbed; // set from prefs (restart required)

 TableFrames* _parent;
 void initTempRow();
 /*private*/ static bool deletePortal(Portal* portal);
 static Logger* log;
 /*private*/ void editPortal(Portal* portal);

protected:
 /*protected*/ QString getMasterClassName();
 /*protected*/ int verifyWarning(QString message);
friend class PortalEditFrame;
};

#endif // PORTALTABBLEMODEL_H
