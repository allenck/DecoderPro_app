#ifndef BLOCKMANAGER_H
#define BLOCKMANAGER_H
#include "abstractblockmanager.h"
#include "block.h"
#include "exceptions.h"
#include <QCompleter>
#include "decimalformat.h"
#include "abstractshutdowntask.h"

class RosterEntry;
class LIBPR3SHARED_EXPORT BlockManager : public AbstractBlockManager
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit BlockManager(QObject *parent = 0);
    ~BlockManager() {}
    BlockManager(const BlockManager&) : AbstractBlockManager() {}
    /*public*/ int getXMLOrder() const override;
    /*public*/ QString getSystemPrefix() const override;
    /*public*/ char typeLetter() const override;
    /*public*/ QString getNamedBeanClass()const override;
    /*public*/ bool isSavedPathInfo();
    /*public*/ void setSavedPathInfo(bool save);
    /**
     * Method to create a new Block if it does not exist
     *   Returns NULL if a Block with the same systemName or userName
     *       already exists, or if there is trouble creating a new Block.
     */
    /*public*/ Block* createNewBlock(QString systemName, QString userName) const;
    /*public*/ Block* createNewBlock(QString userName) const;
    /*public*/ Block* provideBlock(QString name)const;
    /**
     * Method to get an existing Block.  First looks up assuming that
     *      name is a User Name.  If this fails looks up assuming
     *      that name is a System Name.  If both fail, returns NULL.
     */
    /*public*/ Block* getBlock(QString name)const;
    /*public*/ Block *getBySystemName(QString name) const;
    /*public*/ Block* getByUserName(QString key) const;
    /*public*/ Block* getByDisplayName(QString key);
//    static BlockManager* _instance;// = NULL;
//    static /*public*/ BlockManager* instance();
    /*public*/ void setDefaultSpeed(QString speed) throw (JmriException);
    /*public*/ QString getDefaultSpeed();
    /*public*/ QString getBeanTypeHandled(bool plural) const override;
    /*public*/ QList<Block*> getBlocksOccupiedByRosterEntry(/*@Nonnull*/ RosterEntry* re);
    QCompleter* getCompleter(QString text);
    virtual /*public*/ Block* provide(QString name) const throw (IllegalArgumentException) ;
    /*public*/ qint64 timeSinceLastLayoutPowerOn()const;
    /*public*/ /*final*/ ShutDownTask* shutDownTask = new AbstractShutDownTask("Writing Blocks");

signals:
    //void propertyChange(PropertyChangeEvent *e);

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e) override;
    /*public*/ void vetoableChange(PropertyChangeEvent*) override;
private:
 /*private*/ bool saveBlockPath;// = true;
    DecimalFormat* paddedNumber;// =  DecimalFormat("0000");

    mutable int lastAutoBlockRef;// = 0;
    QString defaultSpeed;// = "Normal";
 static Logger* log;
 QString powerManagerChangeName;
 /*private*/ /*Instant*/qint64 lastTimeLayoutPowerOn; // the most recent time any power manager had a power ON event

 friend class PropertyChangeSupport;
};
Q_DECLARE_METATYPE(BlockManager)
#endif // BLOCKMANAGER_H
