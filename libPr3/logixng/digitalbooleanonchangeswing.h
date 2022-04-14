#ifndef DIGITALBOOLEANONCHANGESWING_H
#define DIGITALBOOLEANONCHANGESWING_H

#include "abstractbooleanactionswing.h"
#include "digitalbooleanonchange.h"
#include "jcombobox.h"

class DigitalBooleanOnChangeSwing : public AbstractBooleanActionSwing
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit DigitalBooleanOnChangeSwing(QObject *parent = nullptr)
   : AbstractBooleanActionSwing(parent) {setObjectName("DigitalBooleanOnChangeSwing");}
  ~DigitalBooleanOnChangeSwing() {}
  DigitalBooleanOnChangeSwing(const DigitalBooleanOnChangeSwing&) : AbstractBooleanActionSwing() {}
  /*public*/  bool validate(/*@Nonnull*/ QList<QString>* errorMessages) override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*CheckForNull*/ QString userName) override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object) override;
  /*public*/  QString toString()override;
  /*public*/  void dispose()override;


  QObject* sself() override {return (QObject*)this;}
 private:
  DigitalBooleanOnChange::Trigger::TargetAction type = DigitalBooleanOnChange::Trigger::TargetAction::CHANGE;
  /*private*/ JComboBox/*<DigitalBooleanOnChange.Trigger>*/* _triggerComboBox;

 protected:
  /*protected*/ void createPanel(/*CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;

};
Q_DECLARE_METATYPE(DigitalBooleanOnChangeSwing);
#endif // DIGITALBOOLEANONCHANGESWING_H
