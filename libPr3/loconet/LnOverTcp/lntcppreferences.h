#ifndef LNTCPPREFERENCES_H
#define LNTCPPREFERENCES_H
#include "preferencesbean.h"

class Preferences;
class Logger;
class LnTcpPreferences : public PreferencesBean
{
 Q_OBJECT
public:
 /*public*/ LnTcpPreferences(QObject* parent = nullptr);

 /*public*/ /*final*/ static QString PORT;// = jmri.web.server.WebServerPreferences.PORT;
 /*public*/ static LnTcpPreferences* getDefault();
 /*public*/ void savePreferences();
 /*public*/ int getPort();
 /*public*/ void setPort(int value);

private:
 /*private*/ static /*final*/ QString PORT_NUMBER_KEY;// = "PortNumber";
 /*private*/ static /*final*/ QString SETTINGS_FILE_NAME;// = "LocoNetOverTcpSettings.ini";
 /*private*/ int port;// = 1234;
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger(LnTcpPreferences.class);
 /*private*/ void readPreferences(Preferences* sharedPreferences);
 bool isPreferencesValid();


friend class LnTcpPreferencesPanel;
};

#endif // LNTCPPREFERENCES_H
