#ifndef WHEREUSEDCOLLECTORS_H
#define WHEREUSEDCOLLECTORS_H

#include <QObject>

class NamedBean;
class Logger;
class WhereUsedCollectors : public QObject
{
 Q_OBJECT
public:
 static QString checkTurnouts(NamedBean* bean);
 static QString checkLights(NamedBean* bean);
 static QString checkRoutes(NamedBean* bean);
 static QString checkBlocks(NamedBean* bean);
 static QString checkLayoutBlocks(NamedBean* bean);
 static QString checkSignalHeadLogic(NamedBean* bean);
 static QString checkSignalMastLogic(NamedBean* bean);
 static QString checkSignalGroups(NamedBean* bean);
 static QString checkOBlocks(NamedBean* bean);
 static QString checkWarrants(NamedBean* bean);
 static QString checkEntryExit(NamedBean* bean);
 static QString checkLogixConditionals(NamedBean* bean);
 static QString checkSections(NamedBean* bean);
 static QString checkTransits(NamedBean* bean);
 static QString checkPanels(NamedBean* bean);
 static QString checkCTC(NamedBean *bean);
 static QString addHeader(QString sb, QString bundleKey);

signals:

public slots:
private:
 static Logger* log;
 explicit WhereUsedCollectors(QObject *parent = nullptr);

};

#endif // WHEREUSEDCOLLECTORS_H
