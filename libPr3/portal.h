#ifndef PORTAL_H
#define PORTAL_H

#include "abstractnamedbean.h"
#include "logger.h"
#include "libPr3_global.h"

class SignalMast;
class SignalHead;
class NamedBean;
class OBlock;
class OPath;
class LIBPR3SHARED_EXPORT Portal : public AbstractNamedBean
{
    Q_OBJECT
public:
    //explicit Portal(QObject *parent = 0);
 /*public*/ Portal(QString sysName, QString userName, QObject* parent = 0);
    ///*public*/ Portal(OBlock* fromBlock, QString portalName, OBlock* toBlock, QObject *parent = 0);
    /*public*/ bool addPath(OPath* path);
    /*public*/ void removePath(OPath* path);
    /*public*/ QString setName(QString name);
    /*public*/ QString getName();
    /*public*/ bool setToBlock(OBlock* block, bool changePaths);
    /*public*/ OBlock* getToBlock();
    /*public*/ QString getToBlockName();
    /*public*/ QList <OPath*>* getToPaths();
    /*public*/ bool setFromBlock(OBlock* block, bool changePaths);
    /*public*/ OBlock* getFromBlock();
    /*public*/ QString getFromBlockName();
    /*public*/ QList <OPath*>* getFromPaths();
    /*public*/ bool setProtectSignal(NamedBean* signal, long time, OBlock* protectedBlock);
    /*public*/ NamedBean* getFromSignal();
    /*public*/ QString getFromSignalName();
    /*public*/ float getFromSignalOffset();
    /*public*/ NamedBean* getToSignal();
    /*public*/ QString getToSignalName();
    /*public*/ float getToSignalOffset();
    /*public*/ void deleteSignal(NamedBean* signal);
    static /*public*/ NamedBean* getSignal(QString name) ;
    /*public*/ QList <OPath*>* getPathsWithinBlock(OBlock* block);
    /*public*/ OBlock* getOpposingBlock(OBlock* block);
    /*public*/ QList <OPath*>* getPathsFromOpposingBlock(OBlock* block);
    /*public*/ NamedBean* getSignalProtectingBlock(OBlock* block);
    /*public*/ QString getPermissibleEntranceSpeed(OBlock* block);
    /*public*/ long getEntranceSpeedChangeWaitForBlock(OBlock* block);
    /*public*/ QString getPermissibleExitSpeed(OBlock* block);
    /*public*/ bool isValid();
    /*public*/ void dispose();
    /*public*/ QString getDescription();
    /*public*/ QString toString();
    /*public*/ float getEntranceSpaceForBlock(OBlock* block);
    /*public*/ bool isValidPath(OPath* path);
    enum STATES
    {
      ENTER_TO_BLOCK = 0x02,
      ENTER_FROM_BLOCK = 0x04
    };
signals:

public slots:
private:
    /*private*/ QList <OPath*>* _fromPaths;// = new ArrayList <OPath>();
    /*private*/ OBlock*      _fromBlock;
    /*private*/ NamedBean*   _fromSignal;          // may be either SignalHead or SignalMast
    /*private*/ float _fromSignalOffset;           // adjustment distance for speed change
    /*private*/ long        _fromSignalDelay;
    /*private*/ QList <OPath*>* _toPaths;// = new ArrayList <OPath>();
    /*private*/ OBlock*      _toBlock;
    /*private*/ NamedBean*   _toSignal;          // may be either SignalHead or SignalMast
    /*private*/ float _toSignalOffset;             // adjustment distance for speed change
    /*private*/ long        _toSignalDelay;
    /*private*/ bool addPath(QList <OPath*>* list, OPath* path);
    /*private*/ QString checkName(QString name, OBlock* block);
    /*private*/ QString getPermissibleSignalEntranceSpeed(SignalHead* signal);
    /*private*/ QString getPermissibleSignalEntranceSpeed(SignalMast* signal);
    /*private*/ QString getPermissibleSignalExitSpeed(SignalHead* signal);
    /*private*/ QString getPermissibleSignalExitSpeed(SignalMast* signal);
    /*private*/ bool verify(QList <OPath*>* paths, OBlock* block);
Logger* log;
};

#endif // PORTAL_H
