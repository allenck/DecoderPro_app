#ifndef TIMESINCEMIDNIGHTSWING_H
#define TIMESINCEMIDNIGHTSWING_H

#include "abstractanalogexpressionswing.h"

class JComboBox;
class TimeSinceMidnightSwing : public AbstractAnalogExpressionSwing
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit TimeSinceMidnightSwing(QObject *parent = nullptr) : AbstractAnalogExpressionSwing(parent) {}
  ~TimeSinceMidnightSwing() {setObjectName("TimeSinceMidnightSwing");}
  TimeSinceMidnightSwing(const TimeSinceMidnightSwing&) : AbstractAnalogExpressionSwing() {}
  /*public*/  bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object)override;
  /*public*/  QString toString()override;
  /*public*/  void dispose()override;

  QObject* sself() override{return (QObject*)this;}

 private:
  /*private*/ JComboBox/*<Type>*/* _stateComboBox;

 protected:
  /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;

};
Q_DECLARE_METATYPE(TimeSinceMidnightSwing)
#endif // TIMESINCEMIDNIGHTSWING_H
