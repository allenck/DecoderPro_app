#ifndef DEFAULTCONDITIONALMANAGER_H
#define DEFAULTCONDITIONALMANAGER_H

#include <QObject>
#include "conditionalmanager.h"
#include "libPr3_global.h"

class Logger;
class Logix;
class Conditional;
class LIBPR3SHARED_EXPORT DefaultConditionalManager : public ConditionalManager
{
    Q_OBJECT
public:
    explicit DefaultConditionalManager(QObject *parent = 0);
    /*public*/ int getXMLOrder();
    /*public*/ QString getSystemPrefix();
    /*public*/ char typeLetter() ;
    /*public*/ Conditional* createNewConditional(QString systemName, QString userName) ;
    /*public*/ Logix* getParentLogix(QString name);
    /*public*/ void deleteConditional(Conditional* c);
    /*public*/ Conditional* getConditional(Logix* x, QString name);
    /*public*/ Conditional* getConditional(QString name);
    /*public*/ Conditional* getByUserName(QString key);
    /*public*/ Conditional* getByUserName(Logix* x, QString key);
    /*public*/ Conditional* getBySystemName(QString name);
    /*public*/ QStringList getSystemNameList();
    /*public*/ QStringList getSystemNameListForLogix(Logix* x);
    static DefaultConditionalManager* _instance;// = null;
    static /*public*/ DefaultConditionalManager* instance();
    /*public*/ QMap<QString, QList<QString> > getWhereUsedMap();
    /*public*/ void addWhereUsed(QString target, QString reference);
    /*public*/ QList<QString> getWhereUsed(QString target);
    /*public*/ void removeWhereUsed(QString target, QString reference);
    /*public*/ void displayWhereUsed();
    /*public*/ QList<QString> getTargetList(QString reference);

signals:

public slots:
private:
    /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("DefaultConditionalManager");

    // --- Conditional Where Used processes ---

    /**
     * Maintain a list of conditionals that refer to a particular conditional.
     * @since 4.7.4
     */
    /*private*/ /*final*/ QMap<QString, QList<QString> > conditionalWhereUsed;// = new HashMap<>();
    /*private*/ static /*final*/ QStringList PATTERNS;

protected:
 /*protected*/ void handleUserNameUniqueness(Conditional* s);

};

#endif // DEFAULTCONDITIONALMANAGER_H
