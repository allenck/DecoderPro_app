#include "simpleserverpreferences.h"

// /*public*/ class SimpleServerPreferences extends jmri.jmris.AbstractServerPreferences {

/*public*/ /*static*/ /*final*/ int SimpleServerPreferences::DEFAULT_PORT = 2056;
/*static*/ /*final*/ QString SimpleServerPreferences::XML_PREFS_ELEMENT = "SimpleServerPreferences"; // NOI18N
/*static*/ /*final*/ QString SimpleServerPreferences::PORT = "port"; // NOI18N

/*public*/ SimpleServerPreferences::SimpleServerPreferences(QString fileName, QObject* parent) : AbstractServerPreferences(fileName, parent){
    //super(fileName);
}

/*public*/ SimpleServerPreferences::SimpleServerPreferences(QObject *parent) : AbstractServerPreferences(parent){
    //super();
}

//@Override
/*public*/ int SimpleServerPreferences::getDefaultPort() {
    return (/*tr("SimpleServerPort")*/2048);
}

//@Override
/*public*/ QString SimpleServerPreferences::getClass()
{
 return "jmri.jmris.simpleserver.SimpleServerPreferences";
}
