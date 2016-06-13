#ifndef THROTTLEFRAMEMANAGER_H
#define THROTTLEFRAMEMANAGER_H

#include <QObject>
#include <QMap>
#include "libPr3_global.h"

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
    //explicit ThrottleFrameManager(QObject *parent = 0);
    /*public*/ static ThrottleFrameManager* instance();
    /*public*/ ThrottleWindow* createThrottleWindow();
    /*public*/ void requestThrottleWindowDestruction(ThrottleWindow* frame);
    /*public*/ void requestAllThrottleWindowsDestroyed();
    /*public*/ QListIterator<ThrottleWindow*> getThrottleWindows();
    /*public*/ int getNumberThrottleWindows();
    /*public*/ ThrottleWindow* getCurrentThrottleFrame();
    /*public*/ ThrottlesPreferences* getThrottlesPreferences();
    /*public*/ ListThrottles* getThrottlesListPanel();
    /*public*/ void showThrottlesList();
    /*public*/ void showThrottlesPreferences();
    /*public*/ /*ThrottleFrame*/ ThrottleWindow* createThrottleFrame();
    /*public*/ void nextRunningThrottleFrame();

signals:
    void newThrottle(ThrottleWindow*);
public slots:
private:
    /*private*/ static ThrottleFrameManager* _instance;// = null;

    /*private*/ static int NEXT_THROTTLE_KEY;// = KeyEvent.VK_RIGHT;
    /*private*/ static int PREV_THROTTLE_KEY;// = KeyEvent.VK_LEFT;

    /*private*/ int activeFrame;
    /*private*/ ThrottleCyclingKeyListener* throttleCycler;

    /*private*/ QList<ThrottleWindow*>* throttleWindows;

    /*private*/ ThrottlesPreferences* throttlesPref;
    /*private*/ JmriJFrame* throttlePreferencesFrame;
    /*private*/ /*JmriJFrame*/ JmriJFrame* throttlesListFrame;
    /*private*/ ListThrottles* throttlesListPanel;
    /*private*/ ThrottleFrameManager(QObject *parent = 0); // can only be created by instance() => /*private*/
    /*private*/ void destroyThrottleWindow(ThrottleWindow* window);
    /*private*/ void requestFocusForNextFrame();
    /*private*/ void requestFocusForPreviousFrame();
    /*private*/ void buildThrottlePreferencesFrame();
    /*private*/ void buildThrottleListFrame();

};

#endif // THROTTLEFRAMEMANAGER_H
