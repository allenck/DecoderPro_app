#ifndef DIGITALFORMULASWING_H
#define DIGITALFORMULASWING_H

#include "abstractdigitalexpressionswing.h"
#include "jtextfield.h"

class DigitalFormulaSwing : public AbstractDigitalExpressionSwing
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit DigitalFormulaSwing(QObject *parent = nullptr) : AbstractDigitalExpressionSwing(parent) {setObjectName("DigitalFormulaSwing");}
  ~DigitalFormulaSwing() {}
  DigitalFormulaSwing(const DigitalFormulaSwing&) : AbstractDigitalExpressionSwing() {}
  /*public*/  bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName)override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object)override;
  /*public*/  QString toString()override;
  /*public*/  void dispose()override;

  QObject* sself() override {return (QObject*)this;}
 private:
  static Logger* log;
  /*private*/ JTextField* _formula;

 protected:
  /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;


};
Q_DECLARE_METATYPE(DigitalFormulaSwing)
#endif // DIGITALFORMULASWING_H
