#ifndef CLASS_H
#define CLASS_H
#include <QObject>
#include "exceptions.h"

class ClassLoader;

class Class
{
 Q_OBJECT
public:
 Class();
 /*public*/ QString toString();
 /*public*/ QString toGenericString();
 /*public*/ static Class* forName(QString className);
 /*public*/ bool isInstance(QObject* obj);
 /*public*/ QString getCanonicalName();
 /*public*/ Class* newInstance() throw (InstantiationException, IllegalAccessException);
 /*public*/ /*native*/ bool isAssignableFrom(QString cls);

private:
 /*private*/ static /*final*/ int ANNOTATION;//= 0x00002000;
 /*private*/ static /*final*/ int ENUM      ;//= 0x00004000;
 /*private*/ static /*final*/ int SYNTHETIC ;//= 0x00001000;

 /*private*/ static /*native*/ void registerNatives();
 /*private*/ Class(ClassLoader* loader);
 ClassLoader* classLoader;
};

#endif // CLASS_H
