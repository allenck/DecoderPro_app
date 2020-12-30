#ifndef INDICATORTURNOUTICON_H
#define INDICATORTURNOUTICON_H
#include "turnouticon.h"

class IndicatorTOItemPanel;
class IndicatorTrackPaths;
class OBlock;
class Sensor;
class IndicatorTurnoutIcon : public TurnoutIcon
{
    Q_OBJECT
public:
    //explicit IndicatorTurnoutIcon(QObject *parent = 0);
    QMap<QString, QHash<int, NamedIcon*>*>* _iconMaps;
    /*public*/ IndicatorTurnoutIcon(Editor* editor, QObject *parent = 0);
    /*public*/ void setOccSensor(QString pName);
   /*public*/ void setOccSensorHandle(NamedBeanHandle<Sensor*>* sen);
   /*public*/ Sensor* getOccSensor();
    /*public*/ NamedBeanHandle <Sensor*>* getNamedOccSensor();
    /*public*/ void setOccBlock(QString pName);
   /*public*/ void setOccBlockHandle(NamedBeanHandle<OBlock*>* blockHandle);
   /*public*/ OBlock* getOccBlock();
   /*public*/ NamedBeanHandle <OBlock*>* getNamedOccBlock();
    /*public*/ void setIcon(QString status,QString stateName, NamedIcon* icon);
    /*public*/ NamedIcon* getIcon(QString status, int state);
    /*public*/ QString getStateName(int state);
    /*public*/ QString getStatus();
    /*public*/ int maxHeight();
    /*public*/ int maxWidth();
    /*public*/ void setScale(double s);
    /*public*/ void rotate(int deg);
    /*public*/ void displayState(int state);
    /*public*/ QString getNameString();
    /*public*/ void setStatus(int state);
    /*public*/ void setShowTrain(bool set);
    /*public*/ bool showTrain();
    /*public*/ QStringList getPaths();
    /*public*/ void setPaths(QStringList paths) ;
    /*public*/ void addPath(QString path) ;
    /*public*/ void removePath(QString path);
    /*public*/ QMap<QString, QHash<int, NamedIcon *> *> *getIconMaps();
    /*public*/ void dispose();
    QMap<QString, QHash<int, NamedIcon *> *> *cloneMaps(IndicatorTurnoutIcon* pos);
    /*public*/ Positionable* deepClone();
    /*public*/ Positionable* finishClone(Positionable* p);

signals:

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* evt);
private:
    /*private*/ NamedBeanHandle<Sensor*>* namedOccSensor;// = null;
    /*private*/ NamedBeanHandle<OBlock*>* namedOccBlock;// = null;

    /*private*/ IndicatorTrackPaths* _pathUtil;
    /*private*/ IndicatorTOItemPanel* _TOPanel;
    /*private*/QString _status;
    Logger* log;
    QMap<QString, QHash<int, NamedIcon *> *> *initMaps();
    /*private*/ void setStatus(OBlock* block, int state);
protected:
    /*protected*/ void rotateOrthogonal();
    /*protected*/ void editItem();
    void updateItem();
friend class ITOUpdateActionListener;
};
class ITOUpdateActionListener : public ActionListener
{
 Q_OBJECT
    IndicatorTurnoutIcon* parent;
public:
    ITOUpdateActionListener(IndicatorTurnoutIcon* parent);
public slots:
    void actionPerformed(JActionEvent *e = 0);
};

#endif // INDICATORTURNOUTICON_H
