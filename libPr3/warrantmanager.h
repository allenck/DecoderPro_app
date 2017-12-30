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
    ~WarrantManager() {}
    WarrantManager(const WarrantManager&) : AbstractManager() {}
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
    /*public*/ bool isAssignableFromType() {return true;}

signals:
 void propertyChange(PropertyChangeEvent *e);
public slots:

};
Q_DECLARE_METATYPE(WarrantManager)
#endif // WARRANTMANAGER_H
