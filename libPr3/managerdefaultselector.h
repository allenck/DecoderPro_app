#ifndef MANAGERDEFAULTSELECTOR_H
#define MANAGERDEFAULTSELECTOR_H

#include "abstractpreferencesmanager.h"
#include "propertychangelistener.h"
#include "logger.h"
#include "libPr3_global.h"
#include <QList>
//class Item;

class SystemConnectionMemo;
class MemoListener;
class Class;
class LIBPR3SHARED_EXPORT ManagerDefaultSelector : public AbstractPreferencesManager
{
    Q_OBJECT
public:
 explicit ManagerDefaultSelector(QObject *parent = 0);
 ~ManagerDefaultSelector() {}
 ManagerDefaultSelector(const ManagerDefaultSelector&) : AbstractPreferencesManager() {}
 /*public*/ /*final*/ QMap<QString, QString> defaults = QMap</*Class<?>*/QString, QString>();
 /*public*/ QString getDefault(QString managerClass);
 /*public*/ void setDefault(QString managerClass, QString userName);
// /*public*/ void configure();
 /*public*/ InitializationException* configure(Profile* profile);
 /*public*/ /*static*/ class Item {
 public:
     /*public*/ QString typeName;
     /*public*/ QString managerClass;
     Item(QString typeName,QString managerClass);
 private:
 };
 /*public*/ /*final*/ static QString ALL_INTERNAL_DEFAULTS;// = "allInternalDefaults";

 Q_INVOKABLE/*public*/ void initialize(Profile* profile) override /*throws InitializationException*/;
 /*public*/ void savePreferences(Profile* profile) override;
 /*public*/ bool isPreferencesValid(Profile* profile);

 /*final*/ /*public*/ QList<Item> knownManagers = {
   Item("<html>Throttles</html>", "ThrottleManager"),
   Item("<html>Power<br>Control</html>", "PowerManager"),
   Item("<html>Command<br>Station</html>", "CommandStation"),
   Item("<html>Service<br>Programmer</html>", "GlobalProgrammerManager"),
   Item("<html>Ops Mode<br>Programmer</html>", "AddressedProgrammerManager"),
   Item("<html>Consists</html>", "ConsistManager")
};

 ManagerDefaultSelector* self() {return this;}
public slots:
 /*public*/ void propertyChange(PropertyChangeEvent *);

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("ManagerDefaultSelector");
 void removeConnectionAsDefault(QString removedName);
 /*private*/ QString nameForClass(/*@Non NULL */QString cls);
 /*private*/ QString classForName(/*@Non NULL*/ QString name);
 MemoListener* memoListener = nullptr;
 /*private*/ bool isPreferencesValid(Profile* profile, QList<QObject *>* connections);
 /*private*/ bool allInternalDefaultsValid = false;

 friend class MemoListener;
};
Q_DECLARE_METATYPE(ManagerDefaultSelector)

class MemoListener : public QObject, public PropertyChangeListener
{
 Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
 ManagerDefaultSelector* mds;
public:
 MemoListener(ManagerDefaultSelector* mds) {this->mds = mds;}
 QObject* pself() override{return (QObject*)this;}
public slots:
 void propertyChange(PropertyChangeEvent* e);
};

#endif // MANAGERDEFAULTSELECTOR_H
