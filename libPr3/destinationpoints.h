#ifndef DESTINATIONPOINTS_H
#define DESTINATIONPOINTS_H
#include "abstractnamedbean.h"
#include "runnable.h"
#include "jframe.h"
#include "entryexitpairs.h"

class QPushButton;
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
    QList<LayoutBlock *> getProtecting();
    int getEntryExitType();
    void setEntryExitType(int type);
    /*public*/ void dispose();
    /*public*/ int getState();
    /*public*/ bool isActive();
    /*public*/ void setState(int state);
    void setActiveEntryExit(bool boo);
    /*synchronized*/ void activeBean(bool reverseDirection, bool showMessage);
    /*public*/ void setInterlockRoute(bool reverseDirection);

signals:

public slots:
    void on_jButton_Clear();
    void on_jButton_Cancel();
    void on_jButton_Exit();
    /*public*/ void propertyChange(PropertyChangeEvent* e);

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
    /*private*/ JFrame* cancelClearFrame;
    /*transient*/ /*private*/ QThread* threadAutoClearFrame;// = NULL;
    QPushButton* jButton_Stack;// = new JButton(Bundle.getMessage("Stack"));  // NOI18Nvoid cancelClearOptionBox();
    void cancelClearInterlock(int cancelClear);
    void activeBean(bool reverseDirection);
    Logger* log;
    QMutex mutex;
    void handleNoCurrentRoute(bool reverse, QString message);
    void cancelClearOptionBox();

protected slots:
    /*protected*/ void blockStateUpdated(PropertyChangeEvent* e);
    void propertyBlockListener(PropertyChangeEvent*);
    void propertyChangeListener(PropertyChangeEvent*);
friend class Source;
friend class PointDetails;
friend class MessageTimeOut;
friend class DPRunnable;
};

class DPRunnable : public Runnable {
    Q_OBJECT
    DestinationPoints* p;
public:
    DPRunnable(DestinationPoints* p);

    /*public*/ void run();
};

class MessageTimeOut : public Runnable {
 Q_OBJECT
 DestinationPoints* dp;
public:
    MessageTimeOut(DestinationPoints* dp){this->dp = dp;
    }
    /*public*/ void run() {
        try {
            //Set a timmer before this window is automatically closed to 30 seconds
            //Thread.sleep(dp->NXMESSAGEBOXCLEARTIMEOUT*1000);
      sleep(dp->NXMESSAGEBOXCLEARTIMEOUT);
            dp->cancelClearFrame->setVisible(false);
            dp->cancelClearInterlock(EntryExitPairs::EXITROUTE);
        } catch (InterruptedException ex) {
            dp->log->debug("Flash timer cancelled");
        }
    }
};

#endif // DESTINATIONPOINTS_H
