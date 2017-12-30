#ifndef WEBSERVERPREFERENCES_H
#define WEBSERVERPREFERENCES_H

#include "bean.h"
#include <QVector>
#include <QtXml>
#include "exceptions.h"
#include "xmlfile.h"

class Preferences;
class Logger;
class WebServerPreferences : public Bean
{
 Q_OBJECT
public:
 explicit WebServerPreferences(QObject *parent = 0);
 /*public*/ static /*final*/ QString DISALLOWED_FRAMES;// = "disallowedFrames"; // NOI18N
 QT_DEPRECATED/*public*/ static /*final*/ QString DisallowedFrames;// = DISALLOWED_FRAMES;
 QT_DEPRECATED/*public*/ static /*final*/ QString WEB_SERVER_PREFERENCES;// = "WebServerPreferences"; // NOI18N
 QT_DEPRECATED/*public*/ static /*final*/ QString _WebServerPreferences;// = WEB_SERVER_PREFERENCES;
 QT_DEPRECATED/*public*/ static /*final*/ QString FRAME;// = "frame"; // NOI18N
 /**
  * @deprecated since 4.7.1; use {@link #FRAME} instead
  */
 //@Deprecated
 QT_DEPRECATED/*public*/ static /*final*/ QString Frame;// = FRAME;
 QT_DEPRECATED/*public*/ static /*final*/ QString PORT;// = "port"; // NOI18N
 /**
  * @deprecated since 4.7.1; use {@link #PORT} instead
  */
 //@Deprecated
 QT_DEPRECATED/*public*/ static /*final*/ QString Port;// = PORT;
 QT_DEPRECATED/*public*/ static /*final*/ QString CLICK_DELAY;// = "clickDelay"; // NOI18N
 /**
  * @deprecated since 4.7.1; use {@link #CLICK_DELAY} instead
  */
 //@Deprecated
 QT_DEPRECATED/*public*/ static /*final*/ QString ClickDelay;// = CLICK_DELAY;
 QT_DEPRECATED/*public*/ static /*final*/ QString REFRESH_DELAY;// = "refreshDelay"; // NOI18N
 /**
  * @deprecated since 4.7.1; use {@link #REFRESH_DELAY} instead
  */
 //@Deprecated
 QT_DEPRECATED/*public*/ static /*final*/ QString RefreshDelay;// = REFRESH_DELAY;
 QT_DEPRECATED/*public*/ static /*final*/ QString USE_AJAX;// = "useAjax"; // NOI18N
 /**
  * @deprecated since 4.7.1; use {@link #USE_AJAX} instead
  */
 //@Deprecated
 QT_DEPRECATED/*public*/ static /*final*/ QString UseAjax;// = USE_AJAX;
 QT_DEPRECATED/*public*/ static /*final*/ QString SIMPLE;// = "simple"; // NOI18N
 /**
  * @deprecated since 4.7.1; use {@link #SIMPLE} instead
  */
 //@Deprecated
 QT_DEPRECATED/*public*/ static /*final*/ QString Simple;// = SIMPLE;
 QT_DEPRECATED/*public*/ static /*final*/ QString RAILROAD_NAME;// = "railRoadName"; // NOI18N
 /**
  * @deprecated since 4.7.1; use {@link #RAILROAD_NAME} instead
  */
 //@Deprecated
 QT_DEPRECATED/*public*/ static /*final*/ QString RailRoadName;// = RAILROAD_NAME;
 QT_DEPRECATED/*public*/ static /*final*/ QString ALLOW_REMOTE_CONFIG;// = "allowRemoteConfig"; // NOI18N
 /**
  * @deprecated since 4.7.1; use {@link #ALLOW_REMOTE_CONFIG} instead
  */
 //@Deprecated
 QT_DEPRECATED/*public*/ static /*final*/ QString AllowRemoteConfig;// = ALLOW_REMOTE_CONFIG;
 QT_DEPRECATED/*public*/ static /*final*/ QString READONLY_POWER;// = "readonlyPower"; // NOI18N
 /**
  * @deprecated since 4.7.1; use {@link #READONLY_POWER} instead
  */
 //@Deprecated
 QT_DEPRECATED/*public*/ static /*final*/ QString ReadonlyPower;// = READONLY_POWER;
 QT_DEPRECATED/*public*/ static /*final*/ QString DISABLE_FRAME_SERVER;// = "disableFrames"; // NOI18N
 QT_DEPRECATED/*public*/ static /*final*/ QString REDIRECT_FRAMES;// = "redirectFramesToPanels"; // NOI18N
 /*public*/ static /*final*/ QString DIRTY;// = "dirty"; // NOI18N
 /*public*/ static /*final*/ QString RESTART_REQUIRED;// = "restartRequired"; // NOI18N


