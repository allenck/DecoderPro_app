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
    /*public*/ QChar typeLetter() override;
    /*public*/ Memory* provideMemory(QString sName) override;
    /*public*/ Memory* getMemory(QString name) override;
    /*public*/ Memory* getBySystemName(QString name) override;
    /*public*/ Memory* getByUserName(QString key) override;
    /*public*/ Memory* newMemory(QString systemName, QString userName) override;
    /*public*/ Memory* newMemory(QString userName) override;
    /*public*/ QString getBeanTypeHandled(bool plural) const override;
    /*public*/ Memory* provide(QString name)  throw (IllegalArgumentException) override;

signals:
    void newMemoryCreated(Memory* m);
public slots:
private:
 Logger log;
 mutable int lastAutoMemoryRef = 0;
protected:
 /*abstract protected*/ virtual Memory* createNewMemory(QString systemName, QString userName)  = 0;

};

#endif // ABSTRACTMEMORYMANGER_H
