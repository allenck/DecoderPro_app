#ifndef SOURCE_H
#define SOURCE_H

#include <QObject>
#include <QMap>

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
    /*public*/ bool isEnabled(QObject* dest,LayoutEditor* panel);
    /*public*/ void setEnabled(QObject* dest, LayoutEditor* panel, bool boo);
    void createPopUpMenu();
    void cancelClearInterlockFromSource(int cancelClear);
    void setMenuEnabled(bool boo);
    PointDetails* getPoint();
    LayoutBlock* getStart();
    LayoutBlock* getSourceProtecting();
    NamedBean* getSourceSignal();
    /*public*/ void addDestination(PointDetails* dest, QString id);
    /*public*/ void removeDestination(PointDetails* dest);
    void addSourceObject(NamedBean* source);
    QObject* getSourceObject();
    /*public*/ QList<PointDetails*>* getDestinationPoints() ;
    /*public*/ bool isDestinationValid(PointDetails* destPoint);
    /*public*/ bool getUniDirection(QObject* dest, LayoutEditor* panel);
    /*public*/ void setUniDirection(QObject* dest, LayoutEditor* panel, bool set);
    /*public*/ bool canBeBiDirection(QObject* dest, LayoutEditor* panel);
    /*public*/ bool isRouteActive(PointDetails* endpoint);
    void activeBean(DestinationPoints* dest, bool reverseDirection);
    /*public*/ int getNumberOfDestinations();
    /*public*/ void setEntryExitType(QObject* dest, LayoutEditor* panel, int type);
    /*public*/ int getEntryExitType(QObject* dest, LayoutEditor* panel);
    /*public*/ void cancelInterlock(QObject* dest, LayoutEditor* panel);
    /*public*/ QString getUniqueId(QObject* dest, LayoutEditor* panel);
    /*public*/ QStringList getDestinationUniqueId();
    /*public*/ DestinationPoints* getByUniqueId(QString id);
    /*public*/ DestinationPoints* getByUserName(QString id);
signals:

public slots:
    void on_editClear();
    void on_editCancel();
    void on_clear();
    void on_cancel();
private:
    QMenu* entryExitPopUp;// = NULL;
    QAction* clear;// = NULL;
    QAction* cancel;// = NULL;

    NamedBean* sourceObject;// = NULL;
    NamedBean* sourceSignal;// = NULL;
    //String ref = "Empty";
    /*transient*/ PointDetails* pd;// = NULL;

    EntryExitPairs* manager;// = InstanceManager::getDefault("EntryExitPairs");

    //Using Object here rather than sourceSensor, working on the basis that it might
    //one day be possible to have a signal icon selectable on a panel and
    //generate a propertychange, so hence do not want to tie it down at this stage.
    /*transient*/ QMap<PointDetails*, DestinationPoints*>* pointToDest;// = new HashMap<PointDetails, DestinationPoints>();
    friend class PointDetails;
    friend class DestinationPoints;
};

#endif // SOURCE_H
