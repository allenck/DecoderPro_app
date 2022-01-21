#ifndef OBLOCKMANAGER_H
#define OBLOCKMANAGER_H
#include "abstractmanager.h"
#include "libPr3_global.h"
#include "instancemanagerautodefault.h"

class OBlock;
class LIBPR3SHARED_EXPORT OBlockManager : public AbstractManager, public InstanceManagerAutoDefault
{
    Q_OBJECT
  Q_INTERFACES(InstanceManagerAutoDefault)
public:
    Q_INVOKABLE explicit OBlockManager(QObject *parent = 0);
    ~OBlockManager(){}
    OBlockManager(const OBlockManager&) : AbstractManager() {}
    /*public*/ int getXMLOrder()const  override;
    /*public*/ QString getSystemPrefix()  override;
    /*public*/ QChar typeLetter()  override ;
    /*public*/ OBlock* createNewOBlock(QString systemName, QString userName);
    /*public*/ OBlock* createNewOBlock(/*@Nonnull*/ QString userName);
    /*public*/ OBlock* getOBlock(QString name);
    /*public*/ NamedBean* getBySystemName(QString name)const ;
    /*public*/ NamedBean* getByUserName(QString key) override;
    /*public*/ OBlock* provideOBlock(QString name) ;
    static OBlockManager* _instance;// = NULL;
    static /*public*/ OBlockManager* instance();
    /*public*/ bool isAssignableFromType() {return true;}
    virtual /*public*/ OBlock *provide(QString name) ;
    /*public*/ QString getNamedBeanClass()const override {
        return "OBlock";
    }
    /*public*/ QString getBeanTypeHandled(bool plural) const override
    {
     return tr(plural?"OBlocks":"OBlock");
    }
    QObject* self() override{return (QObject*)this;}
    /*public*/ SystemConnectionMemo* getMemo() override {return AbstractManager::getMemo();}
    /*public*/ QSet<NamedBean*> getNamedBeanSet() override {return AbstractManager::getNamedBeanSet();}
    /*public*/ NamedBean* getBySystemName(QString name) override {return AbstractManager::getBySystemName(name);}
    /*public*/ void addPropertyChangeListener(PropertyChangeListener* l) override{PropertyChangeSupport::addPropertyChangeListener(l);}
    /*public*/ void removePropertyChangeListener(PropertyChangeListener* l) override{PropertyChangeSupport::removePropertyChangeListener(l);}

signals:
public slots:

};
Q_DECLARE_METATYPE(OBlockManager)
#endif // OBLOCKMANAGER_H
