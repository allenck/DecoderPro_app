#ifndef ENTRYEXITTESTTOOLS_H
#define ENTRYEXITTESTTOOLS_H

#include <QObject>
#include "exceptions.h"

class LayoutEditor;
class PointDetails;
class EntryExitPairs;
class Source;
class Sensor;
class DestinationPoints;
class EntryExitTestTools : public QObject
{
 Q_OBJECT
public:
 explicit EntryExitTestTools(QObject *parent = nullptr);
 static QMap<QString, LayoutEditor*>* getPanels() throw (Exception);
 PointDetails* getPoint(Sensor* sensor, LayoutEditor* panel, EntryExitPairs* eep);
 Source* getSourceInstance(Sensor* sensor, LayoutEditor* panel, EntryExitPairs* eep);
 DestinationPoints* getDestinationPoint(Sensor* srcSensor, Sensor* destSensor, LayoutEditor* panel,  EntryExitPairs* eep);

signals:

public slots:
};

#endif // ENTRYEXITTESTTOOLS_H
