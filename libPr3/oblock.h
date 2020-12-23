#ifndef OBLOCK_H
#define OBLOCK_H
#include "block.h"
#include <QColor>
#include <QFont>
#include "libPr3_global.h"

class OPath;
class Portal;
class Warrant;
class LIBPR3SHARED_EXPORT OBlock : public Block
{
    Q_OBJECT
public:
    //explicit OBlock(QObject *parent = 0);
    static QHash<QString, int> initOldStatusMap();
    static QHash<QString, int> initStatusMap();
    static QHash<QString, QString> initStatusNameMap();

    /*
    * Block states.
    * NamedBean.UNKNOWN                 = 0x01;
    * Block.OCCUPIED =  Sensor.ACTIVE =   0x02;
    * Block.UNOCCUPIED = Sensor.INACTIVE= 0x04;
    * NamedBean.INCONSISTENT            = 0x08;
    * Add the following to the 4 sensor states.
    * States are OR'ed to show combination.  e.g. ALLOCATED | OCCUPIED = allocated block is occupied by rouge
    */
    enum STATES
    {
     ALLOCATED = 0x10,   // reserve the block for subsequent use by a train
     RUNNING = 0x20,     // Block that running train has reached
     OUT_OF_SERVICE = 0x40,     // Block that running train has reached
     DARK = 0x01,        // Block has no Sensor, same as UNKNOWN
     TRACK_ERROR = 0x80 // Block has Error
    };
    static /*final*/ QHash<QString, int> _oldstatusMap;// = new Hashtable<String, Integer>();
    static /*final*/ QHash<QString, int> _statusMap;// = new Hashtable<String, Integer>();
    static /*final*/ QHash<QString, QString> _statusNameMap;// = new Hashtable<String, String>();
    /*public*/ OBlock(QString systemName, QString userName = "", QObject *parent = 0);
    /*public*/ static QStringList getLocalStatusNames();
    /*public*/ static QString getLocalStatusName(QString str) ;
    /*public*/ static QString getSystemStatusName(QString str);
    /*public*/ bool setSensor(QString pName) override;
    /*public*/ void setNamedSensor(NamedBeanHandle<Sensor*>* namedSensor) override;
    /*public*/ bool setErrorSensor(QString pName);
    /*public*/ Sensor* getErrorSensor();
    /*public*/ NamedBeanHandle<Sensor*>* getNamedErrorSensor();
    /*public*/ QString getAllocatedPathName();
    /*public*/ float getLengthScaleFeet();
    /*public*/ float getLengthMeters() ;
    /*public*/ void setMetricUnits(bool type);
    /*public*/ bool isMetric();
    /*public*/ void setScaleRatio(float sr);
    /*public*/ float getScaleRatio();
    /*public*/ bool statusIs(QString statusName);
    /*public*/ bool isFree();
    /*public*/ QString allocate(QString pathName);
    /*public*/ QString deAllocate(Warrant* warrant);
    /*public*/ void setOutOfService(bool set);
    /*public*/ void addPortal(Portal* portal);
    /*public*/ void removePortal(Portal* portal);
    /*public*/ Portal* getPortalByName(QString name);
    /*public*/ QList <Portal*> getPortals();
    /*public*/ OPath* getPathByName(QString name);
    /*public*/ bool addPath(OPath* path); // does not override!
    /*public*/ bool removeOPath(OPath *path);
    /*public*/ QString setPath(QString pathName, Warrant* warrant);
    /*public*/ void pseudoPropertyChange(QString propName, QVariant old, QVariant n);
    /*public*/ void goingInactive() override;
    /*public*/ void goingActive();
    /*public*/ void dispose() override ;
    /*public*/ QString getDescription();
    /*public*/ bool addSharedTurnout(OPath* key, OBlock* block, OPath* path);
    /*public*/ void setMarkerForeground(QColor c);
    /*public*/ QColor getMarkerForeground() ;
    /*public*/ void setMarkerBackground(QColor c);
    /*public*/ QColor getMarkerBackground();
    /*public*/ void setMarkerFont(QFont f);
    /*public*/ QFont getMarkerFont();
    /*public*/ void setValue(QVariant o) override;
    /*public*/ void setError(bool set);
    /*public*/ void goingUnknown() override;
    /*public*/ void goingInconsistent() override;
    /*public*/ QString getAllocatingWarrantName();
    /*public*/ bool isAllocatedTo(Warrant* warrant);

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* evt);

signals:

public slots:
private:

    QList<Portal*> _portals;// = new ArrayList <Portal>();     // portals to this block

    /*private*/ Warrant* _warrant;       // when not null, block is allocated to this warrant
    /*private*/ QString  _pathName;      // when not null, this is the allocated path
    /*private*/ float _scaleRatio;//   = 87.1f;
    /*private*/ bool _metric;//     = false; // desired display mode
    /*private*/ NamedBeanHandle<Sensor*>* _errNamedSensor;
    // path keys a list of Blocks whose paths conflict with the path.  These Blocks key
    // a list of their conflicting paths.
    /*private*/ QMap<QString, QList<QMap<OBlock*, QList<OPath*> > > > _sharedTO;
//            = new HashMap<String, List<HashMap<OBlock, List<OPath>>>>();
    /*private*/ bool _ownsTOs; // = false;
    Logger* log;
    static void loadStatusMap();
    static void loadStatusNameMap();
    /*private*/ QString checkSharedTO();
    /*private*/ QColor _markerForeground;// = Color.WHITE;
    /*private*/ QColor _markerBackground;// = DEFAULT_FILL_COLOR;
    /*private*/ QFont _markerFont;
    static /*final*/ QColor DEFAULT_FILL_COLOR;// = new Color(200, 0, 200);
protected:
    /*protected*/ Warrant* getWarrant();
    /*protected*/ QString allocate(Warrant* warrant);
    /*protected*/ bool ownsTOs();
    /*protected*/ QString isPathSet(QString path);
    /*protected*/ qint64 _entryTime;		// time when block became occupied

friend class Warrant;
friend class WarrantTableAction;
friend class WarrantTableModel;
friend class Tracker;
friend class TableFrame;
friend class WarrantFrame;
friend class Calibrater;
friend class SpeedUtil;
friend class SCWarrant;
friend class WarrantTest;
friend class OBlockTableModel;
};

#endif // OBLOCK_H
