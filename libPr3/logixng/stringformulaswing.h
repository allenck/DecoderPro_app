#ifndef STRINGFORMULASWING_H
#define STRINGFORMULASWING_H

#include "abstractstringexpressionswing.h"

class JTextField;
class StringFormulaSwing : public AbstractStringExpressionSwing
{
  Q_OBJECT
 public:
  explicit StringFormulaSwing(QObject *parent = nullptr) : AbstractStringExpressionSwing(parent) {setObjectName("StringFormulaSwing");}
  ~StringFormulaSwing() {}
  StringFormulaSwing(const StringFormulaSwing&) : AbstractStringExpressionSwing() {}
  /*public*/  bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object)override;
  /*public*/  QString toString()override;
  /*public*/  void dispose()override;

  QObject* sself() override{return (QObject*)this;}

 private:
  /*private*/ JTextField* _formula;
  static Logger* log;

 protected:
  /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;

};
Q_DECLARE_METATYPE(StringFormulaSwing)
#endif // STRINGFORMULASWING_H
