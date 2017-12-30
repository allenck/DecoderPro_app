#ifndef BASICPERMISSION_H
#define BASICPERMISSION_H
#include "permission.h"

class BasicPermission : public Permission
{
public:
 BasicPermission();
 /*public*/ BasicPermission(QString name);
 /*public*/ BasicPermission(QString name, QString actions);
 /*public*/ bool implies(Permission* p);
 /*public*/ bool equals(QObject* obj);

private:
 // does this permission have a wildcard at the end?
 /*private*/ /*transient*/ bool wildcard;

 // the name without the wildcard on the end
 /*private*/ /*transient*/ QString path;

 // is this permission the old-style exitVM permission (pre JDK 1.6)?
 /*private*/ /*transient*/ bool exitVM;
 /*private*/ void init(QString name);

};

#endif // BASICPERMISSION_H
