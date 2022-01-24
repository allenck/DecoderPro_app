#ifndef BLOCKORDER_H
#define BLOCKORDER_H

#include <QObject>
#include "libPr3_global.h"
class Warrant;
class NamedBean;
class Portal;
class OPath;
class OBlock;
class LIBPR3SHARED_EXPORT BlockOrder : public QObject
{
    Q_OBJECT
public:
    //explicit BlockOrder(QObject *parent = 0);
    /*public*/ BlockOrder(OBlock* block, QObject *parent = 0);
    /*public*/ BlockOrder(OBlock* block, QString path, QString entry, QString exit, QObject *parent = 0);
    /*public*/ QString getEntryName();
    /*public*/ QString getExitName();
    /*public*/ QString getPathName();
    /*public*/ OBlock* getBlock();
    /*public*/ QString toString();

signals:

public slots:
private:
    /*private*/ OBlock*  _block;     // OBlock of these orders
    /*private*/ QString  _pathName;  // path the train is to take in the block
    /*private*/ QString  _entryName; // Name of entry Portal
    /*private*/ QString  _exitName;  // Name of exit Portal
protected:
    /*protected*/ BlockOrder(BlockOrder* bo, QObject *parent = 0);
    /*protected*/ void setEntryName(QString name);
    /*protected*/ void setExitName(QString name);
    /*protected*/ bool validateOrder();
    /*protected*/ void setPathName(QString path);
    /*protected*/ OPath* getPath();
    /*protected*/ QString setPath(Warrant* warrant);
    /*protected*/ void setBlock(OBlock* block);
    /*protected*/ Portal* getEntryPortal();
    /*protected*/ Portal* getExitPortal();
    /*protected*/ QString getPermissibleEntranceSpeed();
    /*protected*/ long getEntranceSpeedChangeWait() ;
    /*protected*/ QString getPermissibleExitSpeed();
    /*protected*/ NamedBean* getSignal();
    /*protected*/ QString hash();
    /*protected*/ float getEntranceSpace();

friend class Warrant;
friend class WarrantFrame;
friend class WFRouteTableModel;
friend class WarrantTableAction;
friend class CreateWarrantFrame;
friend class WarrantTableFrame;
friend class RouteLocation;
friend class WarrantRoute;
friend class RouteTableModel;
friend class NXFrame;
friend class Calibrater;
friend class SpeedUtil;
friend class SCWarrant;
friend class WarrantManager;
friend class RouteBoxCellEditor;
};

#endif // BLOCKORDER_H
