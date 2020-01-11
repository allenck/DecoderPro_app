#ifndef BLOCKCONTENTICON_H
#define BLOCKCONTENTICON_H
#include "lememoryicon.h"
#include "block.h"

class AddBCIconActionListener;
class ActiveTrain;
class DispatcherFrame;
class BlockContentsIcon : public MemoryIcon
{
 Q_OBJECT
public:
 /*public*/ BlockContentsIcon(QString s, Editor* editor, QObject* parent = 0);
 /*public*/ BlockContentsIcon(NamedIcon* s, Editor* editor, QObject* parent = 0);
 /*public*/ Positionable* deepClone();
 /*public*/ void resetDefaultIcon();
 virtual/*public*/ void setBlock(QString pName);
 /*public*/ void setBlock(NamedBeanHandle<Block*>* m);
 /*public*/ NamedBeanHandle<Block*>* getNamedBlock();
 /*public*/ Block* getBlock();
 /*public*/ NamedBean* getNamedBean();
 /*public*/ QMap<QString, NamedIcon*>* getMap();
 /*public*/ QString getNameString();
 /*public*/ bool showPopUp(QMenu* popup);
 /*public*/ bool setTextEditMenu(QMenu* popup);
 /*public*/ void displayState();
 /*public*/ bool setEditIconMenu(QMenu* popup);
 /*public*/ void dispose();
// /*public*/ void doMouseClicked(QMouseEvent* e);
 /*public*/ void mouseDoubleClickEvent(QMouseEvent*);

public slots:
 void on_newThrottle();
 void on_terminateTrain_triggered();
 void on_extraSections_triggered();
 void on_restart_triggered();
 void on_newTrain_triggered();

private:
     /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger("BlockContentsIcon");
 void common();
 NamedIcon* defaultIcon;// = NULL;
 QMap<QString, NamedIcon*>* map;// = NULL;
 /*private*/ NamedBeanHandle<Block*>* namedBlock = nullptr;
 void editBlock();
 DispatcherFrame* df;
 ActiveTrain* at;

private slots:

protected:
 /*protected*/ Positionable* finishClone(BlockContentsIcon* pos);
 /*protected*/ QVariant getValue();
 /*protected*/ QVariant updateIconFromRosterVal(RosterEntry* roster);

protected slots:
 /*protected*/ void setValue(QVariant val);
 /*protected*/ void editBlockValue();
 /*protected*/ void edit();
 friend class AddBCIconActionListener;

};

class AddBCIconActionListener : public ActionListener
{
 Q_OBJECT
 BlockContentsIcon* icon;
public:
 AddBCIconActionListener(BlockContentsIcon* icon);
public slots:
 void actionPerformed();
};
#endif // DISPLAYBLOCKCONTENTICON_H
