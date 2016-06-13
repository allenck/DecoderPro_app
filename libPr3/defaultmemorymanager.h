#ifndef DEFAULTMEMORYMANAGER_H
#define DEFAULTMEMORYMANAGER_H
#include "abstractmemorymanager.h"
#include "libPr3_global.h"
class LIBPR3SHARED_EXPORT DefaultMemoryManager : public AbstractMemoryManager
{
    Q_OBJECT
public:
    explicit DefaultMemoryManager(QObject *parent = 0);
    /*public*/ QString getSystemPrefix();

signals:
    
public slots:
protected:
 /*protected*/ Memory* createNewMemory(QString systemName, QString userName);

};

#endif // DEFAULTMEMORYMANAGER_H
