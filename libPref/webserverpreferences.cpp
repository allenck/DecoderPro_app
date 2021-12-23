#include "webserverpreferences.h"
#include "logger.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "preferences.h"
#include "profileutils.h"
#include "profilemanager.h"
#include "exceptions.h"
#include "fileutil.h"

//WebServerPreferences::WebServerPreferences(QObject *parent) : Bean(parent)
//{

//}
/**
 * @author Randall Wood Copyright (C) 2012
 */
///*public*/ class WebServerPreferences extends Bean {

// preferences elements
/*public*/ /*static*/ /*final*/ QString WebServerPreferences::DISALLOWED_FRAMES = "disallowedFrames"; // NOI18N
/**
 * @deprecated since 4.7.1; use {@link #DISALLOWED_FRAMES} instead
 */
//@Deprecated
/*public*/ /*static*/ /*final*/ QString WebServerPreferences::DisallowedFrames = WebServerPreferences::DISALLOWED_FRAMES;
/*public*/ /*static*/ /*final*/ QString WebServerPreferences::WEB_SERVER_PREFERENCES = "WebServerPreferences"; // NOI18N
/**
 * @deprecated since 4.7.1; use {@link #WEB_SERVER_PREFERENCES} instead
 */
//@Deprecated
/*public*/ /*static*/ /*final*/ QString WebServerPreferences::_WebServerPreferences = WebServerPreferences::WEB_SERVER_PREFERENCES;
/*public*/ /*static*/ /*final*/ QString WebServerPreferences::FRAME = "frame"; // NOI18N
/**
 * @deprecated since 4.7.1; use {@link #FRAME} instead
 */
//@Deprecated
/*public*/ /*static*/ /*final*/ QString WebServerPreferences::Frame = WebServerPreferences::FRAME;
/*public*/ /*static*/ /*final*/ QString WebServerPreferences::PORT = "port"; // NOI18N
/**
 * @deprecated since 4.7.1; use {@link #PORT} instead
 */
//@Deprecated
/*public*/ /*static*/ /*final*/ QString WebServerPreferences::Port =WebServerPreferences:: PORT;
/*public*/ /*static*/ /*final*/ QString WebServerPreferences::CLICK_DELAY = "clickDelay"; // NOI18N
/**
 * @deprecated since 4.7.1; use {@link #CLICK_DELAY} instead
 */
//@Deprecated
/*public*/ /*static*/ /*final*/ QString WebServerPreferences::ClickDelay = WebServerPreferences::CLICK_DELAY;
/*public*/ /*static*/ /*final*/ QString WebServerPreferences::REFRESH_DELAY = "refreshDelay"; // NOI18N
/**
 * @deprecated since 4.7.1; use {@link #REFRESH_DELAY} instead
 */
//@Deprecated
/*public*/ /*static*/ /*final*/ QString WebServerPreferences::RefreshDelay = WebServerPreferences::REFRESH_DELAY;
/*public*/ /*static*/ /*final*/ QString WebServerPreferences::USE_AJAX = "useAjax"; // NOI18N
/**
 * @deprecated since 4.7.1; use {@link #USE_AJAX} instead
 */
//@Deprecated
/*public*/ /*static*/ /*final*/ QString WebServerPreferences::UseAjax = WebServerPreferences::USE_AJAX;
/*public*/ /*static*/ /*final*/ QString WebServerPreferences::SIMPLE = "simple"; // NOI18N
/**
 * @deprecated since 4.7.1; use {@link #SIMPLE} instead
 */
//@Deprecated
/*public*/ /*static*/ /*final*/ QString WebServerPreferences::Simple = WebServerPreferences::SIMPLE;
/*public*/ /*static*/ /*final*/ QString WebServerPreferences::RAILROAD_NAME = "railRoadName"; // NOI18N
/**
 * @deprecated since 4.7.1; use {@link #RAILROAD_NAME} instead
 */
