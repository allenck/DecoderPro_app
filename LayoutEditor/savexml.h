#ifndef SAVEXML_H
#define SAVEXML_H

#include <QObject>
#include <QtXml/QDomDocument>
#include "positionablelabel.h"
#include "sensoricon.h"
#include "layoutturnout.h"
#include "positionablepoint.h"
#include "tracksegment.h"
#include "levelxing.h"
#include "layoutslip.h"

class DefaultAudioManager;
class LayoutEditor;
class SaveXml : public QObject
{
    Q_OBJECT
public:
 explicit SaveXml(QObject *parent = 0);
 bool store(QString filename);

 /*public*/ void storeCommonAttributes(PositionableLabel* p, QDomElement element);
 /*public*/ QDomElement storeIcon(QString elemName, NamedIcon* icon);
 /**
  * Store the text formatting information.
  * <p>
  * This is always stored, even if the icon isn't in text mode,
  * because some uses (subclasses) of PositionableLabel flip
  * back and forth between icon and text, and want to remember their
  * formatting.
  */
 /*protected*/ void storeTextInfo(PositionableLabel* p, QDomElement element);
 QDomElement storeLayoutTurnout(LayoutTurnout* t);
 QDomElement storeTrackSegment(TrackSegment*);
 QDomElement storePositionablePoint(PositionablePoint*);
 QDomElement storeLevelXing(LevelXing*sub);
 QDomElement storeBlocks(BlockManager* b);
 QDomElement storeLayoutBlock(LayoutBlockManager* p);
 QDomElement storeRoutes(RouteManager* m);
 QDomElement storeTimebase(Timebase* t);
 void storeSensors(SensorManager* p);
 QDomElement storeLnTurnouts(TurnoutManager* t);
 QDomElement storeTurnouts(TurnoutManager* t);
 void storeLights(LightManager* l);
 void storeReporters(ReporterManager* r);
 QDomElement storeMemories(MemoryManager* m);
 QDomElement storeSignalHeads(SignalHeadManager* s);
 QDomElement storeSignalMasts(SignalMastManager* m);
 QDomElement storeLogix(LogixManager* m);
 QDomElement storeConditionals(ConditionalManager* m);
 QDomElement storeSignalMastLogic(SignalMastLogicManager* m);
 QDomElement storeBlockBossLogic(QObject* o);
 QDomElement storeOBlocks(QObject* o);
 QDomElement storeWarrants(QObject* o);
 QDomElement storeEntryExit(QObject *m);
 QDomElement storeSignalGroups(QObject *m);
 QDomElement storeSections(QObject *m);
 QDomElement storeAudio(DefaultAudioManager *m);
 QDomElement storeSlipTurnouts(QObject *m);
 QDomElement storeTurntables(QObject* m);

 /**
  * Subclass provides implementation to create the correct top
  * element, including the type information.
  * Default implementation is to use the local class here.
  * @param layoutblocks The top-level element being created
  */
// /*public*/ void setStoreElementClass(QDomElement layoutblocks);
 /*protected*/ void storeCommon(NamedBean* t, QDomElement elem);
 void storeComment(AbstractNamedBean* t, QDomElement elem);
 void storeUserName(AbstractNamedBean* t, QDomElement elem);
 void storeProperties(AbstractNamedBean* t, QDomElement elem);

signals:
    
public slots:
private:
 QDomElement root;
 QDomDocument doc;
 QObject *parent;
 LayoutEditor* p;
 Logger log;
 QDomElement createTextElement(QString tagName, QString text);
 void addPath(QDomElement e, Path* p);
 void addBeanSetting(QDomElement e, BeanSetting* bs);
 /*public*/ void setStoreElementClass(QDomElement memories);

protected:
 /*protected*/ void storeIconInfo(SensorIcon* p, QDomElement element);

};

#endif // SAVEXML_H
