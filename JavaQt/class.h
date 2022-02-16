#ifndef CLASS_H
#define CLASS_H
#include <QObject>
#include "exceptions.h"

class ClassLoader;
class Logger;
class Class : QObject
{
 Q_OBJECT
public:
 Class();
 /*public*/ QString toString();
 /*public*/ QString toGenericString();
 /*public*/ static Class* forName(QString className);
 /*public*/ bool isInstance(QObject* obj);
 /*public*/ QString getCanonicalName();
 /*public*/ Class* newInstance() /*throw (InstantiationException, IllegalAccessException)*/;
 /*public*/ /*native*/ bool isAssignableFrom(QString cls);
 ///*pubic*/ QString className();
 /*public*/ static bool isAssignableFrom(QString clazz, QString type);
 /*public*/ QString getName() {return metaObject()->className();}
 /*public*/ Class *getConstructor();
private:
 /*private*/ static /*final*/ int ANNOTATION;//= 0x00002000;
 /*private*/ static /*final*/ int ENUM      ;//= 0x00004000;
 /*private*/ static /*final*/ int SYNTHETIC ;//= 0x00001000;
 QString _name;
// void setName(QString);
 /*private*/ static /*native*/ void registerNatives();
 /*private*/ Class(ClassLoader* loader);
 ClassLoader* classLoader;
 static Logger* log;
};

#endif // CLASS_H
