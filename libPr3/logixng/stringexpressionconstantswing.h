#ifndef STRINGEXPRESSIONCONSTANTSWING_H
#define STRINGEXPRESSIONCONSTANTSWING_H

#include "abstractstringexpressionswing.h"
#include "jtextfield.h"

class StringExpressionConstantSwing : public AbstractStringExpressionSwing
{
 public:
  explicit StringExpressionConstantSwing(QObject *parent = nullptr);
  /*public*/  bool validate(/*@Nonnull*/ QList<QString>* errorMessages) override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName)override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object)override;
  /*public*/  QString toString()override;
  /*public*/  void dispose()override;

 private:
  /*private*/ JTextField* _constant;


 protected:
  /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;

};

#endif // STRINGEXPRESSIONCONSTANTSWING_H
