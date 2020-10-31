#ifndef THROTTLESPREFERENCES_H
#define THROTTLESPREFERENCES_H

#include <QObject>
#include "xmlfile.h"
#include <QSize>
#include "libpref.h"
class PropertyChangeEvent;
class ThrottlesPrefsXml;
class QSize;
class LIBPREFSHARED_EXPORT ThrottlesPreferences : public QObject
{
    Q_OBJECT
public:
    explicit ThrottlesPreferences(QObject *parent = 0);
    ~ThrottlesPreferences() {}
    ThrottlesPreferences(const ThrottlesPreferences&);
    /*public*/ void load(QDomElement e);
    /*private*/ QDomElement store();
    /*public*/ void set(ThrottlesPreferences* tp);
    /*public*/ bool compareTo(ThrottlesPreferences* tp);
    /*public*/ void save();
    /*public*/ QSize getWindowDimension();
    /*public*/ void setWindowDimension(QSize d);
    /*public*/ bool isUsingExThrottle();
    /*public*/ void setUseExThrottle(bool exThrottle);
    /*public*/ bool isUsingToolBar();
    /*public*/ void setUsingToolBar(bool win4all);
    /*public*/ bool isUsingFunctionIcon();
    /*public*/ void setUsingFunctionIcon(bool useFunctionIcon);
    /*public*/ bool isUsingIcons();
    /*public*/ bool isResizingWindow();
    /*public*/ void setResizeWindow(bool winImg);
    /*public*/ bool isUsingRosterImage();
    /*public*/ void setUseRosterImage(bool rosterImage);
    /*public*/ bool isEnablingRosterSearch();
    /*public*/ void setEnableRosterSearch(bool b);
    /*public*/ void setAutoLoad(bool b);
    /*public*/ bool isAutoLoading();
    /*public*/ void setHideUndefinedFuncButt(bool b);
    /*public*/ bool isHidingUndefinedFuncButt();
    /*public*/ void setIgnoreThrottlePosition(bool b);
    /*public*/ bool isIgnoringThrottlePosition();
    /*public*/ void setSaveThrottleOnLayoutSave(bool b);
    /*public*/ bool isSavingThrottleOnLayoutSave();
    /*public*/ bool isDirty();

signals:
    void propertyChange(PropertyChangeEvent*);

public slots:
private:
    /*private*/ bool _useExThrottle;// = true;
    /*private*/ bool _useToolBar;// = true;
    /*private*/ bool _useFunctionIcon;// = false;
    /*private*/ bool _resizeWinImg;// = false;
    /*private*/ bool _useRosterImage;// = true;
    /*private*/ bool _enableRosterSearch;// = true;
    /*private*/ bool _enableAutoLoad;// = true;
    /*private*/ bool _hideUndefinedFunButton;// = false;
    /*private*/ bool _ignoreThrottlePosition;// = true;
    /*private*/ bool _saveThrottleOnLayoutSave;// = true;

    /*private*/ QSize _winDim;// =  QSize(800,600);
    /*private*/ QString prefFile;
//    /*private*/ QList<PropertyChangeListener> listeners;
    void init();
    Logger* log;
    void common();
protected:
    /*protected*/ bool dirty;// = false;
};
class ThrottlesPrefsXml : public XmlFile
{
 Q_OBJECT
};

#endif // THROTTLESPREFERENCES_H
