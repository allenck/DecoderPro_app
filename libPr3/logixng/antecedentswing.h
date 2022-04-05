#ifndef ANTECEDENTSWING_H
#define ANTECEDENTSWING_H

#include "abstractdigitalexpressionswing.h"
#include "jtextfield.h"

class AntecedentSwing : public AbstractDigitalExpressionSwing
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit AntecedentSwing(QObject *parent = nullptr) : AbstractDigitalExpressionSwing(parent){}
  ~AntecedentSwing() {}
  AntecedentSwing(const AntecedentSwing&) : AbstractDigitalExpressionSwing() {}
  /*public*/  bool validate(/*@Nonnull*/ QList<QString> errorMessages)override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName)override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object)override;
  /*public*/  QString toString()override;
  /*public*/  void dispose()override;

  QObject* sself() override {return (QObject*)this;}
 private:
  static Logger* log;
  /*private*/ JTextField* _antecedent;

 protected:
  /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull */JPanel* buttonPanel)override;

};
Q_DECLARE_METATYPE(AntecedentSwing)
#endif // ANTECEDENTSWING_H