//@Deprecated
/*public*/ /*static*/ /*final*/ QString WebServerPreferences::RailRoadName = WebServerPreferences::RAILROAD_NAME;
/*public*/ /*static*/ /*final*/ QString WebServerPreferences::ALLOW_REMOTE_CONFIG = "allowRemoteConfig"; // NOI18N
/**
 * @deprecated since 4.7.1; use {@link #ALLOW_REMOTE_CONFIG} instead
 */
//@Deprecated
/*public*/ /*static*/ /*final*/ QString WebServerPreferences::AllowRemoteConfig = WebServerPreferences::ALLOW_REMOTE_CONFIG;
/*public*/ /*static*/ /*final*/ QString WebServerPreferences::READONLY_POWER = "readonlyPower"; // NOI18N
/**
 * @deprecated since 4.7.1; use {@link #READONLY_POWER} instead
 */
//@Deprecated
/*public*/ /*static*/ /*final*/ QString WebServerPreferences::ReadonlyPower = WebServerPreferences::READONLY_POWER;
/*public*/ /*static*/ /*final*/ QString WebServerPreferences::DISABLE_FRAME_SERVER = "disableFrames"; // NOI18N
/*public*/ /*static*/ /*final*/ QString WebServerPreferences::REDIRECT_FRAMES = "redirectFramesToPanels"; // NOI18N
// properties
/*public*/ /*static*/ /*final*/ QString WebServerPreferences::DIRTY = "dirty"; // NOI18N
/*public*/ /*static*/ /*final*/ QString WebServerPreferences::RESTART_REQUIRED = "restartRequired"; // NOI18N

/*private*/ /*final*/ /*static*/ Logger* WebServerPreferences::log = LoggerFactory::getLogger("WebServerPreferences");

/*public*/ WebServerPreferences::WebServerPreferences(QString fileName, QObject *parent) : Bean(parent)
{
 common();
    bool migrate = false;
    Preferences* sharedPreferences = ProfileUtils::getPreferences(ProfileManager::getDefault()->getActiveProfile(), "jmri.web.server.WebServer.WebServerPreferences", true);
    try {
        if (sharedPreferences->keys().length() == 0) {
            log->info("No Webserver preferences exist.");
            migrate = true;
        }
    } catch (BackingStoreException* ex) {
        log->info("No preferences file exists.");
        migrate = true;
    }
    if (migrate) {
        if (fileName != NULL) {
            try {
                this->openFile(fileName);
            } catch (FileNotFoundException ex) {
                migrate = false;
            }
        } else {
            migrate = false;
        }
    }
    this->readPreferences(sharedPreferences);
    if (migrate) {
        try {
            log->info(tr("Migrating from old Webserver preferences in %1 to new format in %2.").arg(fileName).arg(FileUtil::getAbsoluteFilename("profile:profile")));
            sharedPreferences->sync();
        } catch (BackingStoreException* ex) {
            log->error("Unable to write WebServer preferences." + ex->getMessage());
        }
    }
}

/*public*/ WebServerPreferences::WebServerPreferences(QObject *parent) : Bean(parent)
{
 common();
 Preferences* sharedPreferences = ProfileUtils::getPreferences(ProfileManager::getDefault()->getActiveProfile(), "jmri.web.server.WebServer.WebServerPreferences", true);
 this->readPreferences(sharedPreferences);
}

/*public*/ /*static*/ WebServerPreferences* WebServerPreferences::getDefault()
{
 if (InstanceManager::getNullableDefault("WebServerPreferences") == NULL)
 {
  InstanceManager::setDefault("WebServerPreferences", new WebServerPreferences());
 }
 return (WebServerPreferences*)InstanceManager::getDefault("WebServerPreferences");
}

void WebServerPreferences::common()
{
 _isDirty = false;
 // flag that changed prefs cannot be applied before restarting
 restartRequired = false;
 // initial defaults if prefs not found
  clickDelay = 1;
  refreshDelay = 5;
 useAjax = true;
 simple = false;
 disallowedFrames = QString("DecoderPro;PanelPro;LocoNet Simulator;Preferences;WiThrottle;Change Signal Head Icons;Item Palette").split(";");
 railRoadName = tr("My JMRI Railroad");
 _allowRemoteConfig;// = false;
 readonlyPower = true;
  port = 12080;
 disableFrames = true;
 redirectFramesToPanels = true;

}

