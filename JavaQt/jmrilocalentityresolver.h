#ifndef JMRILOCALIDENTITYRESOLVER_H
#define JMRILOCALIDENTITYRESOLVER_H
#include "entityresolver.h"

class Logger;
class JmriLocalEntityResolver : public EntityResolver
{
 Q_OBJECT
public:
 JmriLocalEntityResolver();
 /*public*/ InputSource* resolveEntity(QString /*public*/Id, QString systemId) /*throw (SAXException, IOException)*/;

private:
 Logger* log;
 static /*private*/ bool toldYouOnce;// = false;

};

#endif // JMRILOCALIDENTITYRESOLVER_H
