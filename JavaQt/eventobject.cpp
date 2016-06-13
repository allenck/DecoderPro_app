#include "eventobject.h"
#include "exceptions.h"
//const long long EventObject::serialVersionUID = 5516075349620653480L;
//EventObject::EventObject(QObject *parent) :
//    QObject(parent)
//{
//}
/**
 * <p>
 * The root class from which all event state objects shall be derived.
 * <p>
 * All Events are constructed with a reference to the object, the "source",
 * that is logically deemed to be the object upon which the Event in question
 * initially occurred upon.
 *
 * @since JDK1.1
 */

//public class EventObject implements java.io.Serializable {

/**
 * Constructs a prototypical Event.
 *
 * @param    source    The object on which the Event initially occurred.
 * @exception  IllegalArgumentException  if source is null.
 */
/*public*/ EventObject::EventObject(QObject* source,  QObject *parent) : QObject(parent)
{
 //this->parent = parent;
 if (source == NULL)
  throw new IllegalArgumentException("null source");
 this->source = source;
}

 /**
  * The object on which the Event initially occurred.
  *
  * @return   The object on which the Event initially occurred.
  */
 /*public*/ QObject* EventObject::getSource()
{
 return source;
}

/**
 * Returns a String representation of this EventObject.
 *
 * @return  A a String representation of this EventObject.
 */
/*public*/ QString EventObject::toString() {
    return /*getClass().getName() + */"[source=" + source->objectName() + "]";
}
