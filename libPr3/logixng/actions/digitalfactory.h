#ifndef DIGITALFACTORY_H
#define DIGITALFACTORY_H

#include <QObject>
#include "../digitalactionfactory.h"

class DigitalFactory : public QObject, public DigitalActionFactory
{
  Q_OBJECT
  Q_INTERFACES(DigitalActionFactory)
 public:
  explicit DigitalFactory(QObject *parent = nullptr);
  /*public*/ QSet<QHash<Category, /*Class<? extends DigitalActionBean>*/QString>> getActionClasses()override;

 signals:

};

#endif // DIGITALFACTORY_H
