#ifndef LOCOICON_H
#define LOCOICON_H
#include "positionablelabel.h"
#include <QActionGroup>
#include "../libPr3/Roster/rosterentry.h"
#include "liblayouteditor_global.h"

class ThrottleWindow;
//class ThrottleFrame;
class LayoutEditor;
class LIBLAYOUTEDITORSHARED_EXPORT LocoIcon : public PositionableLabel, public PropertyChangeListener
{
    Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
public:
    //explicit LocoIcon(QObject *parent = 0);
    /*public*/ static const /*final*/ QString WHITE;// = "White";		//loco background colors
    /*public*/ static const /*final*/ QString GREEN;// = "Green";
    /*public*/ static const /*final*/ QString GRAY;// = "Gray";
    /*public*/ static const /*final*/ QString RED;// = "Red";
    /*public*/ static const /*final*/ QString BLUE;// = "Blue";
    /*public*/ static const /*final*/ QString YELLOW;// = "Yellow";
    /*public*/ LocoIcon(Editor* editor);
    void common();
    /*public*/ Positionable* deepClone() override ;
    /*public*/ Positionable* finishClone(Positionable* p) override;
    /*public*/ void setShowToolTip(bool set) override;
    /*public*/ void setPositionable(bool enabled) override;
    /*public*/ bool doViemMenu() override;
    /*public*/ bool showPopUp(QMenu* popup) override;
    /*public*/ void setLocoColor(QString color);
    /*public*/ static QStringList getLocoColors();
    /*public*/ void setDockingLocation(int x, int y);
    /*public*/ int getDockX();
    /*public*/ int getDockY();
    /*public*/ void dock();
    /*public*/ void addLocoMenuEntry (QMenu* iconMenu, /*final*/ QString color);
    /*public*/ void setRosterEntry (RosterEntry* entry);
    /*public*/ RosterEntry* getRosterEntry ();
    /*public*/ void init();
    /*public*/ bool updateScene() override;
    void setLocation(double x, double y);
    QObject* self() override {return (QObject*)this;}
    QObject* pself() override{return (QObject*)this;}

signals:
    
public slots:
 void on_locoColor_selected(QAction* act);
 void on_throttleAction();
private:
 /*private*/ int _dockX = 0;
 /*private*/ int _dockY = 0;
 Editor* editor;
 //  jmri.jmrit.throttle.ThrottleFrame tf = null;
 QActionGroup* locoButtonGroup = nullptr;
 //QGraphicsItem* item;
 //ThrottleFrame* tf;
 ThrottleWindow* tw = nullptr;
 QColor _locoColor;

protected:
 /*protected*/ QMenu* makeLocoIconMenu();
 NamedIcon* white;// = new NamedIcon("resources/icons/markers/loco-white.gif",                                  "resources/icons/markers/loco-white.gif");
 NamedIcon* green;// = new NamedIcon("resources/icons/markers/loco-green.gif",                                 "resources/icons/markers/loco-green.gif");
 NamedIcon* gray;// = new NamedIcon("resources/icons/markers/loco-gray.gif",                                 "resources/icons/markers/loco-gray.gif");
 NamedIcon* red;// = new NamedIcon("resources/icons/markers/loco-red.gif",                                 "resources/icons/markers/loco-red.gif");
 NamedIcon* blue;// = new NamedIcon("resources/icons/markers/loco-blue.gif",                                 "resources/icons/markers/loco-blue.gif");
 NamedIcon* yellow;// = new NamedIcon("resources/icons/markers/loco-yellow.gif",                                 "resources/icons/markers/loco-yellow.gif");
 Logger log;
 /*protected*/ QAction* makeDockingMenu();
 /*protected*/ QAction* makeDockMenu();
/*protected*/ RosterEntry* entry;// = NULL;
 friend class Editor;
 friend class DockingActionListener;
 friend class DockMenuListener;
};

class DockingActionListener : public QObject
{
 Q_OBJECT
 Editor* ed;
 LocoIcon* loco;
public:
 DockingActionListener* init(Editor* e, LocoIcon* l);
public slots:
 /*public*/ void actionPerformed();
};

class DockMenuListener : public QObject
{
 Q_OBJECT
 Editor* ed;
 LocoIcon* loco;
public:
 DockMenuListener* init(Editor* e, LocoIcon* l);
public slots:
 /*public*/ void actionPerformed();
};

#endif // LOCOICON_H