 /*public*/ WebServerPreferences(QString fileName,QObject *parent = 0);
 /*public*/ static WebServerPreferences* getDefault();
 /*public*/ int getPort();
 /*public*/ void setPort(int value);
 /*public*/ QString getRailRoadName();
 /*public*/ void setRailRoadName(QString railRoadName);
 /*public*/ bool isDefaultRailroadName();
 /*public*/ QString getDefaultRailroadName();
 /*public*/ void load(QDomElement child);
 /*public*/ bool compareValuesDifferent(WebServerPreferences* prefs);
 /*public*/ void apply(WebServerPreferences* prefs);
 /*public*/ /*final*/ void openFile(QString fileName) throw (FileNotFoundException);
 /*public*/ bool isDirty();
 /*public*/ void setIsDirty(bool value);
 /*public*/ int getClickDelay();
 /*public*/ void setClickDelay(int value) ;
 /*public*/ int getRefreshDelay();
 /*public*/ void setRefreshDelay(int value);
 /*public*/ QVector<QString> getDisallowedFrames();
 /*public*/ bool isUseAjax();
 /*public*/ void setUseAjax(bool useAjax);
 /*public*/ bool isSimple();
 /*public*/ void setSimple(bool value);
 /*public*/ bool allowRemoteConfig() ;
 /*public*/ void setAllowRemoteConfig(bool value);
 /*public*/ bool isReadonlyPower();
 /*public*/ void setReadonlyPower(bool readonlyPower);
 /*public*/ void setDisallowedFrames(QVector<QString> disallowedFrames);
 /*public*/ bool isRestartRequired() ;
 /*public*/ void save();
 /*public*/ bool isDisableFrames();
 /*public*/ void setDisableFrames(bool disableFrames);
 /*public*/ bool isRedirectFramesToPanels();
 /*public*/ void setRedirectFramesToPanels(bool redirectFramesToPanels);


signals:

public slots:

private:
 void common();
 // Flag that prefs have not been saved
 /*private*/ bool _isDirty;// = false;
 // flag that changed prefs cannot be applied before restarting
 /*private*/ bool restartRequired;// = false;
 // initial defaults if prefs not found
 /*private*/ int clickDelay;// = 1;
 /*private*/ int refreshDelay;// = 5;
 /*private*/ bool useAjax;// = true;
 /*private*/ bool simple;// = false;
 /*private*/ /*final*/ QStringList disallowedFrames;// = new ArrayList<>(Arrays.asList(Bundle.getMessage("DefaultDisallowedFrames").split(";")));
 /*private*/ QString railRoadName;// = tr("My JMRI Railroad");
 /*private*/ bool _allowRemoteConfig;// = false;
 /*private*/ bool readonlyPower;// = true;
 /*private*/ int port;// = 12080;
 /*private*/ bool disableFrames;// = true;
 /*private*/ bool redirectFramesToPanels;// = true;
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger(WebServerPreferences.class.getName());
 /*private*/ void readPreferences(Preferences* sharedPreferences);
 /*private*/ void setRestartRequired();

protected:
 /*protected*/ void firePropertyChange(QString propertyName, QVariant oldValue, QVariant newValue);
 /*protected*/ void firePropertyChange(QString propertyName, bool oldValue, bool newValue);
 /*protected*/ void firePropertyChange(QString propertyName, int oldValue, int newValue);

};
/*private*/ /*static*/ class WebServerPreferencesXml : public XmlFile
{
public:
};

#endif // WEBSERVERPREFERENCES_H
