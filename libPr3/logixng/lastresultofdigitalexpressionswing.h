#ifndef LASTRESULTOFDIGITALEXPRESSIONSWING_H
#define LASTRESULTOFDIGITALEXPRESSIONSWING_H

#include "abstractdigitalexpressionswing.h"

class JComboBox;
class LastResultOfDigitalExpressionSwing : public AbstractDigitalExpressionSwing
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit LastResultOfDigitalExpressionSwing(QObject *parent = nullptr);
  ~LastResultOfDigitalExpressionSwing() {}
  LastResultOfDigitalExpressionSwing(const LastResultOfDigitalExpressionSwing&) : AbstractDigitalExpressionSwing() {}
  /*public*/  bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*CheckForNull*/ QString userName) override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object)override;
  /*public*/  QString toString()override;
  /*public*/  void dispose()override;

  QObject* sself() override {return (QObject*)this;}
 private:
  /*private*/ JComboBox/*<String>*/* _expressionsComboBox;

 protected:
  /*protected*/ void createPanel(/*CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;

};
Q_DECLARE_METATYPE(LastResultOfDigitalExpressionSwing)
#endif // LASTRESULTOFDIGITALEXPRESSIONSWING_H
