#ifndef ABSTRACTMEMORYMANGER_H
#define ABSTRACTMEMORYMANGER_H
#include "abstractmanager.h"
#include "memorymanager.h"
#include "exceptions.h"
#include "vetoablechangesupport.h"

class InternalSystemConnectionMemo;
class LIBPR3SHARED_EXPORT AbstractMemoryManager : public AbstractManager, public MemoryManager
{
    Q_OBJECT
  Q_INTERFACES(MemoryManager)
public:
    explicit AbstractMemoryManager(InternalSystemConnectionMemo* memo, QObject *parent = 0);
    /*public*/ int getXMLOrder()const override;
    /*public*/ QChar typeLetter()const override;
    /*public*/ Memory* provideMemory(QString sName) override;
    /*public*/ Memory* getMemory(QString name) override;
    /*public*/ Memory* getBySystemName(QString name) override;
    /*public*/ Memory* getByUserName(QString key) override;
    /*public*/ Memory* newMemory(QString systemName, QString userName) override;
    /*public*/ Memory* newMemory(QString userName) override;
    /*public*/ QString getBeanTypeHandled(bool plural) const override;
    /*public*/ Memory* provide(QString name)  /*throw (IllegalArgumentException)*/ override;

signals:
    void newMemoryCreated(Memory* m);
public slots:
private:
 static Logger* log;
 mutable int lastAutoMemoryRef = 0;
protected:
 /*abstract protected*/ virtual Memory* createNewMemory(QString systemName, QString userName)  = 0;

};

#endif // ABSTRACTMEMORYMANGER_H
