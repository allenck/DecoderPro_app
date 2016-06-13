#ifndef LOADXML_H
#define LOADXML_H

#include <QObject>
#include <QtXml/QDomDocument>
#include "instancemanager.h"
#include <QColor>
#include <QSize>
#include "tracksegment.h"
#include "abstractmemory.h"

class XmlAdapter;
class LayoutEditor;
class LoadXml : public QObject
{
    Q_OBJECT
public:
 explicit LoadXml(QObject *parent = 0);
 int loadfile(QString fileName);
 QStringList _Colors;
 QList<QColor> _colors;
 QMap<QString, QColor> colorMap;

signals:
 void newSensor(QString name, int x, int y);
public slots:

private:
 QDomDocument doc;
 bool processBlocks(QDomElement mimetype);
 void processSensors(QDomElement e);
 void processTurnouts(QDomElement e);
 bool processLights(QDomElement e);
 void processLayoutBlocks(QDomElement e);
 void processRoutes(QDomElement e);
 bool processTimebase(QDomElement e);
 void processLayoutEditor(QDomElement e);
 void processPanelEditor(QDomElement e);
 bool processReporters(QDomElement mimetype);
 void processMemories(QDomElement mimetype);
 bool processSignalHeads(QDomElement e);
 bool processSignalMasts(QDomElement e);
 bool processSignalMastLogics(QDomElement e);
 bool processBlockBossLogic(QDomElement e);
 bool processLogix(QDomElement e);
 bool processConditionals(QDomElement e);
 bool processWarrants(QDomElement e);
 bool processOBlocks(QDomElement e);
 bool processEntryExitPairs(QDomElement e);
 bool processSections(QDomElement e);
 bool processSignalGroups(QDomElement e);
 bool processPositionableCircle(QDomElement e);
 bool processPositionableRectangle(QDomElement e);
 bool processPositionableRoundRect(QDomElement e);
 bool processPositionableEllipse(QDomElement e);
 bool processAudio(QDomElement e);
 XmlAdapter* loadXmlAdapter(QDomElement e);

 /*public*/ NamedIcon* loadIcon(PositionableLabel* l, QString attrName, QDomElement element,                                 QString name, LayoutEditor* ed);
 /*public*/ void loadCommonAttributes(PositionableLabel* l, int defaultLevel, QDomElement element);
 void loadBlock(QDomElement element);
 /*public*/ void loadPath(Block* block, QDomElement element) throw (JmriConfigureXmlException);
 /*public*/ void loadBeanSetting(Path* path, QDomElement element);
 void loadProperties(NamedBean* t, QDomElement elem);


 BlockManager* blockMgr;
 SensorManager* sensorMgr;
 LayoutEditor* editor;
 QSize layoutSize;
 QPoint scaleLoc(int x, int y);
 QPointF scaleLoc(double x, double y);
 /*protected*/ void loadCommon(NamedBean* t, QDomElement elem);
 void loadValue(QDomElement memory, Memory* m);
 /*protected*/ QString getUserName(QDomNodeList beanList, int i);
 /*protected*/ QString getUserName(QDomElement elem);
 /*protected*/ QString getSystemName(QDomElement elem);
 /*protected*/ NamedIcon* getNamedIcon(QString childName, QDomElement element,                                        QString name, LayoutEditor* ed);
 /*protected*/ void loadTextInfo(PositionableLabel* l, QDomElement element);
 QList<LayoutBlock*> layoutBlocks;
 Logger* log;
 void loadComment(NamedBean* t, QDomNodeList beanList, int i) ;
 void loadComment(NamedBean* t, QDomElement elem);

};

#endif // LOADXML_H
