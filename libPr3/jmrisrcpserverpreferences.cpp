#include "jmrisrcpserverpreferences.h"

/*public*/ /*static*/ /*final*/ int JmriSRCPServerPreferences::DEFAULT_PORT = 2056;
/*static*/ /*final*/ QString JmriSRCPServerPreferences::XML_PREFS_ELEMENT = "SRCPServerPreferences"; // NOI18N
/*static*/ /*final*/ QString JmriSRCPServerPreferences::PORT = "port"; // NOI18N

/*public*/ JmriSRCPServerPreferences::JmriSRCPServerPreferences(QString fileName, QObject* parent) : AbstractServerPreferences(fileName, parent)
{
    //super(fileName);
}

/*public*/ JmriSRCPServerPreferences::JmriSRCPServerPreferences(QObject* parent) : AbstractServerPreferences(parent) {
    //super();
}

//@Override
/*public*/ int JmriSRCPServerPreferences::getDefaultPort() {
    return (tr("4303").toInt());
}
