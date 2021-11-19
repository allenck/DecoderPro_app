#ifndef LEMEMORYICON_H
#define LEMEMORYICON_H
#include "memoryicon.h"
#include "Roster/roster.h"
#include "propertychangelistener.h"

class LayoutBlock;
class Editor;
class LEMemoryIcon : public MemoryIcon
{
    Q_OBJECT
public:
//    explicit MemoryIcon(QObject *parent = 0);
    /*public*/ LEMemoryIcon(QString s, LayoutEditor *panel, QObject* parent = 0);
    /*public*/ void setText(QString text) ;
    /*public*/ LayoutBlock* getLayoutBlock();
    /*public*/ void setLayoutBlock(LayoutBlock* lb);
    /*public*/ void displayState() override;
    /*public*/ void setMemory(QString pName) override;
    /*public*/ bool showPopUp(QMenu* popup) override;
    enum POS
    {
     LEFT = 0x00,
     RIGHT = 0x02,
     CENTRE = 0x04
    };
    Q_ENUM(POS)
    QObject* self() override {return (QObject*)this;}

signals:

public slots:
    void on_updateBlockItemAction_toggled(bool bState);
    /*public*/ void propertyChange(PropertyChangeEvent* e) override;

private:
 QString defaultText;// = " ";
 LayoutBlock* lBlock;// = NULL;
Logger* log;
/*Stores the original location of the memory, this is then used to calculate
     the position of the text dependant upon the justification*/
    /*private*/ int originalX = 0;
    /*private*/ int originalY = 0;
 QAction* updateBlockItem;

protected:
 /*protected*/ void setValue(QVariant obj);
 /*protected*/ void addRosterToIcon(RosterEntry* roster);
 /*protected*/ QVariant getValue();

friend class MIActionListener;
};

class MIActionListener : public QObject, public ActionListener
{
 Q_OBJECT
    Q_INTERFACES(ActionListener)
 LEMemoryIcon* memoryIcon;
public:
 MIActionListener(LEMemoryIcon* memoryIcon) {this->memoryIcon = memoryIcon;}
public slots:
 void actionPerformed(JActionEvent */*e*/ = 0)override { memoryIcon->editMemory();}
};
#endif // LEMEMORYICON_H
