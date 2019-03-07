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
 /*public*/ void updateSize();
 /*public*/ void setOriginalLocation(int x, int y);
 /*public*/ int getOriginalX();
 /*public*/ int getOriginalY();
 /*public*/ void setLocation(int x, int y);
 /*public*/ bool setEditIconMenu(QMenu* popup);
 enum POS
 {
  LEFT = 0x00,
  RIGHT = 0x02,
  CENTRE = 0x04
 };
 Q_ENUM(POS)

signals:

public slots:
    void on_updateBlockItemAction_toggled(bool bState);
    /*public*/ void propertyChange(PropertyChangeEvent* e);
    void edit();

private:
 QString defaultText;// = " ";
 LayoutBlock* lBlock;// = NULL;
Logger* log;
/*Stores the original location of the memory, this is then used to calculate
     the position of the text dependant upon the justification*/
    /*private*/ int originalX = 0;
    /*private*/ int originalY = 0;
    void editMemory();

protected:
/*protected*/ void setValue(QVariant obj);
/*protected*/ void addRosterToMemory(RosterEntry* roster);
/*protected*/ void displayState(QVariant key);
/*protected*/ QVariant updateIconFromRosterVal(RosterEntry* roster);
friend class MIActionListener;
};

class MIActionListener : public ActionListener
{
 Q_OBJECT
 MemoryIcon* memoryIcon;
public:
 MIActionListener(MemoryIcon* memoryIcon) {this->memoryIcon = memoryIcon;}
public slots:
 void actionPerformed() { memoryIcon->editMemory();}
};
#endif // MEMORYICON_H
