#ifndef JYNSTRUMENTFACTORY_H
#define JYNSTRUMENTFACTORY_H

#include <QObject>
#include "jynstrument.h"
#include "exceptions.h"


class Logger;
class JynstrumentFactory : public QObject
{
 Q_OBJECT
public:
 /*public*/ static Jynstrument* createInstrument(QString path, QObject* context);


signals:

public slots:

private:
     /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger("JynstrumentFactory");
 /*private*/ static /*final*/ QString instanceName;// = "jynstrumentObjectInstance";
 /*private*/ static QString validate(QString path);

};

class ScriptException : public Exception
{
 ScriptException(QString msg) : Exception(msg) {}
};
#endif // JYNSTRUMENTFACTORY_H
