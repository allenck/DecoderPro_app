#ifndef DEFAULTFEMALEDIGITALBOOLEANACTIONSOCKETTESTACTION_H
#define DEFAULTFEMALEDIGITALBOOLEANACTIONSOCKETTESTACTION_H

#include <abstractaction.h>
#include <QObject>

class DefaultFemaleDigitalBooleanActionSocketTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  explicit DefaultFemaleDigitalBooleanActionSocketTestAction(QObject *parent = nullptr);
 public slots:
  void actionPerformed();
 private:
  static Logger* log;};

#endif // DEFAULTFEMALEDIGITALBOOLEANACTIONSOCKETTESTACTION_H
