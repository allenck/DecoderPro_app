#ifndef CLASS_H
#define CLASS_H
#include <QObject>

class ClassLoader;
template<class T>
class Class
{
 Q_OBJECT
public:
 Class();
 /*public*/ QString toString();
 /*public*/ QString toGenericString();
 /*public*/ static T* forName(QString className);

private:
 /*private*/ static /*final*/ int ANNOTATION;//= 0x00002000;
 /*private*/ static /*final*/ int ENUM      ;//= 0x00004000;
 /*private*/ static /*final*/ int SYNTHETIC ;//= 0x00001000;

 /*private*/ static /*native*/ void registerNatives();
 /*private*/ Class(ClassLoader* loader);
 ClassLoader* classLoader;
};

#endif // CLASS_H
