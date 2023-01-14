#ifndef THROTTLEFRAMEMANAGER_H
#define THROTTLEFRAMEMANAGER_H

#include <QObject>
#include <QMap>
#include "libPr3_global.h"
#include "jmrijframe.h"
#include "instancemanagerautodefault.h"

class ThrottlePreferencesFrame;
class ThrottlesListPanel;
class QMainWindow;
//class ThrottlesListPanel;
class ListThrottles;
class JmriJFrame;
class ThrottleCyclingKeyListener;
class ThrottlesPreferences;
class ThrottleWindow;
class LIBPR3SHARED_EXPORT ThrottleFrameManager : public QObject, InstanceManagerAutoDefault
{
  Q_OBJECT
  Q_INTERFACES(InstanceManagerAutoDefault)
public:
 Q_INVOKABLE /*public*/ ThrottleFrameManager(QObject *parent = 0);
 ~ThrottleFrameManager() {}
 ThrottleFrameManager(const ThrottleFrameManager&) : QObject() {}

    /*public*/ ThrottleWindow* createThrottleWindow();
    /*public*/ void requestThrottleWindowDestruction(ThrottleWindow* frame);
    /*public*/ void requestAllThrottleWindowsDestroyed();
    /*public*/ QListIterator<ThrottleWindow*> getThrottleWindows();
    /*public*/ int getNumberThrottleWindows();
    /*public*/ ThrottleWindow* getCurrentThrottleFrame();
    /*public*/ ThrottlesPreferences* getThrottlesPreferences();
    /*public*/ ThrottlesListPanel* getThrottlesListPanel();
    /*public*/ void showThrottlesList();
    /*public*/ void showThrottlesPreferences();
    /*public*/ /*ThrottleFrame*/ ThrottleWindow* createThrottleFrame();
    /*public*/ void nextRunningThrottleFrame();

signals:
    void newThrottle(ThrottleWindow*);
public slots:

private:
    /*private*/ static int NEXT_THROTTLE_KEY;// = KeyEvent.VK_RIGHT;
    /*private*/ static int PREV_THROTTLE_KEY;// = KeyEvent.VK_LEFT;

    /*private*/ int activeFrame = -1;
    /*private*/ ThrottleCyclingKeyListener* throttleCycler = nullptr;

    /*private*/ QList<ThrottleWindow*>* throttleWindows = nullptr;

    /*private*/ ThrottlesPreferences* throttlesPref = nullptr;
    /*private*/ ThrottlePreferencesFrame* throttlePreferencesFrame = nullptr;
    /*private*/ JmriJFrame* throttlesListFrame = nullptr;
    /*private*/ ThrottlesListPanel* throttlesListPanel = nullptr;
    /*private*/ void destroyThrottleWindow(ThrottleWindow* window);
    /*private*/ void requestFocusForNextFrame();
    /*private*/ void requestFocusForPreviousFrame();
    /*private*/ void buildThrottlePreferencesFrame();
    /*private*/ void buildThrottleListFrame();

private slots:
    /*private*/ void initFrame();

};
Q_DECLARE_METATYPE(ThrottleFrameManager)

class ThrottlesListFrame : public  JmriJFrameX
{
 Q_OBJECT
public:
 /*public*/ ThrottlesListFrame(QString name) : JmriJFrameX(name) {}
 /*public*/ QString getClassName() {return "jmri.jmrit.throttle.ThrottleFrameManager:ThrottlesListFrame";}
};

class ThrottlePreferencesFrame : public  JmriJFrame
{
 Q_OBJECT
public:
 /*public*/ ThrottlePreferencesFrame(QString name) : JmriJFrame(name) {}
 /*public*/ QString getClassName() {return "jmri.jmrit.throttle.ThrottleFrameManager:ThrottlePreferencesFrame";}
};

#endif // THROTTLEFRAMEMANAGER_H
