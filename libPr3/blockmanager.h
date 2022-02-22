#ifndef BLOCKMANAGER_H
#define BLOCKMANAGER_H

#include "block.h"
#include "exceptions.h"
#include <QCompleter>
#include "decimalformat.h"
#include "abstractshutdowntask.h"
#include "instancemanagerautodefault.h"
#include "propertyvetoexception.h"
#include "providingmanager.h"
#include "abstractmanager.h"

class RosterEntry;
class LIBPR3SHARED_EXPORT BlockManager : public AbstractManager, public ProvidingManager, public InstanceManagerAutoDefault
{
    Q_OBJECT
  Q_INTERFACES(ProvidingManager InstanceManagerAutoDefault )
public:
    Q_INVOKABLE explicit BlockManager(QObject *parent = 0);
    ~BlockManager() {}
    BlockManager(const BlockManager&) : AbstractManager() {}
    /*public*/ void dispose() override;
    /*public*/ int getXMLOrder() const override;
    /*public*/ QString getSystemPrefix() const override;
    /*public*/ QChar typeLetter() const override;
    /*public*/ QString getNamedBeanClass()const override;
    /*public*/ bool isSavedPathInfo();
    /*public*/ void setSavedPathInfo(bool save);
    /**
     * Method to create a new Block if it does not exist
     *   Returns NULL if a Block with the same systemName or userName
     *       already exists, or if there is trouble creating a new Block.
     */
    /*public*/ Block* createNewBlock(QString systemName, QString userName);
    /*public*/ Block* createNewBlock(QString userName);
    /*public*/ Block* provideBlock(QString name);
    /**
     * Method to get an existing Block.  First looks up assuming that
     *      name is a User Name.  If this fails looks up assuming
     *      that name is a System Name.  If both fail, returns NULL.
     */
    /*public*/ Block* getBlock(QString name);
//    /*public*/ Block *getBySystemName(QString name) const;
//    /*public*/ Block* getByUserName(QString key)  override;
    /*public*/ Block* getByDisplayName(QString key);
//    static BlockManager* _instance;// = NULL;
//    static /*public*/ BlockManager* instance();
    /*public*/ void setDefaultSpeed(QString speed) /*throw (JmriException)*/;
    /*public*/ QString getDefaultSpeed();
    /*public*/ QString getBeanTypeHandled(bool plural) const override;
    /*public*/ QList<Block*> getBlocksOccupiedByRosterEntry(/*@Nonnull*/ RosterEntry* re);
    QCompleter* getCompleter(QString text);
    virtual /*public*/ NamedBean* provide(QString name) /*throw (IllegalArgumentException)*/override ;
    /*public*/ qint64 timeSinceLastLayoutPowerOn()const;
    /*public*/ /*final*/ ShutDownTask* shutDownTask = new AbstractShutDownTask("Writing Blocks");
    QObject* self() override {return (QObject*)this;}
    QObject* vself() override{return (QObject*)this;}
    QObject* pself() override{return (QObject*)this;}

    /*public*/ SystemConnectionMemo* getMemo()  override;
    /*public*/ NamedBean* getNamedBean(QString s)  override;
    /*public*/ void Register(NamedBean*)  override;
    /*public*/ void deregister(NamedBean*)override;
    /*public*/ void addDataListener(Manager::ManagerDataListener*)override;
    /*public*/ void removeDataListener(Manager::ManagerDataListener*)override;

    ///*public*/ QSet<NamedBean*> getNamedBeanSet() override {return AbstractManager::getNamedBeanSet();}
    /*public*/ NamedBean* getBySystemName(QString name) override {return AbstractManager::getBySystemName(name);}
    /*public*/ void addPropertyChangeListener(PropertyChangeListener* l) override{PropertyChangeSupport::addPropertyChangeListener(l);}
    /*public*/ void removePropertyChangeListener(PropertyChangeListener* l) override{PropertyChangeSupport::removePropertyChangeListener(l);}

signals:
    //void propertyChange(PropertyChangeEvent *e);

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e) override;
//    /*public*/ void vetoableChange(PropertyChangeEvent* e) /*throw (PropertyVetoException)*/ override;
private:
 /*private*/ bool saveBlockPath;// = true;
    DecimalFormat* paddedNumber;// =  DecimalFormat("0000");

    mutable int lastAutoBlockRef;// = 0;
    QString defaultSpeed;// = "Normal";
 static Logger* log;
 QString powerManagerChangeName;
 /*private*/ /*Instant*/qint64 lastTimeLayoutPowerOn; // the most recent time any power manager had a power ON event

 friend class SwingPropertyChangeSupport;
};
Q_DECLARE_METATYPE(BlockManager)
#endif // BLOCKMANAGER_H
