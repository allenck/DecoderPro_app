#ifndef RUNTIMEPERMISSION_H
#define RUNTIMEPERMISSION_H
#include "basicpermission.h"

class RuntimePermission : public BasicPermission
{
public:
 //RuntimePermission();
 /*public*/ RuntimePermission(QString name);

 /**
  * Creates a new RuntimePermission object with the specified name.
  * The name is the symbolic name of the RuntimePermission, and the
  * actions String is currently unused and should be null.
  *
  * @param name the name of the RuntimePermission.
  * @param actions should be null.
  *
  * @throws NullPointerException if <code>name</code> is <code>null</code>.
  * @throws IllegalArgumentException if <code>name</code> is empty.
  */

 /*public*/ RuntimePermission(QString name, QString actions);

};

#endif // RUNTIMEPERMISSION_H
