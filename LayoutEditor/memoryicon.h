#ifndef DISPLAYMEMORYICON_H
#define DISPLAYMEMORYICON_H
#include "positionablelabel.h"
#include "namedbeanhandle.h"
#include "namedicon.h"
#include "../libPr3/memory.h"
#include "defaultmemorymanager.h"
#include "liblayouteditor_global.h"
#include "Roster/roster.h"
#include "actionlistener.h"

class NamedIcon;
class AbstractNamedBean;
//class PositionableLabel;
class LIBLAYOUTEDITORSHARED_EXPORT MemoryIcon : public PositionableLabel
{
    Q_OBJECT
public:
    //explicit DisplayMemoryIcon(QObject *parent = 0);
    /*public*/ MemoryIcon(QString s, Editor* editor, QObject *parent = 0);
    /*public*/ MemoryIcon(NamedIcon* s, Editor* editor, QObject *parent = 0);
    /*public*/ Positionable* deepClone() ;
    /*public*/ Positionable* finishClone(Positionable* p);

    /*As the size of a memory label can change we want to adjust the position of the x,y
    if the width is fixed*/

    static const int LEFT   = 0x00;
    static const int RIGHT  = 0x02;
    static const int CENTRE = 0x04;
    virtual /*public*/ void resetDefaultIcon() ;
    /*public*/ void setDefaultIcon(NamedIcon* n) ;
    /*public*/ NamedIcon* getDefaultIcon();
    /*public*/ void setOriginalLocation(int x, int y);
    /*public*/ int getOriginalX();
    /*public*/ int getOriginalY();
    /**
     * Attached a named Memory to this display item
      * @param pName Used as a system/user name to lookup the Memory object
     */
     virtual /*public*/ void setMemory(QString pName);
    /**
     * Attached a named Memory to this display item
     * @param m The Memory object
     */
    /*public*/ void setMemory(NamedBeanHandle<Memory*>* m);
    /*public*/ NamedBeanHandle<Memory*>* getNamedMemory();
    /*public*/ Memory* getMemory();
    /*public*/ NamedBean* getNamedBean();
    virtual /*public*/ QMap<QString, NamedIcon*>* getMap();
    /*public*/ void addKeyAndIcon(NamedIcon* icon, QString keyValue);
    /**
     * Drive the current state of the display from the state of the
     * Memory.
     */
    virtual /*public*/ void displayState();
    //QGraphicsItem* item;
    /*public*/ void setSelectable(bool b);
    /*public*/ bool isSelectable();
    /*public*/ bool showPopUp(QMenu* popup);
    /*public*/ bool setTextEditMenu(QMenu* popup);
    /*public*/ void updateSize();
    /*public*/ void updateBlockValueOnChange(bool boo);
    /*public*/ bool updateBlockValueOnChange();
    /*public*/ bool DisplayMemoryIconupdateBlockValueOnChange();
    /*public*/ void setLocation(int x, int y) override;
    /*public*/ QString getNameString();
    /*public*/ bool setEditIconMenu(QMenu* popup);
    /*public*/ void dispose();
    /*public*/ QString getGroupName();

signals:
    
public slots:
    void on_editMemoryValueAction_triggered();
    void on_propertyChange(QString,QVariant,QVariant);
    /*public*/ void propertyChange(PropertyChangeEvent* e);
    void on_act_triggered(QString);

private:
NamedIcon* defaultIcon;// = NULL;
// the associated Memory object
//protected Memory memory = NULL;
// the map of icons
QMap<QString, NamedIcon*>* map;// = NULL;
/*private*/ NamedBeanHandle<Memory*>* namedMemory;
bool selectable;// = false;

protected:
/*protected*/ Memory* memory;// = NULL;
/*private*/ void setMap();
int originalX, originalY;
Logger* log;
QColor _saveColor;
/*protected*/ void flipIcon(int flip);
/*protected*/ RosterEntry* re;// = NULL;
/*protected*/ QVariant updateIconFromRosterVal(RosterEntry* roster);
/*protected*/ bool flipRosterIcon;// = false;
//This is used by the LayoutEditor
/*protected*/ bool updateBlockValue;// = false;
/*protected*/ virtual void addRosterToIcon(RosterEntry* roster);
/*protected*/ virtual void setValue(QVariant val);
void editMemory();
/*protected*/ void editMemoryValue();
/*protected*/ void displayState(QVariant key);

class AddIconActionListener : public ActionListener
{
// Q_OBJECT
 MemoryIcon* parent;
public:
 AddIconActionListener(MemoryIcon* parent);

public:
 void actionPerformed(JActionEvent *e = 0);
};

protected slots:
/*protected*/ void edit();

friend class LEMemoryIcon;
friend class AddIconActionListener;
friend class BlockContentsIcon;
};

#endif // DISPLAYMEMORYICON_H
