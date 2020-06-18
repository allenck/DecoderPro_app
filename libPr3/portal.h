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
class LIBPR3SHARED_EXPORT Portal : public QObject
{
    Q_OBJECT
public:
    //explicit Portal(QObject *parent = 0);
    /*public*/ Portal(QString uName, QObject* parent = 0);
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
    /*public*/ OBlock* getProtectedBlock(NamedBean* signal);
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
    QT_DEPRECATED /*public*/ QString getPermissibleEntranceSpeed(OBlock* block);
    /*public*/ long getEntranceSpeedChangeWaitForBlock(OBlock* block);
    QT_DEPRECATED /*public*/ QString getPermissibleExitSpeed(OBlock* block);
    /*public*/ bool isValid();
    /*public*/ bool dispose();
    /*public*/ QString getDescription();
    /*public*/ QString toString();
    /*public*/ float getEntranceSpaceForBlock(OBlock* block);
    /*public*/ bool isValidPath(OPath* path);
    enum STATES
    {
      UNKNOWN = 0x01,
      ENTER_TO_BLOCK = 0x02,
      ENTER_FROM_BLOCK = 0x04
    };
    Q_ENUM(STATES)
    /*public*/ QString getPermissibleSpeed(/*@Nonnull*/ OBlock* block, bool entrance);
    /*public*/ void setState(int s);
    /*public*/ int getState();
    /*public*/ /*synchronized*/ void addPropertyChangeListener(PropertyChangeListener* listener);
    /*public*/ /*synchronized*/ void removePropertyChangeListener(PropertyChangeListener* listener);
    /*public*/ void setEntranceSpaceForBlock(/*@Nonnull*/ OBlock* block, float distance);

signals:

public slots:
private:
    /*private*/ static /*final*/ QString NAME_CHANGE;// = "NameChange";
    /*private*/ static /*final*/ QString SIGNAL_CHANGE;// = "signalChange";
    /*private*/ static /*final*/ QString ENTRANCE;// = "entrance";

    /*private*/ QList <OPath*>* _fromPaths;// = new ArrayList <OPath>();
    /*private*/ OBlock*      _fromBlock;
    /*private*/ NamedBean*   _fromSignal;          // may be either SignalHead or SignalMast
    /*private*/ float _fromSignalOffset;           // adjustment distance for speed change
    /*private*/ long        _fromSignalDelay;
    /*private*/ QList <OPath*>* _toPaths;// = new ArrayList <OPath>();
    /*private*/ OBlock*      _toBlock;
    /*private*/ NamedBean*   _toSignal;          // may be either SignalHead or SignalMast
    /*private*/ float _toSignalOffset;             // adjustment distance for speed change
    /*private*/ QString _name;
    /*private*/ int _state = UNKNOWN;
    /*private*/ long        _toSignalDelay;
    /*private*/ bool addPath(QList <OPath*>* list, OPath* path);
    /*private*/ QString checkName(QString name, OBlock* block);
//    /*private*/ QString getPermissibleSignalEntranceSpeed(SignalHead* signal);
//    /*private*/ QString getPermissibleSignalEntranceSpeed(SignalMast* signal);
//    /*private*/ QString getPermissibleSignalExitSpeed(SignalHead* signal);
//    /*private*/ QString getPermissibleSignalExitSpeed(SignalMast* signal);
    /*private*/ static /*@Nonnull*/ QString getPermissibleSignalSpeed(/*@Nonnull */SignalHead* signal, bool entrance);
    /*private*/ static /*@Nonnull*/ QString getPermissibleSignalSpeed(/*@Nonnull*/ SignalMast* signal, bool entrance);
    /*private*/ bool verify(QList <OPath*>* paths, OBlock* block);
    /*private*/ /*final*/ PropertyChangeSupport* pcs = new PropertyChangeSupport(this);

 static Logger* log;

protected:
 /*protected*/ void setEntryState(OBlock* block);

};

#endif // PORTAL_H
