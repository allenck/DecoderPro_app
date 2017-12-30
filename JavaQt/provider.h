#ifndef PROVIDER_H
#define PROVIDER_H
#include "properties.h"
#include <QVariant>

class Provider : public Properties
{
public:
 //Provider();
 /*public*/ QString getName();
 /*public*/ double getVersion();
 /*public*/ QString getInfo();
 /*public*/ QString toString();
 /*public*/ /*synchronized*/ void clear();
 /*public*/ /*synchronized*/ QVariant put(QVariant key, QVariant value);
 /*public*/ QVariant get(QVariant key);

private:
 /**
  * The provider name.
  *
  * @serial
  */
 /*private*/ QString name;

 /**
  * A description of the provider and its services.
  *
  * @serial
  */
 /*private*/ QString info;

 /**
  * The provider version number.
  *
  * @serial
  */
 /*private*/ double version;


 // /*private*/ /*transient*/ Set<Map.Entry<Object,Object>> entrySet = null;
 /*private*/ /*transient*/ int entrySetCallCount;// = 0;

 /*private*/ /*transient*/ bool initialized;
 /*private*/ void checkInitialized();
 /*private*/ void check(QString directive);
 /*private*/ void putId();

protected:
 /*protected*/ Provider(QString name, double version, QString info);

};

#endif // PROVIDER_H
