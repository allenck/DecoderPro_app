#ifndef THROTTLEFRAME_H
#define THROTTLEFRAME_H
#include <QDockWidget>
#include "controlpanel.h"
#include "functionpanel.h"
#include "backgroundpanel.h"
#include "addresspanel.h"
#include "throttlewindow.h"
class FrameListener;
class ThrottleFrame : public QMainWindow, public AddressListener
{
  Q_OBJECT
  Q_INTERFACES(AddressListener)

 public:
  ThrottleFrame(ThrottleWindow* tw);
  /*public*/ static QString getDefaultThrottleFolder();
  /*public*/ static QString getDefaultThrottleFilename();
  /*public*/ ThrottleWindow* getThrottleWindow();
  /*public*/ ControlPanel* getControlPanel();
  /*public*/ FunctionPanel* getFunctionPanel();
  /*public*/ AddressPanel* getAddressPanel();
  /*public*/ RosterEntry* getRosterEntry();
  /*public*/ void toFront();
  /*public*/ SpeedPanel* getSpeedPanel();
  /*public*/ void setLocation(int x, int y);
  /*public*/ void setTitle(QString txt);
  /*public*/ QString getTitle();
  /*public*/ void loadThrottle(QString sfile);
  /*public*/ void dispose();
  /*public*/ void saveRosterChanges();
  /*public*/ QDomElement getXml();
  /*public*/ void setXml(QDomElement e);
  /*public*/ void setFrameTitle();
  /*public*/ void saveThrottle();
  /*public*/ void saveThrottleAs();
  /*public*/ QString getLastUsedSaveFile();
  /*public*/ void setLastUsedSaveFile(QString lusf);
  /*public*/ static void setTransparentBackground(QObject* jcomp);
  /*public*/ static void setTransparent(QWidget jcomp);
  /*public*/ static void setTransparent(QWidget* jcomp, bool transparency);
  /*private*/ static void setTransparent(QObjectList comps, bool transparency);

 public slots:
  /*public*/ void notifyAddressChosen(LocoAddress* l);
  /*public*/ void notifyAddressReleased(LocoAddress* la);
  /*public*/ void notifyAddressThrottleFound(DccThrottle* throttle);
  /*public*/ void notifyConsistAddressChosen(int newAddress, bool isLong);
  /*public*/ void notifyConsistAddressReleased(int address, bool isLong);
  /*public*/ void notifyConsistAddressThrottleFound(DccThrottle* throttle);

 signals:
     void throttleWindowupdate(PropertyChangeEvent*);
     void propertyChange(QString, QObject*, QObject*);

 private:
  static Logger* log;
  /*private*/ /*final*/ int BACKPANEL_LAYER = 0;//Integer.MIN_VALUE;
  /*private*/ /*final*/ int PANEL_LAYER_FRAME = 1;
  /*private*/ /*final*/ int PANEL_LAYER_PANEL = 2;

  /*private*/ /*final*/ ThrottleWindow* throttleWindow;

  /*private*/ ControlPanel* controlPanel;
  /*private*/ FunctionPanel* functionPanel;
  /*private*/ AddressPanel* addressPanel;
  /*private*/ BackgroundPanel* backgroundPanel;
  /*private*/ FrameListener* frameListener;
  /*private*/ SpeedPanel* speedPanel;

  /*private*/ QString title;
  /*private*/ QString lastUsedSaveFile = null;

  /*private*/ bool isEditMode = true;
  /*private*/ bool willSwitch = false;
  /*private*/ static /*final*/ QString DEFAULT_THROTTLE_FILENAME;// = "JMRI_ThrottlePreference.xml";
  /*private*/ void saveThrottle(QString sfile);
  /*private*/ void initGUI();
  QDomDocument doc;
};

#endif // THROTTLEFRAME_H
