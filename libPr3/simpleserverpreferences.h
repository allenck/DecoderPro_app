#ifndef SIMPLESERVERPREFERENCES_H
#define SIMPLESERVERPREFERENCES_H
#include "abstractserverpreferences.h"

class SimpleServerPreferences : public AbstractServerPreferences
{
public:
 SimpleServerPreferences(QObject* parent =nullptr);
 /*public*/ static /*final*/ int DEFAULT_PORT;// = 2056;
 /*public*/ SimpleServerPreferences(QString fileName, QObject* parent =nullptr);
 /*public*/ int getDefaultPort();

private:
 static /*final*/ QString XML_PREFS_ELEMENT;// = "SimpleServerPreferences"; // NOI18N
 static /*final*/ QString PORT;// = "port"; // NOI18N

};

#endif // SIMPLESERVERPREFERENCES_H
