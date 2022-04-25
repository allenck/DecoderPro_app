#ifndef ACTIONPOWERSWING_H
#define ACTIONPOWERSWING_H

#include "abstractdigitalactionswing.h"

class JComboBox;
class ActionPowerSwing : public AbstractDigitalActionSwing
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit ActionPowerSwing(QObject *parent = nullptr);
  ~ActionPowerSwing() {}
  ActionPowerSwing(const ActionPowerSwing&) : AbstractDigitalActionSwing() {}
  /*public*/  bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
  /*public*/  QString getAutoSystemName() override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*CheckForNull*/ QString userName) override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object) override;
  /*public*/  QString toString() override;
  /*public*/  void dispose()override;
  QObject* sself() override{return (QObject*)this;}

 private:
  /*private*/ JComboBox/*<PowerState>*/* _stateComboBox;

 protected:
  /*protected*/ void createPanel(/*CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;

};
Q_DECLARE_METATYPE(ActionPowerSwing)
#endif // ACTIONPOWERSWING_H