/*private*/ void WebServerPreferences::readPreferences(Preferences* sharedPreferences)
{
 this->_allowRemoteConfig = sharedPreferences->getBoolean(ALLOW_REMOTE_CONFIG, this->_allowRemoteConfig);
 this->clickDelay = sharedPreferences->getInt(CLICK_DELAY, this->clickDelay);
 this->simple = sharedPreferences->getBoolean(SIMPLE, this->simple);
 this->railRoadName = sharedPreferences->get(RAILROAD_NAME, this->railRoadName);
 this->readonlyPower = sharedPreferences->getBoolean(READONLY_POWER, this->readonlyPower);
 this->refreshDelay = sharedPreferences->getInt(REFRESH_DELAY, this->refreshDelay);
 this->useAjax = sharedPreferences->getBoolean(USE_AJAX, this->useAjax);
 this->disableFrames = sharedPreferences->getBoolean(DISABLE_FRAME_SERVER, this->disableFrames);
 this->redirectFramesToPanels = sharedPreferences->getBoolean(REDIRECT_FRAMES, this->redirectFramesToPanels);
 try
 {
  Preferences* frames = sharedPreferences->node(DISALLOWED_FRAMES);
  if (frames->keys().length() != 0)
  {
   this->disallowedFrames.clear();
   foreach (QString key, frames->keys())
   {
    // throws BackingStoreException
    QString frame = frames->get(key, NULL);
    if (frame != NULL && !frame.trimmed().isEmpty()) {
        this->disallowedFrames.append(frame);
    }
   }
  }
 } catch (BackingStoreException* ex)
 {
     // this is expected if sharedPreferences have not been written previously,
     // so do nothing.
 }
 this->port = sharedPreferences->getInt(PORT, this->port);
 this->setIsDirty(false);
}

/*public*/ void WebServerPreferences::load(QDomElement child)
{
 QString a;
 a = child.attribute(CLICK_DELAY);
 if (a != NULL) {
     try {
         setClickDelay(a.toInt());
     } catch (DataConversionException* e) {
         log->debug(e->getLocalizedMessage() + e->getMessage());
     }
 }
 a = child.attribute(REFRESH_DELAY);
 if (a != NULL) {
     try {
         setRefreshDelay(a.toInt());
     } catch (DataConversionException* e) {
         log->debug(e->getLocalizedMessage() + e->getMessage());
     }
 }
 a = child.attribute(USE_AJAX);
 if (a != NULL) {
     setUseAjax(a=="true");
 }
 a = child.attribute(SIMPLE);
 if (a != NULL) {
     setSimple(a== "true");
 }
 a = child.attribute(ALLOW_REMOTE_CONFIG);
 if (a != NULL) {
     setAllowRemoteConfig(a== "true");
 }
 a = child.attribute(READONLY_POWER);
 if (a != NULL) {
     setReadonlyPower(a== "true");
 }
 a = child.attribute(PORT);
 if (a != NULL)
 {
  try {
      setPort(a.toInt());
  } catch (DataConversionException* ex) {
      setPort(12080);
      log->error("Unable to read port. Setting to default value."+ ex->getMessage());
  }
 }
 a = child.attribute(RAILROAD_NAME);
 if (a != NULL) {
     setRailroadName(a);
 }
 QDomElement df = child.firstChildElement(DISALLOWED_FRAMES);
 if (df != QDomElement())
 {
  this->disallowedFrames.clear();
  //df.getChildren(FRAME).stream().forEach((f) -> {
  QDomNodeList nl = df.elementsByTagName(FRAME);
  for(int i = 0; i < nl.size(); i++)
  {
   QDomElement f = nl.at(i).toElement();
   this->disallowedFrames.append(f.text().trimmed());
  }
 }
}

