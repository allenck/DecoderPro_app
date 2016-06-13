#ifndef LAYOUTBLOCKMANAGER_H
#define LAYOUTBLOCKMANAGER_H
#include "abstractmanager.h"
#include "layoutblock.h"

class LayoutBlockManager : public AbstractManager
{
 Q_OBJECT
public:
 explicit LayoutBlockManager(QObject *parent = 0);
 /*public*/ int getXMLOrder();
 /*public*/ QString getSystemPrefix() { return "I"; }
 /*public*/ char typeLetter() { return 'B'; }
/**
 * Method to create a new LayoutBlock if the LayoutBlock does not exist
 *   Returns null if a LayoutBlock with the same systemName or userName
 *       already exists, or if there is trouble creating a new LayoutBlock.
 *   Note that since the userName is used to address LayoutBlocks, the
 *       user name must be present.  If the user name is not present,
 *       the new LayoutBlock is not created, and null is returned.
 */
/*public*/ LayoutBlock* createNewLayoutBlock(QString systemName, QString userName);
/*public*/ LayoutBlock* createNewLayoutBlock();
/**
 * Remove an existing LayoutBlock.
 */
/*public*/ void deleteLayoutBlock(LayoutBlock* block);
/**
 * Method to get an existing LayoutBlock.  First looks up assuming that
 *      name is a User Name.  If this fails looks up assuming
 *      that name is a System Name.  If both fail, returns NULL.
 */
/*public*/ LayoutBlock* getLayoutBlock(QString name);
/*public*/ LayoutBlock* getLayoutBlock(Block* block);
/*public*/ LayoutBlock* getBySystemName(QString name);
/*public*/ LayoutBlock* getByUserName(QString key);
static LayoutBlockManager* _instance;// = NULL;
static /*public*/ LayoutBlockManager* instance();

signals:
    
public slots:
private:
    /*private*/ int blkNum;// = 1;
Logger log;
};

#endif // LAYOUTBLOCKMANAGER_H
