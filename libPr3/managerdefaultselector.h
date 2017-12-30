#ifndef MANAGERDEFAULTSELECTOR_H
#define MANAGERDEFAULTSELECTOR_H

#include "abstractpreferencesmanager.h"
#include "propertychangelistener.h"
#include "logger.h"
#include "libPr3_global.h"
#include <QList>
//class Item;

class Class;
class LIBPR3SHARED_EXPORT ManagerDefaultSelector : public AbstractPreferencesManager
{
    Q_OBJECT
public:
    explicit ManagerDefaultSelector(QObject *parent = 0);
 ~ManagerDefaultSelector() {}
 ManagerDefaultSelector(const ManagerDefaultSelector&) : AbstractPreferencesManager() {}
 /*public*/ /*final*/ QHash<QString, QString> defaults;// = new Hashtable<>();
 /*public*/ QString getDefault(QString managerClass);
 /*public*/ void setDefault(QString managerClass, QString userName);
 /*public*/ InitializationException* configure();
 /*public*/ void initialize(Profile* profile) throw (InitializationException);
 /*public*/ void savePreferences(Profile* profile);

 /*public*/ /*static*/ class Item1 {
 public:

     /*public*/ QString typeName;
     /*public*/ QString managerClass;
     Item1(QString typeName,QString managerClass);
 private:
 };
 /*final*/ /*public*/ QList<Item1> knownManagers;
public slots:
 /*public*/ void propertyChange(PropertyChangeEvent *);

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("ManagerDefaultSelector");
 void removeConnectionAsDefault(QString removedName);
 /*private*/ QString nameForClass(/*@Non NULL */QString cls);
 /*private*/ QString classForName(/*@Non NULL*/ QString name);

};

Q_DECLARE_METATYPE(ManagerDefaultSelector)
#endif // MANAGERDEFAULTSELECTOR_H
