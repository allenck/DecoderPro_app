#ifndef OBLOCKMANAGER_H
#define OBLOCKMANAGER_H
#include "abstractmanager.h"
#include "libPr3_global.h"

class OBlock;
class LIBPR3SHARED_EXPORT OBlockManager : public AbstractManager
{
    Q_OBJECT
public:
    explicit OBlockManager(QObject *parent = 0);
    /*public*/ int getXMLOrder();
    /*public*/ QString getSystemPrefix();
    /*public*/ char typeLetter();
    /*public*/ OBlock* createNewOBlock(QString systemName, QString userName);
    /*public*/ OBlock* getOBlock(QString name);
    /*public*/ OBlock* getBySystemName(QString name);
    /*public*/ OBlock* getByUserName(QString key);
    /*public*/ OBlock* provideOBlock(QString name);
    static OBlockManager* _instance;// = NULL;
    static /*public*/ OBlockManager* instance();

signals:
 void propertyChange(PropertyChangeEvent *e);
public slots:

};

#endif // OBLOCKMANAGER_H
