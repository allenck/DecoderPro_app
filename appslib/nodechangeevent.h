#ifndef NODECHANGEEVENT_H
#define NODECHANGEEVENT_H
#include "eventobject.h"

class Preferences;
class NodeChangeEvent : public EventObject
{
public:
 /*public*/ NodeChangeEvent(Preferences* parent, Preferences* child);
 /*public*/ Preferences* getParent();
 /*public*/ Preferences* getChild();

private:
 /**
  * The node that was added or removed.
  *
  * @serial
  */
 /*private*/ Preferences* child;
 /*private*/ static /*final*/ long serialVersionUID;// = 8068949086596572957L;

};

#endif // NODECHANGEEVENT_H
