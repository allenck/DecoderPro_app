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
    /*public*/ int getXMLOrder();
    /*public*/ char typeLetter()const;
    /*public*/ Memory* provideMemory(QString sName);
    /*public*/ Memory* getMemory(QString name);
    /*public*/ Memory* getBySystemName(QString name);
    /*public*/ Memory* getByUserName(QString key);
    /*public*/ Memory* newMemory(QString systemName, QString userName);
    /*public*/ Memory* newMemory(QString userName);
    virtual Memory* createNewMemory(QString systemName, QString userName) =0;
signals:
    void newMemoryCreated(Memory* m);
public slots:
private:
 Logger log;
 int lastAutoMemoryRef;// = 0;

};

#endif // ABSTRACTMEMORYMANGER_H