/*public*/ bool WebServerPreferences::compareValuesDifferent(WebServerPreferences* prefs) {
    if (getClickDelay() != prefs->getClickDelay()) {
        return true;
    }
    if (getRefreshDelay() != prefs->getRefreshDelay()) {
        return true;
    }
    if (isUseAjax() != prefs->isUseAjax()) {
        return true;
    }
    if (this->allowRemoteConfig() != prefs->allowRemoteConfig()) {
        return true;
    }
    if (this->isReadonlyPower() != prefs->isReadonlyPower()) {
        return true;
    }
#if 0 // TODO:
    if (!(Arrays.equals(getDisallowedFrames(), prefs->getDisallowedFrames()))) {
        return true;
    }
#else
    bool result = true;
    if( getDisallowedFrames().count() == prefs->getDisallowedFrames().count())
    {
     for(int i=0; i < prefs->getDisallowedFrames().count(); i++)
     {
      if(!(prefs->getDisallowedFrames().contains(getDisallowedFrames().at(i))))
      {
       result = false;
       break;
      }
     }
    }
    else result = false;
    if(result == true)
     return true;
#endif
    if (getPort() != prefs->getPort()) {
        return true;
    }
    return getRailroadName()!=(prefs->getRailroadName());
}

/*public*/ void WebServerPreferences::apply(WebServerPreferences* prefs) {
    setClickDelay(prefs->getClickDelay());
    setRefreshDelay(prefs->getRefreshDelay());
    setUseAjax(prefs->isUseAjax());
    this->setAllowRemoteConfig(prefs->allowRemoteConfig());
    this->setReadonlyPower(prefs->isReadonlyPower());
    setDisallowedFrames(prefs->getDisallowedFrames());
    setPort(prefs->getPort());
    setRailroadName(prefs->getRailroadName());
}

/*public*/ /*final*/ void WebServerPreferences::openFile(QString fileName) //throw (FileNotFoundException)
{

    WebServerPreferencesXml* prefsXml = new WebServerPreferencesXml();
    File* file = new File(fileName);
    QDomElement root;
    try {
        root = prefsXml->rootFromFile(file);
    } catch (FileNotFoundException ex) {
        log->debug("Could not find Web Server preferences file. Normal if preferences have not been saved before.");
        throw ex;
    } catch (IOException /*| JDOMException*/ ex) {
        log->error("Exception while loading web server preferences: " + ex.getMessage());
        root = QDomElement();
    }
    if (root != QDomElement()) {
        load(root);
    }

}

/*public*/ void WebServerPreferences::save()
{
 Preferences* sharedPreferences = ProfileUtils::getPreferences(ProfileManager::getDefault()->getActiveProfile(), "jmri.web.server.WebServerPreferences", true);
 sharedPreferences->putInt(PORT, this->getPort());
 sharedPreferences->putInt(CLICK_DELAY, this->getClickDelay());
 sharedPreferences->putInt(REFRESH_DELAY, this->getRefreshDelay());
 sharedPreferences->putBoolean(USE_AJAX, this->isUseAjax());
 sharedPreferences->putBoolean(SIMPLE, this->isSimple());
 sharedPreferences->putBoolean(ALLOW_REMOTE_CONFIG, this->allowRemoteConfig());
 sharedPreferences->putBoolean(READONLY_POWER, this->isReadonlyPower());
 sharedPreferences->put(RAILROAD_NAME, getRailroadName());
 sharedPreferences->putBoolean(DISABLE_FRAME_SERVER, this->isDisableFrames());
 sharedPreferences->putBoolean(REDIRECT_FRAMES, this->redirectFramesToPanels);
 try
 {
  Preferences* node = sharedPreferences->node(DISALLOWED_FRAMES);
//        this->disallowedFrames.stream().forEach((frame) ->
  foreach(QString frame, disallowedFrames)
  {
   node->put(QString::number(this->disallowedFrames.indexOf(frame)), frame);
  } //);
  if (this->disallowedFrames.size() < node->keys().length())
  {
   for (int i = node->keys().length() - 1; i >= this->disallowedFrames.size(); i--)
   {
    node->remove(QString::number((i)));
   }
  }
  sharedPreferences->sync();
  setIsDirty(false);  //  Resets only when stored
 }
 catch (BackingStoreException* ex) {
  log->error("Exception while saving web server preferences", ex);
 }
}

