#ifndef EXPRESSIONREFERENCESWING_H
#define EXPRESSIONREFERENCESWING_H

#include "abstractdigitalexpressionswing.h"

class JTextField;
class JComboBox;
class ExpressionReferenceSwing : public AbstractDigitalExpressionSwing
{
  Q_OBJECT
 public:
  explicit ExpressionReferenceSwing(QObject *parent = nullptr);
  ~ExpressionReferenceSwing() {}
  ExpressionReferenceSwing(const ExpressionReferenceSwing&) : AbstractDigitalExpressionSwing() {}
  /*public*/  bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
  /*public*/  QString getAutoSystemName()override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*CheckForNull*/ QString userName)override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object) override;
  /*public*/  QString toString() override;
  /*public*/  void dispose()override;

  QObject* sself() override{return (QObject*)this;}
 private:
  /*private*/ JTextField* _sensorReferenceTextField;
  /*private*/ JComboBox/*<Is_IsNot_Enum>*/* _is_IsNot_ComboBox;
  /*private*/ JComboBox/*<PointsTo>*/* _stateComboBox;

 protected:
  /*protected*/ void createPanel(/*CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;

};
Q_DECLARE_METATYPE(ExpressionReferenceSwing)
#endif // EXPRESSIONREFERENCESWING_H
