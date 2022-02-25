#ifndef ABSTRACTINSTANCEINITIALIZER_H
#define ABSTRACTINSTANCEINITIALIZER_H
#include "instanceinitializer.h"
#include <QObject>

class AbstractInstanceInitializer : public QObject, public InstanceInitializer
{
  Q_OBJECT
  Q_INTERFACES(InstanceInitializer)
public:
 AbstractInstanceInitializer(QObject* parent = nullptr);
 /*public*/ /*<T>*/ QObject* getDefault(/*Class<T>*/QString type) const override /*throw (IllegalArgumentException)*/;
 /*public*/ QSet</*Class<?>*/QString> getInitalizes()override;

};

#endif // ABSTRACTINSTANCEINITIALIZER_H