/*public*/ bool WebServerPreferences::isDirty() {
    return _isDirty;
}

/*public*/ void WebServerPreferences::setIsDirty(bool value) {
    bool old = this->_isDirty;
    if (old != value) {
        this->_isDirty = value;
        this->firePropertyChange(DIRTY, old, value);
    }
}

/*public*/ int WebServerPreferences::getClickDelay() {
    return clickDelay;
}

/*public*/ void WebServerPreferences::setClickDelay(int value) {
    int old = this->clickDelay;
    if (old != value) {
        this->clickDelay = value;
        this->firePropertyChange(CLICK_DELAY, old, value);
    }
}

/*public*/ int WebServerPreferences::getRefreshDelay() {
    return refreshDelay;
}

/*public*/ void WebServerPreferences::setRefreshDelay(int value) {
    int old = this->refreshDelay;
    if (old != value) {
        this->refreshDelay = value;
        this->firePropertyChange(REFRESH_DELAY, old, value);
    }
}

/*public*/ QVector<QString> WebServerPreferences::getDisallowedFrames() {
    return this->disallowedFrames.toVector(); //new String[this->disallowedFrames.size()]);
}

/*public*/ bool WebServerPreferences::isUseAjax() {
    return useAjax;
}

/*public*/ void WebServerPreferences::setUseAjax(bool useAjax) {
    bool old = this->useAjax;
    if (old != useAjax) {
        this->useAjax = useAjax;
        this->firePropertyChange(USE_AJAX, old, useAjax);
    }
}

/*public*/ bool WebServerPreferences::isSimple() {
    return simple;
}

/*public*/ void WebServerPreferences::setSimple(bool value) {
    bool old = this->simple;
    if (old != value) {
        this->simple = value;
        this->firePropertyChange(SIMPLE, old, value);
    }
}

/*public*/ bool WebServerPreferences::allowRemoteConfig() {
    return this->_allowRemoteConfig;
}

/*public*/ void WebServerPreferences::setAllowRemoteConfig(bool value) {
    bool old = this->_allowRemoteConfig;
    if (old != value) {
        this->_allowRemoteConfig = value;
        this->firePropertyChange(ALLOW_REMOTE_CONFIG, old, value);
    }
}

/**
 * @return the readonlyPower
 */
/*public*/ bool WebServerPreferences::isReadonlyPower() {
    return readonlyPower;
}

/**
 * @param readonlyPower the readonlyPower to set
 */
/*public*/ void WebServerPreferences::setReadonlyPower(bool readonlyPower) {
    this->readonlyPower = readonlyPower;
}

/*public*/ void WebServerPreferences::setDisallowedFrames(QVector<QString> disallowedFrames)
{
 QVector<QString> old = this->getDisallowedFrames();

 bool bArraysEqual=true;
 if(old.count() != getDisallowedFrames().count())
  bArraysEqual = false;
 else
 foreach(QString s, old)
 {
  if(!disallowedFrames.contains(s))
  {
   bArraysEqual= false;
   break;
  }
 }
 //if (!Arrays.equals(old, disallowedFrames))
 if(!bArraysEqual)
 {
     this->disallowedFrames.clear();
     //this->disallowedFrames.addAll(Arrays.asList(disallowedFrames));
     foreach(QString s, disallowedFrames)
      this->disallowedFrames.append(s);
     this->firePropertyChange(DISALLOWED_FRAMES, old.count(), disallowedFrames.count()); // ?? Should the arrays be posted?
 }
}

/*public*/ int WebServerPreferences::getPort() {
    return port;
}

/*public*/ void WebServerPreferences::setPort(int value)
{
 int old = this->port;
 if (old != value) {
     this->port = value;
     this->firePropertyChange(PORT, old, value);
     this->setRestartRequired();
 }
}

/**
 * @return the railRoadName
 */
/*public*/ QString WebServerPreferences::getRailroadName() {
    return railRoadName;
}

/**
 * @param railRoadName the railRoadName to set
 */
