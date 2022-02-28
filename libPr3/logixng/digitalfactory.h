#ifndef DIGITALFACTORY_H
#define DIGITALFACTORY_H

#include "digitalactionfactory.h"
#include <QWidget>

class DigitalFactory : public QObject, public DigitalActionFactory
{
  Q_OBJECT
  Q_INTERFACES(DigitalActionFactory)
 public:
  DigitalFactory(QObject* parent = nullptr) : QObject(parent) {setObjectName("DigitalFactory");}
  /*public*/ QSet<QHash<Category*, /*Class<? extends DigitalActionBean>*/QString>> getActionClasses() override;

};

#endif // DIGITALFACTORY_H
