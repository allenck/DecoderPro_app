#ifndef PROPERTYVETOEXCEPTION_H
#define PROPERTYVETOEXCEPTION_H
#include "exceptions.h"

class PropertyChangeEvent;
class PropertyVetoException : public Exception
{
public:
 PropertyVetoException(QString mess, PropertyChangeEvent* evt);
 /*public*/ PropertyChangeEvent* getPropertyChangeEvent();

private:
 /**
  * A PropertyChangeEvent describing the vetoed change.
  * @serial
  */
 /*private*/ PropertyChangeEvent* evt;

};

#endif // PROPERTYVETOEXCEPTION_H
