#ifndef DEFAULTCONDITIONALMANAGER_H
#define DEFAULTCONDITIONALMANAGER_H

#include <QObject>
#include "abstractmanager.h"
#include "libPr3_global.h"

class Logix;
class Conditional;
class LIBPR3SHARED_EXPORT DefaultConditionalManager : public AbstractManager
{
    Q_OBJECT
public:
    explicit DefaultConditionalManager(QObject *parent = 0);
    /*public*/ int getXMLOrder();
    /*public*/ QString getSystemPrefix();
    /*public*/ char typeLetter();
    /*public*/ Conditional* createNewConditional(QString systemName, QString userName) ;
    /*public*/ Logix* getParentLogix(QString name);
    /*public*/ void deleteConditional(Conditional* c);
    /*public*/ Conditional* getConditional(Logix* x, QString name);
    /*public*/ Conditional* getConditional(QString name);
    /*public*/ Conditional* getByUserName(QString key);
    /*public*/ Conditional* getByUserName(Logix* x, QString key);
    /*public*/ Conditional* getBySystemName(QString name);
    /*public*/ QStringList* getSystemNameListForLogix(Logix* x);
    static DefaultConditionalManager* _instance;// = null;
    static /*public*/ DefaultConditionalManager* instance();

signals:

public slots:
private:
    Logger* log;
};

#endif // DEFAULTCONDITIONALMANAGER_H
