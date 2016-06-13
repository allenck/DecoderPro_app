#ifndef WARRANTMANAGER_H
#define WARRANTMANAGER_H
#include "abstractmanager.h"
#include "libPr3_global.h"

class Warrant;
class LIBPR3SHARED_EXPORT WarrantManager : public AbstractManager
{
    Q_OBJECT
public:
    explicit WarrantManager(QObject *parent = 0);
    /*public*/ int getXMLOrder();
    /*public*/ QString getSystemPrefix();
    /*public*/ char typeLetter();
    /*public*/ Warrant* createNewWarrant(QString systemName, QString userName);
    /*public*/ Warrant* getWarrant(QString name);
    /*public*/ Warrant* getBySystemName(QString name);
    /*public*/ Warrant* getByUserName(QString key);
    /*public*/ Warrant* provideWarrant(QString name) ;
    static WarrantManager* _instance;// = NULL;
    static /*public*/ WarrantManager* instance();

signals:
 void propertyChange(PropertyChangeEvent *e);
public slots:

};

#endif // WARRANTMANAGER_H
