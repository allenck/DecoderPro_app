#ifndef ACTIONCLOCKSWING_H
#define ACTIONCLOCKSWING_H

#include "abstractdigitalactionswing.h"

class JComboBox;
class ActionClockSwing : public AbstractDigitalActionSwing
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit ActionClockSwing(QObject *parent = nullptr);
  ~ActionClockSwing() {}
  ActionClockSwing(const ActionClockSwing&) : AbstractDigitalActionSwing() {}
  /*public*/  bool validate(/*@Nonnull*/ QList<QString> *errorMessages);
  /*public*/  QString getAutoSystemName()override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*CheckForNull*/ QString userName)override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object)override;
  /*public*/  QString toString()override;
  /*public*/  void dispose()override;

  QObject* sself() override{return(QObject*)this;}
 private:
  /*private*/ JComboBox/*<ClockState>*/* _stateComboBox;
  /*private*/ JTextField* _timeTextField;
  /*private*/ int _minutes = 0;
  /*private*/ void setTimeField(int time);


 protected:
   /*protected*/ void createPanel(/*CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;

};
Q_DECLARE_METATYPE(ActionClockSwing)
#endif // ACTIONCLOCKSWING_H
