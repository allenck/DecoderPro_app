#ifndef ABSTRACTANALOGIOMANAGER_H
#define ABSTRACTANALOGIOMANAGER_H

#include "abstractmanager.h"
#include <QObject>
#include "analogiomanager.h"

class AbstractAnalogIOManager : public AbstractManager, public AnalogIOManager
{
  Q_OBJECT
  Q_INTERFACES(AnalogIOManager)
 public:
  explicit AbstractAnalogIOManager(SystemConnectionMemo* memo, QObject *parent = nullptr);
  /*public*/  int getXMLOrder() const override;
  /*public*/  QChar typeLetter() const override;
  /*public*/  QString getBeanTypeHandled(bool plural) const override;
  /*public*/  /*Class<AnalogIO>*/QString getNamedBeanClass()const override;
};

#endif // ABSTRACTANALOGIOMANAGER_H