/*public*/ void WebServerPreferences::setRailroadName(QString railRoadName)
{
 QString old = this->railRoadName;
 if ((old != NULL && old!=(railRoadName)) || railRoadName != NULL)
 {
  if (railRoadName != NULL)
  {
   this->railRoadName = railRoadName;
  }
  else
  {
   this->railRoadName = tr("My JMRI Railroad");
  }
  this->firePropertyChange(RAILROAD_NAME, old, this->railRoadName);
 }
}

/**
 * Test if the railroad name has been set by user.
 *
 * @return true if user has not set the railroad name.
 */
/*public*/ bool WebServerPreferences::isDefaultRailroadName() {
    return this->getRailroadName()==(tr("My JMRI Railroad"));
}

/**
 * Get the default railroad name. This method exists solely to support unit
 * testing.
 *
 * @return The default railroad name
 */
/*public*/ QString WebServerPreferences::getDefaultRailroadName() {
    return tr("My JMRI Railroad");
}

/**
 * @return true if displaying frames in web pages is disabled, false
 *         otherwise
 */
/*public*/ bool WebServerPreferences::isDisableFrames() {
    return disableFrames;
}

/**
 * Set whether or not frames are returned when requests for frames are made
 * from web pages.
 *
 * @param disableFrames true to prevent frames from being displayed in web
 *                      pages
 */
/*public*/ void WebServerPreferences::setDisableFrames(bool disableFrames) {
    bool old = this->disableFrames;
    if (old != disableFrames) {
        this->disableFrames = disableFrames;
        this->firePropertyChange(DISABLE_FRAME_SERVER, old, disableFrames);
    }
}

/**
 * Are requests for frames redirected to panels when frames are disabled?
 *
 * @return true if frames should be redirected to panels, false otherwise
 */
/*public*/ bool WebServerPreferences::isRedirectFramesToPanels() {
    return redirectFramesToPanels;
}

/**
 * Set whether or not requests for frames should be redirected to panels
 * when frames are disabled.
 *
 * @param redirectFramesToPanels true if frames should be redirected to
 *                               panels, false otherwise
 */
/*public*/ void WebServerPreferences::setRedirectFramesToPanels(bool redirectFramesToPanels) {
    bool old = this->redirectFramesToPanels;
    if (old != redirectFramesToPanels) {
        this->redirectFramesToPanels = redirectFramesToPanels;
        this->firePropertyChange(REDIRECT_FRAMES, old, this->redirectFramesToPanels);
    }
}

/**
 * Check if some preferences cannot be applied without restarting JMRI.
 *
 * @return true if JMRI needs to be restarted, false otherwise.
 */
/*public*/ bool WebServerPreferences::isRestartRequired() {
    return this->restartRequired;
}

/**
 * Set if restart needs to be required for some preferences to take effect.
 *
 * @param restartRequired true if JMRI needs to be restarted.
 */
/*private*/ void WebServerPreferences::setRestartRequired() {
    if (!this->restartRequired) {
        this->restartRequired = true;
        this->firePropertyChange(RESTART_REQUIRED, false, true);
    }
}

//@Override
/*protected*/ void WebServerPreferences::firePropertyChange(QString propertyName, QVariant oldValue, QVariant newValue) {
    this->propertyChangeSupport->firePropertyChange(propertyName, oldValue, newValue);
    if (DIRTY!=(propertyName)) {
        this->setIsDirty(true);
    }
}

//@Override
/*protected*/ void WebServerPreferences::firePropertyChange(QString propertyName, bool oldValue, bool newValue) {
    this->propertyChangeSupport->firePropertyChange(propertyName, oldValue, newValue);
    if (DIRTY!=(propertyName)) {
        this->setIsDirty(true);
    }
}

//@Override
/*protected*/ void WebServerPreferences::firePropertyChange(QString propertyName, int oldValue, int newValue) {
    this->propertyChangeSupport->firePropertyChange(propertyName, oldValue, newValue);
    if (DIRTY != propertyName) {
        this->setIsDirty(true);
    }
}

///*private*/ static class WebServerPreferencesXml extends XmlFile {
//}

