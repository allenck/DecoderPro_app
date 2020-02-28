#ifndef ABSTRACTMEMORYMANGER_H
#define ABSTRACTMEMORYMANGER_H
#include "abstractmanager.h"
#include "memorymanager.h"
#include "exceptions.h"

class LIBPR3SHARED_EXPORT AbstractMemoryManager : public MemoryManager
{
    Q_OBJECT
public:
    explicit AbstractMemoryManager(QObject *parent = 0);
    /*public*/ int getXMLOrder()const override;
    /*public*/ char typeLetter()const override;
    /*public*/ Memory* provideMemory(QString sName)const override;
    /*public*/ Memory* getMemory(QString name)const override;
    /*public*/ Memory* getBySystemName(QString name)const override;
    /*public*/ Memory* getByUserName(QString key)const override;
    /*public*/ Memory* newMemory(QString systemName, QString userName)const override;
    /*public*/ Memory* newMemory(QString userName)const override;
    /*public*/ QString getBeanTypeHandled(bool plural) const override;
    /*public*/ Memory* provide(QString name) const  throw (IllegalArgumentException) override;

signals:
    void newMemoryCreated(Memory* m);
public slots:
private:
 Logger log;
 mutable int lastAutoMemoryRef = 0;
protected:
 /*abstract protected*/ virtual Memory* createNewMemory(QString systemName, QString userName) const = 0;

};

#endif // ABSTRACTMEMORYMANGER_H
