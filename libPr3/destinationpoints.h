#ifndef DESTINATIONPOINTS_H
#define DESTINATIONPOINTS_H
#include "abstractnamedbean.h"
#include "runnable.h"

class QFrame;
class EntryExitPairs;
class LayoutBlock;
class SignalMastLogic;
class Source;
class PointDetails;
class DestinationPoints : public AbstractNamedBean
{
    Q_OBJECT
public:
    //explicit DestinationPoints(QObject *parent = 0);
    DestinationPoints(PointDetails* point, QString id, Source* src, QObject *parent = 0);
    bool isEnabled();
    void setEnabled(bool boo);
    /*public*/ QString getDisplayName();
    QString getUniqueId();
    PointDetails* getDestPoint();
    bool getUniDirection();
    void setUniDirection(bool uni);
    NamedBean* getSignal();
    void setRouteTo(bool set) ;
    void setRouteFrom(bool set);
    bool isRouteToPointSet();
    LayoutBlock* getFacing();
    LayoutBlock* getProtecting();
    int getEntryExitType();
    void setEntryExitType(int type);
    /*public*/ void dispose();
    /*public*/ int getState();
    /*public*/ bool isActive();
    /*public*/ void setState(int state);
    void setActiveEntryExit(bool boo);

signals:

public slots:
private:
    /*transient*/ PointDetails* point;// = null;
    bool uniDirection;// = true;
    int entryExitType;// = EntryExitPairs.SETUPTURNOUTSONLY;//SETUPSIGNALMASTLOGIC;
    bool enabled;// = true;
    bool activeEntryExit;// = false;
    QList<LayoutBlock*> routeDetails;// = new ArrayList<LayoutBlock>();
    LayoutBlock* destination;
    bool disposed;// = false;
    QString uniqueId;// = null;

    /*transient*/ EntryExitPairs* manager;// = jmri.InstanceManager.getDefault(jmri.jmrit.signalling.EntryExitPairs.class);

   // private static final long serialVersionUID = 1209131245L;

    /*transient*/ SignalMastLogic* sml;

    /*final*/ static int NXMESSAGEBOXCLEARTIMEOUT;// = 30;
    /*transient*/ Source* src;// = NULL;
    QVariant lastSeenActiveBlockObject;
    /*synchronized*/ void removeBlockFromRoute(LayoutBlock* lBlock);
    void setRoute(bool state);
    /*private*/ QFrame* cancelClearFrame;
    /*transient*/ /*private*/ QThread* threadAutoClearFrame;// = NULL;
    void cancelClearOptionBox();
    void cancelClearInterlock(int cancelClear);
    void activeBean(bool reverseDirection);
Logger* log;
QMutex mutex;
protected slots:
    /*protected*/ void blockStateUpdated(PropertyChangeEvent* e);
    void propertyBlockListener(PropertyChangeEvent*);
    void propertyChangeListener(PropertyChangeEvent*);
friend class Source;
friend class PointDetails;
};
class DPRunnable : public Runnable {
    Q_OBJECT
    DestinationPoints* p;
public:
    DPRunnable(DestinationPoints* p);

    /*public*/ void run();
};

#endif // DESTINATIONPOINTS_H
