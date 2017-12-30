#ifndef LOGGERFACTORY_H
#define LOGGERFACTORY_H

#include <QObject>
#include "logger.h"

class Logger;
class LoggerFactory : public QObject
{
 Q_OBJECT
public:
 explicit LoggerFactory(QObject *parent = 0);
 /*public*/ static Logger* getLogger(QString name);

signals:

public slots:

private:
 static /*private*/ QMap<QString, Logger*>* loggerMap;
};

#endif // LOGGERFACTORY_H
