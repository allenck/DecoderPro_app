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
    /*public*/ int getXMLOrder()const override;
    /*public*/ QString getSystemPrefix() const override;
    /*public*/ QChar typeLetter() const override ;
    /*public*/ Conditional* createNewConditional(QString systemName, QString userName)  override;
    /*public*/ Logix* getParentLogix(QString name) override;
    /*public*/ void deleteConditional(Conditional* c) override;
    /*public*/ Conditional* getConditional(Logix* x, QString name) override;
    /*public*/ Conditional* getConditional(QString name) override;
    /*public*/ Conditional* getByUserName(QString key) override;
    /*public*/ Conditional* getByUserName(Logix* x, QString key)override;
    /*public*/ Conditional* getBySystemName(QString name) override;
    /*public*/ QStringList getSystemNameList() override;
    /*public*/ QStringList getSystemNameListForLogix(Logix* x) override;
    static DefaultConditionalManager* _instance;// = null;
    static /*public*/ DefaultConditionalManager* instance();
    /*public*/ QMap<QString, QList<QString> > getWhereUsedMap() override;
    /*public*/ void addWhereUsed(QString target, QString reference) override;
    /*public*/ QList<QString> getWhereUsed(QString target);
    /*public*/ void removeWhereUsed(QString target, QString reference) override;
    /*public*/ void displayWhereUsed() override;
    /*public*/ QList<QString> getTargetList(QString reference);
    /*public*/ QString getNamedBeanClass()const override {
        return "Conditional";
    }

    QObject* self() override {return (QObject*)this;}
    QObject* vself() override {return (QObject*)this;}
    QObject* pself() override{return (QObject*)this;}

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
