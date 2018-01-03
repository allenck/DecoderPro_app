#ifndef STARTUPACTIONMODELUTIL_H
#define STARTUPACTIONMODELUTIL_H
#include "bean.h"
#include "exceptions.h"
#include "class.h"

class ActionAttributes;
class Logger;
class StartupActionModelUtil : public Bean
{
 Q_OBJECT
public:
 StartupActionModelUtil(QObject* parent = 0);
 static /*public*/ StartupActionModelUtil* getDefault();
 /*public*/ QString getActionName(/*@NonNULL Class<?>*/Class* clazz);
 /*public*/ QString getActionName(/*@NonNULL*/ QString className);
 /*public*/ bool isSystemConnectionAction(/*@NonNULL*/ Class* clazz);
 /*public*/ bool isSystemConnectionAction(/*@NonNULL*/ QString className);
 /*public*/ QString getClassName(/*@NonNULL*/ QString name);
 /*public*/ QStringList getNames();
 /*public*/ QVector<Class*> getClasses();
 /*public*/ void addAction(/*@NonNULL*/ QString strClass, /*@NonNULL*/ QString name) throw (ClassNotFoundException);
 /*public*/ void removeAction(/*@NonNULL*/ QString strClass) throw (ClassNotFoundException);
 /*public*/ QString getOverride(/*@Nullable */QString name);

private:
 /*private*/ QMap<Class*, ActionAttributes*>* actions;// = NULL;
 /*private*/ QMap<QString, Class*>* overrides;// = NULL;
 /*private*/ QList<QString>* actionNames;// = NULL; // built on demand, invalidated in changes to actions
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger(StartupActionModelUtil.class);
 /*private*/ void prepareActionsHashMap();
 QMap<QString, QString> actionListBundle;

};
/*private*/ /*static*/ class ActionAttributes
{
public:
    /*final*/ QString name;
 Class* clazz;
    /*final*/ bool isSystemConnectionAction;

    ActionAttributes(QString name, Class* clazz);
};
#endif // STARTUPACTIONMODELUTIL_H
