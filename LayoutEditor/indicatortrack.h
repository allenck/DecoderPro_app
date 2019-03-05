#ifndef INDICATORTRACK_H
#define INDICATORTRACK_H
#include "positionable.h"
#include "namedbeanhandle.h"

class Sensor;
class OBlock;
/**
 * Defines track objects that display status color.
 * <P>
 *
 * @author Pete Cressman Copyright (c) 2010
 * @version $Revision: 21470 $
 */
/*public*/ /*interface*/ class IndicatorTrack : public Positionable
{
  //Q_OBJECT
 public:
    /*public*/ virtual void setOccSensor(QString pName) = 0;
    /*public*/ virtual void setOccSensorHandle(NamedBeanHandle<Sensor*> senHandle) = 0;
    /*public*/ virtual Sensor* getOccSensor() = 0;
    /*public*/ virtual NamedBeanHandle <Sensor*> getNamedOccSensor() = 0;

    /*public*/ virtual void setOccBlock(QString pName) = 0;
    /*public*/ virtual void setOccBlockHandle(NamedBeanHandle<OBlock*>* blockHandle) = 0;
    /*public*/ virtual OBlock* getOccBlock() = 0;
    /*public*/ virtual NamedBeanHandle <OBlock*> getNamedOccBlock() = 0;

    /*public*/ virtual void setShowTrain(bool set) = 0;
    /*public*/ virtual bool showTrain() = 0;
    /*public*/ virtual QStringList* getPaths() {return NULL;}
    /*public*/ virtual void addPath(QString path) = 0;
    /*public*/ virtual void removePath(QString path) = 0;
    /*public*/ virtual void setStatus(int state) = 0;
};
Q_DECLARE_INTERFACE(IndicatorTrack, "IndicatorTrack")
#endif // INDICATORTRACK_H
