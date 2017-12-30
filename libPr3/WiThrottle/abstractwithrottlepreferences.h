#ifndef ABSTRACTWITHROTTLEPREFERENCES_H
#define ABSTRACTWITHROTTLEPREFERENCES_H

#include <QObject>
#include "xmlfile.h"

class AbstractWiThrottlePreferences : public QObject
{
 Q_OBJECT
public:
 explicit AbstractWiThrottlePreferences(QObject *parent = 0);
 /*public*/ void openFile(QString fileName);
 /*public*/ void save();

signals:

public slots:
private:
 /*private*/ QString fileName;
 /*abstract*/ virtual void load(QDomElement child);

 /*abstract*/ virtual QDomElement store();
 Logger* log;

};
/*public*/ /*static*/ class AbstractWiThrottlePreferencesXml : public XmlFile
{
 Q_OBJECT
};

#endif // ABSTRACTWITHROTTLEPREFERENCES_H
