#ifndef DEFAULTMODULESWING_H
#define DEFAULTMODULESWING_H

#include "abstractswingconfigurator.h"

class DefaultModuleSwing : public AbstractSwingConfigurator
{
 public:
  explicit DefaultModuleSwing(QObject *parent = nullptr);
};

#endif // DEFAULTMODULESWING_H
