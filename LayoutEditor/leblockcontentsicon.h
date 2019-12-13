#ifndef LEBLOCKCONTENTICON_H
#define LEBLOCKCONTENTICON_H
#include "blockcontentsicon.h"
#include "block.h"

class AddBCIconActionListener;
class ActiveTrain;
class DispatcherFrame;
class LEBlockContentsIcon : public BlockContentsIcon
{
 Q_OBJECT
public:
 /*public*/ LEBlockContentsIcon(QString s, LayoutEditor* panel, QObject *parent = nullptr);
 /*public*/ void setBlock(NamedBeanHandle<Block *> *m);
public slots:

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger("BlockContentsIcon");
 /*private*/ /*transient*/ LayoutBlock* lBlock = nullptr;

private slots:

protected:
 /*protected*/ void addRosterToIcon(RosterEntry* roster);

protected slots:

};

#endif // BLOCKCONTENTICON_H
