#ifndef ANALOGFORMULASWING_H
#define ANALOGFORMULASWING_H

#include "abstractanalogexpressionswing.h"

class AnalogFormulaSwing : public AbstractAnalogExpressionSwing
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit AnalogFormulaSwing(QObject *parent = nullptr)
   : AbstractAnalogExpressionSwing(parent){setObjectName("AnalogFormulaSwing");}
  ~AnalogFormulaSwing() {}
  AnalogFormulaSwing(const AnalogFormulaSwing&) : AbstractAnalogExpressionSwing() {}
  /*public*/  bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object)override;
  /*public*/  QString toString()override;
  /*public*/  void dispose()override;

  QObject* sself() override{return (QObject*)this;}

 private:
  static Logger* log;
  /*private*/ JTextField* _formula;

 protected:
  /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;

};
Q_DECLARE_METATYPE(AnalogFormulaSwing)
#endif // ANALOGFORMULASWING_H
