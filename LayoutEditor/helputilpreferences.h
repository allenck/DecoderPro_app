#ifndef HELPUTILPREFERENCES_H
#define HELPUTILPREFERENCES_H

#include <preferencesbean.h>
#include "instancemanagerautodefault.h"

class Preferences;
class HelpUtilPreferences : public PreferencesBean, public InstanceManagerAutoDefault
{
  Q_OBJECT
  Q_INTERFACES(InstanceManagerAutoDefault)
 public:
  explicit HelpUtilPreferences(QObject *parent = nullptr);
  ~HelpUtilPreferences() {}
  HelpUtilPreferences(const HelpUtilPreferences&) : PreferencesBean(nullptr) {}
  /*public*/ static /*final*/ QString OPEN_HELP_ONLINE;// = "openHelpOnline";
  /*public*/ static /*final*/ QString OPEN_HELP_ON_FILE;// = "openHelpOnFile";
  /*public*/ static /*final*/ QString OPEN_HELP_ON_JMRI_WEB_SERVER;// = "openHelpOnJMRIWebServer";
  /*public*/ bool compareValuesDifferent(HelpUtilPreferences* prefs);
  /*public*/ void apply(HelpUtilPreferences* prefs);
  /*public*/ void save();
  /*public*/ void setOpenHelpOnline(bool value);
  /*public*/ bool getOpenHelpOnline();
  /*public*/ void setOpenHelpOnFile(bool value);
  /*public*/ bool getOpenHelpOnFile();
  /*public*/ void setOpenHelpOnJMRIWebServer(bool value);
  /*public*/ bool getOpenHelpOnJMRIWebServer();

 private:
  /*private*/ bool _openHelpOnline = false;
  /*private*/ bool _openHelpOnFile = true;
  /*private*/ bool _openHelpOnJMRIWebServer = false;
  /*private*/ void readPreferences(Preferences* sharedPreferences);

};
Q_DECLARE_METATYPE(HelpUtilPreferences)
#endif // HELPUTILPREFERENCES_H
