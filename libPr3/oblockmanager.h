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
    /*public*/ QString getSystemPrefix() const override;
    /*public*/ char typeLetter()const  override ;
    /*public*/ OBlock* createNewOBlock(QString systemName, QString userName);
    /*public*/ OBlock* createNewOBlock(/*@Nonnull*/ QString userName);
    /*public*/ OBlock* getOBlock(QString name);
    /*public*/ OBlock* getBySystemName(QString name)const ;
    /*public*/ OBlock* getByUserName(QString key)const ;
    /*public*/ OBlock* provideOBlock(QString name)const ;
    static OBlockManager* _instance;// = NULL;
    static /*public*/ OBlockManager* instance();
    /*public*/ bool isAssignableFromType() {return true;}
    virtual /*public*/ OBlock *provide(QString name) const throw (IllegalArgumentException);
    /*public*/ QString getNamedBeanClass()const override {
        return "QBlock";
    }
    QObject* self() {return (QObject*)this;}

signals:
public slots:

};
Q_DECLARE_METATYPE(OBlockManager)
#endif // OBLOCKMANAGER_H
