#ifndef SIMPLEBINDINGS_H
#define SIMPLEBINDINGS_H

#include "bindings.h"
#include <QMap>

class SimpleBindings : public Bindings
{
public:
 /*public*/ SimpleBindings();
 /*public*/ SimpleBindings(QMap<QString,QObject*>* m);
private:
 /**
  * The <code>Map</code> field stores the attributes.
  */
 /*private*/ QMap<QString,QObject*>* map;


};

#endif // SIMPLEBINDINGS_H
