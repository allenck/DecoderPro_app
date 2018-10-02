#ifndef THROTTLEFRAMEMANAGER_H
#define THROTTLEFRAMEMANAGER_H

#include <QObject>
#include <QMap>
#include "libPr3_global.h"

class ThrottlesListPanel;
class QMainWindow;
//class ThrottlesListPanel;
class ListThrottles;
class JmriJFrame;
class ThrottleCyclingKeyListener;
class ThrottlesPreferences;
class ThrottleWindow;
class LIBPR3SHARED_EXPORT ThrottleFrameManager : public QObject
{
    Q_OBJECT
public:
 /*private*/ ThrottleFrameManager(QObject *parent = 0);
 ~ThrottleFrameManager() {}
 ThrottleFrameManager(const ThrottleFrameManager&) : QObject() {}
 QT_DEPRECATED /*public*/ static ThrottleFrameManager* instance();

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

    /*private*/ int activeFrame;
    /*private*/ ThrottleCyclingKeyListener* throttleCycler;

    /*private*/ QList<ThrottleWindow*>* throttleWindows;

    /*private*/ ThrottlesPreferences* throttlesPref;
    /*private*/ JmriJFrame* throttlePreferencesFrame;
    /*private*/ JmriJFrame* throttlesListFrame;
    /*private*/ ThrottlesListPanel* throttlesListPanel;
    /*private*/ void destroyThrottleWindow(ThrottleWindow* window);
    /*private*/ void requestFocusForNextFrame();
    /*private*/ void requestFocusForPreviousFrame();
    /*private*/ void buildThrottlePreferencesFrame();
    /*private*/ void buildThrottleListFrame();

};
Q_DECLARE_METATYPE(ThrottleFrameManager)
#endif // THROTTLEFRAMEMANAGER_H
