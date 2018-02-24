#ifndef MEMORYICON_H
#define MEMORYICON_H
#include "displaymemoryicon.h"
#include "Roster/roster.h"

class LayoutBlock;
class Editor;
class MemoryIcon : public DisplayMemoryIcon
{
    Q_OBJECT
public:
//    explicit MemoryIcon(QObject *parent = 0);
    /*public*/ MemoryIcon(QString s, Editor* panel, QObject* parent = 0);
    /*public*/ MemoryIcon(NamedIcon* s, Editor* editor, QObject* parent=0);
    /*public*/ void setText(QString text) ;
    /*public*/ LayoutBlock* getLayoutBlock();
    /*public*/ void setLayoutBlock(LayoutBlock* lb);
    /*public*/ void displayState();
    /*public*/ void setMemory(QString pName);
    /*public*/ void setMemory(NamedBeanHandle<Memory*>* m);
    /*public*/ NamedBeanHandle<Memory*>* getNamedMemory();
    /*public*/ Memory* getMemory();
    /*public*/ NamedBean* getNamedBean();
    /*public*/ bool showPopUp(QMenu* popup);
    /*public*/ QString getNameString();
//    /*public*/ bool updateScene();
    /*public*/ QString getGroupName();

signals:

public slots:
    void on_updateBlockItemAction_toggled(bool bState);
    /*public*/ void propertyChange(PropertyChangeEvent* e);
private:
 QString defaultText;// = " ";
 LayoutBlock* lBlock;// = NULL;
Logger* log;
protected:
/*protected*/ void setValue(QVariant obj);
/*protected*/ void addRosterToMemory(RosterEntry* roster);
/*protected*/ void displayState(QVariant key);
/*protected*/ QVariant updateIconFromRosterVal(RosterEntry* roster);

};

#endif // MEMORYICON_H
