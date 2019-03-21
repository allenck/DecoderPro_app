#ifndef JMRISRCPSERVERPREFERENCES_H
#define JMRISRCPSERVERPREFERENCES_H
#include "abstractserverpreferences.h"

/*public*/ class JmriSRCPServerPreferences : public  AbstractServerPreferences {

    /*public*/ static /*final*/ int DEFAULT_PORT;// = 2056;
    static /*final*/ QString XML_PREFS_ELEMENT;// = "SRCPServerPreferences"; // NOI18N
    static /*final*/ QString PORT;// = "port"; // NOI18N

    /*public*/ JmriSRCPServerPreferences(QString fileName, QObject*parent = nullptr);
    /*public*/ JmriSRCPServerPreferences(QObject*parent = nullptr);
    /*public*/ int getDefaultPort() ;

    friend class JmriSRCPServerManager;
};
#endif // JMRISRCPSERVERPREFERENCES_H
