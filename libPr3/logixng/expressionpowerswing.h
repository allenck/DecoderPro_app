#ifndef EXPRESSIONPOWERSWING_H
#define EXPRESSIONPOWERSWING_H

#include "abstractdigitalexpressionswing.h"
#include "jcombobox.h"

class ExpressionPowerSwing : public AbstractDigitalExpressionSwing
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit ExpressionPowerSwing(QObject *parent = nullptr);
  ~ExpressionPowerSwing() {}
  ExpressionPowerSwing(const ExpressionPowerSwing&) : AbstractDigitalExpressionSwing() {}
  /*public*/  bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
  /*public*/  QString getAutoSystemName()override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*CheckForNull*/ QString userName)override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object) override;
  /*public*/  QString toString() override;
  /*public*/  void dispose()override;

  QObject* sself() override{return (QObject*)this;}


 private:
  /*private*/ JComboBox/*<Is_IsNot_Enum>*/* _is_IsNot_ComboBox;
  /*private*/ JComboBox/*<PowerState>*/* _stateComboBox;


 protected:
  /*protected*/ void createPanel(/*CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;

};
Q_DECLARE_METATYPE(ExpressionPowerSwing)
#endif // EXPRESSIONPOWERSWING_H
