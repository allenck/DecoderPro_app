#ifndef INDICATORTRACKICON_H
#define INDICATORTRACKICON_H
#include "namedbeanhandle.h"
#include "positionableicon.h"
#include "actionlistener.h"

class IndicatorItemPanel;
class IndicatorTrackPaths;
class Sensor;
class OBlock;
class IndicatorTrackIcon : public PositionableIcon, public  PropertyChangeListener
{
    Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
public:
    //explicit IndicatorTrackIcon(QObject *parent = 0);
    /*public*/ IndicatorTrackIcon(Editor* editor, QObject *parent = 0);
    /*public*/ Positionable* deepClone() override;
    /*public*/ Positionable* finishClone(Positionable* p) override;
    /*public*/ QMap<QString, NamedIcon *> *getIconMap();
     /*public*/ void setOccSensor(QString pName);
     /*public*/ void setOccSensorHandle(NamedBeanHandle<Sensor*>* senHandle);
     /*public*/ Sensor* getOccSensor();
     /*public*/ NamedBeanHandle <Sensor*>* getNamedOccSensor();
     /*public*/ void setOccBlock(QString pName);
    /*public*/ void setOccBlockHandle(NamedBeanHandle<OBlock*>* blockHandle);
    /*public*/ OBlock* getOccBlock();
    /*public*/ NamedBeanHandle <OBlock*>* getNamedOccBlock();
    /*public*/ void setShowTrain(bool set);
    /*public*/ bool showTrain();
    /*public*/ QStringList getPaths();
    /*public*/ void setPaths(QStringList paths);
    /*public*/ void addPath(QString path);
    /*public*/ void removePath(QString path);
    /*public*/ void setStatus(int state);
    /*public*/ void setIcon(QString name, NamedIcon* icon);
    /*public*/ QString getStatus();
    /*public*/ QString getNameString() override;
    /*public*/ bool showPopUp(QMenu* popup) override;
    void displayState(QString status);
    /*public*/ bool setEditItemMenu(QMenu* popup) override;
    void updateItem();
    /*public*/ void dispose() override;
    QObject* self() override {return (QObject*)this;}

signals:

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent*) override;

private:
    /*private*/ NamedBeanHandle<Sensor*>* namedOccSensor;// = NULL;
    /*private*/ NamedBeanHandle<OBlock*>* namedOccBlock;// = NULL;

    /*private*/ IndicatorTrackPaths* _pathUtil;
    /*private*/ IndicatorItemPanel* _trackPanel;
    /*private*/ QString _status;     // is a key for _iconMap
 Logger * log;
 /*private*/ void setStatus(OBlock* block, int state);
protected slots:
 /*protected*/ void editItem();

};
class ItiActionListener : public QObject, public ActionListener
{
 Q_OBJECT
    Q_INTERFACES(ActionListener)
    IndicatorTrackIcon* iti;
public:
    ItiActionListener(IndicatorTrackIcon* iti);
    QObject* self() override {return (QObject*)this;}
public slots:
 /*public*/ void actionPerformed(JActionEvent* a = 0);
};

#endif // INDICATORTRACKICON_H
