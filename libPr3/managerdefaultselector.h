#ifndef MANAGERDEFAULTSELECTOR_H
#define MANAGERDEFAULTSELECTOR_H

#include "abstractpreferencesmanager.h"
#include "propertychangelistener.h"
#include "logger.h"
#include "libPr3_global.h"
#include <QList>
//class Item;

class MemoListener;
class Class;
class LIBPR3SHARED_EXPORT ManagerDefaultSelector : public AbstractPreferencesManager
{
    Q_OBJECT
public:
 explicit ManagerDefaultSelector(QObject *parent = 0);
 ~ManagerDefaultSelector() {}
 ManagerDefaultSelector(const ManagerDefaultSelector&) : AbstractPreferencesManager() {}
 /*public*/ /*final*/ QMap<QString, QString> defaults;// = new Hashtable<>();
 /*public*/ QString getDefault(QString managerClass);
 /*public*/ void setDefault(QString managerClass, QString userName);
 /*public*/ void configure();
// /*public*/ void initialize(Profile* profile) throw (InitializationException);
// /*public*/ void savePreferences(Profile* profile);
 /*public*/ /*static*/ class Item1 {
 public:

     /*public*/ QString typeName;
     /*public*/ QString managerClass;
     Item1(QString typeName,QString managerClass);
 private:
 };
 /*final*/ /*public*/ QList<Item1> knownManagers;
 ManagerDefaultSelector* self() {return this;}
public slots:
 /*public*/ void propertyChange(PropertyChangeEvent *);

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("ManagerDefaultSelector");
 void removeConnectionAsDefault(QString removedName);
 /*private*/ QString nameForClass(/*@Non NULL */QString cls);
 /*private*/ QString classForName(/*@Non NULL*/ QString name);
 MemoListener* memoListener = nullptr;
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
 QObject* self() override{return (QObject*)this;}
public slots:
 void propertyChange(PropertyChangeEvent* e);
};

#endif // MANAGERDEFAULTSELECTOR_H
