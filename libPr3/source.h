#ifndef SOURCE_H
#define SOURCE_H

#include <QObject>
#include <QMap>
#include "propertychangelistener.h"
#include "propertychangesupport.h"

class LayoutBlock;
class LayoutEditor;
class PointDetails;
class DestinationPoints;
class QMenu;
class QAction;
class NamedBean;
class EntryExitPairs;
class Source : public QObject
{
    Q_OBJECT
public:
    //explicit Source(QObject *parent = 0);
    /*public*/ Source(PointDetails* point, QObject *parent = 0);
    /*public*/ bool isEnabled(NamedBean *dest, LayoutEditor* panel);
    /*public*/ void setEnabled(NamedBean* dest, LayoutEditor* panel, bool boo);
    /*public*/ void addPropertyChangeListener(PropertyChangeListener* listener);
    /*public*/ void removePropertyChangeListener(PropertyChangeListener* listener);
    //void createPopUpMenu();
    void cancelClearInterlockFromSource(int cancelClear);
    void setMenuEnabled(bool boo);
    PointDetails* getPoint();
    LayoutBlock* getStart();
    QList<LayoutBlock *> getSourceProtecting();
    NamedBean* getSourceSignal();
    /*public*/ void addDestination(PointDetails* dest, QString id);
    /*public*/ void removeDestination(PointDetails* dest);
    void addSourceObject(NamedBean* source);
    NamedBean *getSourceObject();
    /*public*/ QList<PointDetails *> getDestinationPoints() ;
    /*public*/ bool isDestinationValid(PointDetails* destPoint);
    /*public*/ bool getUniDirection(NamedBean *dest, LayoutEditor* panel);
    /*public*/ void setUniDirection(NamedBean* dest, LayoutEditor* panel, bool set);
    /*public*/ bool canBeBiDirection(NamedBean *dest, LayoutEditor* panel);
    /*public*/ bool isRouteActive(PointDetails* endpoint);
    void activeBean(DestinationPoints* dest, bool reverseDirection);
    /*public*/ int getNumberOfDestinations();
    /*public*/ void setEntryExitType(NamedBean* dest, LayoutEditor* panel, int type);
    /*public*/ int getEntryExitType(NamedBean* dest, LayoutEditor* panel);
    /*public*/ void cancelInterlock(NamedBean *dest, LayoutEditor* panel);
    /*public*/ QString getUniqueId(NamedBean* dest, LayoutEditor* panel);
    /*public*/ QStringList getDestinationUniqueId();
    /*public*/ DestinationPoints* getByUniqueId(QString id);
    /*public*/ DestinationPoints* getByUserName(QString id);
    /*public*/ DestinationPoints* getDestForPoint(PointDetails* dp);

signals:

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* evt);
#if 0
    void on_editClear();
    void on_editCancel();
    void on_clear();
    void on_cancel();
#endif
private:
    QMenu* entryExitPopUp = nullptr;
    QAction* clear = nullptr;
    QAction* cancel = nullptr;
    QAction* editCancel = nullptr;
    QAction* editClear = nullptr;
    QAction* editOneClick = nullptr;
    QAction* oneClick = nullptr;
    NamedBean* sourceObject = nullptr;
    NamedBean* sourceSignal = nullptr;
    //String ref = "Empty";
    /*transient*/ PointDetails* pd = nullptr;

    EntryExitPairs* manager;// = InstanceManager::getDefault("EntryExitPairs");
    PropertyChangeSupport* pcs;

    //Using Object here rather than sourceSensor, working on the basis that it might
    //one day be possible to have a signal icon selectable on a panel and
    //generate a propertychange, so hence do not want to tie it down at this stage.
    /*transient*/ QHash<PointDetails*, DestinationPoints*>* pointToDest;// = new HashMap<PointDetails, DestinationPoints>();
    friend class PointDetails;
    friend class DestinationPoints;
    friend class DPRunnable;
};

#endif // SOURCE_H
